#version 120

// õ¹
const vec3 ldiff  = vec3(1.0, 1.0, 1.0);  // õ¹­xÌgU½Ë¬ª

// Þ¿
const vec3 kdiff  = vec3(0.8, 0.8, 0.8);  // gU½ËW

// ¸_®«
attribute vec4 pv;  // [JÀWnÌ¸_Êu
attribute vec4 nv;  // ¸_Ì@üxNg

// Ï·sñ
uniform mat4 mw;    // _ÀWnÖÌÏ·sñ
uniform mat4 mc;    // NbsOÀWnÖÌÏ·sñ
uniform mat4 mg;    // @üxNgÌÏ·sñ

// Ê²aðÍ
const float k1 = 0.429043;
const float k2 = 0.511664;
const float k3 = 0.743125;
const float k4 = 0.886227;
const float k5 = 0.247708;
uniform vec3 sh[9]; // Ê²aW

// tOgVF[_Éé½Ëõ­x
varying vec3 idiff; // gU½Ëõ­x

void main(void)
{
  vec3 l = normalize(vec3(4.0, 8.0, 8.0));     // õüxNg
  vec3 v = normalize((mw * pv).xyz);           // üxNg
  vec3 n = normalize((mg * nv).xyz);           // @üxNg
  vec3 h = normalize(l - v);                   // ÔxNg
  
  //Â«©çÌúËÆxÌaE
  vec3 E = k1*sh[8]*(n.x*n.x-n.y*n.y) + k3*sh[6]*n.z*n.z + k4*sh[0] - k5*sh[6]
		 + 2*k1*( sh[4]*n.x*n.y + sh[7]*n.x*n.z + sh[5]*n.y*n.z )
		 + 2*k2*( sh[3]*n.x + sh[1]*n.y + sh[2]*n.z );

  idiff = kdiff * E * ldiff;
  
  gl_Position = mc * pv;
}

