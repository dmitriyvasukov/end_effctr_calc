#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>
using namespace Eigen;
using namespace std;

float deg2rad(float degrees) {
    return degrees * EIGEN_PI / 180.0f;
}

enum offset_axis {X,Y,Z};

enum link_type {r = 1, p = 0};
class link {

    float  length;
    public:
    Vector3f offset_vector{0,0,0};
    float angle;
    float type;

    link(float length, offset_axis axis, float angle,link_type type ): length(length), angle(angle), type(type)
    {
        offset_vector[axis] = length;
    }
};



class manipulator {
vector<link>links;


vector<Matrix3f> initial_position;


public:
vector<Matrix4f> constant_geometry() {
    vector<Matrix4f> constant_geometry;
    constant_geometry.push_back(Matrix4f::Identity()); 

    for (size_t i = 1; i < initial_position.size(); i++) {
        Matrix4f A = Matrix4f::Identity();
        A.block<3,3>(0,0) = initial_position[i];
        A.block<3,1>(0,3) = links[i - 1].offset_vector; 
        constant_geometry.push_back(A);
    }

    return constant_geometry;
}

Matrix4f translation_matrix() {
    Matrix4f T = Matrix4f::Identity();

    vector<Matrix4f> cg = constant_geometry();

    for (size_t i = 0; i < links.size(); ++i) {
        Matrix4f G = Matrix4f::Identity();

        if (links[i].type == r) {
            // Вращение вокруг Z — в локальной СК
            G.block<3,3>(0,0) = AngleAxisf(links[i].angle, Vector3f::UnitZ()).toRotationMatrix();
        } else {
            // Поступательное — сдвиг вдоль Z
            G(2,3) = links[i].angle;
        }

        // Множим: T = T * M[i] * G
        T = T * cg[i] * G;
    }

    // Не забываем про финальное смещение (последнее звено)
    T = T * cg.back();

    return T;
}



    manipulator(vector<link>links,vector<Matrix3f> initial_position ) : links(links), initial_position(initial_position) {

    }

};

 

