#include <stdio.h>
#include <setjmp.h>

jmp_buf env_p;
jmp_buf env_c;
jmp_buf env_p2;

int n = 0;
#define MAX_NUM  100*10000

void customer() {
    setjmp(env_c);
    //printf("i am customer n=%d\n", n);
    if (n < 3)
        longjmp(env_p, n);
    else if (n < MAX_NUM)
        longjmp(env_p2, n);
}

void productor() {
    if (n == 0) {
        setjmp(env_p);
        n++;
        if (n == 1)
            return;
    }

    setjmp(env_p2);
    n++;
    //printf("i am productor n=%d\n", n);
    if (n < MAX_NUM)
        longjmp(env_c, n);
}
int main() {
    //printf("i am main\n");

    productor();

    customer();
    return 0;
}
