#include "BBMD2.h"

BBMD2::BBMD2(const std::string& model_path, const std::string& texture_path)
	: m_model(model_path, texture_path)
{

}

int BBMD2::getSpecificAnim(const std::string & animName)
{
	return m_model.GetSpecificAnim(animName);
}

std::string BBMD2::getSpecificAnim(int animIndx)
{
	return m_model.GetSpecificAnim(animIndx);
}

void BBMD2::setTexture() const
{ 
	m_model.setTexture(); 
}
