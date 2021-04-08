#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
using namespace std;

void toUppercase(string & srcStr) {
//    cout << srcStr << endl;
    for (int i = 0; i < srcStr.length(); i++) {
        if (srcStr[i] >= 'a' && srcStr[i] <= 'z') {
            srcStr[i] -= 32;
        }
    }
//    cout << srcStr << endl;
    return;
}

void changePhases(string & srcStr, string phases[31][2]) {
    srcStr = srcStr.replace(srcStr.find('\r'), 1, "");
    for (int i = 0; i < 31; i++) {
        int pos = 0;
        string subStr = srcStr.substr(pos, srcStr.length());
//        cout << "origin " << subStr << endl;
        while (pos < srcStr.length() && pos > -1) {
            subStr = srcStr.substr(pos, srcStr.length());
//            cout << "find " << phases[i][0] << endl;
//            cout << subStr << endl;
//            cout << subStr.length() << endl;
            int subPos =  subStr.find(phases[i][0]);
//            cout << "pos " << pos + subPos << endl;
            if (subPos < subStr.length() && subPos > -1) {
                srcStr = srcStr.replace(pos + subPos, phases[i][0].length(), ' ' + phases[i][1] + ' ');
//                cout << "after replace /" << srcStr << endl;
                pos += subPos + phases[i][1].length() + 2;
                continue;
            }
            break;
        }
    }
    return;
}

string lab1(stringstream & changedFile, string phases[31][2]);
string lab2(stringstream & changedFile, string phases[31][2]);

int readCase(string path) {
//    cout << path << endl;
    string phases[31][2] = {
            {"BEGIN",       "BEGINSYM"},
            {"CALL",        "CALLSYM"},
            {"CONST",       "CONSTSYM"},
            {"DO",          "DOSYM"},
            {"END",         "ENDSYM"},
            {"IF",          "IFSYM"},
            {"ODD",         "ODDSYM"},
            {"PROCEDURE",   "PROCEDURESYM"},
            {"READ",        "READSYM"},
            {"THEN",        "THENSYM"},
            {"VAR",         "VARSYM"},
            {"WHILE",       "WHILESYM"},
            {"WRITE",       "WRITESYM"},
            {"ELSE",        "ELSESYM"},     // ELSE

            {"<=",  "LEQ"},
            {">=",  "GEQ"},
            {":=",  "BECOMES"},

            {"+",   "PLUS"},
            {"-",   "MIUNS"},
            {"*",   "TIMES"},
            {"/",   "SLASH"},
            {"=",   "EQL"},
            {"#",   "NEQ"},
            {"<",   "LSS"},
            {">",   "GTR"},
            {"(",   "LPAREN"},
            {")",   "RPAREN"},
            {",",   "COMMA"},
            {";",   "SEMICOLON"},
            {".",   "PERIOD"},

            {"®",   "REGISTED"},
    };

    ifstream caseFile;
    char data[256];
    string strFile;
    stringstream ssFile;

    caseFile.open(path);
//    ssFile << caseFile;
    if (!caseFile.is_open()) {
        cout << "error" << endl;
    } else {
        while (getline(caseFile, strFile)) {
            if (strFile.empty() || strFile == "\r") continue;
            toUppercase(strFile);
//            cout << strFile << endl;
            changePhases(strFile, phases);
            ssFile << strFile << endl;
        }
    }

    string input;
    cout << "请选择实验（1/2）：";
    cin >> input;
    if (input == "1") {
//        cout << ssFile.str() << endl;
        string fo = lab1(ssFile, phases);
        string outpath = path.replace(path.find(".txt"), 4, "lab1out.txt");
        ofstream fileOut(outpath);
        fileOut << fo;
        fileOut.flush();
        fileOut.close();
    } else if (input == "2") {
//        cout << ssFile.str() << endl;
        string fo2 = lab2(ssFile, phases);
        string outpath = path.replace(path.find(".txt"), 4, "lab2out.txt");
        ofstream fileOut(outpath);
        fileOut << fo2;
        fileOut.flush();
        fileOut.close();
    } else {
        cout << "请重新输入。" << endl;
        return 1;
    }
    caseFile.close();
    return 0;
}

string lab1(stringstream & changedFile, string phases[31][2]) {
//    cout << changedFile.str() << endl;
    string res[1024] = {""};
    int i = 0;
    int cnt = 0;
    while (!changedFile.eof()) {
        string temp = "";
        changedFile >> temp;
//        cout << phase[i] << endl;
        for (int k = 0; k < 31 ; k++) {
            if (temp == phases[k][1]) {
//                cout << temp << " is phase" << endl;
                break;
            } else if (k == 31 - 1 && temp != phases[k][0] && temp != ""
                        && temp[0] != '0' && temp[0] != '1' && temp[0] != '2' && temp[0] != '3' && temp[0] != '4'
                        && temp[0] != '5' && temp[0] != '6' && temp[0] != '7' && temp[0] != '8' && temp[0] != '9') {
                res[i] = temp;
//                cout << temp << " is ident/number" << endl;
                cnt++;
            }
        }
        i++;
    }
//    cout << cnt << endl;
    string * resIN = new string[cnt];
    int p = 0;
    for (int j = 0; j < 1024; j++) {
        if (res[j] != "") {
            resIN[p] = res[j];
//            cout << resIN[p] << " ";
            p++;
        }
    }
//    cout << endl;
    for (int bi = 0; bi < cnt; bi ++) {
        for (int bb = 0; bb < cnt - 1; bb ++) {
            string bbtemp;
            if (resIN[bb] > resIN[bb + 1]) {
                bbtemp = resIN[bb];
                resIN[bb] = resIN[bb + 1];
                resIN[bb + 1] = bbtemp;
            }
        }
    }
//    for (int bb = 0; bb < cnt; bb ++) {
//        cout << resIN[bb] << " ";
//    }
//    cout << endl;

    stringstream fOut;
    int last = 0;
    for (int bb = 1; bb < cnt + 1; bb ++) {
        if (resIN[bb] != resIN[bb - 1]) {
//            cout << "(" << resIN[bb - 1] << ": " << bb - last << ")" << endl;
            fOut << "(" << resIN[bb - 1] << ": " << bb - last << ")" << endl;
            last = bb;
        }
    }
    cout << fOut.str();
    return fOut.str();
}

string lab2(stringstream & changedFile, string phases[31][2]) {
//    cout << changedFile.str() << endl;
    string res[1024] = {""};
    int i = 0;
    stringstream resSS;
    while (!changedFile.eof()) {
        string temp = "";
        changedFile >> temp;
//        cout << temp << endl;
        for (int k = 0; k < 31 ; k++) {
            if (temp[0] == '0' || temp[0] == '1' || temp[0] == '2' || temp[0] == '3' || temp[0] == '4'
                || temp[0] == '5' || temp[0] == '6' || temp[0] == '7' || temp[0] == '8' || temp[0] == '9') {
                res[i] = temp;
//                cout << temp << " is number" << endl;
//                cout << "(number,\t" << temp << ")" << endl;
                resSS << "(number,\t" << temp << ")" << endl;
                break;
            } else {
                if (temp == phases[k][1]) {
                    res[i] = temp;
//                    cout << temp << " is phase " << phases[k][0] << endl;
                    if (temp.length() < 6) {
//                        cout << "(" << temp << ",\t\t" << phases[k][0] << ")" << endl;
                        resSS << "(" << temp << ",\t\t" << phases[k][0] << ")" << endl;
                    }
                    else {
//                        cout << "(" << temp << ",\t" << phases[k][0] << ")" << endl;
                        resSS << "(" << temp << ",\t" << phases[k][0] << ")" << endl;
                    }
                    break;
                } else if (temp != "" && k == 31 - 1) {
                    res[i] = temp;
//                    cout << temp << " is ident" << endl;
//                    cout << "(ident,\t\t" << temp << ")" << endl;
                    resSS << "(ident,\t\t" << temp << ")" << endl;
                    break;
                }
            }
        }
        i++;
    }
    cout << resSS.str();
    return resSS.str();
}

int main() {
    char * buffer;
    if ((buffer = getcwd(NULL, 0)) == NULL) {
        perror("getcwd error");
    } else {
//        printf("%s\n", buffer);
        free(buffer);
    }
    string filePath = "../case01.txt";
    while (1) {
        cout << "请输入测试文件名：";
        cin >> filePath;
        if (filePath == "exit") break;
        filePath = "../" + filePath;
        readCase(filePath);
    }
    cout << "Hello, World!" << endl;
    return 0;
}
