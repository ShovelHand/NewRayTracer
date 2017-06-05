#pragma once
#include "common.h"

typedef cv::Vec3b Colour;

typedef Eigen::Vector2f vec2;
typedef Eigen::Vector3f vec3;

class LightSource
{
public:
	LightSource(vec3 pos, Colour colour, float intensity);
	~LightSource();

	vec3 GetPos() { return m_vPos; }
	Colour GetColour() { return m_cColour; }
	float GetI() { return m_fI; }

private:
	vec3 m_vPos;
	Colour m_cColour;
	float m_fI; //light intensity

};

