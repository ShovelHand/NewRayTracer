#include "Sphere.h"



Sphere::Sphere(vec3 pos, float rad, Colour colour, int gloss)
	:m_vPos(pos)
	, m_fRadius(rad)
	, m_cColour(colour)
	, m_iGloss(gloss)
{
//	bounds = BuildVolumes(m_vPos, m_fRadius);
}

Sphere::~Sphere()
{
}

void Sphere::BuildBoundingBox()
{
	bounds[0] = m_vPos - (vec3(1.0f, 1.0f, 1.0f) * m_fRadius);
	bounds[1] = m_vPos + (vec3(1.0f, 1.0f, 1.0f) * m_fRadius);
}

bool Sphere::CheckBoundsIntersection(vec3 o, vec3 r)
{
	/*o.normalize();
	r.normalize();*/
	float t0x = (bounds[0].x() - o.x()) / r.x();
	float t1x = (bounds[1].x() - o.x()) / r.x();
	
	float tmin = min(t0x, t1x);
	float tmax = max(t0x, t1x);

	//float t0y = (bounds[0].y() - o.y()) / r.y();
	//float t1y = (bounds[1].y() - o.y()) / r.y();

	//tmin = max(tmin, min(t0y, t1y));
	//tmax = min(tmax, max(t0y, t1y));

	//float t0z = (bounds[0].z() - o.z()) / r.z();
	//float t1z = (bounds[1].z() - o.z()) / r.z();

	//tmin = max(tmin, min(t0z, t1z));
	//tmax = min(tmax, max(t0z, t1z));

	return tmax >= tmin;

	//float t0z = (bounds[0].z() - o.z()) / r.z();
	//float t1z = (bounds[1].z() - o.z()) / r.z();

	//float tmin = (t0x > t0y) ? t0x : t0y;
	//float tmax = (t1x < t1y) ? t1x : t1y;

	//if (tmin > t1z || t0z > tmax)
	//	return false;
	//if (t0z > tmin)
	//	tmin = t0z;
	//if (t1z < tmax)
	//	tmax = t1z;
	//
	//
	//return true;
}
//not sure if I'll keep this.
//Bounds Sphere::BuildVolumes(vec3 pos, float m_fRadius)
//{
//	Bounds bound;
//	bound.xLeft = pos.x() - m_fRadius;
//	bound.xRight = pos.x() + m_fRadius;
//	bound.yTop = pos.y() - m_fRadius;
//	bound.yBottom = pos.y() + m_fRadius;
//	bound.zFront = pos.z() - m_fRadius;
//	bound.zBack = pos.z() + m_fRadius;
//	return bound;
//}
