#include <iostream>

#include "Vector.hpp"
using namespace std;
void test() {
    static int num = 0;
    cout << "num:" << num++ << endl;
}
int main() {
    Vector3f v1(1, 3, 5);
    Vector3f v2 = v1;
    v1.x = 20;
    cout << v2 << endl;
    for (int i = 0; i < 10; i++) {
        test();
    }
    cout << fmax(21., 32.) << endl;
    cout << fabs(-5.) << endl;
}