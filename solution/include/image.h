#include <stdint.h>

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image create_image(uint64_t width, uint64_t height);

void delete_image(struct image* image);


