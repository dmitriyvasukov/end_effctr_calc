#include "geometry.hpp"

int main() {

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

    link link1(0.8, Z, deg2rad(30.0), r);
    link link2(0.6, X, deg2rad(20.0), r);
    link link3(0.5, X, deg2rad(10.0), r);

    vector<link>links{link1,link2,link3};

    manipulator robot(links, config);

    Matrix4f tm = robot.translation_matrix();

    

    cout  << tm;
}