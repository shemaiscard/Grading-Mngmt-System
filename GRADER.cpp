#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <string>
#include <map>

class GradeManager {
private:
    int refNumber;
    std::string name;
    std::vector<std::string> subjects;
    std::vector<std::string> professors;
    std::vector<float> marks;
    char grade;

    static std::map<char, float> gradeThresholds;

    void calculateGrade();
    static bool validateMark(float mark) { return mark >= 0 && mark <= 100; }

public:
    GradeManager() : refNumber(0), grade(' ') {}

    // Public methods to access private members
    std::vector<float> getMarks() const { return marks; }
    std::vector<std::string> getSubjects() const { return subjects; }
    std::vector<std::string> getProfessors() const { return professors; }
    char getGrade() const { return grade; }

    void createRecord();
    void showRecord() const;
    void modifyRecord();
    int getRefNumber() const { return refNumber; }
    void deleteRecord();
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
    float getAverage() const;

    static void setGradeThresholds(const std::map<char, float>& thresholds) {
        gradeThresholds = thresholds;
    }

    static std::map<char, float> getGradeThresholds() {
        return gradeThresholds;
    }

    // Custom exception for invalid marks
    class InvalidMarkException : public std::runtime_error {
    public:
        InvalidMarkException() : std::runtime_error("Invalid mark value") {}
    };
};

std::map<char, float> GradeManager::gradeThresholds = {
    {'A', 90}, {'B', 80}, {'C', 70}, {'D', 60}, {'E', 50}, {'F', 0}
};

void GradeManager::calculateGrade() {
    float average = getAverage();

    if (average >= gradeThresholds['A']) grade = 'A';
    else if (average >= gradeThresholds['B']) grade = 'B';
    else if (average >= gradeThresholds['C']) grade = 'C';
    else if (average >= gradeThresholds['D']) grade = 'D';
    else if (average >= gradeThresholds['E']) grade = 'E';
    else grade = 'F';
}

void GradeManager::createRecord() {
    std::cout << "Enter Reference Number: ";
    while (!(std::cin >> refNumber) || refNumber <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive integer: ";
    }
    std::cin.ignore();

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);

    subjects.clear();
    professors.clear();
    marks.clear();

    for (int i = 0; i < 5; i++) {
        std::string subject, professor;
        float mark;

        std::cout << "Enter Subject " << i + 1 << ": ";
        while (std::getline(std::cin, subject) && subject.empty()) {
            std::cout << "Subject cannot be empty. Please enter a valid subject: ";
        }
        subjects.push_back(subject);

        std::cout << "Enter Professor Name: ";
        while (std::getline(std::cin, professor) && professor.empty()) {
            std::cout << "Professor name cannot be empty. Please enter a valid name: ";
        }
        professors.push_back(professor);

        bool validMark = false;
        do {
            try {
                std::cout << "Enter Marks (0-100): ";
                if (std::cin >> mark && validateMark(mark)) {
                    marks.push_back(mark);
                    validMark = true;
                } else {
                    throw InvalidMarkException();
                }
            } catch (const InvalidMarkException&) {
                std::cout << "Invalid mark. Please enter a value between 0 and 100.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!validMark);
        std::cin.ignore();
    }

    calculateGrade();
    std::cout << "Grade: " << grade << std::endl;
}

void GradeManager::showRecord() const {
    std::cout << "Reference Number: " << refNumber << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Marks:\n";
    for (int i = 0; i < marks.size(); i++) {
        std::cout << "Subject: " << subjects[i] << std::endl;
        std::cout << "Professor: " << professors[i] << std::endl;
        std::cout << "Marks: " << marks[i] << std::endl;
    }
    std::cout << "Grade: " << grade << std::endl;
}

void GradeManager::modifyRecord() {
    std::cout << "Modify Reference Number: ";
    while (!(std::cin >> refNumber) || refNumber <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive integer: ";
    }
    std::cin.ignore();

    std::cout << "Modify Name: ";
    std::getline(std::cin, name);

    subjects.clear();
    professors.clear();
    marks.clear();

    for (int i = 0; i < 5; i++) {
        std::string subject, professor;
        float mark;

        std::cout << "Modify Subject " << i + 1 << ": ";
        while (std::getline(std::cin, subject) && subject.empty()) {
            std::cout << "Subject cannot be empty. Please enter a valid subject: ";
        }
        subjects.push_back(subject);

        std::cout << "Modify Professor Name: ";
        while (std::getline(std::cin, professor) && professor.empty()) {
            std::cout << "Professor name cannot be empty. Please enter a valid name: ";
        }
        professors.push_back(professor);

        bool validMark = false;
        do {
            try {
                std::cout << "Modify Marks (0-100): ";
                if (std::cin >> mark && validateMark(mark)) {
                    marks.push_back(mark);
                    validMark = true;
                } else {
                    throw InvalidMarkException();
                }
            } catch (const InvalidMarkException&) {
                std::cout << "Invalid mark. Please enter a value between 0 and 100.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (!validMark);
        std::cin.ignore();
    }

    calculateGrade();
    std::cout << "Modified Grade: " << grade << std::endl;
}

void GradeManager::deleteRecord() {
    refNumber = 0;
    name.clear();
    subjects.clear();
    professors.clear();
    marks.clear();
    grade = ' ';
}

void GradeManager::saveToFile(std::ofstream& file) const {
    file << "Reference Number: " << refNumber << "\n";
    file << "Name: " << name << "\n";

    // Save the table headers
    file << std::left << std::setw(20) << "Subject" << std::setw(20) << "Professor" << std::setw(10) << "Marks" << std::setw(10) << "Grade" << "\n";
    for (int i = 0; i < subjects.size(); i++) {
        file << std::left << std::setw(20) << subjects[i] 
             << std::setw(20) << professors[i] 
             << std::setw(10) << marks[i] 
             << std::setw(10) << (marks[i] >= 50 ? "Pass" : "Fail") << "\n";
    }

    // Calculate and save total marks and grade
    float totalMarks = getAverage();
    file << "\nTotal Marks: " << totalMarks << "\n";
    file << "Grade: " << grade << "\n";
    file << "--------------------------------------------------\n";
}

void GradeManager::loadFromFile(std::ifstream& file) {
    file >> refNumber;
    file.ignore();
    std::getline(file, name);
    for (int i = 0; i < 5; i++) {
        std::string subject;
        std::getline(file, subject);
        subjects.push_back(subject);
        std::string professor;
        std::getline(file, professor);
        professors.push_back(professor);
        float mark;
        file >> mark;
        file.ignore();
        marks.push_back(mark);
    }
    file >> grade;
}

float GradeManager::getAverage() const {
    float average = 0;
    for (float mark : marks) {
        average += mark;
    }
    return average / marks.size();
}

class GradeSystem {
private:
    std::vector<std::unique_ptr<GradeManager>> records;
    std::string filename;

public:
    explicit GradeSystem(std::string fname) : filename(std::move(fname)) {}

    void addRecord() {
        auto record = std::make_unique<GradeManager>();
        record->createRecord();
        records.push_back(std::move(record));
        std::cout << "Record added successfully!" << std::endl;
    }

    void displayRecords() const {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
        } else {
            std::cout << "\n********** STUDENT GRADE RECORDS **********\n";
            for (const auto& record : records) {
                record->showRecord();
                std::cout << std::endl;
            }
        }
    }

    void modifyRecord() {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
            return;
        }

        int refNumber;
        std::cout << "Enter Reference Number of the record to modify: ";
        while (!(std::cin >> refNumber) || refNumber <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid positive integer: ";
        }

        auto it = std::find_if(records.begin(), records.end(), [refNumber](const std::unique_ptr<GradeManager>& record) {
            return record->getRefNumber() == refNumber;
        });

        if (it != records.end()) {
            (*it)->modifyRecord();
            std::cout << "Record modified successfully!" << std::endl;
        } else {
            std::cout << "No record found with the given Reference Number." << std::endl;
        }
    }

    void deleteRecord() {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
            return;
        }

        int refNumber;
        std::cout << "Enter Reference Number of the record to delete: ";
        while (!(std::cin >> refNumber) || refNumber <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid positive integer: ";
        }

        auto it = std::find_if(records.begin(), records.end(), [refNumber](const std::unique_ptr<GradeManager>& record) {
            return record->getRefNumber() == refNumber;
        });

        if (it != records.end()) {
            records.erase(it);
            std::cout << "Record deleted successfully!" << std::endl;
        } else {
            std::cout << "No record found with the given Reference Number." << std::endl;
        }
    }

    void calculateAverages() const {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
            return;
        }

        std::vector<float> subjectTotals(5, 0);
        std::vector<int> subjectCounts(5, 0);

        for (const auto& record : records) {
            auto marks = record->getMarks();
            for (int i = 0; i < marks.size(); i++) {
                subjectTotals[i] += marks[i];
                subjectCounts[i]++;
            }
        }

        std::cout << "Average Grade for each Subject:\n";
        for (int i = 0; i < 5; i++) {
            float average = subjectTotals[i] / subjectCounts[i];
            std::cout << "Subject " << i + 1 << ": " << average << std::endl;
        }
    }

    void calculatePassPercentage() const {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
            return;
        }

        int passCount = std::count_if(records.begin(), records.end(), [](const std::unique_ptr<GradeManager>& record) {
            return record->getAverage() >= 50;
        });

        float passPercentage = (static_cast<float>(passCount) / records.size()) * 100;
        std::cout << "Pass Percentage: " << passPercentage << "%" << std::endl;
    }

    void generateReport() const {
        if (records.empty()) {
            std::cout << "No records found." << std::endl;
            return;
        }

        int refNumber;
        std::cout << "Enter Reference Number of the student: ";
        while (!(std::cin >> refNumber) || refNumber <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid positive integer: ";
        }

        auto it = std::find_if(records.begin(), records.end(), [refNumber](const std::unique_ptr<GradeManager>& record) {
            return record->getRefNumber() == refNumber;
        });

        if (it != records.end()) {
            std::cout << "\nPerformance Report for Student (Reference Number: " << refNumber << ")\n";
            (*it)->showRecord();
        } else {
            std::cout << "No record found with the given Reference Number." << std::endl;
        }
    }

    void saveToFile() const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& record : records) {
                record->saveToFile(file);
            }

            // Save additional statistics
            file << "\nAdditional Statistics:\n";
            file << "--------------------------------------------------\n";

            // Class Averages
            std::vector<float> subjectTotals(5, 0);
            std::vector<int> subjectCounts(5, 0);
            for (const auto& record : records) {
                auto marks = record->getMarks();
                for (int i = 0; i < marks.size(); i++) {
                    subjectTotals[i] += marks[i];
                    subjectCounts[i]++;
                }
            }
            file << "Class Averages:\n";
            for (int i = 0; i < 5; i++) {
                float average = subjectTotals[i] / subjectCounts[i];
                file << "Subject " << i + 1 << ": " << average << "\n";
            }

            // Highest and Lowest Marks
            for (int i = 0; i < 5; i++) {
                float highest = 0, lowest = 100;
                for (const auto& record : records) {
                    auto marks = record->getMarks();
                    if (marks[i] > highest) highest = marks[i];
                    if (marks[i] < lowest) lowest = marks[i];
                }
                file << "Subject " << i + 1 << " - Highest: " << highest << ", Lowest: " << lowest << "\n";
            }

            file.close();
            std::cout << "Records saved to file successfully!\n";
        } else {
            std::cerr << "Unable to open file for saving records.\n";
        }
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            records.clear();
            while (!file.eof()) {
                auto record = std::make_unique<GradeManager>();
                record->loadFromFile(file);
                records.push_back(std::move(record));
            }
            file.close();
            std::cout << "Records loaded from file successfully!" << std::endl;
        } else {
            std::cerr << "Unable to open file for loading records." << std::endl;
        }
    }

    void editGradeThresholds() {
        std::map<char, float> thresholds = GradeManager::getGradeThresholds();
        std::cout << "Current Grade Thresholds:\n";
        for (const auto& threshold : thresholds) {
            std::cout << threshold.first << ": " << threshold.second << "\n";
        }

        std::cout << "Enter new thresholds (A-F):\n";
        for (auto& threshold : thresholds) {
            std::cout << threshold.first << ": ";
            float newThreshold;
            while (!(std::cin >> newThreshold) || newThreshold < 0 || newThreshold > 100) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a value between 0 and 100: ";
            }
            threshold.second = newThreshold;
        }

        GradeManager::setGradeThresholds(thresholds);
        std::cout << "Grade thresholds updated successfully!\n";
    }
};

int main() {
    GradeSystem system("grades.txt");

    int choice;
    do {
        std::cout << "\nGrade Management System\n";
        std::cout << "1. Add Record\n";
        std::cout << "2. Display Records\n";
        std::cout << "3. Modify Record\n";
        std::cout << "4. Delete Record\n";
        std::cout << "5. Calculate Averages\n";
        std::cout << "6. Calculate Pass Percentage\n";
        std::cout << "7. Generate Report\n";
        std::cout << "8. Save to File\n";
        std::cout << "9. Load from File\n";
        std::cout << "10. Edit Grade Thresholds\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: system.addRecord(); break;
            case 2: system.displayRecords(); break;
            case 3: system.modifyRecord(); break;
            case 4: system.deleteRecord(); break;
            case 5: system.calculateAverages(); break;
            case 6: system.calculatePassPercentage(); break;
            case 7: system.generateReport(); break;
            case 8: system.saveToFile(); break;
            case 9: system.loadFromFile(); break;
            case 10: system.editGradeThresholds(); break;
            case 0: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice, try again!\n"; break;
        }
    } while (choice != 0);

    return 0;
}