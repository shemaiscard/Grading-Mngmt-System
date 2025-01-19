Grade Management System - C++
=============================

License
-------
The Grade Management System is a C++ application designed to manage student grades efficiently. 
It allows users to add, modify, delete, and view student records, calculate averages, generate reports, and save/load data to/from a file. The system also supports customizable grade thresholds and provides additional statistics like class averages, highest/lowest marks, and pass percentages.

Features
--------
- **Add Records**: Add new student records with details like reference number, name, subjects, professors, and marks.
- **Modify Records**: Edit existing student records by reference number.
- **Delete Records**: Remove student records by reference number.
- **Display Records**: View all student records in a readable format.
- **Calculate Averages**: Calculate and display the average marks for each subject across all students.
- **Calculate Pass Percentage**: Determine the percentage of students who passed (marks >= 50).
- **Generate Reports**: Generate a detailed performance report for a specific student.
- **Save to File**: Save all records to a file in a table format with additional statistics.
- **Load from File**: Load records from a file to continue working with existing data.
- **Customizable Grade Thresholds**: Edit the grade thresholds (A, B, C, etc.) based on institutional policies.
- **Input Validation**: Ensures all inputs (subjects, professors, marks, etc.) are valid to prevent errors.

How to Use
-----------

**Prerequisites**:
- A C++ compiler (e.g., GCC, Clang, or MSVC).
- A terminal or command prompt to run the program.

**Steps to Run the Program**:
1. Clone the repository or download the source code.
```bash
git clone https://github.com/shemaiscard/Grading-Mngmt-System.git
cd grade-management-system
```

2. Compile the program using a C++ compiler.
```bash
g++ GRADER.cpp -o GradeSystem
```

3. Run the compiled program.
```bash
./GradeSystem
```

4. Follow the on-screen menu to perform operations like adding, modifying, deleting, or viewing records.

File Structure
--------------
- `GRADER.cpp`: The main source code file containing the implementation of the Grade Management System.
- `grades.txt`: The default file where records are saved and loaded from (created automatically if it doesn't exist).

Example Usage
-------------
**Main Menu**:
```
Grade Management System
1. Add Record
2. Display Records
3. Modify Record
4. Delete Record
5. Calculate Averages
6. Calculate Pass Percentage
7. Generate Report
8. Save to File
9. Load from File
10. Edit Grade Thresholds
0. Exit
Enter choice:
```

**Adding a Record**:
- Select option 1 to add a new record.
- Enter the student's reference number, name, subjects, professors, and marks.
- The system will calculate the grade based on the entered marks.

**Modifying a Record**:
- Select option 3 to modify an existing record.
- Enter the reference number of the student you want to edit.
- Update the student's details as needed.

**Saving and Loading Records**:
- Use option 8 to save all records to a file.
- Use option 9 to load records from a file.

**Customizing Grade Thresholds**:
- Select option 10 to edit grade thresholds.
- Enter new thresholds for grades A, B, C, D, E, and F.
- The system will use these thresholds to calculate grades for students.

Contributing
------------
Contributions are welcome! If you'd like to contribute to this project, please follow these steps:
1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Make your changes and commit them with clear messages.
4. Submit a pull request.

License
-------
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
---------------
This project was developed as a demonstration of C++ Object-Oriented programming concepts.
Special thanks to the C++ community for providing valuable resources and inspiration.

Contact
-------
For questions or feedback, feel free to reach out:
- GitHub: shemaiscard

Enjoy using the Grade Management System! 🚀
