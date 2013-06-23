#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 光源
const vec4 lamb   = vec4(0.2, 0.2, 0.2, 1.0);       // 環境光成分の強度
const vec4 ldiff  = vec4(1.0, 1.0, 1.0, 0.0);       // 拡散反射成分の強度
const vec4 lspec  = vec4(1.0, 1.0, 1.0, 0.0);       // 鏡面反射成分の強度

// 材質
const vec4 kamb   = vec4(0.2, 0.4, 0.6, 1.0);       // 環境光の反射係数
const vec4 kdiff  = vec4(0.2, 0.4, 0.6, 1.0);       // 拡散反射係数
const vec4 kspec  = vec4(0.4, 0.4, 0.4, 1.0);       // 鏡面反射係数
const float kshi  = 40.0;                           // 輝き係数

// ラスタライザから受け取る頂点属性の補間値
in vec3 v;                                          // 補間された視線ベクトル
in vec3 l;                                          // 補間された光線ベクトル
in vec3 n;                                          // 補間された法線ベクトル
in vec3 t;                                          // 補間された接線ベクトル

// フレームバッファに出力するデータ
layout (location = 0) out vec4 fc;                  // フラグメントの色

void main(void)
{
  vec3 nv = normalize(v);                           // 視線ベクトル
  vec3 nl = normalize(l);                           // 光線ベクトル
  vec3 nn = normalize(n);                           // 法線ベクトル
  vec3 nt = normalize(t);                           // 接線ベクトル
  
  vec3 r = 2.0 * dot(nn, nl) * nn - nl;             // 反射ベクトル

  vec4 iamb = kamb * lamb;
  vec4 idiff = max(dot(nn, nl), 0.0) * kdiff * ldiff;
  vec4 ispec = pow(max(dot(nv, r), 0.0), kshi) * kspec * lspec;

  fc = iamb + idiff + ispec;
}
