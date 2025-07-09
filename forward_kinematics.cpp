#include "geometry.hpp"

int main() {
setlocale(LC_ALL, "Russian");
    Matrix3f M0 = Matrix3f::Identity();

    Matrix3f M1;
    M1 << 0, 0, 1,
          1, 0, 0,
          0, 1, 0;
    
    Matrix3f M2;
    M2 << 0, 1, 0,
         -1, 0, 0,
          0, 0, 1;
    
    Matrix3f M3;
    M3 << 0, 0, 1,
          1, 0, 0,
          0, 1, 0;

    
    vector<Matrix3f>config{M0,M1,M2,M3};

    link link1(7, Z, deg2rad(-30.0), r);
    link link2(4, X, deg2rad(-10.0), r);
    link link3(4, X, deg2rad(-60.0), p);

    vector<link>links{link1,link2,link3};

    manipulator robot(links, config);

    vector<Matrix4f> cg = robot.constant_geometry();




    Matrix4f tm = robot.translation_matrix();

    cout << tm * Vector4f(0,0,0,1);

}
