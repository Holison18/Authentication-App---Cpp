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

    string encryptPassword(const string& password, const string& key) {
        string encryptedPassword;
        unsigned char iv[AES_BLOCK_SIZE];
        memset(iv, 0x00, AES_BLOCK_SIZE);

        AES_KEY aesKey;
        if (AES_set_encrypt_key((unsigned char*)key.c_str(), 128, &aesKey) < 0) {
            cerr << "Unable to set encryption key in AES" << endl;
            return encryptedPassword;
        }

        int passwordLength = password.length();
        int paddedLength = ((passwordLength / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
        unsigned char* paddedPassword = new unsigned char[paddedLength];
        memset(paddedPassword, 0x00, paddedLength);
        memcpy(paddedPassword, password.c_str(), passwordLength);

        unsigned char* encryptedData = new unsigned char[paddedLength];
        AES_cbc_encrypt(paddedPassword, encryptedData, paddedLength, &aesKey, iv, AES_ENCRYPT);
        encryptedPassword.assign(reinterpret_cast<const char*>(encryptedData), paddedLength);

        delete[] paddedPassword;
        delete[] encryptedData;

        return encryptedPassword;
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