#include <stdio.h>

int atoi(const char *s) {
    int sign = 0, i = 0;
    if (*s == '-') {
        sign = 1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    for (; *s != '\0'; s++) {
        if (*s < '0' || *s > '9') {
            continue;
        }

        i *= 10;
        i += (int)(*s - '0');
    }

    return sign ? -i : i;
}

int main(int argc, char *argv[]) {
    char s[128];
    while (scanf("%s", s) != EOF) {
        printf("%d\n", atoi(s));
    }

    return 0;
}
