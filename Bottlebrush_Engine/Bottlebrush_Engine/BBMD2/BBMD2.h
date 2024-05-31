#pragma once

#include "MD2Model.h"

class BBMD2
{
public:
	BBMD2(std::string model_path, std::string texture_path);

	int getSpecificAnim(std::string animName);
	std::string getSpecificAnim(int animIndx);

	int getAnimationCurrentFrame(int AnimIndx, float interpolation);
	
	void setTexture() const;

	const std::vector<unsigned int>& getVecArrays() const { return m_model.returnVaos(); }
      
	const int getModelSize() const { return m_model.getNumTris(); }

	void updateInterpolation(float deltaTime);

 private:
	MD2Model m_model;
    float interpolation = 0.f;
};	