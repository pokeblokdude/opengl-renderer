#include "Scene.h"
#include "Object.h"

Scene::~Scene() {
	for (Object* obj : objects) {
		delete obj;
	}
}