#include <iostream>
using namespace std;

char lookahead;
long stringsub;

void ParseP();
void ParseD();
void ParseDhi();
void ParseS();
void ParseShi();

char getToken() {
    char inchar;
    inchar = getchar();
//    cout << "inchar>" << inchar << "<end" << endl;
    stringsub += 1;
//    cout << stringsub << endl;
//    cout << "inchar " << inchar << endl;
    string sbegin = "begin";
    string send = "end";
    if (inchar == 'b') {
//        cout << "Might be 'begin'" << endl;
        for (int i = 1; i < 5; i++) {
            inchar = getchar();
            stringsub += 1;
            if (inchar != sbegin[i]) {
                cout << "[error@";
                cout << stringsub;
                cout << "] Do you mean 'begin'? Plz correct the misspelling." << endl;
                exit(0);
            } else {
                if (i == 4) {
                    inchar = 'B';
//                    cout << "yes that's begin." << endl;
                    return 'B';
                }
            }
        }
    } else if (inchar == 'e') {
//        cout << "Might be 'end'" << endl;
        for (int i = 1; i < 3; i++) {
            inchar = getchar();
            if (inchar != send[i]) {
                cout << "[error@";
                cout << stringsub;
                cout << "] Do you mean 'end'? Plz correct the misspelling." << endl;
                exit(0);
            } else {
                if (i == 2) {
                    inchar = 'E';
//                    cout << "yes that's end." << endl;
                    return 'E';
                }
            }
        }
    } else if (inchar == ' ') {
        inchar = getToken();
    } else if (inchar == '\n') {
        return inchar;
    } else if (inchar != ';' && inchar != 's' && inchar != 'd') {
        cout << "[error@";
        cout << stringsub;
        cout << "] Illegal incoming char '";
        cout << inchar;
        cout << "'. Plz check your sentence." << endl;
        exit(0);
    }
    return inchar;
}

void MatchToken(char expected) {
//    cout << lookahead << expected << endl;
//    cout << "lookahead>" << lookahead << "<end" << endl;
//    cout << "expected>" << expected << "<end" << endl;
    if (lookahead != expected) {
        cout << "[error@";
        cout << stringsub;
        cout << "] Illegal coming phase'." << endl;
        exit(0);
    } else {
//        cout << "lookahead>" << lookahead << "<end" << endl;
//        cout << "expected>" << expected << "<end" << endl;
//        cout << "accept" << endl;
        lookahead = getToken();
    }
    return;
}


// ParseP
void ParseP() {
    cout << "P -> begin D S end" << endl;
    if (lookahead == 'B') {             // begin
        MatchToken('B');       // begin
        ParseD();
        ParseS();
//        cout << "lookahead>" << lookahead << "<end" << endl;
        if (lookahead == 'E') {         // end
//            cout << "lookahead>" << lookahead << "<end" << endl;
            MatchToken('E');   // end
        } else {
            cout << "[error@";
            cout << stringsub;
            cout << "] The coming phase should be 'end'." << endl;
            exit(0);
        }
    } else {
        cout << "[error@";
        cout << stringsub;
        cout << "] The coming phase should be 'begin'." << endl;
        exit(0);
    }
    if (lookahead == '\n') {
//        cout << lookahead << endl;
        cout << "[Result] Accepted sentence." << endl;
    }
    else {
//        cout << lookahead << endl;
        cout << "[error@";
        cout << stringsub;
        cout << "] Illegal sentence end." << endl;
    }
}

// ParseD
void ParseD() {
    cout << "D -> dD'" << endl;
    if (lookahead == 'd') {
        MatchToken('d');
        ParseDhi();
    } else {
        cout << "[error@";
        cout << stringsub;
        cout << "] For D, the coming phase should be 'd'." << endl;
        exit(0);
    }
}

// ParseDhi
void ParseDhi() {
    switch(lookahead) {
        case ';': {
            cout << "D' -> ;dD'" << endl;
            if (lookahead == ';') {
                MatchToken(';');
                if (lookahead == 'd') {
                    MatchToken('d');
                    ParseDhi();
                } else {
                    cout << "[error@";
                    cout << stringsub;
                    cout << "] Detected ';', the coming phase should be 'd'." << endl;
                    exit(0);
                }
            } else {
                cout << "[error@";
                cout << stringsub;
                cout << "] The coming phase should be ';'." << endl;
                exit(0);
            }
            break;
        }
        case 's':
            cout << "D' -> epsilon" << endl;
            break;
        default:
            cout << "[error@";
            cout << stringsub;
            cout << "] For D', the coming phase should be ';' or 'd'." << endl;
            exit(0);
    }
}

// ParseS
void ParseS() {
    cout << "S -> sS'" << endl;
    if (lookahead == 's') {
        MatchToken('s');
        ParseShi();
    } else {
        cout << "error S" << endl;
        exit(0);
    }
}

// ParseShi
void ParseShi() {
    switch(lookahead) {
        case ';': {
            cout << "S' -> ;sS'" << endl;
            if (lookahead == ';') {
                MatchToken(';');
                if (lookahead == 's') {
                    MatchToken('s');
                    ParseShi();
                } else {
                    cout << "[error@";
                    cout << stringsub;
                    cout << "] Detected ';', the coming phase should be 's'." << endl;
                    exit(0);
                }
            } else {
                cout << "[error@";
                cout << stringsub;
                cout << "] For S', the coming phase should be ';'." << endl;
                exit(0);
            }
            break;
        }
        case 'E':
            cout << "S' -> epsilon" << endl;
            break;
        default:
            cout << "[error@";
            cout << stringsub;
            cout << "] For S', the coming phase should be ';' or 'end'." << endl;
            exit(0);
    }
//    cout << "end of shi" << endl;
}

int main() {
    stringsub = 0;
    lookahead = getToken();
    ParseP();
    return 0;
}
