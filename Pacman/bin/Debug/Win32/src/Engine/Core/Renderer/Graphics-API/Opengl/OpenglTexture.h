#pragma once
#include <string>
#include "../Texture.h"

class OpenglTexture : public Texture
{
public:
	OpenglTexture(const char* Rsrc);
	virtual ~OpenglTexture() override;
	virtual void Bind() override;

private:
	void Load(const char* Rsrc);
    unsigned int TextureId;
};