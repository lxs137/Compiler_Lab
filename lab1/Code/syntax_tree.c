#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include "syntax_tree.h"

AST_node* new_token_node(int line, int column, char* string)
{
    AST_node *token = (AST_node *)(malloc(sizeof(AST_node)));
    token->loc_line = line;
    token->loc_column = column;

    if (string == NULL)
      token->str = NULL;
    else
    {
        // str指向的是词法分析缓冲区的指针,如直接存储该指针值,之后打印会出错
        char* str_ptr = string;
        int str_length = 0;
        while(*str_ptr != '\0')
        {
            str_length++;
            str_ptr++;
        }
        // 为token的str新建一段内存区域,将string所指字符串拷贝进去
        char* new_str = (char *)(malloc(sizeof(char)*(str_length+1)));
        strcpy(new_str, string);
        token->str = new_str;
    }

    token->first_child = NULL;
    token->next_brother = NULL;
    return token;
}

// 传入指向子节点的指针
// 为保证parent的line正确赋值,请按子节点出现的前后顺序传入参数
AST_node* new_parent_node(int node_num, ...)
{
    AST_node* parent = new_token_node(0, 0, NULL);
    va_list ap;
    va_start(ap, node_num);

    // 将同一父节点的子节点用指针连接起来
    int i = 0;
    AST_node *cur_node = NULL;
    AST_node *pre_code = NULL;
    for(i = 0; i < node_num; i++)
    {       
        if(i == 0)
        {
            cur_node = va_arg(ap, AST_node*);          
            parent->first_child = cur_node;
        }
        else
        {
            cur_node = va_arg(ap, AST_node*);
            pre_code->next_brother = cur_node;
        }
        pre_code = cur_node;
    }
    va_end(ap);

    if(node_num > 0)
    {
        parent->loc_line = parent->first_child->loc_line;
        parent->loc_column = parent->first_child->loc_column;
    }

    //TODO: 为parent的str赋值
    parent->str = parent->first_child->str;

    return parent;
}


