#pragma once

#include "Transform.h"
#include <string>
#include <vector>

class Object {

public:
	Object() {
		name = "New Object";
	}
	Object(const std::string& name) {
		this->name = name;
	}

	~Object();

	uint32_t ID;
	std::string name;
	Transform transform;

	Object* parent;
	std::vector<Object*> children;

	class Model* model;
	class Mesh* mesh;

};

