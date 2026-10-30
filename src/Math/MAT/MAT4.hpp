#ifndef MAT4_HPP
#define MAT4_HPP

#include "Math/VEC/Vec3.hpp"

// Matrice 4x4 stockée en column-major (ordre attendu par OpenGL) :
// l'élément (ligne r, colonne c) est m[c * 4 + r].
class Mat4
{
public:
    float m[16];

    Mat4();                                   // matrice nulle
    static Mat4 identity();

    Mat4 operator*(const Mat4& o) const;

    static Mat4 translate(const Vec3& t);
    static Mat4 scale(const Vec3& s);
    static Mat4 rotate(const Vec3& axis, float angleRad);
    static Mat4 rotateX(float angleRad);
    static Mat4 rotateY(float angleRad);
    static Mat4 rotateZ(float angleRad);

    static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
    static Mat4 perspective(float fovRad, float aspect, float nearPlane, float farPlane);

    static float radians(float degrees);
};

#endif