#pragma once
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "Ray.hpp"
#include "object/Object.hpp"

class Scene
{
public:
    void add(std::unique_ptr<Object> obj);
    Eigen::Vector3f cast_ray(Ray ray) const;

private:
    std::vector<std::tuple<std::unique_ptr<Object>, Bound3>> objects;
};
