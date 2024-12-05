//
// Created by seppeheinlesschaeve on 05/12/24.
//

#include "day05.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rule[100][100];

static int compare(const void *p, const void *q){
    return rule[*(const int *)p][*(const int *)q];
}

int main(void){
    long int page[200][23];
    long int pages[200];
    FILE *f = fopen("Day05/day05.txt", "r");
    if (!f) { fputs("File not found.\n", stderr); return -1; }
    char buf[BUFSIZ];
    for (int i = 0; fgets(buf, sizeof buf, f); ) {
        if (buf[0] == '\n')
            continue;
        if (buf[2] == '|') {
            strtok(buf, "\n"); // remove any newlines
            char *pch = strtok(buf, "|");
            long int rule_values[2];
            int n = 0;
            for (; pch != NULL; n++) {
                char *ptr;
                long int value = strtol(pch, &ptr, 10);
                rule_values[n] = value;
                pch = strtok(NULL, ",");
            }
            rule[rule_values[0]][rule_values[1]] = -1;
            rule[rule_values[1]][rule_values[0]] = 1;
        } else {
            strtok(buf, "\n"); // remove any newlines
            char *pch = strtok(buf, ",");
            int n = 0;
            for (; pch != NULL; n++) {
                char *ptr;
                long int value = strtol(pch, &ptr, 10);
                page[i][n] = value;
                pch = strtok(NULL, ",");
            }
            pages[i++] = n;
        }
    }
    fclose(f);
    long int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 200; i++) {
        int ordered = 1;
        for (int j = 1; j < pages[i]; j++) {
            for (int k = 0; k < j; k++) {
                if (rule[page[i][j]][page[i][k]] == -1) {
                    ordered = 0;
                    qsort(page[i], pages[i], sizeof **page, compare);
                    break;
                }
            }
            if (!ordered) {
                break;
            }
        }
        if (ordered) {
            sum1 += page[i][(pages[i]-1)/2];
        } else {
            sum2 += page[i][(pages[i]-1)/2];
        }
    }
    printf("%ld\n%ld\n", sum1, sum2);
    return 0;
}
