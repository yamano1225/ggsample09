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

// 球のデータの頂点数と面数
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

//
// 球のデータの作成
//
static void makeSphere(float radius, int slices, int stacks,
  GLfloat (*pv)[3], GLfloat (*nv)[3], GLfloat (*tv)[2], GLuint (*f)[3])
{
  // 頂点の位置とテクスチャ座標を求める
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

      // 頂点の座標値
      pv[k][0] = x * radius;
      pv[k][1] = y * radius;
      pv[k][2] = z * radius;

      // 頂点の法線ベクトル
      nv[k][0] = x;
      nv[k][1] = y;
      nv[k][2] = z;

      // 頂点のテクスチャ座標値
      tv[k][0] = s;
      tv[k][1] = t;

      ++k;
    }
  }

  // 面の指標を求める
  for (int k = 0, j = 0; j < stacks; ++j)
  {
    for (int i = 0; i < slices; ++i)
    {
      int count = (slices + 1) * j + i;

      // 上半分の三角形
      f[k][0] = count;
      f[k][1] = count + slices + 2;
      f[k][2] = count + 1;
      ++k;

      // 下半分の三角形
      f[k][0] = count;
      f[k][1] = count + slices + 1;
      f[k][2] = count + slices + 2;
      ++k;
    }
  }
}

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
  GLfloat pv[VERTICES][3];
  GLfloat nv[VERTICES][3];
  GLfloat tv[VERTICES][2];
  GLuint face[FACES][3];
  makeSphere(1.0f, SLICES, STACKS, pv, nv, tv, face);

  // 頂点配列オブジェクトの作成
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // 頂点バッファオブジェクトの作成
  GLuint vbo[4];
  glGenBuffers(4, vbo);

  // 頂点の座標値 pv 用のバッファオブジェクト
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);

  // 結合されている頂点バッファオブジェクトを in 変数 pv (index == 0) から参照できるようにする
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // 頂点の色 nv 用のバッファオブジェクト
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof nv, nv, GL_STATIC_DRAW);

  // 結合されている頂点バッファオブジェクトを in 変数 nv (index == 1) から参照できるようにする
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // 頂点の座標値 tv 用のバッファオブジェクト
  glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof tv, tv, GL_STATIC_DRAW);

  // 頂点のインデックス face 用のバッファオブジェクト
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof face, face, GL_STATIC_DRAW);

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

    // モデル変換行列 (時刻 t にもとづく回転アニメーション)
    GgMatrix mm;
    mm.loadRotateY(12.56637f * t);

    // モデルビュー変換行列
    GgMatrix mw = mv * mm;

    // 法線変換行列
    GgMatrix mg;
    mg.loadNormal(mw);

    // モデルビュー・投影変換
    GgMatrix mc = mp * mw;

    // uniform 変数を設定する
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());

    // 描画に使う頂点配列オブジェクトの指定
    glBindVertexArray(vao);

    // 図形の描画
    glDrawElements(GL_TRIANGLES, FACES * 3, GL_UNSIGNED_INT, 0);

    // 頂点配列オブジェクトの指定解除
    glBindVertexArray(0);

    // シェーダプログラムの使用終了
    glUseProgram(0);

    // ダブルバッファリング
    glfwSwapBuffers();
  }

  return 0;
}
