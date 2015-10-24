#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;



class PersInt{
    PersInt();
    fstream file;

public:
    PersInt(string fileName){
        fileName += ".txt";
        file.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    }

    void addInt(string key, int value){
        stringstream stream;
        stream << value;

        key = key + ":" + stream.str();
        file << key << endl;
    }

    int getInt(string key){
        string parser;
        int track = 0;
        bool found = 0;
        file.clear();
        file.seekg(0,file.beg);
        int parsLen;
        while( !file.eof() ){
            track = 0;
            getline(file,parser);
            parsLen = getKeyLen(parser);
            for(int i = 0; i < key.length(); i++){
                if(key[i] == parser[i])
                    track++;
            }
            if( (track == (int)key.length()) && (track == parsLen) ){
                found = 1;
                break;
            }
        }

        if(found){
            int val = getVal(parser);
            return val;
        }

        return -9999;
    }


    int getVal(string s){
        int i = 0;
        bool flag = 0;
        while( i < s.length() ){
            if(s[i] == ':'){
                flag = 1;
                break;
            }
            i++;
        }

        if(flag){
            char temp[ s.length() - (i + 1) ];
            i++;
            int j = 0;
            while(i < s.length()){
                temp[j] = s[i];
                j++;
                i++;
            }
            int val = atoi(temp);
            return val;
        }

        return -9999;
    }

    int getKeyLen(string s){
        int i = 0;

        while(s[i] != ':')
            i++;
        return i;
    }


    void closeIt(){
        file.close();
    }

};


/*
*int main(){
*    short int reply;
*    string keyString, searchKey;
*    int valString, result;
*    PersInt test("test");
*    cout << "What do you want to do? " << endl;
*    while(1){
*        cout << "1. Add a new value to the database" << endl << "2. Get a value from the database." << endl << "3. Exit" << endl;
*        cin >> reply;
*        switch(reply){
*        case 1:
*            cout << "Enter the key" << endl;
*            cin >> keyString;
*            cout << "Enter the value" << endl;
*            cin >>  valString;
*            test.addInt(keyString, valString);
*            cout << keyString << ":" << valString << " added." << endl;
*            break;
*
*        case 2:
*            cout << "Enter the key" << endl;
*            cin >> searchKey;
*            result = test.getInt(searchKey);
*            if(result != -9999)
*                cout << "The value of " << searchKey << " is " << result << endl;
*            else
*                cout << "The given key doesn't exist in the database." << endl;
*            break;
*
*        case 3:
*            test.closeIt();
*            return 0;
*            break;
*
*        default:
*            cout << "Invalid option. Please try again" << endl;
*            break;
*        }
*    }
*
*
*return 0;
*}
*
*/