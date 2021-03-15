#version 460 core
in vec3 outColor;
out vec4 myColor;
void main( ){
    myColor = vec4( outColor, 1.0f );
}
