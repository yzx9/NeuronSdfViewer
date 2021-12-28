#include "../render/Scene.hpp"

class NeuronScene : public Scene
{
public:
	NeuronScene(int width, int height);
	~NeuronScene();

	void load(std::string filepath);

private:

};
