#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
int MouseX = 1280, MouseY = 1024, WinH, WinW;
double size;
static double spinAngle = 0.0;
static double earthAngle = 0.0;

double pi = 3.1415;//円周率
void Recube(double n, double i, double r);
double M=6;//ギアの段

/*void initialize(void)
{
	glClearColor(0.5, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 0.5, -1.0, 1.0, -1.0, 1.0);
}
*/
void ModelDraw(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//背景の色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//奥行き比較のため、デプスバッファをクリアする


	float diffuse[] = { 0.4, 0.4, 0.4, 1.0 };//色
	float specular[] = { 0.5, 0.5, 0.5, 1.0 };
	float ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	float shininess = 100.0;
	float light[] = { 10.0,10.0,10.0,0.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light);


	glPushMatrix();
	glRotated(spinAngle, 0.0, 0.0, 1.0);
	glTranslated(0.0, 0.0, 0.4 * M + 0.2);
	glColor3d(0.60, 0.5, 0.2); /* モデル描画色を設定 */
	glutWireTorus(0.3, 0.8, 20, 20); /* ドーナツをソリッドで描画 */
	glPopMatrix(); /* 変換行列を呼び戻す(popする) */

	double r = 10.0;//半径
	double s = 0.1;//ギアの厚み

	glColor3d(0.5, 0.0, 0.5);


	glPushMatrix();

	glRotated(spinAngle, 0.0, 0.0, 1.0);

	for (double N = 0; N < M; N++) {
		glTranslated(0.0, 0.0, 0.4);
		r = r - 0.5 * N;


		glBegin(GL_POLYGON);//表面
		glNormal3d(0.0, 0.0, 1.0);
		for (double i = 0; i < 100; i++) {//100角形を作る
			double t = pi * 2 / 100 * i;//三角関数に代入する角度を設定
			glVertex3d(r * cos(t), r * sin(t), s);//円周上の点を描画
		}
		glEnd();

		glColor3d(0.8, 1.0, 0.5);

		glBegin(GL_QUAD_STRIP);//横面
		for (double i = 0; i <= 100; i = i + 1) {

			double t = pi * 2 / 100 * i;
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t), r * sin(t), -s);
			glVertex3d(r * cos(t), r * sin(t), s);
		}
		glEnd();
		glColor3d(0.8, 1.0, 1.0);

		glBegin(GL_POLYGON);//裏
		glNormal3d(0.0, 0.0, -1.0);
		for (double i = 0; i < 100; i++) {//100角形を作る
			double t = pi * 2 / 100 * i;//三角関数に代入する角度を設定
			glVertex3d(r * cos(t), r * sin(t), -s);//円周上の点を描画
		}
		glEnd();



		double n = 30-N*3;//歯の数
		double i = 0;
		for (i = 0; i < n; i++) {


			glColor3d(0.0, 0.0, 1.0);
			double t = pi * 2 / n * i;
			double lx = 1.0;//ギアの長さ
			double ly = 0.1;//ギアの太さ
			double o = 0.4;//外側の歯の太さ
			s = 0.15;//ギアの歯のの厚み

			glBegin(GL_POLYGON);//表面
			glNormal3d(0.0, 0.0, 1.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), s);//i=0の時、内側上
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//外側上
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//外側下
			glVertex3d(r * cos(t - ly), r * sin(t - ly), s);//内側下
			glEnd();

			glBegin(GL_POLYGON);//横面
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), s);//i=0の時、内側上 表
			glVertex3d(r * cos(t + ly), r * sin(t + ly), -s);//i=0の時、内側上 裏
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//外側上 裏
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//外側上 表
			glEnd;

			glBegin(GL_POLYGON);//横面
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//外側下 表
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//外側下 裏
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//外側上 裏
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//外側上 表
			glEnd;

			glBegin(GL_POLYGON);//裏面
			glNormal3d(0.0, 0.0, -1.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), -s);//i=0の時、内側上
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//外側上
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//外側下
			glVertex3d(r * cos(t - ly), r * sin(t - ly), -s);//内側下
			glEnd();

			glBegin(GL_POLYGON);//横面
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t - ly), r * sin(t - ly), -s);//内側下 裏
			glVertex3d(r * cos(t - ly), r * sin(t - ly), s);//内側下 表
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//外側下 表
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//外側下 裏
			glEnd();
		}
	}

		glPopMatrix();




	glutSwapBuffers();
}

void ModelSpin(void)
{
	spinAngle += 0.01;
	if (spinAngle > 360.0) spinAngle -= 360.0; /* 360度以上なら360を引く */
	ModelDraw();
}

void keyboard(unsigned char c, int x, int y)
{
	if (c == 27) exit(0);
}

void reshape(int w, int h)
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, (float)w / (float)h, 0.1, 100.0);//(縦方向の画角、縦横比（ウィンドウのサイズに合わせる）、近い面、遠い面、)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(13.0, 0.0, 13.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);/*(前3つ、どこから見るか、中３つ、どこに向かてみるか、後ろ３つどっちを上にするか*/
}

void mouse(int button, int state, int x, int y) /* ( x, y )は窓の物理アドレス */
{
	size = (double)MouseX / WinW;
	switch (button) {
	case GLUT_LEFT_BUTTON: /* 左ボタン */
		if (state == GLUT_UP) /* 左ボタンを戻したとき */
		{
			MouseX = x;
			MouseY = y;
			glutPostRedisplay(); /* 窓を再表示(描画)させる */
		}
		if (state == GLUT_DOWN); /* 左ボタンを押下したとき */

		break;
	case GLUT_MIDDLE_BUTTON: /* 中央ボタン */
		break;
	case GLUT_RIGHT_BUTTON: /* 右ボタンは今回使わない */
		break;
	default: /* それ以外 */
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);//OpenGLの初期化
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);//描画ウィンドウ左隅の座標を指定
	glutInitWindowSize(500, 500);//開くウィンドウのサイズを指定
	glutCreateWindow(argv[0]);//描画用のウィンドウを開く
	glEnable(GL_DEPTH_TEST);//奥行きを検査する
	glutDisplayFunc(ModelDraw);//何を表示するかを関数名を用いて指定
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);//キーが押された時にイベント処理すること
	glutMouseFunc(mouse);
	glutIdleFunc(ModelSpin); //回転をさせる関数を呼び出す
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glutMainLoop();
	return 0;
}
