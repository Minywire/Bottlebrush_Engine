#include "GraphicsFactory.h"

#include <filesystem>
#include <stb/stb_image.h>

class Skybox {
 public:
  Skybox(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);
  ~Skybox();

  void InitMesh(std::filesystem::path model, std::vector<std::filesystem::path> texPaths);
  void ActiveTexture();
  inline std::unique_ptr<Model>& getModel() { return m_Model; }
 private:
  std::unique_ptr<Model> m_Model;
  std::unique_ptr<Texture> m_Texture;
};
