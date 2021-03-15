#include "../include/format_mesh.hpp"

void format_mesh(std::vector<GLfloat> &output_mesh,
                 std::vector<glm::vec4> &vertices,
                 std::vector<GLushort> &elements  ) {

    output_mesh.resize(elements.size() * 3, GLfloat(0.0));

    for(unsigned int i = 0; i < elements.size() / 3; i++) {
        for(unsigned int j = i * 3; j < (i * 3) + 3; j++) {
            int k = j * 3;
            output_mesh[ k + 0 ] = vertices[ elements[ j ] ].x;
            output_mesh[ k + 1 ] = vertices[ elements[ j ] ].y;
            output_mesh[ k + 2 ] = vertices[ elements[ j ] ].z;
        }
    }

}
