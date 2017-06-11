#pragma once
#include "common.h"
#include "main.h"
#include <time.h>

/*Place Spheres and light sources*/
void BuildScene() 
{
	Sphere sphere1(vec3(0.85f, -1.0f, 1.0f), 0.25f, Colour(255, 0, 0), 50);
	Spheres.push_back(sphere1);
	
	Sphere sphere4(vec3(-0.4f, -0.75f, 0.5f), 0.04f, Colour(150, 0, 150), 10000);
	Spheres.push_back(sphere4);
	Sphere sphere5(vec3(-0.5f, -1.0f, 0.5f), 0.4f, Colour(150, 155, 150), 10000);
	Spheres.push_back(sphere5);

	LightSource light1(vec3(-0.5f, -1.7f, 1.75f), Colour(150, 150, 150), 10);
	LightSources.push_back(&light1);
}

/*cast a ray*/
vec3 castRay(vec3 o, vec3 d)
{
	vec3 ray(d.x() - o.x(), d.y() - o.y(), d.z() - o.z());
	ray.normalize();
	raysCast += 1;
	return ray;
}

/*Ray tracing happens here*/
void ScanImage()
{
	cout << "Ray tracing scene. This may take a while..." << endl;
	clock_t timeStart = clock();
	vec3 eye(0.0f, 0.0f, -2.0);  //if we assume image pane has origin at 0,0,0, then eye is 10 units in front of it, and 'd' = 10
	float dist = eye.z();

	//finding pixel coords
	float left, right, top, bottom;
	left = -(float(image.cols) / float(image.rows));
	bottom = -1;
	top = 1;
	right = (float(image.cols) / float(image.rows));

	for (int row = 0; row < image.rows; ++row) {
		for (int col = 0; col < image.cols; ++col) {
			//construct ray
			float u = (left + (right - left)*(col + 0.5) / image.cols);
			float v = (bottom + (top - bottom)*(row + 0.5) / image.rows);

			vec3 d(u, v, 0);
			vec3 r = castRay(eye, d);
			float tmin = 1000;//arbitrarily large instantiation for infinity.
			float t;
			bool intersection = false;
			
			/******GROUND DRAWING*********/
			//check for ground plane intersection
			vec3 p0(0, 1, 2);
			vec3 n(0, 1, 0); //normal vector to plane on the x-z plane
			Colour groundColour(50, 50, 50);

			if (r.dot(n) != 0 && row >= image.rows / 2) //the inequality is here until I can figure out why the plane appears in the sky.
			{

				t = ((p0 - eye).dot(n)) / r.dot(n);

				tmin = t;

				intersection = true;
				Colour colour(100, 100, 100);  //only one ground, so its colour is declared here
				vec3 p(eye.x() + t*r.x(), eye.y() + t*r.y(), eye.z() + t*r.z()); //point of intersection
				//TODO: lighting calculations go here.

				image(row, col) = colour;
			}
			/******END OF GROUND DRAWING******/

			//draw spheres
				for (std::vector<Sphere>::iterator itr = Spheres.begin(); itr != Spheres.end(); ++itr)
				{
					if ((*itr).CheckBoundsIntersection(eye, r))
					{
						boundingBoxHits += 1;
						float b = (r.dot(eye - (*itr).GetPos()));
						float c = (eye - (*itr).GetPos()).dot(eye - (*itr).GetPos()) - pow((*itr).GetRad(), 2);
						float discriminant = sqrt(pow(b, 2) - c);
						if (discriminant >= 0) //don't waste computation time if no intersection
						{
							t = fmin(((-1)*b - discriminant), ((-1)*b + discriminant));
							intersection = true;
							sphereIntersections += 1;
							if (t < tmin)
							{
								vec3 p(eye.x() + t*r.x(), eye.y() + t*r.y(), eye.z() + t*r.z());
								tmin = t;
								image(row, col) = (itr)->GetColour();
							}
						}
					}

				
				}
			
			//just draw black if ray hit nothing
			if (!intersection)
			{
				image(row, col) = Colour(0, 0, 0);
			}

		}
	}//end of scan loop

	clock_t timeEnd = clock();
	cout << "Render time: " << float(timeEnd - timeStart)/1000.0f << " seconds" << endl;
	cout << "Rays cast: " << raysCast << endl;
	cout << "Rays that hit spheres: " << sphereIntersections << endl;
	cout << "Bounding box hits: " << boundingBoxHits << endl;
}

int main()
{
	raysCast = sphereIntersections = boundingBoxHits = 0;
	BuildScene();
	ScanImage();
	image.show();
	// image.save("output.png"); ///< Does not work on Windows!
 
	return EXIT_SUCCESS;
}