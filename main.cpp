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
            std::cout << "\r";
            std::cout << "\033[32m[info]:A键被按下\033[0m"  << std::flush; // 绿色
        }

        // 正确获取B键状态（使用Button枚举值作为参数）
        uint8_t buttonB = lang8.getButtonState(joystickLib::controller<int>::Button::B);

        // 示例：打印B键状态（按下时输出提示）
        if (buttonB == 1) {
            std::cout << "\r";
            std::cout << "\033[34m[info]:B键被按下\033[0m"  << std::flush; // 蓝色
        }

        // 正确获取Y键状态（使用Button枚举值作为参数）
        uint8_t buttonY = lang8.getButtonState(joystickLib::controller<int>::Button::Y);
        // 示例：打印Y键状态（按下时输出提示）
        if (buttonY == 1) {
            std::cout << "\r";
            std::cout << "\033[33m[info]:Y键被按下\033[0m"  << std::flush; // 黄色
        }

        // 正确获取X键状态（使用Button枚举值作为参数）
        uint8_t buttonX = lang8.getButtonState(joystickLib::controller<int>::Button::X);
        // 示例：打印X键状态（按下时输出提示）
        if (buttonX == 1) {
            std::cout << "\r";
            std::cout << "\033[35m[info]:X键被按下\033[0m"  << std::flush; // 紫色
        }

        usleep(5000);  // 5ms延迟，降低CPU占用
    }

    return 0;
}