//
// gouraud.frag - Gouraud Shading 用フラグメントシェーダ
//
#version 130

in vec3 Color;

out vec4 fColor;

void main(void)
{
	fColor = vec4(Color, 1.0);
}
