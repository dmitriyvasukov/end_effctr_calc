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
enum OffSetAxis { X = 0, Y = 1, Z = 2 };

class Link {
private:
    Matrix3f M;
    float length;
    OffSetAxis axis;
    LinkType B;
    float q;

    Matrix4f getAii_Matrix() const {
        Vector3f L = Vector3f::Zero();
        L[axis] = length;
        
        Matrix4f Aii_ = Matrix4f::Identity();
        Aii_.block<3,3>(0,0) = M;
        Aii_.block<3,1>(0,3) = M * L; // Умножаем ориентацию на смещение
        
        return Aii_;
    }

public:
    Matrix4f getAijMatrix() const {
        float rad_q = deg2rad(q);
        Matrix4f Q = Matrix4f::Identity();
        
        if (B == ROTATING) {
            Q.block<2,2>(0,0) << cos(rad_q), -sin(rad_q),
                                sin(rad_q),  cos(rad_q);
        } else {
            Q(static_cast<int>(axis), 3) = rad_q;
        }
        
        return getAii_Matrix() * Q;
    }

    Link(Matrix3f M, float length, OffSetAxis axis, LinkType B, float q)
        : M(M), length(length), axis(axis), B(B), q(q) {}
};

class Manipulator {
private:
    vector<Link> links;
    Matrix4f base_transform;

public:
    Matrix4f getTMatrix() const {
        Matrix4f T = base_transform;
        for (const auto& link : links) {
            T = T * link.getAijMatrix();
        }
        return T;
    }

    Manipulator(vector<Link> links, Matrix4f base = Matrix4f::Identity())
        : links(links), base_transform(base) {}
};

int main() {
    // Матрицы ориентации звеньев (M1, M2, M3 соответствуют вашим расчетам)
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

    // Создаем звенья с параметрами из ваших расчетов
    Link link0(M0, 0.0, Z, ROTATING, 0);   // Базовое звено
    Link link1(M1, 0.8, Z, ROTATING, 30);  // q1 = 30°
    Link link2(M2, 0.6, X, ROTATING, 20);  // q2 = 20°
    Link link3(M3, 0.5, X, ROTATING, 10);  // q3 = 10°

    // Собираем манипулятор
    Manipulator robot({link0, link1, link2, link3});
    
    // Получаем итоговую матрицу преобразования
    Matrix4f A03 = robot.getTMatrix();
    
    cout << "Final transformation matrix A03:\n" << A03 << endl;
    
    return 0;
}