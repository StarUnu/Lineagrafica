#include <GL/glut.h>
#include<iostream>
using namespace std;
GLfloat xRotated, yRotated, zRotated;

bool fullscreen = false;
bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

void init(void)
{
glClearColor(0, 0, 0, 0);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
glClearDepth(1.0f);
}

int fabs(int derivadas){
  if (derivadas<0){
    return derivadas*-1;  
  }
  return derivadas;
}


void lineaDDA_dos(float x2,float y2,float z2, float x1, float y1,float z1)
{
  float dx = x2 - x1, dy = y2 - y1,dz= z2-z1, steps, k;
  float xIncrement, yIncrement, zIncrement, x = x1, y = y1, z=z1;
  if (fabs (dx) > fabs (dy))//pendiente positiva
    steps = fabs (dx);
  else
    steps = fabs (dy);
  xIncrement = dx / float (steps);
  yIncrement = dy / float (steps);
  zIncrement = dz / float (steps);

  glBegin(GL_POINTS);
  glVertex3f(x,y,z);
  glEnd();

  for ( k = 0; k < steps; k+=0.1) {
  x += xIncrement;
  y += yIncrement;
  z += zIncrement;
  glBegin(GL_POINTS);
  glVertex3f(x,y,z);
  glEnd();
  }
}

void plot_pixel(float x, float y, float z)
{
  glBegin(GL_POINTS);
  glColor3f(1,0,0);
  x=y=z=0;
  cout<<"x="<<x<<"y="<<y<<"z="<<z<<endl;
  glVertex3f(x,y,z);
  glEnd();
  glFlush();
}


//algoritmo incremental
void linea(float x1, float y1, float z1, float x2,float y2,float z2)
{
  glBegin(GL_POINTS);
  float m,x,y,z,dy,dx;  
  dy=y2-y1;
  dx=x2-x1; 
  m=dy/dx;
  for(x=x1;x<=x2;x+=0.01){
      y=(y1+m*(x-x1));
      glVertex3f(x,y,x);
  }
  glEnd();
  glFlush();
}

void displey(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(0.0f, 0.0f, 3.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
  glRotatef(xrot, 1.0f, 0.0f, 0.0f);
  glRotatef(yrot, 0.0f, 1.0f, 0.0f);
 
  glMatrixMode(GL_MODELVIEW);
  // clear the drawing buffer.
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1,0,0);
  glBegin(GL_LINES); //y
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 2.0f, 0.0f);
  glEnd();
  glColor3f(0,0,1);
  glBegin(GL_LINES);//x 
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(2.0f, 0.0f, 0.0f);
  glEnd();

  glColor3f(0,1,0);
  glBegin(GL_LINES); //z
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 2.0f);
  glEnd();

   glColor3f(0,1,1);
   glPointSize(4); 
   linea(-0.5f, -0.5f,-0.5f,0.5f,0.5f,0.5f);
   //lineaDDA_dos(-0.5f, -0.5f,-0.5f,0.8f,0.8f,0.8f);
    glColor3f(0,1,1);
  /* //verificando
   glBegin(GL_LINES); 
   glVertex3f(-0.5f, -0.5f,-0.5f);
   glVertex3f(0.8f,0.8f,0.8f);
   glEnd();*/

  glFlush();
  glutSwapBuffers();
}


void resize(int w, int h)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mouseDown = true;
    xdiff = x - yrot;
    ydiff = -y + xrot;
  }
  else
    mouseDown = false;
}

void mouseMotion(int x, int y)
{
  if (mouseDown)
  {
    yrot = x - xdiff;
    xrot = y + ydiff;
    glutPostRedisplay();
  }

}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutInitWindowSize(600,600);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(displey);
glutMouseFunc(mouse);
glutMotionFunc(mouseMotion);
glutReshapeFunc(resize);
glutMainLoop();
return 0;
}