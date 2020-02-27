#pragma once

#include <vector>
#include "glm/glm.hpp"

class ObjFile
{
public:
	ObjFile(std::vector<std::vector<glm::dvec3> > grid);
	~ObjFile();

	void export_obj_file();

private:
	std::vector<std::vector<glm::dvec3> > grid;
};

