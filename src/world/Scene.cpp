#include "Scene.h"

Scene::~Scene() {
	for (Object* obj : objects) {
		delete obj;
	}
}