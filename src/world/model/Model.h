#pragma once

#include <vector>
#include <string>
#include "ModelUtil.h"
#include "Mesh.h"

class Model {

public:
	Model(const std::string& path) {
		loadModel(path);
	}
	~Model() {
		for (Mesh* m : meshes) {
			delete m;
		}
	}
	void Draw(class Shader& shader);
	void AddMesh(Mesh* mesh);

private:
	std::vector<Mesh*> meshes;
	std::string directory;
	std::vector<Texture> texturesLoaded;

	void loadModel(const std::string& path);
	void processNode(struct aiNode* node, const struct aiScene* scene);
	Mesh* processMesh(struct aiMesh* mesh, const struct aiScene* scene);
	std::vector<Texture> loadMaterialTextures(struct aiMaterial* mat, enum aiTextureType type, const std::string& typeName);
};