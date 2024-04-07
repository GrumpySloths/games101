#include <eigen3/Eigen/Eigen>
#include<iostream>
#include<vector>
using namespace std;
using namespace Eigen;

int main(void){
    cout << "hello world" << endl;
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Transform<float,3,Affine> t(AngleAxisf(0.25*M_PI,Vector3f(0.0f,0.0f,1.0f)));
    model =model* t.matrix();
    cout << model << endl;
    cout << tan(45.0 / 180 * M_PI) << endl;
    cout << "vector3f测试" << endl;
    Vector3f v1(0.5, 0.3, 0.2);
    cout << v1.z() << "   "<<abs(1.5)<<endl;
    vector<int> v2;
    v2.resize(3);
    v2[2] = 10;
    cout << v2[2] << endl;
    int a[] = {1, 3, 5}, *b = a;
    cout << b[2] << endl;
    return 0;
}