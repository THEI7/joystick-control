# 🎮 Joystick Control

<div align="center">

**Linux 版遥控器控制库**

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

</div>

## 简介

这是一个用于Linux系统的游戏手柄/遥控器控制库，提供了简单易用的API来读取和处理手柄输入。

## 快速开始

### 编译项目

```bash
mkdir build && cd build
cmake ..
make
```

### 使用示例

#### 基本使用

```cpp
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

        // 正确获取B键状态（使用Button枚举值作为参数）
        uint8_t buttonB = lang8.getButtonState(joystickLib::controller<int>::Button::B);

        // 示例：打印B键状态（按下时输出提示）
        if (buttonB == 1) {
            std::cout << "\033[32m[info]:\033[0m B键被按下"  << std::endl;
        }

        usleep(5000);  // 5ms延迟，降低CPU占用
    }

    return 0;
}
```

#### API 说明

- **初始化手柄**: `joystickLib::controller<T>(device_path)`
  - `device_path`: 手柄设备路径，通常为 `/dev/input/js0`
  
- **更新状态**: `update()`
  - 读取最新的手柄输入状态
  
- **获取按键状态**: `getButtonState(Button button)`
  - 返回值: `1` 表示按下，`0` 表示未按下
  - 按钮枚举: `Button::A`, `Button::B`, `Button::X`, `Button::Y` 等

## 技术说明

### 模板实例化

**函数外面实例化（显式实例化）**
```cpp
// 显式实例化常用类型，避免链接问题
template class MathVector<int>;
template class MathVector<float>;
template class MathVector<double>;
```

**函数里面实例化**
```cpp
// 实例化两个int类型向量 
MathVector<int> vec1(std::vector<int>{1, 2, 3});
MathVector<int> vec2(std::vector<int>{4, 5, 6});
```

## 📄 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件
