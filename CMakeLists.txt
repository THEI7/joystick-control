cmake_minimum_required(VERSION 3.22)
project(joystick_control)

set(CMAKE_CXX_STANDARD 20)

add_library(joystick_control SHARED src/joystickControl.cpp)

target_include_directories(joystick_control
        PUBLIC
            include
)

add_executable(joystick_test
        main.cpp
)

target_link_libraries(joystick_test
        PRIVATE
            joystick_control
)

