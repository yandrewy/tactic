#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define L       3
#define W       3

#define TTT     -1
#define MIND    1
#define TICTOE  2
#define HELPER  3

int board_state[L][W];
char char_arr_arr[L][W];
int move_hist[2][3][2];

int init_board(void)
{
        memset(board_state, 0, sizeof(board_state));
        memset(char_arr_arr, ' ', sizeof(char_arr_arr));
        memset(move_hist, -1, sizeof(move_hist));

        return 0;
}

int draw_board(int mode)
{
        switch (mode) {
        case 0 :
                printf("   |   |   \n   |   |   \n   |   |   \n");
                printf("---+---+---\n   |   |   \n   |   |   \n");
                printf("---+---+---\n   |   |   \n   |   |   \n   |   |   \n\n");
                return 0;
        case 1 :
                printf("   |   |   \n 1 | 2 | 3 \n   |   |   \n");
                printf("---+---+---\n   |   |   \n 4 | 5 | 6 \n   |   |   \n");
                printf("---+---+---\n   |   |   \n 7 | 8 | 9 \n   |   |   \n\n");
                return 0;
        case 2 :
                printf("   |   |   \n %c | %c | %c \n   |   |   \n", char_arr_arr[0][0], char_arr_arr[0][1], char_arr_arr[0][2]);
                printf("---+---+---\n   |   |   \n %c | %c | %c \n   |   |   \n", char_arr_arr[1][0], char_arr_arr[1][1], char_arr_arr[1][2]);
                printf("---+---+---\n   |   |   \n %c | %c | %c \n   |   |   \n\n", char_arr_arr[2][0], char_arr_arr[2][1], char_arr_arr[2][2]);
                return 0;
        default:
                return 1;
        }
        return 1;
}

int select_gamemode(void)
{
        int mode;
        printf("\n-1) Tic-Tac-Toe  1) Mind  2) Tic-Toe  3) Helper\nChoose gamemode: ");
        scanf("%d", &mode);
        return mode;
}

int select_player(void)
{
        int p;
        printf("1) X  -1) O\nWho's playing first: ");
        scanf("%d", &p);
        return p;
}

void input_move(int *x, int *y)
{
        int pinpad;
        printf("Enter your move: ");
        scanf("%d", &pinpad);

        switch (pinpad) {
        case 1 :
                *x = 0;
                *y = 0;
                break;
        case 2 :
                *x = 0;
                *y = 1;
                break;
        case 3 :
                *x = 0;
                *y = 2;
                break;
        case 4 :
                *x = 1;
                *y = 0;
                break;
        case 5 :
                *x = 1;
                *y = 1;
                break;
        case 6 :
                *x = 1;
                *y = 2;
                break;
        case 7 :
                *x = 2;
                *y = 0;
                break;
        case 8 :
                *x = 2;
                *y = 1;
                break;
        case 9 :
                *x = 2;
                *y = 2;
                break;
        default :
                ;
        }
}

int check_move(int x, int y)
{
        int move_coord[2];
        move_coord[0] = x;
        move_coord[1] = y;

        if ((board_state[move_coord[0]][move_coord[1]]) != 0) {
                return 1;
        }
        return 0;
}

int tabulate_move(int x, int y, int player)
{
        board_state[x][y] = player;

        if (player == 1) {
                char_arr_arr[x][y] = 'X';
        }
        if (player == -1) {
                char_arr_arr[x][y] = 'O';
        }

        if (player == -1) {
                player = 0;
        }

        move_hist[player][2][0] = move_hist[player][1][0];
        move_hist[player][1][0] = move_hist[player][0][0];
        move_hist[player][2][1] = move_hist[player][1][1];
        move_hist[player][1][1] = move_hist[player][0][1];

        move_hist[player][0][0] = x;
        move_hist[player][0][1] = y;

/*
        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 2; j++) {
                        printf("%d", move_hist[player][i][j]);
                }
        }
*/

//       printf("%d", move_hist[player][2][0]);
//        printf("%d", move_hist[player][2][1]);
        return 0;
}

int check_win()
{
        if (board_state[0][0] == 1 && board_state[0][1] == 1 && board_state[0][2] == 1) {
                return 1;
        }
        if (board_state[1][0] == 1 && board_state[1][1] == 1 && board_state[1][2] == 1) {
                return 1;
        }
        if (board_state[2][0] == 1 && board_state[2][1] == 1 && board_state[2][2] == 1) {
                return 1;
        }
        if (board_state[0][0] == 1 && board_state[1][0] == 1 && board_state[2][0] == 1) {
                return 1;
        }
        if (board_state[0][1] == 1 && board_state[1][1] == 1 && board_state[2][1] == 1) {
                return 1;
        }
        if (board_state[0][2] == 1 && board_state[1][2] == 1 && board_state[2][2] == 1) {
                return 1;
        }
        if (board_state[0][0] == 1 && board_state[1][1] == 1 && board_state[2][2] == 1) {
                return 1;
        }
        if (board_state[2][0] == 1 && board_state[1][1] == 1 && board_state[0][2] == 1) {
                return 1;
        }
   
        if (board_state[0][0] == -1 && board_state[0][1] == -1 && board_state[0][2] == -1) {
                return -1;
        }
        if (board_state[1][0] == -1 && board_state[1][1] == -1 && board_state[1][2] == -1) {
                return -1;
        }
        if (board_state[2][0] == -1 && board_state[2][1] == -1 && board_state[2][2] == -1) {
                return -1;
        }
        if (board_state[0][0] == -1 && board_state[1][0] == -1 && board_state[2][0] == -1) {
                return -1;
        }
        if (board_state[0][1] == -1 && board_state[1][1] == -1 && board_state[2][1] == -1) {
                return -1;
        }
        if (board_state[0][2] == -1 && board_state[1][2] == -1 && board_state[2][2] == -1) {
                return -1;
        }
        if (board_state[0][0] == -1 && board_state[1][1] == -1 && board_state[2][2] == -1) {
                return -1;
        }
        if (board_state[2][0] == -1 && board_state[1][1] == -1 && board_state[0][2] == -1) {
                return -1;
        }

        for (int i = 0; i < L; i++) {
                for (int j = 0; j < W; j++) {
                        if (board_state[i][j] == 0) {
                                return 0;
                        }
                
                }
        }
        return 420;
}

int remove_move(int player)
{
        if (player == -1) {
                player = 0;
        }

        int x = move_hist[player][2][0];
        int y = move_hist[player][2][1];

        board_state[x][y] = 0;
        char_arr_arr[x][y] = ' ';
        return 0;
}

int helper(void)
{
        FILE *fp;

        fp = fopen(".wire", "w");
        for (int i = 0; i < L; i++) {
                for (int j = 0; j < W; j++) {
                        int move = board_state[i][j];
                        fprintf(fp, "%d ", move);
                }
        }
        fclose(fp);

        system("python3 ./helper.py");

        return 0;
}

int main(void)
{
        fprintf(stdout, "\nmain function POST...\n");
        sleep(2);
        printf("PASSED\n\n");

        if (init_board() != 0) {
                fprintf(stderr, "SCRAMBLE GOBLIN FOUND");
                exit(1);
        }
        
        draw_board(0);

        int turns = 0;
        int current_player = -2;
        int move_x = -1;
        int move_y = -1;
        int gamemode = 420;
        int winner = -123;

        printf("Welcome to Tac-Tic!\n");
        sleep(3);

        gamemode = select_gamemode();
        current_player = select_player();

        system("clear");
        draw_board(1);

        while(turns < 100) {
                do {
                        input_move(&move_x, &move_y);
                } while (check_move(move_x, move_y) != 0);

                tabulate_move(move_x, move_y, current_player);
                system("clear");
                
                if (check_win() != 0) {
                        winner = check_win();
                        break;
                }

                if (gamemode == TICTOE && turns > 3) {
                        remove_move(current_player);
                }

                if (gamemode == HELPER) {
                        helper();
                }

                turns++;

                if (gamemode != MIND) {
                        draw_board(2);
                }

                if (current_player == 1) {
                        current_player = -1;
                        continue;
                }
                if (current_player == -1) {
                        current_player = 1;
                        continue;
                }
        }

        system("clear");
        draw_board(2);
        printf("%d is winner!", winner);

        return 0;
}