#include <iostream>
#include <fstream>
using namespace std;
struct Lessons{
    string Lesson_Name;
    int Lesson_ID{};
    Lessons *Next{};
    string Mark;
};
struct Users{
    int ID{};
    string First_Name;
    string Last_Name;
    string User_ID;
    string Password;
    Users *Next{};
};
struct Teachers{
    string First_Name;
    string Last_Name;
    string Teacher_ID;
    Teachers *Next{};
};
struct Students{
    string First_Name;
    string Last_Name;
    string Student_ID;
    string Mark;
    Students *Next{};
};
struct Lesson{
    string T_First_Name;
    string T_Last_Name;
    string Teacher_ID;
    Students *S{};
};
struct TL{
    string Teacher_ID;
    Lessons *Lessons{};
    TL *Next{};
};
string U_ID;
int entry();
void ADMIN();
void STUDENT();
void TEACHER();
void add_new_user();
void delete_user();
void change_password();
void change_student_password();
void add_new_lesson();
void choose_new_lesson();
void add_new_teacher();
void add_new_student();
void set_mark();
void add_lesson_to_teacher(string);
void add_to_tl(string , string);
bool ID_check(string);
Lessons * show_lessons();
int main(){
    int ID=-1;
    for(int i=0 ;ID==-1;i++) {
        ID = entry();
        if(i==2){
            cout<<"you are baned!!";
            break;
        }
    }
    switch (ID) {
        case 0 : ADMIN();break;
        case 1 : TEACHER();break;
        case 2 : STUDENT();break;
        default : ;
    }
}

int entry(){
    int x = -1;
    bool check = true;
    string username;
    string password;

    //LOADING USERS
    Users *Head;
    Users *curr;
    ifstream users("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!users.eof()){
        curr = new struct Users;
        users>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    //CHECKING USER_ID AND PASSWORD
    curr = Head;
    cout << "Enter your USER_ID : ";
    cin >> username;
    while(curr != nullptr){
        if(username==curr->User_ID){
            for(int i=0 ; check ; i++){
                cout<<"Enter your Password : ";
                cin>>password;
                if(password == curr->Password){
                    check = false;
                    x = curr->ID;
                    U_ID=curr->User_ID;
                }
                else if(i==2){
                    int j = 1;
                    cout<<"Forgot your password?\n1.Try again\t2.Change USER_ID\n";
                    cin >> j;
                    if(j==1)
                        continue;
                    else if(j==2) {
                        x = -1;
                        break;
                    }
                }
                else if(i==5){
                    cout<<"you are banned!!";
                    x = -2;
                    break;
                }
                else {
                    cout<<"Password is not true Try again!!\n";
                }
            }
            break;
        }
        curr = curr->Next;
    }
    if (x==-1){
        cout<<"USER_ID is not true Try again!\n";
    }

    //DELETING HIP MEMORY
    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;
    return x;
}

void ADMIN(){
    int menu=0;
    while(menu==0){
        cout<<"1)Add new user.\t2)Delete User.\n3)Change User Password.\t4)Add new Lesson.\n5)Add new Teacher.\t";
        cout<<"6)Add new Student.\n7)Exit.";
        cin>>menu;
        switch (menu) {
            case 1 : add_new_user();menu=0;break;
            case 2 : delete_user();menu=0;break;
            case 3 : change_password();menu=0;break;
            case 4 : add_new_lesson();menu=0;break;
            case 5 : add_new_teacher();menu=0;break;
            case 6 : add_new_student();menu=0;break;
            case 7 : menu = -1;
            default : ;
        }
    }
}

void STUDENT(){
    int menu=0;
    while(menu==0){
        cout<<"1)Choose new Lesson.\n2)See Marks.\n3)Change Password.\n4)Exit.\n";
        cin>>menu;
        switch (menu) {
            case 1 : choose_new_lesson();menu=0;break;
            //case 2 : delete_user();menu=0;break;
            case 3 : change_student_password();menu=0;break;
            case 4 : menu = -1;
            default : ;
        }
    }
}

void TEACHER(){
    int menu=0;
    while(menu==0){
        cout<<"1)Choose new Lesson.\n2)Exit.\n";
        cin>>menu;
        switch (menu) {
            case 1 : set_mark();menu=0;break;
            case 2 : menu = -1;
            default : ;
        }
    }
}

void add_new_user(){
    Users *Head = nullptr;
    Users *curr;
    ifstream Iusers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!Iusers.eof()){
        curr = new struct Users;
        Iusers>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    Iusers.close();
    int id=-1;
    string test;
    curr = new struct Users;
    while(id>2 || id<0) {
        cout << "enter User's ID _ 0 for Admin _ 1 for Teacher _ 2 for Student : ";
        cin >> id;
        if (-1 < id && id < 3) {
            curr->ID = id;
        } else {
            cout << "NOT valid Try again!\n";
        }
    }
    cout<<"Enter User's Firstname : ";
    cin>>curr->First_Name;
    cout<<"Enter User's Lastname : ";
    cin>>curr->Last_Name;
    while(true) {
        int i=0;
        cout << "Enter User's USER_ID : ";
        cin >> test;
        while(test[i]){
            i++;
        }
        if(i<10||i>10){
            cout<<"USER_ID most have 10 character, Try again!\n";
        }
        else if(i==10){
            bool x = true;
            Users * temp = Head;
            while(temp != nullptr){
                if(test == temp->User_ID) {
                    cout <<"This USER_ID exist Try another one.\n";
                    x = false;
                    break;
                }
                temp = temp->Next;
            }
            if(x) {
                curr->User_ID = test;
                break;
            }
        }
    }
        cout << "Enter User's Password : ";
        cin >> curr->Password;
        curr->Next = Head;
        Head = curr;

    ofstream Ousers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(curr!= nullptr){
        Ousers<<curr->ID<<" "<<curr->First_Name<<" "<<curr->Last_Name<<" "<<curr->User_ID<<" "<<curr->Password;
        curr = curr->Next;
        if(curr!= nullptr)
            Ousers<<endl;
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;
    cout<<"Done.\n";
}

void delete_user(){
    string test;
    Users *Head = nullptr;
    Users *curr;
    ifstream users("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!users.eof()){
        curr = new struct Users;
        users>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    users.close();
    bool i = false;
    while(!i) {
        cout << "Enter User's USER_ID : ";
        cin >> test;
        curr = Head;
        while (curr != nullptr) {
            if (test == curr->User_ID) {
                i = true;
                break;
                }
                curr = curr->Next;
            }
        if(!i){
            cout<<"USER_ID does not exist try again.\n";
        }
    }

    while(true){
        cout<<"USER_ID : "<<curr->User_ID<<endl<<"First name : "<<curr->First_Name<<endl;
        cout<<"Last name : "<<curr->Last_Name<<endl;
        cout<<"Delete this user :\n1.Yes\n2.No\n";
        int x = 2;
        cin>>x;
        if(x==2){
            cout<<"OK.\n";
            break;
        }
        else if(x==1){
            Users * temp = curr;
            Users *pre = Head;
            while(pre->Next!=temp) {
                pre = pre->Next;
            }
            pre->Next = temp->Next;
            delete temp;
            cout<<"Done. USER_ID : "<<test<<" Deleted.\n";
            break;
        }
    }

    curr = Head;
    ofstream Ousers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(curr!= nullptr){
        Ousers<<curr->ID<<" "<<curr->First_Name<<" "<<curr->Last_Name<<" "<<curr->User_ID<<" "<<curr->Password;
        curr = curr->Next;
        if(curr!= nullptr)
            Ousers<<endl;
    }
    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;
}

void change_password(){
    string test;
    Users *Head = nullptr;
    Users *curr;
    ifstream users("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!users.eof()){
        curr = new struct Users;
        users>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    users.close();
    bool i = false;
    while(!i) {
        cout << "Enter User's USER_ID : ";
        cin >> test;
        curr = Head;
        while (curr != nullptr) {
            if (test == curr->User_ID) {
                i = true;
                break;
            }
            curr = curr->Next;
        }
        if(!i){
            cout<<"USER_ID does not exist try again.\n";
        }
    }
    bool z = true;
    while(z){
        cout<<"USER_ID : "<<curr->User_ID<<endl<<"First name : "<<curr->First_Name<<endl;
        cout<<"Last name : "<<curr->Last_Name<<endl;
        cout<<"Change the Password :\n1.Yes\n2.No\n";
        int x = 2;
        cin>>x;
        if(x==2){
            cout<<"OK.\n";
            break;
        }
        else if(x==1){
            while(z) {
                string password1;
                string password2;
                cout << "Enter the new Password : ";
                cin >> password1;
                cout << "Repeat the new Password : ";
                cin >> password2;
                if (password1 != password2) {
                    cout << "Passwords does not Mached!! try again.\n";
                }
                else{
                    if(password1==curr->Password){
                        cout<<"This password is the same as the current one, try another one.\n";
                    }
                    else {
                        curr->Password = password1;
                        cout << "Done.\n";
                        z = false;
                    }
                }
            }
        }
    }

    curr = Head;
    ofstream Ousers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(curr!= nullptr){
        Ousers<<curr->ID<<" "<<curr->First_Name<<" "<<curr->Last_Name<<" "<<curr->User_ID<<" "<<curr->Password;
        curr = curr->Next;
        if(curr!= nullptr)
            Ousers<<endl;
    }
    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;
}

void add_new_lesson(){
    Lessons *Head = nullptr;
    Lessons *curr;

    ifstream lesson("/Users/largexim/Documents/Golestan/files/lessons.txt");
    while(!lesson.eof()){
        curr = new struct Lessons;
        lesson>>curr->Lesson_Name>>curr->Lesson_ID;
        curr->Next = Head;
        Head = curr;
    }
    lesson.close();

    Lessons *ID_creator = Head;
    while(ID_creator->Next!= nullptr) {
        ID_creator = ID_creator->Next;
    }
    curr = new struct Lessons;
    cout<<"Enter Lesson Name : ";
    cin>>curr->Lesson_Name;
        curr->Lesson_ID = (ID_creator->Lesson_ID) + 1;
        curr->Next = Head;
        Head = curr;

    cout<<"Done. Lesson Added.\n";
    cout<<"Lesson Name : "<<curr->Lesson_Name<<"\nLesson ID : "<<curr->Lesson_ID<<endl;

    add_lesson_to_teacher(curr->Lesson_Name);

    curr = Head;
    ofstream olesson("/Users/largexim/Documents/Golestan/files/lessons.txt");
    while(curr!= nullptr){
        olesson<<curr->Lesson_Name<<" "<<curr->Lesson_ID;
        curr = curr->Next;
        if(curr!= nullptr)
            olesson<<endl;
    }
    olesson.close();

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
}

void add_new_teacher(){
    Teachers *THead = nullptr;
    Teachers *Tcurr;
    string test;

    Users *Head = nullptr;
    Users *curr;
    ifstream Iusers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!Iusers.eof()){
        curr = new struct Users;
        Iusers>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    Iusers.close();

    ifstream Teachers("/Users/largexim/Documents/Golestan/files/Teachers.txt");
    while(!Teachers.eof()){
        Tcurr = new struct Teachers;
        Teachers>>Tcurr->First_Name>>Tcurr->Last_Name>>Tcurr->Teacher_ID;
        Tcurr->Next = THead;
        THead = Tcurr;
    }
    Teachers.close();

    bool x = false;
    cout<<"Enter Teacher's ID : ";
    cin>>test;
    while(!x) {
        while (curr != nullptr) {
            if (curr->User_ID == test) {
                Tcurr = new struct Teachers;
                Tcurr->First_Name = curr->First_Name;
                Tcurr->Last_Name = curr->Last_Name;
                Tcurr->Teacher_ID = curr->User_ID;
                Tcurr->Next = THead;
                THead = Tcurr;
                x = true;
                break;
            } else {
                curr = curr->Next;
            }
        }
        if (!x) {
            cout << "ID not found!!\n";
        }
    }
    if(x){
        cout<<"Done.\n";
    }
    ofstream oTeachers("/Users/largexim/Documents/Golestan/files/Teachers.txt");
    Tcurr = THead;
    while(Tcurr!= nullptr){
        oTeachers<<Tcurr->First_Name<<" "<<Tcurr->Last_Name<<" "<<Tcurr->Teacher_ID;
        Tcurr = Tcurr->Next;
        if(Tcurr!= nullptr) {
            oTeachers << endl;
        }
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }

    while(THead!= nullptr){
        Tcurr = THead->Next;
        delete THead;
        THead = Tcurr;
    }
}

void add_new_student(){
    Students *SHead = nullptr;
    Students *Scurr;
    string test;

    Users *Head = nullptr;
    Users *curr;
    ifstream users("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!users.eof()){
        curr = new struct Users;
        users>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    users.close();

    ifstream Teachers("/Users/largexim/Documents/Golestan/files/Students.txt");
    while(!Teachers.eof()){
        Scurr = new struct Students;
        Teachers>>Scurr->First_Name>>Scurr->Last_Name>>Scurr->Student_ID;
        Scurr->Next = SHead;
        SHead = Scurr;
    }
    Teachers.close();

    bool x = false;
    cout<<"Enter Student's ID : ";
    cin>>test;
    while(!x) {
        while (curr != nullptr) {
            if (curr->User_ID == test ) {
                Scurr = new struct Students;
                Scurr->First_Name = curr->First_Name;
                Scurr->Last_Name = curr->Last_Name;
                Scurr->Student_ID = curr->User_ID;
                Scurr->Next = SHead;
                SHead = Scurr;
                x = true;
                break;
            } else {
                curr = curr->Next;
            }
        }
        if (!x) {
            cout << "ID not found!!\n";
        }
    }
    if(x){
        cout<<"Done.\n";
    }
    ofstream oTeachers("/Users/largexim/Documents/Golestan/files/Students.txt");
    Scurr = SHead;
    while(Scurr!= nullptr){
        oTeachers<<Scurr->First_Name<<" "<<Scurr->Last_Name<<" "<<Scurr->Student_ID;
        Scurr = Scurr->Next;
        if(Scurr!= nullptr) {
            oTeachers << endl;
        }
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }

    while(SHead!= nullptr){
        Scurr = SHead->Next;
        delete SHead;
        SHead = Scurr;
    }

}

void add_lesson_to_teacher(string lname){
    Teachers *THead = nullptr;
    Teachers *Tcurr;
    string test;

    Lesson *Head = nullptr;
    Lesson *curr;

    ifstream Teachers("/Users/largexim/Documents/Golestan/files/Teachers.txt");
    while(!Teachers.eof()){
        Tcurr = new struct Teachers;
        Teachers>>Tcurr->First_Name>>Tcurr->Last_Name>>Tcurr->Teacher_ID;
        Tcurr->Next = THead;
        THead = Tcurr;
    }
    Teachers.close();

    bool x = false;
    cout<<"Enter Teacher's ID : ";
    cin>>test;
    while(!x) {
        while (Tcurr != nullptr) {
            if (Tcurr->Teacher_ID == test) {
                x = true;
                break;
            } else {
                Tcurr = Tcurr->Next;
            }
        }
        if (!x) {
            cout << "ID not found!!\n";
        }
    }
    if(x){
        curr = new struct Lesson;
        curr->T_First_Name = Tcurr->First_Name;
        curr->T_Last_Name = Tcurr->Last_Name;
        curr->Teacher_ID = Tcurr->Teacher_ID;
        curr->S = nullptr;
        cout<<"Done.\n";
    }

    add_to_tl(curr->Teacher_ID ,lname);

    ofstream Lesson("/Users/largexim/Documents/Golestan/files/"+lname+".txt");
    Lesson<<curr->T_First_Name<<" "<<curr->T_Last_Name<<" "<<curr->Teacher_ID<<endl;
    Lesson.close();

    delete Head;

    while(THead!= nullptr){
        Tcurr = THead->Next;
        delete THead;
        THead = Tcurr;
    }

}

void add_to_tl(string teacher , string lname){
    TL *Head = nullptr;
    TL *curr;
    Lessons *Lcurr;
    string test;

    ifstream TL("/Users/largexim/Documents/Golestan/files/TL.txt");
            while (!TL.eof()) {
                TL>>test;
                if(ID_check(test)){
                    curr = new struct TL;
                    curr->Lessons = nullptr;
                    curr->Teacher_ID = test;
                    curr->Next = Head;
                    Head = curr;
                }
                else {
                    Lcurr = new struct Lessons;
                    Lcurr->Lesson_Name = test;
                    Lcurr->Next = curr->Lessons;
                    curr->Lessons = Lcurr;
                }
            }
    TL.close();

    bool x = false;
    curr = Head;
    while(curr!= nullptr){
        if(curr->Teacher_ID == teacher){
            Lcurr = new struct Lessons;
            Lcurr->Lesson_Name = lname;
            Lcurr->Next = curr->Lessons;
            curr->Lessons = Lcurr;
            x = true;
            break;
        }
        curr = curr->Next;
    }

    if(!x){
        curr = new struct TL;
        curr->Teacher_ID = teacher;
        curr->Lessons = nullptr;
        Lcurr = new struct Lessons;
        Lcurr->Lesson_Name = lname;
        Lcurr->Next = curr->Lessons;
        curr->Lessons = Lcurr;
        curr->Next = Head;
        Head = curr;
    }

        curr = Head;
        ofstream oTL("/Users/largexim/Documents/Golestan/files/TL.txt");
    while(curr!= nullptr){
        Lcurr = curr->Lessons;
        oTL<<curr->Teacher_ID<<" ";
        while(Lcurr!= nullptr){
            oTL<<Lcurr->Lesson_Name;
            Lcurr = Lcurr->Next;
            if(Lcurr!= nullptr){
                oTL<<" ";
            }
        }
        curr = curr->Next;
        if(curr!= nullptr){
            oTL<<endl;
        }
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;

    cout<<"TL File Updated.\n";
}

bool ID_check(string ID){
    bool x = false;
    int j = 0;
    int i;
    for( i=0 ; i<10 ; i++){
        if('0'<=ID[i] && ID[i]<='9'){
            j++;
        }
    }
    if(i==j){
        x = true;
    }

    return x;
}

void change_student_password(){
    string test;
    Users *Head = nullptr;
    Users *curr;
    ifstream users("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(!users.eof()){
        curr = new struct Users;
        users>>curr->ID>>curr->First_Name>>curr->Last_Name>>curr->User_ID>>curr->Password;
        curr->Next = Head;
        Head = curr;
    }
    users.close();
    bool i = false;
    while(!i) {
        test = U_ID;
        curr = Head;
        while (curr != nullptr) {
            if (test == curr->User_ID) {
                string test2;
                while(!i) {
                    cout << "Enter your current Password :";
                    cin >> test2;
                    if (curr->Password == test2) {
                        i = true;
                        break;
                    }
                    if(!i){
                        cout<<"Password is not true.";
                    }
                }
                if(i){
                    break;
                }
            }
            curr = curr->Next;
        }
        if(!i){
            cout<<"USER_ID does not exist try again.\n";
        }
    }
    bool z = true;
    while(z){
        cout<<"USER_ID : "<<curr->User_ID<<endl<<"First name : "<<curr->First_Name<<endl;
        cout<<"Last name : "<<curr->Last_Name<<endl;
        cout<<"Change the Password :\n1.Yes\n2.No\n";
        int x = 2;
        cin>>x;
        if(x==2){
            cout<<"OK.\n";
            break;
        }
        else if(x==1){
            while(z) {
                string password1;
                string password2;
                cout << "Enter the new Password : ";
                cin >> password1;
                cout << "Repeat the new Password : ";
                cin >> password2;
                if (password1 != password2) {
                    cout << "Passwords does not Mached!! try again.\n";
                }
                else{
                    if(password1==curr->Password){
                        cout<<"This password is the same as the current one, try another one.\n";
                    }
                    else {
                        curr->Password = password1;
                        cout << "Done.\n";
                        z = false;
                    }
                }
            }
        }
    }

    curr = Head;
    ofstream Ousers("/Users/largexim/Documents/Golestan/files/Users.txt");
    while(curr!= nullptr){
        Ousers<<curr->ID<<" "<<curr->First_Name<<" "<<curr->Last_Name<<" "<<curr->User_ID<<" "<<curr->Password;
        curr = curr->Next;
        if(curr!= nullptr)
            Ousers<<endl;
    }
    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }
    Head = nullptr;
}

void choose_new_lesson() {
    string firstname;
    string lastname;
    {
        Users *Head = nullptr;
        Users *curr;
        ifstream Iusers("/Users/largexim/Documents/Golestan/files/Users.txt");
        while (!Iusers.eof()) {
            curr = new struct Users;
            Iusers >> curr->ID >> curr->First_Name >> curr->Last_Name >> curr->User_ID >> curr->Password;
            curr->Next = Head;
            Head = curr;
        }
        Iusers.close();

        curr = Head;
        while (curr != nullptr) {
            if (curr->User_ID == U_ID) {
                firstname = curr->First_Name;
                lastname = curr->Last_Name;
                break;
            }
            curr = curr->Next;
        }
        while(Head!= nullptr){
            curr = Head->Next;
            delete Head;
            Head = curr;
        }
        Head = nullptr;
    }
    Lesson *Head = nullptr;
    Students *curr;
    Lessons *Lcurr;
    Lcurr = show_lessons();

    ifstream Lesson("/Users/largexim/Documents/Golestan/files/"+Lcurr->Lesson_Name+".txt");
    int x = 1;
    while(!Lesson.eof()){
        if(x==1){
            Head = new struct Lesson;
            Lesson>>Head->T_First_Name>>Head->T_Last_Name>>Head->Teacher_ID;
            Head->S = nullptr;
            x=0;
        }
        else if(x==0){
            curr = new struct Students;
            Lesson>>curr->Student_ID>>curr->Mark;
            curr->Next = Head->S;
            Head->S = curr;
        }
    }

    curr = new struct Students;
    curr->Student_ID = U_ID;
    curr->Mark = "NULL";
    curr->Next = Head->S;
    Head->S = curr;

    ofstream oLesson("/Users/largexim/Documents/Golestan/files/"+Lcurr->Lesson_Name+".txt");
    oLesson<<Head->T_First_Name<<" "<<Head->T_Last_Name<<" "<<Head->Teacher_ID<<endl;
    curr = Head->S;
    while(curr!= nullptr){
        oLesson<<curr->Student_ID<<" "<<curr->Mark;
        curr = curr->Next;
        if(curr!= nullptr){
            oLesson<<endl;
        }
    }
    while(Head->S!= nullptr) {
        curr = Head->S->Next;
        delete Head->S;
        Head->S = curr;
    }
    delete Head;


    cout<<"Done.\n";

}

Lessons *show_lessons(){
    Lessons *Head = nullptr;
    Lessons *curr;

    string test;

    ifstream lesson("/Users/largexim/Documents/Golestan/files/lessons.txt");
    while(!lesson.eof()){
        curr = new struct Lessons;
        lesson>>curr->Lesson_Name>>curr->Lesson_ID;
        curr->Next = Head;
        Head = curr;
    }
    lesson.close();

    int x=0;
    int i = 1;
    while(curr!= nullptr){
        cout<<i<<")"<<curr->Lesson_Name<<" _ "<<curr->Lesson_ID<<".\n";
        curr = curr->Next;
        i++;
    }
    cout<<"which Lesson do you want to Choose?\n";
    cin>>x;

    Lessons *Lcurr;
    curr = Head;
    i=1;
    while(curr!= nullptr){
        if(i==x){
            Lcurr = new struct Lessons;
            Lcurr->Lesson_Name = curr->Lesson_Name;
            Lcurr->Lesson_ID = curr->Lesson_ID;
        }
        curr = curr->Next;
        i++;
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }

    while(Head!= nullptr){
        curr = Head->Next;
        delete Head;
        Head = curr;
    }

    return Lcurr;
}

void set_mark(){
    TL *Head = nullptr;
    TL *curr;
    string Lesson_Name;
    Lessons *Lcurr;
    string test;
    {
        ifstream TL("/Users/largexim/Documents/Golestan/files/TL.txt");
        while (!TL.eof()) {
            TL >> test;
            if (ID_check(test)) {
                curr = new struct TL;
                curr->Lessons = nullptr;
                curr->Teacher_ID = test;
                curr->Next = Head;
                Head = curr;
            } else {
                Lcurr = new struct Lessons;
                Lcurr->Lesson_Name = test;
                Lcurr->Next = curr->Lessons;
                curr->Lessons = Lcurr;
            }
        }
        TL.close();
        curr = Head;
        while (curr != nullptr) {
            if (curr->Teacher_ID == U_ID) {
                Lcurr = curr->Lessons;
                int i = 1;
                while (Lcurr != nullptr) {
                    cout << i << ")" << Lcurr->Lesson_Name << endl;
                    Lcurr = Lcurr->Next;
                    i++;
                }
                int x;
                cout << "Which Lesson do you want to set Mark : ";
                cin >> x;
                Lcurr = curr->Lessons;
                i = 1;
                while (Lcurr != nullptr) {
                    if (i == x) {
                        Lesson_Name = Lcurr->Lesson_Name;
                        break;
                        i++;
                    }
                    Lcurr = Lcurr->Next;
                }
            }
            curr = curr->Next;
        }
    }

    Lesson *LHead = nullptr;
    Students *Scurr;
    ifstream Lesson("/Users/largexim/Documents/Golestan/files/"+Lesson_Name+".txt");
    int x = 1;
    while(!Lesson.eof()){
        if(x==1){
            LHead = new struct Lesson;
            Lesson>>LHead->T_First_Name>>LHead->T_Last_Name>>LHead->Teacher_ID;
            LHead->S = nullptr;
            x=0;
        }
        else if(x==0){
            Scurr = new struct Students;
            Lesson>>Scurr->Student_ID>>Scurr->Mark;
            Scurr->Next = LHead->S;
            LHead->S = Scurr;
        }
    }

    Scurr = LHead->S;
    int i=1;
    while(Scurr!= nullptr){
        cout<<i<<")"<<Scurr->Student_ID<<endl;
        Scurr=Scurr->Next;
        i++;
    }
    cout<<"Which Student do you want to score : ";
    cin>>x;
    i=1;
    Scurr =LHead->S;
    while(Scurr!= nullptr){
        if(i==x){
            cout<<"Enter the Mark : ";
            cin>>Scurr->Mark;
            break;
        }
        Scurr = Scurr->Next;
        i++;
    }

    ofstream oLesson("/Users/largexim/Documents/Golestan/files/"+Lesson_Name+".txt");
    oLesson<<LHead->T_First_Name<<" "<<LHead->T_Last_Name<<" "<<LHead->Teacher_ID<<endl;
    Scurr = LHead->S;
    while(Scurr != nullptr){
        oLesson<<Scurr->Student_ID<<" "<<Scurr->Mark;
        Scurr = Scurr->Next;
        if(Scurr!= nullptr){
            oLesson<<endl;
        }
    }
    oLesson.close();
    cout<<"Done.\n";


    while(Head!= nullptr){
        curr = Head->Next;
        while(Head->Lessons != nullptr){
            Lcurr = Head->Lessons->Next;
            delete Head->Lessons;
            Head->Lessons = Lcurr;
        }
        delete Head;
        Head = curr;
    }

    while(LHead->S!= nullptr) {
        Scurr = LHead->S->Next;
        delete LHead->S;
        LHead->S = Scurr;
    }
    delete LHead;

}
