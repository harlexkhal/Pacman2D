#pragma once

class Texture
{
public:
	Texture() {};
	virtual ~Texture() {};
	virtual void Bind() = 0;
};