#include <stdio.h>
#include <stdlib.h>

////////////////// function: print_board //////////////////

void print_board(int board[8][8]) {
int r, c, i, j, k, map[8][8] ;
printf("     0   1   2   3   4   5   6   7  \n"); 
    for (i=0; i<8; i++)
        {
        printf("   +---+---+---+---+---+---+---+---+\n");
        printf(" %d ", i);
            {
        for (j=0; j<8; j++)
            if (board[i][j]==1)
                printf("| O ");
                else if (board[i][j]==2)
                    printf("| # ");
                        else printf("|   ");
             }    
        printf("|\n");
        } 
        printf("   +---+---+---+---+---+---+---+---+\n");
    }

////////////////// function: print_game_details //////////////////

void print_game_details(int board[8][8], int current_player) {
	int c1=0, c2=0, i, j;
	char player;
	/*
		Purpose: print the game details as described in
		P.9 of the specification

		No return value.
	*/
	if (current_player==1)
		player='O';
		else player='#';
	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			if (board[i][j]==1)
				c1++;
				else if (board[i][j]==2)
						c2++;

	printf("\n");
	printf("Player O: %d            ",c1);
	printf("Player #: %d \n", c2);
	printf("Current Turn:  %c\n\n", player);
}

////////////////// function: need_pass //////////////////

int need_pass(int board[8][8], int current_player) {
	/*
		Purpose: to determine if current_player can find at least one cell
		to place a new disc

		Return value:
		0: can find at least one cell.
		1: cannot find any cell.
	*/
	int i, j;
	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			if (can_flip_opponent(board, i, j, current_player) == 1)
				return 0;
				
	return 1;
}


////////////////// function: is_end_game //////////////////

int is_end_game(int board[8][8], int current_player) {
	/*
		Purpose: to determine if the game has been ended or not

		Return value:
		0: false, i.e., the game is not ended.
		1: true,  i.e., the game is ended.
	*/
	int i, j;
	int opponent=2;
	if (current_player==2)	
		opponent=1;
	if ((need_pass(board,current_player)==1)&&(need_pass(board,opponent)==1))
		return 1;
	else return 0;
}

////////////////// function: is_wrong_input_range //////////////////

int is_wrong_input_range(int row, int col) {
	if ((row >= 0)&&(row <= 7)&&(col >= 0)&&(col <= 7 ))
		return 0;
		else return 1;
	/*
		Purpose: to determine if the input is in the wrong range

		Return value:
		0: no,  i.e., correct input.
		1: yes, i.e., wrong input.
	*/
}

////////////////// function: is_empty_cell //////////////////

int is_empty_cell(int board[8][8], int row, int col) {
	if (board[row][col]!=0)
		return 0;
		else return 1;
	/*
		Purpose: to determine if (row, col) refers to an empty cell

		Return value:
		0: no,  i.e., not empty.
		1: yes, i.e., empty.
	*/
}

////////////////// function: can_flip_opponent //////////////////

int can_flip_opponent(int board[8][8], int row, int col, int current_player) 
{
	int opponent=2;
	int dx, dy, r, c, num;
	if (current_player==2)	
		opponent=1;
	for (dx=-1; dx<2; dx++)
		for  (dy=-1; dy<2; dy++)
		{
			if (dx==0 && dy==0)	continue;
			r = row + dx;
			c = col + dy;
			num=0;
			while( !is_wrong_input_range(r,c) && board[r][c]==opponent) 
			{
				r = r + dx;
				c = c + dy;
				num++;
			}
			if (num==0)	continue;
			if (!is_wrong_input_range(r,c) && board[r][c]==current_player)
				return 1;
		}
	return 0;
}
	/*
		Purpose: to determine the new disc in (row, col)
		can flip any opponent's discs

		Return value:
		0: no,  i.e., cannot flip.
		1: yes, i.e., can flip.
	*/
	
////////////////// function: flip_opponent //////////////////

void flip_opponent(int board[8][8], int row, int col, int current_player) {
	/*
		Purpose: using a new disc in (row, col) to flip opponent's disc

		Because "board" is an array, update it in this function
		will also change the variable in the main function.

		No return value.
	*/
		int opponent=2;
	int dx, dy, r,c,num;
	if (current_player==2)	
		opponent=1;
	for (dx=-1; dx<2; dx++)
		for  (dy=-1; dy<2; dy++)
		{
			if (dx==0 && dy==0)	continue;
			r = row + dx;
			c = col + dy;
			num=0;
			while( !is_wrong_input_range(r,c) && board[r][c]==opponent) 
			{
				r = r + dx;
				c = c + dy;
				num++;
			}
			if (num==0)	continue;
			if (!is_wrong_input_range(r,c) && board[r][c]==current_player)
			{
				do{
				r = r - dx;
				c = c - dy;
				board[r][c]=current_player;
				} while(r!=row || c!=col);
			}
				
		}
}
////////////////// function: print_winner //////////////////

void print_winner(int board[8][8]) {
	int c1=0, c2=0, i, j;
	for (i=0; i<8; i++)
		for (j=0; j<8; j++)
			if (board[i][j]==1)
				c1++;
				else if (board[i][j]==2)
						c2++;
	if (c1>c2)
		printf("Winner: Player: O");
	else if (c2<c1)
		printf("Winner: Player: #");
	else if (c2==c1)
		printf("Draw");	
	/*
		Purpose:
			- print number of 'O' in the board;
			- print number of '#' in the board;
			- print who the winner is / draw grame
		*/

}

///////////////// Main /////////////////

int main(int argc, char **argv) {
	int current_player = 1;  // current_player can be 1 or 2;
	int board[8][8];           // store the current game board
	int i, j, row, col,row_k, col_k, mode, stop, all_test_pass;

	printf("Select Mode: [1. Normal Mode | 2. Debug Mode] ?\n");
	scanf("%d", &mode);
	/*

		mode == 1: normal mode
		mode == 2: debug mode

	*/

	if(mode == 1) {
		for (row=0; row<8; row++)
			for (col=0; col<8; col++)
				board[row][col]=0;
		board[3][3]= 2;
		board[4][4]= 2;
		board[4][3]= 1;
	    board[3][4]= 1;


	}
	else if(mode == 2) {
		/*
			Preset for debuging
		*/
		for (row=0; row<8; row++)
			for (col=0; col<8; col++)
				board[row][col]=0;	
		board[0][3]= 1;
	    board[0][5]= 1;
	    board[1][3]= 1;
	    board[1][4]= 1;
	    board[1][6]= 1;
	    board[2][1]= 1;
	    board[2][3]= 1;
	    board[2][5]= 1;
	    board[3][2]= 1;
	    board[3][4]= 1;
	    board[4][1]= 1;
	    board[4][2]= 1;
	    board[4][3]= 1;
	    board[4][4]= 1;
	    board[5][5]= 1;
	    board[1][1]= 2;
		board[2][2]= 2;
		board[3][3]= 2;
	}
		

	stop = 0;

	while(stop == 0) { // the big game loop begins

		print_board(board);
		print_game_details(board, current_player);

		if( is_end_game(board, current_player) == 1 ) {
			stop = 1;
		}

		if(need_pass(board, current_player) == 1) {
			printf("You have to pass this turn\n");
		}
		else {
			/*
				Inside the else body, 

				- Read input.

				- Check if "row" & "col" are in the wrong input range
				  

				- If "row" & "col" are in the correct input range,
				  check if (row, col) points to an empty cell
				 

				- If (row, col) points to an empty cell,
				  check if the new disc in (row, col) can flip any
				  opponent's discs
				


				When (row, col) passes all the above three tests,
				flip the opponent's discs
			*/
			


				do {
					printf("Row: [0-7]:\n");
					scanf("%d", &row);
					printf("col: [0-7]:\n");
					scanf("%d", &col);
					col_k=col;
					row_k=row;
						all_test_pass = 1;

						if(  is_wrong_input_range(row, col) == 1 ) {
							printf("wrong range\n");
							all_test_pass = 0;
						}
						else if( is_empty_cell(board, row, col) == 0 ) {
							printf("not empty\n");
							all_test_pass = 0;
						}
						else if( can_flip_opponent(board, row, col, current_player) == 0 ) {
							printf("cannot flip\n");
							all_test_pass = 0;
						}

						if(all_test_pass == 1) {
							flip_opponent(board, row_k, col_k, current_player);
						} 

				} while( all_test_pass == 0 );

		} // end of else body //

		/*
			Change of player
		*/
if (current_player==1)
	current_player=2;
	else current_player=1;

	}  // the big game loop ends

	print_board(board);
	print_winner(board);
	return 0;
}
