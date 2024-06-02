#pragma once

#include "MD2Model.h"

class BBMD2
{
public:
	BBMD2(const std::string & model_path, const std::string & texture_path, float animationSpeed = 5.0f);

	const int & getSpecificAnim(const std::string & animName);
	const std::string & getSpecificAnim(int animIndx);

	int getAnimationCurrentFrame(int AnimIndx, float interpolation);
	
	void setTexture() const;

	const std::vector<unsigned int>& getVecArrays() const { return m_model.returnVaos(); }
      
	const int getModelSize() const { return m_model.getNumTris(); }

	void updateInterpolation(float deltaTime);

	void setAnimationSpeed(const float & speed);

	void setCurrentAnimation(const std::string& animName);

	float getInterpolation() const { return interpolation; }

	float getAnimationSpeed() const { return animSpeed;  }

	std::string getCurrentAnimation() const { return currentAnimation; }

 private:
	MD2Model m_model;
    float interpolation = 0.f;
	float animSpeed = 0.f;
    std::string currentAnimation = "stand";
};	