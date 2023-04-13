#include <iostream>
#include <fstream>
using namespace std;
struct Users{
    int ID;
    string First_Name;
    string Last_Name;
    string User_ID;
    string Password;
    Users *Next;
};
int entry();
int ADMIN();
void add_new_user();
void delete_user();
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
        case 1 : cout<<"you are teacher.";break;
        case 2 : cout<<"you are student.";break;
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
int ADMIN(){
    int menu=0;
    while(menu==0){
        cout<<"1)Add new user.\n2)Delete User.\n3)Exit.\n";
        cin>>menu;
        switch (menu) {
            case 1 : add_new_user();menu=0;break;
            case 2 : delete_user();menu=0;break;
            case 3 : menu = -1;
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
    while(i==false) {
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
        if(i==false){
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



