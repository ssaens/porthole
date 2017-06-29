#version 330 core

in vec2 tex_coord;

out vec4 color;

uniform sampler2D frame;

void main() {
	color = texture(frame, tex_coord);
}
