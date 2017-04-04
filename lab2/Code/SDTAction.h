#ifndef SDTACTION_H
#define SDTACTION_H

#define I(proNum) sdtIActionTable[proNum] = pro##proNum##IAction;

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
