/* File: apex_code.cpp
 * Project: Apex Lab 8 - Arrays and Vectors Lab
 * Class: CISC 192 - C++
 * Professor: Alex Chow
 * Written by: Joshua Lopez
 * Description: This code defines 6 functions:
 *
 *-void ShowBoard(int board[][COLS]):
 * Takes a multi-dimenstional array as an argument and prints out the rows and columns in the console.
 *
 *-bool PlacePiece(int col, int player, int board[][COLS]):
 * Takes a specific column, checks if the column is within range of the board, checks if there is space
 * avaiable in the column, and if so, it places the piece in the last available row in that specific column
 *
 *-int LongestRunInRow(int player, int length, int row[]):
 * Takes 1D array, checks the longest consecutive row based off the player, and returns the longest
 * consecutive run.
 *
 *-int LongestRunInCol(int player, int colNumber, int clength, int rlength, int board[][COLS]):
 * Takes a board, a column number, and it creates a 1D array of a column with row elements, then it passes
 * this to LongestRunInRow() and returns the longest run in that 1D array based off the player.
 *
 *-void PlayerTurn(int player, int board[][COLS]):
 * Prompts which player is next, prompts them to select a column, and will use PlacePiece() to check if
 * a valid placement was made.
 *
 *-bool GameWon(int player, int board[][COLS]):
 * Checks the entire board to see if the given player has won. A win is defined as having a run of
 * NUM_TO_WIN pieces in any row or column.
 * */
#include <iostream>
#include "apex_code.h"

using namespace std;

// Prints the current board.
void ShowBoard(int board[][COLS])
{
	// Builds the top of the board
  cout << endl;
  for(int h = 0; h < COLS; ++h)
  {
	  // Prints the columns from 0-9
    cout << h << " ";
  }
  // Creates a separator
  cout << endl;
  cout << string(COLS*2-1, '_') << endl;
  // Builds the main board
  cout << endl;
  // Outer loop iterates through the rows
  for(int r = 0; r < ROWS; ++r)
  {
	  // Inner loop iterates through the columns
    for(int c = 0; c < COLS; ++c)
    {
    	// Prints the data to their respective cell
      std::cout << board[r][c] << " ";
    }
    std::cout << std::endl;
  }
}

// This function tries to place a piece for a player in a specific column of their choosing.
// It returns true if successful, and false otherwise.
bool PlacePiece(int col, int player, int board[][COLS]) {
	// Check if the selected column is in range
	if (!(0 <= col && col < COLS)) {
		cout << "Please select a column between [0," << COLS-1 << "]" << endl;
		return false;
	}
	// If we're here, then we're within range of the board and need to see if the column has space
	// Variable below holds how much space is in that column. None player is 0 and represents empty space.
	int columnSpace = LongestRunInCol(NONE, col, ROWS, COLS, board);
	// Check if column is full
	if (columnSpace == 0) {
		// Output that column is full and return false (fail fast)
		cout << "Column is full!" << endl;
		return false;
	}

	// Variable row tells us in which row we need to place the player's chip/checker. This is calculated by
	// getting the last row space available in a columns and subtracted by 1 because of arrays start at 0.
	int row = columnSpace - 1;
	// This finds the exact location in the board to store the player's play
	board[row][col] = player;

	return true;
}

// This function finds the longest consecutive run of a certain player in a 1D array.
int LongestRunInRow(int player, int length, int row[]) {
	// These variables are going to hold my current row count and if the code finds one that is longer,
	// it will assign it to maxRowCount.
	int currRowCount = 0;
	int maxRowCount = 0;

	// For loop iterates through the row array passed in the function parameter and it will count
	// how many times it sees the player's number in that row.
	for(int r = 0; r < length; ++r) {
		// Here we check if the element in the index is equal to the player's number
		if (row[r] == player) {
			// Performs the counting
			++currRowCount;
		}
		// In here, it means there was a break and will check if there's a new max
		else {
			// if the current count is greater than the previous max,
			// it assigns maxRowCount with the new max.
			if (currRowCount > maxRowCount) {
				maxRowCount = currRowCount;
			}
			// Resets currRowCount for the next consecutive run
			currRowCount = 0;
		}

	}

	// Does a final max check outside of the for loop
	if (currRowCount > maxRowCount) {
		maxRowCount = currRowCount;
	}

	// Returns the longest row count
	return maxRowCount;
}

// This function finds the longest consecutive run of a player in a specific column of the 2D board.
// It reuses the logic from LongestRunInRow().
int LongestRunInCol(int player, int colNumber, int clength, int rlength, int board[][COLS]) {
	// Created a column array and initialized it with the number of elements in a row because rows make up
	// a column contain row elements.
	int col[rlength];

	// In this for loop, we iterate through the rows in board using a specific, passed in column number, and
	// assign the rows to our local col array to hold that column's row elements.
	for(int r = 0; r < rlength; ++r)
	{
		// This is the assignment operation to take the rows of a specific column and assign to our array.
		col[r] = board[r][colNumber];
	}

	// We then pass in the player, rlength, and col to LongestRunInRow to return the longest run in column
	// as it uses the same logic to find our longest run. We essentially turned the column into a 1D array,
	// that our LongestRunInRow can use just the same as a row.
	return LongestRunInRow(player, rlength, col);
}

// Handles the player turns
void PlayerTurn(int player, int board[][COLS])
{
	// Prompts the current player
  cout << "Player " << player << "'s turn." << endl;
  int col;
  // Prompts the player for a column
  do
  {
    cout << "Select a column: " << endl;
    cin >> col;

    // Checks if the column chosen is valid and if there is space, if true, it exits the function.
  }while(false == PlacePiece(col, player, board));
}

// Checks the board for a specific player to see if they won the game
bool GameWon(int player, int board[][COLS]) {

	// 1. Checks all runs for a winning run
	// row array is assigned with number of columns since column elements make up each row.
	int row[COLS];

	// Outer loop is to iterate through the rows
	for (int r = 0; r < ROWS; ++r) {
		// inner loop is used to iterate through the columns and assign column elemetns to a 1D array
		for(int c = 0; c < COLS; ++c) {
			// Column elements are assigned to the row array
			row[c] = board[r][c];
		}

		// Player, COLS(elements that make up the row), and the 1D row are passed to LongestRunInRow() to
		// check if the longest consecutive run and it compares it to the number needed to win which is 6.
		if (LongestRunInRow(player, COLS, row) >= NUM_TO_WIN) {
			return true;
		}
	}

	// 2. Checks all columns for a winning run
	for (int c = 0; c < COLS; ++c) {
		// LongestRunInCol reuses LongestRunInRow to check a column.
		if (LongestRunInCol(player, c, COLS, ROWS, board) >= NUM_TO_WIN) {
			return true;
		}
	}
	// 3. If there isn't a winning run, the game is still going.
	// Returns false if a long run was not found.
	return false;
}
