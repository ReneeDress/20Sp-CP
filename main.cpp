#include <iostream>
#include <sstream>
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
                cout << "[error@" + to_string(stringsub) + "] Do you mean 'begin'? Plz correct the misspelling." << endl;
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
                cout << "[error@" + to_string(stringsub) + "] Do you mean 'end'? Plz correct the misspelling." << endl;
                exit(0);
            } else {
                if (i == 2) {
                    inchar = 'E';
//                    cout << "yes that's end." << endl;
                    return 'E';
                }
            }
        }
    } else if (inchar != ';' && inchar != 's' && inchar != 'd' && inchar != '\t' && inchar != '\n') {
        cout << "[error@" + to_string(stringsub) + "] Illegal incoming char '";
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
        cout << "[error@" + to_string(stringsub) + "] Illegal coming phase'." << endl;
        exit(0);
    } else {
//        cout << "lookahead>" << lookahead << "<end" << endl;
//        cout << "expected>" << expected << "<end" << endl;
//        cout << "accept" << endl;
        lookahead = getToken();
    }
}


// ParseP
void ParseP() {
    cout << "P -> begin   D   S   end" << endl;
    if (lookahead == 'B') {             // begin
        MatchToken('B');       // begin
        MatchToken('\t');
        ParseD();
        MatchToken('\t');
        ParseS();
        MatchToken('\t');
        if (lookahead == 'E') {         // end
            MatchToken('E');   // end
        } else {
            cout << "[error@" + to_string(stringsub) + "] The coming phase should be 'end'." << endl;
            exit(0);
        }
    } else {
        cout << "[error@" + to_string(stringsub) + "] The coming phase should be 'begin'." << endl;
        exit(0);
    }
    if (lookahead == '\n') {
        cout << "[Result] Accepted sentence." << endl;
    }
    else {
        cout << "[error@" + to_string(stringsub) + "] Illegal sentence end." << endl;
    }
}

// ParseD
void ParseD() {
    cout << "D ->   dD'" << endl;
    if (lookahead == '\t') {
        MatchToken('\t');
        if (lookahead == 'd') {
            MatchToken('d');
            ParseDhi();
        } else {
            cout << "[error@" + to_string(stringsub) + "] Detected '   ', the coming phase should be 'd'." << endl;
            exit(0);
        }
    } else {
        cout << "[error@" + to_string(stringsub) + "] For D, the coming phase should be '  '." << endl;
        exit(0);
    }
}

// ParseDhi
void ParseDhi() {
    switch(lookahead) {
        case ';': {
            cout << "D' -> ;d   D'" << endl;
            if (lookahead == ';') {
                MatchToken(';');
                if (lookahead == 'd') {
                    MatchToken('d');
                    if (lookahead == '\t') {
                        MatchToken('\t');
                        ParseDhi();
                    } else {
                        cout << "[error@" + to_string(stringsub) + "] Detected ';d', the coming phase should be '  '." << endl;
                        exit(0);
                    }
                } else {
                    cout << "[error@" + to_string(stringsub) + "] Detected ';', the coming phase should be 'd'." << endl;
                    exit(0);
                }
            } else {
                cout << "[error@" + to_string(stringsub) + "] The coming phase should be ';'." << endl;
                exit(0);
            }
            break;
        }
        case '\t':
            cout << "D' -> epsilon" << endl;
            break;
        default:
            cout << "[error@" + to_string(stringsub) + "] For D', the coming phase should be ';' or '  '." << endl;
            exit(0);
    }
}

// ParseS
void ParseS() {
    cout << "S ->   sS'" << endl;
    if (lookahead == '\t') {
        MatchToken('\t');
        if (lookahead == 's') {
            MatchToken('s');
            ParseShi();
        } else {
            cout << "[error@" + to_string(stringsub) + "] Detected '   ', the coming phase should be 's'." << endl;
            exit(0);
        }
    } else {
        cout << "[error@" + to_string(stringsub) + "] For S, the coming phase should be '  '." << endl;
        exit(0);
    }
}

// ParseShi
void ParseShi() {
    switch(lookahead) {
        case ';': {
            cout << "S' -> ;s   S'" << endl;
            if (lookahead == ';') {
                MatchToken(';');
                if (lookahead == 's') {
                    MatchToken('s');
                    if (lookahead == '\t') {
                        MatchToken('\t');
                        ParseShi();
                    } else {
                        cout << "[error@" + to_string(stringsub) + "] Detected ';s', the coming phase should be '  '." << endl;
                        exit(0);
                    }
                } else {
                    cout << "[error@" + to_string(stringsub) + "] Detected ';', the coming phase should be 's'." << endl;
                    exit(0);
                }
            } else {
                cout << "[error@" + to_string(stringsub) + "] For S', the coming phase should be ';'." << endl;
                exit(0);
            }
            break;
        }
        case '\t': {
            cout << "S' -> epsilon" << endl;
            break;
        }
        default:
            cout << "[error@" + to_string(stringsub) + "] For S', the coming phase should be ';' or '  '." << endl;
            exit(0);
    }
}

int main() {
    stringsub = 0;
    lookahead = getToken();
    ParseP();
    return 0;
}
