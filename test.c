#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND 30

// fread(&fh_data, sizeof(fh_data), 1, fh_read);
// void set_player_names(char *player1, char *player2);
void set_players(char **players);
void set_player_markers(char *player1_marker, char *player2_marker);
bool is_valid_marker(char *marker);
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

    // User Defined Number of Players
    int *number_of_players = malloc(sizeof(int));
    char *user_input = malloc(COMMAND);
    printf("Please Enter the Number of Players:\n");
    fgets(user_input, COMMAND - 1, stdin);
    *number_of_players = atoi(user_input);

    // allocate space for player array
    char **players = malloc(sizeof(char *) * *number_of_players);

    // Allocate Memory for "Global" Variables and assign to pointers.
    char **board = create_board();

    int player = 1;

    printf("You are about to play tic-tack-toe.\n");
    commands();

    // gameplay loop

    // Create player names
    for (int counter = 0; counter < *number_of_players; counter++)
    {
        // printf("number of players: %d\n", *number_of_players);
        // printf("counter: %d\n", counter);
        *(players + counter) = malloc(COMMAND);
    }

    // will need to allocate space for each value in player array
    // can do that as soon as you get the number of players
    printf("%d\n", *number_of_players);
    set_players(players);

    // Create Player Markers
    char *player1_marker = malloc(COMMAND);
    char *player2_marker = malloc(COMMAND);
    set_player_markers(player1_marker, player2_marker);

    play_game(&player, board, *(players + 1), *(players + 2));

    printf("\n");
    print_board(board);

    free(board);

    return 0;
}

bool is_valid_marker(char *marker)
{

    if (*marker == '\0')
    {
        printf("Marker must contain a value\n");
        return false;
    }

    if (strlen(marker) > 1)
    {
        printf("Marker is too long. It can only be one digit.\n");
        return false;
    }

    if (!isalpha(*marker))
    {
        printf("Marker must be an uppercase alphanumeric character\n");
        return false;
    }

    if (islower(*marker))
    {
        printf("Marker must be uppercase\n");
        return false;
    }
}

void set_player_markers(char *player1_marker, char *player2_marker)
{
    bool is_valid = false;

    while (!is_valid)
    {
        printf("Player 1 enter your marker:\n");
        fgets(player1_marker, COMMAND - 1, stdin);
        player1_marker[strcspn(player1_marker, "\n")] = 0;
        if (!is_valid_marker(player1_marker))
        {
            is_valid = false;
        }
        else
        {
            is_valid = true;
        }
    }

    is_valid = false;

    while (!is_valid)
    {
        printf("Player 2 enter your marker:\n");
        fgets(player2_marker, COMMAND - 1, stdin);
        player2_marker[strcspn(player2_marker, "\n")] = 0;
        if (!is_valid_marker(player2_marker))
        {
            is_valid = false;
        }
        else
        {
            is_valid = true;
        }
    }
}

void set_players(char **players)
{
    for (int counter = 0; counter < sizeof(players); counter++)
    {

        printf("size of players pointer array: %d\n", sizeof(players));
        printf("Player %d enter your name:\n", counter + 1);
        fgets(*(players + counter), COMMAND - 1, stdin);
        *(players + strcspn(*(players + counter), "\n")) = 0;
    }
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
        printf("your command is too long. The command must be 2 characters\n");
        commands();
        return false;
    }

    if (strlen(user_input) < 3)
    {
        printf("your command is too short. The command must be 2 characters\n");
        commands();
        return false;
    }

    if (strchr(rows, *user_input) == NULL || strchr(columns, *(user_input + 1)) == NULL)
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
    if (*(*(game + row) + column) == '-')
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
            if (*(*(board + i) + j) == '-')
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
            *(*(board + i) + j) = '-';
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

            char current_board = *(*(board + i) + j);
            printf("| %c |", current_board);
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
        if (*element == *(element + 1) && *element == *(element + 2) && *element != '-')
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

        if (e1 == e2 && e1 == e3 && e1 != '-')
        {
            printf("Column %d has three in a row\n", column_counter + 1);
            is_won = true;
        }
    }

    // Diagonal win

    if (**board == *(*(board + 1) + 1) && **board == *(*(board + 2) + 2) && **board != '-')
    {
        printf("Left to Right Diagonal has 3 in a row\n");
        is_won = true;
    }

    if (*(*(board + 2)) == *(*(board + 1) + 1) && *(*(board + 2)) == *(*(board) + 2) && *(*board + 2) != '-')
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
