# SPDX-License-Identifier: BSD-3-Clause
import argparse
import os
import sys
from typing import List

import numpy as np
import tensorflow as tf
import keras
from PIL import Image

DATASET_DIR = "./imagenette2-160/imagenette2-160/val"
ERROR_MISSING_DS = (
    "Please download dataset untar in the same directory "
    "https://s3.amazonaws.com/fast-ai-imageclas/imagenette2-160.tgz"
)

def build_model():
    base = keras.applications.MobileNet(
        input_shape=(224, 224, 3),
        alpha=0.25,
        include_top=True,
        weights="imagenet",
        classifier_activation="softmax",
    )
    # Fix batch size to 1 for export
    inputs = keras.Input(shape=(224, 224, 3), batch_size=1)
    outputs = base(inputs)
    return keras.Model(inputs, outputs)

def preprocess_image(image_path: str) -> np.ndarray:
    img = Image.open(image_path).convert("RGB")
    img = img.resize((224, 224))
    arr = np.array(img, dtype=np.float32)
    arr = (arr / 127.5) - 1.0  # [-1, 1], matches MobileNet preprocess
    arr = np.expand_dims(arr, axis=0)  # shape (1, 224, 224, 3)
    return arr

def list_images(folder: str, need: int, exts=(".jpg", ".jpeg", ".png", ".bmp")) -> List[str]:
    if not os.path.isdir(folder):
        return []
    out = []
    for root, _, files in os.walk(folder):
        for f in files:
            if f.lower().endswith(exts):
                out.append(os.path.join(root, f))
                if len(out) >= need:
                    return out
    return out

def make_representative_dataset(calib_paths: List[str]):
    def gen():
        for p in calib_paths:
            yield [preprocess_image(p)]
    return gen

def convert_fp32(model: keras.Model) -> bytes:
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    return converter.convert()

def convert_int8(model: keras.Model, calib_paths: List[str]) -> bytes:
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
    converter.inference_input_type = tf.int8
    converter.inference_output_type = tf.int8
    converter.representative_dataset = make_representative_dataset(calib_paths)
    return converter.convert()

def main():
    parser = argparse.ArgumentParser(
        description="Export MobileNetV1 to TFLite in FP32 or INT8."
    )
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument("--fp32", action="store_true", help="Export FP32 TFLite")
    group.add_argument("--int8", action="store_true", help="Export INT8 TFLite")
    parser.add_argument(
        "--calib-images",
        type=int,
        default=300,
        help="Number of calibration images to use for INT8 (default: 300)",
    )
    parser.add_argument(
        "--dataset",
        type=str,
        default=DATASET_DIR,
        help=f'Calibration dataset root (default: "{DATASET_DIR}")',
    )
    args = parser.parse_args()

    # If no quantization flag, prompt once
    mode = None
    if args.fp32:
        mode = "fp32"
    elif args.int8:
        mode = "int8"
    else:
        choice = input("Choose quantization mode [int8|fp32]: ").strip().lower()
        if choice in ("int8",):
            mode = "int8"
        elif choice in ("fp32",):
            mode = "fp32"
        else:
            print("Invalid choice. Use --int8 or --fp32.", file=sys.stderr)
            sys.exit(2)

    model = build_model()

    if mode == "fp32":
        tflite_bytes = convert_fp32(model)
        out_path = "mobilenet_v1_FP32.tflite"
    else:
        # Check dataset presence
        if not os.path.isdir(args.dataset):
            print(f"Error: {ERROR_MISSING_DS}", file=sys.stderr)
            sys.exit(1)
        calib_paths = list_images(args.dataset, need=args.calib_images)
        if len(calib_paths) < args.calib_images:
            print(
                f"Found {len(calib_paths)} images, need {args.calib_images}. "
                f"{ERROR_MISSING_DS}",
                file=sys.stderr,
            )
            sys.exit(1)
        tflite_bytes = convert_int8(model, calib_paths)
        out_path = "mobilenet_v1_int8.tflite"

    with open(out_path, "wb") as f:
        f.write(tflite_bytes)
    print(f"Saved {out_path}")

if __name__ == "__main__":
    main()
