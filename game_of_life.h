#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 80
#define FNAME "dev/tty"
#define MODE "r"

typedef struct config {
    float speed;
    int delay;
    int game_finished;
    int matrix[ROWS][COLS];
    int matrix_help[ROWS][COLS];
} config;

void draw_generation(int matrix[ROWS][COLS], int m, int n);
int check_cell(int matrix[ROWS][COLS], int y, int x);
void add_state(int matrix[ROWS][COLS], int matrix_help[ROWS][COLS], int rows, int cols, int* sum);
void copy_matrix(int matrix[ROWS][COLS], int matrix_help[ROWS][COLS]);
void input(int[ROWS][COLS], int rows, int cols);
void check_input(float * speed);
void init();
void start_game(config cf);
void* safe_reopen();
void game_cycle(config * ncf);

#endif