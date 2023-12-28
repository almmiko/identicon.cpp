#ifndef IDENTICON_CPP_IMAGE_H
#define IDENTICON_CPP_IMAGE_H

namespace Identicon {

class Image {
public:
    static void write(const char *file_name, int* rgb, int length, int width);
};

}

#endif //IDENTICON_CPP_IMAGE_H
