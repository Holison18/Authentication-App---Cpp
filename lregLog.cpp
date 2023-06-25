#include <iostream>
#include <string>
#include <openssl/ssl.h>



using namespace std;

class registrationLogin{
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

};

int main(){
    // create a variable to take user response
    int option;

    // main menu screen
    cout<<"\n\t\t\t\t**********Registration and Login*************"<<endl;
    cout<<"[1] login"<<endl;
    cout<<"[1] Register an account"<<endl;
    cin>>option;

    if(option == 1){
        // create variables for user details
        string username;
        string email;
        string password;

        cout<<"\n\t\t\t**********Registration and Login*************"<<endl;
    }

}