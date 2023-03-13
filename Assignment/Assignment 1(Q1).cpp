#include <iostream>
using namespace std;
const int N = 4;
class Stack {
public:

    void push(int stack[][2], int& top, int x, int y) {
        stack[top][0] = x;
        top++;
        stack[top][1] = y;
    }

    void pop(int& top) {
        top--;
    }
    
    void solveMaze(int maze[N][N])
    {
        int stack[N * N][2];
        int top = 0;
        push(stack, top, 0, 0);
        maze[0][0] = 2;
        while (top != -1)
        {
            int row = stack[top][0];
            int col = stack[top][1];

          
            if (row == N - 1 && col == N - 1) {
                break;
            }
            else if (valid(maze, row + 1, col)) {
                push(stack, top, row + 1, col);
                maze[row + 1][col] = 2;
            }
            else if (valid(maze, row, col + 1)) {
                push(stack, top, row, col + 1);
                maze[row][col + 1] = 2;
            }
            else {
                maze[row][col]=0;
                pop(top);
            }
        }
        
         for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    }
    bool valid(int maze[N][N],int row, int col)
    {
    return (row >= 0 && row < N && col >= 0 && col < N && maze[row][col] == 1);
    }
   
};

int main() {
    int maze[4][4] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    Stack s;
    s.solveMaze(maze);

    return 0;
}
