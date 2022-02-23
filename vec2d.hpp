#pragma once
#include <cmath>

class vec2d {
public:
	float x, y;

	__forceinline constexpr vec2d() {
		x = y = 0.0f;
	}

	template< typename t >
	__forceinline constexpr vec2d(t X, t Y) {
		x = (float)X;
		y = (float)Y;
	}

	__forceinline constexpr vec2d(float* v) {
		x = v[0];
		y = v[1];
	}

	__forceinline constexpr vec2d(const float* v) {
		x = v[0];
		y = v[1];
	}

	__forceinline constexpr vec2d(const vec2d& v) {
		x = v.x; 
		y = v.y;
	}

	__forceinline constexpr vec2d& operator=(const vec2d& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	__forceinline constexpr float& operator[](int i) {
		return ((float*)this)[i];
	}

	__forceinline constexpr float operator[](int i) const {
		return ((float*)this)[i];
	}

	__forceinline constexpr vec2d& operator+=(const vec2d& v) {
		x += v.x; y += v.y; return *this;
	}

	__forceinline constexpr vec2d& operator-=(const vec2d& v) {
		x -= v.x; y -= v.y; return *this;
	}

	__forceinline constexpr vec2d& operator*=(const vec2d& v) {
		x *= v.x; y *= v.y; return *this;
	}

	__forceinline constexpr vec2d& operator/=(const vec2d& v) {
		x /= v.x; y /= v.y; return *this;
	}

	__forceinline constexpr vec2d& operator+=(float v) {
		x += v; y += v; return *this;
	}

	__forceinline constexpr vec2d& operator-=(float v) {
		x -= v; y -= v; return *this;
	}

	__forceinline constexpr vec2d& operator*=(float v) {
		x *= v; y *= v; return *this;
	}

	__forceinline constexpr vec2d& operator/=(float v) {
		x /= v; y /= v; return *this;
	}

	__forceinline constexpr vec2d operator+(const vec2d& v) const {
		return vec2d(x + v.x, y + v.y);
	}

	__forceinline constexpr vec2d operator-(const vec2d& v) const {
		return vec2d(x - v.x, y - v.y);
	}

	__forceinline constexpr vec2d operator*(const vec2d& v) const {
		return vec2d(x * v.x, y * v.y);
	}

	__forceinline constexpr vec2d operator/(const vec2d& v) const {
		return vec2d(x / v.x, y / v.y);
	}

	__forceinline constexpr vec2d operator+(float v) const {
		return vec2d(x + v, y + v);
	}

	__forceinline constexpr vec2d operator-(float v) const {
		return vec2d(x - v, y - v);
	}

	__forceinline constexpr vec2d operator*(float v) const {
		return vec2d(x * v, y * v);
	}

	__forceinline constexpr vec2d operator/(float v) const {
		return vec2d(x / v, y / v);
	}

	__forceinline constexpr void set(float X, float Y) {
		x = X; 
		y = Y;
	}

	__forceinline float length(void) const {
		return std::sqrt(x * x + y * y);
	}

	__forceinline float lengthsqr(void) const {
		return x * x + y * y;
	}

	__forceinline float dist_to(const vec2d& v) const {
		return (*this - v).length();
	}

	__forceinline float dist_to_sqr(const vec2d& v) const {
		return (*this - v).lengthsqr();
	}

	__forceinline constexpr float dot(const vec2d& v) const {
		return x * v.x + y * v.y;
	}

	__forceinline constexpr bool is_zero(void) const {
		return x > -FLT_EPSILON && x < FLT_EPSILON && y > -FLT_EPSILON && y < FLT_EPSILON;
	}

	__forceinline constexpr operator bool() const noexcept {
		return !is_zero();
	}
};