#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define max 100000

int stack_in[max], stack_out[max];
int top_in = -1, top_out = -1;
void push_in(int x) {
    stack_in[++top_in] = x;
}
void push_out(int x) {
    stack_out[++top_out] = x;
}
int pop_in() {
    return stack_in[top_in--];
}
int pop_out() {
    return stack_out[top_out--];
}
int peek_out() {
    return stack_out[top_out];
}
void transfer() {
    if (top_out == -1) {
        while (top_in != -1) {
            push_out(pop_in());
        }
    }
}
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    
   int q;
    scanf("%d", &q);

    while (q--) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &x);
            push_in(x);
        }
        else if (type == 2) {
            transfer();
            pop_out();
        }
        else if (type == 3) {
            transfer();
            printf("%d\n", peek_out());
        }
    }

    return 0;
}