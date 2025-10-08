//
// Created by fangjunjie on 25-8-26.
//
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  - /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//           佛祖保佑       永不宕机     永无BUG
//
#ifndef JOYSTICK_CONTROL_LIBRARY_H
#define JOYSTICK_CONTROL_LIBRARY_H
#include <string>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <vector>
#include <iomanip>


namespace joystickLib {
template <typename T>
class controller {
public:        // 定义轴的枚举映射（对应通道号）
    enum class Axis {
        LEFT_X = 0,     // 左摇杆X轴
        LEFT_Y = 1,     // 左摇杆Y轴
        RIGHT_X = 2,    // 右摇杆X轴
        RIGHT_Y = 3,    // 右摇杆Y轴
        DPAD_X = 4,     // 方向键X轴
        DPAD_Y = 5,     // 方向键Y轴
        L2 = 6,         // L2扳机键
        R2 = 7          // R2扳机键
    };

    // 定义按钮的枚举映射（对应通道号）
    enum class Button {
        A = 0,          // A键
        B = 1,          // B键
        X = 2,          // X键
        Y = 3,          // Y键
        L1 = 4,         // L1肩键
        R1 = 5,         // R1肩键
        SELECT = 6,     // 选择键
        START = 7,      // 开始键
        L3 = 8,         // 左摇杆按键
        R3 = 9          // 右摇杆按键
    };

    controller(const char* device);//初始化
    bool update(void);//更新数据
    int getAxisValue(Axis axis);// 获取轴值
    int getButtonState(Button button);// 获取按钮状态
private:
    const char* device_;
    int js_fd_;
    char name_[128];  // 固定大小的字符数组
    uint8_t num_axes_;
    uint8_t num_buttons_;
    struct js_event js_event_;

    std::vector<int> axis_;
    std::vector<int> button_;

};


}


#endif //JOYSTICK_CONTROL_LIBRARY_H