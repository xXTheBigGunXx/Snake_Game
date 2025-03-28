#include "TaskUtils.h"
#include <cmath>
#include <iostream>

namespace win {
    #include <windows.h>
}
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

const char* TaskUtils::_clouds_path = "Textures\\clouds.jpg";
const char* TaskUtils::_bc_path = "Textures\\background.jpg";
const char* TaskUtils::_apple_path = "Textures\\apple.png";
const char* TaskUtils::_snake_head_path = "Textures\\snakeshead.png";

int TaskUtils::RandomInt(int range) {
    int num;
    if (win::BCryptGenRandom(NULL, (win::PUCHAR)&num, sizeof(num), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        return -1;
    }
    int temp = static_cast<int>((num % range) / 60)  * 60;
    if (temp < 0)
        return -1;
    return temp;
}

char TaskUtils::KeyPressed() {
    for (size_t i = 0; i < 256; i++) {
        if (win::GetAsyncKeyState(i) & 0x8000) {
            return static_cast<char>(i);
        }
    }
    return '!';
}
