#pragma once
#include "../Ray.hpp"

class Object
{
public:
    Object(Eigen::Vector3f position) : position(position) {};

    virtual bool intesect_ray(Ray &ray) const = 0;

protected:
    Eigen::Vector3f position;
};
