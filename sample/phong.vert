//
// phong.vert - Phong Shading 用頂点シェーダ
//
#version 130

in vec4 vPosition;	// 頂点座標
in vec3 vNormal;	// 頂点法線

uniform mat4 pvmMatrix;	// PVM変換行列
uniform mat4 vmMatrix;	// VM変換行列

out vec3 vmNormal;	// 頂点法線(カメラ座標系)

void main(void)
{
// 法線をカメラ座標系に
	vmNormal = mat3(vmMatrix) * vNormal;
// 座標変換
	gl_Position = pvmMatrix * vPosition;
}
