#include <stdio.h>
#include <stdlib.h>

// эти макросы повышают "читабельность" кода и позволяют избежать использования глобальных переменных в функциях
#define POP stackPop(&myStack)
#define PUSH(value) stackPush(&myStack, value)

// описание ячейки стека
struct value {
    int value;
    struct value *p;
} *myStack = NULL;


void stackPush (struct value **stack,const int newValue); // добавляет значение в стек
int stackPop (struct value **stack ); // получает значение из стека
void stackClear(struct value **stack ); // помоги товарищ нам, убери посуду сам :)))

int main(){
    char ch;
    int number = 0;
    ch = getchar();
    while (ch!='.'){
        if (ch <= '9' && ch >='0'){ // получаем число и пихаем его в стек
            while (ch != ' ') {
                number = number * 10 + ch - '0';
                ch = getchar();
            }
            PUSH(number);

        } else {  // в противном случае предполагаем что нам попалось действие
            switch (ch) {
                case '+':
                    PUSH(POP + POP);
                    break;
                case '*':
                    PUSH(POP * POP);
                    break;
                case '/':
                    number = POP;
                    PUSH(POP / number);
                    break;
                case '-':
                    number = POP;
                    PUSH(POP - number); // PUSH(- POP + POP) давал ошибку в некоторых компиляторах
                    break;
            }
        }  // пробел после действия и любые лишние символы будут проигнорированы
        number = 0;
        ch = getchar();
    }
    printf("%d\n", POP); // выдаем результат
    stackClear(&myStack); // чистим память
    return 0;
}


void stackPush (struct value **stack,const int newValue) {
    struct value *new;
    new= malloc(sizeof (struct value));
    new->value=newValue;
    new->p = *stack;
    *stack = new;
    return;
}


int stackPop (struct value **stack ) {
    if (NULL == *stack) return 0;
    int result = (*stack)->value;
    struct value *old;
    old=*stack;
    *stack=(*stack)->p;
    free(old);
    return result;
}

void stackClear(struct value **stack ){
    while (*stack) stackPop(stack);
    return;
}
