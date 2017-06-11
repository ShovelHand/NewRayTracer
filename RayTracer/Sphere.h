#pragma once
#include "common.h"

typedef cv::Vec3b Colour;

typedef Eigen::Vector2f vec2;
typedef Eigen::Vector3f vec3;
struct Bounds {
	float xLeft, xRight, yTop, yBottom, zFront, zBack;
};

class Sphere
{
public:
	Sphere(vec3 pos, float rad, Colour colour, int gloss);
	~Sphere();

	vec3 GetPos() { return m_vPos; }
	float GetRad() { return m_fRadius; }
	Colour GetColour() { return m_cColour; }
	int GetGloss() { return m_iGloss; }
	//Bounds GetBoundingBox() { return bounds; }
	bool CheckBoundsIntersection(vec3 o, vec3 r);


private:
	//enum plane {
	//	xLeft, xRight, yTop, yBottom, zNear, zFar
	//};

	vec3 bounds[2];

	//Bounds BuildVolumes(vec3 pos, float rad);
	void BuildBoundingBox();
	//Bounds bounds;

	float m_fRadius;
	vec3 m_vPos;
	Colour m_cColour;
	int m_iGloss;

};

