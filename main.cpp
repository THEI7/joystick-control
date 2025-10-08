#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>

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


    // 设置非阻塞模式
    fcntl(js_fd, F_SETFL, O_NONBLOCK);

    struct js_event event;
    std::cout << "[info]开始读取事件.................." << std::endl;

    while (true) {
        ssize_t bytes = read(js_fd, &event, sizeof(event));
        if (bytes == sizeof(event)) {
            // 使用 ANSI 序列清屏 + 光标归位（带 flush）
            std::cout << "\033[H\033[J"; // 另一种兼容写法
            std::cout.flush();

            std::cout << "================= 手柄信息 =================\n";
            std::cout << "[手柄名称]: " << name << std::endl;
            std::cout << "[轴数量]: " << (int)num_axes << std::endl;
            std::cout << "[按钮数量]: " << (int)num_buttons << std::endl;

            std::cout << "================= 手柄状态 =================\n";
            std::cout << "手柄名称: " << name << "\n";
            std::cout << "时间戳 (最后事件): " << event.time << " ms\n";
            std::cout << "--------------------------------------------\n";

            std::cout << "============================================\n";

            usleep(5000);
        }

        usleep(10000);
    }

    close(js_fd);
    return 0;
}