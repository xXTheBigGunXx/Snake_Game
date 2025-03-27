#include "TaskUtils.h"

namespace win {
    #include <windows.h>
}
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

const char* TaskUtils::_clouds_path = "Textures\\clouds.jpg";
const char* TaskUtils::_bc_path = "Textures\\background.jpg";

int TaskUtils::RandomInt(size_t range) {
    if (range == 0) {
        return 0;
    }

    int num;
    if (win::BCryptGenRandom(NULL, (win::PUCHAR)&num, sizeof(num), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        return 0;
    }
    return static_cast<int>(num % range);
}

char TaskUtils::KeyPressed() {
    for (size_t i = 0; i < 256; i++) {
        if (win::GetAsyncKeyState(i) & 0x8000) {
            return static_cast<char>(i);
        }
    }
    return '!';
}
