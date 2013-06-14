#version 150 core

// ����
const vec4 lamb   = vec4(0.2, 0.2, 0.2, 1.0);       // ���������̋��x
const vec4 ldiff  = vec4(1.0, 1.0, 1.0, 0.0);       // �g�U���ː����̋��x
const vec4 lspec  = vec4(1.0, 1.0, 1.0, 0.0);       // ���ʔ��ː����̋��x

// �ގ�
const vec4 kamb   = vec4(0.2, 0.4, 0.6, 1.0);       // �����̔��ˌW��
const vec4 kdiff  = vec4(0.2, 0.4, 0.6, 1.0);       // �g�U���ˌW��
const vec4 kspec  = vec4(0.4, 0.4, 0.4, 1.0);       // ���ʔ��ˌW��
const float kshi  = 40.0;                           // �P���W��

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec3 l;                                          // ��Ԃ��ꂽ�����x�N�g��
in vec3 n;                                          // ��Ԃ��ꂽ�@���x�N�g��
in vec3 h;                                          // ��Ԃ��ꂽ���ԃx�N�g��
in vec2 t;                                          // ��Ԃ��ꂽ�ڐ��x�N�g��

// �t���[���o�b�t�@�ɏo�͂���f�[�^
out vec4 fc;                                        // �t���O�����g�̐F

void main(void)
{
  vec3 nl = normalize(l);                           // �����x�N�g��
  vec3 nn = normalize(n);                           // �@���x�N�g��
  vec3 nh = normalize(h);                           // ���ԃx�N�g��

  vec4 iamb = kamb * lamb;
  vec4 idiff = max(dot(nn, nl), 0.0) * kdiff * ldiff;
  vec4 ispec = pow(max(dot(nn, nh), 0.0), kshi) * kspec * lspec;

  fc = iamb + idiff + ispec;
}
