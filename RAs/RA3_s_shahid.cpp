//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <regex>
//
//using namespace std;
//
//int main(int argc, char **argv) {
//    regex numeric ("^((?!.*(_){2,})[_|@][a-zA-Z][0-9a-zA-Z_]+)$");
//    int totalW = 0;
//    int totalSp = 0;
//    int totalLines = 0;
//    string keyword;
//    string filename;
//    string line;
//    if (argc == 1){
//        cerr << "NO SPECIFIED INPUT FILE NAME." << filename << endl;
//        exit(1);
//    }
//
//    else if (argc == 2){
//        filename = argv[1];
//        ifstream inClientFile(filename.c_str());
//        if (inClientFile.fail()) {
//            cerr << "CANNOT OPEN THE FILE " << filename << endl;
//            exit(1);
//        }
//        while (getline(inClientFile, line)) {
//            totalLines += 1;
//            istringstream iss(line);
//            string word;
//            while (iss >> word) {
//                totalW += 1;
//            }
//        }
//        inClientFile.close();
//        if (totalLines == 0){
//            cerr << "File is empty.";
//            cout << endl;
//            exit(1);
//        }
//        cout << "Total number of words: " << totalW << "\n";
//    }
//
//    else {
//        filename = argv[1];
//        ifstream inClientFile(filename.c_str());
//        if (inClientFile.fail()) {
//            //cerr << endl;
//            cerr << "CANNOT OPEN THE FILE " << filename << endl;
//            exit(1);
//        }
//        keyword = argv[2];
//        if (keyword == "-all") {
//            while (getline(inClientFile, line)) {
//                totalLines += 1;
//                istringstream iss(line);
//                string word;
//                while (iss >> word) {
//                    totalW += 1;
//                    if (regex_match(word, numeric)){
//                        totalSp += 1;
//                    }
//                }
//            }
//            inClientFile.close();
//            if (totalLines == 0){
//                cerr << "File is Empty";
//                cout << endl;
//                exit(1);
//            }
//            else{
//                cout << "Total number of words: " << totalW << "\n";
//                cout << "Total number of special names: " << totalSp << "\n";
//            }
//        }
//
//        else if (keyword == "-sp") {
//            while (getline(inClientFile, line)) {
//                totalLines += 1;
//                istringstream iss(line);
//                string word;
//                while (iss >> word) {
//                    if (regex_match(word, numeric)){
//                        totalSp += 1;
//                    }
//                }
//            }
//            inClientFile.close();
//            if (totalLines == 0){
//                cerr << "File is Empty";
//                cout << endl;
//                exit(1);
//            }
//            else{
//                cout << "Total number of special names: " << totalSp << "\n";
//            }
//
//        }
//        else{
//            cerr << "UNRECOGNIZED FLAG " << keyword << endl;
//            exit(1);
//        }
//    }
//    return 0;
//}