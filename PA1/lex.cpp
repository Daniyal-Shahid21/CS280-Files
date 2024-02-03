//#include <iostream>
//#include "lex.h"
//#include <map>
//#include <fstream>
//
//enum TokState{
//    START, INID, INSTRING, ININT, INREAL, INCOMMENT ,INCOLON
//};
//
//LexItem id_or_kw(const string& lexeme, int linenum) {
//    map <string, Token> StrToTok = {
//            {"AND", AND},
//            {"PROGRAM", PROGRAM},
//            {"WRITELN", WRITELN},
//            {"WRITE", WRITE },
//            {"IF", IF },
//            {"ELSE", ELSE },
//            {"IDENT", IDENT },
//            {"VAR", VAR},
//            {"BEGIN", BEGIN},
//            {"INTEGER", INTEGER},
//            {"REAL", REAL},
//            {"THEN",THEN},
//            {"STRING", STRING},
//            {"BOOLEAN", BOOLEAN},
//            {"FALSE", BCONST},
//            {"TRUE", BCONST},
//            {"DIV", IDIV},
//            {"MOD", MOD},
//            {"NOT", NOT},
//            {"OR", OR},
//
//    };
//    string uplex = "";
//    for (int i = 0; i < lexeme.length(); i ++){
//        uplex += toupper(lexeme[i]);
//    }
//
//    if(StrToTok.find(uplex)!=StrToTok.end()) {
//        Token token = StrToTok[uplex];
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
//            {THEN, "THEN"},
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
//            {COLON, "COLON"},
//            {LPAREN, "LPAREN"},
//            {RPAREN, "RPAREN"},
//            {SEMICOL, "SEMICOL"},
//            {DOT, "DOT"},
//            {ERR, "Error"},
//            {DONE, "DONE"},
//    };
//
//    if(tok.GetToken() == IDENT || tok.GetToken() == TRUE || tok.GetToken() == FALSE || tok.GetToken() == RCONST
//       || tok.GetToken() == ICONST || tok.GetToken() == BCONST || tok.GetToken() == SCONST){
//        out << TokToStr[tok.GetToken()] << ": \"" << tok.GetLexeme() << "\"";
//    }
//    else if (tok.GetToken() == IF || tok.GetToken() == ELSE || tok.GetToken() == WRITELN || tok.GetToken() == WRITE
//             || tok.GetToken() == INTEGER || tok.GetToken() == REAL || tok.GetToken() == BOOLEAN || tok.GetToken() == STRING
//             || tok.GetToken() == BEGIN || tok.GetToken() == END || tok.GetToken() == VAR || tok.GetToken() == THEN
//             || tok.GetToken() == PROGRAM || tok.GetToken() == PLUS || tok.GetToken() == MINUS || tok.GetToken() == MULT
//             || tok.GetToken() == DIV || tok.GetToken() == IDIV || tok.GetToken() == MOD || tok.GetToken() == ASSOP
//             || tok.GetToken() == EQ || tok.GetToken() == GTHAN || tok.GetToken() == LTHAN || tok.GetToken() == AND
//             || tok.GetToken() == OR || tok.GetToken() == NOT || tok.GetToken() == COMMA || tok.GetToken() == SEMICOL
//             || tok.GetToken() == LPAREN || tok.GetToken() == RPAREN || tok.GetToken() == DOT || tok.GetToken() == COLON) {
//        out << TokToStr[tok.GetToken()];
//    }
//    else if(tok.GetToken() == ERR){
//        out << "Error in line " << tok.GetLinenum()+1 << ": Unrecognized Lexeme {" << tok.GetLexeme() << "}";
//    }
//    else if (tok.GetToken() == DONE){
//        out << TokToStr[tok.GetToken()] << ": at line no. " << tok.GetLinenum() << endl;
//    }
//    return out;
//}
//
//LexItem getNextToken(istream& in, int& linenum){
//    TokState lexstate = START;
//    char c;
//    string stored;
//    while (in.get(c)) {
//        if ((lexstate == INCOMMENT || lexstate == START) && in.peek() == ifstream::traits_type::eof()){
//            linenum += 1;
//            LexItem lexy = LexItem(DONE, stored, linenum);
//            return lexy;
//        }
//        if (lexstate == START) {
//            if (isalpha(c)) {
//                lexstate = INID;
//                stored = stored + c;
//            }
//            else if (isdigit(c)){
//                lexstate = ININT;
//                stored = stored + c;
//            }
//            else if (c == ' ' || c == '\t' || c == '\r'){
//                continue;
//            }
//            else if (c == '\''){
//                lexstate = INSTRING;
//                stored = stored + c;
//            }
//            else if (c == '{'){
//                lexstate = INCOMMENT;
//                stored = stored + c;
//            }
//            else if (c == ':') {
//                lexstate = INCOLON;
//                stored = stored + c;
//            }
//            else if (c == '.'){
//                stored = stored + c;
//                LexItem lexy = LexItem(DOT, stored, linenum);
//                return lexy;
//            }
//            else if (c == ')'){
//                stored = stored + c;
//                LexItem lexy = LexItem(RPAREN, stored, linenum);
//                return lexy;
//            }
//            else if (c == '('){
//                stored = stored + c;
//                LexItem lexy = LexItem(LPAREN, stored, linenum);
//                return lexy;
//            }
//            else if (c == ';'){
//                stored = stored + c;
//                LexItem lexy = LexItem(SEMICOL, stored, linenum);
//                return lexy;
//            }
//            else if (c == ','){
//                stored = stored + c;
//                LexItem lexy = LexItem(COMMA, stored, linenum);
//                return lexy;
//            }
//            else if (c == '>'){
//                stored = stored + c;
//                LexItem lexy = LexItem(GTHAN, stored, linenum);
//                return lexy;
//            }
//            else if (c == '<'){
//                stored = stored + c;
//                LexItem lexy = LexItem(LTHAN, stored, linenum);
//                return lexy;
//            }
//            else if (c == '='){
//                stored = stored + c;
//                LexItem lexy = LexItem(EQ, stored, linenum);
//                return lexy;
//            }
//            else if (c == '*'){
//                stored = stored + c;
//                LexItem lexy = LexItem(MULT, stored, linenum);
//                return lexy;
//            }
//            else if (c == '/'){
//                stored = stored + c;
//                LexItem lexy = LexItem(DIV, stored, linenum);
//                return lexy;
//            }
//            else if (c == '-'){
//                stored = stored + c;
//                LexItem lexy = LexItem(MINUS, stored, linenum);
//                return lexy;
//            }
//            else if (c == '+'){
//                stored = stored + c;
//                LexItem lexy = LexItem(PLUS, stored, linenum);
//                return lexy;
//            }
//
//            else if (c == '\n') {
//                linenum += 1;
//            }
//
//            else if (in.peek() == ifstream::traits_type::eof()){
//                LexItem lexy = LexItem(DONE, stored, linenum);
//                return lexy;
//            }
//            else {
//                stored = stored + c;
//                LexItem lexy = LexItem(ERR, stored, linenum);
//                return lexy;
//            }
//
//        }
//        else if (lexstate == INCOLON){
//            if (c == '='){
//                stored = stored + c;
//                LexItem lexy = LexItem(ASSOP, stored, linenum);
//                return lexy;
//            }
//            else{
//                in.putback(c);
//                LexItem lexy = LexItem(COLON, stored, linenum);
//                return lexy;
//            }
//        }
//
//        else if (lexstate == INID){
//            if (!(isalpha(c) || isdigit(c) || c == '_' || c == '$')){
//                in.putback(c);
//                return (id_or_kw(stored, linenum));
//            }
//            else {
//                stored = stored + c;
//            }
//        }
//        else if (lexstate == INSTRING){
//            if (c == '\''){
//                stored = stored.substr(1, stored.size()-1);
//                LexItem lexy = LexItem(SCONST, stored, linenum);
//                return lexy;
//            }
//            else if (c == '\n'){
//                LexItem lexy = LexItem(ERR, stored, linenum);
//                return lexy;
//            }
//            else {
//                stored = stored + c;
//            }
//        }
//
//        else if (lexstate == ININT){
//            if (c == '.'){
//                stored = stored + c;
//                lexstate = INREAL;
//            }
//            else if (!(isdigit(c))){
//                in.putback(c);
//                LexItem lexy = LexItem(ICONST, stored, linenum);
//                return lexy;
//            }
//            else {
//                stored = stored + c;
//            }
//        }
//
//
//        else if (lexstate == INREAL){
//            if (c == '.'){
//                stored = stored + c;
//                LexItem lexy = LexItem(ERR, stored, linenum);
//                return lexy;
//            }
//
//            else if (!(isdigit(c))){
//                in.putback(c);
//                LexItem lexy = LexItem(RCONST, stored, linenum);
//                return lexy;
//            }
//
//            else {
//                stored = stored + c;
//            }
//
//
//        }
//        else if (lexstate == INCOMMENT) {
//            if (c == '}') {
//                lexstate = START;
//                stored.clear(); // Clear the comment content
//            }
//                // Add the following line to ignore all characters inside the comment:
//            else if (c == '\n') {
//                linenum += 1;
//            }
//        }
//
//    }
//    return LexItem();
//}