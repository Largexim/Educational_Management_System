#include <iostream>
#include <fstream>
using namespace std;
struct Students{
    string UserName;
    string Password;
    float Mark;
    Students *Next;
};
struct Teacher{
    string UserName;
    string Password;
    string LessonName;
    Students *student;
    Teacher *Next;
};
int main() {

}
