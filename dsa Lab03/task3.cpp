#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const int ROWS = 3;
    const int COLS = 3;

    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}