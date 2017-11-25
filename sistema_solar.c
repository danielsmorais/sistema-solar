#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int year = 0, day_moon = 0;
static int day_mercurio = 0, day_venus = 0, day_earth = 0, day_mars = 0, day_jupter = 0, day_saturn = 0;
static int day_urain = 0, day_neturn = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   glPushMatrix();
	   glutWireSphere(1.0, 20, 16);   /* draw sun */
	   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
	   glTranslatef (1.5, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_mercurio, 0.0, 1.0, 0.0);
		   glutWireSphere(0.08, 10, 8);    /* draw mercurio */
	   glPopMatrix();
	   glTranslatef (0.7, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_venus, 0.0, 1.0, 0.0);
		   glutWireSphere(0.1, 10, 8);    /* draw venus */
	   glPopMatrix();
	   glTranslatef (0.7, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_earth, 0.0, 1.0, 0.0);
		   glutWireSphere(0.2, 10, 8);    /* draw earth */
	   glPopMatrix();
	   glTranslatef (0.7, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_mars, 0.0, 1.0, 0.0);
		   glutWireSphere(0.15, 10, 8);    /* draw mars */
	   glPopMatrix();
	   glTranslatef (1.3, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_jupter, 0.0, 1.0, 0.0);
		   glutWireSphere(0.6, 15, 10);    /* draw jupter */
	   glPopMatrix();
	   glRotatef (-15, 1.0, 0.0, 0.0);
	   glTranslatef (2.0, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_saturn, 0.0, 1.0, 0.0);
		   glutWireSphere(0.5, 15, 10);    /* draw saturn */
	   glPopMatrix();
	   glTranslatef (1.8, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_urain, 0.0, 1.0, 0.0);
		   glutWireSphere(0.2, 10, 8);    /* draw urain */
	   glPopMatrix();
	   glTranslatef (1.0, 0.0, 0.0);
	   glPushMatrix();
		   glRotatef ((GLfloat) day_neturn, 0.0, 1.0, 0.0);
		   glutWireSphere(0.1, 10, 8);    /* draw neturn */
	   glPopMatrix();
   glPopMatrix();

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
         year = (year + 5) % 360;
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
