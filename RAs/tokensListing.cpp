//#include <iostream>
//#include <map>
//#include <fstream>
//#include <cctype>
//#include <map>
//#include "lex.h"
///*
//* CS280 - Fall 2023
//*/
//using std::map;
//using namespace std;
//istream& operator>>(istream& in, LexItem& tok) {
//    map <string, Token> StrToTok = {
//            {"PROGRAM", PROGRAM},
//            {"WRITELN", WRITELN},
//            {"WRITE", WRITE },
//            { "IF", IF },
//            { "ELSE", ELSE },
//            { "IDENT", IDENT },
//            {"VAR", VAR},
//            {"BEGIN", BEGIN},
//            {"END", END},
//            {"INTEGER", INTEGER},
//            {"REAL", REAL},
//            {"STRING", STRING},
//            {"BOOLEAN", BOOLEAN},
//            {"TRUE", TRUE},
//            {"FALSE", FALSE},
//            { "ICONST", ICONST },
//            { "RCONST", RCONST },
//            { "SCONST", SCONST },
//            { "BCONST", BCONST },
//            { "PLUS", PLUS },
//            { "MINUS" , MINUS },
//            { "MULT" , MULT },
//            { "DIV" , DIV },
//            { "IDIV" , IDIV },
//            { "ASSOP", ASSOP },
//            { "EQ", EQ },
//            { "GTHAN" , GTHAN },
//            { "LTHAN", LTHAN },
//            { "MOD", MOD},
//            { "AND", AND},
//            { "OR", OR},
//            { "NOT", NOT},
//            { "COMMA", COMMA },
//            { "LPAREN", LPAREN },
//            { "RPAREN", RPAREN },
//            { "SEMICOL", SEMICOL },
//            { "DOT", DOT },
//            { "ERR",ERR },
//            { "DONE", DONE },
//    };
//    Token tt;
//    string tokstr, lexeme, str2;
//    int line, strlen, i;
//    char ch;
//    in >> tokstr ;
//    if(!in)
//    {
//        return in;
//    }
//    auto ttitr = StrToTok.find(tokstr);
////cout << tokstr << endl;
//    if(ttitr != StrToTok.end())
//    {
//        tt = ttitr->second;
//        if(tt == IDENT)
//        {
//            in >> lexeme >> line;
//            tok = id_or_kw(lexeme, line);
//        }
//        else if (tt == ICONST || tt == RCONST )
//        {
//            in >> lexeme >> line;
//            LexItem item(tt, lexeme, line);
//            tok = item;
//        }
//        else if (tt == SCONST)
//        {
//            in >> strlen;
//            str2 = ""; i = 0;
//            ch = in.get();
//            while (ch != '\"')
//            {
//                ch = in.get();
//            }
//            ch = in.get();
//            while ( (ch != '\"') && (i < strlen))
//            {
//                str2 += ch;
//                ch = in.get();
//                i++;
//            }
//            in >> line;
//            LexItem item(tt, str2, line);
//            tok = item;
//        }
//        else
//        {
//            in >> lexeme >> line;
//            LexItem item(tt, lexeme, line);
//            tok = item;
//        }
//    }
//    return in;
//}
//int main(int argc, char *argv[])
//{
//    LexItem item(ERR, "", 0);
//    LexItem& tokItem = item;
//    LexItem kwtok;
//    ifstream file ;
//    string str1;
//    if (argc == 1)
//    {
//        cerr << "NO SPECIFIED INPUT FILE." << endl;
//        return 0;
//    }
//    else
//    {
//        if(argv[1][0] == '-')
//        {
//            cerr << "NO SPECIFIED INPUT FILE." << endl;
//            return 0;
//        }
//        file.open(argv[1]);
//        if( file.is_open() == false ) {
//            cerr << "CANNOT OPEN THE FILE " << argv[1] << endl;
//            return 0;
//        }
//    }
//    while (file >> tokItem)
//    {
//        cout << tokItem; //<< endl;
//    }
//    return 0;
//}