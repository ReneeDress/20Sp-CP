#include <iostream>
using namespace std;

string lookahead;
long stringsub;

long currentValue;

string getToken();
void MatchToken(string expected);

void ParseS();
long ParseE();
long ParseR(long Rin);
long ParseT();
long ParseP(long Pin);
long ParseD();

string getToken() {
    char inchar;
    inchar = getchar();
//    cout << "inchar>" << inchar << "<inchar" << endl;
    stringsub += 1;
    switch(inchar) {
        case '+': {
            return "plus";
        }
        case '-': {
            return "minus";
        }
        case '*': {
            return "times";
        }
        case '/': {
            return "slash";
        }
        case '(': {
            return "lparen";
        }
        case ')': {
            return "rparen";
        }
        case '\n': {
            return "END";
        }
        case ' ': {
            return getToken();
        }
        default: {
            if (inchar >= 48 && inchar <= 57) {
                long value = 0;
//                cout << inchar << ": " << long(inchar - 48) << endl;
                value = long(inchar - 48);
                inchar = getchar();
                stringsub += 1;
                while (inchar) {
                    if (inchar >= 48 && inchar <= 57) {
                        value = value * 10 + long(inchar - 48);
                        inchar = getchar();
                        stringsub += 1;
                    }
                    else if (inchar == '+' || inchar == '-' || inchar == '*' || inchar == '/' || inchar == '(' || inchar == ')' || inchar == '\n' || inchar == ' ') {
                        ungetc(inchar, stdin);
                        stringsub -= 1;
                        currentValue = value;
//                        cout << to_string(value) << endl;
                        return "number";
                    } else {
                        cout << "[error@" + to_string(stringsub) + "] Illegal coming char after number." << endl;
                        exit(0);
                    }
                }
            } else if (inchar >= 'A' && inchar <= 'z') {
                string identname;
                identname += inchar;
                inchar = getchar();
                stringsub += 1;
                while (inchar) {
                    if ((inchar >= 48 && inchar <= 57) || (inchar >= 'A' && inchar <= 'z')) {
                        identname += inchar;
                        inchar = getchar();
                        stringsub += 1;
                    }
                    else if (inchar == '+' || inchar == '-' || inchar == '*' || inchar == '/' || inchar == '(' || inchar == ')' || inchar == '\n' || inchar == ' ') {
                        ungetc(inchar, stdin);
                        stringsub -= 1;
//                        cout << identname << endl;
                        return "ident";
                    } else {
                        cout << "[error@" + to_string(stringsub) + "] Illegal coming char after number." << endl;
                        exit(0);
                    }
                }
            } else {
                cout << "[error@" + to_string(stringsub) + "] Illegal coming char." << endl;
                exit(0);
            }
        }
    }
}

void MatchToken(string expected) {
    if (lookahead != expected) {
        cout << "[error@" + to_string(stringsub) + "] Illegal coming phase'." << endl;
        exit(0);
    } else {
        lookahead = getToken();
    }
}

void ParseS() {
    cout << "S -> E" << endl;
    long Ev;
    Ev = ParseE();
    cout << "[Result] " << to_string(Ev) << "." << endl;
}

long ParseE() {
    long Tv;
    long Rin;
    long Ev;
    long Rv;
    cout << "E -> TR" << endl;
    Tv =  ParseT();
    Rin = Tv;
    Rv = ParseR(Rin);
    Ev = Rv;
    return Ev;
}

long ParseR(long Rin) {
    long Rv;
    long R1v;
    long Tv;
    long R1in;
    if (lookahead == "plus") {
        cout << "R -> +TR" << endl;
        MatchToken("plus");
        Tv = ParseT();
        R1in = Rin + Tv;
        R1v = ParseR(R1in);
        Rv = R1v;
        return Rv;
    } else if (lookahead == "minus") {
        cout << "R -> -TR" << endl;
        MatchToken("minus");
        Tv = ParseT();
        R1in = Rin - Tv;
        R1v = ParseR(R1in);
        Rv = R1v;
        return Rv;
    } else if (lookahead != "plus" && lookahead != "minus") {
        cout << "R -> epsilon" << endl;
        Rv = Rin;
        return Rv;
    }
}

long ParseT() {
    long Dv;
    long Pin;
    long Pv;
    long Tv;
    cout << "T -> DP" << endl;
    Dv = ParseD();
    Pin = Dv;
    Pv = ParseP(Pin);
    Tv = Pv;
    return Tv;
}

long ParseP(long Pin) {
    long Pv;
    long P1v;
    long Dv;
    long P1in;
    if (lookahead == "times") {
        cout << "P -> *DP" << endl;
        MatchToken("times");
        Dv = ParseD();
        P1in = Pin * Dv;
        P1v = ParseP(P1in);
        Pv = P1v;
        return Pv;
    } else if (lookahead == "slash") {
        cout << "P -> /DP" << endl;
        MatchToken("slash");
        Dv = ParseD();
        if (Dv == 0) {
            cout << "[error@" << stringsub << "] Cannot do slash 0." << endl;
        }
        P1in = Pin / Dv;
        P1v = ParseP(P1in);
        Pv = P1v;
        return Pv;
    } else if (lookahead != "times" && lookahead != "slash") {
        cout << "P -> epsilon" << endl;
        Pv = Pin;
        return Pv;
    }
}

long ParseD() {
    long Dv;
    if (lookahead == "lparen") {
        cout << "D -> (E)" << endl;
        MatchToken("lparen");
        Dv = ParseE();
        if (lookahead == "rparen") {
            MatchToken("rparen");
            return Dv;
        } else {
            cout << "[error@" + to_string(stringsub) + "] Detected '(E', the coming phase should be ')'." << endl;
            exit(0);
        }
    } else if (lookahead == "ident") {
        cout << "D -> ident" << endl;

        cout << "[error@" + to_string(stringsub) + "] Cannot do caculation with ident." << endl;
        exit(0);

        MatchToken("ident");
    } else if (lookahead == "number") {
        cout << "D -> number" << endl;
        MatchToken("number");
//        cout << to_string(currentValue) << endl;
        Dv = currentValue;
        return Dv;
    } else {
        cout << "[error@" + to_string(stringsub) + "] For D, the coming phase should be an ident or a number." << endl;
        exit(0);
    }
}


int main() {
    stringsub = 0;
    lookahead = getToken();
    ParseS();
    return 0;
}
