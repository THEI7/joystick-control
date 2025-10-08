#include <iostream>
#include <joystickControl.h>

int main(int argc, char* argv[]) {
    // 初始化手柄（默认设备路径）
    joystickLib::controller<int> lang8("/dev/input/js0");

    // 主循环：持续更新并读取状态
    while (true) {
        lang8.update();  // 更新手柄状态

        // 正确获取A键状态（使用Button枚举值作为参数）
        uint8_t buttonA = lang8.getButtonState(joystickLib::controller<int>::Button::A);

        // 示例：打印A键状态（按下时输出提示）
        if (buttonA == 1) {
            std::cout << "\033[32m[info]:\033[0m A键被按下"  << std::endl;
        }

        // 正确获取A键状态（使用Button枚举值作为参数）
        uint8_t buttonB = lang8.getButtonState(joystickLib::controller<int>::Button::B);

        // 示例：打印A键状态（按下时输出提示）
        if (buttonB == 1) {
            std::cout << "\033[32m[info]:\033[0m B键被按下"  << std::endl;
        }

        usleep(5000);  // 5ms延迟，降低CPU占用
    }

    return 0;
}