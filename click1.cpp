//Grafico en 2D
//Uso
// g++ click1.cpp -o click1 -lglut -lGLU -lGL
// ./click1
// Hacer click derecho y mantenerlo apretado hasta el punto que se quiere trazar la linea
// despues se hace click derecho a la pantalla, haciendo los vertices del poligono
// con click izquierdo se junta los vertices 
// con  los direccionales del teclado se puede mover el poligono(trasladarse)
// con shift(pausa) se puede engrandar el poligono (escalamiento)
// con shift(flecha arriba) se puede disminuir el poligono (escalamiento)
// con alt se puede rotar el poligo en 45 grados
// con control se puede colorear el poligono 

#include<GL/glut.h> 
#include<stdlib.h> 
#include<iostream>
#include<vector>
#include<cmath>
#include "PintarPoligono.h"
using namespace std;
int up, down;
float r,g,b,x,y,x_a,y_a;
vector<vector<float>> datos ;
int desplazamiento=10;
float escala_me=0.9;///2*0.9=1.8 , no lo pierde todo
float escala_gra=1.5;///tiene que ser mayor a 1 para aumente y se expanda
int tamano_pantallax=1000;//ancho
int tamano_pantallay=700;//alto

//algoritmo incremental
void linea()
{
  glBegin(GL_POINTS);
  glColor3f(1,0,0);
  float dy,dx,m;
  float xd,yd,x1,y1,x2,y2;
  
  if(y_a>=y and x>=x_a){
  x2=x;
  y2=y;
  x1=x_a;
  y1=y_a;
  }
  if(y_a>=y and x<=x_a){
  x2=x_a;
  y2=y_a;
  x1=x;
  y1=y;
  }
  if(y_a<=y and x_a<=x){
  x1=x_a;
  y1=y_a;
  x2=x;
  y2=y; 
  }
  if(y_a<=y and x_a>=x){
  x1=x;
  y1=y;
  x2=x_a;
  y2=y_a; 
  }
  dy=y2-y1;
  dx=x2-x1; 
  m=dy/dx;
  for(xd=x1;xd<=x2;xd++){
      yd=(y1+m*(xd-x1));
      glVertex2f(xd,yd);
  }
  glEnd();
  glFlush();
}

void lineaDDA()
{
  int xEnd=x;
  int yEnd=y;
  int x0=x_a;
  int y0=y_a;
  int dx = xEnd - x0, dy = yEnd - y0, steps, k;
  float xIncrement, yIncrement, x = x0, y = y0;
  if (fabs (dx) > fabs (dy))//pendiente positiva
    steps = fabs (dx);
  else
    steps = fabs (dy);//pendiente negativa
  xIncrement = float (dx) / float (steps);
  yIncrement = float (dy) / float (steps);
  int r,g,b;
  r=0;g=0;b=1;
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  for ( k = 0; k < steps; k++) {
  x += xIncrement;
  y += yIncrement;
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  }
}

void lineaDDA_dos(int xEnd,int yEnd, int x0, int y0)
{
  int dx = xEnd - x0, dy = yEnd - y0, steps, k;
  float xIncrement, yIncrement, x = x0, y = y0;
  if (fabs (dx) > fabs (dy))//pendiente positiva
    steps = fabs (dx);
  else
    steps = fabs (dy);//pendiente negativa
  xIncrement = float (dx) / float (steps);
  yIncrement = float (dy) / float (steps);
  int r,g,b;
  r=0;g=0;b=1;
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();

  for ( k = 0; k < steps; k++) {
  x += xIncrement;
  y += yIncrement;
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  }
}


void lineaptomedio()
{
  float dx,dy,x1,y1,x2,y2,d,incE,incNE;
  glBegin(GL_POINTS);
  glColor3f(0,0,1);
  glVertex2f(x,y);
  glEnd();
  glBegin(GL_POINTS);
  glColor3f(0,0,1);
  if(x_a<x){
  x2=x;
  y2=y;
  x1=x_a;
  y1=y_a;
  }
  dx=x2-x1;
  dy=y2-y1;
  d=2*dy-dx;
  incE=2*dy;
  incNE=2*(dy-dx);
  glVertex2f(x1,y1);
  while(x1<x2){
    if(d<=0){
      d=d+incE;
      x1=x1+1;
    }
    else{
      d=d+incNE;
      x1=x1+1;
      y1=y1+1;
    }
    glVertex2f(x1,y1);
  }
  //tratando que acepte el otro lado :'o
 int i=0;
  while(x2<x1){
    if(d<=0){
      d=d+incE;
      x2=x2-1;
    }
    else{
      d=d+incNE;
      x2=x2-1;
      y2=y2+1;
    }
    i+=1;
    glVertex2f(x2,y2);
  }
  glEnd();
}

void plot_polygon(){
  int tamano=datos.size();
  for(int i=0;i+1<tamano;)
  {
    if(i+1<tamano){
      lineaDDA_dos(datos[i][0], datos[i][1], datos[i+1][0],datos[i+1][1]);
      glBegin(GL_POINTS);
      glColor3f(0,0,1);
      glVertex2f(x,y);
      glEnd();
      cout<<"dos veces "<<endl;
      cout<<datos[i][0]<<datos[i][1]<<datos[i+1][0]<<datos[i+1][1]<<endl;
    }
    i+=1;
  }
  lineaDDA_dos(datos[0][0], datos[0][1], datos[tamano-1][0],datos[tamano-1][1]);
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        x_a = mousex;
        y_a = tamano_pantallay-mousey;
        vector<float> pares;
        pares.push_back(x_a);
        pares.push_back(y_a);
        datos.push_back(pares);
        r=1;
        g=0;
        b=0;
    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
      x = mousex;
      y = tamano_pantallay-mousey;
      r=1;
      g=0;
      b=0;
      //linea();//metodo incremental
      lineaDDA();
      //punto_medio();
      //lineaptomedio();
      //MidPointCircle();
    }
    if(button==GLUT_RIGHT_BUTTON ){
      //graficar los poligonos
      datos.push_back(datos[0]);
      plot_polygon();
    }
    glutPostRedisplay();
}


void keyboard(int key, int x, int y) {
  glClearColor(1, 1, 1, 0); //limpia la pantalla
  glClear(GL_COLOR_BUFFER_BIT);
  if (key==GLUT_KEY_UP){//flecha arriba del teclado,traslación arriba
    up = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]+=desplazamiento;
    }
    plot_polygon();
  }
  if (key==GLUT_KEY_DOWN){//flecha arriba del teclado,traslación abajo
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]-=desplazamiento;
    }
    plot_polygon();
  }
  if (key==GLUT_KEY_LEFT){//flecha arriba del teclado,traslación izquierda
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]-=desplazamiento;
    }
    plot_polygon();
   }
   if (key==GLUT_KEY_RIGHT){//flecha arriba del teclado,traslación derecha
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]+=desplazamiento;
    }
    plot_polygon();

   } 

   if(key==112){//tecla shift(flecha para arriba), escalamiento negativo
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]*= escala_me;
      datos[i][1]*= escala_me;
    }
    plot_polygon();
   }

   if(key==115){//tecla control, relleno de poligono
    PintarPoligono rellenopoligono;
    rellenopoligono.display_(datos);
   }


   if(key==113){//tecla shift(flecha para arriba), escalamiento positivo
    cout<<"imprimiendo más deberas en enl maas"<<endl;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]*= escala_gra;
      datos[i][1]*= escala_gra;
    }
    plot_polygon();
    for(int i=0;i<tamano;i++)
    {
      cout<<datos[i][0]<<endl;
      cout<<datos[i][1]<<endl;
    }
   }

   if(key==116){//rotacion 45 grados
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      int next=i+1;
      cout<<"x="<<datos[i][0]<<endl;
      cout<<"y="<<datos[i][1]<<endl;
      float tempx=datos[i][0];
      datos[i][0]=200+(datos[i][0]-200)*sqrt(2)/2 - (datos[i][1]-200)*sqrt(2)/2;
      datos[i][1]=200+(tempx-200)*sqrt(2)/2 + (datos[i][1]-200)*sqrt(2)/2;
      cout<<" "<<datos[i][0]<<endl;
      cout<<" "<<datos[i][1]<<endl;
    }
    plot_polygon();
   }
    glutPostRedisplay();
}


void display()
{  
    glColor3f(r,g,b); 
    glPointSize(4); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, tamano_pantallax, 0.0, tamano_pantallay);

    glFlush();     // flushes the frame buffer to the screen


}

int main(int argc,char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(tamano_pantallax,tamano_pantallay);
  glutInitWindowPosition(10,10);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("DDA Line Drawing");
  glClearColor(1, 1, 1, 0); 
  glClear(GL_COLOR_BUFFER_BIT); //limpia el buffer con los valores glClearColor

  glutDisplayFunc(display);//links the display event with the display event handler(display)
  glutMouseFunc(mouse);//keyboard event handler
  glutSpecialFunc(keyboard);
  glutMainLoop();//loops the current event
}
