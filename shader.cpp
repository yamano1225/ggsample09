#include <iostream>
#include <fstream>

#include "gg.h"
using namespace gg;

#include "shader.h"

//
// �V�F�[�_�[�̃\�[�X�v���O�����̓ǂݍ���
//
static GLboolean readShaderSource(GLuint shader, const char *name)
{
  GLint status = GL_FALSE; // �I���X�e�[�^�X�iGL_FALSE �Ȃ�G���[�j

  // �\�[�X�t�@�C�����J��
  std::ifstream file(name, std::ios::binary);

  if (file.fail())
  {
    // �J���Ȃ�����
    std::cerr << "Error: Can't open source file: " << name << std::endl;
  }
  else
  {
    // �t�@�C���̖����Ɉړ������݈ʒu�i���t�@�C���T�C�Y�j�𓾂�
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // �t�@�C���T�C�Y�̃��������m��
    char *buffer = new GLchar[length];

    // �t�@�C����擪����ǂݍ���
    file.seekg(0L, std::ios::beg);
    file.read(buffer, length);

    if (file.bad())
    {
      // ���܂��ǂݍ��߂Ȃ�����
      std::cerr << "Error: Could not read souce file: " << name << std::endl;
    }
    else {
      // �V�F�[�_�̃\�[�X�v���O�����̃V�F�[�_�I�u�W�F�N�g�ւ̓ǂݍ���
      const GLchar *source[] = { buffer };
      glShaderSource(shader, 1, source, &length);
      status = GL_TRUE;
    }
    file.close();

    // �ǂݍ��݂Ɏg�������������J������
    delete[] buffer;
  }

  return static_cast<GLboolean>(status);
}

//
// �V�F�[�_�̃R���p�C�����ʂ̕\��
//
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // �R���p�C�����ʂ��擾����
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

  // �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return static_cast<GLboolean>(status);
}

//
// �V�F�[�_�̃����N���ʂ̕\��
//
static GLboolean printProgramInfoLog(GLuint program)
{
  // �����N���ʂ��擾����
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error" << std::endl;

  // �V�F�[�_�̃����N���̃��O�̒������擾����
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // �V�F�[�_�̃����N���̃��O�̓��e���擾����
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return static_cast<GLboolean>(status);
}

//
// �v���O�����I�u�W�F�N�g�̍쐬
//
//     vsrc: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����, pv: attribute �� in �ϐ���
//     fsrc: �t���O�����g�V�F�[�_�̃\�[�X�t�@�C����, fc: �J���[�o�b�t�@�Ɍ������� out �ϐ���
//
GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc)
{
  // �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  readShaderSource(vobj, vsrc);
  glCompileShader(vobj);
  printShaderInfoLog(vobj, "vertex shader");

  // �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g�̍쐬
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  readShaderSource(fobj, fsrc);
  glCompileShader(fobj);
  printShaderInfoLog(fobj, "fragment shader");

  // �V�F�[�_�I�u�W�F�N�g�̎��t��
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // �v���O�����I�u�W�F�N�g�̃����N
  glBindAttribLocation(program, 0, pv);
  glBindFragDataLocation(program, 0, fc);
  glLinkProgram(program);
  printProgramInfoLog(program);

  return program;
}
