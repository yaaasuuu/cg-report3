//
// phong.frag - Phong Shading 用フラグメントシェーダ
//
#version 130

in vec3 vmNormal;	// 法線(カメラ座標系)

uniform vec3 lColor;	// 光源色(RGB別強さ)
uniform vec3 lDirection;// 光源方向(カメラ座標系)
uniform vec3 ambColor;	// 環境光色(RGB別強さ)
uniform vec3 albDifAmb;	// 拡散/環境反射率
uniform vec2 albSpec;	// 鏡面反射率とn

out vec4 fColor;	// 描画色

void main(void)
{
// (補間済み)法線を単位ベクトル化
	vec3 vmNormal2 = normalize(vmNormal);
// 入射角の余弦
	float difcos = max(0.0, dot(vmNormal2, lDirection));
// 正反射方向と視線の余弦
	vec3 ref = reflect(- lDirection, vmNormal2);
	float speccos = max(0.0, dot(ref, vec3(0.0, 0.0, 1.0)));
	if(difcos == 0.0)
		speccos = 0.0;
	else
		speccos = pow(speccos, albSpec.y);
// 環境光/拡散光/鏡面光の和を出力
	fColor = vec4(albDifAmb * ambColor + albDifAmb * lColor * difcos
	       + vec3(albSpec.x) * lColor * speccos, 1.0);
}
