#include <inttypes.h>

struct image rotate_image_by_angle(struct image* image,int angle);

void rotate(struct image* image, int angle);

static inline void set_pixels(struct image image, struct pixel data) {
    image.data = &data;
}

