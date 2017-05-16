#ifndef Generation_H
#define Generation_H

#define gen printf 

typedef struct {
    enum Value_kind {
        Variable = 0, // 普通变量或临时变量, v1
        Constant,     // 立即数, #1
        Address,      // 地址, &x
        Content,      // 地址中的内容, *x  
    } kind;

    char *content;

} Value;

char* value2str(Value*);
Value* str2value(char*);

enum IR_kind {
    Label = 0, // "LABEL target :"
    Fun,       // "FUNCTION target :"
    Calculate, // "target := arg1 u.op arg2"
    Assign,    // "target := arg1"    "target := &arg1" 
               // "target := *arg1"   "*target := arg1"
    Goto,      // "GOTO target"
    GotoRel,   // "IF arg1 u.relop arg2 GOTO target"
    Return,    // "RETURN target"
    Dec,       // "DEC target arg1"
    Arg,       // "ARG target"
    Call,      // "target := CALL arg1"
    Param,     // "PARAM target"
    Read,      // "READ target"
    Write,     // "WRITE teaget"
};

typedef struct {
    IR_kind kind;

    Value *target;
    union {
        char* op;
        char* relop;  
    }u;
    Value *arg1;
    Value *arg2;
}IR;

void free_IR(void *val);
list_t *new_IR_list();
void del_IR_list();
void traverse_IR_list(void (*action)(IR*));

void print_IR(IR*);

#endif
