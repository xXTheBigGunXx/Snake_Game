#include "TaskUtils.h"
#include <cmath>

namespace win {
    #include <windows.h>
}
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

const char* TaskUtils::_clouds_path = "Textures\\clouds.jpg";
const char* TaskUtils::_bc_path = "Textures\\background.jpg";
const char* TaskUtils::_apple_path = "Textures\\apple.jpg";

int TaskUtils::RandomInt(size_t range) {
    int num;
    if (win::BCryptGenRandom(NULL, (win::PUCHAR)&num, sizeof(num), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        return 0;
    }
    return std::round(static_cast<int>(num % range) / 60)  * 60;
}

char TaskUtils::KeyPressed() {
    for (size_t i = 0; i < 256; i++) {
        if (win::GetAsyncKeyState(i) & 0x8000) {
            return static_cast<char>(i);
        }
    }
    return '!';
}
