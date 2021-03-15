#version 460 core
layout ( location = 0 ) in vec3 vertexPosition_modelspace;
layout ( location = 1 ) in vec3 inColor;
out vec3 outColor;
void main( ){
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    outColor = inColor;
}
