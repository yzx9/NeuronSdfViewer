#pragma once
#include "../MaterialBase.hpp"

class MaterialLight : public MaterialBase
{
public:
    bool has_emission() const { return true; };

protected:
    MaterialLight(MaterialType type) : MaterialBase(type) {};
};
