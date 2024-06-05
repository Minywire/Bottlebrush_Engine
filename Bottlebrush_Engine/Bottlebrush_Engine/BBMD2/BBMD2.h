#pragma once

#include "MD2Model.h"

class BBMD2
{
public:
	BBMD2(const std::string & model_path, const std::string & texture_path);

	/**
	* @brief Fetches animation index from a name if it exists
	* @param animName The animation name for which to find the index
	* @return The integer index location of an animation
	*/
	int getSpecificAnim(const std::string & animName);

	/**
	* @brief Fetches animation name from a index if it exists
	* @param animIndx The animation index for which to find the name
	* @return The string name location of an animation
	*/
	std::string getSpecificAnim(int animIndx);
	
	/*
	* @brief Binds texture for an MD2 model
	*/
	void setTexture() const;

	/*
	* @return The container containing the Vertex Array Object for a frame
	*/
	const std::vector<unsigned int>& getVecArrays() const { return m_model.returnVaos(); }
    
	const int getModelSize() const { return m_model.getNumTris(); }

	std::map<std::string, anim_md2>& getAnimations() { return m_model.getAnimations(); }

 private:
	MD2Model m_model; ///The encapsulated MD2 model. Based on the specification from ICT397 Lab7
};	
