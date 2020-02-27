#pragma once

#include "DiscreteParaCurve.h"
#include "ObjFile.h"
#include "glm/glm.hpp"

class SurfaceGenerator
{
public:
	SurfaceGenerator(DiscreteParaCurve init);
	~SurfaceGenerator();

	void growth();
	void growth_log_spiral();
	void create_obj_file();

private:
	std::vector<DiscreteParaCurve> surface;	
	std::vector<std::vector<glm::vec3> > grid;
	
	glm::vec3 growth_dir(float u);
	float growth_length(float u);

	void generate_grid();
};