#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    const int NUM_STUDENTS = 6;
    const int NUM_SUBJECTS = 4;

    string subjects[NUM_SUBJECTS] = {"English", "Math", "Programming", "AI"};

    int marks[NUM_STUDENTS][NUM_SUBJECTS] = {
        {85, 90, 88, 92},
        {78, 82, 80, 85},
        {92, 95, 94, 98},
        {65, 70, 72, 68},
        {88, 84, 90, 89},
        {75, 80, 85, 82}
    };

    int totalMarks[NUM_STUDENTS] = {0};
    double averageMarks[NUM_STUDENTS] = {0.0};

    for (int i = 0; i < NUM_STUDENTS; i++) {
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            totalMarks[i] += marks[i][j];
        }
        averageMarks[i] = static_cast<double>(totalMarks[i]) / NUM_SUBJECTS;
    }

    cout << "=========================================================================\n";
    cout << setw(12) << "Student" 
         << setw(12) << subjects[0] 
         << setw(12) << subjects[1] 
         << setw(15) << subjects[2] 
         << setw(10) << subjects[3] 
         << setw(10) << "Total" 
         << setw(10) << "Average" << endl;
    cout << "=========================================================================\n";

    for (int i = 0; i < NUM_STUDENTS; i++) {
        cout << setw(12) << ("Student " + to_string(i + 1));
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            cout << setw(12) << marks[i][j];
        }
        cout << setw(10) << totalMarks[i] 
             << setw(10) << fixed << setprecision(2) << averageMarks[i] << endl;
    }
    cout << "=========================================================================\n\n";

    cout << "--- Highest Marks in Each Subject ---\n";
    for (int j = 0; j < NUM_SUBJECTS; j++) {
        int highestSubjectMark = marks[0][j];
        for (int i = 1; i < NUM_STUDENTS; i++) {
            if (marks[i][j] > highestSubjectMark) {
                highestSubjectMark = marks[i][j];
            }
        }
        cout << setw(15) << subjects[j] << ": " << highestSubjectMark << endl;
    }

    int highestTotal = totalMarks[0];
    int topStudentIndex = 0;

    for (int i = 1; i < NUM_STUDENTS; i++) {
        if (totalMarks[i] > highestTotal) {
            highestTotal = totalMarks[i];
            topStudentIndex = i;
        }
    }

    cout << "\n-------------------------------------------------------------------------\n";
    cout << "Top Performing Student: Student " << (topStudentIndex + 1) 
         << " with a Total Score of " << highestTotal 
         << " (Average: " << fixed << setprecision(2) << averageMarks[topStudentIndex] << ")\n";
    cout << "-------------------------------------------------------------------------\n";

    return 0;
}