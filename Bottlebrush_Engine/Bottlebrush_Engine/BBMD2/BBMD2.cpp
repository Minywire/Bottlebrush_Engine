#include "BBMD2.h"

BBMD2::BBMD2(const std::string& model_path, const std::string& texture_path, float animationSpeed)
    : animSpeed(animationSpeed) {
	m_model = MD2Model(model_path, texture_path);
}

const int & BBMD2::getSpecificAnim(const std::string & animName)
{
	return m_model.GetSpecificAnim(animName);
}

const std::string & BBMD2::getSpecificAnim(int animIndx)
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

void BBMD2::setAnimationSpeed(const float& speed)
{
	animSpeed = speed;
}