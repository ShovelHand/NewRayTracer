#include "Sphere.h"



Sphere::Sphere(vec3 pos, float rad, Colour colour, float gloss)
	:m_vPos(pos)
	, m_fRadius(rad)
	, m_cColour(colour)
	, m_iGloss(gloss)
{
	BuildBoundingBox();
}

Sphere::~Sphere()
{
}

void Sphere::BuildBoundingBox()
{
	float r = m_fRadius + 0.275f; //bounds checking had bad misses when bounding box was tangent to sphere
	bounds[0] = vec3(m_vPos.x() - r, m_vPos.y() - r, m_vPos.z() + r);
	bounds[1] = vec3(m_vPos.x() + r, m_vPos.y() + r, m_vPos.z() - r);
}

//Check to see if a ray passes through a sphere's bounding box before doing more expensive ray/sphere intersection test.
//See http://www.cs.utah.edu/~awilliam/box/box.pdf
bool Sphere::CheckBoundsIntersection(vec3 o, vec3 r, float t0, float t1)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (r.x() >= 0) {
		tmin = (bounds[0].x() - o.x()) / r.x();
		tmax = (bounds[1].x() - o.x()) / r.x();
	}
	else {
		tmin = (bounds[1].x() - o.x()) / r.x();
		tmax = (bounds[0].x() - o.x()) / r.x();
	}
	if (r.y() >= 0) {
		tymin = (bounds[0].y() - o.y()) / r.y();
		tymax = (bounds[1].y() - o.y()) / r.y();
	}
	else {
		tymin = (bounds[1].y() - o.y()) / r.y();
		tymax = (bounds[0].y() - o.y()) / r.y();
	}
	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	if (r.z() >= 0) {
		tzmin = (bounds[0].z() - o.z()) / r.z();
		tzmax = (bounds[1].z() - o.z()) / r.z();
	}
	else {
		tzmin = (bounds[1].z() - o.z()) / r.z();
		tzmax = (bounds[0].z() - o.z()) / r.z();
	}
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	return ((tmin < t1) && (tmax > t0));
}


/*For debugging*/
void Sphere::ReportPlanes(vec3 o, vec3 r) {
	//cout << "vmin: " << bounds[0] << " vmax: " << bounds[1] << endl;
	float tx0 = vec3(-1.0f, 0.0f, 0.0f).dot(bounds[0] - o) / (vec3(-1.0f, 0.0f, 0.0f).dot(r));
	float tx1 = vec3(1.0f, 0.0f, 0.0f).dot(bounds[1] - o) / (vec3(1.0f, 0.0f, 0.0f).dot(r));

	float tz0 = vec3(0.0f, 0.0f, -1.0f).dot(bounds[0] - o) / (vec3(0.0f, 0.0f, -1.0f).dot(r));
	float tz1 = vec3(0.0f, 0.0f, 1.0f).dot(bounds[1] - o) / (vec3(0.0f, 0.0f, 1.0f).dot(r));

	float ty0 = vec3(0.0f, -1.0f, 0.0f).dot(bounds[0] - o) / (vec3(0.0f, -1.0f, 0.0f).dot(r));
	float ty1 = vec3(0.0f, 1.0f, 0.0f).dot(bounds[1] - o) / (vec3(0.0f, 1.0f, 0.0f).dot(r));
	cout << "Plane distances: \nxLeft: " << tx0 << " xRight: " << tx1 << " zNear: " << tz1 << " zFar: " << tz0 << " yLow: " << ty0 << " yHigh: " << ty1 << endl;
}

