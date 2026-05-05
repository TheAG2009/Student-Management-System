#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include "Student.h"

class FileHandler {
private:
    static const std::string FILENAME;
    
public:
    static bool saveStudent(const Student& student);
    static std::vector<Student> loadAllStudents();
    static bool updateStudent(const Student& student);
    static bool deleteStudent(int rollNo);
    static bool studentExists(int rollNo);
    static int getNextRollNo();
    static void backupData();
};

#endif
