#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "texture.h"

# define PI	3.14159265358979323846

#define true 1
#define false 0
typedef int bool;

static int year = 0, day_moon = 0;
static int day_mercurio = 0, day_venus = 0, day_earth = 0, day_mars = 0, day_jupter = 0, day_saturn = 0;
static int day_urain = 0, day_neturn = 0;
static double zoom = 0, lookSide = 0, moveSide = 0, moveUpDown = 0;

GLuint textura[11];
float anoA = 0,anoB = 0, anoC = 0, dia = 0, luna=0;
int angulo_z = 0;



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

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
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
	textura[9] = LoadBitmap("media/Tierra/Luna.bmp");
	textura[10] = LoadBitmap("media/estrellas_03.bmp");


	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);

	//negocio para nao ficar mais transparente
	glEnable(GL_DEPTH_TEST);

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	glLineWidth(1.0f);
	glPushMatrix();
	glRotatef((GLfloat) 90.0, 1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
	glPopMatrix();
}

 void planeta(float ano, float dia, float lua, float raio, float distancia, GLuint text,bool truelua)
 {

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricOrientation(qobj, GLU_OUTSIDE);	
	gluQuadricDrawStyle(qobj, GLU_FILL);
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
            gluSphere(qobj,raio, 30, 30);            /* desenha o planeta */
			glDisable(GL_TEXTURE_2D);
        glPopMatrix();
		if(truelua){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textura[9]);
			glRotatef (25, 0.0, 0.0, 0.0);              //angulo da lua em relação ao planeta
			glRotatef ((GLfloat) lua, 0.0, 1.0, 0.0);   //angulo da lua de acordo coma hora
			glTranslatef (0.3, 0.0, 0.0);               //Distancia da lua em relação ao planeta
			gluSphere(qobj,0.1, 30, 30);				// desenha a lua /// modificar
			glDisable(GL_TEXTURE_2D);
		}

		gluDeleteQuadric(qobj);

    glPopMatrix();
 }


 void espaco(void)
 {
	glPushMatrix();
	//desenha espaço com estrelas
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textura[10]);
	
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj,30, 30, 30);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
 }


void display(void)
{    
	glMatrixMode(GL_MODELVIEW);
	
   	glClear (GL_COLOR_BUFFER_BIT);
   	glColor3f (1.0, 1.0, 1.0);

	GLUquadric *qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
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
    gluSphere(qobj,1, 30, 30);
	gluDeleteQuadric(qobj);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
    planeta(anoA,dia,luna,0.2,2,textura[1],false); //mercurio
	drawHollowCircle(0,0,2);
    planeta(anoA*0.9,dia,luna,0.3,3,textura[2],false); //venus
	drawHollowCircle(0,0,3);
    planeta(anoA*0.8,dia,luna,0.2,3.5,textura[3],true); //terra
	drawHollowCircle(0,0,3.5);
	planeta(anoA*0.7,dia,luna,0.2,4,textura[4],false); //marte
	drawHollowCircle(0,0,4);
    planeta(anoA*0.6,dia,luna,0.2,5,textura[5],false); //jupiter
	drawHollowCircle(0,0,5);
    planeta(anoA*0.5,dia,luna,0.2,6,textura[6],false); //saturno
	drawHollowCircle(0,0,6);
	planeta(anoA*0.4,dia,luna,0.2,7,textura[7],false); //urano
	drawHollowCircle(0,0,7);
    planeta(anoA*0.3,dia,luna,0.2,8,textura[8],false); //netuno
	drawHollowCircle(0,0,8);

	espaco();
	
    glutSwapBuffers();

}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 40.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (lookSide+7.0, zoom+3, 0.01, moveSide, moveUpDown, 0.0, 0.0, 1.0, 0.0);
   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		//melhora a qualidade dos gráficos
   glutPostRedisplay();
}

void idle(void)
{
    anoA-=1; 
    anoB-=0.5;
    anoC-=0.25;
    dia-=8;
    luna-=5;
    glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y)
{
   switch (key) {

   		case 'p':
   			if(moveUpDown > -1.9)
   				moveUpDown -= 0.2;
   			reshape(1000,500);
   			break;
   		case 'l':
   			if(moveUpDown < 1.9)
   				moveUpDown += 0.5;
   			reshape(1000,500);
   			break;
   		case '[':
   			if(moveSide > -10)
   				moveSide -= 0.5;
   			reshape(1000,500);
   			break;
   		case ']':
   				moveSide += 0.5;
   			reshape(1000,500);
   			break;
   		case '+':
   			if(zoom > 0)
   				zoom -= 0.5;
   			reshape(1000,500);
   			break;
   		case '-':
   			if(zoom < 20)
   				zoom += 0.5;
   			reshape(1000,500);
   			break;
   		case '.':
   			if(lookSide < 15)
   				lookSide += 1;
   			reshape(1000,500);
   			break;
   		case ',':
   			if(lookSide > -15)
   				lookSide -= 1;
   			reshape(1000,500);
   			break;
      case 27:
         	exit(0);			   

/////////////////////////////////////////////////

        case 'g':
			anoA-=4; 			//Planetas transladarem em suas orbitas
            anoB-=2;
            anoC-=1;
            glutPostRedisplay();
            break;
        case 'h':
			dia--; 				//Permite que os planetas girem sobre o próprio eixo
            glutPostRedisplay();
            break;
    	case 'j':
			luna-=4; 			//Permite que as luas girem em torno de seus planetas
            glutPostRedisplay();
            break;

/////////////////////////////////////////////////

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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //GLUT_DEPTH: buffer para evitar transparencia(por profundidade)
   glutInitWindowSize (1000, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
