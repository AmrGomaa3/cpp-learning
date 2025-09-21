#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>
#include <limits>


// constant variables
constexpr int MAX_STUDENTS {50};
constexpr int MIN_STUDENTS {1};
constexpr int EXAMS {3};


// student struct
struct Student {
    int id;
    std::string name;
    int scores[EXAMS];
    float average;
};


// function prototypes
int getIntInput(std::string_view inputMsg, int upperLimit, int lowerLimit);
Student* createStudentArray(int num);
void getStudentData(Student* arr, int size);
int menu();
void printStudentRecords(Student* arr, int size, bool search=false, int ID=0);
void searchByID(Student* arr, int size);
void printStats(Student* arr, int size);


int main() {
    int noOfStudents {getIntInput("Enter no. of Students", MAX_STUDENTS, MIN_STUDENTS)};

    Student* studentArr;
    try {
        studentArr = createStudentArray(noOfStudents);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    getStudentData(studentArr, noOfStudents);

    while (true) {
        int choice {menu()};

        if (choice == 1) printStudentRecords(studentArr, noOfStudents);
        else if (choice == 2) searchByID(studentArr, noOfStudents);
        else if (choice == 3) printStats(studentArr, noOfStudents);
        else {
            delete[] studentArr;
            break;
        }
    }

    return EXIT_SUCCESS;
}


int getIntInput(std::string_view inputMsg, int upperLimit, int lowerLimit) {
    int input;

    while (true) {
        try {
            std::cout << inputMsg << ": ";
            std::cin >> input;

            // check valid input
            if (std::cin.fail() || input > upperLimit || input < lowerLimit) {
                throw std::invalid_argument("Invalid input!\n");
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard leftover junk
                break;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what();
            std::cerr << "Input must be an integer between " << lowerLimit << " and " << upperLimit << "\n";

            std::cin.clear(); // reset the stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard leftover junk
        }
    }

    return input;
}


Student* createStudentArray(int num) {
    Student* ptr {nullptr};

    try {
        ptr = new Student[num];
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Fatal error!\n";
        throw; // return to the caller
    }

    return ptr;
}


void getStudentData(Student* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "===== Student " << i + 1 << " =====\n";
        std::cout << "Student name: ";
        std::getline(std::cin >> std::ws, arr[i].name);

        int sumExams {0};

        for (int j = 0; j < EXAMS; j++) {
            std::string inputMsg {"Exam " + std::to_string(j + 1) + " score: "};
            arr[i].scores[j] = getIntInput("Exam " + std::to_string(j + 1) + " score: ", 100, 0);
            sumExams += arr[i].scores[j];
        }

        arr[i].id = 1000 + 1 + i;

        arr[i].average = static_cast<float>(sumExams) / EXAMS;
    }
}


int menu() {
    std::cout << "\n";
    std::cout << "===== Menu =====\n"
              << "1. Print all records\n"
              << "2. Search by id\n"
              << "3. Print statistics\n"
              << "4. Quit\n";

    int choice {getIntInput("Choice", 4, 1)};

    return choice;
}


void printStudentRecords(Student* arr, int size, bool search, int ID) {
    bool found {false};

    for (int i = 0; i < size; i++) {
        if (search) {
            if (arr[i].id == ID) found = true;
            else continue;
        }

        std::cout << "\n";
        std::cout << "===== Student " << i + 1 << " =====\n";
        std::cout << "Student id   : " << arr[i].id << "\n";
        std::cout << "Student name : " << arr[i].name << "\n";

        for (int j = 0; j < EXAMS; j++) {
            std::cout << "Exam " << j + 1 << "       : " << arr[i].scores[j] << "\n";
        }

        std::cout << "Average score: " << arr[i].average << "\n";

        if (found) return;
    }

    if (search && !found) throw std::out_of_range("Student id not found!");
}


void searchByID(Student* arr, int size) {
    int ID {getIntInput("Enter student id", 1000+MAX_STUDENTS, 1000+MIN_STUDENTS)};

    try {
        printStudentRecords(arr, size, true, ID);
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }
}


void printStats(Student* arr, int size) {
    int highestScore {0};
    std::string_view highestScoreStudent {};
    int lowestScore {100};
    std::string_view lowestScoreStudent {};
    int classSum {0};

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < EXAMS; j++) {
            classSum += arr[i].scores[j];

            if (arr[i].scores[j] > highestScore) {
                highestScore = arr[i].scores[j];
                highestScoreStudent = arr[i].name;
            } else if (arr[i].scores[j] < lowestScore) {
                lowestScore = arr[i].scores[j];
                lowestScoreStudent = arr[i].name;
            }
        }
    }

    std::cout << "\n";
    std::cout << "class average: " << static_cast<float>(classSum) / (size * EXAMS) << "\n";
    std::cout << "Highest score: " << highestScoreStudent << "(" << highestScore << ")" << "\n";
    std::cout << "Lowest score : " << lowestScoreStudent << "(" << lowestScore << ")" << "\n";
}
