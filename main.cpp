#include <iostream>
#include <queue>
using namespace std;
struct number {
    int i;
    int x;
    int y;
    number(int i, int x, int y):i(i), x(x), y(y) {}

    void out() {
        cout << i + 1 << ' ' << x << ' ' << y << endl;
    }
};

struct node {
    int i;
    int x;
    int y;
    bool sign[3][3];
    
    node(int i = 0, int x = 0, int y = 0) {
        this->i = i;
        this->x = x;
        this->y = y;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sign[i][j] = true;
            }
        }
    }
    
    int getSum() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sum += sign[i][j];
            }
        }
        return sum;
    }
    
    void outSign() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << sign[i][j];
            }
            cout << endl;
        }
    }
};

node& signBox(node box[9][3][3], int i, int j, int k, bool value) {
    int x = j / 3;
    int y = k / 3;
    int u = j % 3;
    int v = k % 3;
    box[i][x][y].sign[u][v] = value;
    return box[i][x][y];
}

bool getBox(node box[9][3][3], int i, int j, int k) {
    int x = j / 3;
    int y = k / 3;
    int u = j % 3;
    int v = k % 3;
    return box[i][x][y].sign[u][v];
}

void init(int chessBoard[9][9], node box[9][3][3]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                box[i][j][k].i = i;
                box[i][j][k].x = j;
                box[i][j][k].y = k;
            }
        }
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (chessBoard[i][j] == 0) {
                    continue;
                }
                if (k != chessBoard[i][j] - 1) {
                    signBox(box, k, i, j, false);
                    continue;
                }
                for (int l = 0; l < 9; l++) {
                    // clear the sign of row
                    signBox(box, k, i, l, false);
                    // clear the sign of col
                    signBox(box, k, l, j, false);
                    // clear the sign of box
                    box[k][i / 3][j / 3].sign[l / 3][l % 3] = false;
                }
            }
        }
    }
}

void print(int chessBoard[9][9]) {
    cout << "当前棋局为：" << endl;
    cout << "┌─────┬─────┬─────┐" << endl;
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            cout << "├─────┼─────┼─────┤" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                cout << "│";
            } else {
                cout << ' ';
            }
            if (chessBoard[i][j] == 0) {
                cout << ' ';
            } else {
                cout << chessBoard[i][j];
            }
        }
        cout << "│" << endl;
    }
    cout << "└─────┴─────┴─────┘" << endl;
    cout << endl;
}

void printBox(node box[9][3][3], int x) {
    cout << x + 1 << "的hash:" << endl;
    cout << "┌─────┬─────┬─────┐" << endl;
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            cout << "├─────┼─────┼─────┤" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                cout << "│";
            } else {
                cout << ' ';
            }
            int val = (getBox(box, x, i, j) ? 1 : 0);
            if (val == 0) {
                cout << ' ';
            } else {
                cout << val;
            }
        }
        cout << "│" << endl;
    }
    cout << "└─────┴─────┴─────┘" << endl;
    // for (int i = 0; i < 3; i++) {
    // for (int j = 0; j < 3; j++) {
    // cout << box[x][i][j].getSum();
    // }
    // cout << endl;
    // }
}

void read(int chessBoard[9][9]) {
    char ch;
    cout << "请输入数独残局，共九行，每行连续九个数字，格子为空直接输入空格" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            ch = cin.get();
            if (ch == ' ') {
                chessBoard[i][j] = 0;
            } else {
                chessBoard[i][j] = ch - '0';
            }
        }
        cin.get();
    }
}

// void initQueue(node box[9][3][3], queue<number> &que) {
    // for (int i = 0; i < 9; i++) {
        // for (int j = 0; j < 3; j++) {
            // for (int k = 0; k < 3; k++) {
                // if (box[i][j][k].getSum() == 1) {
                    // for (int m = 0; m < 3; m++) {
                        // for (int n = 0; n < 3; n++) {
                            // if (box[i][j][k].sign[m][n]) {
                                // que.push(number(i, j * 3 + m, k * 3 + n));
                            // }
                        // }
                    // }
                // }
            // }
        // }
    // }
// }

void updateQueue(node box[9][3][3], queue<number> &que, int validMap[9][9], int chessBoard[9][9]) {
    // update box with rule1
    // for (int i = 0; i < 9; i++) {
        // if (i != cur.i) {
            // signBox(box, i, cur.x, cur.y, false);
            // continue;
        // }
        // for (int j = 0; j < 9; j++) {
            // signBox(box, i, cur.x, j, false);
            // signBox(box, i, j, cur.y, false);
            // signBox(box, i, cur.x / 3 * 3 + j / 3, cur.y / 3 * 3 + j % 3, false);
        // }
    // }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (chessBoard[i][j] != 0) {
                for (int k = 0; k < 9; k++) {
                    signBox(box, k, i, j, false);
                    signBox(box, chessBoard[i][j] - 1, i, k, false);
                    signBox(box, chessBoard[i][j] - 1, k, j, false);
                    signBox(box, chessBoard[i][j] - 1, i / 3 * 3 + k / 3, j / 3 * 3 + k % 3, false);
                }
            }
        }
    }

    // update box with rule3
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int baseX = j / 3 * 3;
            int baseY = j % 3 * 3;
            int sum = box[i][j / 3][j % 3].getSum();
            for (int k = 0; k < 3; k++) {
                int rowSum = 0;
                int colSum = 0;
                for (int l = 0; l < 3; l++) {
                    rowSum += getBox(box, i, baseX + k, baseY + l);
                    colSum += getBox(box, i, baseX + l, baseY + k);
                }
                if (rowSum == sum && sum != 0) {
                    for (int l = 0; l < 9; l++) {
                        if (l / 3 != j % 3) {
                            signBox(box, i, baseX + k, l, false);
                        }
                    }
                }
                if (colSum == sum && sum != 0) {
                    for (int l = 0; l < 9; l++) {
                        if (l / 3 != j / 3) {
                            signBox(box, i, l, baseY + k, false);
                        }
                    }
                }
            }
        }
    }
    
    // update queue with boxes from rule1 && rule3
    for (int i = 0; i < 9; i++) {
        int sum = 0;
        int tmpX = -1;
        int tmpY = -1;
        // row
        for (int j = 0; j < 9; j++) {
            sum = 0;
            for (int k = 0; k < 9; k++) {
                if (getBox(box, i, j, k)) {
                    sum++;
                    tmpX = j;
                    tmpY = k;
                }
            }
            if (sum == 1 && validMap[tmpX][tmpY]) {
                validMap[tmpX][tmpY] = 0;
                que.push(number(i, tmpX, tmpY));
                cout << "row " << ' ';
                cout << tmpX + 1 << ' ' << tmpY + 1 << ' ' << i + 1 << endl;
            }
        }
        // col
        for (int j = 0; j < 9; j++) {
            sum = 0;
            for (int k = 0; k < 9; k++) {
                if (getBox(box, i, k, j)) {
                    sum++;
                    tmpX = k;
                    tmpY = j;
                }
            }
            if (sum == 1 && validMap[tmpX][tmpY]) {
                validMap[tmpX][tmpY] = 0;
                que.push(number(i, tmpX, tmpY));
                cout << "col " << ' ';
                cout << tmpX + 1 << ' ' << tmpY + 1 << ' ' << i + 1 << endl;
            }
        }
        // box
        for (int j = 0; j < 9; j++) {
            sum = 0;
            for (int k = 0; k < 9; k++) {
                if (getBox(box, i, j / 3 * 3 + k / 3, j % 3 * 3 + k % 3)) {
                    sum++;
                    tmpX = j / 3 * 3 + k / 3;
                    tmpY = j % 3 * 3 + k % 3;
                }
            }
            if (sum == 1 && validMap[tmpX][tmpY]) {
                validMap[tmpX][tmpY] = 0;
                que.push(number(i, tmpX, tmpY));
                cout << "box " << ' ';
                cout << tmpX + 1 << ' ' << tmpY + 1 << ' ' << i + 1 << endl;
            }
        }
    }
    
    // update queue with rule2
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int sum = 0;
            int tmpNum = -1;
            for (int k = 0; k < 9; k++) {
                if (getBox(box, k, i, j)) {
                    sum++;
                    tmpNum = k;
                }
            }
            
            if (validMap[i][j] && sum == 1) {
                validMap[i][j] = 0;
                que.push(number(tmpNum, i, j));
                cout << "rest" << ' ';
                cout << i + 1 << ' ' << j + 1 << ' ' << tmpNum + 1 << endl;
            }
        }
    }
}

void bfs(node box[9][3][3], queue<number> &que, int chessBoard[9][9]) {
    /**
     * rule1: 直接摒除法
     * rule2: 唯一解法
     * rule3: 区间摒除法
     */
    int validMap[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (chessBoard[i][j] == 0) {
                validMap[i][j] = 1;
            } else {
                validMap[i][j] = 0;
            }
        }
    }
    updateQueue(box, que, validMap, chessBoard);
    while (!que.empty()) {
        number cur = que.front();
        que.pop();
        if (chessBoard[cur.x][cur.y] != 0) {
            continue;
        }
        // update chessBoard
        chessBoard[cur.x][cur.y] = cur.i + 1;

        // for (int i = 0; i < 9; i++) {
            // if (i != cur.i) {
                // signBox(box, i, cur.x, cur.y, false);
                // continue;
            // }
            // for (int j = 0; j < 9; j++) {
                // signBox(box, i, cur.x, j, false);
                // signBox(box, i, j, cur.y, false);
                // signBox(box, i, cur.x / 3 * 3 + j / 3, cur.y / 3 * 3 + j % 3, false);
            // }
        // }

        updateQueue(box, que, validMap, chessBoard);
    }
}

int main() {
    int chessBoard[9][9];
    node box[9][3][3];
    queue<number> que;
    read(chessBoard);
    init(chessBoard, box);
    bfs(box, que, chessBoard);
    for (int i = 0; i < 9; i++) printBox(box, i);
    print(chessBoard);
    return 0;
}
