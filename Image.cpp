#include "include/Image.h"

#include <stdio.h>
#include <filesystem>

namespace Identicon {
    // Function to round an int to a multiple of 4
    int round4(int x) {
        return x % 4 == 0 ? x : x - x % 4 + 4;
    }

    void Image::write(const char *file_name, int* rgb, int length, int width) {
        int height = (length / 3) / width;

        // Pad the width of the destination to a multiple of 4
        int padded_width = round4(width * 3);

        int bitmap_size = height * padded_width * 3;

        char bitmap[bitmap_size * sizeof(char)];

        for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

        // For each pixel in the RGB image...
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {

                // For R, G, and B...
                for (int color = 0; color < 3; color++) {

                    // Get the index of the destination image
                    int index = row * padded_width + col * 3 + color;

                    // Set the destination to the value of the src at row, col.
                    bitmap[index] = rgb[3*(row * width + col) + (2 - color)];
                }
            }
        }

        char tag[] = { 'B', 'M' };
        int header[] = {
                0, 0, 0x36, 0x28, width, height, 0x180001,
                0, 0, 0x002e23, 0x002e23, 0, 0
        };
        header[0] = sizeof(tag) + sizeof(header) + bitmap_size;

        auto path = std::filesystem::current_path() / file_name;

        FILE *fp = fopen(path.c_str(), "w+");

        fwrite(&tag, sizeof(tag), 1, fp);
        fwrite(&header, sizeof(header), 1, fp);
        fwrite(bitmap, bitmap_size * sizeof(char), 1, fp);

        fclose(fp);
    }
}
