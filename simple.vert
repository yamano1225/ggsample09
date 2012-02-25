#version 120

attribute vec4 pv;  // ローカル座標系の頂点位置
attribute vec4 nv;  // 頂点の法線ベクトル

uniform mat4 mw;    // 視点座標系への変換行列
uniform mat4 mc;    // クリッピング座標系への変換行列
uniform mat4 mg;    // 法線ベクトルの変換行列

varying vec3 l;     // フラグメントシェーダに送る光線ベクトル
varying vec3 v;     // フラグメントシェーダに送る頂点位置
varying vec3 n;     // フラグメントシェーダに送る法線ベクトル
varying vec3 t;     // フラグメントシェーダに送る接線ベクトル

void main(void)
{
  l = normalize(vec3(4.0, 8.0, 8.0));     // 光線ベクトル
  v = normalize((mw * pv).xyz);           // 視線ベクトル
  n = normalize((mg * nv).xyz);           // 法線ベクトル
  t = normalize(vec3(-nv.z, 0.0, nv.x));  // 接線ベクトル
  gl_Position = mc * pv;
}
