//Grafico en 2D
//Uso
// g++ click1.cpp -o click1 -lglut -lGLU -lGL
// ./click1
// Hacer click derecho se grafica un circulo, puede hacer varios
// circulo con radio de 30
// con  los direccionales del teclado se puede mover el poligono(trasladarse)
// con shift(pausa) se puede engrandar el poligono
// con control(alado del alt gr) se puede disminuir el poligono
// con alt se puede rotar el poligo en 45 grados

#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
int tamano_pantallax=1000;
int tamano_pantallay=700;
int ro=0;
int g=0;
int b=1;
int desplazamiento=10;
float escala_me=0.9;///2*0.9=1.8 , no lo pierde todo
float escala_gra=1.5;///tiene que ser mayor a 1 para aumente y se expanda

vector<vector<float>> datos ;

void setPixel (float xCoord, float yCoord)
{
	glBegin (GL_POINTS);
	
	vector<float> punto;
	punto.push_back(xCoord);
	punto.push_back(yCoord);
	datos.push_back(punto);
    glColor3f(ro,g,b);
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

void plot_circle(){
	int tamano=datos.size();
	for(int i=0;i<tamano;i++)
    {
    	glBegin(GL_POINTS);
     	glColor3f(ro,g,b);
		glVertex2f (datos[i][0],datos[i][1]);
		glEnd ( );
    }
}
void circleMidpoint2(float x, float y,int r){
	float d,tempx,tempy;
	tempx=0;
	tempy=r;
	d=5/4-r;
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


void eclipseMidpoint(float x, float y){
	float d,d2,tempx,tempy;
	tempx=0;
	tempy=y;
	d=y*y - x*x*y + x*x/4.0;
	setPixel(tempx,tempy);
	while (x*x*(tempy-0.5)>y*y*(tempx+1)){
		if(d<0){
			d=d+y*y*(2*tempx+3);
			tempx++;
		}
		else{
			d=d+y*y*(2*tempx+3)+x+x*(-2*y+2);
			tempx++;
			tempy--;
		}
		setPixel(tempx,tempy);
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
    //eclipseMidpoint(100,100);

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
		circleMidpoint2(xc,yc,30);
    }
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
  glClearColor(1, 1, 1, 0); //limpia la pantalla
  glClear(GL_COLOR_BUFFER_BIT);
  if (key==GLUT_KEY_UP){
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]+=desplazamiento;
    }
    plot_circle();
  }
  if (key==GLUT_KEY_DOWN){
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]-=desplazamiento;
    }
    plot_circle();
  }

  if (key==GLUT_KEY_LEFT){
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]-=desplazamiento;
    }
    plot_circle();
   }

   if (key==GLUT_KEY_RIGHT){
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]+=desplazamiento;
    }
    plot_circle();

   } 

   if(key==115){//control
    cout<<"imprimiendo menos debera en el menos"<<endl;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]*= escala_me;
      datos[i][1]*= escala_me;
    }
    plot_circle();
   }

   if(key==113){//pausao shift :v
    cout<<"imprimiendo más deberas en enl maas"<<endl;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]*= escala_gra;
      datos[i][1]*= escala_gra;
    }
	plot_circle();
    for(int i=0;i<tamano;i++)
    {
      cout<<datos[i][0]<<endl;
      cout<<datos[i][1]<<endl;
    }
   }

   if(key==116){
    //cout<<"engrandiamiento debera??"<<endl;
    //cout<<"imprimiendo más deberas en enl maas"<<endl;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      int next=i+1;
      //float r = sqrt(pow(datos[i][0],2)+pow(datos[i][1],2));
      //nt t_x=r*cos(45);
      cout<<"x="<<datos[i][0]<<endl;
      cout<<"y="<<datos[i][1]<<endl;
      float tempx=datos[i][0];
      datos[i][0]=200+(datos[i][0]-200)*sqrt(2)/2 - (datos[i][1]-200)*sqrt(2)/2;
      datos[i][1]=200+(tempx-200)*sqrt(2)/2 + (datos[i][1]-200)*sqrt(2)/2;
      cout<<" "<<datos[i][0]<<endl;
      cout<<" "<<datos[i][1]<<endl;
    }
    cout<<"coseno"<<sqrt(2)/2<<endl;
    cout<<"coseno"<<cos(45)<<endl;
	plot_circle();
    for(int i=0;i<tamano;i++)
    {
      cout<<"PUNTO"<<endl;
      
    }
   }
   cout<<"esto seria ENTRA ACAAA"<<key<<endl;
    glutPostRedisplay();
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
    glutInitWindowSize(tamano_pantallax,tamano_pantallay); 
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Circulo");
    glClearColor(1, 1, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT);
  	glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutMainLoop();//loops the current event
	return 0;
}