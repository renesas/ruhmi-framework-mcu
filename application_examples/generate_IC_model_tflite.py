# SPDX-License-Identifier: BSD-3-Clause

import tensorflow as tf
import keras
import numpy as np
import os
from PIL import Image

model = keras.applications.MobileNet(
    input_shape=(224, 224, 3),
    alpha=0.25,
    include_top=True,
    weights="imagenet",
    classifier_activation='softmax'
)

def preprocess_image(image_path):
    img = Image.open(image_path).convert('RGB')
    img_resized = img.resize((224, 224))
    img_np = np.array(img_resized).astype(np.float32)
    img_np = np.expand_dims(img_np, axis=0)
    return (img_np/127.5 - 1.0)

def get_image_paths_from_folder(folder_path, num_images=100):
    image_paths = []
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file.endswith(".JPEG"):
                image_paths.append(os.path.join(root, file))
            if len(image_paths) >= num_images:
                return image_paths
    return image_paths

folder = "./image_data/train"  # Calibration data, you can download from https://s3.amazonaws.com/fast-ai-imageclas/imagenette2-160.tgz
calibration_images = get_image_paths_from_folder(folder, num_images=300)

def representative_data_gen():
    for image_path in calibration_images:
        img_np = preprocess_image(image_path)
        yield [img_np]


converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8

converter.representative_dataset = representative_data_gen

tflite_model = converter.convert()

tflite_model_path = "mobilenet_v1.tflite"
with open(tflite_model_path, "wb") as f:
    f.write(tflite_model)