#pragma once

#include "Ray.hpp"

class Object
{
public:
    virtual bool intesect_ray(Ray &ray) const = 0;
};
