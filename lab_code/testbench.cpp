//
// Don't modify code in this file, with the exception
// of adding test cases.
//
#include "apex_code.h"
#include <fstream>
#include <iostream>

using namespace std;

static int testNum = 0;
static int testsCorrect = 0;

static int funcTestNum = 0;
static int funcTestCorrect = 0;

// Use for everything other than doubles/floats
template <typename T> bool test(T expected, T result) {
  funcTestNum++;
  testNum++;
  if (expected != result) {
    cout << "FAILED: Expected " << expected << ", received " << result << ".\n";
  } else {
    cout << "PASS\n";
    testsCorrect++;
    funcTestCorrect++;
  }

  return expected == result;
}

/**
 * Mark the starting point for the tests of a specific function.
 *
 * @param startFuncName the function name to start testing
 */
void startTests(string startFuncName) {
  cout << "----- Start of testing " << startFuncName << " -----" << endl;

  funcTestNum = 0;
  funcTestCorrect = 0;
}

/**
 * Mark the ending point for the tests of a specific function.
 *
 * @param endFuncName the function name to end testing
 */
void endTests(string endFuncName) {
  if (funcTestNum == funcTestCorrect) {
    cout << "----- All tests passed for " << endFuncName << "! -----" << endl;
  } else {
    cout << "----- Some tests failed for " << endFuncName << " :( -----"
         << endl;
  }
  cout << endl;
}

/**
 * Mark the end of the test suite.
 */
void endAllTests() {
  if (testsCorrect == testNum) {
    cout << "All tests passed! Let's goooo" << endl;
  } else {
    cout << "Some tests failed. Keep trying!" << endl;
  }
}

int main() {
  // To add a test case, duplicate one of the test lines below
  // modify input with the first string, and the expected output
  // in the second string.

  startTests("LongestRunInRow");
  int a_test[ROWS] = {FIRST, SECOND, FIRST, SECOND, NONE,
                      FIRST, FIRST,  FIRST, FIRST,  SECOND};

  (void)test(4, LongestRunInRow(FIRST, ROWS, a_test));
  (void)test(1, LongestRunInRow(SECOND, ROWS, a_test));

  int b_test[ROWS] = {SECOND, SECOND, SECOND, SECOND, NONE,
                      SECOND, FIRST,  FIRST,  FIRST,  SECOND};

  (void)test(3, LongestRunInRow(FIRST, ROWS, b_test));
  (void)test(4, LongestRunInRow(SECOND, ROWS, b_test));
  endTests("LongestRunInRow");

  startTests("LongestRunInCol");
  int board_test[ROWS][COLS] = {
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {FIRST, SECOND, FIRST, SECOND, NONE, FIRST, FIRST, FIRST, FIRST, SECOND},
      {FIRST, SECOND, FIRST, SECOND, NONE, FIRST, FIRST, FIRST, FIRST, SECOND},
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {FIRST, SECOND, FIRST, SECOND, NONE, FIRST, FIRST, FIRST, FIRST, SECOND},
      {SECOND, SECOND, SECOND, SECOND, NONE, SECOND, FIRST, FIRST, FIRST,
       SECOND},
      {SECOND, SECOND, SECOND, SECOND, FIRST, SECOND, FIRST, FIRST, FIRST,
       SECOND}};

  (void)test(10, LongestRunInCol(SECOND, 1, COLS, ROWS, board_test));
  (void)test(3, LongestRunInCol(SECOND, 2, COLS, ROWS, board_test));
  endTests("LongestRunInCol");

  startTests("PlacePiece");
  (void)test(false, PlacePiece(9, SECOND, board_test));
  (void)test(false, PlacePiece(COLS, SECOND, board_test));
  ShowBoard(board_test);
  (void)test(true, PlacePiece(4, FIRST, board_test));
  endTests("PlacePiece");

  // Create board filled with FIRST values for testing
  int test_win[ROWS][COLS];
  for (int r = 0; r < ROWS; ++r) {
    fill_n(test_win[r], COLS, FIRST);
  }
  ShowBoard(test_win);

  startTests("GameWon");
  (void)test(true, GameWon(FIRST, test_win));
  (void)test(false, GameWon(SECOND, test_win));
  endTests("GameWon");

  endAllTests();

  return 0;
}
