#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <algorithm>
#define DARK_BLUE "\033[38;5;17m"
#define NEON_BLUE "\033[38;5;33m"
#define PURPLE "\033[38;5;129m"
#define GREEN "\033[1;32m"
#define DBLUE "\033[34m"
#define DBLUEBG "\033[44m"
#define GOLD "\033[43m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define BLUEBG "\033[104m"
#define DPURPLE "\033[1;35m"
#define B1 "\033[38;5;39m"
#define B2 "\033[38;5;45m"
#define B3 "\033[38;5;51m"
#define B4 "\033[38;5;117m"
#define B5 "\033[38;5;19m"
#define P1 "\033[38;5;93m"
#define P2 "\033[38;5;99m"
#define P3 "\033[38;5;63m"
#define P4 "\033[38;5;54m"
#define P5 "\033[38;5;135m"
using namespace std;
struct Cell
{
    int value = 0;
    bool found = false;
} c;
struct Board
{
    Cell board[4][4];
    bool isSolved = false;
    int move = 0;
} board;
struct Player
{
    string username = "";
    int wins = 0;
    int losses = 0;
    int time = 0;
    int timeLimit = 1000;
    int index = 0;
} p;
Player players[100];
time_t startTime;
int cursorRow = 0, cursorCol = 0;
void SignIn(Player &p)
{
    system("cls");
    bool found = false;
    int count = 0;
    string username;
    cout << DBLUE << "Who are you? (when nobody's watching) " << RESET;
    getline(cin, username);

    ifstream fin("scoreboard.txt");
    if (!fin)
    {
        ofstream fout("scoreboard.txt");
        fout << 0 << endl;
        fout.close();
        fin.open("scoreboard.txt");
    }

    if (fin)
    {
        fin >> count;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; i++)
        {
            fin >> players[i].wins >> players[i].losses >> players[i].time;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(fin, players[i].username);

            if (players[i].username == username)
            {
                system("cls");
                cout << PURPLE << "You can check out anytime you like, but you can never leave. WELCOME BACK! :)" << endl
                     << endl
                     << endl
                     << DBLUE << "Press any key..."
                     << RESET;
                _getch();
                p.index = i;
                p.username = username;
                p.wins = players[i].wins;
                p.losses = players[i].losses;
                found = true;
                break;
            }
        }
        fin.close();
    }

    if (!found)
    {
        system("cls");
        cout << PURPLE << "We've rewritten the code for you. You are part of the system now!" << endl
             << endl
             << DBLUE << "Press any key..."
             << RESET;
        _getch();
        p.index = count;
        p.username = username;
        p.wins = 0, p.losses = 0;
        players[count].username = username;
        players[count].wins = 0;
        players[count].losses = 0;
        count++;
    }
}
void UpdatePlayer(Player &p, bool win)
{
    int count = 0;
    ifstream fin("scoreboard.txt");
    if (fin)
    {
        fin >> count;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < count; i++)
        {
            fin >> players[i].wins >> players[i].losses >> players[i].time;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(fin, players[i].username);
        }
        fin.close();
    }
    if (p.index >= count)
    {
        players[p.index].username = p.username;
        players[p.index].wins = 0;
        players[p.index].losses = 0;
        count = p.index + 1;
    }

    if (win)
    {
        players[p.index].wins++;
    }
    else
    {
        players[p.index].losses++;
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (players[j].wins > players[i].wins || (players[j].wins == players[i].wins && players[j].losses < players[i].losses))
            {
                swap(players[i], players[j]);
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (players[i].username == p.username)
        {
            p.index = i;
            break;
        }
    }
    ofstream fout("scoreboard.txt");
    fout << count << endl;
    for (int i = 0; i < count; i++)
    {
        fout << players[i].wins << " " << players[i].losses << endl
             << players[i].username << endl;
    }
    fout.close();
}
void ScoreBoard()
{
    system("cls");
    int count = 0;
    ifstream fin("scoreboard.txt");
    if (!fin)
    {
        cout << PURPLE << "Be the first one..." << endl
             << endl
             << DBLUE << "Press any key..." << RESET;
        _getch();
        return;
    }
    fin >> count;
    for (int i = 0; i < count; i++)
    {
        fin >> players[i].wins >> players[i].losses;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, players[i].username);
    }
    fin.close();
    int nameWidth = 10;
    for (int i = 0; i < count; i++)
    {
        nameWidth = max(nameWidth, (int)players[i].username.length());
    }
    cout << BLUEBG << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << endl;
    cout << "|| #  || " << setw(nameWidth) << left << "PLAYER"
         << " || WINS   || LOSSES ||" << endl;
    cout << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << RESET << endl;

    for (int i = 0; i < count; i++)
    {
        cout << BLUEBG << "|| " << DPURPLE << setw(2) << left << i + 1 << RESET << BLUEBG
             << " || " << DPURPLE << setw(nameWidth) << left << players[i].username << RESET << BLUEBG
             << " || " << DPURPLE << setw(6) << left << players[i].wins << RESET << BLUEBG
             << " || " << DPURPLE << setw(6) << left << players[i].losses << RESET << BLUEBG
             << " ||" << endl;
    }
    cout << "||====||" << string(nameWidth + 2, '=') << "||========||========||" << RESET << endl
         << endl;
    cout << endl
         << DBLUE << "Press any key to return..." << RESET;
    _getch();
}
int RunMenu(string options[], int count)
{
    int selected = 0;
    while (true)
    {
        system("cls");
        cout << PURPLE << "Blue pill or red pill? The choice is yours!" << endl
             << RESET << endl;

        for (int i = 0; i < count; i++)
        {
            if (i == selected)
            {
                cout << DBLUE << "> " << DBLUEBG << options[i] << RESET << endl;
            }
            else
            {
                cout << "  " << DBLUE << options[i] << endl
                     << RESET;
            }
        }

        int key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
            {
                selected--;
                if (selected < 0)
                {
                    selected = count - 1;
                }
            }
            else if (key == 80)
            {
                selected++;
                if (selected >= count)
                {
                    selected = 0;
                }
            }
        }
        else if (key == 13)
        {
            return selected;
        }
    }
    return selected;
}
void Print(Board &b, Player &p, Cell &c)
{
    system("cls");
    time_t now = time(0);
    p.time = difftime(now, startTime);
    int minutes = p.time / 60;
    int seconds = p.time % 60;
    cout << GOLD << "Time: "
         << minutes << ":"
         << (seconds < 10 ? "0" : "") << seconds
         << RESET << endl
         << DBLUE << "moves: " << b.move << endl;
    cout << DARK_BLUE << "===================================" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b.board[i][j].value == 0)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "       ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||       |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "       |" << RESET;
                }
            }
            else if (b.board[i][j].value == 2)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "   " << RESET << NEON_BLUE << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||   " << RESET << NEON_BLUE << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "   " << RESET << NEON_BLUE << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 4)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "   " << RESET << B1 << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||   " << RESET << B1 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "   " << RESET << B1 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 8)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "   " << RESET << B2 << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||   " << RESET << B2 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "   " << RESET << B2 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 16)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << B3 << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << B3 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << B3 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 32)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << B4 << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << B4 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << B4 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 64)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << B5 << b.board[i][j].value << RESET << DARK_BLUE << "   ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << B5 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << B5 << b.board[i][j].value << RESET << DARK_BLUE << "   |" << RESET;
                }
            }
            else if (b.board[i][j].value == 128)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << P1 << b.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << P1 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << P1 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
            }
            else if (b.board[i][j].value == 256)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << P2 << b.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << P2 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << P2 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
            }
            else if (b.board[i][j].value == 512)
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << "  " << RESET << P3 << b.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "||  " << RESET << P3 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << "  " << RESET << P3 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
            }
            else if (b.board[i][j].value == 2048)
            {
                c.found = true;
                if (j == 3)
                {
                    cout << DARK_BLUE << " " << RESET << P4 << b.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "|| " << RESET << P4 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << " " << RESET << P4 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
            }
            else
            {
                if (j == 3)
                {
                    cout << DARK_BLUE << " " << RESET << P5 << b.board[i][j].value << RESET << DARK_BLUE << "  ||" << RESET;
                }
                else if (j == 0)
                {
                    cout << DARK_BLUE << "|| " << RESET << P5 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
                else
                {
                    cout << DARK_BLUE << " " << RESET << P5 << b.board[i][j].value << RESET << DARK_BLUE << "  |" << RESET;
                }
            }
        }
        if (i == 3)
        {
            cout << endl
                 << DARK_BLUE << "===================================" << RESET << endl;
        }
        else
        {
            cout << endl
                 << DARK_BLUE << "||-------|-------|-------|-------||" << RESET << endl;
        }
    }
    cout << endl
         << endl
         << PURPLE << "E.T. phone home... (Press Esc)" << RESET << endl;
}
bool End(Board &b)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b.board[i][j].value == 0)
                return false;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b.board[i][j].value == b.board[i][j + 1].value)
                return false;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (b.board[i][j].value == b.board[i + 1][j].value)
                return false;
        }
    }
    return true;
}
void SaveGame(Board &b)
{
    system("cls");
    ofstream fout("savedgame.txt");
    if (!fout)
    {
        cout << DBLUE << "Failed to open the file." << RESET;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fout << b.board[i][j].value << " ";
        }
        fout << endl;
    }
    fout << b.move << endl;
    fout.close();
    cout << PURPLE << "The gold watch is safe." << endl
         << endl
         << DBLUE << "Press any key to return..." << RESET << endl;
    _getch();
    return;
}
void MoveRight(Board &b)
{
    b.move++;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b.board[i][j].value == 0)
            {
                for (int k = j; k > 0; k--)
                {
                    swap(b.board[i][k], b.board[i][k - 1]);
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (b.board[i][j].value == b.board[i][j - 1].value && b.board[i][j].value != 0)
            {
                b.board[i][j].value *= 2;
                b.board[i][j - 1].value = 0;
                for (int k = j - 1; k > 0; k--)
                {
                    swap(b.board[i][k].value, b.board[i][k - 1].value);
                }
            }
        }
    }
}
void MoveLeft(Board &b)
{
    b.move++;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (b.board[i][j].value == 0)
            {
                for (int k = j; k < 3; k++)
                {
                    swap(b.board[i][k], b.board[i][k + 1]);
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b.board[i][j].value == b.board[i][j + 1].value && b.board[i][j].value != 0)
            {
                b.board[i][j].value *= 2;
                b.board[i][j + 1].value = 0;
                for (int k = j + 1; k < 3; k++)
                {
                    swap(b.board[i][k].value, b.board[i][k + 1].value);
                }
            }
        }
    }
}
void MoveDown(Board &b)
{
    b.move++;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (b.board[i][j].value == 0)
            {
                for (int k = i; k > 0; k--)
                {
                    swap(b.board[k][j], b.board[k - 1][j]);
                }
            }
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int i = 3; i > 0; i--)
        {
            if (b.board[i][j].value == b.board[i - 1][j].value && b.board[i][j].value != 0)
            {
                b.board[i][j].value *= 2;
                b.board[i - 1][j].value = 0;
                for (int k = i - 1; k > 0; k--)
                {
                    swap(b.board[k][j].value, b.board[k - 1][j].value);
                }
            }
        }
    }
}
void MoveUp(Board &b)
{
    b.move++;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 3; i >= 0; i--)
        {
            if (b.board[i][j].value == 0)
            {
                for (int k = i; k < 3; k++)
                {
                    swap(b.board[k][j], b.board[k + 1][j]);
                }
            }
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (b.board[i][j].value == b.board[i + 1][j].value && b.board[i][j].value != 0)
            {
                b.board[i + 1][j].value *= 2;
                b.board[i][j].value = 0;
                for (int k = i + 1; k < 4; k++)
                {
                    swap(b.board[k][j].value, b.board[k - 1][j].value);
                }
            }
        }
    }
}
void GenerateBoard(Board &b, int num)
{
    while (num > 0)
    {
        int col = 0, row = 0;
        int number = rand() % 2;
        do
        {
            col = rand() % 4;
            row = rand() % 4;
        } while (b.board[row][col].value != 0);

        if (number == 0)
            b.board[row][col].value = 2;
        else
            b.board[row][col].value = 4;
        num--;
    }
}
void GamePlay(Board &b, Player &p, Cell &c)
{
    SignIn(p);
    startTime = time(0);

    while (true)
    {
        string options[] = {"Play", "Save The Game", "Exit"};
        int selected = RunMenu(options, 3);
        if (selected == 0)
        {
            Print(b, p, c);
            while (true)
            {
                int key = _getch();

                if (key == 224)
                {
                    key = _getch();

                    if (key == 72)
                    {
                        MoveUp(b);
                    }
                    else if (key == 80)
                    {
                        MoveDown(b);
                    }
                    else if (key == 75)
                    {
                        MoveLeft(b);
                    }
                    else if (key == 77)
                    {
                        MoveRight(b);
                    }
                    GenerateBoard(b, 1);
                }
                else if (key == 27)
                {
                    break;
                }
                Print(b, p, c);
                if (End(b))
                {
                    cout << RED << "-------------------------------" << endl
                         << "| ANOTHER ONE BITES THE DUST! |" << endl
                         << "-------------------------------" << endl
                         << endl
                         << "What does not kill you, makes you stronger. Stand up." << endl
                         << endl
                         << RESET;
                    _getch();
                    UpdatePlayer(p, false);
                    return;
                }
                if (c.found)
                {
                    cout << GREEN << "-------------------------" << endl
                         << "| WE ARE THE CHAMPIONS! |" << endl
                         << "-------------------------" << endl
                         << endl
                         << "Veni, Vidi, Vici." << endl
                         << endl
                         << RESET;
                    _getch();
                    UpdatePlayer(p, true);
                    return;
                }
            }
        }
        else if (selected == 1)
        {
            SaveGame(b);
        }
        else if (selected == 2)
        {
            system("cls");
            cout << PURPLE << "Snap back to reality!" << RESET;
            _getch();
            return;
        }
    }
}
void ContinueGame(Board &b)
{
    system("cls");
    int fix = 0;
    ifstream fin("savedgame.txt");
    if (!fin)
    {
        cout << PURPLE << "ERROR 404! NOT FOUND!" << endl
             << endl
             << DBLUE << "Press any key..." << RESET << endl;
        _getch();
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fin >> b.board[i][j].value;
        }
    }
    fin >> b.move;
    fin.close();
    cout << PURPLE << "The show must go on." << endl
         << endl
         << DBLUE << "Press any key to return..." << RESET;
    GamePlay(b, p, c);
}
void ResetGame(Board &b, Player &p, Cell &c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            b.board[i][j].value = 0;
        }
    }
    b.move = 0, b.move = 0, cursorRow = 0, cursorCol = 0, p.time = 0;
    c.found = false;
}
int main()
{
    while (true)
    {
        int index = 0;
        system("cls");
        cout << PURPLE << "WELCOME! :)" << endl
             << endl
             << DBLUE << "Press any key..." << RESET << endl;
        _getch();
        srand(time(0));
        string options[] = {"New Game", "Scoreboard", "Continue saved game", "Exit"};
        int selected = RunMenu(options, 4);
        int level = 0;

        if (selected == 0)
        {
            ResetGame(board, p, c);
            GenerateBoard(board, 2);
            GamePlay(board, p, c);
        }
        else if (selected == 1)
        {
            ScoreBoard();
        }
        else if (selected == 2)
        {
            ContinueGame(board);
        }
        else if (selected == 3)
        {
            system("cls");
            cout << PURPLE << "The End." << RESET << endl;
            return 1;
        }
    }
    return 0;
}
