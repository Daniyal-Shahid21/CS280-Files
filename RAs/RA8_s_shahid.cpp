//#include "val.h"
//Value Value::operator == (const Value& op) const{
//    if (op.IsBool() && IsBool()) {
//        return Value(op.GetBool() == GetBool());
//    }
//    else if (op.IsInt() && IsInt()) {
//        return Value(op.GetInt() == GetInt());
//    }
//    else if (op.IsReal() && IsReal()) {
//        return Value(op.GetReal() == GetReal());
//    }
//    else if (op.IsString() && IsString()) {
//        return Value(op.GetString() == GetString());
//    }
//    else if (op.IsInt() && IsReal()) {
//        return Value(op.GetInt() == GetReal());
//    }
//    else if (op.IsReal() && IsInt()) {
//        return Value(op.GetReal() == GetInt());
//    }
//    else {
//        return Value();
//    }
//}
//
//Value Value::operator / (const Value& op) const {
//    if(GetType() == VREAL && op.GetType() == VREAL ) {
//        return Value(GetReal() / op.GetReal());
//    }
//    else if (GetType() == VREAL && op.GetType() == VINT ) {
//        return Value(GetReal() / op.GetInt());
//    }
//    else if (GetType() == VINT && op.GetType() == VINT ) {
//        return Value(GetInt() / op.GetInt());
//    }
//    else if (GetType() == VINT && op.GetType() == VREAL ) {
//        return Value(GetInt() / op.GetReal());
//    }
//    else {
//        return Value();
//    }
//}
//
//Value Value::operator % (const Value& oper) const{
//    if (GetType() == VINT && oper.GetType() == VINT) {
//        return Value(GetInt() % oper.GetInt());
//    }
//    else {
//        return Value();
//    }
//}
//
//Value Value::operator && (const Value& oper) const{
//    if (oper.IsBool() && IsBool()) {
//        return Value(oper.GetBool() && GetBool());
//    }
//    else {
//        return Value();
//    }
//}