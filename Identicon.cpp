#include "Identicon.h"
#include "Image.h"

namespace Identicon {
    void Identicon::hash_input() {
        std::size_t hash = std::hash<std::string>{}(this->input);

        std::vector<uint8_t> _hex(sizeof(hash));
        std::memcpy(_hex.data(), &hash, sizeof(hash));

        // sizeof(hash) => 8, we need to make it longer for the grid
        _hex.insert(_hex.end(), _hex.begin(), _hex.end());

        this->hex = _hex;
    }

    void Identicon::create_image(int w, int h, std::string input) {
        Identicon* identicon = new Identicon(w, h, input);

        identicon->hash_input();
        identicon->pick_color();
        identicon->build_grid();
        identicon->generate_image();

        printf("point");
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
        int fr[] = {
                0, 85, 164,    // Bleu
                255, 255, 255, // Blanc
                239, 65, 53,   // Rouge
                0, 85, 164,
                255, 255, 255,
                239, 65, 53,
        };
        Image::write("french_flag.bmp", reinterpret_cast<int *>(&fr), sizeof(fr) / sizeof(char), 3);
    }
}