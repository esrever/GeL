#version 150 core

uniform mat4 MVP;

in vec4 Color;
in vec3 Position;

out block
{
	//flat int Index;
	vec4 Color;
} Out;

void main()
{
	vec3 wpos = Position;
	wpos.z = 0;
	gl_Position = MVP * vec4(wpos, 1.0);
	Out.Color = Color;
}

