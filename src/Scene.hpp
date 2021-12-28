#pragma once

#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "object/Object.hpp"

class Scene
{
public:
    int width;
    int height;

    Scene(int width, int height);
    void add(std::unique_ptr<Object> obj);
    Eigen::Vector3f cast_ray(std::unique_ptr<Object> obj);

private:
    std::vector<std::unique_ptr<Object>> objects;
};
