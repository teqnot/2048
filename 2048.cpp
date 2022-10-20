#include <iostream>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;
int score;
int plusScore;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int board[4][4], backup[4][4];

int randomLocation()
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist4(0, 3);
    return dist4(rng);
}

int randomNumber()
{
    random_device dev2;
    mt19937 rng2(dev2());
    uniform_int_distribution<mt19937::result_type> dist2(0, 1);
    return dist2(rng2);
}

void drawBoard()
{
    string nameGame = R"(
                                                   ____   ___  _  _    ___  
                                                  |___ \ / _ \| || |  ( _ ) 
                                                    __) | | | | || |_ / _ \ 
                                                   / __/| |_| |__   _| (_) |
                                                  |_____|\___/   |_|  \___/ )";
    SetConsoleTextAttribute(hConsole, 14);
    cout << nameGame;

    cout << "\n";
    cout << "\t\t\t [SCORE]: " << score << endl;

    cout << "\n";
    cout << "\t\t\t\t\t   -------------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "\t\t\t\t\t   |";
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) printf("%4c    |", ' ');
            else printf("%4d    |", board[i][j]); 
        }
        cout << "\n";
        cout << "\t\t\t\t\t   -------------------------------------" << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << " \n\n Controls (+ :: o)\tr - restart\n\n     ^\t\t\tu - undo\tq - quit\n\t\t\t\t\t\t\t\t"
        << "\t\t\t\n<    v    >\t\t\t     "
        << " \n\t\t\t\t                             ";
}

void getRight(int i)
{
    int firstNums[2] = { 2, 4 }, x, y, x2, y2;

    switch (i) {

    case 0:
        x = randomLocation();
        y = randomLocation();
        board[x][y] = firstNums[randomNumber()];

        while (true) {
            x2 = randomLocation();
            y2 = randomLocation();
            if (x2 != x && y2 != y) {
                board[x2][y2] = firstNums[randomNumber()];
                break;
            }
            else {
                continue;
            }
        }
        break;

    case 1:
        while (true) {
            x = randomLocation();
            y = randomLocation();
            if (board[x][y] == 0)
            {
                board[x][y] = firstNums[randomNumber()];
                break;
            }
            else continue;
        }
        break;
    }  
}

bool fullBoard()
{
    bool full = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) full = false;
        }
    }
    return full;
}

bool checkForWin()
{
    bool win = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 2048) win = true;
        }
    }
    return win;
}

bool checkForLoss()
{
    bool loss = true;
    if (fullBoard() == true) {
        for (int i = 1; i < 3; i++) {
            for (int j = 1; j < 3; j++) {
                if (board[i][j] && board[i][j] == board[i + 1][j]) loss = false;
                if (board[i][j] && board[i][j] == board[i - 1][j]) loss = false;
                if (board[i][j] && board[i][j] == board[i][j + 1]) loss = false;
                if (board[i][j] && board[i][j] == board[i][j - 1]) loss = false;
            }
        }
    }
    if (fullBoard() == false) loss = false;
    return loss;
}


void updateBoard(char control)
{
    switch (control)
    {
    case 'u':
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                if (board[j][i] && board[j][i] == board[j + 1][i])
                {
                    board[j][i] += board[j + 1][i];
                    board[j + 1][i] = 0;
                    plusScore = (((log2(board[j][i])) - 1) * board[j][i]);
                    score += (((log2(board[j][i])) - 1) * board[j][i]);

                }
            }
        break;

    case 'd':
        for (int i = 0; i < 4; i++)
            for (int j = 3; j > 0; j--)
            {
                if (board[j][i] && board[j][i] == board[j - 1][i])
                {
                    board[j][i] += board[j - 1][i];
                    board[j - 1][i] = 0;
                    plusScore = (((log2(board[j][i])) - 1) * board[j][i]);
                    score += (((log2(board[j][i])) - 1) * board[j][i]);
                }
            }
        break;

    case 'l':
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] && board[i][j] == board[i][j + 1])
                {
                    board[i][j] += board[i][j + 1];
                    board[i][j + 1] = 0;
                    plusScore = ((log2(board[i][j])) - 1) * board[i][j];
                    score += ((log2(board[i][j])) - 1) * board[i][j];
                }
            }
        break;

    case 'r':
        for (int i = 0; i < 4; i++)
            for (int j = 3; j > 0; j--)
            {
                if (board[i][j] && board[i][j] == board[i][j - 1])
                {
                    board[i][j] += board[i][j - 1];
                    board[i][j - 1] = 0;
                    plusScore = ((log2(board[i][j])) - 1) * board[i][j];
                    score += (((log2(board[i][j])) - 1) * board[i][j]);
                }
            }
        break;

    }
}

void fillSpace(char control)
{
    switch (control)
    {
    case 'u':
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
            {
                if (!board[j][i])
                {
                    for (int k = j + 1; k < 4; k++)
                        if (board[k][i])
                        {
                            board[j][i] = board[k][i];
                            board[k][i] = 0;
                            break;
                        }
                }

            }
        }
        break;

    case 'd':
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--)
            {
                if (!board[j][i])
                {
                    for (int k = j - 1; k >= 0; k--)
                        if (board[k][i])
                        {
                            board[j][i] = board[k][i];
                            board[k][i] = 0;
                            break;
                        }
                }

            }
        }
        break;

    case 'l':
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
            {
                if (!board[i][j])
                {
                    for (int k = j + 1; k < 4; k++)
                        if (board[i][k])
                        {
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            break;
                        }
                }

            }
        }
        break;


    case 'r':
        for (int i = 0; i < 4; i++)
            for (int j = 3; j >= 0; j--)
            {
                if (!board[i][j])
                {
                    for (int k = j - 1; k >= 0; k--)
                        if (board[i][k])
                        {
                            board[i][j] = board[i][k];
                            board[i][k] = 0;
                            break;
                        }
                }

            }break;

    }
}

void backUpBoard()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) { 
            backup[i][j] = board[i][j];
        }
    }
}

bool checkIfPossible()
{
    int count = 0;
    bool flag = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == backup[i][j]) count += 1;
        }
    }
    if (count == 16) flag = false;
    return flag;
}

void reset() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
    score = 0;
}

bool winGame()
{
    SetConsoleTextAttribute(hConsole, 14);
    int scoreFile;
    string answer;
    system("cls");
    
    ifstream highscore("score.txt");
    highscore >> scoreFile;
    if (score > scoreFile) {
        highscore.close();
        ofstream file("score.txt");
        file << score;
    }

    string endgame = R"(
                                __  __               _       __            __
                                \ \/ /___  __  __   | |     / /___  ____  / /
                                 \  / __ \/ / / /   | | /| / / __ \/ __ \/ / 
                                 / / /_/ / /_/ /    | |/ |/ / /_/ / / / /_/  
                                /_/\____/\__,_/     |__/|__/\____/_/ /_(_) 
)";
    cout << endgame << endl;

    cout << "\t\t\t\t\t  Your [SCORE] was: " << score << endl;

    cout << "\t\t\t\t   Go back to main menu? [Y/N] ";
    cin >> answer;
    if (answer == "Y" || answer == "y") {
        reset();
        return true;
    }
    if (answer == "N" || answer == "n") {
        return false;
    }
}

bool endGame()
{
    SetConsoleTextAttribute(hConsole, 14);
    int scoreFile;
    string answer;
    system("cls");
    string endgame = R"(
                                __  __               __               __  __
                                \ \/ /___  __  __   / /   ____  _____/ /_/ /
                                 \  / __ \/ / / /  / /   / __ \/ ___/ __/ / 
                                 / / /_/ / /_/ /  / /___/ /_/ (__  ) /_/_/  
                                /_/\____/\__,_/  /_____/\____/____/\__(_)   
                                         )";
    cout << endgame << endl;

    ifstream highscore("score.txt");
    highscore >> scoreFile;
    if (score > scoreFile) {
        highscore.close();
        ofstream file("score.txt");
        file << score;
    }

    cout << "\t\t\t\t\t  Your [SCORE] was: " << score << endl;
    
    cout << "\t\t\t\t   Go back to main menu? [Y/N] ";
    cin >> answer;
    if (answer == "Y" || answer == "y") {
        reset();
        return true;
    }
    if (answer == "N" || answer == "n") {
        return false;
    }
}

void help()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 14);
    string buffer;
    char text[] = "> The game starts with 2 randomly placed numbers (2 or 4) in a 4x4 grid (16 cells).> Use the controls to move the cells. (Arrow Keys)> 2 cells of the same number will merge and add up.> New 2s and 4s will appear randomly on an empty cell with each move you make.> Your objective is to make 2048 in a cell without getting stuck!> Press Enter to continue...";

    for (int i = 0; text[i]; i++)
    {
        if (text[i] == '>')
        {
            cout << "\n\n";
        }

        cout << text[i];
    }
    getchar();
    return;
}

void undo()
{
    if (checkIfPossible() && score >= 0) score -= plusScore;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = backup[i][j];
        }
    }
    return;
}

int GameLoop(int flag) 
{
    if (flag == 0) {
        system("cls");
        getRight(0);
        drawBoard();
    }
    if (flag == 1) {
        system("cls");
        drawBoard();
    }
    
    while (true) {
        if (checkForLoss()) {
            Sleep(1500);
            return 0;
        }

        if (checkForWin()) {
            Sleep(1500);
            return 1;
        }

        else
        {
            switch (_getch())
            {
            case 'h':
                help();
                GameLoop(1);
                break;

            case 'u':
                undo();
                GameLoop(1);
                break;

            case 'q':
                return 2;
                break;

            case 'r':
                reset();
                GameLoop(0);
                break;

            case 72:
                backUpBoard();
                system("cls");
                fillSpace('u');
                updateBoard('u');
                fillSpace('u');
                if (checkIfPossible()) {
                    getRight(1);
                }
                drawBoard();
                break;

            case 80:
                backUpBoard();
                system("cls");
                fillSpace('d');
                updateBoard('d');
                fillSpace('d');
                if (checkIfPossible()) {
                    getRight(1);
                }
                drawBoard();
                break;

            case 75:
                backUpBoard();
                system("cls");
                fillSpace('l');
                updateBoard('l');
                fillSpace('l');
                if (checkIfPossible()) {
                    getRight(1);
                }
                drawBoard();
                break;

            case 77:
                backUpBoard();
                system("cls");
                fillSpace('r');
                updateBoard('r');
                fillSpace('r');
                if (checkIfPossible()) {
                    getRight(1);
                }
                drawBoard();
                break;
            }
        }
    }
    
}

void highscore()
{
    system("cls");
    ifstream file("score.txt");
    int scoreMenu;
    file >> scoreMenu;
    cout << "> Your [HIGHSCORE] is: " << scoreMenu << endl;
    cout << "\n> Press Enter to continue...";
    getchar();
    return;
}

int main()
{
    system("cls");
    char ans;
    int state;
    bool state2, state3;
    SetConsoleTextAttribute(hConsole, 14);
    const auto name = R"(  
                               _______  ________  ___   ___  ________          ___       
                              /  ___  \|\   __  \|\  \ |\  \|\   __  \        |\  \      
                             /__/|_/  /\ \  \|\  \ \  \\_\  \ \  \|\  \       \ \  \     
                             |__|//  / /\ \  \\\  \ \______  \ \   __  \       \ \  \    
                                 /  /_/__\ \  \\\  \|_____|\  \ \  \|\  \       \ \__\   
                                |\________\ \_______\     \ \__\ \_______\       \|__|   
                                 \|_______|\|_______|      \|__|\|_______|          ___ 
                                   v1.3.4                                          |\__\
                                                                                   \|__|
)";
    cout << name;
    string signature = R"(
                                                                               __          _   __                   
                                                                              / /  __ __  (_) / /____ ___ ____  ___ 
                                                                             / _ \/ // / _   / __/ -_) _ `/ _ \/ _ \
                                                                            /_.__/\_, / (_)  \__/\__/\_, /_//_/\___/
                                                                                 /___/                /_/)";
    cout << "\n";
    cout << "\t\t\t\t\t  ---------------------------------" << endl;
    cout << "\t\t\t\t\t  | 1. Play (P)                    |" << endl;
    cout << "\t\t\t\t\t  ---------------------------------" << endl;
    cout << "\t\t\t\t\t  | 2. Highscore (S)               |" << endl;
    cout << "\t\t\t\t\t  ---------------------------------" << endl;
    cout << "\t\t\t\t\t  | 3. Rules/Help (H)              |" << endl;
    cout << "\t\t\t\t\t  ---------------------------------" << endl;
    cout << "\t\t\t\t\t  | 4. Quit (Q)                    |   " << endl;
    cout << "\t\t\t\t\t  ---------------------------------" << endl;

    cout << "\n\n";
    cout << signature;
    reset();
    while (true)
    {
        ans = _getche();
        if (ans == 'p' || ans == 'P' || ans == '1')
        {
            state = GameLoop(0);
            break;
        }
        if (ans == 's' || ans == 'S' || ans == '2')
        {
            highscore();
            main();
            break;
        }
        if (ans == 'h' || ans == 'H' || ans == '3')
        {
            help();
            main();
            break;
        }
        if (ans == 'q' || ans == 'Q' || ans == '4')
            exit(1);
        else {
            cout << "\t\t\t\t\t  Incorrect input. Try again.";
            continue;
        }
    }
    
    if (state == 0)
    {
        state2 = endGame();
        if (state2 == true) main();
    }
    if (state == 1)
    {
        state3 = winGame();
        if (state3 == true) main();
    }
    
    if (state == 2)
    {
        reset();
        main();
    }
}