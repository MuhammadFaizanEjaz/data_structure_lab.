#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const int ROWS = 4;
    const int COLS = 5;

    int parking[ROWS][COLS] = {
        {1, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0}
    };

    int occupiedCount = 0;
    int emptyCount = 0;
    int totalCapacity = ROWS * COLS;

    cout << "=======================================\n";
    cout << "         PARKING LAYOUT (4x5)          \n";
    cout << "=======================================\n";
    cout << "        Space:  1   2   3   4   5\n";
    cout << "---------------------------------------\n";

    for (int i = 0; i < ROWS; i++) {
        cout << "Row " << i + 1 << "          ";
        for (int j = 0; j < COLS; j++) {
            cout << parking[i][j] << "   ";
            if (parking[i][j] == 1) {
                occupiedCount++;
            } else {
                emptyCount++;
            }
        }
        cout << endl;
    }

    cout << "=======================================\n\n";

    cout << "Total Parking Capacity: " << totalCapacity << " spaces\n";
    cout << "Total Occupied Spaces : " << occupiedCount << endl;
    cout << "Total Empty Spaces    : " << emptyCount << "\n\n";

    int userRow, userCol;
    cout << "Enter Row number (1-4): ";
    cin >> userRow;
    cout << "Enter Column/Space number (1-5): ";
    cin >> userCol;

    if (userRow >= 1 && userRow <= ROWS && userCol >= 1 && userCol <= COLS) {
        int rowIdx = userRow - 1;
        int colIdx = userCol - 1;

        cout << "\nStatus at Row " << userRow << ", Space " << userCol << ": ";
        if (parking[rowIdx][colIdx] == 1) {
            cout << "Occupied (1)" << endl;
        } else {
            cout << "Available / Empty (0)" << endl;
        }
    } else {
        cout << "\nInvalid row or column number entered!" << endl;
    }

    return 0;
}