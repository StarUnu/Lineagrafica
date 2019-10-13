#ifndef PINTARPOLIGONO_H
#define PINTARPOLIGONO_H

#include <vector>
using namespace std;

class PintarPoligono{
public:
    PintarPoligono(){;}
    void draw_pixel(int x,int y);
    void detectarBorde(float x1,float y1,float x2,float y2,int *le,int *re);
    void rellenar(vector<vector<float>> );
    void display_(vector<vector<float>>);
};

void PintarPoligono::draw_pixel(int x,int y){
    glColor3f(0,0.8,0.7);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void PintarPoligono::detectarBorde(float x1,float y1,float x2,float y2,int *le,int *re){
    float temp,x,mx;
    int i;
    if(y1>y2){
        temp=x1,x1=x2,x2=temp;
        temp=y1,y1=y2,y2=temp;
    }
    if(y1==y2)
        mx=x2-x1;
    else
        mx=(x2-x1)/(y2-y1);
    x=x1;
    for(i=int(y1);i<=(int)y2;i++){
        if(x<(float)le[i]) le[i]=(int)x;
        if(x>(float)re[i]) re[i]=(int)x;
        x+=mx;
    }

}

void PintarPoligono::rellenar(vector<vector<float>> V){
    int le[2000],re[2000],i,j;
    for(i=0;i<500;i++)
        le[i]=500,re[i]=0;
    int p=0;
    for(p=0;p<V.size()-1;p++){
        detectarBorde(V[p][0],V[p][1],V[p+1][0],V[p+1][1],le,re);
    }
    detectarBorde(V[p][0],V[p][1],V[0][0],V[0][1],le,re);
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                draw_pixel(i,j);
    }
}

void PintarPoligono::display_(vector<vector<float>> vector_p){
    rellenar(vector_p);
    glFlush();
}

#endif 
