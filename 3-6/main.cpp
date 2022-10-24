#include <fstream>
#include <iostream>
#include <string>

#include "LinkedStack.h"
using namespace std;

class NoSuchFile {};

enum Token { BEGIN, END, IF, THEN, ELSE, BLANK };
string token[] = {"begin", "end", "if", "then", "else"};

int currentLine;
string buffer;
ifstream fin;

void init(const char *s) {
    fin.open(s);
    if (!fin) throw NoSuchFile();
    currentLine = 1;
}

Token get_next_token() {
    // '\n' means there is a new line
    while ((fin.peek() == '\n') && currentLine++, fin >> buffer) {
        for (int i = 0; i < 5; i++)
            if (buffer == token[i]) return Token(i);
        if (buffer == "end.") return END;
    }
    return BLANK;
}

bool checkFile() {
    LinkedStack<Token> s;
    Token lastToken, matchToken;
    while ((lastToken = get_next_token()) != BLANK) {
        switch (lastToken) {
            // begin and if don't need check
            case BEGIN:
            case IF:
                s.push(lastToken);
                break;

            case END:
                if (s.isEmpty())
                    return 0;
                else {
                    matchToken = s.pop();

                    // begin
                    // if ... then ...
                    // if ... then ...
                    // end
                    while (matchToken == THEN) matchToken = s.pop();
                    if (matchToken != BEGIN) return 0;
                }
                break;
            case THEN:
                if (s.isEmpty())
                    return 0;
                else {
                    matchToken = s.pop();

                    // if is followed by then 
                    if (matchToken == IF) s.push(THEN);
                    else return 0;
                }
                break;
            case ELSE:
                if (s.isEmpty()) return 0;
                else {
                    matchToken = s.pop();

                    // else occurs after if...then
                    if (matchToken != THEN) return 0;
                }
                break;
            default: break;
        }
    }
    while (!s.isEmpty()) {
        matchToken = s.pop();

        // every then is following if, it's ok
        if (matchToken != THEN) return 0;
    }
    return 1;
}

int main() {
    cout << "Please enter the Pascal source file name (e.g. correct.pas):" << endl;
    char fileName[256];
    cin >> fileName;
    init(fileName);
    if (checkFile()) {
        cout << "File is OK." << endl;
    } else {
        cout << "An error occurred on Line " << currentLine << "." << endl;
    }
}
