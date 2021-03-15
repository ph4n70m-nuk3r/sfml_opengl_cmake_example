#ifndef FORMAT_MESH_HPP
#define FORMAT_MESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

void format_mesh(std::vector<GLfloat> &output_mesh,
                 std::vector<glm::vec4> &vertices,
                 std::vector<GLushort> &elements  );

#endif // FORMAT_MESH_HPP
