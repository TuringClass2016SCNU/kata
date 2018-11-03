#include <stdio.h>
#include <stdlib.h>

typedef struct t_node{
    int data;
    struct t_node* left;
    struct t_node* right;
}t_node;


/*
 Give me a pointer of the root,I will return you a tree.
 */
t_node* autoBuildTree(t_node* n,int data,int floor)
{
    if(floor <= 0) return NULL;
    n = (t_node*)malloc(sizeof(t_node));
    n->data = data;
    n->left = autoBuildTree(n->left,data*2,floor-1);
    n->right = autoBuildTree(n->right,data*2+1,floor-1);
    return n;
}

/* making a stack */
typedef struct s_node{
    t_node* node;
    struct s_node* next;
}s_node;

s_node* stackBuild()
{
    return NULL;
}

s_node* stackPush(s_node* head,t_node* t_data)
{
    s_node* insert = (s_node*)malloc(sizeof(s_node));
    insert->node = t_data;
    insert->next = head;
    head = insert;
    return head;
}

t_node* stackTop(s_node* head)
{
     return head->node;
}

s_node* stackPop(s_node* head)
{
    s_node *tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

int stackIsEmpty(s_node* head)
{
    return head == NULL;
}

void stackDestory(s_node* head)
{
    while(head) stackPop(head);
}
/* end making stack */
void visit(t_node* n)
{
    printf("%d ",n->data);
}

void treeFrontPrint1(t_node* n)
{
    if(!n) return;
    visit(n); 
    treeFrontPrint1(n->left);
    treeFrontPrint1(n->right);
}

void treeFrontPrint2(t_node* n)
{
    s_node* st = stackBuild(); 

    t_node* tmp = n;
    while(1)
    {
        if(tmp)
        {
            if(tmp->right) st = stackPush(st,tmp->right);
            visit(tmp);
            tmp = tmp->left;
        }
        else if(!stackIsEmpty(st))
        {
            tmp = stackTop(st);
            st = stackPop(st);
        }
        else
        {
            break;
        }
    }
}

void destroyTree(t_node* n)
{
    if(!n) return;
    destroyTree(n->left);
    destroyTree(n->right);
    free(n);
    n = NULL;
}

int main()
{
    t_node* root = NULL;
    root = autoBuildTree(root,1,4);
    treeFrontPrint1(root);
    printf("\n");
    treeFrontPrint2(root);
    printf("\n");
    
    return 0;
}
