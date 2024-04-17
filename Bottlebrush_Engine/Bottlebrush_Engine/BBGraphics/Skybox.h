#include "GraphicsFactory.h"

#include <filesystem>

class Skybox {
 public:
  Skybox(std::filesystem::path model);
  ~Skybox();

  void InitMesh(std::filesystem::path model);
  void ActiveTexture();
  inline std::unique_ptr<Model>& getModel() { return m_Model; }
 private:
  std::unique_ptr<Model> m_Model;
  std::unique_ptr<Texture> m_Texture;
};
