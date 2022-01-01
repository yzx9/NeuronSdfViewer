#pragma once

class Bound3Intersect {
public:
	bool happend;
	float tMin;
	float tMax;

	Bound3Intersect();

	Bound3Intersect(float tMin, float tMax);
};
