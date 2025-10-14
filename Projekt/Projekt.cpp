using namespace std;
#include <iostream>
#include <vector>

class Board {
public:
    int x, y;
    vector<vector<int>> board;
    void initializeBoard() {
        board = vector<vector<int>>(x, vector<int>(y, 0));
    }
    void printBoard() {
        cout << "Hodowla robakow o wielkosci " << x << "x" << y << "\n";
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                cout << "[" << board[i][j] << "]";
            }
            cout << endl;
        }
    }
    void startWormColony() {
        int sx, sy, wormAmount;
        while (true) {
            cout << "Podaj wspolrzedna x: ";
            cin >> sx;
            if (sx <= x && sx >= 0) {
                cout << "Podaj wspolrzedna y: ";
                cin >> sy;
                if (sy <= y && sy >= 0) {
                    cout << "Podaj ilosc robakow: ";
                    cin >> wormAmount;
                    board[sx][sy] = wormAmount;
                    break;
                }else {
                    cout << "Wspolrzedna y powinna miescic sie w zakresie 0 - " << y << "\n";
                }
            }else {
                cout << "Wspolrzedna x powinna miescic sie w zakresie 0 - " << x << "\n";
            }
        }
    }
    void wormDistribution() {
        int wormAmount;
        for (size_t i = 0; i < x; i++) {
            for (size_t j = 0; j < y; j++) {
                wormAmount = board[i][j];
                if (wormAmount > 5) {

                    //Rozchodzenie sie robakow po sasiednich polach
                    board[i][j] -= 4;
                    if (i > 0) board[i - 1][j] += 1;
                    if (i < x - 1) board[i + 1][j] += 1;
                    if (j > 0) board[i][j - 1] += 1;
                    if (j < y - 1) board[i][j + 1] += 1;

                    //20% na smierc polowy kolonii na przepelninonym polu
                    if (rand() % 5 == 0) {
                        board[i][j] /= 2;
                    }
                }
            }
            
        }
        
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
};
class Worm {
public:
    int x, y, age, maxAge, direction, m;
    int mv[4] = { 0, 1, 0, -1 };
    float hunger;
    void move(Board plansza) {
        direction = rand() % 3;
        switch (direction) {
        case 0:
            m += 0;
            break;
        case 1:
            m += -1;
            break;
        case 2:
            m += 1;
            break;
        }
        if (x + m > 0 && x + m < plansza.x || y + m > 0 || y + m < plansza.y) {
            x += mv[m];
            y += mv[m + 1];
        }
    }
};
int main(){
    srand(time(0));
    int stop;
    Board plansza;
    plansza.x = 10;
    plansza.y = 10;
    plansza.initializeBoard();
    plansza.printBoard();
    plansza.startWormColony();
    while (true) {
        plansza.printBoard();
        plansza.wormDistribution();
        plansza.printBoard();
        cin >> stop;
        if (stop == 1) {
            break;
        }
    }
    return 0;
}