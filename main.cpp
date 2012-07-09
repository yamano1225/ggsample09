#include <cmath>
#include <cstdlib>

#include "gg.h"
using namespace gg;

#include "matrix.h"

// プログラムオブジェクト
static GLuint program;

// attribute 変数のインデックス
static GLint pvLoc, nvLoc;

// uniform 変数のインデックス
static GLint mwLoc, mcLoc, mgLoc;

// 透視投影変換行列
static GLfloat mp[16];

// アニメーションの周期
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
** 画面表示
*/
static void display(void)
{
  // 時刻の計測
  static int firstTime = 0;
  GLfloat t;
  if (firstTime == 0) { firstTime = glutGet(GLUT_ELAPSED_TIME); t = 0.0f; }
  else t = (GLfloat)((glutGet(GLUT_ELAPSED_TIME) - firstTime) % CYCLE) / (GLfloat)CYCLE;

  // モデリング変換行列
  GLfloat mm[16];
  rotate(mm, 1.0f, 0.0f, 0.0f, 12.56637f * t);

  // 視野変換行列
  GLfloat mv[16];
  lookat(mv, 0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  // モデルビュー変換行列
  GLfloat mw[16];
  multiply(mw, mv, mm);
  
  // 法線変換行列
  GLfloat mg[16];
  normal(mg, mw);
  
  // モデルビュー・投影変換
  GLfloat mc[16];
  multiply(mc, mp, mw);
  
  // 画面クリア
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // シェーダプログラムの選択
  glUseProgram(program);
  
  // uniform 変数を設定する
  glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw);
  glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc);
  glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg);
  
  // attribute 変数 pv, nv, tv を配列変数から得ることを許可する
  glEnableVertexAttribArray(pvLoc);
  glEnableVertexAttribArray(nvLoc);
  
  // attribute 変数 pv, nv, tv と配列変数 pv, nv, tv を結びつける
  glVertexAttribPointer(pvLoc, 3, GL_FLOAT, GL_FALSE, 0, pv);
  glVertexAttribPointer(nvLoc, 3, GL_FLOAT, GL_FALSE, 0, nv);

  // 図形を描画する
  glDrawElements(GL_TRIANGLES, FACES * 3, GL_UNSIGNED_INT, face);

  glutSwapBuffers();
}

/*
** ウィンドウのリサイズ
*/
static void resize(int w, int h)
{
  // ウィンドウ全体をビューポートにする
  glViewport(0, 0, w, h);
  
  // 透視投影変換行列を求める（アスペクト比 w / h）
  perspective(mp, 0.5f, (float)w / (float)h, 1.0f, 20.0f);
}

/*
** アニメーション
*/
static void idle(void)
{
  glutPostRedisplay();
}

/*
** 球のデータを作成する
*/
static void makeSphere(float radius, int slices, int stacks,
  GLfloat (*pv)[3], GLfloat (*nv)[3], GLfloat (*tv)[2], GLuint (*f)[3])
{
  // 頂点の位置とテクスチャ座標を求める
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
  for (int k = 0, j = 0; j < stacks; ++j) {
    for (int i = 0; i < slices; ++i) {
      int count = (slices + 1) * j + i;

      /* 上半分 */
      f[k][0] = count;
      f[k][1] = count + 1;
      f[k][2] = count + slices + 2;
      ++k;

      /* 下半分 */
      f[k][0] = count;
      f[k][1] = count + slices + 2;
      f[k][2] = count + slices + 1;
      ++k;
    }
  }
}

/*
** 初期化
*/
static void init(void)
{
  // ゲームグラフィックス特論の都合にもとづく初期化
  ggInit();

  // シェーダプログラムの読み込み
  program = loadShader("simple.vert", "simple.frag");

  // attribute 変数のインデックスの検索（見つからなければ -1）
  pvLoc = glGetAttribLocation(program, "pv");
  nvLoc = glGetAttribLocation(program, "nv");
  
  // uniform 変数のインデックスの検索（見つからなければ -1）
  mwLoc = glGetUniformLocation(program, "mw");
  mcLoc = glGetUniformLocation(program, "mc");
  mgLoc = glGetUniformLocation(program, "mg");
  
  // 図形データの作成
  makeSphere(1.0f, SLICES, STACKS, pv, nv, tv, face);

  // 隠面消去
  glEnable(GL_DEPTH_TEST);

  // 背景色
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

/*
** メインプログラム
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
