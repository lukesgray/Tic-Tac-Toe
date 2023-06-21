#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND 2

// fread(&fh_data, sizeof(fh_data), 1, fh_read);

// void commands();
// bool parse_command(char *user_input);
// int enter_value(char *user_input, int player, char **game);

int main(int argc, char *argv[])
{
    // char **arr;

    // int rows = 3;
    // int columns = 3;

    // printf("You are about to play tic-tack-toe.");
    // commands();

    // // I think this got added so commenting it out
    // //   printf("\nEnter a 6 digit number:\n");
    // // Get user input with restriction of 4096
    // //  char *user_input = malloc(INPUT_SIZE_BUFFER * sizeof(char)); There was ab error here commiting

    // // player one prompt
    // printf("Player 1, it's your turn! Enter a command:\n");

    // char *user_input = malloc(COMMAND);
    // fgets(user_input, COMMAND, stdin);

    // if (parse_command(user_input))
    // {
    //     enter_value(user_input, 1, rows[3][3]);
    // }

    // // player two prompt

    int nums[10];

    int *ptr;

    ptr = nums;

    int ptrsz = sizeof(ptr);
    int arrsz = sizeof(nums);
    int arrsz2 = sizeof(&nums);

    printf("pointer size: %d\narray name size: %d\narray2 name size:%d\n", ptrsz, arrsz, arrsz2);

    return 0;
}

// bool parse_command(char *user_input)
// {
//     char columns[] = "TMB";
//     char rows[] = "LMR";
//     // int counter = 0;
//     // char *input_buffer = malloc(INPUT_SIZE_BUFFER * sizeof(char));
//     // int length = strlen(user_input);

//     if (strchr(columns, *user_input) == NULL)
//     {
//         return false;
//     }

//     if (strchr(rows, *(user_input + 1)) == NULL)
//     {
//         return false;
//     }

//     return true;
// }

// int enter_value(char *user_input, int player, char **game)
// {
//     int row;
//     int column;

//     // Assign proper Row
//     if (strchr(*user_input, "T"))
//     {
//         row = 0;
//     }
//     if (*strchr(*user_input, "M") == 0)
//     {
//         row = 1;
//     }
//     if (strchr(*user_input, "B"))
//     {
//         row = 2;
//     }

//     // Assign proper column
//     if (strchr(*user_input, "L"))
//     {
//         column = 0;
//     }
//     if (*strchr(*user_input, "M") == 1)
//     {
//         column = 1;
//     }
//     if (strchr(*user_input, "R"))
//     {
//         column = 2;
//     }

//     if (player == 1)
//     {
//         game[row][column] = "X";
//     }

//     if (player == 2)
//     {
//         game[row][column] = "O";
//     }
// }

// void commands()
// {
//     printf("Here are the commands:\n");
//     printf("TL TM TR\n");
//     printf("ML MM MR\n");
//     printf("BL BM BR\n");
// }
