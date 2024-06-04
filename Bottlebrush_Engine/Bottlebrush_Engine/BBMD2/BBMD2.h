#pragma once

#include "MD2Model.h"

class BBMD2
{
public:
	BBMD2(const std::string & model_path, const std::string & texture_path);

	int getSpecificAnim(const std::string & animName);
	std::string getSpecificAnim(int animIndx);
	
	void setTexture() const;

	const std::vector<unsigned int>& getVecArrays() const { return m_model.returnVaos(); }
      
	const int getModelSize() const { return m_model.getNumTris(); }

	std::map<std::string, anim_md2>& getAnimations() { return m_model.getAnimations(); }

 private:
	MD2Model m_model;
};	
