#ifndef IDENTICON_CPP_IDENTICON_H
#define IDENTICON_CPP_IDENTICON_H

#include <vector>
#include <string>

namespace Identicon {

class Identicon {
private:
    int width;
    int height;
    std::vector<uint8_t> hex;
    std::string input;
    std::vector<std::vector<uint8_t>> grid;
    uint8_t color[3];

    void hash_input();
    void pick_color();
    void build_grid();
    void generate_image();

public:
     Identicon(int width, int height, std::string input) : width{width}, height{height}, input{input} {};
     ~Identicon() {};

    static void create_image(int w, int h, std::string input);
};

}

#endif //IDENTICON_CPP_IDENTICON_H
