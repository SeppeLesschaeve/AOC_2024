//
// Created by seppeheinlesschaeve on 02/12/24.
//

#include "day02.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int compare(const void* a, const void* b) {
    return (*(long int*)a - *(long int*)b);
}

void remove_spaces(char *s, char *without) {
    strtok(s, "\n"); // remove any newlines
    char *pch = strtok(s, " ");
    while(pch != NULL) {
        strcat(without, pch);
        strcat(without, " \0");
        pch = strtok(NULL, " ");
    }
    without[strlen(without)-1] = '\0'; // remove extra whitespace at the end
}

int is_safe(long int cols, long int report[]) {
    int ascending = 1;
    int descending = 1;
    for(int i = 1; i < cols - 1; i++) {
        if(report[i] == 0) {
            break;
        }
        ascending = ascending == 1 && (report[i] > report[i - 1] && report[i] - report[i - 1] <= 3);
        descending = descending == 1 && (report[i] < report[i - 1] && report[i - 1] - report[i] <= 3);
    }
    return ascending == 1 || descending == 1;
}

long int part1(long int rows, long int cols, long int report[rows][cols]) {
    long int safes = 0;
    for(int i = 0; i < rows; i++) {
        if(is_safe(cols, report[i])) {
            safes++;
        }
    }
    return safes;
}

long int part2(long int rows, long int cols, long int report[rows][cols]) {
    long int safes = 0;
    for(int i = 0; i < rows; i++) {
        if(is_safe(cols, report[i])) {
            safes++;
        } else {
            for(int j = 0; j < cols; j++) {
                long int skip_one[cols - 1] = {};
                for(int k = 0; k < cols - 1; k++) {
                    if (k < j) {
                        skip_one[k] = report[i][k];
                    } else {
                        skip_one[k] = report[i][k + 1];
                    }
                }
                if (is_safe(cols - 1, skip_one)) {
                    safes++;
                    break;
                }
            }
        }
    }
    return safes;
}

int main() {
    FILE *f = fopen("Day02/day02.txt", "r");
    if (!f) {
        printf("Could not open file\n");
        return 1;
    }
    char line[10000];
    long int reports[1000][100];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        char without[10000] = "";
        remove_spaces(line, without);
        int countline = 0;
        char *token = strtok(without, " ");
        char *endptr;
        while(token) {
            long int value = strtol(token, &endptr, 10);
            reports[count][countline] = value;
            countline++;
            token = strtok(NULL, " ");
        }
        count++;
    }
    printf("%ld\n", part1(1000, 100, reports));
    printf("%ld\n", part2(1000, 100, reports));
    fclose(f);
}
