#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_color;

out vec4 vert_color;

uniform float x_offset;
uniform float y_offset;
uniform float z_offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    gl_Position = projection * view * model * vec4(position.x + z_offset, position.y, position.z + z_offset, 1.0f);
    vert_color = vec4(in_color, 1.0f);
}