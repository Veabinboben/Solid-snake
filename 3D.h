#pragma once
#include "Snake.h";
class vec
{
public:
    float x;
    float y;
    float z;
    float length;
    vec() { x = y = z = 0; length = 0; }
    vec(float a, float b) { x = a; y = b; z = 0; length = sqrt(x * x + y * y); }
    vec(float a, float b, float c) { x = a; y = b; z = c; length = sqrt(x * x + y * y + c * c); }

    vec operator+(vec const& a) { return vec(x + a.x, y + a.y, z + a.z); }

    vec operator-(vec const& a) { return vec(x - a.x, y - a.y, z - a.z); }

    vec operator*(vec const& a) { return vec(x * a.x, y * a.y, z * a.z); }
    vec operator*(float const& a) { return vec(x * a, y * a, z * a); }

    vec operator/(vec const& a) { return vec(x / a.x, y / a.y, z / a.z); }

    void norm() { x = x / length; y = y / length; z = z / length; }

};
float dot(vec& a, vec& b);
float remap(float t, float a, float  b);
inline float MIN(float a, float b);
inline float MAX(float a, float b);
 wchar_t projectcubessnake(vec ro, vec rd, snake &player);
 wchar_t projectspheressnake(vec ro, vec rd, snake& player);
wchar_t projectspheresberry(vec ro, vec rd, berry& fruit);
wchar_t projectcubesberry(vec ro, vec rd, berry& fruit);
wchar_t projectborders(vec ro, vec rd, int coff);
