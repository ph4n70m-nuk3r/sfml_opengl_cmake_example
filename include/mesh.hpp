#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/vec3.hpp> // glm::vec3, glm::ivec3

class Mesh {

public:

	Mesh()
	{
		
	}

	Mesh(std::vector<glm::vec3> data)
	{
		_mesh = data;
	}

	Mesh(std::vector<glm::vec3> data, std::vector<glm::vec3> vcol)
	{
		_mesh = data;
		_colr = vcol;
	}

	void m_update_vertices(std::vector<glm::vec3> data)
	{
		_mesh = data;
	}

	void m_update_vcolours(std::vector<glm::vec3> vcol)
	{
		_colr = vcol;
	}

	void print_v_c()
	{
		for(auto i = 0; i < _mesh.size(); i++)
		{
			std::cout << "vertex " << i << '\n'
						<< _mesh[i].x << '\n'
						<< _mesh[i].y << '\n'
						<< _mesh[i].z << '\n';
		}
		for(auto i = 0; i < _colr.size(); i++)
		{
			std::cout << "colour " << i << '\n'
						<< _colr[i].r << '\n'
						<< _colr[i].g << '\n'
						<< _colr[i].b << '\n';
		}				
	}

private:

	std::vector<glm::vec3> _mesh;

	std::vector<glm::vec3> _colr;

};

#endif // MESH_HPP
