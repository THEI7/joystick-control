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

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <vector>
#include <iomanip>

int main() {
    const char* device = "/dev/input/js0";
    int js_fd = open(device, O_RDONLY);
    if (js_fd < 0) {
        perror("无法打开手柄设备");
        return 1;
    }

    // 获取手柄信息
    char name[128] = "Unknown";
    ioctl(js_fd, JSIOCGNAME(sizeof(name)), name);
    __u8 num_axes = 0, num_buttons = 0;
    ioctl(js_fd, JSIOCGAXES, &num_axes);
    ioctl(js_fd, JSIOCGBUTTONS, &num_buttons);

    std::cout << "[手柄名称]: " << name << std::endl;
    std::cout << "[轴数量]: " << (int)num_axes << std::endl;
    std::cout << "[按钮数量]: " << (int)num_buttons << std::endl;

    struct js_event event;
    fcntl(js_fd, F_SETFL, O_NONBLOCK); // 设置非阻塞模式
    std::vector<int> axis(num_axes, 0);
    std::vector<int> button(num_buttons, 0);
    std::cout << "[info]开始读取事件.................." << std::endl;

    while (true) {

        //读取数据
        ssize_t bytes = read(js_fd, &event, sizeof(event));

        //检查数据是否合规
        if (bytes == sizeof(event)) {
            // 更新当前事件对应的通道值
            switch (event.type & ~JS_EVENT_INIT) {
                case JS_EVENT_AXIS:
                    if (event.number < axis.size())
                        axis[event.number] = event.value;
                    break;
                case JS_EVENT_BUTTON:
                    if (event.number < button.size())
                        button[event.number] = event.value;
                    break;
            }
        }

        // 清屏 + 光标归位
        system("clear");  // 稳定清屏

        // 打印手柄总览
        std::cout << "================= 手柄信息 =================\n";
        std::cout << "[手柄名称]: " << name << "\n";
        std::cout << "[轴数量]: " << (int)num_axes << "\n";
        std::cout << "[按钮数量]: " << (int)num_buttons << "\n";
        std::cout << "时间戳 (最后事件): " << event.time << " ms\n";
        std::cout << "--------------------------------------------\n";

        std::cout << "================= 手柄状态 =================\n";
        std::cout << "[轴状态]\n";
        for (size_t i = 0; i < axis.size(); ++i) {
            std::cout << "  轴 " << std::setw(2) << i << " : "
                      << std::setw(6) << axis[i] << "\n";
        }
        std::cout << "\n[按钮状态]\n";
        for (size_t i = 0; i < button.size(); ++i) {
            std::cout << "  按钮 " << std::setw(2) << i << " : "
                      << (button[i] ? "按下" : "松开") << "\n";
        }
        std::cout << "============================================\n";
        std::cout.flush();

        usleep(5000);
    }

    close(js_fd);
    return 0;
}