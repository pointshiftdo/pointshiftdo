#include <unistd.h>

#define FULLSENDX_IMPLEMENTATION
#include "fullsendx.h"

int main(int argc, char *argv[]) {
    fullsendx_trust_or_exit();

    if (argc == 0) {
        return 0;
    } else {
        return execv(argv[0], &argv[1]);
    }
}
