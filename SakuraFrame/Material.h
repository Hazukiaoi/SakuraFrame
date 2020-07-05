#pragma once

#include "Shader.h"
#include <string>
#include <map>
#include "Type.h"
#include "Texture.h"
#include "json.hpp"

namespace GameCore
{
	class Scene;
}

namespace Render
{

	class MaterialBoard
	{
	public:
		std::map<std::string, float> fValues;
		std::map<std::string, Texture*> tValues;
		std::map<std::string, Vector4> vValues;
	};

	using MaterialJsonDataParse = void(*)(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData);
	class Material
	{
	public:
		Shader* mShader;
		MaterialBoard* mMaterialBoard;
		std::string mName;
		int textureActive = 0;
		static std::map<std::string, MaterialJsonDataParse> MaterialParse;


		static void matJsonParseFloat(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData);
		static void matJsonParseVector(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData);
		static void matJsonParseTexture(GameCore::Scene& scene, Render::MaterialBoard& mb, const std::string propName, const nlohmann::json& jsonData);
		static void MaterialParseInit();

		Material();
		Material(Ref<Shader> shader);
		~Material();
		
		void LoadMaterialFromeJson(const std::string path, GameCore::Scene* scene);

		//≤Œ ˝…Ë÷√
		void SetTexture(const std::string& name, Texture t);
		void SetInt(const std::string& name, int i);
		void SetFloat(const std::string& name, float f);
		void SetVector3(const std::string& name, Vector3 vec3);
		void SetColor(const std::string& name, Color col);
		void SetBool(const std::string& name, bool b);
		void SetMatrix4x4(const std::string& name, glm::mat4 mat4);
	};


}