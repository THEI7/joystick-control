#include "../include/joystickControl.h"

#include <iostream>


namespace joystickLib {

    template <typename T>
    controller<T>::controller(const char* device) {
        device_ = device;
        js_fd_ = open(device_, O_RDONLY | O_NONBLOCK);
        if (js_fd_ < 0) {
            perror("[error]无法打开手柄设备");
        }
        ioctl(js_fd_, JSIOCGNAME(sizeof(name_)), name_);
        ioctl(js_fd_, JSIOCGAXES, &num_axes_);
        ioctl(js_fd_, JSIOCGBUTTONS, &num_buttons_);
        fcntl(js_fd_, F_SETFL, O_NONBLOCK); // 设置非阻塞模式

        axis_.resize(num_axes_, 0);      // 调整大小为num_axes_，初始值0
        button_.resize(num_buttons_, 0); // 调整大小为num_buttons_，初始值0

        std::cout << "\033[35m[手柄名称]\033[0m: " << name_ << std::endl;
        std::cout << "\033[35m[轴数量]\033[0m: " << (int)num_axes_ << std::endl;
        std::cout << "\033[35m[按钮数量]\033[0m: " << (int)num_buttons_ << std::endl;
    }

    template <typename T>
    bool controller<T>::update(void) {

        struct js_event event;

        ssize_t bytes = read(js_fd_, &event, sizeof(event));

        if (bytes == sizeof(event)) {
            //获取值
            js_event_ = event;

            // 更新当前事件对应的通道值
            switch (js_event_.type & ~JS_EVENT_INIT) {
                case JS_EVENT_AXIS:
                        if (js_event_.number < axis_.size())
                        axis_[js_event_.number] = js_event_.value;
                    break;
                case JS_EVENT_BUTTON:
                    if (event.number < button_.size())
                        button_[js_event_.number] = js_event_.value;
                    break;
                default:
                    break;
            }
        }
        else {
            return false;
        }

        return true;
    }

    template <typename T>
    int controller<T>::getAxisValue(Axis axis) {
        // 将枚举转换为索引并返回对应值
        int index = static_cast<int>(axis);
        if (index >= 0 && index < axis_.size()) {
            return axis_[index];
        }
        return 0;  // 索引无效时返回0
    }

    template <typename T>
    int controller<T>::getButtonState(Button button) {
        // 将枚举转换为索引并返回对应状态（0=释放，1=按下）
        int index = static_cast<int>(button);
        if (index >= 0 && index < button_.size()) {
            return button_[index];
        }
        return 0;  // 索引无效时返回0
    }

    // 显式模板实例化
    template class controller<int>;

}