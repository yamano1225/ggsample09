#version 120

// ����
const vec3 ldiff  = vec3(1.0, 1.0, 1.0);  // �������x�̊g�U���ː���

// �ގ�
const vec3 kdiff  = vec3(0.8, 0.8, 0.8);  // �g�U���ˌW��

// ���_����
attribute vec4 pv;  // ���[�J�����W�n�̒��_�ʒu
attribute vec4 nv;  // ���_�̖@���x�N�g��

// �ϊ��s��
uniform mat4 mw;    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;    // �@���x�N�g���̕ϊ��s��

// ���ʒ��a���
const float k1 = 0.429043;
const float k2 = 0.511664;
const float k3 = 0.743125;
const float k4 = 0.886227;
const float k5 = 0.247708;
uniform vec3 sh[9]; // ���ʒ��a�W��

// �t���O�����g�V�F�[�_�ɑ��锽�ˌ����x
varying vec3 idiff; // �g�U���ˌ����x

void main(void)
{
  vec3 l = normalize(vec3(4.0, 8.0, 8.0));     // �����x�N�g��
  vec3 v = normalize((mw * pv).xyz);           // �����x�N�g��
  vec3 n = normalize((mg * nv).xyz);           // �@���x�N�g��
  vec3 h = normalize(l - v);                   // ���ԃx�N�g��
  
  //������̕��ˏƓx�̑��aE
  vec3 E = k1*sh[8]*(n.x*n.x-n.y*n.y) + k3*sh[6]*n.z*n.z + k4*sh[0] - k5*sh[6]
		 + 2*k1*( sh[4]*n.x*n.y + sh[7]*n.x*n.z + sh[5]*n.y*n.z )
		 + 2*k2*( sh[3]*n.x + sh[1]*n.y + sh[2]*n.z );

  idiff = kdiff * E * ldiff;
  
  gl_Position = mc * pv;
}

