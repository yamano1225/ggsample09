#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 光源
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);         // 位置

// 頂点属性
layout (location = 0) in vec4 pv;                 // ローカル座標系の頂点位置
layout (location = 1) in vec4 nv;                 // 頂点の法線ベクトル

// 変換行列
uniform mat4 mw;                                  // 視点座標系への変換行列
uniform mat4 mc;                                  // クリッピング座標系への変換行列
uniform mat4 mg;                                  // 法線ベクトルの変換行列

// ラスタライザに送る頂点属性
out vec3 l;                                       // 光線ベクトル
out vec3 n;                                       // 頂点の法線ベクトル
out vec3 h;                                       // 中間ベクトル
out vec3 t;                                       // 接線ベクトル

void main(void)
{
  vec4 p = mw * pv;                               // 視点座標系の頂点の位置
  vec3 v = -normalize(p.xyz);                     // 視線ベクトル
  l = normalize(p.w * pl.xyz - pl.w * p.xyz);     // 光線ベクトル
  n = normalize((mg * nv).xyz);                   // 頂点の法線ベクトル
  h = normalize(l + v);                           // 中間ベクトル
  t = normalize(vec3(-nv.z, 0.0, nv.x));          // 接線ベクトル

  gl_Position = mc * pv;
}
