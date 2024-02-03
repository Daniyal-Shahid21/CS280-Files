#include "parserInterp.h"


map<string, bool> defVar;
map<string, Token> SymTable;

map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants
queue <Value> * ValQue; //declare a pointer variable to a queue of Value objects

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;
}

// Prog ::= PROGRAM IDENT ; DeclPart CompoundStmt .
bool Prog(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);

    // Check for PROGRAM keyword
    if (t != PROGRAM) {
        ParseError(line, "Missing PROGRAM keyword");
        return false;
    }

    // Check for IDENT
    t = Parser::GetNextToken(in, line);
    if (t != IDENT) {
        ParseError(line, "Missing program identifier");
        return false;
    }

    // Check for semicolon
    t = Parser::GetNextToken(in, line);
    if (t != SEMICOL) {
        ParseError(line, "Missing semicolon after program identifier");
        return false;
    }

    // Parse DeclPart
    if (!DeclPart(in, line)) {
        ParseError(line, "Error in DeclPart");
        return false;
    }

    // Parse CompoundStmt
    if (!CompoundStmt(in, line)) {
        ParseError(line, "Error in CompoundStmt");
        return false;
    }

    // Check for period
    t = Parser::GetNextToken(in, line);
    if (t == END){
        return true;
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    return true;
}

// DeclPart ::= VAR DeclStmt; { DeclStmt ; }
bool DeclPart(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check for VAR keyword
    if (t != VAR) {
        ParseError(line, "Missing VAR keyword in DeclPart");
        return false;
    }

    // Parse the first DeclStmt
    if (!DeclStmt(in, line)) {
        ParseError(line, "Error in first DeclStmt");
        return false;
    }

    // Check for semicolon after the first DeclStmt
    t = Parser::GetNextToken(in, line);
    if (t != SEMICOL) {
        ParseError(line, "Missing semicolon after the first DeclStmt");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    // Parse additional DeclStmts with optional semicolons
    while (true) {
        // Parse the next DeclStmt
        if (t == IDENT) {
            Parser::PushBackToken(t);
            if (!(DeclStmt(in, line))){
                ParseError(line, "Error in DeclStmt");
                return false;
            }
            t = Parser::GetNextToken(in, line);
            if (t != SEMICOL) {
                ParseError(line, "Missing semicolon after DeclStmt");
                return false;
            }
            t = Parser::GetNextToken(in, line);
        }
        if (t != IDENT) {
            break;
        }
    }
    Parser::PushBackToken(t);
    return true;
}


// DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
bool DeclStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Parse the first IDENT
    if (t != IDENT) {
        ParseError(line, "Missing identifier in DeclStmt");
        Parser::PushBackToken(t);
        return false;
    }
    else {
        defVar.insert({t.GetLexeme(), true});
    }

// Parse additional IDENTs separated by commas
    t = Parser::GetNextToken(in, line);
    while (true) {
        if (t == COMMA) {
            t = Parser::GetNextToken(in, line);
            if(t != IDENT) {
                ParseError(line, "Missing Optional Ident");
                Parser::PushBackToken(t);
                return false;
            }
            else if (defVar.find(t.GetLexeme()) != defVar.end()) {
                ParseError(line, "Variable Redefinition");
                return false;
            }
            else {
                defVar.insert({t.GetLexeme(), true});
                t = Parser::GetNextToken(in, line);
            }
        }
        if (t != COMMA) {
            break;
        }
    }
    Parser::PushBackToken(t);

    // Check for colon
    t = Parser::GetNextToken(in, line);
    if (t != COLON) {
        ParseError(line, "Missing colon in DeclStmt");
        return false;
    }

// Parse Type
    t = Parser::GetNextToken(in, line);
    if (t != INTEGER && t != REAL && t != BOOLEAN && t != STRING) {
        ParseError(line, "Invalid type in DeclStmt");
        return false;
    }

    // Check for optional initialization with :=
    t = Parser::GetNextToken(in, line);
    if (t == ASSOP) {
        // Parse Expr
        Value val;
        return Expr(in, line, val);
    }
    else {
        Parser::PushBackToken(t);
    }
    return true;
}

// Stmt ::= SimpleStmt | StructuredStmt
bool Stmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check if it is a SimpleStmt
    if (t == IDENT || t == WRITELN || t == WRITE) {
        Parser::PushBackToken(t);
        if (!SimpleStmt(in, line)) {
            ParseError(line, "Stmt isn't structured");
            return false;
        }
    }
        // Check if it is a StructuredStmt
    else if (t == IF || t == BEGIN) {
        Parser::PushBackToken(t);
        if (!StructuredStmt(in, line)) {
            ParseError(line, "Stmt wasn't structured");
            return false;
        }
    }
    return true;
}

// StructuredStmt ::= IfStmt | CompoundStmt
bool StructuredStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check if it is an IfStmt
    if (t == IF) {
        Parser::PushBackToken(t);
        if (!IfStmt(in, line)) {
            ParseError(line, "In the StructuredStmt, incorrect IF format");
            return false;
        }
    }
    else if (t == BEGIN) {
        // Push back the token if it's not IF
        Parser::PushBackToken(t);
        if(!CompoundStmt(in, line)) {
            ParseError(line, "in Stmt, no compound");
            return false;
        }
    }
    return true;
}

// CompoundStmt ::= BEGIN Stmt {; Stmt } END
bool CompoundStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);

    // Check for BEGIN keyword
    if (t != BEGIN) {
        ParseError(line, "Missing BEGIN keyword in CompoundStmt");
        return false;
    }

    // Parse the first Stmt
    if (!Stmt(in, line)) {
        ParseError(line, "Error in first Stmt in CompoundStmt");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    while (true) {
        if (t == SEMICOL) {
            if (!Stmt(in, line)){
                ParseError(line, "Error in Stmt in CompoundStmt");
                return false;
            }
        }
        t = Parser::GetNextToken(in, line);
        if (t != SEMICOL){
            break;
        }
    }
    Parser::PushBackToken(t);
    if (t != END) {
        ParseError(line, "Missing End keyword in CompoundStmt");
        return false;
    }
    return true;
}

// SimpleStmt ::= AssignStmt | WriteLnStmt | WriteStmt
bool SimpleStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check if it is an AssignStmt
    if (t == IDENT) {
        Parser::PushBackToken(t); // Push back the IDENT token for AssignStmt to handle
        if (!AssignStmt(in, line)) {
            ParseError(line, "Invalid Assign Statement");
            return false;
        }
    }
    // Check if it is a WriteLnStmt
    if (t == WRITELN) {
        Parser::PushBackToken(t); // Push back the WRITELN token for WriteLnStmt to handle
        if (!WriteLnStmt(in, line)) {
            ParseError(line, "Invalid WriteLn Statement");
            return false;
        }
    }
    // Check if it is a WriteStmt
    if (t == WRITE) {
        Parser::PushBackToken(t); // Push back the WRITE token for WriteStmt to handle
        if (!WriteStmt(in, line)) {
            ParseError(line, "Invalid Write Statement");
            return false;
        }
    }
    // If neither AssignStmt nor WriteLnStmt nor WriteStmt, then it's an error
    return true;
}

//WriteLnStmt ::= writeln (ExprList)
bool WriteLnStmt(istream& in, int& line) {
    LexItem t;
    t = Parser::GetNextToken(in, line);
    if( t != WRITELN ) {
        ParseError(line, "Missing Write");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if( t != LPAREN ) {
        ParseError(line, "Missing Left Parenthesis");
        return false;
    }
    bool ex = ExprList(in, line);
    if(!ex) {
        ParseError(line, "Missing expression list for WriteLn statement");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if(t != RPAREN ) {
        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    return ex;
}

//WriteStmt ::= WRITE (ExprList)
bool WriteStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check for LEFT PARENTHESIS
    if( t != WRITE ) {
        ParseError(line, "in writeStmt, Missing write");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if (t != LPAREN) {
        ParseError(line, "Missing Left Parenthesis");
        return false;
    }

    // Parse ExprList
    bool ex = ExprList(in, line);

    if( !ex ) {
        ParseError(line, "in writeStmt, Missing expression list for Write statement");
        return false;
    }

    // Check for RIGHT PARENTHESIS
    t = Parser::GetNextToken(in, line);
    if (t != RPAREN) {
        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    // Evaluate: You can add your code here to handle the list of expression values
    return ex;
}

// IfStmt ::= IF Expr THEN Stmt [ ELSE Stmt ]
bool IfStmt(istream& in, int& line) {
    LexItem t = Parser::GetNextToken(in, line);
    // Check for IF keyword
    if (t != IF) {
        ParseError(line, "Missing IF keyword in IfStmt");
        return false;
    }

    // Parse Expr
    Value val;
    if (!Expr(in, line, val)) {
        ParseError(line, "Error in Expr in IfStmt");
        return false;
    }

    // Check for THEN keyword
    t = Parser::GetNextToken(in, line);
    if (t != THEN) {
        ParseError(line, "Missing THEN keyword in IfStmt");
        return false;
    }

    // Parse Stmt
    if (!Stmt(in, line)) {
        ParseError(line, "Error in Stmt in IfStmt");
        return false;
    }

    // Check for optional ELSE part
    t = Parser::GetNextToken(in, line);
    if (t == ELSE) {
        // Parse the Stmt in the ELSE part
        if (!Stmt(in, line)) {
            ParseError(line, "Error in Stmt in IfStmt (ELSE part)");
            return false;
        }
    }
    else {
        // Push back the token if it's not ELSE
        Parser::PushBackToken(t);
    }
    return true;
}

bool Var(istream& in, int& line, LexItem & idtok)
{
    string identstr;
    idtok = Parser::GetNextToken(in, line);
    if (idtok == IDENT){
        identstr = idtok.GetLexeme();
        if (!defVar[identstr]) {
            ParseError(line, "Undefined Variable");
            return false;
        }
        TempsResults[identstr];
        return true;
    }
    else if(idtok.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << idtok.GetLexeme() << ")" << endl;
        return false;
    }
    return false;
}

bool AssignStmt(istream& in, int& line) {
    bool varstatus;
    bool status;
    LexItem t;
    varstatus = Var(in, line, t);
    if (varstatus){
        string lex = t.GetLexeme();
        LexItem tok = Parser::GetNextToken(in, line);

        if (tok == ASSOP){
            Value val;
            status = Expr(in, line, val);
            if(!status) {
                ParseError(line, "Missing Expression in Assignment Statment");
                return status;
            }

            if (SymTable[lex] == INTEGER) {
                if(val.IsReal()) {
                    float valFloat = val.GetReal();
                    val.SetType(VINT);
                    val.SetInt(static_cast<int>(valFloat));

                }
            } else if (SymTable[lex] == REAL) {
                if(val.IsInt()) {
                    int valInt = val.GetInt();
                    val.SetType(VREAL);
                    val.SetReal(static_cast<float>(valInt));
                }
            }
            TempsResults[lex] = val;
        }
        else if(t.GetToken() == ERR){
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << t.GetLexeme() << ")" << endl;
            return false;
        }
        else {
            ParseError(line, "Missing Assignment Operator =");
            return false;
        }
    }
    else {
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
        return false;
    }
    return status;
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
    bool status = false;
    Value val;
    status = Expr(in, line, val);
    if(!status){
        ParseError(line, "Missing Expression");
        return false;
    }
    ValQue->push(val);
    LexItem t = Parser::GetNextToken(in, line);
    if (t == COMMA) {
        status = ExprList(in, line);
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    else{
        Parser::PushBackToken(t);
        return true;
    }
    return status;
}

// Expr ::= SimpleExpr [ RelOp SimpleExpr ]
bool Expr(istream& in, int& line, Value & retVal) {
    // Parse the first SimpleExpr
    Value val1, val2;
    if (!LogANDExpr(in, line, val1)) {
        ParseError(line, "Error in SimpleExpr in Expr");
        return false;
    }

    // Check for optional RelOp
    LexItem t = Parser::GetNextToken(in, line);
    if (t == EQ || t == LTHAN || t == GTHAN) {
        // Parse the second SimpleExpr
        bool droop = Expr(in, line, val2);
        if(!droop) {
            Parser::PushBackToken(t);
            return false;
        }

        // Perform the relational operation and update retVal
        if (t == EQ) {
            retVal = (val1 == val2);
        }
        else if (t == LTHAN) {
            retVal = (val1 < val2);
        }
        else if (t == GTHAN) {
            retVal = (val1 > val2);
        }
    }
    else if(t == OR) {
        // Push back the token if it's not a RelOp
        Parser::PushBackToken(t);
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    return true;
}

// LogAndExpr ::= RelExpr { AND RelExpr }
bool LogANDExpr(istream& in, int& line, Value & retVal) {
    // Parse the first RelExpr
    if (!RelExpr(in, line, retVal)) {
        ParseError(line, "Error in RelExpr in LogAndExpr");
        return false;
    }
    // Parse additional RelExprs separated by AND
    LexItem t = Parser::GetNextToken(in, line);
    while(t == AND) {
        Value temp;
        if (!RelExpr(in, line, temp)) {
            ParseError(line, "Error in RelExpr in LogAndExpr");
            return false;
        }
        // Perform the logical AND operation and update retVal
        retVal = (retVal && temp);
        t = Parser::GetNextToken(in, line);
    }

    if(t == OR) {
        // Push back the token if it's not a logical AND
        Parser::PushBackToken(t);
    }
    else if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    }
    return true;
}

// RelExpr ::= SimpleExpr [ ( = | < | > ) SimpleExpr ]
bool RelExpr(istream& in, int& line, Value & retVal) {
    // Parse the first SimpleExpr
    Value val1, val2;
    if (!SimpleExpr(in, line, val1)) {
        ParseError(line, "Error in SimpleExpr in RelExpr");
        return false;
    }
    // Check for optional relational operator and additional SimpleExpr
    LexItem t = Parser::GetNextToken(in, line);

    if (t == EQ || t == LTHAN || t == GTHAN) {
        // Parse the second SimpleExpr
        if (!SimpleExpr(in, line, val2)) {
            ParseError(line, "Error in SimpleExpr after relational operator in RelExpr");
            return false;
        }

        // Perform the relational operation and update retVal
        if (t == EQ) {
            retVal = (val1 == val2);
        } else if (t == LTHAN) {
            retVal = (val1 < val2);
        } else if (t == GTHAN) {
            retVal = (val1 > val2);
        }
    }
    else {
        // Push back the token if it's not a relational operator
        Parser::PushBackToken(t);
    }
    return true;
}

// SimpleExpr ::= Term { ( + | - ) Term }
bool SimpleExpr(istream& in, int& line, Value & retVal) {
    // Parse the first Term
    if (!Term(in, line, retVal)) {
        ParseError(line, "Error in Term in SimpleExpr");
        return false;
    }
    // Parse additional Terms separated by + or -
    LexItem t = Parser::GetNextToken(in, line);
    while(t == PLUS || t == MINUS) {
        Value temp;
        if (!Term(in, line, temp)) {
            ParseError(line, "Error in Term in SimpleExpr");
            return false;
        }

        // Perform the addition or subtraction and update retVal
        if (t == PLUS) {
            retVal = (retVal + temp);
        } else if (t == MINUS) {
            retVal = (retVal - temp);
        }

        t = Parser::GetNextToken(in, line);
    }

    if(t.GetToken() == ERR){
        ParseError(line, "Unrecognized Input Pattern");
        return false;
    } else {
        Parser::PushBackToken(t);
    }
    return true;
}

bool Term(istream& in, int& line, Value & retVal) {
    Value val1, val2;
    bool t1 = SFactor(in, line, val1);
    LexItem tok;

    if (!t1) {
        return false;
    }
    retVal = val1;

    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == ERR) {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    while (tok == MULT || tok == DIV || tok == IDIV || tok == MOD) {
        t1 = SFactor(in, line, val2);

        if (!t1) {
            ParseError(line, "Missing operand after operator");
            return false;
        }

        if (retVal.GetType() == VSTRING || val2.GetType() == VSTRING) {
            ParseError(line, "Run-Time Error-Illegal Mixed Type Operands");
            return false;
        } else if (tok == MULT) {
            retVal = retVal * val2;
        } else if (tok == DIV) {
            if (val2.GetInt() == 0) {
                ParseError(line, "Run-Time Error-Illegal Division by Zero");
                return false;
            }
            retVal = retVal / val2;
        } else if (tok == IDIV) {
            if (val2.GetInt() == 0) {
                ParseError(line, "Run-Time Error-Illegal Division by Zero");
                return false;
            }
            retVal = retVal.idiv(val2);
        } else if (tok == MOD) {
            if (val2.GetInt() == 0) {
                ParseError(line, "Run-Time Error-Illegal Modulus by Zero");
                return false;
            }
            retVal = retVal % val2;
        }

        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == ERR) {
            ParseError(line, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
            return false;
        }
    }
    Parser::PushBackToken(tok);
    return true;
}

bool SFactor(istream& in, int& line, Value & retVal) {
    LexItem t = Parser::GetNextToken(in, line);
    bool status;
    int sign = 0;
    if (t == MINUS) {
        sign = -1;
    } else if (t == PLUS) {
        sign = 1;
    } else {
        Parser::PushBackToken(t);
    }

    status = Factor(in, line, retVal, sign);
    return status;
}


bool Factor(istream& in, int& line, Value & retVal, int sign) {
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == IDENT) {
        string lexeme = tok.GetLexeme();

        Value value = TempsResults[lexeme];

        if (value.IsErr()) {
            ParseError(line, "Undefined Variable");
            return false;
        }

        if (sign == -1) {
            if (value.GetType() == VINT) {
                int val3 = value.GetInt();
                val3 = -1 * val3;
                retVal.SetType(VINT);
                retVal.SetInt(val3);
            } else if (value.GetType() == VREAL) {
                float val3 = value.GetReal();
                val3 = -1 * val3;
                retVal.SetType(VREAL);
                retVal.SetReal(val3);
            }
        } else {
            retVal = TempsResults[lexeme];
        }
        return true;
    } else if (tok == ICONST) {
        retVal.SetType(VINT);
        string lex = tok.GetLexeme();
        int value = stoi(lex);

        if (sign == -1) {
            value = -1 * value;
        }
        retVal.SetInt(value);
        return true;
    } else if (tok == SCONST) {
        retVal.SetType(VSTRING);
        retVal.SetString(tok.GetLexeme());
        return true;
    } else if (tok == RCONST) {
        retVal.SetType(VREAL);
        string lex = tok.GetLexeme();
        float value = stof(lex);

        if (sign == -1) {
            value = -1 * value;
        }

        retVal.SetReal(value);
        return true;
    } else if (tok == LPAREN) {
        bool ex = Expr(in, line, retVal);
        if (!ex) {
            ParseError(line, "Missing expression after (");
            return false;
        }
        if (Parser::GetNextToken(in, line) == RPAREN)
            return ex;

        ParseError(line, "Missing ) after expression");
        return false;
    } else if (tok.GetToken() == ERR) {
        ParseError(line, "Unrecognized Input Pattern");
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }

    ParseError(line, "Unrecognized input");
    return false;
}