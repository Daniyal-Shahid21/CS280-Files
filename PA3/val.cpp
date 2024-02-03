#include "val.h"

Value Value::operator+(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp + op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp + op.Rtemp);
    }
    else if (T == VSTRING && op.IsString()) {
        return Value(Stemp + op.Stemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Mixed Type Operands";
    }
}

Value Value::operator-(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp - op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp - op.Rtemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Mixed Type Operands";
    }
}

Value Value::operator*(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp * op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp * op.Rtemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Mixed Type Operands";
    }
}

Value Value::operator/(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        // Handle division by zero
        if (op.Itemp == 0) {
            throw "RUNTIME ERROR: Division by zero";
        }
        return Value(Itemp / op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        // Handle division by zero
        if (op.Rtemp == 0.0) {
            throw "RUNTIME ERROR: Division by zero";
        }
        return Value(Rtemp / op.Rtemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Mixed Type Operands";
    }
}


Value Value::operator%(const Value& oper) const {
    if (T == VINT && oper.IsInt()) {
        // Handle modulus by zero
        if (oper.Itemp == 0) {
            throw "RUNTIME ERROR: Modulus by zero";
        }
        return Value(Itemp % oper.Itemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Modulus Operation";
    }
}


Value Value::div(const Value& oper) const {
    if (T == VINT && oper.IsInt()) {
        // Handle division by zero
        if (oper.Itemp == 0) {
            throw "RUNTIME ERROR: Division by zero";
        }
        return Value(Itemp / oper.Itemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Division Operation";
    }
}


Value Value::operator==(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp == op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp == op.Rtemp);
    }
    else if (T == VSTRING && op.IsString()) {
        return Value(Stemp == op.Stemp);
    }
    else if (T == VBOOL && op.IsBool()) {
        return Value(Btemp == op.Btemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Comparison Operation";
    }
}


Value Value::operator>(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp > op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp > op.Rtemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Greater Than Operation";
    }
}


Value Value::operator<(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        return Value(Itemp < op.Itemp);
    }
    else if (T == VREAL && op.IsReal()) {
        return Value(Rtemp < op.Rtemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Less Than Operation";
    }
}


Value Value::idiv(const Value& op) const {
    if (T == VINT && op.IsInt()) {
        // Handle division by zero
        if (op.Itemp == 0) {
            throw "RUNTIME ERROR: Integer Division by zero";
        }
        return Value(Itemp / op.Itemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Integer Division Operation";
    }
}


Value Value::operator&&(const Value& oper) const {
    if (T == VBOOL && oper.IsBool()) {
        return Value(Btemp && oper.Btemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Logical AND Operation";
    }
}


Value Value::operator||(const Value& oper) const {
    if (T == VBOOL && oper.IsBool()) {
        return Value(Btemp || oper.Btemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal Logical OR Operation";
    }
}

Value Value::operator!() const {
    // Logical NOT implementation
    if (IsBool()) {
        return Value(!Btemp);
    }
    else {
        throw "RUNTIME ERROR: Illegal NOT Operation";
    }
}