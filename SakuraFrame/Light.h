#pragma once

#include "ECS.h"
#include "Type.h"

enum class LightType
{
	LIGHT_DIRECTTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

class Light : public Component
{

public:
	float intensity;
	float range;
	LightType type;
	Color color;

	Light()
	{
		intensity = 1.0f;
		range = 10.f;
		type = LightType::LIGHT_DIRECTTIONAL;
		color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	~Light()
	{
		cout << "Light Destroy" << endl;
	}
};