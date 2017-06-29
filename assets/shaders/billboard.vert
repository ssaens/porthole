#version 330 core

layout (location = 0) in vec3 pos;

out vec2 tex_coord;

void main() {
    gl_Position = vec4(pos, 1.f);
    tex_coord = vec2(pos.x + 0.5, pos.y + 0.5);
}
