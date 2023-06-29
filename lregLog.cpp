#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h> // Added header for AES_set_encrypt_key
#include <fstream>

using namespace std;

class registrationLogin {
private:
    int ID = 0;

public:
    registrationLogin() {}

    void registration(string firstname, string lastname, string username, string DOB, int age, string email, string password) {
        fstream myfile;
        myfile.open("Database.txt", ios::app);
        if (myfile.is_open()) {
            myfile << increaseIDByOne() << "," << firstname << "," << lastname << "," << username << "," << DOB << "," << age << "," << email << "," << encryptPassword(password, "key") << endl;
            myfile.close();
        }
    }

    void login(string username, string password) {
        fstream myfile;
        myfile.open("Database.txt", ios::in);
        if (myfile.is_open()) {
            string line;
            stringstream ssin; // Move the declaration here
            while (getline(myfile, line)) {
                string data[8];
                int i = 0;
                ssin.str(line); // Set the line to the stringstream
                ssin.clear(); // Clear the state flags of the stringstream
                while (ssin.good() && i < 8) {
                    ssin >> data[i];
                    ++i;
                }
                if (data[3] == username) {
                    if (data[7] == encryptPassword(password, "key")) {
                        cout << "Login successful" << endl;
                    } else {
                        cout << "Incorrect password" << endl;
                    }
                    return; // Exit the function after finding the username
                }
            }
            cout << "Incorrect username" << endl; // Username not found
            myfile.close();
        }
    }


    void checkusername(string username) {
        cout << "Check username" << endl;
    }

    int increaseIDByOne() {
        return ++ID;
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
        string* password;

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
        cin>>*password;
        regLog.registration(firstname,lastname,username,dateOfBirth,age,email,regLog.encryptPassword(*password,"key"));

    }else if(option == 2){
        // create variables for user details
        string username;
        string password;

        cout<<"\n\t\t\t********** login *************"<<endl;
        cout<<"\nUsername: ";
        cin>>username;
        cout<<"Password: ";
        cin>>password;
        regLog.login(username,password);
    }else{
        cout<<"Invalid option"<<endl;
    }
}