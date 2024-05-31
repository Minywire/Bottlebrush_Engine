#pragma once

#include "MD2Model.h"

class BBMD2
{
public:
	BBMD2(std::string model_path, std::string texture_path);

	int getSpecificAnim(std::string animName);
	std::string getSpecificAnim(int animIndx);

	int getAnimationCurrentFrame(int AnimIndx, float interpolation);

	const MD2Model & returnMD2() const;

	const std::vector<unsigned int> & getVecArrays() const;

 private:
	MD2Model m_model;
};	