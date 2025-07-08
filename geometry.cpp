#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>
using namespace Eigen;
using namespace std;



enum offset_axis {X,Y,Z};


class link {

    float  length;
    public:
    Vector3f offset_vector{0,0,0};

    link(float length, offset_axis axis): length(length)
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
    constant_geometry.push_back(Matrix4f::Identity()); // A00*

    for (size_t i = 1; i < initial_position.size(); i++) {
        Matrix4f A = Matrix4f::Identity();
        A.block<3,3>(0,0) = initial_position[i];
        A.block<3,1>(0,3) = links[i - 1].offset_vector; // Важно!
        constant_geometry.push_back(A);
    }

    return constant_geometry;
}




    manipulator(vector<link>links,vector<Matrix3f> initial_position ) : links(links), initial_position(initial_position) {

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

    
    vector<Matrix3f>config{M0,M1,M2,M3};

    link link1(0.8, Z);
    link link2(0.6, X);
    link link3(0.5, X);

    vector<link>links{link1,link2,link3};

    manipulator robot(links, config);

    vector<Matrix4f>cg = robot.constant_geometry();

    
    for (size_t i = 0; i < cg.size(); i++){
        cout << cg[i] << endl;
        cout << endl;
    }

}

