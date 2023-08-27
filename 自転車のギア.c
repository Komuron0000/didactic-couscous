#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
int MouseX = 1280, MouseY = 1024, WinH, WinW;
double size;
static double spinAngle = 0.0;
static double earthAngle = 0.0;

double pi = 3.1415;//�~����
void Recube(double n, double i, double r);
double M=6;//�M�A�̒i

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
	glClearColor(0.0, 0.0, 0.0, 0.0);//�w�i�̐F
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//���s����r�̂��߁A�f�v�X�o�b�t�@���N���A����


	float diffuse[] = { 0.4, 0.4, 0.4, 1.0 };//�F
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
	glColor3d(0.60, 0.5, 0.2); /* ���f���`��F��ݒ� */
	glutWireTorus(0.3, 0.8, 20, 20); /* �h�[�i�c���\���b�h�ŕ`�� */
	glPopMatrix(); /* �ϊ��s����Ăі߂�(pop����) */

	double r = 10.0;//���a
	double s = 0.1;//�M�A�̌���

	glColor3d(0.5, 0.0, 0.5);


	glPushMatrix();

	glRotated(spinAngle, 0.0, 0.0, 1.0);

	for (double N = 0; N < M; N++) {
		glTranslated(0.0, 0.0, 0.4);
		r = r - 0.5 * N;


		glBegin(GL_POLYGON);//�\��
		glNormal3d(0.0, 0.0, 1.0);
		for (double i = 0; i < 100; i++) {//100�p�`�����
			double t = pi * 2 / 100 * i;//�O�p�֐��ɑ������p�x��ݒ�
			glVertex3d(r * cos(t), r * sin(t), s);//�~����̓_��`��
		}
		glEnd();

		glColor3d(0.8, 1.0, 0.5);

		glBegin(GL_QUAD_STRIP);//����
		for (double i = 0; i <= 100; i = i + 1) {

			double t = pi * 2 / 100 * i;
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t), r * sin(t), -s);
			glVertex3d(r * cos(t), r * sin(t), s);
		}
		glEnd();
		glColor3d(0.8, 1.0, 1.0);

		glBegin(GL_POLYGON);//��
		glNormal3d(0.0, 0.0, -1.0);
		for (double i = 0; i < 100; i++) {//100�p�`�����
			double t = pi * 2 / 100 * i;//�O�p�֐��ɑ������p�x��ݒ�
			glVertex3d(r * cos(t), r * sin(t), -s);//�~����̓_��`��
		}
		glEnd();



		double n = 30-N*3;//���̐�
		double i = 0;
		for (i = 0; i < n; i++) {


			glColor3d(0.0, 0.0, 1.0);
			double t = pi * 2 / n * i;
			double lx = 1.0;//�M�A�̒���
			double ly = 0.1;//�M�A�̑���
			double o = 0.4;//�O���̎��̑���
			s = 0.15;//�M�A�̎��̂̌���

			glBegin(GL_POLYGON);//�\��
			glNormal3d(0.0, 0.0, 1.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), s);//i=0�̎��A������
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//�O����
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//�O����
			glVertex3d(r * cos(t - ly), r * sin(t - ly), s);//������
			glEnd();

			glBegin(GL_POLYGON);//����
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), s);//i=0�̎��A������ �\
			glVertex3d(r * cos(t + ly), r * sin(t + ly), -s);//i=0�̎��A������ ��
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//�O���� ��
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//�O���� �\
			glEnd;

			glBegin(GL_POLYGON);//����
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//�O���� �\
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//�O���� ��
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//�O���� ��
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), s);//�O���� �\
			glEnd;

			glBegin(GL_POLYGON);//����
			glNormal3d(0.0, 0.0, -1.0);
			glVertex3d(r * cos(t + ly), r * sin(t + ly), -s);//i=0�̎��A������
			glVertex3d((r + lx) * cos(t + ly * o), (r + lx) * sin(t + ly * o), -s);//�O����
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//�O����
			glVertex3d(r * cos(t - ly), r * sin(t - ly), -s);//������
			glEnd();

			glBegin(GL_POLYGON);//����
			glNormal3d(cos(t), sin(t), 0.0);
			glVertex3d(r * cos(t - ly), r * sin(t - ly), -s);//������ ��
			glVertex3d(r * cos(t - ly), r * sin(t - ly), s);//������ �\
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), s);//�O���� �\
			glVertex3d((r + lx) * cos(t - ly * o), (r + lx) * sin(t - ly * o), -s);//�O���� ��
			glEnd();
		}
	}

		glPopMatrix();




	glutSwapBuffers();
}

void ModelSpin(void)
{
	spinAngle += 0.01;
	if (spinAngle > 360.0) spinAngle -= 360.0; /* 360�x�ȏ�Ȃ�360������ */
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
	gluPerspective(80.0, (float)w / (float)h, 0.1, 100.0);//(�c�����̉�p�A�c����i�E�B���h�E�̃T�C�Y�ɍ��킹��j�A�߂��ʁA�����ʁA)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(13.0, 0.0, 13.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);/*(�O3�A�ǂ����猩�邩�A���R�A�ǂ��Ɍ����Ă݂邩�A���R�ǂ�������ɂ��邩*/
}

void mouse(int button, int state, int x, int y) /* ( x, y )�͑��̕����A�h���X */
{
	size = (double)MouseX / WinW;
	switch (button) {
	case GLUT_LEFT_BUTTON: /* ���{�^�� */
		if (state == GLUT_UP) /* ���{�^����߂����Ƃ� */
		{
			MouseX = x;
			MouseY = y;
			glutPostRedisplay(); /* �����ĕ\��(�`��)������ */
		}
		if (state == GLUT_DOWN); /* ���{�^�������������Ƃ� */

		break;
	case GLUT_MIDDLE_BUTTON: /* �����{�^�� */
		break;
	case GLUT_RIGHT_BUTTON: /* �E�{�^���͍���g��Ȃ� */
		break;
	default: /* ����ȊO */
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);//OpenGL�̏�����
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);//�`��E�B���h�E�����̍��W���w��
	glutInitWindowSize(500, 500);//�J���E�B���h�E�̃T�C�Y���w��
	glutCreateWindow(argv[0]);//�`��p�̃E�B���h�E���J��
	glEnable(GL_DEPTH_TEST);//���s������������
	glutDisplayFunc(ModelDraw);//����\�����邩���֐�����p���Ďw��
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);//�L�[�������ꂽ���ɃC�x���g�������邱��
	glutMouseFunc(mouse);
	glutIdleFunc(ModelSpin); //��]��������֐����Ăяo��
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glutMainLoop();
	return 0;
}
