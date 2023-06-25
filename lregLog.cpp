#include <iostream>
#include <string>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <fstream>



using namespace std;

class registrationLogin{
    private:
        int ID = 0;
    public:
        // constructor
        registrationLogin(){};

        void registration(string firstname,string lastname,string username,string DOB,int age,string email, string password){
            // open myfile and append user details
            fstream myflie ;
            myflie.open("Database.txt",ios::app);
            if(myflie.is_open()){
                myflie<<increaceIDByOne()<<","<<firstname<<","<<lastname<<","<<username<<","<<DOB<<","<<age<<","<<email<<","<<encryptPassword(password,"key")<<endl;
                myflie.close();
            }

        }

        void login(string username,string password){
            cout<<"Login"<<endl;cout<<"Registration"<<endl;
        }

        void checkusername(string username){
            cout<<"Check username"<<endl;
        }

        int increaceIDByOne(){
            this->ID += 1;
            return ID;
        }

        string encryptPassword(const std::string& password, const std::string& key) {
            const int keyLength = 32; // AES-256 key length
            unsigned char iv[AES_BLOCK_SIZE] = {0}; // Initialization vector (IV)
            unsigned char encryptedData[password.size() + AES_BLOCK_SIZE];

            EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
            EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), iv);
            EVP_EncryptUpdate(ctx, encryptedData, nullptr, reinterpret_cast<const unsigned char*>(password.c_str()), password.size());
            int encryptedLength = 0;
            EVP_EncryptFinal_ex(ctx, encryptedData + password.size(), &encryptedLength);
            EVP_CIPHER_CTX_free(ctx);

            std::string encryptedString(reinterpret_cast<const char*>(encryptedData), password.size() + encryptedLength);
            return encryptedString;
    }

};

int main(){
    //create an of object of the class
    registrationLogin regLog;

    // create a variable to take user response
    int option;

    // main menu screen
    cout<<"\n\t\t\t\t********** Main Menu *************"<<endl;
    cout<<"\n[1] login"<<endl;
    cout<<"[2] Register an account"<<endl;
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

        cout<<"\n\t\t\t********** Registration *************"<<endl;
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
        regLog.registration(firstname,lastname,username,dateOfBirth,age,email,password);

    }else if(option == 2){
        // create variables for user details
        string username;
        string password;

        cout<<"\n\t\t\t********** login *************"<<endl;
        cout<<"\nUsername: ";
        cin>>username;
        cout<<"Password: ";
        cin>>password;
    }else{
        cout<<"Invalid option"<<endl;
    }
}