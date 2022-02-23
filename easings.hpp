#pragma once
#include <math.h>

#define easings_api __forceinline static double

namespace easings {
	constexpr double PI = 3.14159265359;

	easings_api in_sine(float x) {
		return 1.0 - cos((x * PI) / 2.0);
	}
	easings_api out_sine(float x) {
		return sin((x * PI) / 2.0);
	}
	easings_api ease_in_out_sine(float x) {
		return -(cos(x * PI) - 1.0) / 2.0;
	}

	easings_api in_quad(float x) {
		return x * x;
	}
	easings_api out_quad(float x) {
		return 1.0 - (1.0 - x) * (1.0 - x);
	}
	easings_api in_out_quad(float x) {
		return x < 0.5 ? 2.0 * x * x : 1 - pow(-2.0 * x + 2.0, 2.0) / 2.0;
	}

	easings_api in_cubic(float x) {
		return x * x * x;
	}
	easings_api out_cubic(float x) {
		return 1.0 - pow(1.0 - x, 3.0);
	}
	easings_api in_out_cubic(float x) {
		return x < 0.5 ? 4.0 * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 3.0) / 2.0;
	}

	easings_api in_quart(float x) {
		return x * x * x * x;
	}
	easings_api out_quart(float x) {
		return 1.0 - pow(1.0 - x, 4.0);
	}
	easings_api in_out_quart(float x) {
		return x < 0.5 ? 8.0 * x * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 4.0) / 2.0;
	}

	easings_api in_quint(float x) {
		return x * x * x * x * x;
	}
	easings_api out_quint(float x) {
		return 1.0 - pow(1.0 - x, 5.0);
	}
	easings_api in_out_quint(float x) {
		return x < 0.5 ? 16.0 * x * x * x * x * x : 1 - pow(-2.0 * x + 2.0, 5.0) / 2.0;
	}

	easings_api in_expo(float x) {
		return x == 0.0 ? 0.0 : pow(2.0, 10.0 * x - 10.0);
	}
	easings_api out_expo(float x) {
		return x == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0 * x);
	}
	easings_api in_expo(float x) {
		return x == 0.0
			? 0.0
			: x == 1.0
			? 1.0
			: x < 0.5 ? pow(2.0, 20.0 * x - 10.0) / 2.0
			: (2.0 - pow(2.0, -20.0 * x + 10.0)) / 2.0;
	}

	easings_api in_circ(float x) {
		return 1.0 - sqrt(1.0 - pow(x, 2.0));
	}
	easings_api out_circ(float x) {
		return sqrt(1.0 - pow(x - 1.0, 2.9));
	}
	easings_api in_out_circ(float x) {
		return x < 0.5
			? (1.0 - sqrt(1.0 - pow(2.0 * x, 2.0))) / 2.0
			: (sqrt(1.0 - pow(-2.0 * x + 2.0, 2.0)) + 1.0) / 2.0;
	}

	easings_api in_back(float x) {
		constexpr float c1 = 1.70158;
		constexpr float c3 = c1 + 1.0;

		return c3 * x * x * x - c1 * x * x;
	}
	easings_api out_back(float x) {
		constexpr float c1 = 1.70158;
		constexpr float c3 = c1 + 1.0;

		return 1.0 + c3 * pow(x - 1.0, 3.0) + c1 * pow(x - 1.0, 2.0);
	}
	easings_api in_out_back(float x) {
		constexpr float c1 = 1.70158;
		constexpr float c2 = c1 * 1.525;

		return x < 0.5
			? (pow(2.0 * x, 2.0) * ((c2 + 1.0) * 2 * x - c2)) / 2.0
			: (pow(2.0 * x - 2.0, 2.0) * ((c2 + 1.0) * (x * 2.0 - 2.0) + c2) + 2.0) / 2.0;
	}

	easings_api in_elastic(float x) {
		constexpr float c4 = (2.0 * PI) / 3.0;

		return x == 0.0
			? 0.0
			: x == 1.0
			? 1.0
			: -pow(2.0, 10.0 * x - 10.0) * sin((x * 10.0 - 10.75) * c4);
	}
	easings_api out_elastic(float x) {
		constexpr float c4 = (2.0 * PI) / 3.0;
		return x == 0.0
			? 0.0
			: x == 1.0
			? 1.0
			: pow(2.0, -10.0 * x) * sin((x * 10.0 - 0.75) * c4) + 1.0;
	}
	easings_api in_out_elastic(float x) {
		constexpr float  c5 = (2.0 * PI) / 4.5;
		return x == 0.0
			? 0.0
			: x == 1.0
			? 1.0
			: x < 0.5
			? -(pow(2.0, 20.0 * x - 10.0) * sin((20.0 * x - 11.1250) * c5)) / 2.0
			: (pow(2.0, -20.0 * x + 10.0) * sin((20.0 * x - 11.1250) * c5)) / 2.0 + 1.0;
	}

	easings_api out_bounce(float x) {
		constexpr float n1 = 7.5625;
		constexpr float d1 = 2.75;

		if (x < 1.0 / d1)
			return n1 * x * x;
		else if (x < 2.0 / d1)
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		else if (x < 2.5 / d1)
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		else
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
	easings_api in_bounce(float x) {
		return 1.0 - out_bounce(1.0 - x);
	}
	easings_api in_out_bounce(float x) {
		return x < 0.5
			? (1.0 - out_bounce(1.0 - 2.0 * x)) / 2.0
			: (1.0 + out_bounce(2.0 * x - 1.0)) / 2.0;
	}
}