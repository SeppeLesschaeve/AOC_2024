//
// Created by seppeheinlesschaeve on 04/12/24.
//
#include "day04.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(char lines[140][140]) {
    int sum = 0;
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            if (lines[i][j] == 'X' && i <= 136 && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S') {
                sum ++;
            }
            if (lines[i][j] == 'S' && i <= 136 && lines[i + 1][j] == 'A' && lines[i + 2][j] == 'M' && lines[i + 3][j] == 'X') {
                sum ++;
            }
            if (lines[i][j] == 'X' && j <= 136 && lines[i][j + 1] == 'M' && lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S') {
                sum ++;
            }
            if (lines[i][j] == 'S' && j <= 136 && lines[i][j + 1] == 'A' && lines[i][j + 2] == 'M' && lines[i][j + 3] == 'X') {
                sum ++;
            }
            if (lines[i][j] == 'X' && i <= 136 && j <= 136 && lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S') {
                sum ++;
            }
            if (lines[i][j] == 'S' && i <= 136 && j <= 136 && lines[i + 1][j + 1] == 'A' && lines[i + 2][j + 2] == 'M' && lines[i + 3][j + 3] == 'X') {
                sum ++;
            }
            if (lines[i][j] == 'X' && i >= 3 && j <= 136 && lines[i - 1][j + 1] == 'M' && lines[i - 2][j + 2] == 'A' && lines[i - 3][j + 3] == 'S') {
                sum ++;
            }
            if (lines[i][j] == 'S' && i >= 3 && j <= 136 && lines[i - 1][j + 1] == 'A' && lines[i - 2][j + 2] == 'M' && lines[i - 3][j + 3] == 'X') {
                sum ++;
            }
        }
    }
    return sum;
}

int part2(char lines[140][140]) {
    int sum = 0;
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            if (lines[i][j] == 'M' && i <= 137 && j <= 137 && lines[i + 1][j + 1] == 'A' && lines[i + 2][j + 2] == 'S' &&
                ((lines[i][j + 2] == 'M' && lines[i + 2][j] == 'S') || (lines[i + 2][j] == 'M' && lines[i][j + 2] == 'S'))) {
                sum ++;
            }
            if (lines[i][j] == 'S' && i <= 137 && j <= 137 && lines[i + 1][j + 1] == 'A' && lines[i + 2][j + 2] == 'M' &&
                ((lines[i][j + 2] == 'M' && lines[i + 2][j] == 'S') || (lines[i + 2][j] == 'M' && lines[i][j + 2] == 'S'))){
                sum ++;
            }
        }
    }
    return sum;
}

int main() {
    FILE *f = fopen("Day04/day04.txt", "r");
    if (!f) {
        printf("Could not open file\n");
        return 1;
    }
    char line[10000];
    char lines[140][140];
    int count = 0;
    for(int i = 0; fgets(line, sizeof(line), f); i++) {
        line[strlen(line)-1] = '\0';
        strncpy(lines[i], line, 140);
    }
    printf("Part 1: %d\n", part1(lines));
    printf("Part 2: %d\n", part2(lines));
    fclose(f);
}