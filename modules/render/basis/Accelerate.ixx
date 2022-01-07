export module Render.Basis:Accelerate;

import :Ray;
import :Intersect;
import :Object;

class Accelerate
{
public:
	virtual ~Accelerate() = 0;

	virtual static std::unique_ptr<Accelerate> build(std::vector<std::unique_ptr<Object>> objects) = 0;

	virtual Intersect intersect_ray(const Ray& ray) const = 0;

private:

};
