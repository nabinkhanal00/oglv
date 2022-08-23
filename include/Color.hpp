#pragma once
struct Color
{
	float r;
	float g;
	float b;
	float a;
	Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	Color()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}
};
