#include "game_of_life.h"

int main()
{
    config cf = {.speed = 1.0, .delay = 50000, .game_finished = 0};
    input(cf.matrix, ROWS, COLS);
    start_game(cf);
    return EXIT_SUCCESS;
}

void input(int matrix[ROWS][COLS], int rows, int cols)
{
    int x;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((scanf("%d", &x)))
            {
                matrix[i][j] = x;
            }
        }
    }
}

void start_game(config cf) {
    FILE * stream = safe_reopen();
    init();
    draw_generation(cf.matrix_help, ROWS, COLS);
    while (cf.game_finished == 0)
    {
        usleep(cf.delay / cf.speed);
        check_input(&cf.speed);
        clear();
        add_state(cf.matrix, cf.matrix_help, ROWS, COLS, &cf.game_finished);
        copy_matrix(cf.matrix, cf.matrix_help);
        draw_generation(cf.matrix_help, ROWS, COLS);
        printw("\nSpeed %.1lf", cf.speed);
    }
    fclose(stream);
    endwin();
}

void draw_generation(int matrix[ROWS][COLS], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                printw("O");
            }
            else
            {
                printw(" ");
            }
        }
        if (i != m - 1)
        {
            printw("\n");
        }
    }
}

int check_cell(int matrix[ROWS][COLS], int y, int x)
{
    int sum = 0, col, row;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            col = (x + i + COLS) % COLS;
            row = (y + j + ROWS) % ROWS;
            sum += matrix[row][col];
        }
    }
    sum -= matrix[y][x];
    return sum;
}

void add_state(int matrix[ROWS][COLS], int matrix_help[ROWS][COLS], int rows, int cols, int *dead)
{
    int sum_of_neighbours, cur_state;
    int flag = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix_help[i][j] = 0;
            cur_state = matrix[i][j];
            if (cur_state == 1)
            {
                flag = 0;
            }
            sum_of_neighbours = check_cell(matrix, i, j);
            if (cur_state == 1 && (sum_of_neighbours == 2 || sum_of_neighbours == 3))
            {
                matrix_help[i][j] = 1;
            }
            else if (cur_state == 0 && sum_of_neighbours == 3)
            {
                matrix_help[i][j] = 1;
            }
            else
            {
                matrix_help[i][j] = 0;
            }
        }
    }
    *dead = flag;
}

void copy_matrix(int matrix[ROWS][COLS], int matrix_help[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            matrix[i][j] = matrix_help[i][j];
        }
    }
}

void check_input(float *speed)
{
    char ch = getch();
    if (ch == 'q' || ch == 'Q')
    {
        exit(0);
    }
    else if ((ch == 'm' || ch == 'M') && *speed < 2.9)
    {
        *speed += 0.1;
    }
    else if ((ch == 'l' || ch == 'L') && *speed > 0.5)
    {
        *speed -= 0.1;
    }
}

void init() {
    initscr();
    noecho();
    wtimeout(stdscr, 2);
}

void* safe_reopen() {
    FILE* stream = freopen("/dev/tty", "r", stdin);
    if (stream == NULL) {
        printf("Cannot open /dev/tty\n");
        exit(1);
    }
    return stream;
}
