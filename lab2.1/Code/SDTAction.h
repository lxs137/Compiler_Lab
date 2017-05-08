#ifndef SDTACTION_H
#define SDTACTION_H

#include "syntax_tree.h"
#include "symbol_table.h"
#include "for_each.h"
#include "DebugMacro.h"
#include "3.h"
#include "4.h"
#include "7.h"
#include "8.h"
#include "9.h"
#include "10.h"
#include <malloc.h>
#include <assert.h>
#include <inttypes.h>
#include "Pointer.h"

void allocPointer();
void deallocPointer();
void noallocPointer();

#define I(proNum) registerIAction(proNum, pro##proNum##IAction);
#define IS(...) FOR_EACH(I, __VA_ARGS__)

#define S(proNum) registerSAction(proNum, pro##proNum##SAction);
#define SS(...) FOR_EACH(S, __VA_ARGS__)

#define ID(proNum) \
    void pro##proNum##IAction(AST_node *parent, AST_node *child, int childNum)
#define AssociateHelperI(p1, p2) SDTIAction pro##p2##IAction = pro##p1##IAction;
#define IDS(proNum, ...) \
    void pro##proNum##IAction(AST_node *parent, AST_node *child, int childNum); \
    FOR_EACH_2(AssociateHelperI, proNum, __VA_ARGS__) \
    void pro##proNum##IAction(AST_node *parent, AST_node *child, int childNum)

#define SD(proNum) \
    void pro##proNum##SAction(AST_node *parent)
#define AssociateHelperS(p1, p2) SDTSAction pro##p2##SAction = pro##p1##SAction;
#define SDS(proNum, ...) \
    void pro##proNum##SAction(AST_node *parent); \
    FOR_EACH_2(AssociateHelperS, proNum, __VA_ARGS__) \
    void pro##proNum##SAction(AST_node *parent)

#define D_type_info TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
#define D_parent_info TypeInfo *parent_info = (TypeInfo *)parent->other_info;
#define D_child_info \
    TypeInfo *child_info = (TypeInfo *) \
    child->other_info;
#define D_child_1_info \
    TypeInfo *child_1_info = (TypeInfo *) \
    parent->first_child->other_info;
#define D_child_2_info \
    TypeInfo *child_2_info = (TypeInfo *) \
    parent->first_child->next_brother->other_info;
#define D_child_3_info \
    TypeInfo *child_3_info = (TypeInfo *) \
    parent->first_child->next_brother->next_brother->other_info;

#define D_child_1 \
    AST_node *child_1 = parent->first_child;
#define D_child_2 \
    AST_node *child_2 = parent->first_child->next_brother;
#define D_child_3 \
    AST_node *child_3 = parent->first_child->next_brother->next_brother;

/* 第一个参数是父亲节点，第二个参数是需要准备继承属性的儿子节点 */
/* 第三个参数是需要准备继承属性的节点的编号 */
/* 0代表父节点 */
/* 1-n代表子节点 */
typedef void(*SDTIAction)(AST_node *, AST_node *, int childNum);
/* 在所有儿子节点的继承属性+综合属性算完之后，可以算本节点的综合属性（本节点的继承属性也已经准备好） */
typedef void(*SDTSAction)(AST_node *);

void initActionTable();
void cleanActionTable();
void registerIAction(int proNum, SDTIAction action);
void registerSAction(int proNum, SDTSAction action);
void traversalTreePerformAction(AST_node *parent);

enum TypeKindEnum { BuildInType = 1, ArrayType, ReferType, FunctionType, AlgebraicDataType, GenericType };

typedef struct
{
    enum TypeKindEnum typeKind;
    void *node;
    void *nextInfo;
} TypeInfo;

/* 节点中的域除特别说明者，均为继承属性 */

enum BuildInTypeKindEnum { Int = 1, Float, Let };
/* 内建类型的node域填充BuildInTypeKindEnum */

typedef struct
{
    TypeInfo *arrayTo;
    int width;
} ArrayNode;

typedef struct
{
    TypeInfo *referTo;
} ReferNode;

typedef struct
{
    TypeInfo *paramTypeInfo;
    TypeInfo *returnTypeInfo;
} FunctionNode;

typedef struct LN
{
    struct LN *lastBrother, *nextBrother;
    void *data;
} ListNode;

typedef struct
{
    char *constructorIdName;
    ListNode *fields;
} ConstructorNode;

typedef struct
{
    char *typeIdName;
    ListNode *constructors;
} AlgebraicDataTypeNode;

typedef struct
{
    char *genericTypeName;
} GenericTypeNode;

void printTypeInfo(TypeInfo *typeInfo);

#endif
