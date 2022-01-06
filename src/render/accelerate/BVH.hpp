#pragma once
#include <vector>
#include <memory>
#include "Bound3.hpp"
#include "../Intersect.hpp"
#include "../object/Object.hpp"

class BVH
{
public:
	static std::unique_ptr<BVH> build(std::vector<std::unique_ptr<Object>> objects);

	Intersect intersect_ray(const Ray& ray) const;

	BVH(std::unique_ptr<Object> object);

	BVH(std::unique_ptr<BVH> bvh1, std::unique_ptr<BVH> bvh2);

private:
	std::unique_ptr<Bound3> aabb;
	std::unique_ptr<Object> object;

	std::unique_ptr<BVH> left;
	std::unique_ptr<BVH> right;

	static std::unique_ptr<BVH> build(std::vector<std::unique_ptr<BVH>> &bounds, int left, int right, int depth);
};
