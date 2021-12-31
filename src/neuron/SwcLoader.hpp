#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../render/object/SdfObject.hpp"

class SwcLoader {
public:
	static std::vector<std::unique_ptr<SdfObject>> load(const std::string& filepath);
};
