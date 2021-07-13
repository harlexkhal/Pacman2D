#pragma once
#include "../Shader.h"

class OpenglShader : public Shader
{
public:
	OpenglShader(const char* ShadersFilePath);
	virtual ~OpenglShader() override;
	virtual void Use() override;

	virtual void SetBool(const char* String, bool Value)const override;
	virtual void SetInt(const char* String, int Value)const override;
	virtual void SetFloat(const char* String, float Value)const override;
	virtual void SetFloat2(const char* String, float x, float y)const override;
	virtual void SetFloat3(const char* String, float x, float y, float z)const override;
	virtual void SetFloat4(const char* String, float x, float y, float z, float a)const override;
	virtual void SetMat4FLoatV(const char* String, float* Matindex0)const override;

private:
	void Load(const char* ShadersFilePath);
	unsigned int Program;
};