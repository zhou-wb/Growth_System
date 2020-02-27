#include "ObjFile.h"

#include <fstream>
#include "glm/glm.hpp"
#include <string>



ObjFile::ObjFile(std::vector<std::vector<glm::dvec3> > grid) :grid(grid)
{
}


ObjFile::~ObjFile()
{
}

void ObjFile::export_obj_file()
{
	std::ofstream outfile;
	outfile.open("surface.obj", std::ofstream::out | std::ofstream::trunc);

	std::vector<std::vector<int> > index;
	int num = 1;

	for (unsigned int i = 0; i < grid.size(); i++)
	{
		std::vector<int> newline;
		index.push_back(newline);

		for (unsigned int j = 0; j < grid[i].size(); j++)
		{
			glm::dvec3 p = grid[i][j];
			outfile << "v " + std::to_string(p.x) + " " + std::to_string(p.y) + " " + std::to_string(p.z) << std::endl;
			index[i].push_back(num);
			num++;
		}
	}

	std::vector<std::vector<glm::dvec3> > vertex_normal;
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		std::vector<glm::dvec3> newline;
		vertex_normal.push_back(newline);

		for (unsigned int j = 0; j < grid[i].size(); j++)
		{
			vertex_normal[i].push_back(glm::dvec3(0.f, 0.f, 0.f));
		}
	}

	for (unsigned int i = 0; i < grid.size() - 1; i++)
	{
		for (unsigned int j = 0; j < grid[i].size() - 1; j++)
		{
			glm::dvec3 lowleft_p = grid[i][j];
			glm::dvec3 lowright_p = grid[i][j + 1];
			glm::dvec3 upleft_p = grid[i + 1][j];
			glm::dvec3 upright_p = grid[i + 1][j + 1];

			int lowleft_i = index[i][j];
			int lowright_i = index[i][j + 1];
			int upleft_i = index[i + 1][j];
			int upright_i = index[i + 1][j + 1];

			outfile << "f " + std::to_string(lowleft_i) + "//" + std::to_string(lowleft_i) + " " \
				+ std::to_string(lowright_i) + "//" + std::to_string(lowright_i) + " " \
				+ std::to_string(upleft_i) + "//" + std::to_string(upleft_i) << std::endl;
			glm::dvec3 fn = glm::cross(lowright_p - lowleft_p, upleft_p - lowleft_p);
			vertex_normal[i][j] += fn;
			vertex_normal[i][j + 1] += fn;
			vertex_normal[i + 1][j] += fn;

			outfile << "f " + std::to_string(upleft_i) + "//" + std::to_string(upleft_i) + " " \
				+ std::to_string(lowright_i) + "//" + std::to_string(lowright_i) + " " \
				+ std::to_string(upright_i) + "//" + std::to_string(upright_i) << std::endl;
			fn = glm::cross(upright_p - lowright_p, upleft_p - lowright_p);
			vertex_normal[i + 1][j + 1] += fn;
			vertex_normal[i][j + 1] += fn;
			vertex_normal[i + 1][j] += fn;
		}
	}

	for (unsigned int i = 0; i < vertex_normal.size(); i++)
	{
		for (unsigned int j = 0; j < vertex_normal[i].size(); j++)
		{
			glm::dvec3 vn = normalize(vertex_normal[i][j]);
			outfile << "vn " + std::to_string(vn.x) + " " + std::to_string(vn.y) + " " + std::to_string(vn.z) << std::endl;
		}
	}

	outfile.close();
}