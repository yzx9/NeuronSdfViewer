module;
#include <limits>
export module Render.Basis:Intersect;

constexpr auto infinity = std::numeric_limits<float>::infinity();

export class Intersect
{
public:
    bool happend;

    float t;

    Intersect() : happend(false), t(infinity) {};

    Intersect(float t) : happend(true), t(t) {};

private:

};
