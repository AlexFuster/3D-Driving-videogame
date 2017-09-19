/***************************************************
ISGI::Cuadrado rebotante
Roberto Vivo', 2013 (v1.0)
Anima un cuadrado en pantalla que
rebota al llegar a
los limites de la ventana sin control de tiempos
Dependencias:
+GLUT
***************************************************/
#define PROYECTO "Videojuego 0 m/s"
#define NQUADS 50
#include<iostream>
#include<sstream>
#include<ctime>
#include<utilidades.h>
// Biblioteca de entrada salida
#include<cmath>
// Biblioteca matematica de C
#include<gl\freeglut.h>
#define PI 3.141615926
// Biblioteca grafica
using namespace std;
static float posicionx(0.0), posiciony(0.0);
// Posicion del cuadrado
static GLuint esfera_exterior, decagono,aguja, volante, volante2;
// Id del cuadrado
static const GLfloat semilado(0.1);
// Tamanyo del cuadrado
static GLfloat semiancho, semialto;
bool texturas = true, lights=false, instrumentos = false, girando = false;
float px = 0, pz = 0, v = 0, alfa = PI / 2 + 0.560985;
int i, j;
GLuint tex[4];
int posanuncio = 20, posf1=10, posf2=30, posf3=50;
float angulovolante = 90;

void loadTexture()
// Funcion de carga de texturas e inicializacion
{
	//1a. GENERAR UN OBJETO TEXTURA 
	
	glGenTextures(3, tex);
	
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	loadImageFile("road.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	loadImageFile("martini.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	loadImageFile("nevadas.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	loadImageFile("metal.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	
	
}
void init()
// Funcion propia de inicializacion
{

	cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;
	glClearColor(0, 0, 0, 0);
	// Color de fondo a blanco
	glColor3f(0, 0, 0);
	// Color de dibujo a negro
	// Crea un cuadrado de lado x lado
	GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Sl0[] = { 0,0,0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glEnable(GL_LIGHT0);

	GLfloat Al1[] = { 0.2,0.2,0.2,1.0 };
	GLfloat Dl1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Sl1[] = { 0.3,0.3,0.3,1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
	glEnable(GL_LIGHT1);

	GLfloat Al2[] = { 0.0,0.0,0.0,1.0 };
	GLfloat Dl2[] = { 0.8,0.8,0.2,1.0 };
	GLfloat Sl2[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT4);

	/*glLightfv(GL_LIGHT5, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT5);*/


	GLfloat Al3[] = { 0.0,0.0,0.0,1.0 };
	GLfloat Dl3[] = { 0.6,0.6,1,1.0 };
	GLfloat Sl3[] = { 0.0,0.0,0.0,1.0 };

	glLightfv(GL_LIGHT6, GL_AMBIENT, Al3);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, Dl3);
	glLightfv(GL_LIGHT6, GL_SPECULAR, Sl3);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 10);
	glEnable(GL_LIGHT6);

	GLfloat difuso[] = { 0.8,0.8,0.8,1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
	GLfloat especular[] = { 0.3,0.3,0.3,1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, 3.0);

	// Caracteristicas del render
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	loadTexture();

	esfera_exterior = glGenLists(1);
	glNewList(esfera_exterior, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (i = 0; i <= 360; i++) {
		glVertex3f(0.25*cos(i * 2 * PI / 720), 0.25*sin(i * 2 * PI / 720), -0.3);
	}
	glEnd();
	glEndList();

	decagono = glGenLists(1);
	glNewList(decagono, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (i = 0; i <= 10; i++) {
		glVertex3f(0.2*cos(i * 2 * PI / 20), 0.2* sin(i * 2 * PI / 20), -0.3);
	}
	glEnd();
	glEndList();

	aguja = glGenLists(1);
	glNewList(aguja, GL_COMPILE);
	glBegin(GL_LINES);
	glVertex3f(0,0,-0.3);
	glVertex3f(-0.125, 0, -0.3);
	glEnd();
	glEndList();


	volante = glGenLists(1);
	glNewList(volante, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex3f(-0.15,0,-0.3);
	glVertex3f(0.15, 0, -0.3);
	glVertex3f(0.15, 0.075, -0.3);
	glVertex3f(-0.15, 0.075, -0.3);
	glEnd();
	glEndList();

	volante2 = glGenLists(1);
	glNewList(volante2, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex3f(-0.035, 0, -0.3);
	glVertex3f(-0.035, -0.15, -0.3);
	glVertex3f(0.035, -0.15, -0.3);
	glVertex3f(0.035, 0, -0.3);
	glEnd();
	glEndList();
}
void display()
// Funcion de atencion al dibujo
{
	
	glLineWidth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	//texturarFondo();
	// Borra la pantalla
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	glPushMatrix();

	gluLookAt(px, 1, pz, px + cos(alfa), 1, pz - sin(alfa), 0, 1, 0);
	//gluLookAt(0, 2, 0, 0, 0, 0, 0, 0, -1);

	//ejes();
	GLfloat posicion0[] = { 0,10,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicion0);

	GLfloat posicion1[] = { px,0.7,pz,1.0 };
	GLfloat dir_central1[] = { cos(alfa),-0.7,-sin(alfa) };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicion1);

	GLfloat cniebla[] = { 0.8,0.8,0.8,1.0 };
	if(glIsEnabled(GL_LIGHTING)){
		cniebla[0] = cniebla[1] = cniebla[2]=0.1;
	}
		
	// Color de la niebla
	glFogfv(GL_FOG_COLOR, cniebla);
	glFogf(GL_FOG_DENSITY, 1.5);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	
	/*glPushMatrix();

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -25);
	glutSolidCylinder(75, 40, 50, 50);
	glPopMatrix();*/
	
	glColor3f(0, 0, 0);
	GLfloat vi[3], vd[3], viant[3], vdant[3], cilindroi[3], cilindrod[3], cilindroiant[3], cilindrodant[3];
	float rcilindro = 75, alturacilindro = 170;
	for (i = 0; i <= 10; i++) {
		cilindroi[0] = rcilindro*cos(-PI/2 + i * 2 * PI / 10);
		cilindroi[1] = -alturacilindro-20 ;
		cilindroi[2] = pz - rcilindro*sin(-PI / 2 + i * 2 * PI / 10);

		cilindrod[0] = cilindroi[0];
		cilindrod[1] = -20-cilindroi[1];
		cilindrod[2] = cilindroi[2];

		if (i > 0) {
			quadtex(cilindroiant, cilindroi, cilindrod,cilindrodant,(i-1)*1.0/10,i*1.0/10,0,1);
		}

		cilindroiant[0] = cilindroi[0];
		cilindroiant[1] = cilindroi[1];
		cilindroiant[2] = cilindroi[2];

		cilindrodant[0] = cilindrod[0];
		cilindrodant[1] = cilindrod[1];
		cilindrodant[2] = cilindrod[2];
	}

	//glBegin(GL_QUAD_STRIP);
	int basez = int(pz);

	
	float pxpanel, alfapanel;
	int pospanel = 1;
	for (i = -5; i <= 50; i++) {
		glColor3f(1, 1, 1);
		float pendiente = cos((-basez + i)*PI / 25)*PI / 5;
		float izqx, derx, izqz, derz,angulo;
		float valorx = 5 * sin((-basez + i)*PI / 25);
		if (pendiente == 0) {
			izqx = valorx - 2;
			derx = valorx + 2;
			izqz = derz = basez - i;
			angulo = PI / 2;
		}
		else {
			angulo = atan(pendiente);
			if (angulo < 0)angulo += PI;
			angulo = angulo + PI / 2;
			if (angulo >= PI)angulo -= PI;
			float auxx = 2 * sin(angulo), auxz = 2 * cos(angulo);
			izqx = -valorx - auxx;
			derx = -valorx + auxx;
			izqz = basez - i - auxz;
			derz = basez - i + auxz;

			//printf("\n\n%d:\nder: (%f,%f)\nizq: (%f,%f\npendiente: %f\npz: %f\nmodulo %f\nangulo: %f)", i, derz, derx, izqz, izqx, pendiente, pz, sqrt(pow(derx - izqx, 2) + pow(derz - izqz, 2)), angulo);
		}
		if (i == pospanel) {
			alfapanel = angulo;
			pxpanel = -valorx;
		}
		viant[0] = vi[0];
		viant[1] = vi[1];
		viant[2] = vi[2];

		vdant[0] = vd[0];
		vdant[1] = vd[1];
		vdant[2] = vd[2];


		vi[0] = izqx;
		vi[1] = 0;
		vi[2] = izqz;

		vd[0] = derx;
		vd[1] = 0;
		vd[2] = derz;

		if (i > -5) {
			glBindTexture(GL_TEXTURE_2D, tex[0]);
			quadtex(viant, vdant, vd, vi,0,1,0,1,30,30);
		}

		if ((-basez + i) == posf1) {
			glEnable(GL_LIGHT2);
			GLfloat posicion2[] = { -valorx,4,basez - i,1.0 };
			GLfloat dir_central2[] = { 0,-1,0 };
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central2);
			glLightfv(GL_LIGHT2, GL_POSITION, posicion2);
		}
		if (-pz-5 > posf1) {
			posf1 += 60;
			glDisable(GL_LIGHT2);
		}

		if ((-basez + i) == posf2) {
			glEnable(GL_LIGHT3);
			GLfloat posicion2[] = { -valorx,4,basez - i,1.0 };
			GLfloat dir_central2[] = { 0,-1,0 };
			glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
			glLightfv(GL_LIGHT3, GL_POSITION, posicion2);
		}
		if (-pz-5 > posf2) {
			posf2 += 60;
			glDisable(GL_LIGHT3);
		}

		if ((-basez + i) == posf3) {
			glEnable(GL_LIGHT4);
			GLfloat posicion2[] = { -valorx,4,basez - i,1.0 };
			GLfloat dir_central2[] = { 0,-1,0 };
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central2);
			glLightfv(GL_LIGHT4, GL_POSITION, posicion2);
		}
		if (-pz - 5 > posf3) {
			posf3 += 60;
			glDisable(GL_LIGHT4);
		}

		/*else if ((-basez + i) % 50 == 48) {
			GLfloat posicion2[] = { -valorx,4,basez - i,1.0 };
			GLfloat dir_central2[] = { 0,-1,0 };
			glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central2);
			glLightfv(GL_LIGHT5, GL_POSITION, posicion2);
		}
		/*glVertex3f(derx, 0, derz);
		glVertex3f(izqx, 0, izqz);*/
		if ((-basez + i)  == posanuncio) {
			
			glBindTexture(GL_TEXTURE_2D, tex[1]);
			GLfloat v1an[3], v2an[3], v3an[3], v4an[3], poste1[3],poste2[3],poste3[3],poste4[3];

			float auxx = 0.3 * sin(angulo), auxz = 0.3 * cos(angulo);
			poste1[0] = vi[0] + auxx;
			poste1[1] = 0;
			poste1[2] = vi[2] + auxz;

			poste2[0] = poste1[0];
			poste2[1] = 2;
			poste2[2] = poste1[2];

			poste3[0] = vd[0] - auxx;
			poste3[1] = 0;
			poste3[2] = vd[2] - auxz;

			poste4[0] = poste3[0];
			poste4[1] = 2;
			poste4[2] = poste3[2];

			v1an[0] = vi[0];
			v1an[1] = 2;
			v1an[2] = vi[2];

			v2an[0] = vd[0];
			v2an[1] = 2;
			v2an[2] = vd[2];

			v3an[0] = vd[0];
			v3an[1] = 4;
			v3an[2] = vd[2];

			v4an[0] = vi[0];
			v4an[1] = 4;
			v4an[2] = vi[2];
			quadtex(v1an, v2an, v3an, v4an);
			glBindTexture(GL_TEXTURE_2D, tex[4]);
			glColor3f(0, 0, 0);
			quad(vi, poste1, poste2, v1an);
			quad(poste3, vd, v2an, poste4);


			float poslight6 = 5 * sin((-basez + i-1)*PI / 25);
			GLfloat posicion2[] = { -poslight6,1,basez - i+1 ,1};
			GLfloat dir_central2[] = { -valorx + poslight6,1.5,-1 };
			glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dir_central2);
			glLightfv(GL_LIGHT6, GL_POSITION, posicion2);
		}
		if (-pz > posanuncio) posanuncio+=20;
	}
	//glEnd();

	/*glPushMatrix();
	glRotatef(1.5*PI-alfa, 0, 1, 0);
	glTranslatef(px+0.1*cos(alfa), 1, pz-0.1*sin(alfa));
	glCallList(esfera_exterior);
	glPopMatrix(); */
	glPopMatrix();

	if (!girando) {
		if (angulovolante > 90) angulovolante = max(angulovolante - 10, 90);
		if (angulovolante < 90) angulovolante = min(angulovolante + 10, 90);
	}

	if (instrumentos) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glPushMatrix();
		glColor4f(0, 0, 0, 0.4);
		glTranslatef(0, 0.25, 0);
		glCallList(esfera_exterior);
		glPopMatrix();

		glPushMatrix();
		glPolygonMode(GL_FRONT, GL_POINT);
		glPointSize(10.0);
		glColor3f(1, 1, 1);
		glTranslatef(0, 0.27, 0);
		glCallList(decagono);
		glPopMatrix();

		glPushMatrix();
		glLineWidth(10.0);
		glPolygonMode(GL_FRONT, GL_LINES);
		glColor3f(1, 0, 0);
		glTranslatef(0, 0.26, 0);
		glRotatef(min(180, v * 180 / 12), 0, 0, -1);
		glCallList(aguja);
		glPopMatrix();


		
		glPolygonMode(GL_FRONT, GL_FILL);
		

		glPushMatrix();
		glColor3f(0.15, 0.15, 0.15);
		glTranslatef(0, -0.4, -0.3);
		glRotatef(alfa*180/PI -90,0, 0, 1);
		glutSolidTorus(0.02, 0.16, 2, 200);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, -0.4, 0);
		glRotatef(angulovolante - 90, 0, 0, 1);
		glCallList(volante);
		glCallList(volante2);
		glPopMatrix();

		if (texturas) {
			
			glEnable(GL_TEXTURE_2D);
		}
		else
			glPolygonMode(GL_FRONT, GL_LINE);

		if (lights)
			glEnable(GL_LIGHTING);

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
	glutSwapBuffers();

	// Finaliza el dibujo
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	glViewport(0, 0, w, h);
	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (float)w / h, 0.1, 100);
}
void onTimer(int valor)
{
	//printf("\n%f\t%f",alfa, px);
	px += 0.1*v*cos(alfa);
	pz -= 0.1*v*sin(alfa);

	glutTimerFunc(100, onTimer, 1);
	glutPostRedisplay();
}
void onKey(unsigned char key, int x, int y) {
	switch (key) {
		case 's':
			if (texturas) {
				glDisable(GL_TEXTURE_2D);
				glPolygonMode(GL_FRONT, GL_LINE);
			}
			else {
				glEnable(GL_TEXTURE_2D);
				glPolygonMode(GL_FRONT, GL_FILL);
			}
			texturas = !texturas;
			break;

		case 'l':
			if (lights) {
				glDisable(GL_LIGHTING);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
			else {
				glEnable(GL_LIGHTING);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			lights = !lights;
			break;

		case 'n':
			if (glIsEnabled(GL_FOG))
				glDisable(GL_FOG);
			else
				glEnable(GL_FOG);
			break;

		case 'c':
			instrumentos = !instrumentos;
			break;
			
			

	}
}
void onSpecialKey(int specialKey, int x, int y) {
	
	switch (specialKey) {
	case GLUT_KEY_UP:
		v += 0.1;
		break;
	case GLUT_KEY_DOWN:
		v -= 0.1;
		if (v < 0)v = 0;
		break;
	case GLUT_KEY_LEFT:
		girando = true;
		alfa += PI / 180;
		angulovolante += 1;
		break;
	case GLUT_KEY_RIGHT:
		girando = true;
		alfa -= PI / 180;
		angulovolante -= 1;
		break;

	}
	stringstream titulo;
	titulo << "Interfaz de conducción " << v << "m/s";
	glutSetWindowTitle(titulo.str().c_str());
}
void onSpecialKeyUp(int specialKey, int x, int y) {

	switch (specialKey) {
	case GLUT_KEY_LEFT:
		girando = false;
		alfa += 0.25*PI / 180;
		angulovolante += 0.25;
		break;
	case GLUT_KEY_RIGHT:
		girando = false;
		alfa -= 0.25*PI / 180;
		angulovolante -= 0.25;
		break;

	}
	stringstream titulo;
	titulo << "Videojuego " << v << "m/s";
	glutSetWindowTitle(titulo.str().c_str());
}

void main(
	int argc,
	char ** argv)
	// Programa principal
{
	printf("PRACTICA 9: VIDEOJUEGO\nFLECHAS: girar y acelerar\nL: cambio DIA/NOCHE\nN: cambio NIEBLA/NORMAL\nC: cambio instrumentos ON/OFF\nS: cambio ALAMBRICO/SOLIDO\n");
	FreeImage_Initialise();
	glutInit(&argc, argv);
	// Inicializacion de GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Alta de buffers a usar
	glutInitWindowSize(600, 400);
	// Tamanyoinicial de la ventana
	glutCreateWindow(PROYECTO);
	// Creacion de la ventana con su titulos
	cout << PROYECTO << " running" << endl;
	// Mensaje por consola
	glutDisplayFunc(display);
	// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);
	// Alta de la funcion de atencion a reshape
	glutKeyboardFunc(onKey);
	glutSpecialFunc(onSpecialKey);
	glutSpecialUpFunc(onSpecialKeyUp);
	glutTimerFunc(100, onTimer, 1);
	
	// Alta de la funcion de atencion a idle
	init();
	// Inicializacion propia
	glutMainLoop();
	FreeImage_DeInitialise();
	// Puesta en marcha del programa
}