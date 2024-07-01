#include <bmp.h>
#include <stddef.h>
#include <stdint.h>



inline static uint8_t get_padding(uint64_t width) {
    return (4 - sizeof(struct pixel) * width % 4);
}

inline static size_t file_size(const struct image *image) {
    return (image->width * sizeof(struct pixel) + get_padding(image->width)) * image->height + 54;
}

inline static struct bmp_header create_header(const struct image *image) {
    struct bmp_header new_bmp_header = {
            .bfType = 0x4D42,
            .bfileSize = file_size(image),
            .biWidth = image->width,
            .biHeight = image->height,
            .biBitCount = 24
    };
    return new_bmp_header;
}

enum read_status from_bmp(FILE* input, struct image* image) {
    struct bmp_header new_bmp_header = {0};

    if (input == NULL || image == NULL) {
        return READ_ERROR;
    }

    if (fread(&new_bmp_header, sizeof(struct bmp_header), 1, input) != 1) {
        delete_image(image);
        return READ_ERROR;
    }

    if ((new_bmp_header.bfType != 0x4D42) || (new_bmp_header.biBitCount != 24)){
        delete_image(image);
        return READ_ERROR;
    }

    if ((new_bmp_header.biWidth < 0) || (new_bmp_header.biHeight < 0 )){
        delete_image(image);
        return READ_ERROR;
    }
        *image = create_image(new_bmp_header.biWidth, new_bmp_header.biHeight);
    
    if (fseek(input, (long) new_bmp_header.bOffBits, SEEK_SET)) {
        delete_image(image);
        return READ_ERROR;
    }

    uint8_t padding = get_padding(image->width);

    for (int i = 0; i < image->height; i++) {
        if (fread(image->data + i * image->width, sizeof(struct pixel), image->width, input) != image->width) {
            return READ_ERROR;
        }
        fseek(input, padding, SEEK_CUR);
    }
    return READ_OK;
}

enum write_status to_bmp(FILE* output, const struct image* image) {
    struct bmp_header new_bmp_header = create_header(image);

    if (output == NULL || image == NULL) {
        return WRITE_ERROR;
    }

    if (fwrite(&new_bmp_header, sizeof(struct bmp_header), 1, output) < 1) {
        return WRITE_ERROR;
    }

    uint32_t padding_byte = 0;
    uint64_t you_was_problem = get_padding(image->width);
    
    for (uint32_t i = 0; i < image->height; i++) {
        if (fwrite(image->data + i * image->width, sizeof(struct pixel), image->width, output) != image->width) {
            return WRITE_ERROR;
        }
        if (fwrite(&padding_byte, sizeof(uint8_t), you_was_problem, output) != you_was_problem) {
            return WRITE_ERROR;
        }
    }

    if (fwrite(&new_bmp_header, sizeof(struct bmp_header), 1, output) == 1) {
        return WRITE_OK;
    }
    return WRITE_ERROR;
}
