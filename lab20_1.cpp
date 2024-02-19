#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string  fname, vector<string>& studentlist, vector<int>& score ,vector<char>& grade){
    ifstream stulist(fname) ;
    string infor ;
    char format[] = "%[^:]:%d %d %d";
    int f,s,t ;
    char stuname[100] ;
    int ova ;
    while(getline(stulist, infor)){
        const char * newinfor = infor.c_str() ;
        sscanf(newinfor,format,stuname,&f,&s,&t) ;
        ova = f+s+t ;
        studentlist.push_back(stuname) ;
        score.push_back(ova) ;
        grade.push_back(score2grade(ova)) ;
    }
    stulist.close() ;
}

void getCommand(string &command, string &key){
    cout << "Please input your command: " ;
    cin >> command ;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE"){
        cin.ignore() ;
        getline(cin,key) ;
    }
}

void searchName(vector<string>& studentlist, vector<int>& score ,vector<char>& grade,string key){
    int count = 0 ;
    cout << "---------------------------------\n";
    for(unsigned int i = 0 ; i < studentlist.size(); i++){
        if(key == toUpperStr(studentlist[i])){
            cout << studentlist[i] << "'s score = " << score[i] << '\n' ;
            cout << studentlist[i] << "'s grade = " << grade[i] << '\n' ;
            count++ ;
        }
        else if (i == studentlist.size() - 1 && count == 0){
            cout << "Cannot found." << '\n' ;
        }
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string>& studentlist, vector<int>& score ,vector<char>& grade,string key){
    int count = 0 ;
    char fkey = key[0] ;
    cout << "---------------------------------\n";
    for(unsigned int i = 0 ; i < studentlist.size(); i++){
        if(fkey == grade[i]){
            cout << studentlist[i] << " (" << score[i] << ")" << '\n' ;
            count++ ;
        }
        else if (i == studentlist.size() - 1 && count == 0){
            cout << "Cannot found." << '\n' ;
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
