#pragma once

class Bound3Intersect
{
public:
    bool happend;
    float tMin;
    float tMax;

    Bound3Intersect() : happend(false), tMin(infinity), tMax(infinity){};

    Bound3Intersect(float tMin, float tMax) : happend(true), tMin(tMin), tMax(tMax){};
};
