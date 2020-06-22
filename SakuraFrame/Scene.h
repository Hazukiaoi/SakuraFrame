#pragma once

#include "ECS.h"
#include "Transform.h"
#include "Camera.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <map>

using json = nlohmann::json;
using namespace std;

typedef void (*SceneAddComponentFunc)(Entity& entity, json& jsonData);

static void scene_AddComponent_Transform(Entity& e, json& j)
{
	cout << "AddComponent: " << j["ComponentName"] << endl;

	Vector3		pos(j["Position"]["X"], j["Position"]["Y"], j["Position"]["Z"]);
	Quaternion	rot(j["Rotation"]["X"], j["Rotation"]["Y"], j["Rotation"]["Z"],  j["Rotation"]["W"]);
	Vector3		scale(j["Scale"]["X"],  j["Scale"]["Y"],    j["Scale"]["Z"]);

	e.AddComponent<Transform>(Transform{ pos, rot, scale });
}

static void scene_AddComponent_Camera(Entity& e, json& j)
{
	cout << "AddComponent: " << j["ComponentName"] << endl;

	e.AddComponent<Camera>
		(
			Camera
			{
				j["Size"],
				j["FOV"],
				j["FarPlane"],
				j["NearPlane"],
				j["Aspect"],
				j["Layer"]
			}
		);


}

static void scene_AddComponent_Light(Entity& e, json& j)
{
	cout << "Light" << " | " << j["Intensity"] << " | " << j["Color"]["G"] << endl;
}

static void scene_AddComponent_MeshFilter(Entity& e, json& j)
{
	cout << j["ComponentName"] << endl;

}

static void scene_AddComponent_MeshRenderer(Entity& e, json& j)
{
	cout << j["ComponentName"] << endl;

}

static map<string, SceneAddComponentFunc> AddComponent;


class Scene
{
	ECSManager *ecsManager;
	
public:
	

	void InitAddComponentMap()
	{
		AddComponent["Transform"] = scene_AddComponent_Transform;
		AddComponent["Camera"] = scene_AddComponent_Camera;
		AddComponent["Light"] = scene_AddComponent_Light;
		AddComponent["MeshFilter"] = scene_AddComponent_MeshFilter;
		AddComponent["MeshRenderer"] = scene_AddComponent_MeshRenderer;
	}

	Scene()
	{
		ecsManager = new ECSManager();
		InitAddComponentMap();
	}

	void LoadScene(const char* path)
	{
        ifstream sceneJson;
		sceneJson.open(path);
        assert(sceneJson.is_open());
        string s;
        while (getline(sceneJson, s)) {}
		sceneJson.close();

        auto o = json::parse(s);

        for (auto& obj : o)
        {
			auto& entity = ecsManager->AddEntity();
			entity.name = obj["Name"];
			cout << "New Entity: " << entity.name << endl;
			for (auto& c : obj["Components"])
			{
				AddComponent[c["ComponentName"]](entity, c);
			}
        }
	}
	~Scene()
	{
		
	}

private:

};