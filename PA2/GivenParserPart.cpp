//#include "parser.h"
//#include <map>
//
//map<string, bool> defVar;
//map<string, Token> SymTable;
//
//namespace Parser {
//    bool pushed_back = false;
//    LexItem	pushed_token;
//    static LexItem GetNextToken(istream& in, int& line) {
//        if (pushed_back) {
//            pushed_back = false;
//            return pushed_token;
//        }
//        return getNextToken(in, line);
//    }
//
//    static void PushBackToken(LexItem & t) {
//        if(pushed_back) {
//            abort();
//        }
//        pushed_back = true;
//        pushed_token = t;
//    }
//}
//
//static int error_count = 0;
//int ErrCount(){
//    return error_count;
//}
//
//void ParseError(int line, string msg){
//    ++error_count;
//    cout << line << ": " << msg << endl;
//}
//
//// Prog ::= PROGRAM IDENT ; DeclPart CompoundStmt .
//bool Prog(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//
//    // Check for PROGRAM keyword
//    if (t != PROGRAM) {
//        ParseError(line, "Missing PROGRAM keyword");
//        return false;
//    }
//
//    // Check for IDENT
//    t = Parser::GetNextToken(in, line);
//    if (t != IDENT) {
//        ParseError(line, "Missing program identifier");
//        return false;
//    }
//
//    // Check for semicolon
//    t = Parser::GetNextToken(in, line);
//    if (t != SEMICOL) {
//        ParseError(line, "Missing semicolon after program identifier");
//        return false;
//    }
//
//    // Parse DeclPart
//    if (!DeclPart(in, line)) {
//        ParseError(line, "Error in DeclPart");
//        return false;
//    }
//
//    // Parse CompoundStmt
//    if (!CompoundStmt(in, line)) {
//        ParseError(line, "Error in CompoundStmt");
//        return false;
//    }
//
//    // Check for period
//    t = Parser::GetNextToken(in, line);
//    if (t == END){
//        return true;
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    return true;
//}
//
//// DeclPart ::= VAR DeclStmt; { DeclStmt ; }
//bool DeclPart(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check for VAR keyword
//    if (t != VAR) {
//        ParseError(line, "Missing VAR keyword in DeclPart");
//        return false;
//    }
//
//    // Parse the first DeclStmt
//    if (!DeclStmt(in, line)) {
//        ParseError(line, "Error in first DeclStmt");
//        return false;
//    }
//
//    // Check for semicolon after the first DeclStmt
//    t = Parser::GetNextToken(in, line);
//    if (t != SEMICOL) {
//        ParseError(line, "Missing semicolon after the first DeclStmt");
//        return false;
//    }
//
//    t = Parser::GetNextToken(in, line);
//    // Parse additional DeclStmts with optional semicolons
//    while (true) {
//        // Parse the next DeclStmt
//        if (t == IDENT) {
//            Parser::PushBackToken(t);
//            if (!(DeclStmt(in, line))){
//                ParseError(line, "Error in DeclStmt");
//                return false;
//            }
//            t = Parser::GetNextToken(in, line);
//            if (t != SEMICOL) {
//                ParseError(line, "Missing semicolon after DeclStmt");
//                return false;
//            }
//            t = Parser::GetNextToken(in, line);
//        }
//        if (t != IDENT) {
//            break;
//        }
//    }
//    Parser::PushBackToken(t);
//    return true;
//}
//
//// DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
//bool DeclStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Parse the first IDENT
//    if (t != IDENT) {
//        ParseError(line, "Missing identifier in DeclStmt");
//        Parser::PushBackToken(t);
//        return false;
//    }
//    else {
//        defVar.insert({t.GetLexeme(), true});
//    }
//
//// Parse additional IDENTs separated by commas
//    t = Parser::GetNextToken(in, line);
//    while (true) {
//        if (t == COMMA) {
//            t = Parser::GetNextToken(in, line);
//            if(t != IDENT) {
//                ParseError(line, "Missing Optional Ident");
//                Parser::PushBackToken(t);
//                return false;
//            }
//            else if (defVar.find(t.GetLexeme()) != defVar.end()) {
//                ParseError(line, "Variable Redefinition");
//                return false;
//            }
//            else {
//                defVar.insert({t.GetLexeme(), true});
//                t = Parser::GetNextToken(in, line);
//            }
//        }
//        if (t != COMMA) {
//            break;
//        }
//    }
//    Parser::PushBackToken(t);
//
//    // Check for colon
//    t = Parser::GetNextToken(in, line);
//    if (t != COLON) {
//        ParseError(line, "Missing colon in DeclStmt");
//        return false;
//    }
//
//// Parse Type
//    t = Parser::GetNextToken(in, line);
//    if (t != INTEGER && t != REAL && t != BOOLEAN && t != STRING) {
//        ParseError(line, "Invalid type in DeclStmt");
//        return false;
//    }
//
//    // Check for optional initialization with :=
//    t = Parser::GetNextToken(in, line);
//    if (t == ASSOP) {
//        // Parse Expr
//        return Expr(in, line);
//    }
//    else {
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//// Stmt ::= SimpleStmt | StructuredStmt
//bool Stmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check if it is a SimpleStmt
//    if (t == IDENT || t == WRITELN || t == WRITE) {
//        Parser::PushBackToken(t);
//        if (!SimpleStmt(in, line)) {
//            ParseError(line, "Stmt isn't structured");
//            return false;
//        }
//    }
//    // Check if it is a StructuredStmt
//    else if (t == IF || t == BEGIN) {
//        Parser::PushBackToken(t);
//        if (!StructuredStmt(in, line)) {
//            ParseError(line, "Stmt wasn't structured");
//            return false;
//        }
//    }
//    return true;
//}
//
//// StructuredStmt ::= IfStmt | CompoundStmt
//bool StructuredStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check if it is an IfStmt
//    if (t == IF) {
//        Parser::PushBackToken(t);
//        if (!IfStmt(in, line)) {
//            ParseError(line, "In the StructuredStmt, incorrect IF format");
//            return false;
//        }
//    }
//    else if (t == BEGIN) {
//        // Push back the token if it's not IF
//        Parser::PushBackToken(t);
//        if(!CompoundStmt(in, line)) {
//            ParseError(line, "in Stmt, no compound");
//            return false;
//        }
//    }
//    return true;
//}
//
//// CompoundStmt ::= BEGIN Stmt {; Stmt } END
//bool CompoundStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//
//    // Check for BEGIN keyword
//    if (t != BEGIN) {
//        ParseError(line, "Missing BEGIN keyword in CompoundStmt");
//        return false;
//    }
//
//    // Parse the first Stmt
//    if (!Stmt(in, line)) {
//        ParseError(line, "Error in first Stmt in CompoundStmt");
//        return false;
//    }
//
//    t = Parser::GetNextToken(in, line);
//    while (true) {
//        if (t == SEMICOL) {
//            if (!Stmt(in, line)){
//                ParseError(line, "Error in Stmt in CompoundStmt");
//                return false;
//            }
//        }
//        t = Parser::GetNextToken(in, line);
//        if (t != SEMICOL){
//            break;
//        }
//    }
//    Parser::PushBackToken(t);
//    if (t != END) {
//        ParseError(line, "Missing End keyword in CompoundStmt");
//        return false;
//    }
//    return true;
//}
//
//// SimpleStmt ::= AssignStmt | WriteLnStmt | WriteStmt
//bool SimpleStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check if it is an AssignStmt
//    if (t == IDENT) {
//        Parser::PushBackToken(t); // Push back the IDENT token for AssignStmt to handle
//        if (!AssignStmt(in, line)) {
//            ParseError(line, "Invalid Assign Statement");
//            return false;
//        }
//    }
//    // Check if it is a WriteLnStmt
//    if (t == WRITELN) {
//        Parser::PushBackToken(t); // Push back the WRITELN token for WriteLnStmt to handle
//        if (!WriteLnStmt(in, line)) {
//            ParseError(line, "Invalid WriteLn Statement");
//            return false;
//        }
//    }
//    // Check if it is a WriteStmt
//    if (t == WRITE) {
//        Parser::PushBackToken(t); // Push back the WRITE token for WriteStmt to handle
//        if (!WriteStmt(in, line)) {
//            ParseError(line, "Invalid Write Statement");
//            return false;
//        }
//    }
//    // If neither AssignStmt nor WriteLnStmt nor WriteStmt, then it's an error
//    return true;
//}
//
////WriteLnStmt ::= writeln (ExprList)
//bool WriteLnStmt(istream& in, int& line) {
//    LexItem t;
//    t = Parser::GetNextToken(in, line);
//    if( t != WRITELN ) {
//        ParseError(line, "Missing Write");
//        return false;
//    }
//
//    t = Parser::GetNextToken(in, line);
//    if( t != LPAREN ) {
//        ParseError(line, "Missing Left Parenthesis");
//        return false;
//    }
//    bool ex = ExprList(in, line);
//    if(!ex) {
//        ParseError(line, "Missing expression list for WriteLn statement");
//        return false;
//    }
//    t = Parser::GetNextToken(in, line);
//    if(t != RPAREN ) {
//        ParseError(line, "Missing Right Parenthesis");
//        return false;
//    }
//    return ex;
//}
//
////WriteStmt ::= WRITE (ExprList)
//bool WriteStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check for LEFT PARENTHESIS
//    if( t != WRITE ) {
//        ParseError(line, "in writeStmt, Missing write");
//        return false;
//    }
//
//    t = Parser::GetNextToken(in, line);
//    if (t != LPAREN) {
//        ParseError(line, "Missing Left Parenthesis");
//        return false;
//    }
//
//    // Parse ExprList
//    bool ex = ExprList(in, line);
//
//    if( !ex ) {
//        ParseError(line, "in writeStmt, Missing expression list for Write statement");
//        return false;
//    }
//
//    // Check for RIGHT PARENTHESIS
//    t = Parser::GetNextToken(in, line);
//    if (t != RPAREN) {
//        ParseError(line, "Missing Right Parenthesis");
//        return false;
//    }
//    // Evaluate: You can add your code here to handle the list of expression values
//    return ex;
//}
//
//// IfStmt ::= IF Expr THEN Stmt [ ELSE Stmt ]
//bool IfStmt(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    // Check for IF keyword
//    if (t != IF) {
//        ParseError(line, "Missing IF keyword in IfStmt");
//        return false;
//    }
//
//    // Parse Expr
//    if (!Expr(in, line)) {
//        ParseError(line, "Error in Expr in IfStmt");
//        return false;
//    }
//
//    // Check for THEN keyword
//    t = Parser::GetNextToken(in, line);
//    if (t != THEN) {
//        ParseError(line, "Missing THEN keyword in IfStmt");
//        return false;
//    }
//
//    // Parse Stmt
//    if (!Stmt(in, line)) {
//        ParseError(line, "Error in Stmt in IfStmt");
//        return false;
//    }
//
//    // Check for optional ELSE part
//    t = Parser::GetNextToken(in, line);
//    if (t == ELSE) {
//        // Parse the Stmt in the ELSE part
//        if (!Stmt(in, line)) {
//            ParseError(line, "Error in Stmt in IfStmt (ELSE part)");
//            return false;
//        }
//    }
//    else {
//        // Push back the token if it's not ELSE
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//// AssignStmt ::= Var := Expr
//bool AssignStmt(istream& in, int& line) {
//    // Parse Var
//    if (!Var(in, line)) {
//        ParseError(line, "Error in Var in AssignStmt");
//        return false;
//    }
//    // Check for := (ASSOP)
//    LexItem t = Parser::GetNextToken(in, line);
//    if (t != ASSOP) {
//        ParseError(line, "Missing := (ASSOP) in AssignStmt");
//        return false;
//    }
//    // Parse Expr
//    if (!Expr(in, line)) {
//        ParseError(line, "Error in Expr in AssignStmt");
//        return false;
//    }
//    return true;
//}
//
//// Var ::= IDENT
//bool Var(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//
//    // Check for IDENT
//    if (t != IDENT) {
//        ParseError(line, "Missing identifier in Var");
//        return false;
//    }
//    else if (t == IDENT && defVar.find(t.GetLexeme()) == defVar.end()) {
//        ParseError(line, "in Var, ident not defined");
//        return false;
//    }
//    // Additional logic for handling the identifier if needed
//    return true;
//}
//
////ExprList:= Expr {,Expr}
//bool ExprList(istream& in, int& line) {
//    bool status = false;
//    status = Expr(in, line);
//    if(!status){
//        ParseError(line, "Missing Expression");
//        return false;
//    }
//
//    LexItem t = Parser::GetNextToken(in, line);
//    if (t == COMMA) {
//        status = ExprList(in, line);
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else{
//        Parser::PushBackToken(t);
//        return true;
//    }
//    return status;
//}
//
//// Expr ::= SimpleExpr [ RelOp SimpleExpr ]
//bool Expr(istream& in, int& line) {
//    // Parse the first SimpleExpr
//    if (!LogANDExpr(in, line)) {
//        ParseError(line, "Error in SimpleExpr in Expr");
//        return false;
//    }
//
//    // Check for optional RelOp
//    LexItem t = Parser::GetNextToken(in, line);
//    if (t == OR) {
//        // Parse the second SimpleExpr
//        bool droop = Expr(in, line);
//        if(!droop) {
//            Parser::PushBackToken(t);
//            return false;
//        }
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else {
//        // Push back the token if it's not a RelOp
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//
//// LogAndExpr ::= RelExpr { AND RelExpr }
//bool LogANDExpr(istream& in, int& line) {
//    // Parse the first RelExpr
//    if (!RelExpr(in, line)) {
//        ParseError(line, "Error in RelExpr in LogAndExpr");
//        return false;
//    }
//    // Parse additional RelExprs separated by AND
//    LexItem t = Parser::GetNextToken(in, line);
//    if(t == AND) {
//        return LogANDExpr(in, line);
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else {
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//// RelExpr ::= SimpleExpr [ ( = | < | > ) SimpleExpr ]
//bool RelExpr(istream& in, int& line) {
//    // Parse the first SimpleExpr
//    if (!SimpleExpr(in, line)) {
//        ParseError(line, "Error in SimpleExpr in RelExpr");
//        return false;
//    }
//    // Check for optional relational operator and additional SimpleExpr
//    LexItem t = Parser::GetNextToken(in, line);
//
//    if (t == EQ || t == LTHAN || t == GTHAN) {
//        // Parse the second SimpleExpr
//        if (!SimpleExpr(in, line)) {
//            ParseError(line, "Error in SimpleExpr after relational operator in RelExpr");
//            return false;
//        }
//    }
//    else {
//        // Push back the token if it's not a relational operator
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//// SimpleExpr ::= Term { ( + | - ) Term }
//bool SimpleExpr(istream& in, int& line) {
//    // Parse the first Term
//    if (!Term(in, line)) {
//        ParseError(line, "Error in Term in SimpleExpr");
//        return false;
//    }
//    // Parse additional Terms separated by + or -
//    LexItem t = Parser::GetNextToken(in, line);
//    if(t == PLUS || t == MINUS) {
//        return SimpleExpr(in, line);
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else {
//        Parser::PushBackToken(t);
//    }
//    return true;
//}
//
//// Term ::= SFactor { ( * | / | DIV | MOD ) SFactor }
//bool Term(istream& in, int& line) {
//    // Parse the first SFactor
//    if (!SFactor(in, line)) {
//        ParseError(line, "Error in SFactor in Term");
//        return false;
//    }
//
//    // Parse additional SFactors separated by *, /, DIV, or MOD
//    LexItem t = Parser::GetNextToken(in, line);
//    if(t == MULT || t == DIV || t == MOD) {
//        return Term(in, line);
//    }
//    else if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else {
//        Parser::PushBackToken(t);
//    }
//
//    return true;
//}
//
//// SFactor ::= [ ( - | + | NOT ) ] Factor?
//bool SFactor(istream& in, int& line) {
//    LexItem t = Parser::GetNextToken(in, line);
//    int sign = 1; // Initialize the sign to 1
//
//    // Check for optional unary operators - or + or NOT
//    if (t == MINUS || t == PLUS || t == NOT) {
//        // Update the sign before parsing the optional Factor
//        sign = t.GetToken();
//    }
//    else {
//        // Push back the token if it's not a unary operator
//        Parser::PushBackToken(t);
//    }
//
//
//    // Parse the optional Factor
//    if (!Factor(in, line, sign)) {
//        ParseError(line, "Error in Factor after unary operator in SFactor");
//        return false;
//    }
//    return true;
//}
//
//// Factor ::= IDENT | ICONST | RCONST | SCONST | BCONST | (Expr)
//bool Factor(istream& in, int& line, int sign) {
//    LexItem t = Parser::GetNextToken(in, line);
//    if(t.GetToken() == ERR){
//        ParseError(line, "Unrecognized Input Pattern");
//        return false;
//    }
//    else if(t == LPAREN) {
//        if(!Expr(in, line)) {
//            ParseError(line, "in factor, parenthesis but no expr");
//            return false;
//        }
//
//        t = Parser::GetNextToken(in, line);
//        if(t != RPAREN) {
//            ParseError(line, "in factor, no right parenthesis");
//            Parser::PushBackToken(t);
//            return false;
//        }
//    }
//    else if(t != IDENT && t != ICONST && t != RCONST && t != SCONST && t != BCONST) {
//        ParseError(line, "in Factor, no value");
//        Parser::PushBackToken(t);
//        return false;
//    }
//    return true;
//}