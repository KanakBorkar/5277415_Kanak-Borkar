#include <stdio.h>
#include <stdlib.h>

static int cmp_asc(const void *a, const void *b) {
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}

int main(void) {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        int n;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);

        // 1) Sort ascending
        qsort(a, n, sizeof(int), cmp_asc);

        // 2) Swap middle with last
        int mid = (n - 1) / 2;
        int tmp = a[mid];
        a[mid] = a[n - 1];
        a[n - 1] = tmp;

        // 3) Reverse only the segment [mid+1 .. n-2]
        int st = mid + 1, ed = n - 2;
        while (st < ed) {
            int t2 = a[st];
            a[st] = a[ed];
            a[ed] = t2;
            st++;
            ed--;
        }

        // Print result
        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
    }
    return 0;
}