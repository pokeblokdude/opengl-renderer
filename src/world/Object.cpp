#include "Object.h"
#include "../world/model/Model.h"

Object::~Object() {
	if (model)
		delete model;
}
