#ifndef Generation_H
#define Generation_H

#define gen printf

// enum Relop {
//     Less = 0,
//     More,
//     Less_equal,
//     More_equal,
//     Equal,
//     Not_equal
// };

// enum Operation {
//     ADD = 0,
//     SUB,
//     MUL,
//     DIV
// };

enum IR_kind{
    Label = 0, // "LABEL target :"
    Fun,       // "FUNCTION target :"
    Read,      // "READ target"
    Write,     // "WRITE teaget"
    Cal,       // "target := arg1 u.op arg2"
    Assign,    //
    Return,    // ""
    Dec,
    Arg,
};

typedef struct ir_code {
    IR_kind kind;

    char *target;
    union {
        char* op;
        char* relop;
    }u;
    char *arg1;
    char *arg2;
}IR;

list_t *new_IR_list();
void del_IR_list();
void traverse_IR_list(void (*action)(IR*));

void print_IR(IR*);

#endif
