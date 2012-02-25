#version 120

// ����
const vec4 lamb   = vec4(0.2, 0.2, 0.2, 1.0);  // �������x
const vec4 ldiff  = vec4(1.0, 1.0, 1.0, 0.0);  // �������x�̊g�U���ː���
const vec4 lspec  = vec4(1.0, 1.0, 1.0, 0.0);  // �������x�̋��ʔ��ː���

// �ގ�
const vec4 kamb   = vec4(0.2, 0.4, 0.6, 1.0);  // �����̔��ˌW��
const vec4 kdiff  = vec4(0.2, 0.4, 0.6, 1.0);  // �g�U���ˌW��
const vec4 kspec  = vec4(0.4, 0.4, 0.4, 1.0);  // ���ʔ��ˌW��
const float kshi  = 40.0;                      // �P���W��

// �o�[�e�b�N�X�V�F�[�_����󂯎��f�[�^
varying vec3 l;          // ��Ԃ��ꂽ�����x�N�g��
varying vec3 v;          // ��Ԃ��ꂽ�����x�N�g��
varying vec3 n;          // ��Ԃ��ꂽ�@���x�N�g��
varying vec3 t;          // ��Ԃ��ꂽ�ڐ��x�N�g��

// �e�N�X�`��
uniform sampler2D nmap;  // normal map

void main(void)
{
  vec3 h = normalize(l - normalize(v));          // ���ԃx�N�g��
  vec4 iamb = kamb * lamb;
  vec4 idiff = max(dot(n, l), 0) * kdiff * ldiff;
  vec4 ispec = pow(max(dot(n, h), 0), kshi) * kspec * lspec;

  gl_FragColor = iamb + idiff + ispec;
}
