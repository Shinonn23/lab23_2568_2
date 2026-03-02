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

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream file(filename);
    string line;

    char name[100];
    int s1, s2, s3;

    while (getline(file, line)) {
        if (sscanf(line.c_str(), "%99[^:]: %d %d %d", name, &s1, &s2, &s3) == 4) {
            int sum = s1 + s2 + s3;

            names.push_back(name);
            scores.push_back(sum);
            grades.push_back(score2grade(sum));
        }
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin >> ws, line);

    char cmdBuf[100] = {}, keyBuf[256] = {};
    sscanf(line.c_str(), "%99s %255[^\n]", cmdBuf, keyBuf);

    command = cmdBuf;
    key = keyBuf;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    string target = toUpperStr(key);

    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == target) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }

    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    cout << "---------------------------------\n";

    char target = toupper(key[0]);
    bool found = false;

    for (size_t i = 0; i < names.size(); i++) {
        if (toupper(grades[i]) == target) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Cannot found.\n";
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
