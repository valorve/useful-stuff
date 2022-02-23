#pragma once
#include <algorithm>
#include <cmath>

class c_color {
private:
	union {
		uint8_t rgba[4] = {};
		uint32_t as_u32;
	} m_color;
public:
	__forceinline constexpr c_color() {
		this->u32() = 0;
	}

	__forceinline constexpr c_color(uint32_t color32) {
		this->u32() = color32;
	}

	__forceinline constexpr c_color(int r, int g, int b) {
		this->set((uint8_t)r, (uint8_t)g, (uint8_t)b, 255);
	}

	__forceinline constexpr c_color(int r, int g, int b, int a) {
		this->set((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
	}

	__forceinline constexpr void set(uint32_t value) {
		this->u32() = value;
	}

	__forceinline constexpr void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 0xFF) {
		m_color.rgba[0] = std::clamp<uint8_t>(_r, 0u, 255u);
		m_color.rgba[1] = std::clamp<uint8_t>(_g, 0u, 255u);
		m_color.rgba[2] = std::clamp<uint8_t>(_b, 0u, 255u);
		m_color.rgba[3] = std::clamp<uint8_t>(_a, 0u, 255u);
	}

	__forceinline constexpr void get(int& r, int& g, int& b, int& a) const {
		r = m_color.rgba[0];
		g = m_color.rgba[1];
		b = m_color.rgba[2];
		a = m_color.rgba[3];
	}

	__forceinline constexpr void get(int& r, int& g, int& b) const {
		r = m_color.rgba[0];
		g = m_color.rgba[1];
		b = m_color.rgba[2];
	}

	__forceinline constexpr uint8_t& r() { return m_color.rgba[0]; }
	__forceinline constexpr uint8_t& g() { return m_color.rgba[1]; }
	__forceinline constexpr uint8_t& b() { return m_color.rgba[2]; }
	__forceinline constexpr uint8_t& a() { return m_color.rgba[3]; }

	__forceinline constexpr uint8_t r() const { return m_color.rgba[0]; }
	__forceinline constexpr uint8_t g() const { return m_color.rgba[1]; }
	__forceinline constexpr uint8_t b() const { return m_color.rgba[2]; }
	__forceinline constexpr uint8_t a() const { return m_color.rgba[3]; }

	__forceinline constexpr uint8_t& operator[](int idx) {
		return m_color.rgba[idx];
	}

	const __forceinline constexpr uint8_t& operator[](int idx) const {
		return m_color.rgba[idx];
	}

	const __forceinline constexpr bool& operator ==(const c_color& other) const {
		return other.u32() == this->u32();
	}

	const __forceinline constexpr bool& operator !=(const c_color& other) const {
		return !(*this == other);
	}

	__forceinline constexpr c_color& operator=(const c_color& other) {
		this->u32() = other.u32();
		return *this;
	}

	__forceinline constexpr uint32_t& u32() {
		return m_color.as_u32;
	}
	__forceinline constexpr uint32_t u32() const {
		return m_color.as_u32;
	}

	__forceinline constexpr double hue() const {
		double r = m_color.rgba[0] / 255.f;
		double g = m_color.rgba[1] / 255.f;
		double b = m_color.rgba[2] / 255.f;

		double mx = std::max<double>(r, std::max<double>(g, b));
		double mn = std::min<double>(r, std::min<double>(g, b));
		if (mx == mn)
			return 0.f;

		double delta = mx - mn;

		double hue = 0.f;
		if (mx == r)
			hue = (g - b) / delta;
		else if (mx == g)
			hue = 2.f + (b - r) / delta;
		else
			hue = 4.f + (r - g) / delta;

		hue *= 60.f;
		if (hue < 0.f)
			hue += 360.f;

		return hue / 360.f;
	}

	__forceinline constexpr double saturation() const {
		double r = m_color.rgba[0] / 255.f;
		double g = m_color.rgba[1] / 255.f;
		double b = m_color.rgba[2] / 255.f;

		double mx = std::max<double>(r, std::max<double>(g, b));
		double mn = std::min<double>(r, std::min<double>(g, b));

		double delta = mx - mn;

		if (mx == 0.f)
			return delta;

		return delta / mx;
	}

	__forceinline constexpr double brightness() const {
		double r = m_color.rgba[0] / 255.f;
		double g = m_color.rgba[1] / 255.f;
		double b = m_color.rgba[2] / 255.f;

		return std::max<double>(r, std::max<double>(g, b));
	}

	static __forceinline constexpr c_color hsb(float hue, float saturation, float brightness) {
		hue = std::clamp<float>(hue, 0.f, 1.f);
		saturation = std::clamp<float>(saturation, 0.f, 1.f);
		brightness = std::clamp<float>(brightness, 0.f, 1.f);

		float h = (hue == 1.f) ? 0.f : (hue * 6.f);
		float f = h - static_cast<int>(h);
		float p = brightness * (1.f - saturation);
		float q = brightness * (1.f - saturation * f);
		float t = brightness * (1.f - (saturation * (1.f - f)));

		if (h < 1.f)
			return c_color((int)(brightness * 255), (int)(t * 255), (int)(p * 255));
		else if (h < 2.f)
			return c_color((int)(q * 255), (int)(brightness * 255), (int)(p * 255));
		else if (h < 3.f)
			return c_color((int)(p * 255), (int)(brightness * 255), (int)(t * 255));
		else if (h < 4)
			return c_color((int)(p * 255), (int)(q * 255), (int)(brightness * 255));
		else if (h < 5)
			return c_color((int)(t * 255), (int)(p * 255), (int)(brightness * 255));
		else
			return c_color((int)(brightness * 255), (int)(p * 255), (int)(q * 255));
	}

	__forceinline constexpr c_color multiply(const c_color& other, float strength) const {
		if (*this == other)
			return *this;

		return c_color(
			(int)std::lerp((float)m_color.rgba[0], (float)other.r(), strength),
			(int)std::lerp((float)m_color.rgba[1], (float)other.g(), strength),
			(int)std::lerp((float)m_color.rgba[2], (float)other.b(), strength)
		);
	}

	__forceinline constexpr c_color new_alpha(int alpha) const {
		return c_color(m_color.rgba[0], m_color.rgba[1], m_color.rgba[2], std::clamp(alpha, 0, 255));
	}

	__forceinline constexpr c_color increase(int value, bool consider_alpha = false) const {
		return c_color(m_color.rgba[0] + value, m_color.rgba[1] + value, m_color.rgba[2] + value, m_color.rgba[3] + consider_alpha * value);
	}
	__forceinline constexpr c_color decrease(int value, bool consider_alpha = false) const {
		return increase(-value, consider_alpha);
	}
};

namespace colors {
	inline const constexpr c_color red = c_color(0xFF0000FF);
	inline const constexpr c_color green = c_color(0x00FF00FF);
	inline const constexpr c_color blue = c_color(0x0000FFFF);
	inline const constexpr c_color black = c_color(0x000000FF);
	inline const constexpr c_color white = c_color(0xFFFFFFFF);
}