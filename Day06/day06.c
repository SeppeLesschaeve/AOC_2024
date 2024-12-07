//
// Created by seppeheinlesschaeve on 06/12/24.
//

#include "day06.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Obstacle{
  int x;
  int y;
  int amount_hit[4];
};

int will_exit(char *direction, int position[2]) {
  return (direction == "up" && position[0] == 0) ||
         (direction == "down" && position[0] == 129) ||
         (direction == "left" && position[1] == 0) ||
         (direction == "right" && position[1] == 129);
}

int will_hit(char *direction, int position[2], int obstacle[130][130]) {
  return (direction == "up" && obstacle[position[0] - 1][position[1]] == -1) ||
         (direction == "down" && obstacle[position[0] + 1][position[1]] == -1) ||
         (direction == "left" && obstacle[position[0]][position[1] - 1] == -1) ||
         (direction == "right" && obstacle[position[0]][position[1] + 1] == -1);
}

char *rotate(char *direction) {
  if (direction == "up") {
    return "right";
  } else if (direction == "down") {
    return "left";
  } else if (direction == "left") {
    return "up";
  } else if (direction == "right") {
    return "down";
  }
  return direction;
}

void advance(char *direction, int position[2]) {
    if (direction == "up") {
        position[0]--;
    } else if (direction == "down") {
        position[0]++;
    } else if (direction == "left") {
        position[1]--;
    } else if (direction == "right") {
        position[1]++;
    }
}

long int part1(char *direction, int position[2], long int path_length, int obstacle[130][130], int visited[130][130]) {
  if (will_exit(direction, position)) {
    return path_length;
  }
  if (will_hit(direction, position, obstacle)) {
    direction = rotate(direction);
    return part1(direction, position, path_length, obstacle, visited);
  }
  advance(direction, position);
  if (visited[position[0]][position[1]] == 0) {
    path_length++;
    visited[position[0]][position[1]] = 1;
  }
  return part1(direction, position, path_length, obstacle, visited);
}

void apply_hit(struct Obstacle obstacles[825], int position[2], char *direction) {
  for (int i = 0; i < 825; i++) {
    if (direction == "up" && obstacles[i].x == position[0] - 1 && obstacles[i].y == position[1]) {
      obstacles[i].amount_hit[0]++; break;
    }
    if (direction == "down" && obstacles[i].x == position[0] + 1 && obstacles[i].y == position[1]) {
      obstacles[i].amount_hit[1]++; break;
    }
    if (direction == "left" && obstacles[i].x == position[0] && obstacles[i].y == position[1] - 1) {
      obstacles[i].amount_hit[2]++; break;
    }
    if (direction == "right" && obstacles[i].x == position[0] && obstacles[i].y == position[1] + 1) {
      obstacles[i].amount_hit[3]++; break;
    }
  }
}

int hit_twice(struct Obstacle obstacles[825]) {
  for (int i = 0; i < 825; i++) {
    for (int j = 0; j < 4; j++) {
      if (obstacles[i].amount_hit[j] == 2) {
        return 1;
      }
    }
  }
  return 0;
}

int looping(char *dir, int position[2], int obstacle[130][130], struct Obstacle obstacles[825]) {
  while (1) {
    if (will_exit(dir, position)) {
      return 0;
    }
    if (will_hit(dir, position, obstacle)) {
      apply_hit(obstacles, position, dir);
      if (hit_twice(obstacles)) {
        break;
      }
      dir = rotate(dir);
    } else {
      advance(dir, position);
    }
  }
  return 1;
}

void clear(struct Obstacle obstacle[825]) {
  for (int i = 0; i < 825; i++) {
    for (int j = 0; j < 4; j++) {
      obstacle[i].amount_hit[j] = 0;
    }
  }
}

int main(void){
    FILE *f = fopen("Day06/day06.txt", "r");
    if (!f) { fputs("File not found.\n", stderr); return -1; }
    int position[2];
    int row = 0, col = 0;
    char *direction = "up";
    long int path_length = 1;
    char buf[BUFSIZ];
    int obstacle[130][130];
    int visited[130][130];
    int obstacle_length = 1;
    struct Obstacle obstacles[825];
    for (int i = 0; fgets(buf, sizeof buf, f); i++) {
        strtok(buf, "\n"); // remove any newlines
        for (int j = 0; j < 130; j++) {
          if(buf[j] == '#') {
            obstacle[i][j] = -1;
            obstacles[obstacle_length].x = i;
            obstacles[obstacle_length].y = j;
            obstacle_length++;
          } else if (buf[j] == '^') {
            row = i;
            col = j;
          }
        }
    }
    fclose(f);
    position[0] = row, position[1] = col;
    path_length = part1(direction, position, path_length, obstacle, visited);
    printf("%ld\n", path_length);
    int amount_loops = 0;
    for (int i = 0; i < 130; i++) {
      for (int j = 0; j < 130; j++) {
        if (visited[i][j] == 1 && !(row == i && col == j)) {
          obstacle[i][j] = -1;
          int ps[] = {row, col};
          obstacles[0].x = i;
          obstacles[0].y = j;
          if (looping("up", ps, obstacle, obstacles)) {
            amount_loops++;
          }
          clear(obstacles);
          obstacle[i][j] = 0;
        }
      }
    }
    printf("%d\n", amount_loops);
    return 0;
}

