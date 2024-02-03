//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "lex.h"
//#include <set>
//#include <vector>
//#include <cstring>
//
//using namespace std;
//
//int main (int argc, char **argv) {
//    string filename;
//    int counter = 0;
//    int vindex = 0;
//    int nindex = 0;
//    int sindex = 0;
//    int bindex = 0;
//    int iindex = 0;
//    int fileindex = 0;
//    int filecount = 0;
//    int linenum = 0;
//
//    set <double> numset;
//    set <string> identset;
//    set <string> boolset;
//    set <string> stringset;
//    vector <LexItem> lexvector;
//
//    ifstream inClientFile;
//
//    for (int i = 1; i < argc; i++) {
//        if (argv[i][0] == '-') {
//            if (strcmp(argv[i], "-v") == 0) {
//                vindex = i;
//            }
//            else if (strcmp(argv[i], "-nconst") == 0) {
//                nindex = i;
//            }
//            else if (strcmp(argv[i], "-sconst") == 0) {
//                sindex = i;
//            }
//            else if (strcmp(argv[i], "-bconst") == 0) {
//                bindex = i;
//            }
//            else if (strcmp(argv[i], "-ident") == 0) {
//                iindex = i;
//            }
//            else {
//                cerr << "UNRECOGNIZED FLAG {" << argv[i] << "}" << endl;
//                exit(1);
//            }
//            counter += 1;
//        }
//        else {
//            filecount += 1;
//            fileindex = i;
//        }
//    }
//
//    if (filecount > 1){
//        cerr << "ONLY ONE FILE NAME IS ALLOWED." << endl;
//        exit(1);
//    }
//
//    else if (argc == 1 || (argc - 1) == counter) {
//        cerr << "NO SPECIFIED INPUT FILE." << endl;
//        exit(1);
//    }
//
//    else if (argc == 2) {
//        filename = argv[1];
//        inClientFile.open(filename.c_str());
//        if (inClientFile.fail()) {
//            cerr << "CANNOT OPEN THE FILE " << filename << endl;
//            exit(1);
//        }
//        else if (inClientFile.peek() == ifstream::traits_type::eof()) {
//            cerr << "Empty File.";
//            cout << endl;
//            exit(1);
//        }
//        else {
//            int j = 0;
//            int nowork = 0;
//            while (inClientFile.peek() != ifstream::traits_type::eof()){
//                lexvector.push_back(getNextToken(inClientFile, linenum));
//                if (lexvector[j].GetToken() == DONE){
//                    lexvector.pop_back();
//                    break;
//                }
//                if (lexvector[j].GetToken() == ERR){
//                    nowork = 5;
//                    break;
//                }
//                if (lexvector[j].GetToken() == IDENT){
//                    identset.insert(lexvector[j].GetLexeme());
//                }
//                else if (lexvector[j].GetToken() == RCONST || lexvector[j].GetToken() == ICONST){
//                    numset.insert(stod(lexvector[j].GetLexeme()));
//                }
//                else if (lexvector[j].GetToken() == BCONST){
//                    boolset.insert(lexvector[j].GetLexeme());
//                }
//                else if (lexvector[j].GetToken() == SCONST){
//                    stringset.insert(lexvector[j].GetLexeme());
//                }
//                j += 1;
//            }
//            if (nowork != 5) {
//                cout << endl;
//                cout << "Lines: " << linenum << endl;
//                cout << "Total Tokens: " << lexvector.size()<< endl;
//                cout << "Identifiers: " << identset.size() << endl;
//                cout << "Numbers: " << numset.size() << endl;
//                cout << "Booleans: " << boolset.size() << endl;
//                cout << "Strings: " << stringset.size() << endl;
//            }
//        }
//    }
//
//    else if (argc > 2){
//        filename = argv[fileindex];
//        inClientFile.open(filename.c_str());
//        if (inClientFile.fail()) {
//            cerr << "CANNOT OPEN THE FILE " << filename << endl;
//            exit(1);
//        }
//        else if (inClientFile.peek() == ifstream::traits_type::eof()) {
//            cerr << "Empty File.";
//            cout << endl;
//            exit(1);
//        }
//        int j = 0;
//        int nowork = 0;
//        while (inClientFile.peek() != ifstream::traits_type::eof()){
//            lexvector.push_back(getNextToken(inClientFile, linenum));
//            if (lexvector[j].GetToken() == DONE){
//                lexvector.pop_back();
//                break;
//            }
//            if (lexvector[j].GetToken() == ERR){
//                nowork = 5;
//                break;
//            }
//            if (lexvector[j].GetToken() == IDENT){
//                identset.insert(lexvector[j].GetLexeme());
//            }
//            else if (lexvector[j].GetToken() == RCONST || lexvector[j].GetToken() == ICONST){
//                numset.insert(stod(lexvector[j].GetLexeme()));
//            }
//            else if (lexvector[j].GetToken() == BCONST){
//                boolset.insert(lexvector[j].GetLexeme());
//            }
//            else if (lexvector[j].GetToken() == SCONST){
//                stringset.insert(lexvector[j].GetLexeme());
//            }
//            j += 1;
//        }
//        if (vindex > 0){
//            for (int i = 0; i < lexvector.size(); i++) {
//                if (lexvector[i].GetToken() == ERR) {
//                    cout << lexvector[i];
//                }
//                else {
//                    cout << lexvector[i] << endl;
//                }
//            }
//        }
//        cout << endl;
//        if (nowork != 5) {
//            cout << "Lines: " << linenum << endl;
//            cout << "Total Tokens: " << lexvector.size() << endl;
//            cout << "Identifiers: " << identset.size() << endl;
//            cout << "Numbers: " << numset.size() << endl;
//            cout << "Booleans: " << boolset.size() << endl;
//            cout << "Strings: " << stringset.size() << endl;
//        }
//        if (iindex > 0 && nowork != 5){
//            cout << "IDENTIFIERS:" << endl;
//            set<string>::iterator itr = identset.begin();
//            while (itr != identset.end()) {
//                cout << *itr;
//                ++itr;
//                if (itr != identset.end()) {
//                    cout << ", ";
//                }
//            }
//            cout << endl; // Print a newline character at the end
//        }
//
//        if (nindex > 0 && nowork != 5){
//            cout << "NUMBERS:" << endl;
//            set<double>::iterator itr;
//            for (itr = numset.begin(); itr != numset.end(); itr++) {
//                cout << *itr << endl;
//            }
//        }
//
//        if (bindex > 0 && nowork != 5){
//            cout << "BOOLEANS:" << endl;
//            set<string>::iterator itr;
//            for (itr = boolset.begin(); itr != boolset.end(); itr++) {
//                cout << *itr << endl;
//            }
//        }
//
//        if (sindex > 0 && nowork != 5){
//            cout << "STRINGS:" << endl;
//            set<string>::iterator itr;
//            for (itr = stringset.begin(); itr != stringset.end(); itr++) {
//                cout << "\"" << *itr << "\"" << endl;
//            }
//        }
//    }
//}