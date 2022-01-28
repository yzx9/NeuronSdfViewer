#pragma once
#include <Eigen/Dense>
#include "MaterialBase.hpp"

class Material : public MaterialBase
{
public:
    bool has_emission() const { return false; };

protected:
    Material(MaterialType type) : MaterialBase(type) {};
};
