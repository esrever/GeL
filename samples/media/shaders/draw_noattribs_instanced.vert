#version 150 core

uniform mat4 MVP;

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

const int VertexCount = 4;
const vec2 Position[VertexCount] = vec2[](
	vec2(-1.0,-1.0),
	vec2( 1.0,-1.0),
	vec2( 1.0, 1.0),
	vec2(-1.0,1.0));

void main()
{
	vec2 pos = Position[gl_VertexID];
	vec4 wpos = InstanceData.xform[gl_InstanceID] * vec4(pos,0,1);
	wpos = vec4(pos,0,1);
	gl_Position = MVP * wpos;
	Out.Color = vec4(pos*0.5 + 0.5,0,1);
}

