//
//  Created by Alan 16/04/2024
//
#ifndef BOTTLEBRUSH_ENGINE_SKYBOX_H
#define BOTTLEBRUSH_ENGINE_SKYBOX_H

#include "GraphicsFactory.h"

#include <filesystem>
#include <stb/stb_image.h>

class Skybox {
 public:
  Skybox() = default;
  Skybox(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);

  /// @author Alan
  /// @brief Inits creation of the mesh
  /// @param model needs a cube obj
  /// @param texPaths requires 6 textures for a cubemap
  void InitMesh(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);

  /// @author Alan
  /// @brief Binds the Cubemap texture before drawing
  void ActiveTexture();

  inline std::unique_ptr<Model>& getModel() { return m_Model; }
 private:
  std::unique_ptr<Model> m_Model;
  std::unique_ptr<Texture> m_Texture;
};

#endif  // BOTTLEBRUSH_ENGINE_SKYBOX_H
