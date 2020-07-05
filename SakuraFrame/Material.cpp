#include "Material.h"
#include "Scene.h"


using Render::Material;
//namespace GameCore
//{
//	class Scene;
//}
std::map<std::string, Render::MaterialJsonDataParse> Render::Material::MaterialParse;

void Render::Material::MaterialParseInit()
{
	MaterialParse.emplace("Range", matJsonParseFloat);
	MaterialParse.emplace("Float", matJsonParseFloat);
	MaterialParse.emplace("Texture", matJsonParseTexture);
	MaterialParse.emplace("Color", matJsonParseVector);
	MaterialParse.emplace("Vector", matJsonParseVector);
}

void Material::LoadMaterialFromeJson(const std::string path, GameCore::Scene* scene)
{
	ifstream assetJson;
	ostringstream m_path;
	m_path << scene->assetPath << path;
	assetJson.open(m_path.str());
	assert(assetJson.is_open());
	string s;
	while (getline(assetJson, s)) {}
	assetJson.close();


	Render::MaterialBoard *mb = new Render::MaterialBoard();
	auto o = nlohmann::json::parse(s);
	for (auto& obj : o.items())
	{
		string key = obj.key();
		if (key == "Name")
		{
			mName = obj.value();
		}
		else
		{
			auto& type = obj.value();

			Render::Material::MaterialParse[type["Type"]](*scene, *mb, key, type);
		}
		
	}

}

void Render::Material::matJsonParseFloat(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData)
{
	mb.fValues.emplace(propName, (float)jsonData["Value"]);
	//std::cout << propName << " | "  << " Load " << std::endl;
}
void Render::Material::matJsonParseVector(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData)
{
	Vector4 _v(jsonData["Value"][0], jsonData["Value"][1], jsonData["Value"][2], jsonData["Value"][3]);
	mb.vValues.emplace(propName, _v);
	//std::cout << propName << " | " << " Load " << std::endl;
}
void Render::Material::matJsonParseTexture(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData)
{
	string nullStr = "\"NULL\"";
	ostringstream ossValue;
	ossValue << jsonData["Value"];
	string _v = ossValue.str();
	std::cout << propName << " | " << (strcmp(_v.c_str(), nullStr.c_str()) == 0) << std::endl;

	Vector4 texST(0, 0, 0, 0);
	//ÅÐ¶ÏÊÇ·ñÎªnull
	if (strcmp(_v.c_str(), nullStr.c_str()) != 0)
	{
		int _iV = stoi(_v);	
		if (scene.textures.count(_iV) == 0)
		{
			ostringstream oss;
			oss << scene.assetPath << scene.assetInfo[_iV];

			Texture2D _t(oss.str().c_str());
			scene.textures.emplace(_iV, &_t);
		}
		mb.tValues.emplace(_v, scene.textures[_iV]);
		texST.x = jsonData["TextureInfo"][0];
		texST.y = jsonData["TextureInfo"][1];
		texST.z = jsonData["TextureInfo"][2];
		texST.w = jsonData["TextureInfo"][3];
	}
	else
	{
		mb.tValues.emplace(_v, nullptr);
	}
	mb.vValues.emplace(propName + "_ST", texST);
}


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
