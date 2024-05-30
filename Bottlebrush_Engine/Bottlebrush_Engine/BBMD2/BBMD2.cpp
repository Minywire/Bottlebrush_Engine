#include "BBMD2.h"

BBMD2::BBMD2(std::string model_path, std::string texture_path) 
{
	m_model = MD2Model(model_path, texture_path);
}

int BBMD2::getSpecificAnim(std::string animName) 
{
	return m_model.GetSpecificAnim(animName);
}

std::string BBMD2::getSpecificAnim(int animIndx) 
{
	return m_model.GetSpecificAnim(animIndx);
}

int BBMD2::getCurrentAnimationFrame(int animIndex, float interpolation) 
{
	return m_model.GetCurrentAnimationFrame(animIndex, interpolation);
}

const MD2Model& BBMD2::returnMD2() const
{ 
	return m_model; 
}

const std::vector<unsigned int>& BBMD2::getVecArrays() const
{
  return m_model.returnVaos();
}