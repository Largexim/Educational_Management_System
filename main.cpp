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
Teacher *Load();
Teacher *AddTeacher(Teacher *);
void AddStudent(Teacher *);
int main() {
    Teacher *Teachers = NULL;
    Teachers = Load();
    Teachers = AddTeacher(Teachers);
    cout<<"teacher added.";
    AddStudent(Teachers);
}

Teacher *Load(){
    Teacher *Head=NULL;
    Teacher *curr;
    bool check=true;

    ifstream Teachers("/Users/largexim/Documents/Golestan/Teachers");

    curr = new struct Teacher;
    Teachers >> curr->UserName;
    Teachers >> curr->Password;
    Teachers >> curr->LessonName;
    curr->student = NULL;
    curr->Next=Head;
    Head = curr;

}

Teacher *AddTeacher(Teacher * Head){
    Teacher *curr;
    curr = new struct Teacher;
    cout<<"Enter Teacher's UserName : ";
    cin>>curr->UserName;
    cout<<"Enter Teacher's Password : ";
    cin>>curr->Password;
    cout<<"Enter Teacher's DarsName : ";
    cin>>curr->LessonName;
    curr->student = NULL;
    curr->Next = Head;
    Head = curr;

    curr = Head;
    ofstream Teachers("/Users/largexim/Documents/Golestan/Teachers");
    while(curr!=NULL){
        Teachers << curr->UserName << " " << curr->Password << " " << curr->LessonName<<endl;
        curr = curr->Next;
    }

    return Head;
}

void AddStudent(Teacher *Head){
    bool check = false;
    Teacher *curr = Head;
    string TeacherName;
    cout<<"Enter name : ";
    cin>>TeacherName;
    while(curr!=NULL){
        if(TeacherName == curr->UserName){
            check = true;
            break;
        }
        curr = curr->Next;
    }
    if (check == true){
        Students *New;
        New = new struct Students;
        cout << "Enter student's Name : ";
        cin >> New->UserName;
        New->Next = curr->student;
        curr->student = New;
    }
    else {
        cout<<"TeacherName Does Not Exist!!";
    }
}



