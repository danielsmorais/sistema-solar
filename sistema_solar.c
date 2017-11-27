#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "texture.h"

static int year = 0, day_moon = 0;
static int day_mercurio = 0, day_venus = 0, day_earth = 0, day_mars = 0, day_jupter = 0, day_saturn = 0;
static int day_urain = 0, day_neturn = 0;

GLuint textura[10];
	int anoA = 0,anoB = 0, anoC = 0, dia = 0, luna=0;
int angulo_z = 0;
float azul[3]={0.0,0.0,1.0};
float verde[3]={0.0,1.0,0.0};
float rojo[3]={1.0,0.0,0.0};

void init(void) 
{
	//Obs: o uso de textura consiste apenas em dois passos: Carga e Aplicação.

	// Habilitar o uso de texturas
	glEnable ( GL_TEXTURE_2D );
	glEnable(GL_COLOR_MATERIAL);
	// Definir a forma de armazenamento dos pixels na textura (1= alinhamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Definir quantas texturas serão usadas no programa
	glGenTextures (10, textura);  // 1 = uma textura;
					// texture_id = vetor que guarda os números das texturas(para ir trocando depois)
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	//carregar texturas
	textura[0] = LoadBitmap("media/Sol/Sol.bmp");
	textura[1] = LoadBitmap("media/Mercurio/Mercurio.bmp");
	textura[2] = LoadBitmap("media/Venus/Venus.bmp");
	textura[3] = LoadBitmap("media/Tierra/Tierra.bmp");
	textura[4] = LoadBitmap("media/Marte/Marte.bmp");
	textura[5] = LoadBitmap("media/Jupiter/Jupiter.bmp");
	textura[6] = LoadBitmap("media/Saturno/Saturno.bmp");
	textura[7] = LoadBitmap("media/Urano/Urano.bmp");
	textura[8] = LoadBitmap("media/Neptuno/Neptuno.bmp");


	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);


	//negocio para nao ficar mais transparente
	glEnable(GL_DEPTH_TEST);

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

 void planeta(float ano, float dia, float lua, float tamanho, float distancia, GLuint text)
 {

	GLUquadric *qobj = gluNewQuadric();

	gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,text);

    glPushMatrix();
        glRotatef (angulo_z, 0.0, 0.0, 0.0);    		//angulo constante de inclinacao em z
        glRotatef ((GLfloat)ano, 0.0, 1.0, 0.0);   		//angulo  para o numero de anos
        glTranslatef (distancia, 0.0, 0.0);    			//Distancia entre o sol e o planeta
        glPushMatrix();
            glRotatef ((GLfloat) dia, 0.0, 1.0, 0.0);   //angulo do planeta de acorodo com o dia
            gluSphere(qobj,tamanho, 30, 30);            /* desenha o planeta */
        glPopMatrix();
        glRotatef (25, 0.0, 0.0, 0.0);               	//angulo da lua em relação ao planeta
        glRotatef ((GLfloat) lua, 0.0, 1.0, 0.0);   	//angulo da lua de acordo coma hora
        glTranslatef (0.3, 0.0, 0.0);                	//Distancia da lua em relação ao planeta
        glColor3f (0.7, 0.7, 0.7);                   	//Cor da lua /// modificar para textura
        glutWireSphere(0.07, 10, 8);                 	// desenha a lua /// modificar
    glPopMatrix();

	glDisable(GL_TEXTURE_2D);
 }


void display(void)
{    

	glMatrixMode(GL_MODELVIEW);
	
   	glClear (GL_COLOR_BUFFER_BIT);
   	glColor3f (1.0, 1.0, 1.0);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textura[0]);

    glEnable(GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
	
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);    
    gluSphere(qobj,0.7, 30, 30);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
    planeta(anoA,dia,luna,0.1,1,textura[1]); //mercurio
    planeta(anoB,dia,luna,0.2,2,textura[2]); //venus
    planeta(anoC,dia,luna,0.2,3,textura[3]); //terra

	planeta(anoA,dia,luna,0.2,4,textura[4]); //marte
    planeta(anoB,dia,luna,0.2,5,textura[5]); //jupiter
    planeta(anoC,dia,luna,0.2,6,textura[6]); //saturno

	planeta(anoA,dia,luna,0.2,7,textura[7]); //urano
    planeta(anoB,dia,luna,0.2,8,textura[8]); //netuno

    glutSwapBuffers();

}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {

        case 'g':
			anoA-=4; //Caso que hace avanzar los planetas sobre sus �rbitas.
            anoB-=2;
            anoC-=1;
            glutPostRedisplay();
            break;
        case 'h':
			dia--; //Caso que permite que los planetas giren sobre su propio eje
            glutPostRedisplay();
            break;
    	case 'j':
			luna-=4; //Caso que permite que las lunas giren alrededor de sus planetas
            glutPostRedisplay();
            break;

/////////////////////////////////////////////////


		case 'q':
			day_mercurio = (day_mercurio + 10) % 360;
			glutPostRedisplay();
			break;
		case 'Q':
			day_mercurio = (day_mercurio - 10) % 360;
			glutPostRedisplay();
			break;

		case 'w':
			day_venus = (day_venus + 10) % 360;
			glutPostRedisplay();
			break;
		case 'W':
			day_venus = (day_venus - 10) % 360;
			glutPostRedisplay();
			break;

		case 'e':
			day_earth = (day_earth + 10) % 360;
			glutPostRedisplay();
			break;
		case 'E':
			day_earth = (day_earth - 10) % 360;
			glutPostRedisplay();
			break;

		case 'r':
			day_mars = (day_mars + 10) % 360;
			glutPostRedisplay();
			break;
		case 'R':
			day_mars = (day_mars - 10) % 360;
			glutPostRedisplay();
			break;

		case 't':
			day_jupter = (day_jupter + 10) % 360;
			glutPostRedisplay();
			break;
		case 'T':
			day_jupter = (day_jupter - 10) % 360;
			glutPostRedisplay();
			break;

		case 'y':
			day_saturn = (day_saturn + 10) % 360;
			glutPostRedisplay();
			break;
		case 'Y':
			day_saturn = (day_saturn - 10) % 360;
			glutPostRedisplay();
			break;

		case 'u':
			day_urain = (day_urain + 10) % 360;
			glutPostRedisplay();
			break;
		case 'U':
			day_urain = (day_urain - 10) % 360;
			glutPostRedisplay();
			break;

		case 'i':
			day_neturn = (day_neturn + 10) % 360;
			glutPostRedisplay();
			break;
		case 'I':
			day_neturn = (day_neturn - 10) % 360;
			glutPostRedisplay();
			break;

		case 'm':
			day_moon = (day_moon + 15) % 360;
			glutPostRedisplay();
			break;
		case 'M':
			day_moon = (day_moon - 15) % 360;
			glutPostRedisplay();
			break;
		case 'z':
			year = (year+5) % 360;
			glutPostRedisplay();
			break;
		case 'Z':
			year = (year - 5) % 360;
			glutPostRedisplay();
			break;
		default:
			break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1000, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
