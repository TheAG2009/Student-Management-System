#include "../include/Student.h"
#include "../include/FileHandler.h"
#include "../include/Validator.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

class StudentManagementSystem {
private:
    std::vector<Student> students;
    
    void clearScreen() {
        std::system(CLEAR);
    }
    
    void loadingAnimation(const std::string& message, int duration) {
        std::cout << message;
        for (int i = 0; i < 3; i++) {
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        }
        std::cout << std::endl;
    }
    
    void printHeader(const std::string& title) {
        std::cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                         " << title << "║\n";
        std::cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    }
    
    void printSuccess(const std::string& message) {
        std::cout << "\n✅ " << message << " ✅\n";
    }
    
    void printError(const std::string& message) {
        std::cout << "\n❌ " << message << " ❌\n";
    }
    
    void printInfo(const std::string& message) {
        std::cout << "\nℹ️  " << message << "\n";
    }
    
    void displayMenu() {
        std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
        std::cout << "│                    📚 STUDENT MANAGEMENT SYSTEM 📚              │\n";
        std::cout << "├─────────────────────────────────────────────────────────────────┤\n";
        std::cout << "│                                                                 │\n";
        std::cout << "│  1. ➕ Add New Student                                          │\n";
        std::cout << "│  2. 📝 Update Student Information                               │\n";
        std::cout << "│  3. ❌ Delete Student                                           │\n";
        std::cout << "│  4. 🔍 Search Student                                           │\n";
        std::cout << "│  5. 📊 Display All Students                                     │\n";
        std::cout << "│  6. 💾 Backup Data                                              │\n";
        std::cout << "│  7. 🚪 Exit                                                     │\n";
        std::cout << "│                                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    }
    
    void addStudent() {
        clearScreen();
        printHeader("ADD NEW STUDENT");
        
        Student newStudent;
        
        int rollNo = FileHandler::getNextRollNo();
        newStudent.setRollNo(rollNo);
        printInfo("Auto-generated Roll Number: " + std::to_string(rollNo));
        
        std::string name = Validator::getValidatedString("Enter Student Name: ");
        while (!Validator::validateName(name)) {
            std::cout << "❌ Name must contain only letters and spaces!\n";
            name = Validator::getValidatedString("Enter Student Name: ");
        }
        newStudent.setName(name);
        
        std::string className = Validator::getValidatedString("Enter Class (e.g., 10th Grade): ");
        newStudent.setClassName(className);
        
        float marks = Validator::getValidatedFloat("Enter Marks (0-100): ", 0, 100);
        newStudent.setMarks(marks);
        
        std::string email = Validator::getValidatedEmail("Enter Email: ");
        newStudent.setEmail(email);
        
        std::string phone = Validator::getValidatedPhone("Enter Phone Number: ");
        newStudent.setPhone(phone);
        
        loadingAnimation("Saving student record", 300);
        
        if (FileHandler::saveStudent(newStudent)) {
            printSuccess("Student added successfully!");
            std::cout << "\n📋 Student Details:\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            newStudent.display();
        } else {
            printError("Failed to add student!");
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void displayAllStudents() {
        clearScreen();
        printHeader("STUDENT RECORDS");
        
        students = FileHandler::loadAllStudents();
        
        if (students.empty()) {
            printInfo("No students found in the database!");
        } else {
            std::cout << "\n📊 Total Students: " << students.size() << "\n\n";
            std::cout << std::left 
                      << std::setw(10) << "Roll No"
                      << std::setw(25) << "Name"
                      << std::setw(15) << "Class"
                      << std::setw(10) << "Marks"
                      << std::setw(10) << "Grade"
                      << std::setw(25) << "Email"
                      << std::setw(15) << "Phone"
                      << std::endl;
            std::cout << std::string(110, '─') << std::endl;
            
            for (const auto& student : students) {
                student.display();
            }
            std::cout << std::string(110, '─') << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void updateStudent() {
        clearScreen();
        printHeader("UPDATE STUDENT INFORMATION");
        
        int rollNo = Validator::getValidatedInt("Enter Roll Number to update: ", 1, 999999);
        
        students = FileHandler::loadAllStudents();
        bool found = false;
        
        for (auto& student : students) {
            if (student.getRollNo() == rollNo) {
                found = true;
                std::cout << "\n📋 Current Details:\n";
                std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                student.display();
                std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
                
                std::string name = Validator::getValidatedString("Enter New Name: ");
                while (!Validator::validateName(name)) {
                    std::cout << "❌ Name must contain only letters and spaces!\n";
                    name = Validator::getValidatedString("Enter New Name: ");
                }
                student.setName(name);
                
                std::string className = Validator::getValidatedString("Enter New Class: ");
                student.setClassName(className);
                
                float marks = Validator::getValidatedFloat("Enter New Marks (0-100): ", 0, 100);
                student.setMarks(marks);
                
                std::string email = Validator::getValidatedEmail("Enter New Email: ");
                student.setEmail(email);
                
                std::string phone = Validator::getValidatedPhone("Enter New Phone: ");
                student.setPhone(phone);
                
                loadingAnimation("Updating student record", 300);
                
                if (FileHandler::updateStudent(student)) {
                    printSuccess("Student information updated successfully!");
                } else {
                    printError("Failed to update student!");
                }
                break;
            }
        }
        
        if (!found) {
            printError("Student with Roll Number " + std::to_string(rollNo) + " not found!");
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void deleteStudent() {
        clearScreen();
        printHeader("DELETE STUDENT");
        
        int rollNo = Validator::getValidatedInt("Enter Roll Number to delete: ", 1, 999999);
        
        students = FileHandler::loadAllStudents();
        bool found = false;
        Student toDelete;
        
        for (const auto& student : students) {
            if (student.getRollNo() == rollNo) {
                found = true;
                toDelete = student;
                break;
            }
        }
        
        if (!found) {
            printError("Student with Roll Number " + std::to_string(rollNo) + " not found!");
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }
        
        std::cout << "\n📋 Student to delete:\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        toDelete.display();
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        
        char confirm;
        std::cout << "\n⚠️  Are you sure you want to delete this student? (Y/N): ";
        std::cin >> confirm;
        std::cin.ignore();
        
        if (tolower(confirm) == 'y') {
            loadingAnimation("Deleting student record", 300);
            
            if (FileHandler::deleteStudent(rollNo)) {
                printSuccess("Student deleted successfully!");
            } else {
                printError("Failed to delete student!");
            }
        } else {
            printInfo("Deletion cancelled!");
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void searchStudent() {
        clearScreen();
        printHeader("SEARCH STUDENT");
        
        int rollNo = Validator::getValidatedInt("Enter Roll Number to search: ", 1, 999999);
        
        students = FileHandler::loadAllStudents();
        bool found = false;
        
        for (const auto& student : students) {
            if (student.getRollNo() == rollNo) {
                found = true;
                std::cout << "\n✅ Student Found!\n";
                std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                std::cout << std::left 
                          << std::setw(15) << "Roll Number:" << student.getRollNo() << "\n"
                          << std::setw(15) << "Name:" << student.getName() << "\n"
                          << std::setw(15) << "Class:" << student.getClassName() << "\n"
                          << std::setw(15) << "Marks:" << student.getMarks() << "\n"
                          << std::setw(15) << "Grade:" << student.getGrade() << "\n"
                          << std::setw(15) << "Email:" << student.getEmail() << "\n"
                          << std::setw(15) << "Phone:" << student.getPhone() << "\n";
                std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
                break;
            }
        }
        
        if (!found) {
            printError("Student with Roll Number " + std::to_string(rollNo) + " not found!");
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void backupData() {
        clearScreen();
        printHeader("BACKUP DATA");
        
        loadingAnimation("Creating backup", 300);
        FileHandler::backupData();
        printSuccess("Data backup completed successfully!");
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
public:
    void run() {
        while (true) {
            clearScreen();
            displayMenu();
            
            int choice = Validator::getValidatedInt("\n🔹 Enter your choice (1-7): ", 1, 7);
            
            switch (choice) {
                case 1: addStudent(); break;
                case 2: updateStudent(); break;
                case 3: deleteStudent(); break;
                case 4: searchStudent(); break;
                case 5: displayAllStudents(); break;
                case 6: backupData(); break;
                case 7:
                    clearScreen();
                    std::cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗\n";
                    std::cout << "║                    👋 THANK YOU FOR USING OUR SYSTEM! 👋                      ║\n";
                    std::cout << "║                           Have a great day!                                  ║\n";
                    std::cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
                    exit(0);
            }
        }
    }
};

int main() {
    // Create data directory if it doesn't exist
    std::system("mkdir -p data 2>/dev/null || mkdir data 2>nul");
    
    StudentManagementSystem sms;
    sms.run();
    
    return 0;
}
