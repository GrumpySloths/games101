#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>
#include<eigen3/Eigen/Geometry>
// #include<math.h>
int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i(1,1) << std::endl;
    std::cout << j << std::endl;
    // matrix add i + j
    // matrix scalar multiply i * 2.0
    // matrix multiply i * j
    // matrix multiply vector i * v
    Eigen::Transform<float, 2, Eigen::Isometry> t = Eigen::Translation2f(1, 2) * Eigen::Rotation2Df(M_PI*0.25);
    Eigen::Vector2f p(2.0f, 1.0f);
    Eigen::Vector2f p1 = t * p;
    std::cout << "transformation matrix" << std::endl;
    std::cout << t.matrix() << std::endl;
    std::cout << "p coordinate after transformation:" << std::endl;
    std::cout << p1 << std::endl;
    // 四元数测试
    std::cout << "四元数测试__________" << std::endl;
    Eigen::AngleAxisf ax(0.25 * M_PI, Eigen::Vector3f::UnitX());
    Eigen::AngleAxisf ax2(0.5 * M_PI, Eigen::Vector3f::UnitX());
    Eigen::Quaternionf q2(ax2);
    Eigen::Quaternionf q1(ax);
    std::cout << q1.coeffs().transpose() << std::endl;
    std::cout << q2.coeffs().transpose() << std::endl;
    
    return 0;
}