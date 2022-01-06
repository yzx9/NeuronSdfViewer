#include <limits>
#include "Intersect.hpp"

constexpr auto infinity = std::numeric_limits<float>::infinity();

Intersect::Intersect() : happend(false), t(infinity) {}

Intersect::Intersect(float t) : happend(true), t(t) {}
