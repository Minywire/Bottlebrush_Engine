#include "BBMD2.h"

BBMDD2::BBMD2(std::string model_path, std::string texture_path, Transform Tmat) 
{
  m_model = MD2Model(model_path, texture_path, Tmat);
}

int BBMD2::getSpecificAnim(std::string animName) 
{
	return m_model.GetSpecificAnim(animName);
}

std::string BBMD2::getSpecificAnim(int animIndx) 
{
	return m_model.GetSpecificAnim(animIndx);
}

void BBMD2::renderAnimation(int animIndex, float interpolation) 
{
  m_model.RenderAnimation(animIndex, interpolation);
}

void BBMD2::updatePosHeight(float newHeight) 
{
	m_model.updatePosHeight(newHeight);
}

const glm::mat4 BBMD2::getModelMatrix() const 
{
	return m_model.getModelMatrix();
}

const MD2Model& BBMD2::returnMD2() const
{ 
	return m_model; 
}