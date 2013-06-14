#include <iostream>
#include <cmath>

// �⏕�v���O����
#include "gg.h"
using namespace gg;

// �A�j���[�V�����̎����i�b�j
#define CYCLE 5.0

// ���̃f�[�^�̕�����
#define SLICES 64
#define STACKS 32

// ���̃f�[�^�̒��_���Ɩʐ�
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

//
// ���̃f�[�^�̍쐬
//
static void makeSphere(float radius, int slices, int stacks,
  GLfloat (*pv)[3], GLfloat (*nv)[3], GLfloat (*tv)[2], GLuint (*f)[3])
{
  // ���_�̈ʒu�ƃe�N�X�`�����W�����߂�
  for (int k = 0, j = 0; j <= stacks; ++j)
  {
    float t = (float)j / (float)stacks;
    float ph = 3.141593f * t;
    float y = cosf(ph);
    float r = sinf(ph);

    for (int i = 0; i <= slices; ++i)
    {
      float s = (float)i / (float)slices;
      float th = -2.0f * 3.141593f * s;
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
  for (int k = 0, j = 0; j < stacks; ++j)
  {
    for (int i = 0; i < slices; ++i)
    {
      int count = (slices + 1) * j + i;

      // �㔼���̎O�p�`
      f[k][0] = count;
      f[k][1] = count + slices + 2;
      f[k][2] = count + 1;
      ++k;

      // �������̎O�p�`
      f[k][0] = count;
      f[k][1] = count + slices + 1;
      f[k][2] = count + slices + 2;
      ++k;
    }
  }
}

//
// �����ݒ�
//
static int init(void)
{
  // GLFW ������������
  if (glfwInit() == GL_FALSE)
  {
    // �������Ɏ��s����
    std::cerr << "Error: Failed to initialize GLFW." << std::endl;
    return 1;
  }

  // OpenGL Version 3.2 Core Profile ��I������
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // �E�B���h�E���J��
  if (glfwOpenWindow(0, 0, 0, 0, 0, 0, 24, 0, GLFW_WINDOW) == GL_FALSE)
  {
    // �E�B���h�E���J���Ȃ�����
    std::cerr << "Error: Failed to open GLFW window." << std::endl;
    return 1;
  }

  // �J�����E�B���h�E�ɑ΂���ݒ�
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // �⏕�v���O�����ɂ�鏉����
  ggInit();

  // �w�i�F
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // �B�ʏ���
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // ����������
  return 0;
}

// �������e�ϊ��s��
static GgMatrix mp;

//
// �E�B���h�E�̃T�C�Y�ύX���̏���
//
static void GLFWCALL resize(int w, int h)
{
  // �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
  glViewport(0, 0, w, h);

  // �������e�ϊ��s������߂�i�A�X�y�N�g�� w / h�j
  mp.loadPerspective(0.5f, (float)w / (float)h, 1.0f, 20.0f);
}

//
// ���C���v���O����
//
int main(int argc, const char * argv[])
{
  // �����ݒ�
  if (init()) return 1;

  // �v���O�����I�u�W�F�N�g�̍쐬
  GLuint program = ggLoadShader("simple.vert", "simple.frag");

  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  GLint mwLoc = glGetUniformLocation(program, "mw");
  GLint mcLoc = glGetUniformLocation(program, "mc");
  GLint mgLoc = glGetUniformLocation(program, "mg");

  // �r���[�ϊ��s��� mv �ɋ��߂�
  GgMatrix mv;
  mv.loadLookat(0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  // �}�`�f�[�^�̍쐬
  GLfloat pv[VERTICES][3];
  GLfloat nv[VERTICES][3];
  GLfloat tv[VERTICES][2];
  GLuint face[FACES][3];
  makeSphere(1.0f, SLICES, STACKS, pv, nv, tv, face);

  // ���_�z��I�u�W�F�N�g�̍쐬
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�o�b�t�@�I�u�W�F�N�g�̍쐬
  GLuint vbo[4];
  glGenBuffers(4, vbo);

  // ���_�̍��W�l pv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� pv (index == 0) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // ���_�̐F nv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof nv, nv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� nv (index == 1) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // ���_�̍��W�l tv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof tv, tv, GL_STATIC_DRAW);

  // ���_�̃C���f�b�N�X face �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof face, face, GL_STATIC_DRAW);

  // �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̐ݒ�
  glfwSetWindowSizeCallback(resize);

  // �o�ߎ��Ԃ̃��Z�b�g
  glfwSetTime(0.0);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p�J�n
    glUseProgram(program);

    // �����̌v��
    float t = static_cast<float>(fmod(glfwGetTime(), CYCLE) / CYCLE);

    // ���f���ϊ��s�� (���� t �ɂ��ƂÂ���]�A�j���[�V����)
    GgMatrix mm;
    mm.loadRotateY(12.56637f * t);

    // ���f���r���[�ϊ��s��
    GgMatrix mw = mv * mm;

    // �@���ϊ��s��
    GgMatrix mg;
    mg.loadNormal(mw);

    // ���f���r���[�E���e�ϊ�
    GgMatrix mc = mp * mw;

    // uniform �ϐ���ݒ肷��
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());

    // �`��Ɏg�����_�z��I�u�W�F�N�g�̎w��
    glBindVertexArray(vao);

    // �}�`�̕`��
    glDrawElements(GL_TRIANGLES, FACES * 3, GL_UNSIGNED_INT, 0);

    // ���_�z��I�u�W�F�N�g�̎w�����
    glBindVertexArray(0);

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    // �_�u���o�b�t�@�����O
    glfwSwapBuffers();
  }

  return 0;
}
