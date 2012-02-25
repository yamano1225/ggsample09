#version 120

// 光源
const vec4 lamb   = vec4(0.2, 0.2, 0.2, 1.0);  // 環境光強度
const vec4 ldiff  = vec4(1.0, 1.0, 1.0, 0.0);  // 光源強度の拡散反射成分
const vec4 lspec  = vec4(1.0, 1.0, 1.0, 0.0);  // 光源強度の鏡面反射成分

// 材質
const vec4 kamb   = vec4(0.2, 0.4, 0.6, 1.0);  // 環境光の反射係数
const vec4 kdiff  = vec4(0.2, 0.4, 0.6, 1.0);  // 拡散反射係数
const vec4 kspec  = vec4(0.4, 0.4, 0.4, 1.0);  // 鏡面反射係数
const float kshi  = 40.0;                      // 輝き係数

// バーテックスシェーダから受け取るデータ
varying vec3 l;          // 補間された光線ベクトル
varying vec3 v;          // 補間された視線ベクトル
varying vec3 n;          // 補間された法線ベクトル
varying vec3 t;          // 補間された接線ベクトル

// テクスチャ
uniform sampler2D nmap;  // normal map

void main(void)
{
  vec3 h = normalize(l - normalize(v));          // 中間ベクトル
  vec4 iamb = kamb * lamb;
  vec4 idiff = max(dot(n, l), 0) * kdiff * ldiff;
  vec4 ispec = pow(max(dot(n, h), 0), kshi) * kspec * lspec;

  gl_FragColor = iamb + idiff + ispec;
}
