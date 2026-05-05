#include "../include/FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <ctime>

const std::string FileHandler::FILENAME = "data/students.txt";

bool FileHandler::saveStudent(const Student& student) {
    std::ofstream file(FILENAME, std::ios::app);
    if (!file.is_open()) return false;
    
    file << student.toString() << std::endl;
    file.close();
    return true;
}

std::vector<Student> FileHandler::loadAllStudents() {
    std::vector<Student> students;
    std::ifstream file(FILENAME);
    
    if (!file.is_open()) return students;
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromString(line));
        }
    }
    
    file.close();
    return students;
}

bool FileHandler::updateStudent(const Student& updatedStudent) {
    std::vector<Student> students = loadAllStudents();
    bool found = false;
    
    for (auto& student : students) {
        if (student.getRollNo() == updatedStudent.getRollNo()) {
            student = updatedStudent;
            found = true;
            break;
        }
    }
    
    if (!found) return false;
    
    std::ofstream file(FILENAME);
    if (!file.is_open()) return false;
    
    for (const auto& student : students) {
        file << student.toString() << std::endl;
    }
    
    file.close();
    return true;
}

bool FileHandler::deleteStudent(int rollNo) {
    std::vector<Student> students = loadAllStudents();
    bool found = false;
    
    auto it = students.begin();
    while (it != students.end()) {
        if (it->getRollNo() == rollNo) {
            it = students.erase(it);
            found = true;
        } else {
            ++it;
        }
    }
    
    if (!found) return false;
    
    std::ofstream file(FILENAME);
    if (!file.is_open()) return false;
    
    for (const auto& student : students) {
        file << student.toString() << std::endl;
    }
    
    file.close();
    return true;
}

bool FileHandler::studentExists(int rollNo) {
    std::vector<Student> students = loadAllStudents();
    for (const auto& student : students) {
        if (student.getRollNo() == rollNo) return true;
    }
    return false;
}

int FileHandler::getNextRollNo() {
    std::vector<Student> students = loadAllStudents();
    int maxRoll = 0;
    for (const auto& student : students) {
        if (student.getRollNo() > maxRoll) {
            maxRoll = student.getRollNo();
        }
    }
    return maxRoll + 1;
}

void FileHandler::backupData() {
    std::ifstream src(FILENAME, std::ios::binary);
    if (!src.is_open()) return;
    
    auto now = std::time(nullptr);
    auto timestamp = std::to_string(now);
    std::string backupFile = "data/backup_" + timestamp + ".txt";
    
    std::ofstream dst(backupFile, std::ios::binary);
    dst << src.rdbuf();
    
    src.close();
    dst.close();
}
