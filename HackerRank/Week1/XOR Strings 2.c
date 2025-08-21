#include <stdio.h>
#include <string.h>

void strings_xor(char s[], char t[]) {
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i])
            putchar('0');
        else
            putchar('1');
    }
    putchar('\n');
}

int main() {
    char s[101], t[101];
    scanf("%s", s);
    scanf("%s", t);
    strings_xor(s, t);
    return 0;
}