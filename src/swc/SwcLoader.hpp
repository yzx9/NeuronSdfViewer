#include <string>
#include <vector>
#include <memory>
#include "../object/SdfObject.hpp"

class SwcLoader {
public:
	static std::vector<std::unique_ptr<SdfObject>> load(std::string filepath);
};
