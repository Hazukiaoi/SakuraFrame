#pragma once

#include "Shader.h"

struct Material
{
public:
	Shader* mShader;

	Material() 
	{
		mShader = nullptr;
	}

	Material(Ref<Shader> shader)
	{
		mShader = shader.get();
	}

	~Material()
	{
		mShader = nullptr;
	}

private:
	int textureActive = 0;

//²ÎÊýÉèÖÃ
	void SetTexture(const std::string& name, Texture t)
	{
		mShader->SetTexture(name.c_str(), t);
	}

	void SetInt(const std::string& name, int i)
	{
		mShader->SetInt(name.c_str(), i);
	}

	void SetFloat(const std::string& name, float f)
	{
		mShader->SetFloat(name.c_str(), f);
	}

	void SetVector3(const std::string& name, Vector3 vec3)
	{
		mShader->SetVector3(name.c_str(), vec3);
	}

	void SetColor(const std::string& name, Color col)
	{
		mShader->SetColor(name.c_str(), col);
	}

	void SetBool(const std::string& name, bool b)
	{
		mShader->SetBool(name.c_str(), b);
	}

	void SetMatrix4x4(const std::string& name, glm::mat4 mat4)
	{
		mShader->SetMatrix4x4(name.c_str(), mat4);
	}
};