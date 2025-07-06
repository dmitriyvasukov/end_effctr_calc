#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include  <vector>
using namespace Eigen;
using namespace std;

float deg2rad(float q) {
    return (q * EIGEN_PI) / 180.0f;
}

enum LinkType { ROTATING = 1, PROCESSING = 0 };
enum OffSetAxis { X, Y, Z};


class Link {
    public:
        float length;
        LinkType type;
        OffSetAxis axis;
        Vector3f form_offset_vector() {
            Vector3f offset_vector{0,0,0};
            offset_vector[axis] = length;
            return offset_vector;
        }
    Link(float length, LinkType type, OffSetAxis axis):
        length(length), type(type), axis(axis) {};


};
class Manipulator {

    vector<Link>links;
    vector<Matrix3f>init_configuration;

    vector<Matrix3f> const_geometry() {
        vector<Matrix4f>constant_geometry;
        if (init_configuration[0] == Matrix3f::Identity()) {
            constant_geometry[0] = Matrix4f::Identity();
        } 

        else {
            constant_geometry[0].block<3,3>(0,0) = init_configuration[0];
            constant_geometry[0].block<3,1>(0,4) = links[0].form_offset_vector();
        }
    }
};

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


    
    return 0;
}