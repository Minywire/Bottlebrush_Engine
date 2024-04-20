//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_MODEL_H
#define BOTTLEBRUSH_ENGINE_MODEL_H

#include <string>
#include <memory>
#include <filesystem>

#include "Mesh.h"

class Model {
public:
	virtual ~Model() = default;

	/// @author Niamh
	/// @brief loads the model using assimp and init it
	/// @param filePath is the object
	/// @param texturePath is the image to use as a texture
	virtual bool LoadModel(const std::filesystem::path& filePath, const std::filesystem::path &texturePath) = 0;

	/// @author Alan
	/// @brief unbinds the model from openGL storage
	virtual void UnbindModel() = 0;

	virtual inline std::vector<std::unique_ptr<Mesh>>& GetSubMeshes() = 0;
};


#endif //BOTTLEBRUSH_ENGINE_MODEL_H
