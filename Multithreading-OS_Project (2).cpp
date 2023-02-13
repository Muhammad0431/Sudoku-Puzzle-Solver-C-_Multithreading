#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;
#define N 9

// int board[9][9];
int board[9][9] = {
            {5, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
};
int valid[11]; 
int subgridCt = 2;



bool isPresentInCol(int col, int num) { 
    for (int row = 0; row < N; row++)
        if (board[row][col] == num)
            return true;
    return false;
}
bool isPresentInRow(int row, int num) { 
    for (int col = 0; col < N; col++)
        if (board[row][col] == num)
            return true;
    return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}
void sudokuGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            //  if (col == 3 || col == 6)
            //      cout << " | ";
            cout << board[row][col] << " ";
        }
        // if (row == 2 || row == 5) {
        //     cout << endl;
        //     //  for (int i = 0; i < N; i++)
        //     //       cout << "---";
        // }
         cout << endl;
    }
}
bool findEmptyPlace(int& row, int& col) { 
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (board[row][col] == 0) 
                return true;
    return false;
}
bool isValidPlace(int row, int col, int num) {
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3,
        col - col % 3, num);
}
bool solveSudoku() {
    int row, col;
    if (!findEmptyPlace(row, col))
        return true;
    for (int num = 1; num <= 9; num++) { 
        if (isValidPlace(row, col, num)) {
            board[row][col] = num;
            if (solveSudoku())
                return true;
            board[row][col] = 0; 
        }
    }
    return false;
}




typedef struct {

    int row;
    int column;

}parameters;

pthread_t col_thread, row_thread, first_thread, second_thread, third_thread, fourth_thread, fifth_thread, sixth_thread, seventh_thread, eighth_thread, ninth_thread;

void* column_worker(void* param);
void* row_worker(void* param);
void* square_worker(void* param);


int main(int argc, char* argv[])
{
    int j = 0;
    int i = 0;
    int k = 0;


    //     //Error checking: if user only enters ./hw2 then gets this error
    // if (argc == 1) {
    //         fprintf(stderr,"Usage: ./hw2 <sudoku grid>\n");

    //         return -1;
    // 	}


    //    // reading file from agrv[] and portioning the numbers to the sudoku board
    // FILE *sudoku; 
    // sudoku = fopen(argv[1], "r");

    // for(i = 0; i < 9; i++){
    // 	for(j = 0; j < 9; j++){
    // 		fscanf(sudoku, "%d ", &board[i][j]);
    // 	}
    // }		




    // for (i = 0; i < 9; i++) {
    //     for (j = 0; j < 9; j++) {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << endl;
    // }




    parameters* checkRows = (parameters*)malloc(sizeof(parameters));
    checkRows->row = 0;
    checkRows->column = 0;

    parameters* checkCols = (parameters*)malloc(sizeof(parameters));
    checkCols->row = 0;
    checkCols->column = 0;

    parameters* first3by3 = (parameters*)malloc(sizeof(parameters));
    first3by3->row = 0;
    first3by3->column = 0;

    parameters* second3by3 = (parameters*)malloc(sizeof(parameters));
    second3by3->row = 0;
    second3by3->column = 3;

    parameters* third3by3 = (parameters*)malloc(sizeof(parameters));
    third3by3->row = 0;
    third3by3->column = 6;

    parameters* fourth3by3 = (parameters*)malloc(sizeof(parameters));
    fourth3by3->row = 3;
    fourth3by3->column = 0;

    parameters* fifth3by3 = (parameters*)malloc(sizeof(parameters));
    fifth3by3->row = 3;
    fifth3by3->column = 3;

    parameters* sixth3by3 = (parameters*)malloc(sizeof(parameters));
    sixth3by3->row = 3;
    sixth3by3->column = 6;

    parameters* seventh3by3 = (parameters*)malloc(sizeof(parameters));
    seventh3by3->row = 6;
    seventh3by3->column = 0;

    parameters* eighth3by3 = (parameters*)malloc(sizeof(parameters));
    eighth3by3->row = 6;
    eighth3by3->column = 3;

    parameters* ninth3by3 = (parameters*)malloc(sizeof(parameters));
    ninth3by3->row = 6;
    ninth3by3->column = 6;


    void* rows;
    void* cols;
    void* first_square;
    void* second_square;
    void* third_square;
    void* fourth_square;
    void* fifth_square;
    void* sixth_square;
    void* seventh_square;
    void* eighth_square;
    void* ninth_square;


    pthread_create(&col_thread, NULL, column_worker, (void*)checkCols);
    pthread_create(&row_thread, NULL, row_worker, (void*)checkRows);
    pthread_create(&first_thread, NULL, square_worker, (void*)first3by3);
    pthread_create(&second_thread, NULL, square_worker, (void*)second3by3);
    pthread_create(&third_thread, NULL, square_worker, (void*)third3by3);
    pthread_create(&fourth_thread, NULL, square_worker, (void*)fourth3by3);
    pthread_create(&fifth_thread, NULL, square_worker, (void*)fifth3by3);
    pthread_create(&sixth_thread, NULL, square_worker, (void*)sixth3by3);
    pthread_create(&seventh_thread, NULL, square_worker, (void*)seventh3by3);
    pthread_create(&eighth_thread, NULL, square_worker, (void*)eighth3by3);
    pthread_create(&ninth_thread, NULL, square_worker, (void*)ninth3by3);



    pthread_join(col_thread, &cols);
    pthread_join(row_thread, &rows);
    pthread_join(first_thread, &first_square);
    pthread_join(second_thread, &second_square);
    pthread_join(third_thread, &third_square);
    pthread_join(fourth_thread, &fourth_square);
    pthread_join(fifth_thread, &fifth_square);
    pthread_join(sixth_thread, &sixth_square);
    pthread_join(seventh_thread, &seventh_square);
    pthread_join(eighth_thread, &eighth_square);
    pthread_join(ninth_thread, &ninth_square);


    while (k < 11) {

     

        if (valid[k] == 1) {
            k++;
        }
        else {
            printf("\nThe Sudoku Puzzle is NOT solved. \n");
              if (solveSudoku() == true)
      sudokuGrid();
   else
      cout << "No solution exists";
            exit(0);
        }

    }
    printf("\nThe Sudoku Puzzle is solved. \n\n\n");


     if (solveSudoku() == true)
      sudokuGrid();
   else
      cout << "\nNo solution exists\n\n\n";


    return 0;
}


void* column_worker(void* params)
{
    int i, j;

    parameters* c_worker = (parameters*)params;
    int beginCol = c_worker->column;
    int beginRow = c_worker->row;

   
    for (i = beginCol; i < 9; i++) {

        int col[9] = { 0 };

        for (j = beginRow; j < 9; j++) {

            int val = board[i][j];

         

            if (col[val - 1] == 0 && val > 0) {
                col[val - 1] = val;

            }
         
            else {
                valid[0] = 0;
                pthread_exit(0);
            }
        }
    }
    valid[0] = 1;
    pthread_exit(0);
}


void* row_worker(void* params) {

    int i, j;

    parameters* r_worker = (parameters*)params;
    int beginCol = r_worker->column;
    int beginRow = r_worker->row;


    for (i = beginCol; i < 9; i++) {

        int row[9] = { 0 };

        for (j = beginRow; j < 9; j++) {

            int val = board[i][j];

         

            if (row[val - 1] == 0 && val > 0) {
                row[val - 1] = val;
            }


            else {
                valid[1] = 0;
                pthread_exit(0);
            }
        }
    }
    valid[1] = 1;
    pthread_exit(0);
}


void* square_worker(void* params) {

    int i, j;

    parameters* worker = (parameters*)params;
    int beginRow = worker->row;
    int beginCol = worker->column;

   
    int square[9] = { 0 }; 

    for (i = beginRow; i < beginRow + 3; ++i) {
        for (j = beginCol; j < beginCol + 3; ++j) {

            int val = board[i][j];


            if (square[val - 1] == 0 && val > 0) {
                square[val - 1] = val;
            }

          
            else {
                valid[subgridCt] = 0;
                subgridCt++;
                pthread_exit(0);
            }
        }
    }
    valid[subgridCt] = 1;
    subgridCt++;
    pthread_exit(0);
}
