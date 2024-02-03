//#include <iostream>
//#include "lex.h"
//#include <map>
//
//
//LexItem id_or_kw(const string& lexeme, int linenum) {
//    map <string, Token> StrToTok = {
//            {"PROGRAM", PROGRAM},
//            {"WRITELN", WRITELN},
//            {"WRITE", WRITE },
//            {"IF", IF },
//            {"ELSE", ELSE },
//            {"IDENT", IDENT },
//            {"VAR", VAR},
//            {"BEGIN", BEGIN},
//            {"END", END},
//            {"end", END},
//            {"INTEGER", INTEGER},
//            {"REAL", REAL},
//            {"STRING", STRING},
//            {"BOOLEAN", BOOLEAN}
//    };
//    if(StrToTok.find(lexeme)!=StrToTok.end()) {
//        Token token = StrToTok[lexeme];
//        return LexItem(token, lexeme, linenum);
//    }
//    else{
//        return LexItem(IDENT, lexeme, linenum);
//    }
//}
//
//ostream& operator<<(ostream& out, const LexItem& tok) {
//    map <Token, string> TokToStr = {
//            {PROGRAM, "PROGRAM"},
//            {WRITELN, "WRITELN"},
//            {WRITE, "WRITE"},
//            {IF, "IF"},
//            {ELSE, "ELSE"},
//            {IDENT, "IDENT"},
//            {VAR, "VAR"},
//            {BEGIN, "BEGIN"},
//            {END, "END"},
//            {INTEGER, "INTEGER"},
//            {REAL, "REAL"},
//            {STRING, "STRING"},
//            {BOOLEAN, "BOOLEAN"},
//            {TRUE, "TRUE"},
//            {FALSE, "FALSE"},
//            {ICONST, "ICONST"},
//            {RCONST, "RCONST"},
//            {SCONST, "SCONST"},
//            {BCONST, "BCONST"},
//            {PLUS, "PLUS"},
//            {MINUS, "MINUS"},
//            {MULT, "MULT"},
//            {DIV, "DIV"},
//            {IDIV, "IDIV"},
//            {ASSOP, "ASSOP"},
//            {EQ, "EQ"},
//            {GTHAN, "GTHAN"},
//            {LTHAN, "LTHAN"},
//            {MOD, "MOD"},
//            {AND, "AND"},
//            {OR, "OR"},
//            {NOT, "NOT"},
//            {COMMA, "COMMA"},
//            {LPAREN, "LPAREN"},
//            {RPAREN, "RPAREN"},
//            {SEMICOL, "SEMICOL"},
//            {DOT, "DOT"},
//            {ERR, "Error"},
//            {DONE, "DONE"},
//    };
//
//    if(tok.GetToken() == IDENT || tok.GetToken() == TRUE || tok.GetToken() == FALSE){
//        out << TokToStr[tok.GetToken()] << ": \"" << tok.GetLexeme() << "\" at line no. " << tok.GetLinenum() << endl;
//    }
//    else if (tok.GetToken() == IF || tok.GetToken() == ELSE || tok.GetToken() == WRITELN || tok.GetToken() == WRITE || tok.GetToken() == INTEGER || tok.GetToken() == REAL || tok.GetToken() == BOOLEAN || tok.GetToken() == STRING || tok.GetToken() == BEGIN || tok.GetToken() == END || tok.GetToken() == VAR || tok.GetToken() == THEN || tok.GetToken() == PROGRAM || tok.GetToken() == PLUS || tok.GetToken() == MINUS || tok.GetToken() == MULT || tok.GetToken() == DIV || tok.GetToken() == IDIV || tok.GetToken() == MOD || tok.GetToken() == ASSOP || tok.GetToken() == EQ || tok.GetToken() == GTHAN || tok.GetToken() == LTHAN || tok.GetToken() == AND || tok.GetToken() == OR || tok.GetToken() == NOT || tok.GetToken() == COMMA || tok.GetToken() == SEMICOL || tok.GetToken() == LPAREN || tok.GetToken() == RPAREN || tok.GetToken() == DOT || tok.GetToken() == COLON) {
//        out << TokToStr[tok.GetToken()] << ": [" << tok.GetLexeme() << "] at line no. " << tok.GetLinenum() << endl;
//    }
//    else if(tok.GetToken() == RCONST || tok.GetToken() == ICONST || tok.GetToken() == BCONST){
//        out << TokToStr[tok.GetToken()] << ": (" << tok.GetLexeme() << ") at line no. " << tok.GetLinenum() << endl;
//    }
//    else if(tok.GetToken() == SCONST){
//        out << TokToStr[tok.GetToken()] << ": \'" << tok.GetLexeme() << "\' at line no. " << tok.GetLinenum() << endl;
//    }
//    else if(tok.GetToken() == ERR){
//        out << TokToStr[tok.GetToken()] << ": {" << tok.GetLexeme() << "} at line no. " << tok.GetLinenum() << endl;
//    }
//    return out;
//}