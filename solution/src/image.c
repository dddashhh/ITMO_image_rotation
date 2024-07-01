#include <image.h>
#include <stdint.h>
#include <stdlib.h>


struct image create_image(uint64_t width, uint64_t height) {
    return (struct image){
            .height = height,
            .width = width,
            .data = malloc(sizeof(struct pixel) * width * height)};
}

void delete_image(struct image* image) {
    free(image->data);
    image->data = NULL;
}
