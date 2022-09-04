#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
    this->row[0] = r1;
    this->row[1] = r2;
    this->row[2] = r3;
    this->row[3] = r4;
}

Float4& Matrix::operator[](int idx) {
    assert(idx>=0 && idx<=3);
    return(row[idx]);
}

Float4 Matrix::operator[](int idx) const {
    assert(idx>=0 && idx<=3);
    return(row[idx]);
}

Matrix Matrix::operator+(const Matrix& b) const {
    return Matrix(this->row[0] + b[0], this->row[1] + b[1], this->row[2] + b[2], this->row[3] + b[3]);
}

Matrix Matrix::operator-(const Matrix& b) const {
    return Matrix(this->row[0] - b[0], this->row[1] - b[1], this->row[2] - b[2], this->row[3] - b[3]);
}

Matrix Matrix::transpose() const {
    Matrix m;
    m[0] = Float4(this->row[0][0], this->row[1][0], this->row[2][0], this->row[3][0]);
    m[1] = Float4(this->row[0][1], this->row[1][1], this->row[2][1], this->row[3][1]);
    m[2] = Float4(this->row[0][2], this->row[1][2], this->row[2][2], this->row[3][2]);
    m[3] = Float4(this->row[0][3], this->row[1][3], this->row[2][3], this->row[3][3]);
    return m;
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    if (this->row[0] == b.row[0] && this->row[1] == b.row[1] && this->row[2] == b.row[2] && this->row[3] == b.row[3]) {
        return true;
    }
    return false;
}

bool Matrix::operator!=(const Matrix& b) const {
    return !((*this) == b);
}

Matrix product(const Matrix& a, const Matrix& b) {
    Matrix b_T = b.transpose();
    Matrix p = Matrix::zero();
    for (uint16_t i = 0; i < 4; i++) {
        for (uint16_t j = 0; j < 4; j++) {
            p[i][j] = dot(a[i], b_T[j]);
        }
    }
    return(p);
}

Matrix operator*(const Matrix& a, float scalar) {
    return Matrix(a[0] * scalar, a[1] * scalar, a[2] * scalar, a[3] * scalar);
}

Matrix operator*(float scalar, const Matrix& a) {
    return Matrix(a[0] * scalar, a[1] * scalar, a[2] * scalar, a[3] * scalar);
}

Float4 Matrix::operator*(const Float4& b) const {
    return Float4(dot(row[0],b), dot(row[1],b), dot(row[2],b), dot(row[3],b));
}

Vector Matrix::operator*(const Vector& b) const {
    Float4 b_f = Float4(b);
    return Vector(dot(row[0], b_f), dot(row[1], b_f), dot(row[2], b_f));
}

Point Matrix::operator*(const Point& b) const {
    Float4 p = (*this) * Float4(b);
    return Point(p.x / p.w, p.y / p.w, p.z/ p.w);
}

float Matrix::det() const {
    Float4 result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    // Taken from the above definition of Matrix::inverse()
    result[0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0] + m[0][1] * result[1] + m[0][2] * result[2] + m[0][3] * result[3];
    return(det);
}

Matrix Matrix::zero() {
    Float4 z = Float4::rep(0.f);
    return Matrix(z, z, z, z);
}

Matrix Matrix::identity() {
    Float4 r1(1.f, 0.f, 0.f, 0.f);
    Float4 r2(0.f, 1.f, 0.f, 0.f);
    Float4 r3(0.f, 0.f, 1.f, 0.f);
    Float4 r4(0.f, 0.f, 0.f, 1.f);
    return Matrix(r1, r2, r3, r4);
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    return Matrix(Float4(e1), Float4(e2), Float4(e3), Float4(0.f, 0.f, 0.f, 1.f)).transpose();
}

}
