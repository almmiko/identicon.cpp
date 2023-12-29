#include "include/Identicon.h"
#include "include/Image.h"

namespace Identicon {
    void Identicon::hash_input() {
        std::size_t hash = std::hash<std::string>{}(this->input);

        std::vector<uint8_t> _hex(sizeof(hash));
        std::memcpy(_hex.data(), &hash, sizeof(hash));

        // sizeof(hash) => 8, we need to make it longer for the grid
        _hex.insert(_hex.end(), _hex.begin(), _hex.end());

        this->hex = _hex;
    }

    void Identicon::create_image(std::string input) {
        Identicon* identicon = new Identicon(input);

        identicon->hash_input();
        identicon->pick_color();
        identicon->build_grid();
        identicon->generate_image();

        std::string input_with_ext = input + ".bmp";

        printf("Identicon was generated. File: %s\n", input_with_ext.c_str());
    }

    void Identicon::pick_color() {
        for (int i = 0; i < 3; i++) {
            this->color[i] = this->hex[i];
        }
    }

    void Identicon::build_grid() {
        for (int i = 0; i < this->hex.size(); i++) {
            if (i > 0 && i % 3 == 0) {
                std::vector<uint8_t> row;
                int chunk_size = 3;

                while (chunk_size--) {
                    row.push_back(this->hex[i - chunk_size]);
                }

                row.push_back(row[1]);
                row.push_back(row[0]);

                this->grid.push_back(row);
            }
        }
    }

    void Identicon::generate_image() {
       std::vector<int> rgb;

        for (int i = 0; i < this->grid.size(); i++) {
            int pixel_size_height = 50;

            while (pixel_size_height--) {
                for (int j = 0; j < this->grid[0].size(); j++) {
                    int pixel_size_width = 50;
                    if (this->grid[i][j] % 2 == 0) {
                        while (pixel_size_width--) {
                            rgb.push_back(255);
                            rgb.push_back(255);
                            rgb.push_back(255);
                        }
                    } else {
                        while (pixel_size_width--) {
                            rgb.push_back(this->color[0]);
                            rgb.push_back(this->color[1]);
                            rgb.push_back(this->color[2]);
                        }
                    }
                }

            }
        }

        std::string file_name = this->input.append(".bmp");

        Image::write(file_name, &rgb[0], 250, 250);
    }
}