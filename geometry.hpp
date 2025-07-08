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
    vector<Matrix4f> relative_matrices;
    vector<Matrix4f> translation_matrices;
    vector<Matrix4f> cg = constant_geometry();
    Matrix4f final_matrix;
    for(size_t i = 0; i < links.size(); i++ ) {
        Matrix4f T;
        T << 
        cos(links[i].type * links[i].angle), -sin(links[i].type * links[i].angle), 0, 0,
        sin(links[i].type * links[i].angle), cos(links[i].type * links[i].angle), 0, 0,
        0,0,(1-links[i].type)*links[i].angle,0,
        0,0,0,1;

        relative_matrices.push_back(T);
    }

    for(size_t i = 0; i < cg.size()-1; i++) {
        translation_matrices.push_back(cg[i] * relative_matrices[i]);
    }


    final_matrix = translation_matrices[0];
    for(size_t i =  1; i < translation_matrices.size(); i++) {
        final_matrix*=translation_matrices[i];
    }

     return final_matrix;
}




    manipulator(vector<link>links,vector<Matrix3f> initial_position ) : links(links), initial_position(initial_position) {

    }

};

 

