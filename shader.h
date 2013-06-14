//
// プログラムオブジェクトの作成
//
//     vsrc: バーテックスシェーダのソースファイル名, pv: attribute の in 変数名
//     fsrc: フラグメントシェーダのソースファイル名, fc: カラーバッファに結合する out 変数名
//
extern GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc);
