#include <limits>
#include "Bound3Intersect.hpp"

constexpr auto infinity = std::numeric_limits<float>::infinity();

Bound3Intersect::Bound3Intersect()
	: happend(false), tMin(infinity), tMax(infinity)
{
}

Bound3Intersect::Bound3Intersect(float tMin, float tMax)
	: happend(true), tMin(tMin), tMax(tMax)
{
}

