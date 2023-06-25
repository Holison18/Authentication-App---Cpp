#include <iostream>
#include <string>
#include <openssl/ssl.h>



using namespace std;

class registrationLogin{
    private:
        int ID = 0;
    public:
        // constructor
        registrationLogin(){};

        void registration(string username,string email, string password){
            cout<<"Registration"<<endl;
        }

        void login(string username,string password){
            cout<<"Login"<<endl;
        }

        void checkpasswordlen(string password){
            if(password.length() < 8){
                cout<<"Password too short"<<endl;
            }else{
                cout<<"You can proceed"<<endl;
            }

        }

        void checkusername(string username){
            cout<<"Check username"<<endl;
        }

        int increaceIDByOne(){
            this->ID += 1;
            return ID;
        }

};

int main(){
    // create a variable to take user response
    int option;

    // main menu screen
    cout<<"\n\t\t\t\t**********Registration and Login*************"<<endl;
    cout<<"\n[1] login"<<endl;
    cout<<"[1] Register an account"<<endl;
    cin>>option;

    if(option == 1){
        // create variables for user details
        string firstname;
        string lastname;
        string username;
        string dateOfBirth;
        int age;
        string email;
        string password;

        cout<<"\n\t\t\t**********Registration*************"<<endl;
        cout<<"\nfill the form below with your details"<<endl;
        cout<<"First name: ";
        cin>>firstname;
        cout<<"Last name: ";
        cin>>lastname;
        cout<<"Username: ";
        cin>>username;
        cout<<"Date of birth(DD/MM/YY): ";
        cin>>dateOfBirth;
        cout<<"Age: ";
        cin>>age;
        cout<<"Email: ";
        cin>>email;
        cout<<"Password: ";
        cin>>password;
    }else if(option == 2){
        // create variables for user details
        string username;
        string password;

        cout<<"\n\t\t\t**********login*************"<<endl;
        cout<<"\nUsername: ";
        cin>>username;
        cout<<"Password: ";
        cin>>password;

}