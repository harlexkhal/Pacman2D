#pragma once

class Shader
{
public:
	Shader() {};
	virtual ~Shader() {};
	virtual void Use() = 0;

	virtual void SetBool(const char* String, bool Value) const = 0;
	virtual void SetInt(const char* String, int Value) const = 0;
	virtual void SetFloat(const char* String, float Value) const = 0;
	virtual void SetFloat2(const char* String, float x, float y) const = 0;
	virtual void SetFloat3(const char* String, float x, float y, float z) const = 0;
	virtual void SetFloat4(const char* String, float x, float y, float z, float a) const = 0;
	virtual void SetMat4FLoatV(const char* String, float* Matindex0) const = 0;
};