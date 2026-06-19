/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : camera_utils.c
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#include "hal_data.h"
#include "camera_utils.h"
#include "common_util.h"

#include "camera_layer.h"

#include "time_counter.h"

#define ROTATE_16BIT_IMAGE_DIRECTION  (1) // 0: Clock wise, 1: Counter clock wise

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/

/*********************************************************************************************************************
 *  Crop square, downsample and convert RGB565 to 8bpp grayscale (integer).
 *  @param[IN]   const void * inbuf: input 320x240 RGB565 image buffer
 *  @param[IN]   void * outbuf: output 192x192 int8 image buffer
 *  @param[IN]   uint16_t width: width of the input buffer
 *  @param[IN]   uint16_t height: height of the input buffer
 *  @param[IN]   uint16_t width: width of the output buffer
 *  @param[IN]   uint16_t height: height of the output buffer
***********************************************************************************************************************/

vision_ai_app_err_t image_rgb565_to_int8 (const void * p_input_image_buff, void * p_output_image_buff, uint16_t in_width, uint16_t in_height, uint16_t out_width, uint16_t out_height)
{

    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    if ((NULL == p_input_image_buff) || (NULL == p_output_image_buff))
    {
        vision_ai_status = VISION_AI_APP_ERR_NULL_POINTER;
        return vision_ai_status;
    }

    if(in_width < in_height)
    {
        vision_ai_status = VISION_AI_APP_ERR_IMG_PROCESS;
        return vision_ai_status;
    }

    register uint16_t * p_input  = (uint16_t *) p_input_image_buff;
    register int8_t   * p_output = (int8_t *) p_output_image_buff;

    /* Pixels to skip at the start of each line to crop to the center square */
    const uint32_t crop_offset = (in_width - in_height) / 2;

    for (uint32_t y = 0; y < out_height; y++)
    {
        for (uint32_t x = 0; x < out_width; x++)
        {
            /* Number of pixels in the Y-offset */
            uint32_t y_offset = in_width * ((in_height * y) / out_height);

            /* Pointer to the pixel at the start of the target cropped line */
            uint16_t * p_input_base = p_input + crop_offset + y_offset;

            /* Add X-offset for input pixels in cropped image. */
            uint16_t input = *(p_input_base + ((in_height * x) / out_width) );

            /* Approximate RGB to grayscale weighting of 0.25/0.50/0.125 */
            uint8_t weighted_sum = (uint8_t) (((input >> 11) << 1) + ((input >> 4) & 0x7E) + (input & 0x1F));

            /* Convert to integer range */
            *p_output++ = (int8_t) (weighted_sum - 0x80);
        }
    }

    return vision_ai_status;
}

/*********************************************************************************************************************
 *  Rotate an input image of 16 bit per pixel clockwise for 90 degree.
 *  @param[IN]   uint8_t* input_image: input image buffer rgb565
 *  @param[IN]   uint8_t* output_image: output image buffer rgb565
 *  @param[IN]   int input_width: width of the input buffer in pixel
 *  @param[IN]   int input_height: height of the input buffer in pixel
 *  @retval      None
***********************************************************************************************************************/
vision_ai_app_err_t rotate_16bit_image_90_degrees(uint8_t * p_input_image_buff, uint8_t * p_output_image_buff, int input_width, int input_height)
{
    vision_ai_app_err_t vision_ai_status = VISION_AI_APP_SUCCESS;

    if ((NULL == p_input_image_buff) || (NULL == p_output_image_buff))
    {
        vision_ai_status = VISION_AI_APP_ERR_NULL_POINTER;
       return vision_ai_status;
    }

    uint16_t * p_input  = (uint16_t *) p_input_image_buff;
    uint16_t * p_output = (uint16_t *) p_output_image_buff;

#if (ROTATE_16BIT_IMAGE_DIRECTION == 0)
    for(int32_t y = 0; y < input_height; y++)
    {
        for(int32_t x = 0; x < input_width; x ++)
        {
            *(p_output + ((x * input_height) + (input_height - y - 1))) = *p_input++;
        }
    }
#else
    for(int32_t input_y = 0; input_y < input_height; input_y++)
    {
        for(int32_t input_x = 0; input_x < input_width; input_x++)
        {
            *(p_output + (((input_width - input_x - 1) * input_height) + input_y)) = *p_input++;
        }
    }
#endif

    return vision_ai_status;
}
