#define GLM_ENABLE_EXPERIMENTAL

#include "Scene.h"

int main() {
    Scene gameScene("Game/master_file.lua", 1920, 1080);
    gameScene.update();
    return 0;
}