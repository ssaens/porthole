#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex;

out vec3 n;
out vec3 frag_pos;

uniform mat4 proj;
uniform mat4 view;

void main() {
	vec4 position = proj * view * vec4(pos, 1.0);
	frag_pos = pos;
	gl_Position = vec4(position.x * 0.4, position.y * 0.4, position.z * 0.4, 1);
	n = normal;
}
