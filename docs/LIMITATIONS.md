# MERA 2.4.0 based limitations  

There are some known constraints and boundaries of the system.   
While designed to address a wide range of use cases, certain technical, operational, or design limitations may apply. Understanding these limitations ensures optimal deployment and helps guide workarounds or future enhancements.

## Quantizer Limitations

Below is a table of different operators and the Quantizer support for each of them. Depending on the target (MCU_CPU or MCU_ETHOS) different types could be available based on the fatures of C-Codegen and/or Vela.
Other operators are not supported for quantization, those are marked with X.


Table 1: Quantizer Operator Support

|Operator Name|MCU_CPU|MCU_ETHOS|
|---|---|---|
|Conv2d|A8W8|A8W8|
|ConvTranspose|A8W8|A8W8|
|Gemm|A8W8|A8W8|
|Add|A8|A8|
|Sub|A8|A8|
|Mul|F32|A8|
|Mul [ONNX]|A8|A8|
|Div|A8|A8|
|ReLU|A8|A8|
|HardSwish|F32|A8|
|HardSigmoid|A8|A8|
|LeakyReLU|A8|A8|
|MaxPool|A8|A8|
|AveragePool|F32|A8|
|Softmax|A8|A8|
|Reshape|A8|A8|
|Squeeze|A8|A8|
|Transpose|A8|A8|
|ConvertLayout|A8|A8|
|Concatenate|A8|A8|
|Slice|A8|A8|
|BatchNorm|A8|A8|
|Clip|A8|A8|
|Tanh|A8|A8|
|Sigmoid|A8|A8|
|Sigmoid [ONNX]|F32|A8|
|Silu (HSwish)|A8|A8|
|Minimum|F32|F32|
|Maximum|X|X|
|ReduceMax|A8|A8|
|ReduceMean|A8|A8|
|ReduceSum|A8|A8|
|Pack|A8|A8|
|Resize2d|F32|A8|
|PReLU|A8|A8|
|Pad|A8|A8|
|MirrorPad|X|X|
|PadV2|X|X|
|Log|F32|F32|
|Neg|F32|F32|
|Exp|F32|A8|
|Abs|X|X|
|Sqrt|X|X|
|FloorDiv|X|X|
|ArgMax|X|X|
|GatherNd|X|X|
|RSqrt|X|X|
|SquaredDifference|X|X|


## C-Codegen Limitations

• tfl.concatenation (TFL::ConcatenationOp) Only supports up to 4 dimensional inputs.  


