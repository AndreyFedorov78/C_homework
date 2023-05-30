#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

//  выбор набора функций
#define FOOCASE 1

// режимы вывода информации
#define SHOW_ITERATION 1
#define SHOW_ROOTS 1 << 1
#define SHOW_INTEGRALS 1 << 2


// выбор минимумов и максимумов из трех значений (возращается индекс а не значение)
#define MAX(x) (x[0] > x[1] && x[0] > x[2]) ? 0 : (x[1] > x[2]) ? 1 : 2
#define MIN(x) (x[0] < x[1] && x[0] < x[2]) ? 0 : (x[1] < x[2]) ? 1 : 2
// ниже по номеру средней точки будем делать вывод о располажении кривых
#define CHOOSER(x) 3 - (MIN(x)) - (MAX(x))

typedef float (*function)(float);
//  прототипы функций
float integral(function f, float a, float b, float eps2);                         // интегрирование
float root(function f, function g, float x, float eps1, unsigned int *iteration); // поиск пересечения методом ньютона
float subFunction(function f1, function f2, float x);                             //  вычитание функций
float df(function f, function g, float x, float eps);                             // приблизительное вычисление производной
void printHelp();                                                                 // вывод справки

// исследуемые функции
#if FOOCASE == 1
float f1(float x)
{
    return 0.6 * x + 3;
}
float f2(float x) { return (x - 2) * (x - 2) * (x - 2) - 1; }
float f3(float x) { return 3 / x; }
#elif FOOCASE == 2
float f1(float x)
{
    return 0;
}
float f2(float x) { return x + 10; }
float f3(float x) { return 10 - x; }
#else
float f1(float x)
{
    return 0;
}
float f2(float x) { return x + 100; }
float f3(float x) { return 100 - x; }
#endif

int main(int argc, char const *argv[])
{

    float eps = 0.0001; // точночть по умолчанию
    uint8_t show = 0;   // режим отображания по умолчанию

    // анализ вводной строки
    for (int i = 1; i < argc; i++)
    {

        if (strcmp("--help", argv[i]) == 0)
        {
            printHelp();
            return 0;
        }
        if (strcmp("-ri", argv[i]) == 0)
        {
            show |= SHOW_ROOTS;         // включаем отображание корней 
            show |= SHOW_ITERATION;     // включаем отображание кол-ва итераций
        }
        else if (strcmp("-r", argv[i]) == 0)
        {
            show |= SHOW_ROOTS;         // включаем отображание корней 
        }
        else if (strcmp("-i", argv[i]) == 0)
        {
            show |= SHOW_INTEGRALS;    //  включаем отображание интегралов трех функций
        }
        else if (strcmp("-eps", argv[i]) == 0)
        {
            if (++i < argc)            // меняем точность если она задана
            {
                int point = 0;
                char *tmp = &(argv[i][0]);
                eps = 0;
                while (*tmp != 0)
                {
                    if (*tmp == '.')
                        point = 1;
                    if (*tmp >= '0' && *tmp <= '9')
                    {
                        eps = eps * 10 + *tmp - '0';
                        point *= 10;
                    }
                    tmp++;
                }
                if (point)
                    eps /= point;
                if (!eps)
                    eps = 0.0001;  // защита от нулевой точности
                
               
            }
        }
    }

    // ищем три точки пересечения
    float x[3], y[3];
    unsigned int it[3];
    x[0] = root(f1, f2, 0, eps, &it[0]);
    x[1] = root(f1, f3, x[0], eps, &it[1]);
    x[2] = root(f2, f3, x[0], eps, &it[2]);
    if (show & SHOW_ROOTS)   // выводим корни и итерации
    {
        y[0] = f1(x[0]);
        y[1] = f1(x[1]);
        y[2] = f3(x[2]);
        printf("Точки пересечений:");
        for (int i = 0; i < 3; i++)
        {
            printf("(%.3f, %.3f)", x[i], y[i]);
            if (show & SHOW_ITERATION)
            {
                printf(", итераций %u; ", it[i]);
            }
        }
        printf("\n");
    }
    function foo1, foo2, foo3;

    switch (CHOOSER(x)) //  расставляем функции в заранее задуманном порядке
    {
    case 0:
        foo1 = f3;
        if (MAX(x) == 1)
        {
            foo2 = f2;
            foo3 = f1;
        }
        else
        {
            foo3 = f1;
            foo2 = f2;
        }
        break;
    case 1:
        foo1 = f2;
        if (MAX(x) == 2)
        {
            foo2 = f1;
            foo3 = f3;
        }
        else
        {
            foo3 = f3;
            foo2 = f1;
        }
        break;

    default:
        foo1 = f1;
        if (MAX(x) == 0)
        {
            foo2 = f2;
            foo3 = f3;
        }
        else
        {
            foo3 = f3;
            foo2 = f2;
        }
        break;
    }

    if (show & SHOW_INTEGRALS)  // отражаем интегралы всех функций
    {
        printf("foo1 интеграл от %.3f до %.3f = %.3f \n", x[MIN(x)], x[MAX(x)], integral(foo1, x[MIN(x)], x[MAX(x)], eps));
        printf("foo2 интеграл от %.3f до %.3f = %.3f \n", x[MIN(x)], x[CHOOSER(x)], integral(foo2, x[MIN(x)], x[CHOOSER(x)], eps));
        printf("foo3 интеграл от %.3f до %.3f = %.3f \n", x[CHOOSER(x)], x[MAX(x)], integral(foo3, x[CHOOSER(x)], x[MAX(x)], eps));
    }

    // считаем результат
    float result = integral(foo1, x[MIN(x)], x[MAX(x)], eps) - integral(foo2, x[MIN(x)], x[CHOOSER(x)], eps) - integral(foo3, x[CHOOSER(x)], x[MAX(x)], eps);
    result = (result > 0) ? result : -result;
    printf("Интеграл области с точночтью %.7f \033[01;32m%.3f\x1B[0;37;40m\n", eps, result);
    return 0;
}


// вычисление интеграла методом трапеции (функция из методички)
float integral(function f, float a, float b, float eps)
{
    float sum = 0;  
    for (float x = a + eps; x < b - eps; x += eps)
    {
        sum += 0.5 * eps * (f(x) + f(x + eps));
    }
    return sum;
}


// вычисление корней методом Ньютона
float root(function f, function g, float x, float eps1, unsigned int *iteration)
{
    while (df(f, g, x, eps1) == 0)
        x += eps1; // если наткнулись на нулевую производную
    *iteration = 1;
    float x1 = x - subFunction(f, g, x) / df(f, g, x, eps1);
    float x0 = x;
    while (fabs(x0 - x1) > eps1)
    {
        (*iteration)++;
        while (df(f, g, x1, eps1) == 0)
            x1 += eps1; // если наткнулись на нулевую производную
        x0 = x1;
        x1 = x1 - subFunction(f, g, x1) / df(f, g, x1, eps1);
    }
    return x1;
}


float subFunction(function f1, function f2, float x)
{
    return (float)f1(x) - (float)f2(x);
}

// наверное так делать нельзя но уменя работает :)))
float df(function f, function g, float x, float eps)
{
    float eps1 = x + eps / 2;
    float eps2 = x - eps / 2;
    return (subFunction(f, g, (x + eps / 2)) - subFunction(f, g, (x - eps / 2))) / eps;
}

void printHelp()
{
    printf("\n\nЭта программа вычисляет площади фигуры заданной тремя функциями.\n");
    printf("Ключи:\n");
    printf("-esp x.xxx  задает точность x.xxx например 0.0001 .1 итд.\n");
    printf("-r  отображает точки пересечения функций.\n");
    printf("-ri отображает точки пересечения функций и кол-во итераций.\n");
    printf("-i  отображает все результаты интегрирования.\n");
    printf("--help Справка.\n\n\n");
    return;
}
