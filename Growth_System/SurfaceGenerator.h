#pragma once

#include "DiscreteParaCurve.h"
#include "ObjFile.h"
#include "glm/glm.hpp"
#include "CoordinateSystem.h"

class SurfaceGenerator
{
public:
	SurfaceGenerator(DiscreteParaCurve init);
	~SurfaceGenerator();

	void growth();
	void growth_log_spiral();
	void growth_local_speed();
	void create_obj_file();


private:
	std::vector<DiscreteParaCurve> surface;	
	std::vector<std::vector<glm::dvec3> > grid;
	
	glm::dvec3 growth_dir(double u);
	double growth_length(double u);

	void generate_grid();

	CoordinateSystem get_Frenet_frame(int curve_index, int point_index);
};