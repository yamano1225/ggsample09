#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ����
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);         // �ʒu

// ���_����
layout (location = 0) in vec4 pv;                 // ���[�J�����W�n�̒��_�ʒu
layout (location = 1) in vec4 nv;                 // ���_�̖@���x�N�g��

// �ϊ��s��
uniform mat4 mw;                                  // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                  // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                  // �@���x�N�g���̕ϊ��s��

// ���X�^���C�U�ɑ��钸�_����
out vec3 l;                                       // �����x�N�g��
out vec3 n;                                       // ���_�̖@���x�N�g��
out vec3 h;                                       // ���ԃx�N�g��
out vec3 t;                                       // �ڐ��x�N�g��

void main(void)
{
  vec4 p = mw * pv;                               // ���_���W�n�̒��_�̈ʒu
  vec3 v = -normalize(p.xyz);                     // �����x�N�g��
  l = normalize(p.w * pl.xyz - pl.w * p.xyz);     // �����x�N�g��
  n = normalize((mg * nv).xyz);                   // ���_�̖@���x�N�g��
  h = normalize(l + v);                           // ���ԃx�N�g��
  t = normalize(vec3(-nv.z, 0.0, nv.x));          // �ڐ��x�N�g��

  gl_Position = mc * pv;
}
