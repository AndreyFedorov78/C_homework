#include <stdio.h>
#include <string.h>


int mySearch(char str1[], char str2[]){
    int len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    for (int k=0; k<len2; k++){
        if (len2-k<=len1) {
            int i;
            for (i=0; i<len2-k; i++){
                if (str2[i+k] != str1[i]) break;
            }
            if (i == len2-k) {
                return (i);
            }
        }
    }
    return 0;
}

int main() {
    char str1[1000], str2[1000];
    scanf("%s", str1);
    scanf("%s", str2);
    printf("%d %d\n", mySearch(str1, str2), mySearch(str2, str1));
    return 0;
}

