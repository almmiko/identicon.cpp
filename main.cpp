#include "include/Identicon.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: expects 'username'\n");
        exit(EXIT_FAILURE);
    }

    Identicon::Identicon::create_image(argv[1]);

    return 0;
}
