#version 330 core

in vec4 vert_color;

out vec4 color;

uniform float red_color;

void main() {
	color = vec4(vert_color.r, vert_color.g, vert_color.ba);
}