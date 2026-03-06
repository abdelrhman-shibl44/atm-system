#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "./mylib.h"
using namespace std;

struct stClientData {
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    double Balance = 0;
    bool markforDeletion = false;
};

enum enATMOptions { QUICK_WITHDRAW = 1, NORMAL_WITHDRAW, DEPOSIT, CHECK_BALANCE, LOGOUT };

const string clientsFile = "Clients.txt";

void showLoginScreen();

void header(string headerTxt){
    cout << "====================================================\n";
    cout << "=================" << headerTxt << "================\n";
}

stClientData convertLineToRecord(string line){
    stClientData clientData;
    vector<string> data = split(line, "#//#");
    clientData.accountNumber = data[0];
    clientData.pinCode = data[1];
    clientData.name = data[2];
    clientData.phone = data[3];
    clientData.Balance = stod(data[4]);
    return clientData;
}

vector<stClientData> getClients(string fileName){
    fstream file;
    vector<stClientData> vClients;
    file.open(fileName, ios::in);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            stClientData client =  convertLineToRecord(line);
            vClients.push_back(client);
        }
        file.close();
    }
    return vClients;
}

bool isClientExist(string accountNumber, string pinCode){
    vector<stClientData> users = getClients(clientsFile);
    for(stClientData &user: users){
        if(user.accountNumber == accountNumber && user.pinCode == pinCode){
            return true;
        }
    }
    return false;
}

void chooseOperation(short option){
    switch ((enATMOptions) option){
        case enATMOptions::QUICK_WITHDRAW : 
        
        break;  
        case enATMOptions::NORMAL_WITHDRAW :
        
        break;
        case enATMOptions::DEPOSIT :
        
        break;
        case enATMOptions::CHECK_BALANCE :
        break;
        case enATMOptions::LOGOUT: 
        showLoginScreen();
        break;
        default:
            break;
    }
}

void atmMenuScreen(){
    system("cls");
    cout <<"==================================================\n";
    cout << "\t\tATM Menu Screen\n";
    cout <<"==================================================\n";
    cout << "\t[1] Quick Withdraw.\n"
            "\t[2] Normal Withdraw.\n"
            "\t[3] Deposit.\n"
            "\t[4] Check Balance.\n"
            "\t[5] Logout.\n";
    cout <<"==================================================\n";
    short chosenOption = readNumber("Choose what do you want to do? [1 to 6]? ");
    chooseOperation(chosenOption);
}

void showLoginScreen(){
    system("cls");
    header("Login Screen");
    bool clientExist = false;
    do{
        string username = readString("Enter your Account Number? ");
        string password = readString("Enter your PinCode? ");
        if(isClientExist(username, password)){
            clientExist = true;
        }else{
            clientExist = false;
            cout << "Invalid Credential :(\n";
        }
    }while(!clientExist);
    atmMenuScreen();
}


int main(){
    showLoginScreen();
    return 0;
}