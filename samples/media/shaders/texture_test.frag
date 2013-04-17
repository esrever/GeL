#version 150 core

uniform sampler2D image;

in block
{
	vec2 coord;
} In;

out vec4 Color;

void main()
{
	
	//Color = vec4(In.coord,0,1);
	Color = texture(image,In.coord);
}
