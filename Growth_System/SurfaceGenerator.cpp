#include "SurfaceGenerator.h"



SurfaceGenerator::SurfaceGenerator(DiscreteParaCurve init)
{
	surface.push_back(init);
}


SurfaceGenerator::~SurfaceGenerator()
{
}

glm::dvec3 SurfaceGenerator::growth_dir(double u)
{
	return(glm::dvec3(0.f, 0.f, 1.f));
}

double SurfaceGenerator::growth_length(double u)
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
	std::vector<double> coords_next_curve;
	std::vector<glm::dvec3> points_next_curve;

	for (unsigned int i = 0; i < curr_curve.getPoints().size(); i++)
	{
		double curr_coord = curr_curve.getCoordinate(i);
		glm::dvec3 curr_point = curr_curve.getPoint(i);

		glm::dvec3 growth_vec = growth_dir(curr_coord) * growth_length(curr_coord);

		double next_coord = curr_coord;
		glm::dvec3 next_point = curr_point + growth_vec;

		coords_next_curve.push_back(next_coord);
		points_next_curve.push_back(next_point);
	}

	DiscreteParaCurve next_curve(coords_next_curve, points_next_curve);
	surface.push_back(next_curve);
}

void SurfaceGenerator::growth_local_speed()
{
	DiscreteParaCurve curr_curve = surface.back();
	std::vector<double> coords_next_curve;
	std::vector<glm::dvec3> points_next_curve;

	for (unsigned int i = 0; i < curr_curve.getPoints().size(); i++)
	{
		double curr_coord = curr_curve.getCoordinate(i);
		glm::dvec3 curr_point = curr_curve.getPoint(i);

		//glm::dvec3 growth_vec = growth_dir(curr_coord) * growth_length(curr_coord);

		CoordinateSystem local_Frenet_frame = get_Frenet_frame(surface.size() - 1, i);
		/*
		double q1 = -0.5f;
		double q2 = 1.f;
		double q3 = 0.5f;
		*/
		/*
		double q1 = -0.2;
		double q2 = 2 + glm::cos(curr_coord);
		double q3 = 0.;
		*/
		double q1 = -(-0.025+0.32*glm::sin(curr_coord));
		double q2 = 1 + 10*glm::cos(curr_coord);
		double q3 = 0.32*glm::cos(curr_coord);


		local_Frenet_frame.set_local_coordinates(q1, q2, q3);
		glm::dvec3 growth_vec = local_Frenet_frame.get_global_coordinates();
		//glm::normalize(growth_vec);
		growth_vec *= 0.001;

		double next_coord = curr_coord;
		glm::dvec3 next_point = curr_point + growth_vec;

		coords_next_curve.push_back(next_coord);
		points_next_curve.push_back(next_point);
	}

	DiscreteParaCurve next_curve(coords_next_curve, points_next_curve);
	surface.push_back(next_curve);
}

void SurfaceGenerator::growth_log_spiral()
{
	double alpha = -0.45 * 3.14159;

	DiscreteParaCurve curr_curve = surface.back();
	std::vector<double> coords_next_curve;
	std::vector<glm::dvec3> points_next_curve;

	for (unsigned int i = 0; i < curr_curve.getPoints().size(); i++)
	{
		double curr_coord = curr_curve.getCoordinate(i);
		glm::dvec3 curr_point = curr_curve.getPoint(i);

		glm::dvec2 op_xz(curr_point.x, curr_point.z);
		double distance = glm::length(op_xz);
		glm::dmat2x2 rotate;
		rotate[0][0] = glm::cos(alpha);		rotate[0][1] = glm::sin(alpha) * -1.;
		rotate[1][0] = glm::sin(alpha);		rotate[1][1] = glm::cos(alpha);
		glm::dvec2 velocity_xz = glm::normalize(rotate * op_xz);

		glm::dvec3 growth_vec = glm::dvec3(velocity_xz.x, 0., velocity_xz.y) * 0.1;

		double next_coord = curr_coord;
		glm::dvec3 next_point = curr_point + growth_vec;

		coords_next_curve.push_back(next_coord);
		points_next_curve.push_back(next_point);

	}

	DiscreteParaCurve next_curve(coords_next_curve, points_next_curve);
	surface.push_back(next_curve);
}



CoordinateSystem SurfaceGenerator::get_Frenet_frame(int curve_index, int point_index)
{
	DiscreteParaCurve curr_curve = surface[curve_index];
	std::vector<glm::dvec3> curr_curve_points = curr_curve.getPoints();
	glm::dvec3 point_m2 = curr_curve_points[(point_index - 2+ curr_curve_points.size()) % curr_curve_points.size()];
	glm::dvec3 point_m1 = curr_curve_points[(point_index - 1+ curr_curve_points.size()) % curr_curve_points.size()];
	glm::dvec3 point_0 = curr_curve_points[(point_index) % curr_curve_points.size()];
	glm::dvec3 point_p1 = curr_curve_points[(point_index + 1) % curr_curve_points.size()];
	glm::dvec3 point_p2 = curr_curve_points[(point_index + 2) % curr_curve_points.size()];

	glm::dvec3 tan = point_p1 - point_m1;
	tan = glm::normalize(tan);
	glm::dvec3 tan_m1 = point_0 - point_m2;
	tan_m1 = glm::normalize(tan_m1);
	glm::dvec3 tan_p1 = point_p2 - point_0;
	tan_p1 = glm::normalize(tan_p1);

	glm::dvec3 normal = tan_p1 - tan_m1;
	normal = glm::normalize(normal);

	glm::dvec3 binormal = glm::cross(tan, normal);

	CoordinateSystem local_Frenet_frame;
	local_Frenet_frame.set_local_basis(normal, binormal, tan);

	return local_Frenet_frame;
}