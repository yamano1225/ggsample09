#version 120

// 光源
const vec3 ldiff  = vec3(1.0, 1.0, 1.0);  // 光源強度の拡散反射成分

// 材質
const vec3 kdiff  = vec3(0.8, 0.8, 0.8);  // 拡散反射係数

// 頂点属性
attribute vec4 pv;  // ローカル座標系の頂点位置
attribute vec4 nv;  // 頂点の法線ベクトル

// 変換行列
uniform mat4 mw;    // 視点座標系への変換行列
uniform mat4 mc;    // クリッピング座標系への変換行列
uniform mat4 mg;    // 法線ベクトルの変換行列

// 球面調和解析
const float k1 = 0.429043;
const float k2 = 0.511664;
const float k3 = 0.743125;
const float k4 = 0.886227;
const float k5 = 0.247708;
uniform vec3 sh[9]; // 球面調和係数

// フラグメントシェーダに送る反射光強度
varying vec3 idiff; // 拡散反射光強度

void main(void)
{
  vec3 l = normalize(vec3(4.0, 8.0, 8.0));     // 光線ベクトル
  vec3 v = normalize((mw * pv).xyz);           // 視線ベクトル
  vec3 n = normalize((mg * nv).xyz);           // 法線ベクトル
  vec3 h = normalize(l - v);                   // 中間ベクトル
  
  //環境からの放射照度の総和E
  vec3 E = k1*sh[8]*(n.x*n.x-n.y*n.y) + k3*sh[6]*n.z*n.z + k4*sh[0] - k5*sh[6]
		 + 2*k1*( sh[4]*n.x*n.y + sh[7]*n.x*n.z + sh[5]*n.y*n.z )
		 + 2*k2*( sh[3]*n.x + sh[1]*n.y + sh[2]*n.z );

  idiff = kdiff * E * ldiff;
  
  gl_Position = mc * pv;
}

