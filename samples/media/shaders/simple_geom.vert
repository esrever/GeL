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
	// Assume 16 instances
	vec2 off = 2*vec2( gl_InstanceID & 3, gl_InstanceID >> 2);
	vec3 wpos = Position;
	wpos.xy = (wpos.xy + off)/4;
	gl_Position = MVP * vec4(wpos, 1.0);
	Out.Color = Color;
	//Out.Color.xyz = Position.z;
}

