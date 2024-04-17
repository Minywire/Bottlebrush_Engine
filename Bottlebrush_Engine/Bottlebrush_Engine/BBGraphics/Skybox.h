#include "GraphicsFactory.h"

#include <filesystem>
#include <stb/stb_image.h>

class Skybox {
 public:
  Skybox(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);
  ~Skybox();

  /// @author Alan Brunet
  /// @brief Inits creation of the mesh
  /// @param model needs a cube obj
  /// @param texPaths requires 6 textures for a cubemap
  void InitMesh(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);

  /// @author Alan Brunet
  /// @brief Binds the texture before drawing
  void ActiveTexture();

  inline std::unique_ptr<Model>& getModel() { return m_Model; }
 private:
  std::unique_ptr<Model> m_Model;
  std::unique_ptr<Texture> m_Texture;
};