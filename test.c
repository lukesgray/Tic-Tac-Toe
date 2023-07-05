#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND 30

// fread(&fh_data, sizeof(fh_data), 1, fh_read);
// void set_player_names(char *player1, char *player2);
void play_game(int *player, char **game, char *player1, char *player2);
void collect_user_input(int *row, int *column, char **game);
void write_value(int *player, char **game, int row, int column);
bool is_valid_command(char *user_input);
void parse_command(int *row, int *column, char *user_input);
bool is_available(int row, int column, char **game);
bool is_full(char **board);
bool is_won(char **board);
char **create_board();

// Instruction Functions
void print_board(char **board);
void commands();

int main(int argc, char *argv[])
{

    char **board = create_board();
    int player = 1;

    printf("You are about to play tic-tack-toe.\n");
    commands();

    // gameplay loop

    char *player1 = malloc(COMMAND);
    char *player2 = malloc(COMMAND);

    printf("Player 1 enter your name:\n");
    fgets(player1, COMMAND - 1, stdin);
    player1[strcspn(player1, "\n")] = 0;

    printf("Player 2 enter your name:\n");
    fgets(player2, COMMAND - 1, stdin);
    player2[strcspn(player2, "\n")] = 0;

    play_game(&player, board, player1, player2);

    printf("\n");
    print_board(board);

    return 0;
}

void play_game(int *player, char **game, char *player1, char *player2)
{
    int row;
    int column;

    print_board(game);
    printf("%s it's your turn! Enter a command:\n", *player == 1 ? player1 : player2);

    collect_user_input(&row, &column, game);

    write_value(player, game, row, column);

    if (is_won(game))
    {
        printf("%s you won! Better luck next time %s", *player == 1 ? player1 : player2, *player == 1 ? player2 : player1);
    }
    else if (is_full(game))
    {
        printf("Game Ended in a Tie");
    }
    else
    {
        *player = 1 + (*player % 2);
        play_game(player, game, player1, player2);
    }
}

void collect_user_input(int *row, int *column, char **game)
{
    bool is_valid = false;

    while (!is_valid)
    {
        char *user_input = malloc(COMMAND);
        fgets(user_input, COMMAND, stdin);

        if (!is_valid_command(user_input))
        {
            free(user_input);
            continue;
        }

        parse_command(row, column, user_input);

        free(user_input);

        is_valid = is_available(*row, *column, game);
    }
}

void write_value(int *player, char **game, int row, int column)
{
    // writes value to board based on player number
    if (*player == 1)
    {
        *(*(game + row) + column) = 'X';
    }
    else if (*player == 2)
    {
        *(*(game + row) + column) = 'O';
    }
}

bool is_valid_command(char *user_input)
{
    char rows[] = "TMB";
    char columns[] = "LMR";

    int i = strlen(user_input);

    if (strlen(user_input) > 3)
    {
        printf("your in command is too long. The command must be 2 characters\n");
        commands();
        return false;
    }

    if (strlen(user_input) < 3)
    {
        printf("your command is too short. The command must be 2 characters\n");
        commands();
        return false;
    }

    if (strchr(rows, *user_input) == NULL && strchr(columns, *(user_input + 1)) == NULL)
    {
        printf("your command is not a valid command\n");
        commands();
        return false;
    }

    return true;
}

void parse_command(int *row, int *column, char *user_input)
{

    char rows[] = "TMB";
    char columns[] = "LMR";

    for (int counter = 0; counter < 3; counter++)
    {
        if (*user_input == *(rows + counter))
        {
            *row = counter;
        }

        if (*(user_input + 1) == *(columns + counter))
        {
            *column = counter;
        }
    }
}

bool is_available(int row, int column, char **game)
{
    if (*(*(game + row) + column) == '\0')
    {

        return true;
    }
    else
    {
        printf("That spot has already been taken.\n");
        printf("Here are the remaining positions:\n");
        print_board(game);
        printf("Try again\n");
        return false;
    }
}

bool is_full(char **board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (*(*(board + i) + j) == '\0')
            {
                return false;
            }
        }
    }

    return true;
}

char **create_board()
{
    // allocate list of pointers to pointers of chars
    char **board = malloc(sizeof(char *) * 3);

    // allocate list of pointers to chars

    for (int i = 0; i < 3; i++)
    {
        *(board + i) = malloc(sizeof(char) * 3);
        // sets each value equal to NULL for checking for filled board in main gameplay loop
        for (int j = 0; j < 3; j++)
        {
            // board[i][j] = NULL;
            *(*(board + i) + j) = '\0';
        }
    }

    return board;
}

void print_board(char **board)
{
    // print board:
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (*(*(board + i) + j) == 'X' || *(*(board + i) + j) == 'O')
            {
                char final_board = *(*(board + i) + j);
                printf("| %c |", final_board);
            }
            else
            {
                // prints an "A" for "Available"
                printf("| - |");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool is_won(char **board)
{

    bool is_won = false;
    // Row win

    for (int row_counter = 0; row_counter < 3; row_counter++)
    {
        char *element = *(board + row_counter);
        if (*element == *(element + 1) && *element == *(element + 2) && *element != '\0')
        {
            printf("Row %d has three in a row\n", row_counter + 1);
            is_won = true;
        }
    }

    // Column win

    for (int column_counter = 0; column_counter < 3; column_counter++)
    {
        char e1 = *(*board + column_counter);
        char e2 = *(*(board + 1) + column_counter);
        char e3 = *(*(board + 2) + column_counter);

        if (e1 == e2 && e1 == e3 && e1 != '\0')
        {
            printf("Column %d has three in a row\n", column_counter + 1);
            is_won = true;
        }
    }

    // Diagonal win

    if (**board == *(*(board + 1) + 1) && **board == *(*(board + 2) + 2) && **board != '\0')
    {
        printf("Left to Right Diagonal has 3 in a row\n");
        is_won = true;
    }

    if (*(*(board + 2)) == *(*(board + 1) + 1) && *(*(board + 2)) == *(*(board) + 2) && *(*board + 2) != '\0')
    {
        printf("Right to Left Diagonal has 3 in a row\n");
        is_won = true;
    }

    return is_won;
}

void commands()
{
    printf("Here are the commands:\n");
    printf("TL TM TR\n");
    printf("ML MM MR\n");
    printf("BL BM BR\n");
}
