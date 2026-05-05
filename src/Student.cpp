#include "../include/Student.h"
#include <sstream>

Student::Student() : rollNo(0), marks(0.0) {}

Student::Student(int roll, std::string name, std::string className, float marks, std::string email, std::string phone) 
    : rollNo(roll), name(name), className(className), marks(marks), email(email), phone(phone) {}

int Student::getRollNo() const { return rollNo; }
std::string Student::getName() const { return name; }
std::string Student::getClassName() const { return className; }
float Student::getMarks() const { return marks; }
std::string Student::getEmail() const { return email; }
std::string Student::getPhone() const { return phone; }

void Student::setRollNo(int roll) { rollNo = roll; }
void Student::setName(std::string n) { name = n; }
void Student::setClassName(std::string c) { className = c; }
void Student::setMarks(float m) { marks = m; }
void Student::setEmail(std::string e) { email = e; }
void Student::setPhone(std::string p) { phone = p; }

char Student::getGrade() const {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else if (marks >= 50) return 'E';
    else return 'F';
}

void Student::display() const {
    std::cout << std::left 
              << std::setw(10) << rollNo
              << std::setw(25) << name
              << std::setw(15) << className
              << std::setw(10) << marks
              << std::setw(10) << getGrade()
              << std::setw(25) << email
              << std::setw(15) << phone
              << std::endl;
}

std::string Student::toString() const {
    std::stringstream ss;
    ss << rollNo << "|" << name << "|" << className << "|" << marks << "|" << email << "|" << phone;
    return ss.str();
}

Student Student::fromString(const std::string& data) {
    std::stringstream ss(data);
    Student s;
    std::string token;
    
    std::getline(ss, token, '|'); s.rollNo = std::stoi(token);
    std::getline(ss, s.name, '|');
    std::getline(ss, s.className, '|');
    std::getline(ss, token, '|'); s.marks = std::stof(token);
    std::getline(ss, s.email, '|');
    std::getline(ss, s.phone, '|');
    
    return s;
}
