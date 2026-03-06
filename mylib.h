#ifndef MYLIB_H
#define MYLIB_H
#include <iostream>
#include <limits>
#include <math.h>
#include <numbers>
#include <vector>
using namespace std;

struct sDate {
    short Year;
    short Month;
    short Day;
};

int readNumber(string message){
    int num = 0;
    cout << message;
    cin >> num;
    
    while(num < 0){
        cout << "Please Enter a positive number: ";
        cin >> num;
    }

    while (cin.fail())
    {       
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter a valid one: ";
    }
    
    return num;
}


string readString(string message){
    string input = "";
    cout << message;
    getline(cin  >> ws, input);

    while (cin.fail())
    {       
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter a valid string: ";
    }
    
    return input;
}

char readChar(string message){
    char input;
    cout << message;
    cin >> input;

    while (cin.fail())
    {       
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter a valid string: ";
    }
    
    return input;
}

void readArr(int arr[100],int length){
    for(int i = 0; i < length; i++){
    cout << arr[i] << " ";
  }
  cout << endl;
} 
void readArr(string arr[100],int length){
    for(int i = 0; i < length; i++){
        cout << "array [" << i << "] " << arr[i] << " " << endl;;
    }
} 

void readArr(vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
            cout << arr[i] << " ";   
    }
} 

void readArr(vector<string>& arr){
    for(int i = 0; i < arr.size(); i++){
            cout << arr[i] << " ";   
    }
} 

vector<string>split(string text, string delim){
    // cout << "Tokens =" << countWordsInString(text) << endl;
    vector<string> words;
    short pos = 0;
    string word = "";
    short counter = 0;

        while((pos = text.find(delim)) != string::npos){
        word = text.substr(0, pos);
        if(word != ""){
            words.push_back(word);
        }
        text.erase(0, pos + delim.length());
    }
    if(text !=""){
        words.push_back(text);
    }
    return words;
}


string join(vector<string> arr,string delim = " "){
    string text = "";
    for(string &t: arr){
        text += t + delim;
    }
    return text.substr(0, text.length() - 1);;
}

string join(string arr[100],int arrLength,string delim = " "){
    string text = "";
    for(int i = 0; i < arrLength; i++){
        text += arr[i] + delim;
    }
    return text.substr(0, text.length() - 1);;
}

string reverseString(string text){
    vector<string> arr = split(text, " ");
    string string2 = "";

    vector<string>::iterator iter = arr.end();

    while (iter != arr.begin()){   
        --iter;
        string2 += *iter + " ";
    }
    return string2.substr(0, string2.length() - 1);
    // return join(reversedArr, " ");
}

string replaceString(string text, string toReplace, string replaceTo){
    short pos = 0;
    while((pos = text.find(toReplace))  != string::npos){
        text.replace(pos, toReplace.length(), replaceTo);
    }
    return text;
}