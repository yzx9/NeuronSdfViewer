#pragma once
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "Ray.hpp"
#include "object/Object.hpp"
#include "accelerate/BVH.hpp"

class Scene
{
public:
    Scene();

    Eigen::Vector3f cast_ray(const Ray& ray) const;

    void add(std::unique_ptr<Object> obj);

    void build_bvh();

private:
    std::vector<std::unique_ptr<Object>> objects;

    std::unique_ptr<BVH> bvh;
};
