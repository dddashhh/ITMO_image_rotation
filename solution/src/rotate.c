#include "image.h"
#include <math.h>
#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif
#include "rotate.h"
#include <stdio.h>


struct image rotate_image_by_angle(struct image* image, int angle) {
    struct image rotated_image = create_image(image->height, image->width);
    set_pixels(rotated_image, *image->data);
    if (angle != 0) {
        for (size_t y = 0; y < image->height; y++) {
            for (size_t x = 0; x < image->width; x++) {
                double new_x = (int) (cos(angle * M_PI / 180.0) * (double )x - sin(angle * M_PI / 180.0) * (double)y);
                double new_y = (int) (sin(angle * M_PI / 180.0) * (double)x + cos(angle * M_PI / 180.0) * (double)y);
                if (new_y <= 0 || new_x <=0) {
                    if (angle == 90) {
                        rotated_image.data[
                                (rotated_image.height - (int) sin(angle * M_PI / 180.0) * x - 1) * rotated_image.width +
                                (int) sin(angle * M_PI / 180.0) * y] = image->data[
                                (int) sin(angle * M_PI / 180.0) * y * image->width +
                                (int) sin(angle * M_PI / 180.0) * x];

                    } else if (angle == 180)
                        rotated_image.data[
                                (rotated_image.height - (int) cos((180 - angle) * M_PI / 180.0) * x - 1) * rotated_image.width +
                                (int) cos((180 - angle) * M_PI / 180.0) * y] = image->data[
                                (int) cos((180 - angle) * M_PI / 180.0) * y * image->width +
                                (int) cos((180 - angle) * M_PI / 180.0) * x];

                    else if (angle == 270) {
                        rotated_image.data[
                                (rotated_image.height - (int) sin((360 - angle) * M_PI / 180.0) * x - 1) * rotated_image.width +
                                (int) sin((360 - angle) * M_PI / 180.0) * y] = image->data[
                                (int) sin((360 - angle) * M_PI / 180.0) * y * image->width +
                                (int) sin((360 - angle) * M_PI / 180.0) * x];
                    }
                }
            }
        }
    }
    delete_image(image);
    *image = rotated_image;
    return *image;
}

void rotate(struct image* image, int angle) {
    if (angle < 0) {
        angle = 360 + angle;
    }
    if ((angle <= 270) && (angle >= -270) && (angle % 90 == 0)) {
        for (int64_t i = 0; i * 90 < angle; i++) {
            *image = rotate_image_by_angle(image,angle);
        }
    }
}

