#pragma once
#include <vector>
#include <memory>
#include "../object/Object.hpp"
#include "../Intersect.hpp"

class Accelerate
{
public:
	virtual ~Accelerate() {};

	// Dispose accelerate, release objects
	std::vector<std::unique_ptr<Object>> dispose()
	{
		std::vector<std::unique_ptr<Object>> objects;
		dispose(objects);
		return std::move(objects);
	};

	virtual Intersect intersect_ray(const Ray& ray) const = 0;

protected:
	virtual void dispose(std::vector<std::unique_ptr<Object>>& objects) = 0;
};
