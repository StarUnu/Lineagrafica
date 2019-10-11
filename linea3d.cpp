#include <GL/glut.h>
 GLfloat xRotated, yRotated, zRotated;
void init(void)
{
glClearColor(0,0,0,0);
 
}
int fabs(int derivadas){
  if (derivadas<0){
    return derivadas*-1;  
  }
  return derivadas;
}
void lineaDDA_dos(float xEnd,float yEnd, float x0, float y0,float z0)
{
  float dx = xEnd - x0, dy = yEnd - y0, steps, k;
  float xIncrement, yIncrement, x = x0, y = y0;
  if (fabs (dx) > fabs (dy))//pendiente positiva
    steps = fabs (dx);
  else
    steps = fabs (dy);
  xIncrement = float (dx) / float (steps);
  yIncrement = float (dy) / float (steps);
  int r,g,b;
  r=0;g=0;b=1;
  glBegin(GL_POINTS);
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f(x,y,z0);
  glEnd();

  for ( k = 0; k < steps; k+=0.1) {
  x += xIncrement;
  y += yIncrement;  
  glBegin(GL_POINTS);
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f(x,y,z0);
  glEnd();
  }
}

void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin (GL_POINTS);
  glColor3f(1.0f,0.0f,1.0f); 
  glColor3f(1.0f,0.0f,2.0f);
  glColor3f(1.0f,0.0f,3.0f);  
  glVertex3f (0, 0, 0);
   glEnd ();
   /*
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(0.7f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.5f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid

   
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(0.5f, -1.0f, 1.0f);
      glColor3f(1.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
   glEnd();  
   */
   glBegin(GL_LINES); 
   glVertex3f(0.0f, 0.0f, 0.0f);
   glVertex3f(50.0f, 50.0f, 50.0f);
   glEnd();

   lineaDDA_dos(0.0f, 0.0f,50.0f, 50.0f,00.0f);
glFlush();
}


void animation(void)
{
     yRotated += 0.01;
     xRotated += 0.02;
    DrawCube();
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
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
//Set the function for the animation.
glutIdleFunc(animation);
glutMainLoop();
return 0;
}