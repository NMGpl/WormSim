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
    int maxAge = 25;
    int age = 0;
    int m = 0;
    int coords[2] = { 4, 4 };
    

    float hunger;
    void move(Board &board) {
        int dx[4] = { 0, -1, 0, 1 };
        int dy[4] = { 1, 0, -1, 0 };

        int direction = rand() % 4;
        
        int newX = coords[0] + dx[direction];
        int newY = coords[1] + dy[direction];

        if (newX >= 0 && newX < board.getX() && newY >= 0 && newY < board.getY()) {
            coords[0] = newX;
            coords[1] = newY;
        }
        cout << "Jestem w x: " << coords[0] << " y: " << coords[1] << "\n";
        }
    void ageUp() {
        if (age < maxAge) {
            age += 1;
            cout << "Mam " << age << " lat, maksymalnie przezyje " << maxAge;
        }if (age > 3) {
            //rozmnazanie
        }
    }
};
int main(){
    srand(time(0));
    int stop;
    int days = 0;
    Board plansza;
    Worm worm;
    plansza.x = 10;
    plansza.y = 10;
    plansza.initializeBoard();
    plansza.printBoard();
    //plansza.startWormColony();
    while (true) {
        //plansza.printBoard();
        //plansza.wormDistribution();
        cout << "Uplynelo: " << days << " tur\n";
        days += 1;
        plansza.printBoard();
        worm.move(plansza);
        worm.ageUp();
        cin >> stop;
        if (stop == 111) {
            break;
        }
        cout << endl;
    }
    return 0;
}