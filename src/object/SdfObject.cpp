#include <limits>
#include "SdfObject.hpp"

// TODO[pref]: �������Դ���
constexpr auto max_try_matching = 10;

/// <summary>
/// Ray Matching Algorithm
/// </summary>
/// <param name="ray"></param>
/// <returns></returns>
bool SdfObject::intesect_ray(Ray& ray) const {
	auto t = 0.0;

	for (int i = 0; i < max_try_matching; i++) {
		auto dis = sdf(ray(t));
		if (dis < std::numeric_limits<float>::epsilon()) {
			return true;
		}

		t += dis;
	}

	return false;
}