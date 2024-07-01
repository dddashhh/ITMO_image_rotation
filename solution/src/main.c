#include "bmp.h"
#include "rotate.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "The number of arguments entered does not meet the requirements.");
        return -1;
    }


    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");

    int angle = atoi(argv[3]);

    if (angle % 90 != 0 || 270 < angle || angle < -270) {
        fprintf(stderr, "Incorrect angle format");
        return -1;
    }

    if (input == NULL) {
        fprintf(stderr, "There is no such source file");
        return -1;
    }

    if (output == NULL) {
        fprintf(stderr, "There is no such destination file");
        return -1;
    }

    if ((input != NULL) && (output != NULL)) {
        struct image img;

        if (from_bmp(input, &img) != READ_OK) {
            fprintf(stderr, "The source file cannot be read");
            delete_image(&img);
            return -1;
        }

        rotate(&img, angle);

        if (to_bmp(output, &img) != WRITE_OK) {
            fprintf(stderr, "The final file cannot be write");
            delete_image(&img);
            return -1;
        }

        if ((from_bmp(input, &img) == READ_OK) && (to_bmp(output, &img) == WRITE_OK)) {
            printf("Image rotate successfully");
            delete_image(&img);
            return 0;
        }
    delete_image(&img);
    }
}
