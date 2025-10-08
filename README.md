# joystick-control
linux版的遥控器控制代码

函数外面实例化
// 显式实例化常用类型，避免链接问题
template class MathVector<int>;
template class MathVector<float>;
template class MathVector<double>;

函数里面实例化
// 实例化两个int类型向量 
MathVector<int> vec1(std::vector<int>{1, 2, 3});
MathVector<int> vec2(std::vector<int>{4, 5, 6});
