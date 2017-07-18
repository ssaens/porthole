#version 330 core

in vec3 n;
in vec3 frag_pos;

out vec4 color;

void main() {
    vec3 light_pos = vec3(0, 20, 0);
    vec3 light_color = vec3(0.8f, 0.8f, 0.8f);
    vec3 object_color = vec3(0.4f, 0.8f, 0.8f);

    float ambient_strength = .2f;
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(n);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 result = (ambient + diffuse) * object_color;
    color = vec4(result, 1.0f);
}
