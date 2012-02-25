#version 120

attribute vec4 pv;  // ���[�J�����W�n�̒��_�ʒu
attribute vec4 nv;  // ���_�̖@���x�N�g��

uniform mat4 mw;    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;    // �@���x�N�g���̕ϊ��s��

varying vec3 l;     // �t���O�����g�V�F�[�_�ɑ�������x�N�g��
varying vec3 v;     // �t���O�����g�V�F�[�_�ɑ��钸�_�ʒu
varying vec3 n;     // �t���O�����g�V�F�[�_�ɑ���@���x�N�g��
varying vec3 t;     // �t���O�����g�V�F�[�_�ɑ���ڐ��x�N�g��

void main(void)
{
  l = normalize(vec3(4.0, 8.0, 8.0));     // �����x�N�g��
  v = normalize((mw * pv).xyz);           // �����x�N�g��
  n = normalize((mg * nv).xyz);           // �@���x�N�g��
  t = normalize(vec3(-nv.z, 0.0, nv.x));  // �ڐ��x�N�g��
  gl_Position = mc * pv;
}
