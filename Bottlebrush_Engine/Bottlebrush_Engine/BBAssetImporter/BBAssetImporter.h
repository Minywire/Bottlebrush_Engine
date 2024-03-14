//
// Created by Marco on 09/03/24.
//
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class BBAssetImporter {
 public:
  BBAssetImporter();

  bool loadModel(const std::string& filePath);

 private:
  Assimp::Importer import;
};





