#include <iostream>

class MyClass {
public:
    MyClass() { std::cout << "Constructor called!" << std::endl; }

    ~MyClass() { std::cout << "Destructor called!" << std::endl; }
};

MyClass createObject() {
    MyClass obj;
    return obj;
}

int main() {
    MyClass newObj = createObject();
    // 在这里，newObj是一个无效的对象，因为它引用了已经被销毁的栈上对象

    return 0;
}
