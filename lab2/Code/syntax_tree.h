#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H
typedef struct syntax_tree_node
{
    int loc_line;
    int loc_column;
    char *str;
    struct syntax_tree_node *first_child;
    struct syntax_tree_node *next_brother;
    int proNum;
    void *otherInformation;
} AST_node;

AST_node *new_token_node(int line, int column, char *string);
AST_node *new_parent_node(char *string, int proNum, int node_num, ...);
void print_child_node(AST_node *parent, int depth);

/* 产生式总数目 */
#define ProCount 58
/* 第一个参数是父亲节点，第二个参数是需要准备继承属性的儿子节点 */
/* 第三个参数是需要准备继承属性的节点的编号 */
/* 0代表父节点 */
/* 1-n代表子节点 */
/* 如果所有的儿子节点的继承属性可以一起准备好，建议在childNum = 0时处理，其余情况直接返回 */
typedef void(*SDTIAction)(AST_node*, AST_node*, int childNum);
SDTIAction sdtIActionTable[ProCount];
/* 在所有儿子节点的继承属性+综合属性算完之后，可以算本节点的综合属性（本节点的继承属性也已经准备好） */
typedef void(*SDTSAction)(AST_node*);
SDTSAction sdtSActionTable[ProCount];
#endif
