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
		//��ȡ���ݲ�����ʵ��
		

		fs.close();

	}
	~Scene(){}

private:

};