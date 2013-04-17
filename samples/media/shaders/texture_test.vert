#version 150 core


out block
{
	vec2 coord;
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
	gl_Position = vec4(pos,0,1);
	Out.coord = pos*0.5 + 0.5;
}

