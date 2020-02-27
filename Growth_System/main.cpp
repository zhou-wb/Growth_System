
#define _USE_MATH_DEFINES

#include "SurfaceGenerator.h"
#include "DiscreteParaCurve.h"
#include "glm/glm.hpp"


double raduis = 1;

glm::dvec3 func_line(double u)
{
	return(glm::dvec3(u, 0.f, 0.f));
}

glm::dvec3 func_circle(double u)
{
	return(glm::dvec3(glm::cos(u/raduis)*raduis, glm::sin(u/raduis)*raduis, 0.f));
}

int main()
{
	DiscreteParaCurve init_curve(func_circle, 0.f, 2.0f*raduis*M_PI);

	SurfaceGenerator surface(init_curve);

	for (unsigned int i = 0; i < 1000; i++)
	{
		//surface.growth_log_spiral();
		surface.growth_local_speed();
	}

	surface.create_obj_file();

}