#include <array>
#include <algorithm>
#include <iostream>
using namespace std;
struct Vector4f
{
    float x, y, z, w;
};

int main() {
    std::array<Vector4f, 3> arr = {
        {{1.0f, 2.0f, 3.0f, 4.0f},
         {5.0f, 6.0f, 7.0f, 8.0f},
         {9.0f, 10.0f, 11.0f, 12.0f}}
    };

    auto x_minmax = std::minmax_element(arr.begin(), arr.end(),
        [](const Vector4f& a, const Vector4f& b) {
            return a.x < b.x;
        });

    auto y_minmax = std::minmax_element(arr.begin(), arr.end(),
        [](const Vector4f& a, const Vector4f& b) {
            return a.y < b.y;
        });

    std::cout << "x min: " << x_minmax.first->x << ", max: " << x_minmax.second->x << std::endl;
    std::cout << "y min: " << y_minmax.first->y << ", max: " << y_minmax.second->y << std::endl;
    cout << int(0.5) << endl;
    return 0;
}
