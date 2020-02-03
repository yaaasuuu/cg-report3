//
// nglmatrix.c - モダンOpenGL用旧OpenGL互換行列計算用関数
// 注意: このファイルは変更しないで下さい
//
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

#define rc(row,column)	((column) * 4 + (row))	// 行と列の逆転
#define deg2rad(deg)	((deg) * M_PI / 180.0)	// 度からラジアンに変換
#define sqr(x)	((x) * (x))	// 2乗

//
// 4x4変換行列の計算
//

//
// nglLoadMatrix - 行列tgtに行列srcを代入する
//
void
nglLoadMatrix(
	GLfloat *tgt,	// [out] 代入先の行列
	GLfloat *src	// [in] 代入元の行列
)
{
	memcpy(tgt, src, sizeof(GLfloat) * 16);
}

//
// nglLoadIdentity - 行列tgtに単位行列を代入する
//
void
nglLoadIdentity(
	GLfloat *mat	// [out] 単位行列を代入する行列
)
{
	GLfloat templ[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	memcpy(mat, templ, sizeof(GLfloat) * 16);
}

//
// nglMultMatrix - 行列tgtに行列oprを右から掛ける
//
void
nglMultMatrix(
	GLfloat *tgt,	// [in/out] 掛けられる行列
	GLfloat *opr	// [in] 掛ける行列
)
{
	int i, j, k;
	GLfloat tmp[16];

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			tmp[rc(i, j)] = 0;
			for(k = 0; k < 4; k++)
				tmp[rc(i, j)] += tgt[rc(i, k)] * opr[rc(k, j)];
		}
	for(i = 0; i < 16; i++)
		tgt[i] = tmp[i];
}

//
// nglTranslate - 行列tgtに(tx,ty,tz)平行移動の行列を右から掛ける
//
void
nglTranslate(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble tx,	// [in] x方向移動量
	GLdouble ty,	// [in] y方向移動量
	GLdouble tz	// [in] z方向移動量
)
{
	GLfloat tmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	tmat[rc(0, 3)] = tx;
	tmat[rc(1, 3)] = ty;
	tmat[rc(2, 3)] = tz;

	nglMultMatrix(mat, tmat);
}

//
// nglScale - 行列tgtに(sx,sy,sz)倍の拡大縮小の行列を右から掛ける
//
void
nglScale(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble sx,	// [in] x方向倍率
	GLdouble sy,	// [in] y方向倍率
	GLdouble sz	// [in] z方向倍率
)
{
	GLfloat smat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	smat[rc(0, 0)] = sx;
	smat[rc(1, 1)] = sy;
	smat[rc(2, 2)] = sz;

	nglMultMatrix(mat, smat);
}

//
// nglRotateX - 行列tgtにx軸中心のangle回転の行列を右から掛ける
//
void
nglRotateX(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(1, 1)] = rmat[rc(2, 2)] = cos(deg2rad(angle));
	rmat[rc(1, 2)] = - (rmat[rc(2, 1)] = sin(deg2rad(angle)));

	nglMultMatrix(mat, rmat);
}

//
// nglRotateY - 行列tgtにy軸中心のangle回転の行列を右から掛ける
//
void
nglRotateY(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(0, 0)] = rmat[rc(2, 2)] = cos(deg2rad(angle));
	rmat[rc(2, 0)] = - (rmat[rc(0, 2)] = sin(deg2rad(angle)));

	nglMultMatrix(mat, rmat);
}

//
// nglRotateZ - 行列tgtにz軸中心のangle回転の行列を右から掛ける
//
void
nglRotateZ(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(0, 0)] = rmat[rc(1, 1)] = cos(deg2rad(angle));
	rmat[rc(0, 1)] = - (rmat[rc(1, 0)] = sin(deg2rad(angle)));

	nglMultMatrix(mat, rmat);
}

//
// nglLeftMultMatrix - 行列tgtに行列oprを左から掛ける
//
void
nglLeftMultMatrix(
	GLfloat *tgt,	// [in/out] 掛けられる行列
	GLfloat *opr	// [out] 掛ける行列
)
{
	int i, j, k;
	GLfloat tmp[16];

	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++) {
			tmp[rc(i, j)] = 0;
			for(k = 0; k < 4; k++)
				tmp[rc(i, j)] += opr[rc(i, k)] * tgt[rc(k, j)];
		}
	for(i = 0; i < 16; i++)
		tgt[i] = tmp[i];
}

//
// nglLeftTranslate - 行列tgtに(tx,ty,tz)平行移動の行列を左から掛ける
//
void
nglLeftTranslate(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble tx,	// [in] x方向移動量
	GLdouble ty,	// [in] y方向移動量
	GLdouble tz	// [in] z方向移動量
)
{
	GLfloat tmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	tmat[rc(0, 3)] = tx;
	tmat[rc(1, 3)] = ty;
	tmat[rc(2, 3)] = tz;

	nglLeftMultMatrix(mat, tmat);
}

//
// nglLeftScale - 行列tgtに(sx,sy,sz)倍の拡大縮小の行列を左から掛ける
//
void
nglLeftScale(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble sx,	// [in] x方向倍率
	GLdouble sy,	// [in] y方向倍率
	GLdouble sz	// [in] z方向倍率
)
{
	GLfloat smat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	smat[rc(0, 0)] = sx;
	smat[rc(1, 1)] = sy;
	smat[rc(2, 2)] = sz;

	nglLeftMultMatrix(mat, smat);
}

//
// nglLeftRotateX - 行列tgtにx軸中心のangle回転の行列を左から掛ける
//
void
nglLeftRotateX(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(1, 1)] = rmat[rc(2, 2)] = cos(deg2rad(angle));
	rmat[rc(1, 2)] = - (rmat[rc(2, 1)] = sin(deg2rad(angle)));

	nglLeftMultMatrix(mat, rmat);
}

//
// nglLeftRotateY - 行列tgtにy軸中心のangle回転の行列を左から掛ける
//
void
nglLeftRotateY(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(0, 0)] = rmat[rc(2, 2)] = cos(deg2rad(angle));
	rmat[rc(2, 0)] = - (rmat[rc(0, 2)] = sin(deg2rad(angle)));

	nglLeftMultMatrix(mat, rmat);
}

//
// nglLeftRotateZ - 行列tgtにz軸中心のangle回転の行列を左から掛ける
//
void
nglLeftRotateZ(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble angle	// [in] 回転角
)
{
	GLfloat rmat[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	rmat[rc(0, 0)] = rmat[rc(1, 1)] = cos(deg2rad(angle));
	rmat[rc(0, 1)] = - (rmat[rc(1, 0)] = sin(deg2rad(angle)));

	nglLeftMultMatrix(mat, rmat);
}

//
// ngluPerspective - 行列matに透視投影行列を右から掛ける
//
void
ngluPerspective(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble fovy,	// [in] y方向の視野角(画角)
	GLdouble aspect,// [in] ウィンドウのy方向に対するx方向の比
	GLdouble zNear,	// [in] 前方クリッピング面までの距離
	GLdouble zFar	// [in] 後方クリッピング面までの距離
)
{
	GLfloat pmat[16] = {	0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, -1.0,
				0.0, 0.0, 0.0, 0.0 };
	double cotfovy;

	cotfovy = 1.0 / tan(deg2rad(fovy / 2.0));
	pmat[rc(0, 0)] = cotfovy / aspect;
	pmat[rc(1, 1)] = cotfovy;
	pmat[rc(2, 2)] = - (zFar + zNear) / (zFar - zNear);
	pmat[rc(2, 3)] = - 2 * zFar * zNear / (zFar - zNear);

	nglMultMatrix(mat, pmat);
}

//
// nglOrtho - 行列matに平行投影(直投影)行列を右から掛ける
//
void
nglOrtho(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble left,	// [in] x座標最小値
	GLdouble right,	// [in] x座標最大値
	GLdouble bottom,// [in] y座標最小値
	GLdouble top,	// [in] y座標最大値
	GLdouble zNear,	// [in] 前方クリッピング面までの距離
	GLdouble zFar	// [in] 後方クリッピング面までの距離
)
{
	GLfloat pmat[16] = {	0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 1.0 };

	pmat[rc(0, 0)] = 2.0 / (right - left);
	pmat[rc(1, 1)] = 2.0 / (top - bottom);
	pmat[rc(2, 2)] = - 2.0 / (zFar - zNear);

	pmat[rc(0, 3)] = - (right + left) / (right - left);
	pmat[rc(1, 3)] = - (top + bottom) / (top - bottom);
	pmat[rc(2, 3)] = - (zFar + zNear) / (zFar - zNear);

	nglMultMatrix(mat, pmat);
}

//
// ngluLookAt010 - upベクトル(0,1,0)で視野変換を右から掛ける
// 注意：eyex = centerx かつ eyez = centerz は許されない
//
void
ngluLookAt010(
	GLfloat *mat,	// [in/out] 掛けられる行列
	GLdouble eyex,	// [in] 視点x座標
	GLdouble eyey,	// [in] 視点y座標
	GLdouble eyez,	// [in] 視点z座標
	GLdouble centerx,	// [in] 参照視点x座標
	GLdouble centery,	// [in] 参照視点y座標
	GLdouble centerz	// [in] 参照視点z座標
)
{
	double dx, dy, dz;
	double distxz;
	double distxyz;
	GLfloat rot[16];	// 掛ける回転行列

	dx = eyex - centerx;
	dy = eyey - centery;
	dz = eyez - centerz;
	distxz = sqrt(sqr(dx) + sqr(dz));
	distxyz = sqrt(sqr(dx) + sqr(dy) + sqr(dz));
// z平行移動
	nglTranslate(mat, 0.0, 0.0, - distxyz);
// x回転
	nglLoadIdentity(rot);
	rot[rc(1, 1)] = rot[rc(2, 2)] = distxz / distxyz;	// cos
	rot[rc(1, 2)] = - ( rot[rc(2, 1)] = dy / distxyz);	// sin
	nglMultMatrix(mat, rot);
// y回転
	nglLoadIdentity(rot);
	rot[rc(0, 0)] = rot[rc(2, 2)] = dz / distxz;		// cos
	rot[rc(2, 0)] = - (rot[rc(0, 2)] = - dx / distxz);	// sin
	nglMultMatrix(mat, rot);
// 参照視点分平行移動
	nglTranslate(mat, - centerx, - centery, - centerz);
}

//
// 4x4変換行列のスタック
//

// matrixstack型の定義
#define MAXLENGTH_MATRIXSTACK 32	// スタック最大高さ
typedef struct {
	int top;	// 先頭要素のインデックス
	GLfloat mat[MAXLENGTH_MATRIXSTACK][16];	// スタックの要素
} matrixstack;	// matrixstack型

//
// nglInitMatrixStack - 行列スタックmsを初期化する
//
void
nglInitMatrixStack(
	matrixstack *ms	// [out] 初期化される行列スタック
)
{
	ms->top = 0;
	nglLoadIdentity(ms->mat[ms->top]);	// tmp
}

//
// nglPushMatrix - 行列スタックmsの先頭要素をコピーしてpush
//
void
nglPushMatrix(
	matrixstack *ms	// [in/out] 行列スタック
)
{
	if(ms->top < MAXLENGTH_MATRIXSTACK - 1) {
		memcpy(ms->mat[ms->top + 1], ms->mat[ms->top],
		 sizeof(GLfloat) * 16);
		ms->top++;
	}
	else
		fprintf(stderr,
		 "warning: matrix stack overflow (nglPushMatrix)\n");
}

//
// nglPopMatrix - 行列スタックmsをpop
//
void
nglPopMatrix(
	matrixstack *ms	// [in/out] 行列スタック
)
{
	if(ms->top > 0)
		ms->top--;
	else
		fprintf(stderr,
		 "warning: matrix stack is emptied (nglPopMatrix)\n");
}

//
// nglGetTopMatrixStack - 行列スタックmsの先頭要素を返す
//
GLfloat*
nglGetTopMatrixStack(
	matrixstack *ms	// [in] 行列スタック
)
{
	return ms->mat[ms->top];
}

