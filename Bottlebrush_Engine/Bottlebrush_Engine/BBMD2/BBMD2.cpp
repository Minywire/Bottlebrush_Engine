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

int BBMD2::getAnimationCurrentFrame(int animIndex, float interpolation)
{
	return m_model.GetAnimationCurrentFrame(animIndex, interpolation);
}

void BBMD2::setTexture() const
{ 
	m_model.setTexture(); 
}

void BBMD2::updateInterpolation(float deltaTime)
{
    if (interpolation >= 1.0f)
	{
        interpolation = 0.f;
    } else
	{
        interpolation += deltaTime * animSpeed;
    }
}