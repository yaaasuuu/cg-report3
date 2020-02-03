//
// gouraud.vert - Gouraud Shading 用頂点シェーダ
//
#version 130

in vec4 vPosition;	// 頂点座標
in vec3 vNormal;	// 頂点法線

uniform mat4 pvmMatrix;	// PVM変換行列
uniform mat4 vmMatrix;	// VM変換行列
uniform vec3 lColor;	// 光源色(RGB別強さ)
uniform vec3 lDirection;// 光源方向(カメラ座標系)
uniform vec3 ambColor;	// 環境光色(RGB別強さ)
uniform vec3 albDifAmb;	// 拡散/環境反射率
uniform vec2 albSpec;	// 鏡面反射率とn

out vec3 Color;		// 描画色

void main(void)
{
// 法線をカメラ座標系に
	vec3 vmNormal = mat3(vmMatrix) * vNormal;
// 入射角の余弦
	float difcos = max(0.0, dot(vmNormal, lDirection));
// 正反射方向と視線の余弦
	vec3 ref = reflect(- lDirection, vmNormal);
	float speccos = max(0.0, dot(ref, vec3(0.0, 0.0, 1.0)));
	if(difcos == 0.0)
		speccos = 0.0;
	else
		speccos = pow(speccos, albSpec.y);
// 環境光/拡散光/鏡面光の和
	Color = albDifAmb * ambColor + albDifAmb * lColor * difcos
	 + vec3(albSpec.x) * lColor * speccos;
// 座標変換
	gl_Position = pvmMatrix * vPosition;
}
