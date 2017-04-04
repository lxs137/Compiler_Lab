#ifndef SDTACTION_H
#define SDTACTION_H

/* Make a FOREACH macro */
#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME 
#define FOR_EACH(action, ...) \
    GET_MACRO(__VA_ARGS__, FE_5, FE_4, FE_3, FE_2, FE_1)(action, __VA_ARGS__)

#define I(proNum) sdtIActionTable[proNum] = pro##proNum##IAction;
/* #define I_2(proNum) */ 
#define IS(NAME, ...) FOR_EACH(I, __VA_ARGS__) NAME

#include "syntax_tree.h"
#include "symbol_table.h"
/* 产生式总数目 */
#define ProCount 58
/* 第一个参数是父亲节点，第二个参数是需要准备继承属性的儿子节点 */
/* 第三个参数是需要准备继承属性的节点的编号 */
/* 0代表父节点 */
/* 1-n代表子节点 */
typedef void(*SDTIAction)(AST_node *, AST_node *, int childNum);
extern SDTIAction sdtIActionTable[ProCount];
/* 在所有儿子节点的继承属性+综合属性算完之后，可以算本节点的综合属性（本节点的继承属性也已经准备好） */
typedef void(*SDTSAction)(AST_node *);
extern SDTSAction sdtSActionTable[ProCount];

#endif
