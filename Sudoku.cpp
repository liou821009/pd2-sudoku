#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku()
{
    wrong = false;
    nozero = true;
    checknozero = false;
    empty = 0;
	tmp_empty =0;
}
void Sudoku::degree(int n)
{
    for(int x=0;x<n;x++)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                store[j][8-i] = tmp[i][j];
            }
        }
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                tmp[i][j] = store[i][j];
            }

        }
    }
}
bool Sudoku::theSame()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(store[i][j] != tmp[i][j])
                return false;
        }
    }
    return true;


}


void Sudoku::printOut()
{
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<9;++j)
		{
			cout << store[i][j] << " ";
		}
		cout << "\n";
	}
}
void Sudoku::readIn()
{
	for(int i =0;i<9;++i)
	{
		for(int j=0;j<9;++j)
		{
			cin >> store[i][j];
			if(store[i][j] == 0)
            {
                empty++;
                nozero = false;
            }
		}
	}
	for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            tmp[i][j] = store[i][j];
        }

    }
    tmp_empty = empty;

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(store[i][j] != 0)
            {

                if(blockIsValid(store[i][j], i, j,store) && colIsValid(store[i][j], i, j,store) && rowIsValid(store[i][j], i, j, store))
                {
                    wrong = false;

                }
                else
                {
                    wrong = true;
                    return;
                }
            }

        }
    }
}

bool Sudoku::rowIsValid(int num, int row, int col,int array[][9])
{

        if(checknozero == false)
        {

            for(int i = 0; i < 9; ++i)
            {
                if(i != col)
                {
                    if(array[row][i] == num)
                    {
                        return false;
                    }
                }

            }
            return true;
        }
        else
        {
            for(int i = 0; i < 9; ++i)
            {
                if(array[row][i] == num)
                    return false;
            }
            return true;
        }

}

bool Sudoku::colIsValid(int num, int row, int col,int array[][9])
{

        if(checknozero == false)
        {

            for(int i = 0; i < 9; ++i)
            {
                if(i != row)
                {
                    if(array[i][col] == num)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            for(int i = 0; i < 9; ++i)
            {
                if(array[i][col] == num)
                    return false;
            }
            return true;
        }

}

bool Sudoku::blockIsValid(int num, int row, int col,int array[][9])
{
        if(checknozero == false)
        {

            int start_row = (row/3)*3;
            int start_col = (col/3)*3;
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    if(start_row+i != row && start_col+j != col)
                    {
                        if(array[start_row+i][start_col+j] == num)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            int start_row = (row/3)*3;
            int start_col = (col/3)*3;
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    if(array[start_row+i][start_col+j] == num)
                        return false;
                }
            }
            return true;
        }

}
bool Sudoku::first_backtracking()
{

	if(empty == 0)
	{

		return true;
	}

	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(store[i][j] == 0)	//if not filled
			{
				for(int trynum = 9; trynum >= 1; --trynum)
				{

					if( blockIsValid(trynum, i, j,store) && colIsValid(trynum, i, j,store) && rowIsValid(trynum, i,j,store) )
					{

						store[i][j] = trynum;
						empty--;
						if(first_backtracking())
						  return true;
						store[i][j] = 0;
						empty++;
					}
				}
				return false;
			}
		}

	}

}
bool Sudoku::last_backtracking()
{

	if(tmp_empty == 0)
	{
		return true;
	}

	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(tmp[i][j] == 0)	//if not filled
			{
				for(int trynum = 1; trynum <= 9; ++trynum)
				{

					if( blockIsValid(trynum, i, j,tmp) && colIsValid(trynum, i, j,tmp) && rowIsValid(trynum, i,j,tmp) )
					{

						tmp[i][j] = trynum;
						tmp_empty--;
						if(last_backtracking())
						  return true;
						tmp[i][j] = 0;
						tmp_empty++;
					}
				}
				return false;
			}
		}
	}
}
void Sudoku::giveQuestion()
{
    srand(time(NULL));
    int time = rand()%5;
    if(time == 0)
    {
        int q1[9][9] = {{0,0,6,0,0,3,0,0,0},
        {0,0,0,8,9,0,0,0,0},
        {4,0,5,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,5},
        {0,2,0,0,0,1,0,0,0},
        {0,9,0,0,0,0,0,0,6},
        {0,3,0,0,0,0,8,0,0},
        {0,0,1,0,0,0,2,0,0},
        {0,0,0,0,4,5,0,0,0}};
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                store[i][j] = q1[i][j];
                tmp[i][j] = q1[i][j];
            }
        }
        printOut();
    }
    else if(time == 1)
    {
        int q1[9][9] = {{0,0,0,5,0,0,0,3,9},
        {0,3,9,0,4,1,2,5,7},
        {0,0,5,0,3,9,6,8,0},
        {0,9,0,3,2,0,0,6,0},
        {0,0,8,9,5,6,7,4,0},
        {0,0,0,0,1,8,9,2,0},
        {0,4,6,1,0,5,3,0,0},
        {0,8,7,0,9,0,5,1,0},
        {0,5,0,0,0,0,0,0,0}};
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                store[i][j] = q1[i][j];
                tmp[i][j] = q1[i][j];
            }
        }
        printOut();
    }
    else if(time == 2)
    {
        int q1[9][9] = {{0,0,0,6,0,0,0,0,0},
        {0,0,7,0,0,9,5,0,1},
        {9,0,4,3,7,0,0,0,0},
        {3,0,0,0,0,0,2,5,8},
        {0,2,0,0,0,1,0,0,0},
        {7,8,5,0,0,0,0,0,3},
        {0,0,0,0,8,2,6,0,7},
        {2,0,6,7,0,0,9,0,0},
        {0,0,0,0,9,0,0,0,0}};
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                store[i][j] = q1[i][j];
                tmp[i][j] = q1[i][j];
            }
        }
        printOut();
    }
    else if(time == 3)
    {
        int q1[9][9] = {{7,0,0,0,0,0,0,1,9},
        {4,6,0,1,9,0,0,0,0},
        {0,0,0,6,8,2,7,0,4},
        {0,9,0,0,0,0,0,0,7},
        {0,0,0,3,0,0,4,0,5},
        {0,0,6,7,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0},
        {2,0,0,0,7,4,0,0,0},
        {0,0,0,2,0,0,3,0,0}};
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                store[i][j] = q1[i][j];
                tmp[i][j] = q1[i][j];
            }
        }
        printOut();
    }
    else
    {
        int q1[9][9] = {{0,9,0,0,0,0,0,1,0},
        {0,4,6,3,0,0,5,0,0},
        {1,0,0,9,0,0,0,0,2},
        {0,0,0,6,0,1,0,0,4},
        {0,1,0,0,4,0,0,8,0},
        {7,0,0,8,0,9,0,0,0},
        {2,0,0,0,0,3,0,0,6},
        {0,0,1,0,0,4,8,2,0},
        {0,6,0,0,0,0,0,7,0}};
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                store[i][j] = q1[i][j];
                tmp[i][j] = q1[i][j];
            }
        }
        printOut();
    }




}

void Sudoku::solve()
{
    checknozero = true;
	if(wrong == true)
        cout << "0" << "\n";
    else if(nozero == true)
    {
        cout << "1" << "\n";
        printOut();
    }
    else if(last_backtracking() && first_backtracking())
	{
		if(theSame() == true )
        {
             cout << "1" << "\n";
             printOut();
        }
        else
            cout << "2" << "\n";

	}
	else
        cout << "0" << "\n";

}

void Sudoku::changeNum(int a,int b)
{
	for(int i =0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(tmp[i][j] == a)
				store[i][j] = b;
			else if(tmp[i][j] == b)
				store[i][j] = a;
			else
				continue;
		}
	}
	for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            tmp[i][j] = store[i][j];
        }

    }
}
void Sudoku::changeRow(int a,int b)
{
	int a_tmp = (a*3)+1;
	int b_tmp = (b*3)+1;
	for(int i=0;i<9;i++)
    {
        store[a_tmp-1][i] = tmp[b_tmp-1][i];
        store[a_tmp][i] = tmp[b_tmp][i];
        store[a_tmp+1][i] = tmp[b_tmp+1][i];
        store[b_tmp-1][i] = tmp[a_tmp-1][i];
        store[b_tmp][i] = tmp[a_tmp][i];
        store[b_tmp+1][i] = tmp[a_tmp+1][i];
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            tmp[i][j] = store[i][j];
        }

    }
}
void Sudoku::changeCol(int a,int b)
{
	int a_tmp = (a*3)+1;
	int b_tmp = (b*3)+1;
	for(int i=0;i<9;i++)
    {
        store[i][a_tmp-1] = tmp[i][b_tmp-1];
        store[i][a_tmp] = tmp[i][b_tmp];
        store[i][a_tmp+1] = tmp[i][b_tmp+1];
        store[i][b_tmp-1] = tmp[i][a_tmp-1];
        store[i][b_tmp] = tmp[i][a_tmp];
        store[i][b_tmp+1] = tmp[i][a_tmp+1];
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            tmp[i][j] = store[i][j];
        }

    }
}
void Sudoku::rotate(int n)
{

    if(n%4 == 3)
    {
        degree(3);
    }
    else if(n%4 == 2)
    {
        degree(2);
    }
    else if(n%4 == 1)
    {
        degree(1);
    }
    else
    {
        return;
    }





}
void Sudoku::flip(int n)
{
    if(n != 0)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                store[i][j] =  tmp[i][8-j];
            }
        }
    }
    else
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                store[i][j] =  tmp[8-i][j];
            }
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            tmp[i][j] = store[i][j];
        }

    }
}
void Sudoku::transform()
{
    changeNum(2,3);
    changeRow(3,5);
    changeCol(5,3);
    rotate(43);
    flip(0);
    printOut();
}







