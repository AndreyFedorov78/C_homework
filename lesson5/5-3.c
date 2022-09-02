#include <stdio.h>

long int get_number() {
    char ch;
    long int result = 0;
    ch = getchar();
    while (ch != ' ') {
        result = result * 10 + ch - '0';
        ch = getchar();
    }
    return result;
}


int main() {
    long int result = 0;
    char ch=' ';
    result = get_number();
    while (ch!='.'){
       long int value = get_number();
       ch=getchar();
        switch (ch) {
            case '+': result+=value; break;
            case '*': result*=value; break;
            case '/': result/=value; break;
            case '-': result-=value; break;
        }
       ch=getchar();
    }
    printf("%ld\n", result);
    return 0;
};
