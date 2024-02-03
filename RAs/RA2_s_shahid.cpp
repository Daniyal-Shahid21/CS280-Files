//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//
//using namespace std;
//
//int main() {
////    ifstream inClientFile;
//
//    string filename;
//    // if a filename is provided, open file
//    cout << "Enter the name of a file to read from:" << endl;
//    cin >> filename;
//    cout << endl;
//
//    ifstream inClientFile(filename.c_str());
//    if (inClientFile.fail()) {
//        cerr << endl;
//        cerr << "File cannot be opened " << filename << endl;
//        exit(1);
//    }
//
//    int totalLines = 0;
//    int commentedLines = 0;
//    int numWords = 0;
//    int boldCmds = 0;
//    int italicCmds = 0;
//    int regCmds = 0;
//    string line;
//    string itallics = "//";
//    string pound = "##";
//    string words[3] = {"bold", "regular", "italic"};
//
//    // display each record in file
//
//
//    while (getline(inClientFile, line)) {
//        totalLines += 1;
//        if (line.substr(0,2) == itallics){
//            commentedLines += 1;
//        }
//        else if (line.substr(0,2) == pound){
//            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
//            transform(line.begin(), line.end(), line.begin(), [](unsigned char c){return tolower(c);});
//            if (line.substr(2,4) == words[0]){
//                boldCmds += 1;
//            }
//            else if (line.substr(2,7) == words[1]){
//                regCmds +=1;
//            }
//            else if ((line.substr(2,6) == words[2])){
//                italicCmds += 1;
//            }
//            else{
//                cerr << "Error: Unrecognizable command in line " << totalLines << endl;
//                cout << endl;
//            }
//        }
//        else {
//            istringstream iss(line);
//            string word;
//            while (iss >> word) {
//                numWords += 1;
//            }
//        }
//    }
//    inClientFile.close();
//    if (totalLines == 0){
//        cerr << "File is Empty";
//        cout << endl;
//        exit(1);
//    }
//    cout << "Total lines: " << totalLines << "\n";
//    cout << "Commented lines: " << commentedLines << "\n";
//    cout << "Number of words in the Text to be formatted: " << numWords << "\n";
//    cout << "Bold commands: " << boldCmds << "\n";
//    cout << "Italic commands: " << italicCmds << "\n";
//    cout << "Regular commands: " << regCmds << "\n";
//    return 0;
//}