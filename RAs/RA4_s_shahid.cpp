//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <map>
//
//using namespace std;
//
//int main(int argc, char **argv) {
//    int totalLines = 0;
//    string filename;
//    string line;
//    int aboutcnt = 0;
//    int aftercnt = 0;
//    int belowcnt = 0;
//    int forcnt = 0;
//    int fromcnt = 0;
//    int incnt = 0;
//    int intocnt = 0;
//    int undercnt = 0;
//    int withcnt = 0;
//
//    map<string, int> wordCount = {
//        {"about", aboutcnt},
//        {"after", aftercnt},
//        {"below", belowcnt},
//        {"for", forcnt},
//        {"from", fromcnt},
//        {"in", incnt},
//        {"into", intocnt},
//        {"under", undercnt},
//        {"with", withcnt}
//    };
//
//    if (argc == 1){
//        cerr << "NO SPECIFIED INPUT FILE NAME." << filename << endl;
//        exit(1);
//    }
//
//    if (argc == 2) {
//        filename = argv[1];
//        ifstream inClientFile(filename.c_str());
//        if (inClientFile.fail()) {
//            cerr << "CANNOT OPEN THE FILE " << filename << endl;
//            exit(1);
//        }
//        bool anyCounterIncremented = false;
//        while (getline(inClientFile, line)) {
//            totalLines += 1;
//            istringstream iss(line);
//            string word;
//            while (iss >> word) {
//                // Convert the word to lowercase
//                for (char &c : word) {
//                    c = tolower(c);
//                }
//                if (wordCount.find(word) != wordCount.end()) {
//                    wordCount[word]++;
//                    anyCounterIncremented = true;
//                }
//            }
//        }
//        inClientFile.close();
//        if (totalLines == 0) {
//            cerr << "File is empty.";
//            cout << endl;
//            exit(1);
//        }
//        if (!anyCounterIncremented) {
//            cout << "No Preposition words from the given list are found in the file." << endl;
//        }
//        else {
//            cout << "List of Prepositions seen in the file and their number of occurrences:" << endl;
//            cout << endl;
//            int maxCount = 0;
//            string mostFrequentPreposition;
//            for (const auto &pair : wordCount) {
//                if (pair.second > 0) {
//                    cout << pair.first << ": " << pair.second << endl;
//                    if (pair.second > maxCount) {
//                        maxCount = pair.second;
//                        mostFrequentPreposition = pair.first;
//                    }
//                }
//            }
//            if (!mostFrequentPreposition.empty()) {
//                cout << "The preposition with maximum occurrences is \"" << mostFrequentPreposition << "\", which is found " << maxCount << " times." << endl;
//                //cout << endl;
//            }
//        }
//    }
//  return 0;
//}