#pragma once

#include <math.h>
#include <algorithm>

#define def_clamp(v, i, a) ( std::min( std::max(v, i), a) )
#define def_mix( x, y, m ) ( x+((y-x)*m) )

struct float2 {
    float2() {}
    float2( float x, float y ) : x( x ), y( y ) {}
    float x = 0.0f, y = 0.0f;

    float2 operator+(const float2& o) {
        return float2(this->x + o.x, this->y + o.y);
    }

    float2 operator*(const float& o) {
        return float2(this->x * o, this->y * o);
    }
};

float2 operator*(const float& lhs, const float2& rhs);

struct int2
{
    int2() {}
    int2( int32_t x, int32_t y ) : x( x ), y( y ) {}
    int32_t x = 0, y = 0;

    int2 operator+( const int2& o )
    {
        return int2( this->x + o.x, this->y + o.y );
    }

    int2 operator*( const int32_t& o )
    {
        return int2( this->x * o, this->y * o );
    }
};

struct float3 {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    float3() {}
    float3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}
    float3( float2 v, float z ) : x( v.x ), y( v.y ), z( z ) {}

    float length();
    void normalize();

    float3 operator+( const float3& o ) {
        return float3( this->x + o.x, this->y + o.y, this->z + o.z );
    }

    float3 operator+( const float& o ) {
        return float3( this->x + o, this->y + o, this->z + o );
    }

    float3 operator-( const float3& o ) {
        return float3( this->x - o.x, this->y - o.y, this->z - o.z );
    }

    float3 operator-( const float& o ) {
        return float3( this->x - o, this->y - o, this->z - o );
    }

    float3 operator*( const float& o ) {
        return float3( this->x * o, this->y * o, this->z  * o );
    }

    float3 operator*( const float3& o ) {
        return float3( this->x * o.x, this->y * o.y, this->z * o.z );
    }

    float3 operator/( const float& o ) {
        return float3( this->x / o, this->y / o, this->z / o );
    }

};

float3 operator*( const float& lhs, const float3& rhs );

struct float4 {
    float4() {}
    float4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {}
    float4( float3 v, float w ) : x( v.x ), y( v.y ), z( v.z ), w( w ) {}
    float4(float2 v, float z, float w) : x(v.x), y(v.y), z(z), w(w) {}
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

    void normalize();
    void clamp(float min, float max);

    float4 operator+(const float4& o) {
        return float4(this->x + o.x, this->y + o.y, this->z + o.z, this->w + o.w);
    }

    float4 operator/(const float& o) {
        return float4(this->x / o, this->y / o, this->z / o, this->w / o);
    }

    float4 operator*(const float& o) {
        return float4(this->x * o, this->y * o, this->z  * o, this->w  * o);
    }
};

float4 operator*(const float& lhs, const float4& rhs);

struct float4x4 {
    float m[16] = 
    { 
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f 
    };

    float4x4() {}
    float4x4( float x ) { initialize(x); }

    void initialize(float i);
    void identity(){ initialize(1.0f); }

    void translate( float x, float y, float z );
    void rotate_y( float a );
    void perspective( float fov, float aspect_ratio, float n, float f );
    void float4x4::look_at( float3 eye, float3 direction, float3 up );
};

float4 operator*( const float4x4& lhs, const float4& rhs );
float4x4 operator*( const float4x4& lhs, const float4x4& rhs );

float orient2d( const float3 a, const float3 b, const float2 c );
float3 interpolate_floats(float3 pos, float3 x1, float3 x2, float3 x3); 
float3 half(float3 a, float3 b);
float3 normal(const float3 f);
float dot(const float3 d, const float3 f);
float3 cross(const float3 d, const float3 f);