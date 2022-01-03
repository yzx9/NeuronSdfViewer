#pragma once
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "Ray.hpp"
#include "object/Object.hpp"
#include "accelerate/Bound3.hpp"

class Scene
{
public:
    void add(std::unique_ptr<Object> obj);
    Eigen::Vector3f cast_ray(Ray ray) const;

private:
    std::vector<std::tuple<std::unique_ptr<Object>, std::unique_ptr<Bound3>>> objects;
};
