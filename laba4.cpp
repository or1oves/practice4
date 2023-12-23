#include <iostream>
#include <limits>
#include <string.h>
#include <stdlib.h>

using namespace std;
int const maxWords = 10, inWords = 50;
char firstLetters[] = {'A', 'B', 'C', 'D', 'E',
                       'F', 'G', 'H', 'I', 'J'};

char arrOfSymbols[] = {',', '?', '!',
                       ' ', ':', ';',
                       '-', };

void Menu(){

    cout << "1) enter de line" << '\n';
    cout << "2) edit de line" << '\n';
    cout << "3) first task (number 4)" << '\n';
    cout << "4) second task (number 4)" << '\n';
    cout << "5) find dlc-strings" << '\n';
    cout << "0) exit de program" << '\n' << '\n';

}

void deleteSymbols(char string[], char symbol){
    for (int i = 0; i < strlen(string) - 1; i++){
        if (string[i] == symbol &&  string[i + 1] == symbol){
            for (int j = i + 1; j < strlen(string); j ++){
                string[j - 1] = string[j];
            }
            string[strlen(string) - 1] = '\0'; // конец строки
            i--;
        }
    }
}

void registerChange(char string[]){
    for (int i = 1; i < strlen(string); i++ ){
        string[i] = tolower(string[i]); // вниз
    }
    string[0] = toupper(string[0]); // вверх
}

void clearTheBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int count(char string[], char symbol){
    int count = 0;
    for (int i = 0; i < strlen(string); i++ ){
        if (string[i] == symbol ) {
            count ++;
        }
    }
    return count;
}

int find(char string[], char symbol, int start=0){
    for (int index = start; index < strlen(string); index++){
        if (string[index] == symbol){
            return index;
        }
    }
    return -1;
}

int total(char string[], char totalString[inWords][maxWords], char separator=' '){ //стр-соединятор 2023
    int words = count(string, separator) + 1;
    int start, end = -1;
    for ( int i = 0; i < words; i++ ){
        start = end + 1;
        end = find(string, separator, start);
        if (end == -1){
            end = strlen(string);
        }
        for ( int j = start, index = 0; j < end; j++, index++ ){
            totalString[i][index] = string[j];
        }
    }
    return words;
}

bool isRepeated(char string[]){
    for ( int i = 0; i < strlen(arrOfSymbols); i++ ){
        if (string[0] == arrOfSymbols[i]){
            return true;
        }
    }
    return false;
}

void searchikLinear(char *string, char *string2)
{
    int count1 = 0;
    for (int i = 0; string[i] != 0; ++i)
    {
        int count = 0;
        for (int j = 0; string2[j] != 0; ++j)
        {
            if (string[i+j] != string2[j])
            {
                count = 1;
                break;
            }
        }
        if (count == 0)
        {
            cout << i << ' ';
            count1 = 1;
        }
    }
    cout << endl;
}

int main4() {

    int taskNumber,words;
    const int sizeOfString = 500;
    char string[sizeOfString], string2[sizeOfString];
    char crackingString[inWords][maxWords] = {};
    bool repeaters;

    Menu();

    for (int repeatTask = 0; repeatTask < 100; repeatTask++){
        cout << "enter de task number: ";
        cin >> taskNumber;
        cout << '\n';
        clearTheBuffer();

        switch (taskNumber){

            case 1:

                cout << "enter de line: ";
                cin.getline(string, sizeOfString);
                cout << '\n';
                break;

            case 2:

                for ( int i = 0; i < strlen(arrOfSymbols); i++ ){
                    deleteSymbols(string, arrOfSymbols[i]);
                }
                registerChange(string);
                cout << "new string: " << string;
                cout << '\n' << '\n';
                break;

            case 3:

                words = total(string, crackingString);
                cout << "words with repeated letters (if there is a void in de line, then there are no such words): ";
                for (int word = 0; word < words; word++){
                    if (isRepeated(crackingString[word])){
                        continue;
                    }
                    repeaters = false;
                    for (int letter = 0; letter < strlen(crackingString[word]); letter++ ){
                        if (repeaters){
                            break;
                        }
                        for (int i = letter + 1; i < strlen(crackingString[word]); i++ ){
                            if (tolower(crackingString[word][letter]) == tolower(crackingString[word][i])) {
                                cout << crackingString[word] << " ";
                                repeaters = true;
                                break;
                            }
                        }
                    }
                }
                cout << '\n' << '\n';
                break;

            case 4:

                for ( int i = 0; i < strlen(string); i++ ){
                    if (string[i] >= '0' && string[i] <= '9'){
                        string[i] = firstLetters[string[i] - '0'];
                    }
                }
                cout << "new string: " << string << '\n' << '\n';
                break;

            case 5:

                cout << "enter a dlc-substring: ";
                cin.getline(string, sizeOfString);
                cout << '\n';
                searchikLinear(string, string2); // индексы вхождений
                cout << '\n';
                break;

            case 0:
                exit(0);
        }
    }
    return 0;
}