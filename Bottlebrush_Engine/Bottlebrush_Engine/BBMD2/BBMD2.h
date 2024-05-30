#include "MD2Model.h"

class BBMD2
{
public:
  BBMD2(std::string model_path, std::string texture_path);

  int getSpecificAnim(std::string animName);
  std::string getSpecificAnim(int animIndx);

  void renderAnimation(int animIndex, float interpolation);

  void updatePosHeight(float newHeight);

  const glm::mat4 getModelMatrix() const;

  const MD2Model& returnMD2() const;

 private:
	MD2Model m_model;
};	