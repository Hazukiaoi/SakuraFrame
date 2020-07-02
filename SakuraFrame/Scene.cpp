//#include "Scene.h"
//
//
//Scene::Scene()
//{
//	ecsManager = new ECSManager();
//	InitAddComponentMap();
//}
//
//void Scene::LoadAssetsInfo(string asInfoName)
//{
//	ifstream assetJson;
//	ostringstream m_path;
//	m_path << assetPath << asInfoName;
//	assetJson.open(m_path.str());
//	assert(assetJson.is_open());
//	string s;
//	while (getline(assetJson, s)) {}
//	assetJson.close();
//
//	auto o = json::parse(s);
//	for (auto& obj : o)
//	{
//		assetInfo.emplace(obj["Name"], obj["Path"]);
//	}
//}
//
//void Scene::LoadScene(string path, string sceneName, string assetInfoName)
//{
//	assetPath = path;
//
//	LoadAssetsInfo(assetInfoName);
//
//	ifstream sceneJson;
//	ostringstream m_path;
//	m_path << path << sceneName;
//	sceneJson.open(m_path.str());
//	assert(sceneJson.is_open());
//	string s;
//	while (getline(sceneJson, s)) {}
//	sceneJson.close();
//
//	auto o = json::parse(s);
//
//	for (auto& obj : o)
//	{
//		auto& entity = ecsManager->AddEntity();
//		entity.name = obj["Name"];
//		cout << "New Entity: " << entity.name << endl;
//		for (auto& c : obj["Components"])
//		{
//			AddComponent[c["ComponentName"]](entity, c, *this);
//		}
//	}
//}
//
//void Scene::InitAddComponentMap()
//{
//	AddComponent["Transform"] = scene_AddComponent_Transform;
//	AddComponent["Camera"] = scene_AddComponent_Camera;
//	AddComponent["Light"] = scene_AddComponent_Light;
//	AddComponent["MeshFilter"] = scene_AddComponent_MeshFilter;
//	AddComponent["MeshRenderer"] = scene_AddComponent_MeshRenderer;
//}
//
//void  Scene::scene_AddComponent_Transform(Entity& e, json& j, Scene& scene)
//{
//	cout << "AddComponent: " << j["ComponentName"] << endl;
//
//	Vector3		pos(j["Position"]["X"], j["Position"]["Y"], j["Position"]["Z"]);
//	Quaternion	rot(j["Rotation"]["X"], j["Rotation"]["Y"], j["Rotation"]["Z"], j["Rotation"]["W"]);
//	Vector3		scale(j["Scale"]["X"], j["Scale"]["Y"], j["Scale"]["Z"]);
//
//	//em.FindEntity<int>([](Entity* ent, int id) {return (ent->instanceID == id); }, 123);
//	auto& t = e.AddComponent<Transform>(Transform{ pos, rot, scale });
//
//	//如果有父对象则设置父对象
//	string		parent = j["Parent"];
//	if (parent != "NULL")
//	{
//		int id = stoi(parent);
//		auto fe = find_if(scene.ecsManager->entities.begin(), scene.ecsManager->entities.end(), [&](std::unique_ptr<Entity>& e) {return e->instanceID == id; });
//		if (fe != scene.ecsManager->entities.end())
//			t.parent = fe->get()->GetComponent<Transform>();
//	}
//}
//
//void  Scene::scene_AddComponent_Camera(Entity& e, json& j, Scene& scene)
//{
//	cout << "AddComponent: " << j["ComponentName"] << endl;
//
//	e.AddComponent<Camera>
//		(
//			Camera
//			{
//				j["Size"],
//				j["FOV"],
//				j["FarPlane"],
//				j["NearPlane"],
//				j["Aspect"],
//				j["Layer"]
//			}
//	);
//}
//
//void  Scene::scene_AddComponent_Light(Entity& e, json& j, Scene& scene)
//{
//	Color c;
//	c.r = j["Color"]["R"];
//	c.g = j["Color"]["G"];
//	c.b = j["Color"]["B"];
//	c.a = j["Color"]["A"];
//	e.AddComponent<Light>
//		(
//			Light
//			{
//				j["Intensity"],
//				j["Range"],
//				(int)j["LightType"],
//				Color(j["Color"]["R"], j["Color"]["G"], j["Color"]["B"],j["Color"]["A"])
//			}
//	);
//	//cout << "Light" << " | " << j["Intensity"] << " | " << j["Color"]["G"] << endl;
//}
//
//void  Scene::scene_AddComponent_MeshFilter(Entity& e, json& j, Scene& scene)
//{
//	//加载的时候从列表进行索引，如果网格未被初始化，就从字段中加载网格
//	int meshID = j["Name"];
//	//如果网格本身不存在，则创建新的网格
//	if (scene.meshs.count(meshID) == 0)
//	{
//		Mesh* m = new Mesh();
//		ostringstream oss;
//		oss << scene.assetPath << scene.assetInfo[meshID];
//		m->LoadMesh(oss.str().c_str());
//		scene.meshs.emplace(meshID, m);
//	}
//
//	auto& m = e.AddComponent<MeshFilter>();
//	m.mesh = scene.meshs[meshID];
//
//	cout << j["ComponentName"] << endl;
//}
//
//void  Scene::scene_AddComponent_MeshRenderer(Entity& e, json& j, Scene& scene)
//{
//	//创建加载材质和加载贴图
//	int matID = j["Name"];
//
//	if (scene.meshs.count(matID) == 0)
//	{
//		Material* m = new Material();
//	}
//
//
//	cout << j["ComponentName"] << endl;
//}