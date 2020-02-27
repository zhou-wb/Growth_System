#include "SurfaceGenerator.h"
#include "DiscreteParaCurve.h"
#include "glm/glm.hpp"

glm::vec3 func_line(float u)
{
	return(glm::vec3(u, 0.f, 0.f));
}

glm::vec3 func_circle(float u)
{
	return(glm::vec3(glm::cos(u)*0.5f + 1.f, glm::sin(u)*0.5f, 0.f));
}

int main()
{
	DiscreteParaCurve init_curve(func_circle, 0.f, 2.f*3.14159f);

	SurfaceGenerator surface(init_curve);

	for (unsigned int i = 0; i < 300; i++)
	{
		surface.growth_log_spiral();
	}

	surface.create_obj_file();

}