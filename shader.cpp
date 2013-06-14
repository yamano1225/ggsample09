#include <iostream>
#include <fstream>

#include "gg.h"
using namespace gg;

#include "shader.h"

//
// シェーダーのソースプログラムの読み込み
//
static GLboolean readShaderSource(GLuint shader, const char *name)
{
  GLint status = GL_FALSE; // 終了ステータス（GL_FALSE ならエラー）

  // ソースファイルを開く
  std::ifstream file(name, std::ios::binary);

  if (file.fail())
  {
    // 開けなかった
    std::cerr << "Error: Can't open source file: " << name << std::endl;
  }
  else
  {
    // ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // ファイルサイズのメモリを確保
    char *buffer = new GLchar[length];

    // ファイルを先頭から読み込む
    file.seekg(0L, std::ios::beg);
    file.read(buffer, length);

    if (file.bad())
    {
      // うまく読み込めなかった
      std::cerr << "Error: Could not read souce file: " << name << std::endl;
    }
    else {
      // シェーダのソースプログラムのシェーダオブジェクトへの読み込み
      const GLchar *source[] = { buffer };
      glShaderSource(shader, 1, source, &length);
      status = GL_TRUE;
    }
    file.close();

    // 読み込みに使ったメモリを開放する
    delete[] buffer;
  }

  return static_cast<GLboolean>(status);
}

//
// シェーダのコンパイル結果の表示
//
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // コンパイル結果を取得する
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

  // シェーダのコンパイル時のログの長さを取得する
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // シェーダのコンパイル時のログの内容を取得する
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return static_cast<GLboolean>(status);
}

//
// シェーダのリンク結果の表示
//
static GLboolean printProgramInfoLog(GLuint program)
{
  // リンク結果を取得する
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error" << std::endl;

  // シェーダのリンク時のログの長さを取得する
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);

  if (bufSize > 1)
  {
    // シェーダのリンク時のログの内容を取得する
    GLchar *infoLog = new GLchar[bufSize];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    std::cerr << infoLog << std::endl;
    delete[] infoLog;
  }

  return static_cast<GLboolean>(status);
}

//
// プログラムオブジェクトの作成
//
//     vsrc: バーテックスシェーダのソースファイル名, pv: attribute の in 変数名
//     fsrc: フラグメントシェーダのソースファイル名, fc: カラーバッファに結合する out 変数名
//
GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc)
{
  // バーテックスシェーダのシェーダオブジェクト
  GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
  readShaderSource(vobj, vsrc);
  glCompileShader(vobj);
  printShaderInfoLog(vobj, "vertex shader");

  // フラグメントシェーダのシェーダオブジェクトの作成
  GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
  readShaderSource(fobj, fsrc);
  glCompileShader(fobj);
  printShaderInfoLog(fobj, "fragment shader");

  // シェーダオブジェクトの取り付け
  GLuint program = glCreateProgram();
  glAttachShader(program, vobj);
  glDeleteShader(vobj);
  glAttachShader(program, fobj);
  glDeleteShader(fobj);

  // プログラムオブジェクトのリンク
  glBindAttribLocation(program, 0, pv);
  glBindFragDataLocation(program, 0, fc);
  glLinkProgram(program);
  printProgramInfoLog(program);

  return program;
}
