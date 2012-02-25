/*
** �Q�[���O���t�B�b�N�X���_�p�⏕�v���O����
**

Copyright (c) 2011 Kohe Tokoi. All Rights Reserved.

Permission is hereby granted, free of charge,  to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction,  including without limitation the rights 
to use, copy,  modify, merge,  publish, distribute,  sublicense,  and/or sell 
copies or substantial portions of the Software.

The above  copyright notice  and this permission notice  shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR 
IMPLIED,  INCLUDING  BUT  NOT LIMITED  TO THE WARRANTIES  OF MERCHANTABILITY, 
FITNESS  FOR  A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN  NO EVENT  SHALL 
KOHE TOKOI  BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY,  WHETHER IN 
AN ACTION  OF CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM,  OUT OF  OR  IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**
*/

#ifndef __GG_H__
#define __GG_H__

#include <cstring>
#include <cmath>

#if defined(WIN32)
#  pragma warning(disable:4996)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  pragma comment(lib, "glew32.lib")
#  include "glew.h"
#  include "wglew.h"
#  include "glut.h"
#elif defined(X11)
#  define GL_GLEXT_PROTOTYPES
#  define GLX_GLXEXT_PROTOTYPES
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glx.h>
#  include <GL/glut.h>
#elif defined(__APPLE__)
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
// GL_ARB_texture_float
#  define GL_RGBA32F GL_RGBA32F_ARB
#  define GL_RGB32F GL_RGB32F_ARB
#  define GL_ALPHA32F GL_ALPHA32F_ARB
#  define GL_INTENSITY32F GL_INTENSITY32F_ARB
#  define GL_LUMINANCE32F GL_LUMINANCE32F_ARB
#  define GL_LUMINANCE_ALPHA32F GL_LUMINANCE_ALPHA32F_ARB
#  define GL_RGBA16F GL_RGBA16F_ARB
#  define GL_RGB16F GL_RGB16F_ARB
#  define GL_ALPHA16F GL_ALPHA16F_ARB
#  define GL_INTENSITY16F GL_INTENSITY16F_ARB
#  define GL_LUMINANCE16F GL_LUMINANCE16F_ARB
#  define GL_LUMINANCE_ALPHA16F GL_LUMINANCE_ALPHA16F_ARB
// GL_EXT_transform_feedback
#  define glBindBufferRange glBindBufferRangeEXT
#  define glBindBufferOffset glBindBufferOffsetEXT
#  define glBindBufferBase glBindBufferBaseEXT
#  define glBeginTransformFeedback glBeginTransformFeedbackEXT
#  define glEndTransformFeedback glEndTransformFeedbackEXT
#  define glTransformFeedbackVaryings glTransformFeedbackVaryingsEXT
#  define glGetTransformFeedbackVarying glGetTransformFeedbackVaryingEXT
#  define glGetIntegerIndexedv glGetIntegerIndexedvEXT
#  define glGetBooleanIndexedv glGetBooleanIndexedvEXT
#  define GL_TRANSFORM_FEEDBACK_BUFFER GL_TRANSFORM_FEEDBACK_BUFFER_EXT
#  define GL_TRANSFORM_FEEDBACK_BUFFER_START GL_TRANSFORM_FEEDBACK_BUFFER_START_EXT
#  define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE GL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT
#  define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING GL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT
#  define GL_INTERLEAVED_ATTRIBS GL_INTERLEAVED_ATTRIBS_EXT
#  define GL_SEPARATE_ATTRIBS GL_SEPARATE_ATTRIBS_EXT
#  define GL_PRIMITIVES_GENERATED GL_PRIMITIVES_GENERATED_EXT
#  define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT
#  define GL_RASTERIZER_DISCARD GL_RASTERIZER_DISCARD_EXT
#  define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT
#  define GL_TRANSFORM_FEEDBACK_VARYINGS GL_TRANSFORM_FEEDBACK_VARYINGS_EXT
#  define GL_TRANSFORM_FEEDBACK_BUFFER_MODE GL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT
#  define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT
// GL_APPLE_vertex_array_object
#  define glGenVertexArrays glGenVertexArraysAPPLE
#  define glBindVertexArray glBindVertexArrayAPPLE
#  define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#  define glIsVertexArray glIsVertexArrayAPPLE
#  define GL_VERTEX_ARRAY_BINDING GL_VERTEX_ARRAY_BINDING_APPLE
#else
#  error "This platform is not supported."
#endif

#define GG_DEG_TO_RAD(a) ((a) * 0.017453293f)

namespace gg
{
  /*
  ** �Q�[���O���t�B�b�N�X���_�̓s���ɂ��ƂÂ�������
  **
  **    OpenGL �̃����_�����O�R���e�L�X�g���쐬��Ɏ��s����
  */
  extern void ggInit(void);

  /*
  ** OpenGL �̃G���[�`�F�b�N
  **
  **    OpenGL �� API ���Ăяo������Ɏ��s����΃G���[�̂���Ƃ��Ƀ��b�Z�[�W��\������
  **    msg �̓��b�Z�[�W�ɏ悶�镶����
  */
  extern void ggError(const char *msg = 0);

  /*
  ** FBO �̃G���[�`�F�b�N
  **
  **    FBO �� API ���Ăяo������Ɏ��s����΃G���[�̂���Ƃ��Ƀ��b�Z�[�W��\������
  **    msg �̓��b�Z�[�W�ɏ悶�镶����
  */
  extern void ggFBOError(const char *msg = 0);

  /*
  ** �ϊ��s��
  */
  class GgMatrix
  {
    // �ϊ��s��̗v�f
    GLfloat array[16];

    // �s�� a �ƃx�N�g�� b �̐ς��x�N�g�� c �ɑ������
    void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

    // �s�� a �ƍs�� b �̐ς��s�� c �ɑ������
    void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

  public:

    // �f�X�g���N�^
    virtual ~GgMatrix(void) {}

    // �R���X�g���N�^
    GgMatrix(void) {}
    GgMatrix(const GLfloat *a)
    {
      load(a);
    }
    GgMatrix(const GgMatrix &m)
    {
      load(m);
    }

    // ���Z�q
    GgMatrix &multiply(const GgMatrix &m, const GgMatrix &n)
    {
      multiply(array, m.array, n.array);
      return *this;
    }
    GgMatrix &multiply(const GgMatrix &m, const GLfloat *a)
    {
      multiply(array, m.array, a);
      return *this;
    }
    GgMatrix &multiply(const GLfloat *a)
    {
      GLfloat t[16]; multiply(t, array, a);
      memcpy(array, t, sizeof array); return *this;
    }
    GgMatrix &multiply(const GgMatrix &m)
    {
      return multiply(m.array);
    }
    GgMatrix &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgMatrix &operator=(const GgMatrix &m)
    {
      return load(m);
    }
    GgMatrix operator*(const GLfloat *a) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgMatrix operator*(const GgMatrix &m) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, m.array);
      return t;
    }
    GgMatrix &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgMatrix &operator*=(const GgMatrix &m)
    {
      return multiply(m);
    }

    // �ϊ��s��̓ǂݍ���
    GgMatrix &load(const GLfloat *a)
    {
      memcpy(array, a, sizeof array);
      return *this;
    }
    GgMatrix &load(const GgMatrix &m)
    {
      return load(m.array);
    }

    // �P�ʍs���ݒ肷��
    GgMatrix &loadIdentity(void);

    // ���s�ړ��̕ϊ��s���ݒ肷��
    GgMatrix &loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadTranslate(const GLfloat *t)
    {
      return loadTranslate(t[0], t[1], t[2], t[3]);
    }

    // �g��k���̕ϊ��s���ݒ肷��
    GgMatrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadScale(const GLfloat *s)
    {
      return loadScale(s[0], s[1], s[2], s[3]);
    }

    // ��]�̕ϊ��s���ݒ肷��
    GgMatrix &loadRotateX(GLfloat a);
    GgMatrix &loadRotateY(GLfloat a);
    GgMatrix &loadRotateZ(GLfloat a);
    GgMatrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgMatrix &loadRotate(const GLfloat *r)
    {
      return loadRotate(r[0], r[1], r[2], r[3]);
    }

    // ����ϊ��s���ݒ肷��
    GgMatrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // ���𓊉e�ϊ��s���ݒ肷��
    GgMatrix &loadOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // �����������e�ϊ��s���ݒ肷��
    GgMatrix &loadFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // ��p���w�肵�ē������e�ϊ��s���ݒ肷��
    GgMatrix &loadPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // �]�u�s���ݒ肷��
    GgMatrix &loadTranspose(const GgMatrix &m);

    // �t�s���ݒ肷��
    GgMatrix &loadInvert(const GgMatrix &m);

    // �@���ϊ��s���ݒ肷��
    GgMatrix &loadNormal(const GgMatrix &m);

    // ���s�ړ��ϊ����悶��
    GgMatrix &translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m; m.loadTranslate(x, y, z, w); multiply(m);
      return *this;
    }
    GgMatrix &translate(const GLfloat *t)
    {
      return translate(t[0], t[1], t[2], t[3]);
    }

    // �g��k���ϊ����悶��
    GgMatrix &scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m;
      m.loadScale(x, y, z, w);
      multiply(m);
      return *this;
    }
    GgMatrix &scale(const GLfloat *s)
    {
      return scale(s[0], s[1], s[2], s[3]);
    }

    // ��]�ϊ����悶��
    GgMatrix &rotateX(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateX(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateY(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateY(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateZ(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateZ(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
    {
      GgMatrix m;
      m.loadRotate(x, y, z, a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(const GLfloat *r)
    {
      return rotate(r[0], r[1], r[2], r[3]);
    }

    // ����ϊ����悶��
    GgMatrix &lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // ���𓊉e�ϊ����悶��
    GgMatrix &orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // �������e�ϊ����悶��
    GgMatrix &frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // ��p���w�肵�ē������e�ϊ����悶��
    GgMatrix &perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // �]�u�s��𓾂�
    GgMatrix transpose(void) const
    {
      GgMatrix t;
      return t.loadTranspose(*this);
    }

    // �t�s��𓾂�
    GgMatrix invert(void) const
    {
      GgMatrix t;
      return t.loadInvert(*this);
    }

    // �@���ϊ��s��𓾂�
    GgMatrix normal(void) const
    {
      GgMatrix t;
      return t.loadNormal(*this);
    }

    // �x�N�g���ɑ΂��ē��e�ϊ����s��
    void projection(GLfloat *c, const GLfloat *v) const
    {
      projection(c, array, v);
    }

    // �ϊ��s��𓾂�
    const GLfloat *get(void) const
    {
      return array;
    }
  };

  /*
  ** �l����
  */
  class GgQuaternion
  {
    // �l�����̗v�f
    GLfloat array[4];

    // �l���� p �Ǝl���� q �̘a���l���� r �ɋ��߂�
    void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� p �Ǝl���� q �̍����l���� r �ɋ��߂�
    void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� p �Ǝl���� q �̐ς��l���� r �ɋ��߂�
    void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // �l���� q ���\����]�̕ϊ��s��� m �ɋ��߂�
    void toMatrix(GLfloat *m, const GLfloat *q) const;

    // ��]�̕ϊ��s�� m ���\���l������ q �ɋ��߂�
    void toQuaternion(GLfloat *q, const GLfloat *m) const;

    // ���ʐ��`��� q �� r �� t �ŕ�Ԃ����l������ p �ɋ��߂�
    void slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const;

  public:

    // �f�X�g���N�^
    virtual ~GgQuaternion(void) {}

    // �R���X�g���N�^
    GgQuaternion(void) {}
    GgQuaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      load(x, y, z, w);
    }
    GgQuaternion(const GLfloat *a)
    {
      load(a);
    }
    GgQuaternion(const GgQuaternion &q)
    {
      load(q);
    }

    // ���Z�q
    GgQuaternion &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgQuaternion &operator=(const GgQuaternion &q)
    {
      return load(q);
    }
    GgQuaternion operator+(const GLfloat *a) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator+(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator+=(const GLfloat *a)
    {
      return add(a);
    }
    GgQuaternion &operator+=(const GgQuaternion &q)
    {
      return add(q);
    }
    GgQuaternion operator-(const GLfloat *a) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator-(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator-=(const GLfloat *a)
    {
      return subtract(a);
    }
    GgQuaternion &operator-=(const GgQuaternion &q)
    {
      return subtract(q);
    }
    GgQuaternion operator*(const GLfloat *a) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator*(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgQuaternion &operator*=(const GgQuaternion &q)
    {
      return multiply(q);
    }

    // �l������ݒ肷��
    GgQuaternion &load(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      array[0] = x;
      array[1] = y;
      array[2] = z;
      array[3] = w;
      return *this;
    }
    GgQuaternion &load(const GLfloat *a)
    {
      return load(a[0], a[1], a[2], a[3]);
    }
    GgQuaternion &load(const GgQuaternion &q)
    {
      return load(q.array);
    }

    // ��]�̕ϊ��s�� m ��\���l������ݒ肷��
    GgQuaternion &loadMatrix(const GLfloat *m)
    {
      toQuaternion(array, m); return *this;
    }

    // �P�ʌ���ݒ肷��
    GgQuaternion &loadIdentity(void)
    {
      return load(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // (x, y, z) �����Ƃ��Ċp�x a ��]���鎑������ݒ肷��
    GgQuaternion &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgQuaternion &loadRotate(const GLfloat *v, GLfloat a)
    {
      return loadRotate(v[0], v[1], v[2], a);
    }

    // �I�C���[�p (h, p, r) �ŗ^����ꂽ��]��\���l������ݒ肷��
    GgQuaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
    GgQuaternion &loadEuler(const GLfloat *e)
    {
      return loadEuler(e[0], e[1], e[2]);
    }

    // �l�����̘a�����߂�
    GgQuaternion &add(const GgQuaternion &p, const GgQuaternion &q)
    {
      add(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &add(const GgQuaternion &q, const GLfloat *a)
    {
      add(array, q.array, a);
      return *this;
    }
    GgQuaternion &add(const GLfloat *a)
    {
      GLfloat t[4];
      add(t, array, a);
      return load(t);
    }
    GgQuaternion &add(const GgQuaternion &q)
    {
      return add(q.array);
    }

    // �l�����̍������߂�
    GgQuaternion &subtract(const GgQuaternion &p, const GgQuaternion &q)
    {
      subtract(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &subtract(const GgQuaternion &q, const GLfloat *a)
    {
      subtract(array, q.array, a);
      return *this;
    }
    GgQuaternion &subtract(const GLfloat *a)
    {
      GLfloat t[4];
      subtract(t, array, a);
      return load(t);
    }
    GgQuaternion &subtract(const GgQuaternion &q)
    {
      return subtract(q.array);
    }

    // �l�����̐ς����߂�
    GgQuaternion &multiply(const GgQuaternion &p, const GgQuaternion &q)
    {
      multiply(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &multiply(const GgQuaternion &q, const GLfloat *a)
    {
      multiply(array, q.array, a);
      return *this;
    }
    GgQuaternion &multiply(const GLfloat *a)
    {
      GLfloat t[4]; multiply(t, array, a);
      return load(t);
    }
    GgQuaternion &multiply(const GgQuaternion &q)
    {
      return multiply(q.array);
    }

    // ���ʐ��`���
    GgQuaternion &slerp(const GgQuaternion &q, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, q.array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &q, const GLfloat *b, GLfloat t)
    {
      slerp(array, q.array, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, a, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GLfloat *b, GLfloat t)
    {
      slerp(array, a, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &r, GLfloat t)
    {
      slerp(array, array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(GLfloat *b, GLfloat t)
    {
      slerp(array, array, b, t);
      return *this;
    }

    // �l�����̃m���������߂�
    GLfloat norm(void) const;

    // �����l���������߂�
    GgQuaternion conjugate(void) const;

    // �l�����̋t�����߂�
    GgQuaternion invert(void) const;

    // �l�����𐳋K������
    GgQuaternion normalize(void) const;

    // �l���������߂�
    const GLfloat *get(void) const
    {
      return array;
    }
    void get(GLfloat *a) const
    {
      a[0] = array[0];
      a[1] = array[1];
      a[2] = array[2];
      a[3] = array[3];
    }

    // �l�������\����]�̍s��� m �ɋ��߂�
    void getMatrix(GLfloat *m) const
    {
      toMatrix(m, array);
    }
  };

  /*
  ** �e�N�X�`��
  **
  **    �g�U���ːF�e�N�X�`����ǂݍ���Ńe�N�X�`���I�u�W�F�N�g���쐬����
  */
  class GgTexture
  {
    // �e�N�X�`����
    GLuint texture;

  public:

    // �f�X�g���N�^
    virtual ~GgTexture(void)
    {
      glDeleteTextures(1, &texture);
    }

    // �R���X�g���N�^
    GgTexture(void)
    {
      glGenTextures(1, &texture);
    }

    // �R���X�g���N�^
    GgTexture(
      const char *filename,               // �摜�t�@�C�����i3/4 �`���l���� RAW �摜�j
      int width, int height,              // �摜�̕��ƍ����i2^n ��f�j
      GLenum format = GL_RGB              // �ǂݍ��މ摜�̏��� (GL_RGB/GL_RGBA)
      )
    {
      glGenTextures(1, &texture);
      load(filename, width, height, format);
    }

    // �R�s�[�R���X�g���N�^
    GgTexture(const GgTexture &o)
      : texture(o.texture) {}

    // ������Z�q
    GgTexture &operator=(const GgTexture &o)
    {
      if (this != &o)
      {
        glDeleteTextures(1, &texture);
        texture = o.texture;
      }

      return *this;
    }

    // �g�U���ːF�e�N�X�`����ǂݍ���
    //    filename: �t�@�C����, width, height: ���ƍ��� (2^n), format: GL_RGB �� GL_RGBA
    void load(const char *filename, int width, int height, GLenum format = GL_RGB) const;

    // �e�N�X�`���I�u�W�F�N�g���g�p����
    void bind(void) const
    {
      glBindTexture(GL_TEXTURE_2D, texture);
    }
    
    // �e�N�X�`���I�u�W�F�N�g�����擾����
    GLuint tex(void) const
    {
      return texture;
    }
  };

  /*
  ** �@���}�b�v
  **
  **    �����}�b�v�i�O���C�X�P�[���摜�j��ǂݍ���Ŗ@���}�b�v���쐬����
  */
  class GgNormalTexture
    : public GgTexture
  {
  public:

    // �f�X�g���N�^
    virtual ~GgNormalTexture(void) {}

    // �R���X�g���N�^
    GgNormalTexture(void) {}

    // �R���X�g���N�^
    GgNormalTexture(
      const char *filename,               // �摜�t�@�C�����i1 �`���l���� RAW �摜�j
      int width, int height,              // �摜�̕��ƍ����i2^n ��f�j
      float nz = 1.0f                     // �@���}�b�v�� z �����̒l
      ) : GgTexture()                     // �e�N�X�`���I�u�W�F�N�g���쐬����
    {
      load(filename, width, height, nz);
    }

    // �R�s�[�R���X�g���N�^
    GgNormalTexture(const GgNormalTexture &o)
      : GgTexture(o) {}

    // ������Z�q
    GgNormalTexture &operator=(const GgNormalTexture &o)
    {
      if (this != &o)
      {
        GgTexture::operator=(o);
      }

      return *this;
    }

    // �����}�b�v��ǂݍ���Ŗ@���}�b�v���쐬����
    //    filename: �t�@�C����, width, height: ���ƍ��� (2^n), nz: �@���}�b�v�� z �����̒l
    void load(const char *filename, int width, int height, float nz = 1.0f) const;
  };

  /*
  ** �V�F�[�_
  **
  **    �V�F�[�_�̊��N���X
  */
  class GgShader
  {
    // �v���O������
    GLuint program;

    // �V�F�[�_�̃\�[�X�v���O������ǂݍ���
    bool readShaderSource(GLuint shader, const char *filename) const;

    // �V�F�[�_�̃\�[�X�v���O�����̃R���p�C������\������
    void printShaderInfoLog(GLuint shader) const;

    // �V�F�[�_�̃I�u�W�F�N�g�v���O�����̃����N����\������
    void printProgramInfoLog(GLuint program) const;

  public:

    // �f�X�g���N�^
    virtual ~GgShader(void)
    {
      glDeleteProgram(program);
    }

    // �R���X�g���N�^
    GgShader(void)
      : program(glCreateProgram()) {}

    // �R���X�g���N�^
    GgShader(
      const char *vert,                   // �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
      const char *frag = 0,               // �t���O�����g�V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      const char *geom = 0,               // �W�I���g���V�F�[�_�̃\�[�X�t�@�C�����i0 �Ȃ�s�g�p�j
      GLenum input = GL_TRIANGLES,        // �W�I���g���V�F�[�_�̓��̓v���~�e�B�u
      GLenum output = GL_TRIANGLE_STRIP,  // �W�I���g���V�F�[�_�̏o�̓v���~�e�B�u
      int nvarying = 0,                   // �t�B�[�h�o�b�N���� varying �ϐ��̐��i0 �Ȃ�s�g�p�j
      const char **varyings = 0           // �t�B�[�h�o�b�N���� varying �ϐ��̃��X�g
      )
      : program(glCreateProgram())
    {
      load(vert, frag, geom, input, output, nvarying, varyings);
    }

    // �R�s�[�R���X�g���N�^
    GgShader(const GgShader &o)
      : program(o.program) {}

    // ������Z�q
    GgShader &operator=(const GgShader &o)
    {
      if (this != &o)
      {
        glDeleteProgram(program);
        program = o.program;
      }

      return *this;
    }

    // �V�F�[�_�̃\�[�X�v���O������ǂݍ���ŃR���p�C���E�����N���ăv���O�����I�u�W�F�N�g���쐬����
    bool load(const char *vert, const char *frag = 0, const char *geom = 0,
      GLenum input = GL_TRIANGLES, GLenum output = GL_TRIANGLE_STRIP,
      int nvarying = 0, const char **varyings = 0) const;

    // �v���O�����I�u�W�F�N�g���g�p����
    void use(void) const
    {
      glUseProgram(program);
    }
    
    // �v���O�����I�u�W�F�N�g�����擾����
    GLuint getProgram(void) const
    {
      return program;
    }
  };

  /*
  ** �o�b�t�@�I�u�W�F�N�g
  **
  **    ���_�^�C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�̊��N���X
  */
  template <typename T> class GgBuffer
  {
    // �o�b�t�@�I�u�W�F�N�g
    GLuint buffer;

    // �f�[�^��
    unsigned int number;

  public:

    // �f�X�g���N�^
    virtual ~GgBuffer<T>(void)
    {
      glDeleteBuffers(1, &buffer);
    }

    // �R���X�g���N�^
    GgBuffer<T>(void)
      : number(0)
    {
      glGenBuffers(1, &buffer);
    }

    // �R���X�g���N�^
    GgBuffer<T>(GLenum target, unsigned int n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      glGenBuffers(1, &buffer);
      load(target, n, data, usage);
    }

    // �R�s�[�R���X�g���N�^
    GgBuffer<T>(const GgBuffer<T> &o)
    {
      buffer = o.buffer;
      number = o.number;
    }

    // ������Z�q
    GgBuffer<T> &operator=(const GgBuffer<T> &o)
    {
      if (this != &o)
      {
        glDeleteBuffers(1, &buffer);
        buffer = o.buffer;
        number = o.number;
      }

      return *this;
    }

    // �f�[�^�̎擾
    void load(GLenum target, unsigned int n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      number = n;
      glBindBuffer(target, buffer);
      glBufferData(target, sizeof (T) * n, data, usage);
    }

    // �o�b�t�@�I�u�W�F�N�g���𓾂�
    GLuint buf(void) const
    {
      return buffer;
    }

    // �f�[�^�̐��𓾂�
    unsigned int num(void) const
    {
      return number;
    }
  };

  /*
  ** �_�Q
  **
  **    ���_�o�b�t�@�I�u�W�F�N�g���g�p����`��f�[�^�̂��߂̊��N���X
  */
  class GgPoints
  {
    // ���_�o�b�t�@�I�u�W�F�N�g
    GgBuffer<GLfloat[3]> position;
    
  protected:

    // �o�b�t�@�I�u�W�F�N�g���𓾂�
    GLuint pbuf(void) const
    {
      return position.buf();
    }

    // �f�[�^�̐��𓾂�
    unsigned int pnum(void) const
    {
      return position.num();
    }

  public:
    
    // �f�X�g���N�^
    virtual ~GgPoints(void) {}
    
    // �R���X�g���N�^
    GgPoints(void) {}
    
    // �R���X�g���N�^
    //    n: ���_��, pos: ���_�̈ʒu
    GgPoints(int n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      load(n, pos, usage);
    }

    // �R�s�[�R���X�g���N�^
    GgPoints(const GgPoints &o)
      : position(o.position) {}

    // ������Z�q
    GgPoints &operator=(const GgPoints &o)
    {
      if (this != &o)
      {
        position = o.position;
      }

      return *this;
    }
    
    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ē��_���i�[����
    //    n: ���_��, pos: ���_�̈ʒu
    void load(int n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      position.load(GL_ARRAY_BUFFER, n, pos, usage);
    }

    // �_�Q��`�悷��葱��
    virtual void draw(GLint pvLoc, GLenum mode = GL_POINTS);
  };
  
  /*
  ** �O�p�`�Q
  **
  **    ���_�����݂̂ŕ\���ꂽ�}�`�̂��߂̊��N���X
  */
  class GgTriangles
    : public GgPoints
  {
    // �@���̒��_�o�b�t�@�I�u�W�F�N�g
    GgBuffer<GLfloat[3]> normal;

    // ���_�����̏ꏊ
    GLint location;

  protected:

    // �o�b�t�@�I�u�W�F�N�g���𓾂�
    GLuint nbuf(void) const
    {
      return normal.buf();
    }

    // �f�[�^�̐��𓾂�
    unsigned int nnum(void) const
    {
      return normal.num();
    }

  public:

    // �f�X�g���N�^
    virtual ~GgTriangles(void) {}

    // �R���X�g���N�^
    GgTriangles(void) {}

    // �R���X�g���N�^
    //    n: ���_��, pos: ���_�̈ʒu, norm: ���_�̖@��
    GgTriangles(int n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
      : GgPoints(n, pos, usage)
    {
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
    }

    // �R�s�[�R���X�g���N�^
    GgTriangles(const GgTriangles &o)
      : GgPoints(o), normal(o.normal) {}

    // ������Z�q
    GgTriangles &operator=(const GgTriangles &o)
    {
      if (this != &o)
      {
        GgPoints::operator=(o);
        normal = o.normal;
      }

      return *this;
    }
    
    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ĉʒu�Ɩ@�����i�[����
    //    n: ���_��, pos: ���_�̈ʒu, norm: ���_�̖@��
    void load(int n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgPoints::load(n, pos, usage);
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
    }

    // �O�p�`�Q��`�悷��葱��
    virtual void draw(GLint pvLoc, GLint nvLoc, GLenum mode = GL_TRIANGLES);
  };

  /*
  ** ��`
  **
  **    xy ���ʏ�̋�`�̌`��f�[�^
  */
  class GgRectangle
    : public GgTriangles
  {
  public:
    
    // �f�X�g���N�^
    virtual ~GgRectangle(void) {}
    
    // �R���X�g���N�^
    GgRectangle(GLfloat w = 2.0f, GLfloat h = 2.0f)
    {
      resize(w, h);
    }
    
    // �R�s�[�R���X�g���N�^
    GgRectangle(const GgRectangle &o)
      : GgTriangles(o) {}
    
    // ������Z�q
    GgRectangle &operator=(const GgRectangle &o)
    {
      if (this != &o)
      {
        GgTriangles::operator=(o);
      }

      return *this;
    }
    
    // ��`�̃T�C�Y��ύX����
    //    w, h: ��`�̕��ƍ���
    void resize(GLfloat w, GLfloat h);

    // �O�p�`�Q��`�悷��葱��
    virtual void draw(GLint pvLoc, GLint nvLoc, GLenum mode = GL_TRIANGLE_FAN)
    {
      GgTriangles::draw(pvLoc, nvLoc, mode);
    }
  };

  /*
  ** �ȉ~�`
  **
  **    �O�p�`�̌`��f�[�^�ŕ\���� xy ���ʏ�̑ȉ~�`
  */
  class GgEllipse
    : public GgTriangles
  {
  public:

    // �f�X�g���N�^
    virtual ~GgEllipse(void) {}

    // �R���X�g���N�^
    GgEllipse(GLfloat w = 2.0f, GLfloat h = 2.0f, int slices = 16)
    {
      resize(w, h, slices);
    }

    // �R�s�[�R���X�g���N�^
    GgEllipse(const GgEllipse &o)
      : GgTriangles(o) {}

    // ������Z�q
    GgEllipse &operator=(const GgEllipse &o)
    {
      if (this != &o)
      {
        GgTriangles::operator=(o);
      }

      return *this;
    }

    // �ȉ~�`�̃T�C�Y�ƕ�������ύX����
    //    w: �ȉ~�`�̕�, h: �ȉ~�`�̍���, slices: �ӂ̐��i�������j
    void resize(GLfloat w, GLfloat h, int slices = 16);

    // �O�p�`�Q��`�悷��葱��
    virtual void draw(GLint pvLoc, GLint nvLoc, GLenum mode = GL_TRIANGLE_FAN)
    {
      GgTriangles::draw(pvLoc, nvLoc, mode);
    }
  };

  /*
  ** �O�p�`���b�V��
  **
  **    ���_�C���f�b�N�X���g�p����}�`�̂��߂̊��N���X
  */
  class GgMesh
    : public GgTriangles
  {
    // �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
    GgBuffer<GLuint[3]> index;

  protected:

    // �o�b�t�@�I�u�W�F�N�g���𓾂�
    GLuint fbuf(void) const
    {
      return index.buf();
    }

    // �f�[�^�̐��𓾂�
    unsigned int fnum(void) const
    {
      return index.num();
    }

  public:

    // �f�X�g���N�^
    virtual ~GgMesh(void) {}

    // �R���X�g���N�^
    GgMesh(void) {}

    // �R���X�g���N�^
    //    n: ���_��, pos: ���_�̈ʒu, norm:���_�̖@��
    //    f: �ʐ�, face: ���_�̃C���f�b�N�X�f�[�^
    GgMesh(int n, int f, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
      : GgTriangles(n, pos, norm, usage)
    {
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }

    // �R�s�[�R���X�g���N�^
    GgMesh(const GgMesh &o)
      : GgTriangles(o), index(o.index) {}

    // ������Z�q
    GgMesh &operator=(const GgMesh &o)
    {
      if (this != &o)
      {
        GgTriangles::operator=(o);
        index = o.index;
      }

      return *this;
    }

    // �o�b�t�@�I�u�W�F�N�g���m�ۂ��Ĉʒu�Ɩ@���ƃC���f�b�N�X���i�[����
    //    n: ���_��, pos: ���_�̈ʒu, norm:���_�̖@��
    //    f: �ʐ�, face: ���_�̃C���f�b�N�X�f�[�^
    void load(int n, int f, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgTriangles::load(n, pos, norm, usage);
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }

    // �O�p�`���b�V����`�悷��葱��
    virtual void draw(GLint pvLoc, GLint nvLoc, GLenum mode = GL_TRIANGLES);
  };

  /*
  ** ��
  **
  **    �O�p�`�̌`��f�[�^�ŕ\�������_�ɂ��鋅
  */
  class GgSphere
    : public GgMesh
  {
  public:

    // �f�X�g���N�^
    virtual ~GgSphere(void) {}

    // �R���X�g���N�^
    //    �T�C�Y���w�肵�ċ��̃C���X�^���X���쐬����
    //    diameter: ���a, slices: �o�x�����̕�����, stacks: �ܓx�����̕�����
    GgSphere(GLfloat diameter = 1.0f, int slices = 16, int stacks = 8)
    {
      resize(diameter, slices, stacks);
    }

    // �R�s�[�R���X�g���N�^
    GgSphere(const GgSphere &o)
      : GgMesh(o) {}
    
    // ������Z�q
    GgSphere &operator=(const GgSphere &o)
    {
      if (this != &o)
      {
        GgMesh::operator=(o);
      }
      
      return *this;
    }

    // ���̃T�C�Y�ƕ�������ύX����
    //    diameter: ���a, slices: �o�x�����̕�����, stacks: �ܓx�����̕�����
    void resize(GLfloat diameter = 1.0f, int slices = 16, int stacks = 8);
  };
  
  /*
  ** �O�p�`�������ꂽ Alias OBJ �`���̃f�[�^
  **
  **    �O�p�`�������ꂽ Alias OBJ �`���̃f�[�^�ɂ��O�p�`�̌`��f�[�^
  */
  class GgObj
    : public GgMesh
  {
  public:

    // �f�X�g���N�^
    virtual ~GgObj(void) {}

    // �R���X�g���N�^
    GgObj(void) {}

    // �R���X�g���N�^
    //    Alias OBJ �`���̃t�@�C����ǂݍ���ŃC���X�^���X���쐬����
    //    filename: �t�@�C����, scale: 0 �łȂ���Β��S�����_�ɂ��Ċe�������̑傫���̍ő�l�� scale �ɂ���
    GgObj(const char *filename, GLfloat scale = 0.0f)
    {
      loadfile(filename, scale);
    }

     // �R�s�[�R���X�g���N�^
    GgObj(const GgObj &o)
      : GgMesh(o) {}

    // ������Z�q
    GgObj &operator=(const GgObj &o)
    {
      if (this != &o)
      {
        GgMesh::operator=(o);
      }
      
      return *this;
    }
    
    // Alias OBJ �`���̃t�@�C����ǂݍ���
    //    filename: �t�@�C����, scale: 0 �łȂ���Β��S�����_�ɂ��Ċe�������̑傫���̍ő�l�� scale �ɂ���
    bool loadfile(const char *filename, GLfloat scale = 0.0f);
  };

  /*
  ** �ȈՃg���b�N�{�[������
  */
  class GgTrackball
  {
    int cx, cy;       // �h���b�O�J�n�ʒu
    bool drag;        // �h���b�O�����ۂ�
    float sx, sy;     // �}�E�X�̐�Έʒu���E�B���h�E���ł̑��Έʒu�̊��Z�W��
    GgQuaternion cq;  // ��]�̏����l (�l����)
    GgQuaternion tq;  // �h���b�O���̉�] (�l����)
    GLfloat rt[16];   // ��]�̕ϊ��s��

  public:

    // �f�X�g���N�^
    ~GgTrackball(void) {}

    // �R���X�g���N�^
    GgTrackball(void);

    // �g���b�N�{�[�������͈͎̔w��
    //    �E�B���h�E�̃��T�C�Y���ɌĂяo��
    void region(int w, int h);

    // �g���b�N�{�[�������̊J�n
    //    �}�E�X�̃h���b�O�J�n���i�}�E�X�{�^�����������Ƃ��j�ɌĂяo��
    void start(int x, int y);

    // ��]�̕ϊ��s��̌v�Z
    //    �}�E�X�̃h���b�O���ɌĂяo��
    void motion(int x, int y);

    // �g���b�N�{�[�������̒�~
    //    �}�E�X�̃h���b�O�I�����i�}�E�X�{�^���𗣂����Ƃ��j�ɌĂяo��
    void stop(int x, int y);

    // ���݂̉�]�̕ϊ��s��𓾂�
    const GLfloat *get(void) const
    {
      return rt;
    }
  };
}

#endif
