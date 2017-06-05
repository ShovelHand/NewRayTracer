#pragma once
#include "common.h"

typedef cv::Vec3b Colour;

typedef Eigen::Vector2f vec2;
typedef Eigen::Vector3f vec3;

class Sphere
{
public:
	Sphere(vec3 pos, float rad, Colour colour, int gloss);
	~Sphere();

	vec3 GetPos() { return m_vPos; }
	float GetRad() { return m_fRadius; }
	Colour GetColour() { return m_cColour; }
	int GetGloss() { return m_iGloss; }


private:
	float m_fRadius;
	vec3 m_vPos;
	Colour m_cColour;
	int m_iGloss;

};

