#include "Mat4.hpp"
#include <cmath>

Mat4::Mat4()
{
    for (int i = 0; i < 16; i++)
        m[i] = 0.0f;
}

Mat4 Mat4::identity()
{
    Mat4 r;
    r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
    return r;
}

Mat4 Mat4::operator*(const Mat4& o) const
{
    Mat4 r;
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            for (int k = 0; k < 4; k++)
                r.m[col * 4 + row] += m[k * 4 + row] * o.m[col * 4 + k];
    return r;
}

Mat4 Mat4::translate(const Vec3& t)
{
    Mat4 r = identity();
    r.m[12] = t.x;
    r.m[13] = t.y;
    r.m[14] = t.z;
    return r;
}

Mat4 Mat4::scale(const Vec3& s)
{
    Mat4 r = identity();
    r.m[0] = s.x;
    r.m[5] = s.y;
    r.m[10] = s.z;
    return r;
}

// Rotation autour d'un axe quelconque (formule de Rodrigues)
Mat4 Mat4::rotate(const Vec3& axis, float a)
{
    Vec3 n = axis.normalized();
    float c = std::cos(a);
    float s = std::sin(a);
    float t = 1.0f - c;

    Mat4 r = identity();
    r.m[0]  = t * n.x * n.x + c;
    r.m[1]  = t * n.x * n.y + s * n.z;
    r.m[2]  = t * n.x * n.z - s * n.y;

    r.m[4]  = t * n.x * n.y - s * n.z;
    r.m[5]  = t * n.y * n.y + c;
    r.m[6]  = t * n.y * n.z + s * n.x;

    r.m[8]  = t * n.x * n.z + s * n.y;
    r.m[9]  = t * n.y * n.z - s * n.x;
    r.m[10] = t * n.z * n.z + c;
    return r;
}

Mat4 Mat4::rotateX(float a)
{
    Mat4 r = identity();
    r.m[5]  = std::cos(a);
    r.m[9]  = -std::sin(a);
    r.m[6]  = std::sin(a);
    r.m[10] = std::cos(a);
    return r;
}

Mat4 Mat4::rotateY(float a)
{
    Mat4 r = identity();
    r.m[0]  = std::cos(a);
    r.m[8]  = std::sin(a);
    r.m[2]  = -std::sin(a);
    r.m[10] = std::cos(a);
    return r;
}

Mat4 Mat4::rotateZ(float a)
{
    Mat4 r = identity();
    r.m[0] = std::cos(a);
    r.m[4] = -std::sin(a);
    r.m[1] = std::sin(a);
    r.m[5] = std::cos(a);
    return r;
}

Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    Vec3 f = (center - eye).normalized();   // direction du regard
    Vec3 s = cross(f, up).normalized();     // droite
    Vec3 u = cross(s, f);                   // haut réel

    Mat4 r = identity();
    r.m[0] = s.x;   r.m[4] = s.y;   r.m[8]  = s.z;
    r.m[1] = u.x;   r.m[5] = u.y;   r.m[9]  = u.z;
    r.m[2] = -f.x;  r.m[6] = -f.y;  r.m[10] = -f.z;
    r.m[12] = -dot(s, eye);
    r.m[13] = -dot(u, eye);
    r.m[14] = dot(f, eye);
    return r;
}

Mat4 Mat4::perspective(float fovRad, float aspect, float nearPlane, float farPlane)
{
    Mat4 r;
    float f = 1.0f / std::tan(fovRad / 2.0f);
    r.m[0]  = f / aspect;
    r.m[5]  = f;
    r.m[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
    r.m[11] = -1.0f;
    r.m[14] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
    return r;
}

float Mat4::radians(float degrees)
{
    return degrees * 3.14159265358979323846f / 180.0f;
}