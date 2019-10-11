#include <GL/glut.h>
#include <iostream>

using namespace std;
int tamano_pantallax=1000;
int tamano_pantallay=700;
/*class screenPt
{
	private:
	GLint x, y;
	public:
	//Constructor predeterminado: inicializa las coordenadas a (0, 0). 
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

void circleMidpoint (GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;
	GLint p = 1 - radius;
	// Valor inicial para el parámetro de punto medio.
	circPt.setCoords (0, radius); // Establecer coordenadas para
	// punto superior del círculo.
	void circlePlotPoints (GLint, GLint, screenPt);
	// Dibujar el punto inicial en cada cuadrante del círculo. 
	circlePlotPoints (xc, yc, circPt);
	//Calcular el siguiente punto y dibujarlo en cada octante.
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

void circlePlotPoints (GLint xc, GLint yc, screenPt circPt )
{
	
	setPixel (xc + circPt.getx ( ), yc + circPt.gety());
	setPixel (xc - circPt.getx ( ), yc + circPt.gety());
	setPixel (xc + circPt.getx ( ), yc - circPt.gety());
	setPixel (xc - circPt.getx ( ), yc - circPt.gety());
	setPixel (xc + circPt.gety ( ), yc + circPt.getx());
	setPixel (xc - circPt.gety ( ), yc + circPt.getx());
	setPixel (xc + circPt.gety ( ), yc - circPt.getx());
	setPixel (xc - circPt.gety ( ), yc - circPt.getx());
	glutPostRedisplay();
}
*/

void setPixel (float xCoord, float yCoord)
{
	glBegin (GL_POINTS);
	int r,g,b;
	r=g=0;
	b=1;
    glColor3f(r,g,b);
	glVertex2f (xCoord, yCoord);
	glEnd ( );
}

void circlePlotPoints (float x, float y, float tx, float ty)
{
	setPixel (x + tx, y + ty);
	setPixel (x - tx, y + ty);
	setPixel (x + tx, y - ty);
	setPixel (x - tx, y - ty);
	setPixel (x + ty, y + tx);
	setPixel (x - ty, y + tx);
	setPixel (x + ty, y - tx);
	setPixel (x - ty, y - tx);
	glutPostRedisplay();
}

void circleMidpoint2(float x, float y,int r){
	float d,tempx,tempy;
	tempx=0;
	tempy=r;
	d=5/4-r;
	glBegin(GL_POINTS);
	int ro,g,b;
	ro=1;g=0;
	b=0;

	circlePlotPoints(x,y,tempx,tempy);
	while (tempy>tempx){
		if(d<0){
			d=d+2*tempx+3;
			tempx++;
		}
		else{
			d=d+2*(tempx-tempy)+5;
			tempx++;
			tempy--;
		}
		circlePlotPoints(x,y,tempx,tempy);
	}
	glEnd ( );
}



void display()
{  
    glPointSize(2); // sets the size of points to be drawn (in pixels) 
    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    
    gluOrtho2D(0.0, tamano_pantallax, 0.0, tamano_pantallay);//sets the parallel(orthographic) projection of the full frame buffer 
    //circleMidpoint(100,100,30);
    

    glFlush();     // flushes the frame buffer to the screen
}

void mouse(int button, int state, int mousex, int mousey)
{

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ){
		float xc = mousex;
		float yc = tamano_pantallay-mousey;
		int r,g,b;
		r=g=0;
		b=1;
		glBegin (GL_POINTS);
		glColor3f(r,g,b);
		glPointSize(10); 
		glVertex2f(xc,yc);
		glEnd();
		circleMidpoint2(xc,yc,30);
    }
    glutPostRedisplay();
}
int main(int argc,char** argv){
	glutInit(&argc,argv);
    glutInitWindowSize(tamano_pantallax,tamano_pantallay);   //sets the width and height of the window in pixels
    glutInitWindowPosition(10,10);//sets the position of the window in pixels from top left corner 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
    glutCreateWindow("Circulo");//creates the window as specified by the user as above.
    //glutSpecialFunc(keyboard);
    glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
  	glutMouseFunc(mouse);
    glutDisplayFunc(display);//links the display event with the display event handler(display)
    //glutMouseFunc(mouse);//keyboard event handler
    glutMainLoop();//loops the current event
	return 0;
}