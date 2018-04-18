#include "PixelArtist.h"



PixelArtist::PixelArtist()
{
}


PixelArtist::~PixelArtist()
{
}

/*a duplicate of main's CastRay because the compiler doesn't like it in common.h*/
vec3 PixelArtist::ArtistRay(vec3 o, vec3 d) 
{
	vec3 ray(d.x() - o.x(), d.y() - o.y(), d.z() - o.z());
	ray.normalize();
	return ray;
}

/*Compute lighting influence on surface colour
Parameters are starting colour, and normal of the vector of the surface.*/
Colour PixelArtist::AddLight(Colour colour, vec3 n, vec3 p, float gloss)
{
	colour /= 5; //This gives us an ambient light level of 1/5 of the objects brightness instead of having black shadows

	for (std::vector<LightSource*>::iterator itr = LightSources.begin(); itr != LightSources.end(); ++itr)
	{
		vec3 l = (*itr)->GetPos()- p; l.normalize();  //l and n make up lambertian shading component
		n.normalize();
		vec3 view = v - p; view.normalize();
		vec3 h = (view + l); h.normalize();  //h needed for blinn-phong shading, specular highlights
		
		bool inShadow = false;
		
		//cast a ray following the normal of the intersection point. Check for other influences on colour
		vec3 ShadowRay = ArtistRay(p, l); // (l.x() - p.x(), l.y() - p.y(), l.z() - p.z());
		ShadowRay.normalize();

		//check and see if this point is in the shadow of another object closer to the light
		//TODO: This will probably be where recursive ray checking (for reflections, shadows, everything) ends up going.
		for (std::vector<Sphere*>::iterator itr = Spheres.begin(); itr != Spheres.end(); ++itr)
		{
		//	if ((*itr)->CheckBoundsIntersection(p, n, -10.0f, 10.0f))
			{
				float b = (ShadowRay.dot(p - (*itr)->GetPos() ));
				float c = (p - (*itr)->GetPos()).dot(p - (*itr)->GetPos()) - pow((*itr)->GetRad(), 2);
				float discriminant = sqrt(pow(b, 2) - c);
				if (discriminant >= 0) //don't waste computation time if no intersection
				{
					float t = fmin(((-1)*b - discriminant), ((-1)*b + discriminant));
					if(t > 0.0001f) //a check against self intersection
						inShadow = true;
				}
			}

		}

		if (!inShadow) 
		{
			Colour specularColour = Colour(155, 155, 155);
			colour += colour * ((*itr)->GetI() * fmax(0, n.dot(l))); 
			colour += specularColour*((*itr)->GetI()*powf(fmax(0.0f, n.dot(h)), gloss));
		}
	}
	
	return colour;
}

//p is xyz point of intersection with ground surface
Colour PixelArtist::DrawGroundPixel(vec3 p)
{
	return(AddLight(Colour(100, 100, 100), vec3(0, -1, 0), p, 100.0f));
}

//p is point on surface where ray hit sphere.
Colour PixelArtist::DrawSpherePixel(Sphere* sphere, vec3 p)
{
	//get normal. It's just p minus the sphere's origin. 
	vec3 n = p - sphere->GetPos();
	return AddLight(sphere->GetColour(), n, p, sphere->GetGloss());
}