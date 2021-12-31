#include <limits>
#include "SdfObject.hpp"

// TODO[pref]: 调整尝试次数
constexpr auto max_try_matching = 100;

SdfObject::SdfObject(Eigen::Vector3f position) : Object(position) {};

bool SdfObject::intesect_ray(Ray& ray) const {
	// Ray Matching Algorithm
	auto t = 0.0;
	for (int i = 0; i < max_try_matching && ray.is_valid(t); i++) {
		auto dis = sdf(ray(t));
		if (dis < std::numeric_limits<float>::epsilon()) {
			return true;
		}
		t += dis;
	}

	return false;
}
