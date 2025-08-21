#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_leap(int y) {
    return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}

static int days_in_month(int m, int y) {
    static const int d[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) return is_leap(y) ? 29 : 28;
    if (m >= 1 && m <= 12) return d[m - 1];
    return 0;
}

static void next_date(int *d, int *m, int *y) {
    (*d)++;
    if (*d > days_in_month(*m, *y)) {
        *d = 1;
        (*m)++;
        if (*m > 12) {
            *m = 1;
            (*y)++;
        }
    }
}

static long long concat_val(int d, int m, int y) {
    return (long long)d * 1000000LL + (long long)m * 10000LL + (long long)y;
}

/* Extracts next date from buffer by reading 8 digits (ignores separators) */
static int find_next_date(const char *buf, int len, int *pos, int *dd, int *mm, int *yy) {
    for (int i = *pos; i < len; ++i) {
        if (isdigit((unsigned char)buf[i])) {
            int digits[8];
            int di = 0;
            int j;
            for (j = i; j < len && di < 8; ++j) {
                if (isdigit((unsigned char)buf[j])) {
                    digits[di++] = buf[j] - '0';
                }
            }
            if (di == 8) {
                *dd = digits[0]*10 + digits[1];
                *mm = digits[2]*10 + digits[3];
                *yy = digits[4]*1000 + digits[5]*100 + digits[6]*10 + digits[7];
                *pos = j;
                return 1;
            }
        }
    }
    return 0;
}

static int cmp_date(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 != y2) return (y1 < y2) ? -1 : 1;
    if (m1 != m2) return (m1 < m2) ? -1 : 1;
    if (d1 != d2) return (d1 < d2) ? -1 : 1;
    return 0;
}

int main(void) {
    char buf[16384];
    int idx = 0;
    int c;
    while ((c = getchar()) != EOF && idx < (int)sizeof(buf) - 1) {
        buf[idx++] = (char)c;
    }
    buf[idx] = '\0';

    if (idx == 0) return 0;

    int pos = 0;
    int d1, m1, y1, d2, m2, y2;
    if (!find_next_date(buf, idx, &pos, &d1, &m1, &y1)) return 0;
    if (!find_next_date(buf, idx, &pos, &d2, &m2, &y2)) return 0;

    if (cmp_date(d1, m1, y1, d2, m2, y2) > 0) {
        int td=d1, tm=m1, ty=y1;
        d1 = d2; m1 = m2; y1 = y2;
        d2 = td; m2 = tm; y2 = ty;
    }

    long long ans = 0;
    while (1) {
        long long num = concat_val(d1, m1, y1);
        if (num % 4 == 0 || num % 7 == 0) ans++;

        if (d1 == d2 && m1 == m2 && y1 == y2) break;
        next_date(&d1, &m1, &y1);
    }

    printf("%lld\n", ans);
    return 0;
}