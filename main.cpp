#include <cmath>
#include <cstdlib>

#include "gg.h"
using namespace gg;

#include "matrix.h"

// �v���O�����I�u�W�F�N�g
static GLuint program;

// attribute �ϐ��̃C���f�b�N�X
static GLint pvLoc, nvLoc;

// uniform �ϐ��̃C���f�b�N�X
static GLint mwLoc, mcLoc, mgLoc;

// �������e�ϊ��s��
static GLfloat mp[16];

// �A�j���[�V�����̎���
#define CYCLE 10000

#define SLICES 64
#define STACKS 32

#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

static GLfloat pv[VERTICES][3];
static GLfloat nv[VERTICES][3];
static GLfloat tv[VERTICES][2];
static GLuint face[FACES][3];

/*
** ��ʕ\��
*/
static void display(void)
{
  // �����̌v��
  static int firstTime = 0;
  GLfloat t;
  if (firstTime == 0) { firstTime = glutGet(GLUT_ELAPSED_TIME); t = 0.0f; }
  else t = (GLfloat)((glutGet(GLUT_ELAPSED_TIME) - firstTime) % CYCLE) / (GLfloat)CYCLE;

  // ���f�����O�ϊ��s��
  GLfloat mm[16];
  rotate(mm, 1.0f, 0.0f, 0.0f, 12.56637f * t);

  // ����ϊ��s��
  GLfloat mv[16];
  lookat(mv, 0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  // ���f���r���[�ϊ��s��
  GLfloat mw[16];
  multiply(mw, mv, mm);
  
  // �@���ϊ��s��
  GLfloat mg[16];
  normal(mg, mw);
  
  // ���f���r���[�E���e�ϊ�
  GLfloat mc[16];
  multiply(mc, mp, mw);
  
  // ��ʃN���A
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // �V�F�[�_�v���O�����̑I��
  glUseProgram(program);
  
  // uniform �ϐ���ݒ肷��
  glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw);
  glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc);
  glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg);
  
  // attribute �ϐ� pv, nv, tv ��z��ϐ����瓾�邱�Ƃ�������
  glEnableVertexAttribArray(pvLoc);
  glEnableVertexAttribArray(nvLoc);
  
  // attribute �ϐ� pv, nv, tv �Ɣz��ϐ� pv, nv, tv �����т���
  glVertexAttribPointer(pvLoc, 3, GL_FLOAT, GL_FALSE, 0, pv);
  glVertexAttribPointer(nvLoc, 3, GL_FLOAT, GL_FALSE, 0, nv);

  // �}�`��`�悷��
  glDrawElements(GL_TRIANGLES, FACES * 3, GL_UNSIGNED_INT, face);

  glutSwapBuffers();
}

/*
** �E�B���h�E�̃��T�C�Y
*/
static void resize(int w, int h)
{
  // �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
  glViewport(0, 0, w, h);
  
  // �������e�ϊ��s������߂�i�A�X�y�N�g�� w / h�j
  perspective(mp, 0.5f, (float)w / (float)h, 1.0f, 20.0f);
}

/*
** �A�j���[�V����
*/
static void idle(void)
{
  glutPostRedisplay();
}

/*
** ���̃f�[�^���쐬����
*/
static void makeSphere(float radius, int slices, int stacks,
  GLfloat (*pv)[3], GLfloat (*nv)[3], GLfloat (*tv)[2], GLuint (*f)[3])
{
  // ���_�̈ʒu�ƃe�N�X�`�����W�����߂�
  for (int k = 0, j = 0; j <= stacks; ++j) {
    float t = (float)j / (float)stacks;
    float ph = 3.141593f * t;
    float y = cosf(ph);
    float r = sinf(ph);

    for (int i = 0; i <= slices; ++i) {
      float s = (float)i / (float)slices;
      float th = 2.0f * 3.141593f * s;
      float x = r * cosf(th);
      float z = r * sinf(th);

      // ���_�̍��W�l
      pv[k][0] = x * radius;
      pv[k][1] = y * radius;
      pv[k][2] = z * radius;

      // ���_�̖@���x�N�g��
      nv[k][0] = x;
      nv[k][1] = y;
      nv[k][2] = z;

      // ���_�̃e�N�X�`�����W�l
      tv[k][0] = s;
      tv[k][1] = t;

      ++k;
    }
  }

  // �ʂ̎w�W�����߂�
  for (int k = 0, j = 0; j < stacks; ++j) {
    for (int i = 0; i < slices; ++i) {
      int count = (slices + 1) * j + i;

      /* �㔼�� */
      f[k][0] = count;
      f[k][1] = count + 1;
      f[k][2] = count + slices + 2;
      ++k;

      /* ������ */
      f[k][0] = count;
      f[k][1] = count + slices + 2;
      f[k][2] = count + slices + 1;
      ++k;
    }
  }
}

/*
** ������
*/
static void init(void)
{
  // �Q�[���O���t�B�b�N�X���_�̓s���ɂ��ƂÂ�������
  ggInit();

  // �V�F�[�_�v���O�����̓ǂݍ���
  program = loadShader("simple.vert", "simple.frag");

  // attribute �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  pvLoc = glGetAttribLocation(program, "pv");
  nvLoc = glGetAttribLocation(program, "nv");
  
  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  mwLoc = glGetUniformLocation(program, "mw");
  mcLoc = glGetUniformLocation(program, "mc");
  mgLoc = glGetUniformLocation(program, "mg");
  
  // �}�`�f�[�^�̍쐬
  makeSphere(1.0f, SLICES, STACKS, pv, nv, tv, face);

  // �B�ʏ���
  glEnable(GL_DEPTH_TEST);

  // �w�i�F
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

/*
** ���C���v���O����
*/
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);
  init();
  glutMainLoop();
  
  return 0;
}
