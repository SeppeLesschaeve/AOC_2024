//
// Created by seppeheinlesschaeve on 03/12/24.
//
#include <stdio.h>
#include <string.h>
#include <regex.h>

int part1(char input_list[6][5000]) {
    regex_t mul;
    regmatch_t match_mul;
    int error = -1;
    if (regcomp(&mul, "mul\\([0-9]+,[0-9]+\\)", REG_EXTENDED) == 0) {
        int total_1 = 0;
        for (int i = 0; i < 6; i++) {
            int offset = 0;
            while(regexec(&mul, &input_list[i][offset], 1, &match_mul, 0) == 0){
                char mul_str[50];
                strncpy(mul_str, &input_list[i][offset + match_mul.rm_so], match_mul.rm_eo - match_mul.rm_so);
                mul_str[match_mul.rm_eo - match_mul.rm_so] = '\0';
                int i1 = 0, i2 = 0;
                sscanf(mul_str, "mul(%d,%d)", &i1, &i2);
                total_1 += (i1 *i2);
                offset += match_mul.rm_eo;
            }
        }
        printf("The result for part 1 is: %d\n", total_1);
        error++;
    }
    regfree(&mul);
    return error;
}

int part2(char input_list[6][5000]) {
    regex_t mul;
    regex_t todo;
    regex_t todonot;

    regmatch_t match_mul;
    regmatch_t match_do;
    regmatch_t match_dont;
    int error = -1;
    if (regcomp(&mul, "mul\\([0-9]+,[0-9]+\\)", REG_EXTENDED) == 0 &&
        regcomp(&todo, "do\\(\\)", REG_EXTENDED) == 0 &&
        regcomp(&todonot, "don't\\(\\)", REG_EXTENDED) == 0) {
        int j = 0;
        int total_2 = 0;
        int enabled = 0;
        for (int i = 0; i < 6; i++) {
            int offset = 0;
            while (regexec(&mul, &input_list[i][offset], 1, &match_mul, 0) == 0) {
                if (regexec(&todonot, &input_list[i][offset], 1, &match_dont, 0) == 0 && match_dont.rm_so < match_mul.rm_so) {
                    enabled = 1;
                    offset += match_dont.rm_eo;
                    continue;
                }
                if (enabled != 0 && regexec(&todo, &input_list[i][offset], 1, &match_do, 0) == 0 && match_do.rm_so < match_mul.rm_so) {
                    enabled = 0;
                    offset += match_do.rm_eo;
                    continue;
                }
                if (enabled == 0) {
                    char mul_str[50];
                    strncpy(mul_str, &input_list[i][offset + match_mul.rm_so], match_mul.rm_eo - match_mul.rm_so);
                    mul_str[match_mul.rm_eo - match_mul.rm_so] = '\0';
                    int i1 = 0, i2 = 0;
                    sscanf(mul_str, "mul(%d,%d)", &i1, &i2);
                    total_2 += (i1 *i2);
                    j++;
                }
                offset += match_mul.rm_eo;
            }
        }
        // part 2
        printf("The result for part 2 is: %d\n", total_2);
        error++;
    }
    regfree(&mul);
    regfree(&todo);
    regfree(&todonot);
    return error;
}

int main(){
    char input_list[6][5000] = {0};
    FILE *file = fopen("Day03/day03.txt", "r");
    if (file != NULL) {
        for (int i = 0; fgets(input_list[i], sizeof(input_list[i]), file); i++) {
        }
        fclose(file);
    }
    if (part1(input_list) == -1 || part2(input_list) == -1) {
        return -1;
    }
    return 0;
}
