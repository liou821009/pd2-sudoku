#ifndef SUDOKU_H
#define SUDOKU_H
#include<iostream>
#include<string>
using namespace std;

class Sudoku
{
	public:
	    Sudoku();
        void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		void printOut();
    private:
        int store[9][9];
        int tmp[9][9];
		int empty;
		int tmp_empty;
		bool rowIsValid(int num,int row,int col,int array[][9]);
		bool colIsValid(int num,int row,int col,int array[][9]);
		bool blockIsValid(int num,int row,int col,int array[][9]);
        int change[9][9];
        bool theSame();
		bool last_backtracking();
        bool first_backtracking();
		void degree(int n);
		bool wrong;
		bool nozero;
		bool checknozero;

};


#endif // SUDOKU_H
