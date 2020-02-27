#include "SurfaceGenerator.h"



SurfaceGenerator::SurfaceGenerator(DiscreteParaCurve init)
{
	surface.push_back(init);
}


SurfaceGenerator::~SurfaceGenerator()
{
}

glm::vec3 SurfaceGenerator::growth_dir(float u)
{
	return(glm::vec3(0.f, 0.f, 1.f));
}

float SurfaceGenerator::growth_length(float u)
{
	return(1.f);
}

void SurfaceGenerator::generate_grid()
{
	for (unsigned int i = 0; i < surface.size(); i++)
	{
		grid.push_back(surface[i].getPoints());
	}
}

void SurfaceGenerator::create_obj_file()
{
	generate_grid();
	ObjFile out_file(grid);
	out_file.export_obj_file();
}

void SurfaceGenerator::growth()
{
	DiscreteParaCurve curr_curve = surface.back();
	std::vector<float> coords_next_curve;
	std::vector<glm::vec3> points_next_curve;

	for (unsigned int i = 0; i < curr_curve.getPoints().size(); i++)
	{
		float curr_coord = curr_curve.getCoordinate(i);
		glm::vec3 curr_point = curr_curve.getPoint(i);

		glm::vec3 growth_vec = growth_dir(curr_coord) * growth_length(curr_coord);

		float next_coord = curr_coord;
		glm::vec3 next_point = curr_point + growth_vec;

		coords_next_curve.push_back(next_coord);
		points_next_curve.push_back(next_point);
	}

	DiscreteParaCurve next_curve(coords_next_curve, points_next_curve);
	surface.push_back(next_curve);
}

void SurfaceGenerator::growth_log_spiral()
{
	float alpha = -0.45f * 3.14159f;

	DiscreteParaCurve curr_curve = surface.back();
	std::vector<float> coords_next_curve;
	std::vector<glm::vec3> points_next_curve;

	for (unsigned int i = 0; i < curr_curve.getPoints().size(); i++)
	{
		float curr_coord = curr_curve.getCoordinate(i);
		glm::vec3 curr_point = curr_curve.getPoint(i);

		glm::vec2 op_xz(curr_point.x, curr_point.z);
		float distance = glm::length(op_xz);
		glm::mat2x2 rotate;
		rotate[0][0] = glm::cos(alpha);		rotate[0][1] = glm::sin(alpha) * -1.f;
		rotate[1][0] = glm::sin(alpha);		rotate[1][1] = glm::cos(alpha);
		glm::vec2 velocity_xz = glm::normalize(rotate * op_xz);

		glm::vec3 growth_vec = glm::vec3(velocity_xz.x, 0.f, velocity_xz.y) * 0.1f;

		float next_coord = curr_coord;
		glm::vec3 next_point = curr_point + growth_vec;

		coords_next_curve.push_back(next_coord);
		points_next_curve.push_back(next_point);

	}

	DiscreteParaCurve next_curve(coords_next_curve, points_next_curve);
	surface.push_back(next_curve);
}