//
// Created by seppeheinlesschaeve on 01/12/24.
//

#include "day01.h"
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

long int part1(long int left[], long int right[], long int n) {
  long int sum = 0;
  for(int i = 0; i < n; i++) {
    if (left[i] > right[i]) {
      sum += left[i] - right[i];
    } else {
      sum += right[i] - left[i];
    }
  }
  return sum;
}

long int part2(long int left[], long int right[], long int n) {
  long int score = 0;
  for (int i = 0; i < n; i++) {
    long int count_left = 0;
    for (int j = 0; j < n; j++) {
      if (left[i] == right[j]) {
        count_left++;
      }
    }
    score += left[i] * count_left;
  }
  return score;
}

int main() {
  FILE *f = fopen("Day01/day01.txt", "r");
  if (!f) {
    printf("Could not open file\n");
    return 1;
  }
  char line[10000];
  long int left[1000];
  long int right[1000];
  int count = 0;
  while (fgets(line, sizeof(line), f)) {
    char without[10000] = "";
    remove_spaces(line, without);
    int countline = 0;
    char *token = strtok(without, " ");
    char *endptr;
    while(token) {
      long int value = strtol(token, &endptr, 10);
      if (countline == 0) {
        left[count] = value;
      } else {
        right[count] = value;
      }
      countline++;
      token = strtok(NULL, " ");
    }
    count++;
  }
  int n = sizeof(left) / sizeof(left[0]);
  qsort(left, n, sizeof(long int), compare);
  qsort(right, n, sizeof(long int), compare);
  printf("%ld\n", part1(left, right, n));
  printf("%ld\n", part2(left, right, n));
  fclose(f);
}

