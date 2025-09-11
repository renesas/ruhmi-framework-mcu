#include <stdint.h>

/*
 kBufferSize_sub_0001 is a compile-time constant to be used by the user of compute_sub_0001 function
 to allocate a buffer with at least the specified size.

 Example of how to call the compute function:

   // it is possible to use either heap, stack or a custom data section to allocate this buffer
   uint8_t my_buffer[kBufferSize_sub_0001];

   int main() {
     ...
     compute_sub_0001(my_buffer, input, output);
   }
*/
enum BufferSize_sub_0001 {
  kBufferSize_sub_0001 = 1
};

void compute_sub_0001(
  // buffer for intermediate results
  uint8_t* main_storage, // should provide at least 1 bytes of storage

  // inputs
  
  const int8_t mobilenet_0_25_224_conv_pw_13_relu_Relu6_mobilenet_0_25_224_conv_pw_13_bn_FusedBatchNormV3_mobilenet_0_25_224_conv_pw_13_Conv2D_70091[12544], // 1,7,7,256
  

  // outputs
  
  int8_t mobilenet_0_25_224_global_average_pooling2d_Mean_70092[256]  // 1,1,1,256
  
);
