#pragma once
#include <limits>

constexpr auto infinity = std::numeric_limits<float>::infinity();

class Intersect
{
public:
    Intersect() : happend(false), t(infinity){};

    Intersect(float t) : happend(true), t(t){};

    bool happend;

    float t;
};
