//
// Created by Marco on 09/03/24.
//
#include "BBAssetImporter.h"
BBAssetImporter::BBAssetImporter() {
// import.SetPropertyInteger?
}
bool BBAssetImporter::loadModel(const std::string &filePath) {
  const aiScene* scene = import.ReadFile(filePath, aiProcess_Triangulate);

  if(!scene) {
    return false;
  }
  // NOTE This might be able to be made static when all is said and done.
  // If the scene exists, then return true, otherwise return false
  return true;
}
