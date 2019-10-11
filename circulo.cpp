#include <GL/glut.h>
#include <iostream>

using namespace std;
float xmouse,ymouse;
class screenPt
{
private:
GLint x, y;

public:
/* Constructor predeterminado: inicializa las coordenadas a (0, 0). */
screenPt ( ) {
x = y = 0;
}
void setCoords (GLint xCoordValue, GLint yCoordValue) {
x = xCoordValue;
y = yCoordValue;
}

GLint getx ( ) const {
return x;
}
GLint gety ( ) const {
return y;
}
void incrementx ( ) {
	x++;
}
void decrementy ( ) {
	y--;
}
};
void setPixel (GLint xCoord, GLint yCoord)
{
	int r,g,b;
glBegin (GL_POINTS);

r=1;//(rand()%9)/8;
g=0;//(rand()%9)/8;
b=0;
glColor3i(r,g,b);
glVertex2i (xCoord, yCoord);
glEnd ( );
}
void circleMidpoint (GLint xc, GLint yc, GLint radius)
{
	

	screenPt circPt;

	GLint p = 1 - radius;
	
	// Valor inicial para el parámetro de punto medio.
	circPt.setCoords (xc, yc+radius); // Establecer coordenadas para
	// punto superior del círculo.
	void circlePlotPoints (GLint, GLint, screenPt);
	/* Dibujar el punto inicial en cada cuadrante del círculo. */
	circlePlotPoints (xc, yc, circPt);

	/* Calcular el siguiente punto y dibujarlo en cada octante. */
	while (circPt.getx ( ) < circPt.gety ( )) {
		circPt.incrementx ( );
		if (p < 0)
		p += 2 * circPt.getx ( ) + 1;
		else {
		circPt.decrementy ( );
		p += 2 * (circPt.getx ( ) - circPt.gety ( )) + 1;
		}
		circlePlotPoints (xc, yc, circPt);
	}
	
   
}

void circlePlotPoints (GLint xc, GLint yc,screenPt circPt)
{
setPixel (xc + circPt.getx ( ), yc+circPt.gety());
setPixel (xc - circPt.getx ( ), yc+circPt.gety());
setPixel (xc + circPt.getx ( ), yc+circPt.gety());
setPixel (xc - circPt.getx ( ), yc+circPt.gety());
setPixel (xc + circPt.gety ( ), yc+circPt.gety());
setPixel (xc - circPt.gety ( ), yc+circPt.gety());
setPixel (xc + circPt.gety ( ), yc+circPt.gety());
setPixel (xc - circPt.gety ( ), yc+circPt.gety());
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
    	GLint xmouse = mousex;
        GLint ymouse = mousey;//480-mousey; 
        GLint radio=10;
        //circleMidpoint(xmouse,ymouse,radio);
    }

    glutPostRedisplay();
}


void display()
{  
	float r,g,b;
	r=1;//(rand()%9)/8;
    g=0;//(rand()%9)/8;
    b=0;
    glColor3f(r,g,b); // sets the current drawing (foreground) color to blue 
    glPointSize(4); // sets the size of points to be drawn (in pixels)
   
    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);//sets the parallel(orthographic) projection of the full frame buffer 
    //GLint xmouse = mousex;
    //GLint ymouse = mousey;//480-mousey; 
    int  radio=30;
    circleMidpoint(50,50,radio);
    //cout<<"bandera"<<!is_grafica<<endl;


    glFlush();     // flushes the frame buffer to the screen
}
int main(int argc,char** argv)
{
	cout<<"salio"<<endl;
	glutInit(&argc,argv);
    glutInitWindowSize(640,480);   //sets the width and height of the window in pixels
    glutInitWindowPosition(10,10);//sets the position of the window in pixels from top left corner 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
    glutCreateWindow("DDA Line Drawing");//creates the window as specified by the user as above.
        
    glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
  
    glutDisplayFunc(display);//links the display event with the display event handler(display)
    glutMouseFunc(mouse);//keyboard event handler
    glutMainLoop();//loops the current event
	return 0;
}