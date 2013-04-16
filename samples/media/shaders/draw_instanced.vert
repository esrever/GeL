#version 150 core

uniform mat4 MVP;

in vec4 Color;
in vec3 Position;

layout(std140, column_major) uniform;

uniform instanceData
{
	mat4 xform[16];
} InstanceData;

out block
{
	//flat int Index;
	vec4 Color;
} Out;

void main()
{
	vec4 wpos = InstanceData.xform[gl_InstanceID] * vec4(Position,1);
	gl_Position = MVP * wpos;
	Out.Color = Color;
}

