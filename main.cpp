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
  GgElements *sphere = ggElementsSphere(1.0f, SLICES, STACKS);

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

    // ���f���r���[�ϊ��s��
    GgMatrix mw = mv.rotateY(12.56637f * t);

    // �@���ϊ��s��
    GgMatrix mg = mw.normal();

    // ���f���r���[�E���e�ϊ�
    GgMatrix mc = mp * mw;

    // uniform �ϐ���ݒ肷��
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());

    // �}�`�̕`��
    sphere->draw();

    // �_�u���o�b�t�@�����O
    glfwSwapBuffers();
  }

  return 0;
}
