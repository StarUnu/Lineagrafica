#include<GL/glut.h> //includes the opengl, glu, and glut header files
#include<stdlib.h> //includes the standard library header file
#include<iostream>
#include<vector>
#include<cmath>
//http://fernandez-torres-jose.blogspot.com/2012/09/21-transformaciones-bidimensionales.html
//https://community.khronos.org/t/get-keyboard-input/31724/8
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
//https://stackoverflow.com/questions/8629172/how-write-glut-keyboard-functions
//https://dare2compete.com/bites/everything-you-need-to-know-about-programming-in-python/?fbclid=IwAR3UjGAVVefcBlt_TtfDTcA8xqpS_7RU_qZMeAg8t77FjKlX1d3jcVn4A_U
//https://www.superprof.es/apuntes/escolar/matematicas/trigonometria/seno-coseno-y-tangente-de-30o-45o-y-60o.html
using namespace std;
int up, down;
float r,g,b,x,y,x_a,y_a;
bool check=true;
int numclick=0;
bool is_grafica=true;
int entro=0;
vector<vector<float>> datos ;
bool primer_punto= false;
int desplazamiento=10;
float escala_me=0.9;///2*0.9=1.8 , no lo pierde todo
float escala_gra=1.5;///tiene que ser mayor a 1 para aumente y se expanda
int tamano_pantallax=1000;//ancho
int tamano_pantallay=700;//alto
//parte de una circunferencia
void MidPointCircle(){

float d;
/* Valores iniciais */
int re,g,b;

re=0;g=0;b=1;

glBegin(GL_POINTS);
glColor3f(re,g,b);
glVertex2f(x,y);
glEnd();

int r=10;
x = x;
y = y+r;

d = 5/4 - r;

while (y > x){
  if (d < 0){
  /* Selecione E */
  d = d + 2 * x + 3;
  x++;
  }else{
  /* Selecione SE */
  d = d + 2 * (x - y) + 5;
  x++;
  y--;
  }/*end if*/

  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  cout<<"no entra axa"<<x<<"y="<<y<<endl;
}/* end while */

}/* end MidpointCircle */
int fabs(int derivadas){
  if (derivadas<0){
    return derivadas*-1;  
  }
  return derivadas;
}


void punto_medio(){
  int x0=x_a;
  int y0=y_a;
  int xEnd=x;
  int yEnd=y;
  int dx = fabs (xEnd - x0), dy = fabs(yEnd - y0);
  int p = 2 * dy - dx;
  int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
  int x, y;
  /* Determinar qué extremo usar como posición inicial. */
  if (x0 > xEnd) {
    x = xEnd;
    y = yEnd;
    xEnd = x0;
  }
  else {
    x = x0;
    y = y0;
  }

  int r,g,b;
  r=0;g=0;b=1;

  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();

  while (x < xEnd) {
    x++;
    if (p < 0)
     p += twoDy;
    else {
    y++;
    p += twoDyMinusDx;
    }

  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  }
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
  //setPixel (round (x), round (y));
  int r,g,b;
  r=0;g=0;b=1;
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();

  for ( k = 0; k < steps; k++) {
  x += xIncrement;
  y += yIncrement;
  //setPixel (round (x), round (y));
  glBegin(GL_POINTS);
  glColor3f(r,g,b);
  glVertex2f(x,y);
  glEnd();
  }
}
//algoritmo incremental
void linea()
{
  glBegin(GL_POINTS);
  glColor3f(1,0,0);
 
  cout<<"x antiguo"<<x_a<<endl;
  cout<<"y antiguo"<<y_a<<endl;
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
      cout<<"puntos que deberia de graficar x="<< x<<"y="<<y<<endl;
    }

  glEnd();
  is_grafica=true;
  entro=true;
  glFlush();
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
  x2=x;
  y2=y;
  x1=x_a;
  y1=y_a;

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

  while(y1<=y2){
    if(d<=0){
      d=d+incE;
      y1=y1+1;
    }
    else{
      d=d+incNE;
      x1=x1-1;
      y1=y1+1;
    }
    glVertex2f(x1,y1);
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
    /*if(i==3){
      break;
    }*/
  }
  //cout<<"tamano"<<tamano<<endl;
  lineaDDA_dos(datos[0][0], datos[0][1], datos[tamano-1][0],datos[tamano-1][1]);
  //cout<<"enta aca debera apreto el boton dereshoooo"<<endl;
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       check=true;
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
      check=true;
      x = mousex;
      y = tamano_pantallay-mousey;
      //y=mousey;
      cout<<"coordenadas up x="<<x<<"y="<<y<<endl;
      r=1;//(rand()%9)/8;
      g=0;//(rand()%9)/8;
      b=0;
      
      //linea();
      lineaDDA();
      //punto_medio();
      //lineaptomedio();
      //MidPointCircle();
      /*glBegin(GL_LINES);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(50.0f, 50.0f, 50.0f);
      glEnd();*/
    }
    if(button==GLUT_RIGHT_BUTTON ){
      //graficar los poligonos
      datos.push_back(datos[0]);
      plot_polygon();
    }
    glutPostRedisplay();
}


void keyboard(int key, int x, int y) {
  glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
  glClear(GL_COLOR_BUFFER_BIT);
  if (key==GLUT_KEY_UP){
    up = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]+=desplazamiento;
    }
    plot_polygon();
  }
  if (key==GLUT_KEY_DOWN){
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][1]-=desplazamiento;
    }
    plot_polygon();
  }

  if (key==GLUT_KEY_LEFT){
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]-=desplazamiento;
    }
    plot_polygon();
    
    /*
    vector<float> d1;
    d1.push_back(50);
    d1.push_back(20);

    vector<float> d2;
    d2.push_back(90);
    d2.push_back(20);

    vector<float> d3;
    d3.push_back(70);
    d3.push_back(50);

    
    datos.push_back(d1);
    datos.push_back(d2);
    datos.push_back(d3);
    //datos.push_back(d4);
    for(int i=0;i<datos.size();i++)
    {
      cout<<"PUNTO"<<endl;
      cout<<datos[i][0]<<endl;
      cout<<datos[i][1]<<endl;
    }

    plot_polygon();*/
   }

   if (key==GLUT_KEY_RIGHT){
    down = 1;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]+=desplazamiento;
    }
    plot_polygon();

   } 

   if(key==115){//control
    cout<<"imprimiendo menos debera en el menos"<<endl;
    int tamano=datos.size();
    for(int i=0;i<tamano;i++)
    {
      datos[i][0]*= escala_me;
      datos[i][1]*= escala_me;
    }
    plot_polygon();
   }

   if(key==113){//pausa :v
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
    plot_polygon();
    for(int i=0;i<tamano;i++)
    {
      cout<<"PUNTO"<<endl;
      
    }
   }

   cout<<"esto seria ENTRA ACAAA"<<key<<endl;
    glutPostRedisplay();
}


void display()
{  
    glColor3f(r,g,b); // sets the current drawing (foreground) color to blue 
    glPointSize(4); // sets the size of points to be drawn (in pixels) 
    glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, tamano_pantallax, 0.0, tamano_pantallay);//sets the parallel(orthographic) projection of the full frame buffer 
    

    glFlush();     // flushes the frame buffer to the screen


}

int main(int argc,char** argv)
{

	glutInit(&argc,argv);
    glutInitWindowSize(tamano_pantallax,tamano_pantallay);   //sets the width and height of the window in pixels
    glutInitWindowPosition(10,10);//sets the position of the window in pixels from top left corner 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//creates a single frame buffer of RGB color capacity.
    glutCreateWindow("DDA Line Drawing");//creates the window as specified by the user as above.
    glutSpecialFunc(keyboard);
    glClearColor(1, 1, 1, 0); // sets the backgraound color to white light
    glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
  
    glutDisplayFunc(display);//links the display event with the display event handler(display)
    glutMouseFunc(mouse);//keyboard event handler
    glutMainLoop();//loops the current event
}