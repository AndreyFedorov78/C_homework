#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

//  выбор набора функций
#define FOOCASE 1

#define SHOW_ITERATION 1
#define SHOW_ROOTS 1<<1

#define MAX(x) (x[0]>x[1] && x[0]>x[2]) ? 0 : (x[1]>x[2]) ? 1 : 2 
#define MIN(x) (x[0]<x[1] && x[0]<x[2]) ? 0 : (x[1]<x[2]) ? 1 : 2
// ниже по номеру средней точки будем делать вывод о располажении кривых
#define CHOOSER(x) 3-(MIN(x))-(MAX(x))


typedef float(*function)(float);
//  прототипы функций
void integral(void *f,int a,int  b,int  eps2);           // интегрирование
float root (function f,function g,float x, float eps1, unsigned int *iteration); // поиск пересечения методом ньютона
float subFunction(function f1, function f2, float x);    //  вычитание функций
float df(function f, function g, float x,float eps);     // приблизительное вычисление производной
void printHelp();  // вывод справки

// исследуемые функции
#if FOOCASE==1
float f1(float x) {return 0.6 * x + 3;}
float f2(float x) {return (x-2)*(x-2)*(x-2)-1;}
float f3(float x) {return 3/x;}
#elif  FOOCASE==2
float f1(float x) {return 0;}
float f2(float x) {return x+10;}
float f3(float x) {return 10-x;}
#else
float f1(float x) {return 0;}
float f2(float x) {return x+10;}
float f3(float x) {return 10-x;}
#endif


int main(int argc, char const *argv[]) { 

    float eps = 0.0001;
    uint8_t show = 0;


// анализ вводной строки
        for (int i =1; i< argc; i++) {
            
            if (strcmp("--help", argv[i])==0) {
                printHelp();
                return 0;  
            }
            if (strcmp("-si", argv[i])==0) {
                show |= SHOW_ITERATION;
            }
             else if (strcmp("-sr", argv[i])==0) {
                show |= SHOW_ROOTS;
            }
             
        }

// ищем три точки пересечения
    float x[3],y[3];
    unsigned int it[3];
    x[0] = root (f1,f2, 0, eps, &it[0]);
    x[1] = root (f1,f3, x[0], eps, &it[1]);
    x[2] = root (f2,f3, x[0], eps, &it[2]);
    y[0] = f1 (x[0]);
    y[1] = f1 (x[1]);
    y[2] = f3 (x[2]);
    if (show & SHOW_ROOTS)
    { 
        printf ("Точки пересечений:");
        for (int i = 0; i<3; i++){
         printf("(%.3f, %.3f)",x[i],y[i]);
         if (show & SHOW_ITERATION) {
            printf(", итераций %u; ", it[i]);
         }
        }
        printf("\n");
    }
    function foo1, foo2, foo3;
    
    switch (CHOOSER(x))
    {
    case 0:
        foo1 = f3; 
        if (MAX(x) == 1) {
            foo2 = f2;
            foo3 = f1;
         } else {
            foo3 = f1;
            foo2 = f2;
         }
        break;
    case 1:
        foo1 = f2; 
        if (MAX(x) == 2) {
            foo2 = f1;
            foo3 = f3;
         } else {
            foo3 = f3;
            foo2 = f1;
         }
        break;
    
    default:
        foo1 = f1; 
        if (MAX(x) == 0) {
            foo2 = f2;
            foo3 = f3;
         } else {
            foo3 = f3;
            foo2 = f2;
         }
        break;
    }
    
    
        return 0;
}

 void integral(void *f,int a,int  b,int  eps2){
    return;
 }

float root (function f,function g,float x, float eps1, unsigned int *iteration){
    while (df(f,g,x, eps1) == 0) x+=eps1; // если наткнулись на нулевую производную 
    *iteration = 1;
    float x1 = x - subFunction(f,g,x)/df(f,g,x, eps1); 
    float x0 = x; 
    while(fabs(x0-x1) > eps1) {
        (*iteration)++;
        while (df(f,g,x1, eps1) == 0) x1+=eps1;  // если наткнулись на нулевую производную 
        x0 = x1;
        x1 = x1  - subFunction(f,g,x1)/df(f,g,x1, eps1); }
return x1; 
}

float subFunction(function f1,function f2, float x){
    return (float)f1(x) - (float) f2(x);
}


float df(function f, function g, float x,float esp ) {
    float esp1 = x+esp/2;
    float esp2 = x-esp/2;
    
return (subFunction(f,g,(x+esp/2))-subFunction(f,g,(x-esp/2)))/esp;
}


void printHelp(){
    printf("help\n");
    return;
}