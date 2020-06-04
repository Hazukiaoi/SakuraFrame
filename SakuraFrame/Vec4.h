#pragma once

struct Vec4
{
public:
	union 
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
	};
};

typedef Vec4 Color