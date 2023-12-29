#ifndef IDENTICON_CPP_IMAGE_H
#define IDENTICON_CPP_IMAGE_H

#include <string>

namespace Identicon {

class Image {
public:
    static void write(const std::string file_name, int* rgb, int width, int height);
};

}

#endif //IDENTICON_CPP_IMAGE_H
