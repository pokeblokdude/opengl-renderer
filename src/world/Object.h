#pragma once

#include "Transform.h"
#include <string>
#include <vector>

class Object {

public:
	uint32_t ID;
	std::string name;
	Transform transform;
	std::vector<class Object*> children;

	class Mesh* mesh;
};

