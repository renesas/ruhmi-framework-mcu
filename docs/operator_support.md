## Operator support 

Currently, RUHMI framework is backed by MERA compiler powered by EdgeCortix. 

The compiler accepts models from various frameworks such as Executorch (.pte), Tensorflow lite (.tflite) and ONNX (.onnx). Which are then lowered down to TFlite dialect that c-code gen is built upon. The tables below represent what operators are supported from each framework and finally to what operator it would be lowered down to.

> **Note:** The compiler processes inputted model differently according to selected platform and target and not every combination of support should be expected for every operator in the list.

## TensorFlow lite front-end operator support

| TFL Operation                  | TFL Op Class                  |
|-------------------------------|-------------------------------|
| tfl.abs                       | TFL::AbsOp                    |
| tfl.quantize                  | TFL::QuantizeOp               |
| tfl.add                       | TFL::AddOp                    |
| tfl.reduce_max                | TFL::ReduceMaxOp              |
| tfl.average_pool_2d          | TFL::AveragePool2DOp          |
| tfl.relu                      | TFL::ReluOp                   |
| tfl.batch_to_space_nd        | TFL::BatchToSpaceNdOp         |
| tfl.relu6                     | TFL::Relu6Op                  |
| tfl.concatenation            | TFL::ConcatenationOp          |
| tfl.reshape                   | TFL::ReshapeOp                |
| tfl.conv_2d                   | TFL::Conv2DOp                 |
| tfl.resize_bilinear          | TFL::ResizeBilinearOp         |
| tfl.depthwise_conv_2d        | TFL::DepthwiseConv2DOp        |
| tfl.resize_nearest_neighbor  | TFL::ResizeNearestNeighborOp  |
| tfl.dequantize                | TFL::DequantizeOp             |
| tfl.rsqrt                     | TFL::RsqrtOp                  |
| tfl.exp                       | TFL::ExpOp                    |
| tfl.slice                     | TFL::SliceOp                  |
| tfl.expand_dims              | TFL::ExpandDimsOp             |
| tfl.softmax                   | TFL::SoftmaxOp                |
| tfl.fully_connected          | TFL::FullyConnectedOp         |
| tfl.space_to_batch_nd        | TFL::SpaceToBatchNdOp         |
| tfl.hard_swish               | TFL::HardSwishOp              |
| tfl.split                     | TFL::SplitOp                  |
| tfl.leaky_relu               | TFL::LeakyReluOp              |
| tfl.split_v                   | TFL::SplitVOp                 |
| tfl.log                       | TFL::LogOp                    |
| tfl.sqrt                      | TFL::SqrtOp                   |
| tfl.log_softmax              | TFL::LogSoftmaxOp             |
| tfl.squared_difference       | TFL::SquaredDifferenceOp      |
| tfl.logistic                  | TFL::LogisticOp               |
| tfl.strided_slice            | TFL::StridedSliceOp           |
| tfl.max_pool_2d              | TFL::MaxPool2DOp              |
| tfl.sub                       | TFL::SubOp                    |
| tfl.mean                      | TFL::MeanOp                   |
| tfl.sum                       | TFL::SumOp                    |
| tfl.minimum                   | TFL::MinimumOp                |
| tfl.tanh                      | TFL::TanhOp                   |
| tfl.mirror_pad               | TFL::MirrorPadOp              |
| tfl.transpose                 | TFL::TransposeOp              |
| tfl.mul                       | TFL::MulOp                    |
| tfl.transpose_conv           | TFL::TransposeConvOp          |
| tfl.neg                       | TFL::NegOp                    |
| tfl.unpack                    | TFL::UnpackOp                 |
| tfl.pack                      | TFL::PackOp                   |
| tfl.pad                       | TFL::PadOp                    |
| tfl.padv2                     | TFL::PadV2Op                  |
| tfl.pow                       | TFL::PowOp                    |
| tfl.prelu                     | TFL::PReluOp                  |

As a note:  
**TFL Operation**: This is the name of the operation as it appears in TensorFlow Lite models. It’s what you’ll see in model files or when inspecting the graph structure.  
**TFL Op Class**: This is the internal class name used in the TensorFlow Lite codebase (specifically in MLIR). It defines how the operation is implemented and processed during model conversion or optimization. Think of it as the backend implementation of the operation.

> **Limitation:** **tfl.concatenation (TFL::ConcatenationOp)** only supports up to 4 dimensional inputs.



## ONNX front-end operator support

| ONNX Operators||  |
|------------|------------|------------|
| Add        | ArgMax     | AveragePool |
| BatchNormalization | Cast | Clip |
| Concat     | Constant   | Conv |
| ConvTranspose | Cos | CumSum |
| DepthToSpace | Div | Equal |
| Erf        | Exp        | Expand |
| Flatten    | Gather     | Gemm |
| GlobalAveragePool | HardSigmoid | HardSwish |
| InstanceNormalization | LayerNormalization | LeakyRelu |
| Log        | LRN        | MatMul |
| Max        | MaxPool    | Mul |
| Neg        | Not        | Pad |
| Pow        | PRelu      | RandomNormalLike |
| ReduceL2   | ReduceMax  | ReduceMean |
| ReduceSum  | Relu       | Reshape |
| Resize     | ScatterND  | Shape |
| Sigmoid    | Sin        | Slice |
| Softmax    | SpaceToDepth | Split |
| Sqrt       | Squeeze    | Sub |
| Sum        | Tanh       | TopK |
| Transpose  | Unsqueeze  | Upsample |
| Where      |            |         |


## Executorch/Pytorch front-end operator support 

| Executorch Operators         | | |
|------------------------------|------------------------------|------------------------------|
| aten::addmm.out              | aten::eq.Tensor_out          | aten::sigmoid.out            |
| aten::add.out                | aten::expand_copy.out        | aten::sin.out                |
| aten::alias_copy.out         | aten::full_like.out          | aten::slice_copy.Tensor_out  |
| aten::any.out                | aten::gelu.out               | aten::_softmax.out           |
| aten::arange.start_out       | aten::hardtanh.out           | aten::split_with_sizes_copy.out |
| aten::as_strided_copy.out    | aten::index.Tensor_out       | aten::squeeze_copy.dims_out  |
| aten::avg_pool2d.out         | aten::logical_not.out        | aten::sub.out                |
| aten::bmm.out                | aten::max_pool2d_with_indices.out | aten::_to_copy.out           |
| aten::cat.out                | aten::mean.out               | aten::unsqueeze_copy.out     |
| aten::clamp.out              | aten::mm.out                 | aten::upsample_bilinear2d.vec_out |
| aten::clone.out              | aten::mul.out                | aten::upsample_nearest2d.vec_out |
| aten::constant_pad_nd.out    | aten::mul.Scalar_out         | aten::view_copy.out          |
| aten::convolution.out        | aten::_native_batch_norm_legit_no_training.out | aten::where.self_out         |
| aten::cos.out                | aten::native_layer_norm.out  | dim_order_ops::_to_dim_order_copy.out |
| aten::div.out                | aten::permute_copy.out       | executorch_prim::et_view.default |
| aten::eq.Scalar_out          | aten::relu.out               |                              |


## C99 Code-gen operator support 

The operator support on the embedded devices are provided in the table below. The codegen relies on microcontroller technologies that relies heavily on tensorflow lite and tensorflow lite kernels as a reference.  
MERA compiler import operators from other frameworks such as ONNX and Executorch and will eventually lower the operators into the below TFlite dialect. 

> **Note :** ONNX and PyTorch Frontends are currently only meant to be used with Quantizer flow. 

| TFLite Operators             |             |        |
|------------------------------|------------------------------|------------------------------|
| TFLiteAbs                    | TFLiteMirrorPad              | TFLiteResizeNearest          |
| TFLiteBatchToSpaceNd         | TFLiteMul                    | TFLiteSigmoid                |
| TFLiteConcatenate            | TFLiteNeg                    | TFLiteSlice                  |
| TFLiteDequantize             | TFLitePack                   | TFLiteSoftmax                |
| TFLiteExp                    | TFLitePad                    | TFLiteSpaceToBatchNd         |
| TFLiteFullyConnected         | TFLitePadV2                  | TFLiteSquaredDifference      |
| TFLiteFullyConnectedBias     | TFLitePRelu                  | TFLiteStridedSlice           |
| TFLiteHardSwish              | TFLiteQAdd                   | TFLiteSub                    |
| TFLiteLeakyReLU              | TFLiteQConv2d                | TFLiteSum                    |
| TFLiteLog                    | TFLiteQuantize               | TFLiteTanh                   |
| TFLiteLogSoftmax             | TFLiteReduceMax              | TFLiteTranspose              |
| TFLiteMaxPool                | TFLiteRelu                   | TFLiteTransposeConv2d        |
| TFLiteMean                   | TFLiteRelu6                  |                              |
| TFLiteMinimum                | TFLiteResizeBilinear         |                              |
