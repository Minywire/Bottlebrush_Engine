//
// Created by Marco on 09/03/24.
//
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/**
 * @class BBAssetImporter
 * By default, this will use the right handed coordinate system, the same as opengl.
 * The data is stored in a tree structure that lets you access all nodes, meshes, materials, animations or textures that were read from the imported file
 */
class BBAssetImporter {
 public:
  BBAssetImporter();

  /**
   * @brief Loads a 3D model from a given file path
   * @param filePath The filepath of the model
   * @return true or false if the model loaded.
   * @author Niamh Wilson
   */
  bool loadModel(const std::string& filePath);

 private:
  Assimp::Importer import;
};





