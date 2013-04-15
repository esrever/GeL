#version 150 core

uniform mat4 MVP;

in vec3 Position;
in vec4 Color;

out block
{
	flat int Index;
	vec4 Color;
} Out;

void main()
{
	vec3 off = 4*(vec3( gl_InstanceID % 4, gl_InstanceID / 4,0) - vec3(1.5,1.5,0));
	gl_Position = MVP * vec4(Position+off, 1.0);
	Out.Color = Color;
	Out.Index = gl_VertexID / 4;
}

