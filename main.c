#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int matrix[8][8];
int matrix_of_player[8][8];
int running = 1;
int player_turn = 0;


void init_board()
{
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            {
                if(i != 1)
                {
                    if(j == 0)
                        matrix[i][j] = 't';
                    if(j == 1)
                        matrix[i][j] = 'c';
                    if(j == 2)
                        matrix[i][j] = 'n';
                    if(j == 3)
                        matrix[i][j] = 'k';
                    if(j == 4)
                        matrix[i][j] = 'q';
                    if(j == 5)
                        matrix[i][j] = 'n';
                    if(j == 6)
                        matrix[i][j] = 'c';
                    if(j == 7)
                        matrix[i][j] = 't';
                }
                else
                    matrix[i][j] = 'p';
            }
    //printf("%c %c %c %c\n", matrix[0][2], matrix[0][6], matrix[1][2], matrix[1][7]);
    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j ++)
            matrix[i][j] = ' ';

    //printf("%c %c\n", matrix[2][6], matrix[5][5]);

    for(int i = 6; i < 8; i++)
        for(int j = 0; j < 8; j++)
            {
                if(i != 6)
                {
                    if(j == 0)
                        matrix[i][j] = 'T';
                    if(j == 1)
                        matrix[i][j] = 'C';
                    if(j == 2)
                        matrix[i][j] = 'N';
                    if(j == 3)
                        matrix[i][j] = 'K';
                    if(j == 4)
                        matrix[i][j] = 'Q';
                    if(j == 5)
                        matrix[i][j] = 'N';
                    if(j == 6)
                        matrix[i][j] = 'C';
                    if(j == 7)
                        matrix[i][j] = 'T';
                }
                else
                    matrix[i][j] = 'P';


            }
    //printf("%c %c %c %c\n", matrix[6][2], matrix[6][7], matrix[7][2], matrix[7][6]);

}

void print_board()
{
    printf("\n");
    for(int i=0; i<8; i++)
        printf("  %d   ",i);
    printf("\n");
    printf("================================================");
    //printf("------------------------------------------------");
    for(int i=0; i < 8; i++)
    {
        printf("\n");
        for(int j = 0; j<8; j++)
        {
            printf("  %c  |", matrix[i][j]);

        }
    printf(" %d\n",i);
    if(i != 7)
        printf("-----|-----|-----|-----|-----|-----|-----|-----|---");

    }
    //printf("------------------------------------------------");
    printf("================================================\n");
  //printf("%d", c);
}


int check_player_turn(int i, int j)
{
    if(player_turn%2 == 0 && islower(matrix[i][j]))
        return 1;

    if(player_turn%2 != 0 && isupper(matrix[i][j]))
        return 2;

    return -1;
}

int check_bounds(int i, int j)
{
    if(i < 0 || i > 7 || j < 0 || j > 7)
        return -1;
    return 0;
}


int extra_checking(int move, int i, int j, int k, int l)
{
    ///check the pawns
    if(move == 1 || move == 2)
    {
        if(j == l && matrix[k][l] == ' ') return 1;
        if(j != l && matrix[k][l] != ' ') return 2;

        return -1;
    }

    ///check TURA
    if(move == 11 || move == 51)
    {
        for(int x=i+1; x<k; x++)
            if(matrix[x][j] != ' ') return -1;
        for(int x=i-1; x>k; x--)
            if(matrix[x][j] != ' ') return -1;

        for(int x=j+1; x<l; x++)
            if(matrix[i][x] != ' ') return -1;
        for(int x=j-1; x>l; x--)
            if(matrix[i][x] != ' ') return -1;

        //return 11;
    }

    ///check NEBUN
    if(move == 31 || move == 51)
    {
        for(int x=i+1; x<k; x++)
            for(int y=j+1; y<l; y++)
                if(matrix[x][y] != ' ') return -1;

        for(int x=i-1; x>k; x--)
            for(int y=j-1; y>l; y--)
                if(matrix[x][y] != ' ') return -1;

        for(int x=i-1; x>k; x--)
            for(int y=j+1; y<l; y++)
                if(matrix[x][y] != ' ') return -1;

        for(int x=i+1; x<k; x++)
            for(int y=j-1; y>l; y--)
                if(matrix[x][y] != ' ') return -1;

        //return 31;
    }

    ///never gets here
    printf("rada\n\n\n");
    return 0;
}


int correct_move(int i, int j, int k, int l)
{
    ///check the pawns
    if(matrix[i][j] == 'p' && (j == l && (k == i+1 || (k == i+2 && i == 1))) || (k == i+1 && abs(j-l) == 1)) return extra_checking(1, i, j, k, l);
    if(matrix[i][j] == 'P' && (j == l && (k == i-1 || (k == i-2 && i == 6))) || (k == i+1 && abs(j-l) == 1)) return extra_checking(2, i, j, k, l);

    ///check TURA
    if((matrix[i][j] == 't' || matrix[i][j] == 'T') && ((i == k && j != l) || (i != k && j == l))) return extra_checking(11, i, j, k, l);

    ///check CAL
    if((matrix[i][j] == 'c' || matrix[i][j] == 'C') && ((abs(i-k)==2 && abs(j-l)==1) || (abs(i-k)==1 && abs(j-l)==2))) return 21;

    ///check NEBUN
    if((matrix[i][j] == 'n' || matrix[i][j] == 'N') && abs(i-k) == abs(j-l) && (i != k || j != l)) return extra_checking(31, i, j, k, l);

    ///check king
    if((matrix[i][j] == 'k' || matrix[i][j] == 'K') && abs(i-k) <= 1 && abs(j-l) <= 1 && (i != k || j != l)) return 41;

    ///check queen
    if((matrix[i][j] == 'q' || matrix[i][j] == 'Q') && (((i == k && j != l) || (i != k && j == l)) || (abs(i-k) == abs(j-l) && (i != k || j != l)))) return extra_checking(51, i, j, k, l);

    return -1;
}


int delete_own_pawns(int i, int j, int k, int l)
{
    if(isupper(matrix[i][j]) && isupper(matrix[k][l])) return -1;
    if(islower(matrix[i][j]) && islower(matrix[k][l])) return -1;

    return 0;
}


void get_player_move()
{
    int i, j, k, l;
    int is_correct = -1;

    while(is_correct == -1)
    {
        printf("Enter the coordinates of the pawn you wish to move:");

        scanf("%d %d",&i, &j);

        ///check if the input is on the chess table
        is_correct = check_bounds(i,j);
        if(is_correct == -1)
        {
            printf("ERROR, please select a valid zone on the chess table.\n");
            continue;
        }

        ///check if the correct player piece is selected
        is_correct = check_player_turn(i, j);
        if(is_correct == -1)
        {
            printf("ERROR, please select ");
            if(player_turn%2==0)printf(" WHITE color.\n");
            else printf(" BLACK color.\n");
            continue;
        }

        printf("Enter the coordinates of the place to put the pawn in:");
        scanf("%d %d",&k, &l);

        ///check if the input is on the chess table
        is_correct = check_bounds(k,l);
        if(is_correct == -1)
        {
            printf("ERROR, please select a valid zone on the chess table.\n");
            continue;
        }

        ///check if you want to delete your own pawns
        is_correct = delete_own_pawns(i, j, k, l);
        if(is_correct == -1)
        {
            printf("ERROR, you can't delete your own pawns.\n");
            continue;
        }

        ///check if the move is a valid one
        is_correct = correct_move(i, j, k, l);
        printf("\n%d\n", is_correct);
        if(is_correct == -1)
        {
            printf("ERROR, invalid move. Please select another one.\n");
            continue;
        }

        ///modify the new movement
        matrix[k][l] = matrix[i][j];
        matrix[i][j] = ' ';
    }
}

int check_if_ended()
{
    int b_king = 0, w_king = 0;

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(matrix[i][j] == 'k') b_king = 1;
            else if(matrix[i][j] == 'K')w_king = 1;
        }
    if(b_king == 0)
    {
        printf("Black is victorious.\n");
        return 0;
    }
    if(w_king == 0)
    {
        printf("White is victorious.\n");
        return 0;
    }
    return 1;
}

int main()
{
    printf("\nThis is a game of chess / player vs player\n");
    printf("-> Capital letters pawns are black, lowercase letters pawns are white\n");
    init_board();
    print_board();
    while(running)
    {
        get_player_move();
        print_board();

        //ending logic
        if(!check_if_ended()) running = 0;

        player_turn++;
    }

    return 0;
}
