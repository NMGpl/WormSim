class Board {
public:
    int x, y;
    vector<vector<char>> board;
    void initializeBoard() {
        board = vector<vector<char>>(x, vector<char>(y, ' '));
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
                }
                else {
                    cout << "Wspolrzedna y powinna miescic sie w zakresie 0 - " << y << "\n";
                }
            }
            else {
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
    // Setter
    void setWorm(int x, int y) {
        board[x][y] = '8';
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
    int coords[2] = { 10, 20 };

    int hunger = 50;
    int bodySegments = 5;
    vector<vector<int>> bodyCoords;

    Worm() {
        bodyCoords.push_back({ coords[0], coords[1] });
    }

    void moveHead(Board& board) {
        int dx[4] = { 0, -1, 0, 1 };
        int dy[4] = { 1, 0, -1, 0 };

        int direction = rand() % 4;

        int newX = coords[0] + dx[direction];
        int newY = coords[1] + dy[direction];
        if (hunger > 0) {
            hunger -= 1;
            cout << "Moj glod to: " << hunger << " / 25\n";
            if (newX >= 0 && newX < board.getX() && newY >= 0 && newY < board.getY() && isBody(newX, newY)) {
                //moveBody(coords);
                moveBody(board);
                coords[0] = newX;
                coords[1] = newY;
            }
            drawWorm(board);
            cout << "Jestem w x: " << coords[0] << " y: " << coords[1] << "\n";
        }
        else {
            cout << "Zmarlem z glodu :( \n";
        }
    }
    //void moveBody(int headCoords[2]) {
    //    vector<vector<int>> bodyCoords;
    //    bodyCoords = vector<vector<int>>(bodySegments, vector<int>(2));
    //    for (int i = bodySegments - 1; i >= 0; i--) {
    //        if (i > 0) {
    //            bodyCoords[i][0] = bodyCoords[i - 1][0];
    //            bodyCoords[i][1] = bodyCoords[i - 1][1];
    //        }else{
    //            bodyCoords[0][0] = headCoords[0];   //x pierwszego segmentu = x glowy
    //            bodyCoords[0][1] = headCoords[1];   //y pierwszego segmentu = y glowy
    //        }
    //    }
    //    cout << "Koordynaty glowy - x: " << coords[0] << " y: " << coords[1] << endl;
    //    cout << "Koordynaty 1. segmentu - x: " << bodyCoords[0][0] << " y: " << bodyCoords[0][1] << endl;
    //}
    void moveBody(Board& board) {
        if (bodyCoords.size() < bodySegments) {
            vector<int> last = bodyCoords.back();
            while (bodyCoords.size() < bodySegments) {
                bodyCoords.push_back(last);
            }
        }
        for (int i = bodySegments - 1; i > 0; i--) {
            bodyCoords[i] = bodyCoords[i - 1];
        }
        bodyCoords[0] = { coords[0], coords[1] }; // g³owa sprzed ruchu
        cout << "Koordynaty 1. segmentu - x: " << bodyCoords[0][0] << " y: " << bodyCoords[0][1] << endl;
    }
    void ageUp() {
        if (age < maxAge) {
            age += 1;
            cout << "Mam " << age << " lat, maksymalnie przezyje " << maxAge;
        }if (age > 3) {
            //rozmnazanie
        }
    }
    bool isBody(int newX, int newY) {
        for (size_t i = 0; i < bodyCoords.size(); i++) {
            if (newX == bodyCoords[i][0] && newY == bodyCoords[i][1]) {
                cout << "Nie moge tu wejsc \n";
                return false;
            }
        }
        return true;
    }
    void drawWorm(Board& board) {
        board.setWorm(coords[0], coords[1]);
        for (int i = bodySegments - 1; i >= 0; i--) {
            board.setWorm(bodyCoords[i][0], bodyCoords[i][1]);
        }
    }
};