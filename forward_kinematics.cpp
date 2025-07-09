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

    link link1(7, Z, deg2rad(30.0), r);
    link link2(4, X, deg2rad(10.0), r);
    link link3(4, Z, 6.0, p);

    vector<link>links{link1,link2,link3};

    manipulator robot(links, config);

    vector<Matrix4f> cg = robot.constant_geometry();




    Matrix4f tm = robot.translation_matrix();

Vector4f p_tool_local(1, 1, 1, 1); 
Vector4f p_tool_global = tm * p_tool_local;

Vector3f target_point = p_tool_global.head<3>();

// Вектор от последнего звена к этой точке
Vector3f from_last_link = target_point - tm.block<3,1>(0,3);

cout << "GV: " << target_point.transpose() << endl;
cout << "FLJ: " << from_last_link.transpose() << endl;

}
