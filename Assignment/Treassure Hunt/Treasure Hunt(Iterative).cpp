#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
int countroom = 0;
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define N 10
#define M 10

class pathstack
{
    class node
    {
    public:
        friend class stack;
        int x;
        int y;
        node* next;
    };

public:
    node* top;
    pathstack() { top = nullptr; }
    void push(int a, int b)
    {
        if (top == nullptr)
        {
            node* temp = new node;
            temp->x = a;
            temp->y = b;
            top = temp;
            temp->next = nullptr;
        }
        else
        {
            node* temp = new node;
            temp->x = a;
            temp->y = b;
            temp->next = top;
            top = temp;
        }
    }
    void printnode()
    {
        node* c = top;
        while (c != nullptr)
        {
            cout <<"(" << c->x << "," << c->y << ")" << " ";
            c = c->next;
        }
        cout << endl;
    }

};

void Print(int r, int c, char map[10][10])
{
    system("cls");
    char X = '#', S = ' ';

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            if (i == r && j == c) cout << "*" << "  ";
            else cout << map[i][j] << "  ";
        cout << endl;
    }
}

void filehandeling(char map[10][10], string a);

void filehandeling(char map[10][10], string a)
{
    string str;
    fstream file; char data;
    file.open(a);
    if (!file)
    {
        cout << "No file found!" << endl;
    }
    else
    {
        char d;
        int i = 0;
        while (!file.eof())
        {
            getline(file, str);
            for (int j = 0, k = 0; j < 10; j++, k = k + 2)
            {
                d = str[k];
                map[i][j] = d;
            }
            i++;
        }
        file.close();
    }


    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

class roomstack
{
    class node
    {
    public:
        friend class stack;
        int room_number;
        char name[10][10];
        node* next;
    };

public:
    node* top;
    roomstack() { top = nullptr; }

    void push(int a, char room[10][10])
    {
        if (top == nullptr)
        {
            node* temp = new node;
            temp->room_number = a;
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    temp->name[i][j] = room[i][j];
                }
            }

            top = temp;
            temp->next = nullptr;
        }
        else
        {
            node* temp = new node;
            temp->room_number = a;
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    temp->name[i][j] = room[i][j];
                }
            }
            temp->next = top;
            top = temp;
        }
    }

    void pop()
    {
        if (top != nullptr)
        {
            node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    void get_map(char map[10][10])
    {
        node* temp = top;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                map[i][j] = temp->name[i][j];
            }
        }
    }

};

int main()
{
    roomstack memorystack;
    roomstack gamestack;
    pathstack path;

    char map[10][10];
    char room2[10][10]; string room_name = "room2.txt";
    filehandeling(room2, room_name);
    memorystack.push(2, room2);

    char room1[10][10];  room_name = "room1.txt";
    filehandeling(room1, room_name);
    memorystack.push(1, room1);

    int r = 1;
    memorystack.get_map(map);
    memorystack.pop();
    gamestack.push(r, map);

    int c; int x = 8, y = 5;
    int win = -1;
    while (1)
    {
        c = 0;
        switch ((c = _getch()))
        {
        case KEY_UP:
            if (x > 1 && map[x - 1][y] != 'X') x = x - 1;
            Print(x, y, map);
            break;
        case KEY_DOWN:
            if (x < N - 2 && map[x + 1][y] != 'X') x = x + 1;
            Print(x, y, map);
            break;
        case KEY_LEFT:
            if (y > 1 && map[x][y - 1] != 'X') y = y - 1;
            Print(x, y, map);
            break;
        case KEY_RIGHT:
            if (y < M - 2 && map[x][y + 1] != 'X') y = y + 1;
            Print(x, y, map);
            break;
        default:
            break;
        }
        path.push(x, y);
        if (map[x][y] == 'D')
        {
            win = 0;
            break;
        }
        else if (map[x][y] == 'G') //door
        {
            r++;
            memorystack.get_map(map);
            memorystack.pop();
            gamestack.push(r, map);
        }

        else if (map[x][y] == 'P')
        {
            if (r == 1)
            {
                r++;
                memorystack.get_map(map);
                memorystack.pop();
                gamestack.push(r, map);
            }
        }

        else if (map[x][y] == 'T')
        {
            win = 1;
            break;
        }

    }
    if (win == 1)
    {
        cout << "You won the game" << endl;
        path.printnode();
    }
    if (win == 0)
    {
        cout << "You lost the game" << endl;
    }

    system("Pause");
    return 0;
}
