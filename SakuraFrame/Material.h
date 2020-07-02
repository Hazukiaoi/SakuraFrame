#pragma once

#include "Shader.h"
#include <string>
#include <map>
#include "Type.h"
#include "Texture.h"
//#include "Scene.h"

class MaterialBoard
{
	map<string, float> fValues;
	map<string, Texture*> tValues;
	map<string, Vector4> vValues;
};

class Material
{
public:
	Shader* mShader;
	MaterialBoard* mMaterialBoard;
	int textureActive = 0;

	Material();
	Material(Ref<Shader> shader);
	~Material();

	//void LoadMaterialFromeJson(string path, Scene& scene)
	//{

	//}

//≤Œ ˝…Ë÷√
	void SetTexture(const std::string& name, Texture t);
	void SetInt(const std::string& name, int i);
	void SetFloat(const std::string& name, float f);
	void SetVector3(const std::string& name, Vector3 vec3);
	void SetColor(const std::string& name, Color col);
	void SetBool(const std::string& name, bool b);
	void SetMatrix4x4(const std::string& name, glm::mat4 mat4);
};

Material::Material()
{
	mShader = nullptr;
}

Material::Material(Ref<Shader> shader)
{
	mShader = shader.get();
}

Material::~Material()
{
	mShader = nullptr;
}


void Material::SetTexture(const std::string& name, Texture t)
{
	mShader->SetTexture(name.c_str(), t);
}

void Material::SetInt(const std::string& name, int i)
{
	mShader->SetInt(name.c_str(), i);
}

void Material::SetFloat(const std::string& name, float f)
{
	mShader->SetFloat(name.c_str(), f);
}

void Material::SetVector3(const std::string& name, Vector3 vec3)
{
	mShader->SetVector3(name.c_str(), vec3);
}

void Material::SetColor(const std::string& name, Color col)
{
	mShader->SetColor(name.c_str(), col);
}

void Material::SetBool(const std::string& name, bool b)
{
	mShader->SetBool(name.c_str(), b);
}

void Material::SetMatrix4x4(const std::string& name, glm::mat4 mat4)
{
	mShader->SetMatrix4x4(name.c_str(), mat4);
}