#pragma once

class Texture
{
protected:
	
public:
	virtual ~Texture() = 0;

	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;

	virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};
