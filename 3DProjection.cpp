#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "3D.h";
#include "ScreenSpecs.h";
#include "Snake.h";
using namespace std;



float dot(vec& a, vec& b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float remap(float t, float a, float  b)
{
    return ((t - a) / (b - a));
}

inline float MIN(float a, float b)
{
    return a < b ? a : b;
}

inline float MAX(float a, float b)
{
    return a < b ? b : a;
}

float spherecon(vec ro, vec rd, float rad, vec cen, wchar_t &put) // пересечение со сферой с радиусом rad в точке cen
{
    wchar_t gradient[9] = { '.',':','-','=','+','*' ,'#' ,'%', '@' };
    float pos = 0;
    vec dist = cen - ro;
    float  t = dot(dist, rd);
    vec p = ro + rd * t;
    vec yvec = cen - p;
    if (yvec.length < rad && t > 0)
    {
        float x = abs(sqrt(rad * rad - yvec.length * yvec.length));
        float t1 = abs(t - x);
        float t2 = abs(t + x);
        float iner = t1 > t2 ? t1 : t2;                
        pos = remap(iner, abs(dist.length), abs(dist.length) + rad);
        pos = (pos*7)+1;  //&&&&???????????????????
        if (pos < 0) put = ' ';
        else;
        put = gradient[int(pos)];  
        return iner;
    }
    return -1;
}

float cubecon(vec ro, vec rd, vec size, vec cen, int &type) // AABB куб с центров в точке cen и размерами size
{
    //wchar_t gradient[6] = { '=','+','*' ,'#' ,'%', '@' };

    //char out = ' ';

    vec min = (cen - size) * 0.5;
    vec max = (cen + size) * 0.5;

    float t[6];
    t[0] = (min.x - ro.x) * (1 / rd.x);
    t[1] = (max.x - ro.x) * (1 / rd.x);
    t[2] = (min.y - ro.y) * (1 / rd.y);
    t[3] = (max.y - ro.y) * (1 / rd.y);
    t[4] = (min.z - ro.z) * (1 / rd.z);
    t[5] = (max.z - ro.z) * (1 / rd.z);

    float tmin = MAX(MAX(MIN(t[0], t[1]), MIN(t[2], t[3])), MIN(t[4], t[5]));
    float tmax = MIN(MIN(MAX(t[0], t[1]), MAX(t[2], t[3])), MAX(t[4], t[5]));

    if (!(tmax < 0 || tmin > tmax))
    {
        float interc = tmin < 0 ? tmax : tmin;
        interc = abs(interc);
        
        for (int i = 0; i < 6; i++)
            if (interc == t[i]) { type = i; return interc; }
        
    }

    return -1;
}
// пересечени€ с каждым элементом змейки
wchar_t projectcubessnake(vec ro, vec rd,snake &player) 
{
    wchar_t gradient[9] = { '.',':','-','=','+','*' ,'#' ,'%', '@' };
    wchar_t out = ' ';
    float f = 0;
    float dist = -1;
    int type = 0;
            for (int p = 0; p < player.getlength(); p++)
            {               
                float cubex = player.body[p].x - (gamefieldsize /2);
               // cout << cubex << ' ';
                float cubey = player.body[p].y - (gamefieldsize / 2);
                f = cubecon(ro, rd, { 0.5,0.5,0.5}, {cubex,cubey,0},type);
           
                if (f != -1 && ((f < dist && dist != -1) || (f > dist && dist == -1)))
                {
                    out = gradient[type];
                    dist = f;
                }
            }
      
    return out;
}

 wchar_t projectspheressnake(vec ro, vec rd, snake& player)
{
    wchar_t out = ' ',put = ' ';
    float f = 0;
    float dist = -1;
    for (int p = 0; p < player.getlength(); p++)
    {
        float cubex = (player.body[p].x - (gamefieldsize >> 1));
        // cout << cubex << ' ';
        float cubey = (player.body[p].y - (gamefieldsize >> 1));
        f = spherecon(ro, rd, .5, { cubex,cubey,0 }, put);
        if (f != -1 && ((f < dist && dist != -1) || (f > dist && dist == -1)))
        {
            out = put;
            dist = f;
        }
    }

    return out;
}
 // пересечени€   с €годами
wchar_t projectspheresberry(vec ro, vec rd, berry& fruit)
{
    wchar_t out = ' ', put = ' ';
    float f = 0;
    float cubex = (fruit.getx()- (gamefieldsize / 2));
    float cubey = (fruit.gety() - (gamefieldsize / 2));
    f = spherecon(ro, rd, .5, { cubex,cubey,0 }, put);
    out = put;
    return out;
}

wchar_t projectcubesberry(vec ro, vec rd, berry& fruit)
{
    wchar_t gradient[9] = { '.',':','-','=','+','*' ,'#' ,'%', '@' };
    wchar_t out = ' ';
    int type;
    float f = 0;
    float cubex = fruit.getx() - (gamefieldsize / 2);
    float cubey = fruit.gety() - (gamefieldsize / 2);
    f = cubecon(ro, rd, { 0.5,0.5,0.5 }, { cubex,cubey,0 }, type);
    if (f != -1)
    out = gradient[type];
    return out;
}
// пересечение с границами 
wchar_t projectborders(vec ro, vec rd,int coff)
{
    wchar_t gradient[9] = { '.',':','-','=','+','*' ,'#' ,'%', '@' };
    float size = gamefieldsize;
    int type;
    float f = 0;
    wchar_t out = ' ';
    f = cubecon(ro, rd, { size/2* (coff),0.1,0.5 }, { 0,size / 2 * (coff),0 },type);
    if (f != -1) {
        return gradient[type];
    }
    f = cubecon(ro, rd, { size/2 * (coff),0.1,0.5 }, { 0,-size / 2 * (coff),0 }, type);
    if (f != -1) {
        return gradient[type];
    }
    f = cubecon(ro, rd, { 0.1,size/2 * (coff),0.5 }, { size / 2 * (coff),0,0 }, type);
    if (f != -1) {
        return gradient[type];
    }
    f = cubecon(ro, rd, { 0.1,size/2 * (coff),0.5 }, { -size / 2 * (coff),0,0 }, type);
    if (f != -1) {
        return gradient[type];
    }
    return out;
}
