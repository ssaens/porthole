#version 330 core

layout (location = 0) in vec3 pos;

uniform float x_offset;

uniform mat4 proj;
uniform mat4 view;

void main() {
//    gl_Position = vec4(pos, 1.f);
	gl_Position = proj * view * vec4(pos.x + x_offset, pos.y, pos.z, 1.0);
}
