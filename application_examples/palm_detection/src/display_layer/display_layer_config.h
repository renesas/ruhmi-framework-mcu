#ifndef DISPLAY_LAYER_CONFIG_H__
#define DISPLAY_LAYER_CONFIG_H__

#define DISPLAY_SCREEN_WIDTH              (1024)
#define DISPLAY_SCREEN_HEIGHT             (600)
#define DISPLAY_SCREEN_BYTES_PER_PIXEL    (2)
#define DISPLAY_SCREEN_BUFF_NUMBER        (2)

#define DISPLAY_SCREEN_BUFF_D2_COLOR_CODE (d2_mode_rgb565)

#define CAMERA_IMAGE_SCALING  (1.25f)
#define DISPLAY_FONT_SCALING  (1.25f)

/* Red, matching the two landmark projects.
 *
 * This was black, which is hard to pick out: black has only brightness to
 * separate it from the picture behind it, and a live camera frame is full of
 * brightness. Skin, walls and clothing are all low-saturation, so a strongly
 * saturated overlay stands out from them whatever happens to be in shot. */
#define AI_INFERENCE_RESULT_BOUNDING_BOX_COLOR  (0xFF0000) // 24-bit RGB color format


#endif /* DISPLAY_LAYER_CONFIG_H__ */
