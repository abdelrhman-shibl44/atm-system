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

enum enATMOptions { QUICK_WITHDRAW = 1, NORMAL_WITHDRAW, DEPOSIT, CHECK_BALANCE, CHNAGE_PASS, LOGOUT };
enum enAmount {TWENTY = 1, FIFTY, HUNDRED, TWO_HUNDRED, FOUR_HUNDRED, SIX_HUNDRED , EIGHT_HUNDRED , THOUSAND, EXIST = 9 };

const string clientsFile = "Clients.txt";
stClientData currUser;

void showLoginScreen();
void atmMenuScreen();

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

bool isClientExist(string accountNumber, string pinCode, stClientData &clientData){
    vector<stClientData> clients = getClients(clientsFile);
    for(stClientData &client: clients){
        if(client.accountNumber == accountNumber && client.pinCode == pinCode){
            clientData = client;
            return true;
        }
    }
    return false;
}

void checkBalanceScreen(){
    header("Screen Balance");
    cout << "| " << left << setw(15) << "Balance";
    cout << "\n--------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(15) <<  currUser.Balance << endl;
    cout << endl;
}

void backToMainMenu(){
    cout << "Press any key to go back to the Main Menu :)" << endl;
    system("pause>0");
    atmMenuScreen();
}

stClientData transaction(string accountNumber, vector<stClientData> &vClients, double amount){
    char answer = readChar("Are you sure you want to perform this transaction? ");
    if(tolower(answer) == 'y'){
        for(stClientData &client: vClients){
            if(convertTextToLower(client.accountNumber) == convertTextToLower(accountNumber)){  
                client.Balance = client.Balance + amount;
                return client;
            }
        }
    }
}

string convertRecordToLine(stClientData clientData, string delim = "#//#"){
    return(
        clientData.accountNumber + delim +
        clientData.pinCode + delim +
        clientData.name + delim + 
        clientData.phone + delim +
        to_string(clientData.Balance)
    );
}

void saveClientsToFile(vector<stClientData> vClients){
    fstream file; 
    file.open(clientsFile, ios::out);
    if(file.is_open()){
        for(stClientData &client: vClients){
            if(!client.markforDeletion){
                string line = convertRecordToLine(client);
                file << line << endl;
            }
        }
        file.close();
    }
}

void quickWithDraw(short withDrawAmount){
    vector<stClientData> vClients = getClients(clientsFile);
        while(currUser.Balance < withDrawAmount){
            cout << "Exceed Amount you can withdraw up to " << currUser.Balance << endl;
            withDrawAmount = readNumber("Choose what to withdraw from ? [1 to 8]? ");
            while(withDrawAmount < 1 || withDrawAmount > 8){
                withDrawAmount = readNumber("Choose what to withdraw from ? [1 to 8]? ");
            }
        }
        stClientData updatedClient = transaction(currUser.accountNumber, vClients, withDrawAmount * -1);
        currUser = updatedClient; 
        saveClientsToFile(vClients);
        cout << "Withdraw made successfully :)" << endl;
}

void NormalWithDraw(){
    header("Normal Withdraw Screen");
    cout <<"==================================================\n";
    cout << "Your Balance is: " << currUser.Balance << endl;
    cout <<"==================================================\n";
    int withDrawAmount = readNumber("Enter an amount multiple of 5's ? ");
    vector<stClientData> vClients = getClients(clientsFile);
        while(currUser.Balance < withDrawAmount){
            cout << "Exceed Amount you can withdraw up to " << currUser.Balance << endl;
            withDrawAmount = readNumber("Enter an amount multiple of 5's ? ");
        }
        while(withDrawAmount % 5 != 0 ){
            cout << "Invalid value," << currUser.Balance << endl;
            withDrawAmount = readNumber("Enter an amount multiple of 5's ? ");
        }
        stClientData updatedClient = transaction(currUser.accountNumber, vClients, withDrawAmount * -1);
        currUser = updatedClient; 
        saveClientsToFile(vClients);
        cout << "Withdraw made successfully :)" << endl;
}

void DepositScreen(){
    header("Deposit Screen");
    cout <<"==================================================\n";
    cout << "Your Balance is: " << currUser.Balance << endl;
    cout <<"==================================================\n";
    int depositAmount = readNumber("Enter an amount you want to deposit ? ");
    vector<stClientData> vClients = getClients(clientsFile);
        stClientData updatedClient = transaction(currUser.accountNumber, vClients, depositAmount);
        currUser = updatedClient; 
        saveClientsToFile(vClients);
        cout << "Deposit made successfully :)" << endl;
}

void chooseAmount(short option){
    switch ((enAmount) option){
        case enAmount::TWENTY :
        quickWithDraw(20);
        break;
        case enAmount::FIFTY :
        quickWithDraw(50);
        break;
        case enAmount::HUNDRED :
        cout << "the option is " << option << endl;
        quickWithDraw(100);
        break;
    case enAmount::TWO_HUNDRED :
        quickWithDraw(200);
        break;
    case enAmount::FOUR_HUNDRED :
        quickWithDraw(400);
        break;
    case enAmount::SIX_HUNDRED :
        quickWithDraw(600);
        break;
    case enAmount::EIGHT_HUNDRED :
        quickWithDraw(800);
        break;
    case enAmount::THOUSAND:
        quickWithDraw(1000);
        break;
    case enAmount::EXIST:
        atmMenuScreen();
        break;
    default:
        break;
    }
}

void quickWithDrawScreen(){
    system("cls");
    header("Quick Withdraw");
    cout << "\t[1] 20 \t"    "\t[2] 50.\n" << endl;
    cout << "\t[3] 100 \t"   "[4] 200.\n" << endl;
    cout << "\t[5] 400 \t"   "[6] 600.\n" << endl;
    cout << "\t[7] 800 \t"   "[8] 1000.\n" << endl;
    cout << "\t[9] Exist \t" << endl;
    cout <<"==================================================\n";
    cout << "Your Balance is: " << currUser.Balance << endl;
    cout <<"==================================================\n";
    short chosenOption = readNumber("Choose what to withdraw from ? [1 to 8]? ");
    while(chosenOption < 1 || chosenOption > 9){
        chosenOption = readNumber("Choose what to withdraw from ? [1 to 8]? ");
    }
    chooseAmount(chosenOption);
}

bool findUserByUsername(string username,stClientData &clientData, vector<stClientData> &vClients){
    for(stClientData &client: vClients){
        if(client.name == username){    
            clientData = client;
            return true;
        }
    }
    return false;
}

bool changePassword(string oldPinCode, stClientData clientData, vector<stClientData> &vClients){
    for(stClientData &client: vClients){
        if(client.accountNumber == clientData.accountNumber){
            if(oldPinCode == client.pinCode){
                string newPinCode =  readString("please Enter your new password");
                string confirmPinCode = readString("please Confirm your new password");
                if(newPinCode == confirmPinCode){
                    client.pinCode = newPinCode;
                    return true;
                }else{
                    cout << "passwords don't match" << endl;
                    return false;
                }
            }else{
                cout << "old pinCodes don't match" << endl;
                return false;
            }
        }
    }
}

void changePasswordScreen(){
    header("Change Password Screen");
    vector<stClientData> vClients =  getClients(clientsFile);
    stClientData client;
    if(findUserByUsername(currUser.name, client,vClients)){
        string oldPinCode =  readString("Please Enter your old password ? ");
        if(changePassword(oldPinCode, client, vClients)){
            saveClientsToFile(vClients);
            cout << "Password changed successfully :)" << endl;
        }else{
            cout << "Failed to change password :(" << endl;
        }
    }   
}

void chooseOperation(short option){
    switch ((enATMOptions) option){
        case enATMOptions::QUICK_WITHDRAW : 
        quickWithDrawScreen();
        backToMainMenu();
        break;  
        case enATMOptions::NORMAL_WITHDRAW :
        NormalWithDraw();
        backToMainMenu();
        break;
        case enATMOptions::DEPOSIT :
        DepositScreen();
        backToMainMenu();
        break;
        case enATMOptions::CHECK_BALANCE :
        checkBalanceScreen();
        backToMainMenu();
        break;
        case enATMOptions::CHNAGE_PASS :
        changePasswordScreen    ();
        backToMainMenu();
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
            "\t[5] Change Password.\n"
            "\t[6] Logout.\n";
    cout <<"==================================================\n";
    short chosenOption = readNumber("Choose what do you want to do? [1 to 6]? ");
    chooseOperation(chosenOption);
}

void showLoginScreen(){
    system("cls");
    header("Login Screen");
    bool clientExist = false;
    stClientData clientData;
    do{
        string username = readString("Enter your Account Number? ");
        string password = readString("Enter your PinCode? ");
        if(isClientExist(username, password, clientData)){
            currUser = clientData;
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