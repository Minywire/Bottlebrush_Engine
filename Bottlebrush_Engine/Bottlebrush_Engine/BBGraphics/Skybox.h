#include "GraphicsFactory.h"

class Skybox {
 public:
  Skybox();
  ~Skybox();

  void InitMesh();
  inline std::unique_ptr<Model>& getModel() { return m_Model; }
 private:
  std::unique_ptr<Model> m_Model;
};
