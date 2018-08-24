#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

uniform mat4 projection_mat;
uniform mat4 view_mat = mat4(1.0);
uniform mat4 modele_mat = mat4(1.0);

out DATA{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
	gl_Position = projection_mat * view_mat * modele_mat * position;
	vs_out.position = modele_mat * position;
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}
