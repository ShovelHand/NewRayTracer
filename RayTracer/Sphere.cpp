#include "Sphere.h"



Sphere::Sphere(vec3 pos, float rad, Colour colour, int gloss)
	:m_vPos(pos)
	, m_fRadius(rad)
	, m_cColour(colour)
	, m_iGloss(gloss)
{

}


Sphere::~Sphere()
{
}
