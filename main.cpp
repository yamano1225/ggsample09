#include <iostream>
#include <cmath>

// 補助プログラム
#include "gg.h"
using namespace gg;

// アニメーションの周期（秒）
#define CYCLE 5.0

// 球のデータの分割数
#define SLICES 64
#define STACKS 32

//
// 初期設定
//
static int init(void)
{
  // GLFW を初期化する
  if (glfwInit() == GL_FALSE)
  {
    // 初期化に失敗した
    std::cerr << "Error: Failed to initialize GLFW." << std::endl;
    return 1;
  }

  // OpenGL Version 3.2 Core Profile を選択する
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ウィンドウを開く
  if (glfwOpenWindow(0, 0, 0, 0, 0, 0, 24, 0, GLFW_WINDOW) == GL_FALSE)
  {
    // ウィンドウが開けなかった
    std::cerr << "Error: Failed to open GLFW window." << std::endl;
    return 1;
  }

  // 開いたウィンドウに対する設定
  glfwSwapInterval(1);
  glfwSetWindowTitle("sample");

  // 補助プログラムによる初期化
  ggInit();

  // 背景色
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // 隠面消去
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // 初期化成功
  return 0;
}

// 透視投影変換行列
static GgMatrix mp;

//
// ウィンドウのサイズ変更時の処理
//
static void GLFWCALL resize(int w, int h)
{
  // ウィンドウ全体をビューポートにする
  glViewport(0, 0, w, h);

  // 透視投影変換行列を求める（アスペクト比 w / h）
  mp.loadPerspective(0.5f, (float)w / (float)h, 1.0f, 20.0f);
}

//
// メインプログラム
//
int main(int argc, const char * argv[])
{
  // 初期設定
  if (init()) return 1;

  // プログラムオブジェクトの作成
  GLuint program = ggLoadShader("simple.vert", "simple.frag");

  // uniform 変数のインデックスの検索（見つからなければ -1）
  GLint mwLoc = glGetUniformLocation(program, "mw");
  GLint mcLoc = glGetUniformLocation(program, "mc");
  GLint mgLoc = glGetUniformLocation(program, "mg");

  // ビュー変換行列を mv に求める
  GgMatrix mv;
  mv.loadLookat(0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  // 図形データの作成
  GgElements *sphere = ggElementsSphere(1.0f, SLICES, STACKS);

  // ウィンドウのサイズ変更時に呼び出す処理の設定
  glfwSetWindowSizeCallback(resize);

  // 経過時間のリセット
  glfwSetTime(0.0);

  // ウィンドウが開いている間くり返し描画する
  while (glfwGetWindowParam(GLFW_OPENED))
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // シェーダプログラムの使用開始
    glUseProgram(program);

    // 時刻の計測
    float t = static_cast<float>(fmod(glfwGetTime(), CYCLE) / CYCLE);

    // モデルビュー変換行列
    GgMatrix mw = mv.rotateY(12.56637f * t);

    // 法線変換行列
    GgMatrix mg = mw.normal();

    // モデルビュー・投影変換
    GgMatrix mc = mp * mw;

    // uniform 変数を設定する
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());

    // 図形の描画
    sphere->draw();

    // ダブルバッファリング
    glfwSwapBuffers();
  }

  return 0;
}
