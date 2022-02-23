#pragma once
#include "vec2d.hpp"
#include <algorithm>

class vec3d {
public:
	float x, y, z;
	__forceinline constexpr vec3d() {
		x = y = z = 0.0f;
	}

	__forceinline constexpr vec3d(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	__forceinline constexpr vec3d(float* v) {
		x = v[0];
		y = v[1];
		z = v[2];
	}

	__forceinline constexpr vec3d(const float* v) {
		x = v[0];
		y = v[1];
		z = v[2];
	}

	__forceinline constexpr vec3d(const vec3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	__forceinline constexpr vec3d(const vec2d& v) {
		x = v.x;
		y = v.y;
		z = 0.0f;
	}

	__forceinline constexpr vec3d& operator=(const vec3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	__forceinline constexpr vec3d& operator=(const vec2d& v) {
		x = v.x;
		y = v.y;
		z = 0.0f;
		return *this;
	}

	__forceinline constexpr float& operator[](int i) {
		return ((float*)this)[i];
	}

	__forceinline constexpr float operator[](int i) const {
		return ((float*)this)[i];
	}

	__forceinline constexpr vec3d& operator+=(const vec3d& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	__forceinline constexpr vec3d& operator-=(const vec3d& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	__forceinline constexpr vec3d& operator*=(const vec3d& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	__forceinline constexpr vec3d& operator/=(const vec3d& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	__forceinline constexpr vec3d& operator+=(float v) {
		x += v;
		y += v;
		z += v;
		return *this;
	}

	__forceinline constexpr vec3d& operator-=(float v) {
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	__forceinline constexpr vec3d& operator*=(float v) {
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	__forceinline constexpr vec3d& operator/=(float v) {
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	__forceinline constexpr vec3d operator+(const vec3d& v) const {
		return vec3d(x + v.x, y + v.y, z + v.z);
	}

	__forceinline constexpr vec3d operator-(const vec3d& v) const {
		return vec3d(x - v.x, y - v.y, z - v.z);
	}

	__forceinline constexpr vec3d operator*(const vec3d& v) const {
		return vec3d(x * v.x, y * v.y, z * v.z);
	}

	__forceinline constexpr vec3d operator/(const vec3d& v) const {
		return vec3d(x / v.x, y / v.y, z / v.z);
	}

	__forceinline constexpr vec3d operator+(float v) const {
		return vec3d(x + v, y + v, z + v);
	}

	__forceinline constexpr vec3d operator-(float v) const {
		return vec3d(x - v, y - v, z - v);
	}

	__forceinline constexpr vec3d operator*(float v) const {
		return vec3d(x * v, y * v, z * v);
	}

	__forceinline constexpr vec3d operator/(float v) const {
		return vec3d(x / v, y / v, z / v);
	}

	__forceinline constexpr bool operator== (const vec3d& other) const {
		return x == other.x && y == other.y && other.z == other.z;
	}

	__forceinline constexpr bool operator!= (const vec3d& other) const {
		return !(*this == other);
	}

	__forceinline constexpr bool operator!() const {
		return this->is_zero();
	}

	__forceinline constexpr void set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) {
		x = X;
		y = Y;
		z = Z;
	}

	__forceinline constexpr vec3d center() const {
		return *this * 0.5f;
	}

	__forceinline float length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	__forceinline constexpr float length_sqr() const {
		return (x * x + y * y + z * z);
	}

	__forceinline float length2d() const {
		return std::sqrt(x * x + y * y);
	}

	__forceinline constexpr float length2d_sqr() const {
		return (x * x + y * y);
	}

	__forceinline float dist(const vec3d& v) const {
		return (*this - v).length();
	}

	__forceinline float dist_sqr(const vec3d& v) const {
		return (*this - v).length_sqr();
	}

	__forceinline constexpr float dot(const vec3d& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	__forceinline constexpr float dot_2d(const vec3d& v) const {
		return x * v.x + y * v.y;
	}

	__forceinline constexpr vec3d cross_product(const vec3d& v) const {
		return vec3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	__forceinline bool is_nan() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	__forceinline void normalize_in_place() {
		vec3d& v = *this;

		float iradius = 1.f / (this->length() + FLT_EPSILON);

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;
	}

	__forceinline constexpr bool is_zero() const {
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	__forceinline constexpr vec2d as_2d() {
		return vec2d(x, y);
	}
};