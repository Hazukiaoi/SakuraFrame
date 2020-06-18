#pragma once

#include "ECS.h"
#include <iostream>
#include <fstream>

using namespace std;
class Scene
{
	ECSManager *ecsManager;
public:
	Scene()
	{
		ecsManager = new ECSManager();
	}

	void LoadScene(const char* path)
	{
		fstream fs(path, ios::in | ios::binary);
		//读取数据并创建实体
		

		fs.close();

	}
	~Scene(){}

private:

};