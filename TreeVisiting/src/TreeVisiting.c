#include <stdio.h>
#include <stdlib.h>

typedef struct t_node{
    int data;
    struct t_node* left;
    struct t_node* right;
    unsigned char visited;
}t_node;

/* making stack */
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

unsigned char checker = 0;
void newChecker(int num)
{
    checker = num+1;
}

int checkVisited(t_node* node)
{
    return node->visited == checker;
}

void visit(t_node* n)
{
    printf("%d ",n->data);
    n->visited++;
}

void treeFrontVisit1(t_node* n)
{
    if(!n) return;
    visit(n); 
    treeFrontVisit1(n->left);
    treeFrontVisit1(n->right);
}

void treeFrontVisit2(t_node* root)
{
    s_node* st = stackBuild(); 
    newChecker(root->visited);

    t_node* tmp = root;
    st = stackPush(st,root);
    while(!stackIsEmpty(st))
    {
        if(!checkVisited(tmp)) visit(tmp);
        if(tmp->left && !checkVisited(tmp->left))
        {
            st = stackPush(st,tmp);
            tmp = tmp->left;
        }
        else if(tmp->right && !checkVisited(tmp->right))
        {
            tmp = tmp->right;
        }
        else
        {
            tmp = stackTop(st);
            st = stackPop(st);
        }
    }
    stackDestory(st);
}

void treeFrontVisit3(t_node* root)
{
    s_node* st = stackBuild(); 

    t_node* tmp = root;
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
    stackDestory(st);
}

void treeMiddleVisit1(t_node* n)
{
    if(!n) return;
    treeMiddleVisit1(n->left);
    visit(n); 
    treeMiddleVisit1(n->right);
}

void treeMiddleVisit2(t_node* root)
{
    s_node* st = stackBuild(); 
    newChecker(root->visited);

    t_node* tmp = root;
    st = stackPush(st,root);
    while(!stackIsEmpty(st))
    {
        while(tmp->left && !checkVisited(tmp->left))
        {
            st = stackPush(st,tmp);
            tmp = tmp->left;
        }
        visit(tmp);
        if(tmp->right && !checkVisited(tmp->right))
            tmp = tmp->right;
        else
        {
            tmp = stackTop(st);
            st = stackPop(st);
        }
    }
    stackDestory(st);
}

void treeEndVisit1(t_node* n)
{
    if(!n) return;
    treeEndVisit1(n->left);
    treeEndVisit1(n->right);
    visit(n); 
}

void treeEndVisit2(t_node* root)
{
    s_node* st = stackBuild(); 
    newChecker(root->visited);

    t_node* tmp = root;
    st = stackPush(st,root);
    while(!stackIsEmpty(st))
    {
        while(tmp->left && !checkVisited(tmp->left))
        {
            st = stackPush(st,tmp);
            tmp = tmp->left;
        }
        if(tmp->right && !checkVisited(tmp->right))
        {
            st = stackPush(st,tmp);
            tmp = tmp->right;
            continue;
        }
        else
        {
            visit(tmp);
            tmp = stackTop(st);
            st = stackPop(st);
        }
    }
    stackDestory(st);
}

/*
 Give me a pointer of the root,I will return you a tree.
 */
t_node* autoBuildTree(t_node* n,int data,int floor)
{
    if(floor <= 0) return NULL;
    n = (t_node*)malloc(sizeof(t_node));
    n->data = data;
    n->visited = 1;
    n->left = autoBuildTree(n->left,data*2,floor-1);
    n->right = autoBuildTree(n->right,data*2+1,floor-1);
    return n;
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
    //root->right = (t_node*)malloc(sizeof(t_node));
    //root->right->data = 100;
    //root->right->visited = 1;
    treeFrontVisit1(root);
    printf("\n");
    treeFrontVisit2(root);
    printf("\n");
    treeFrontVisit3(root);
    printf("\n");
    printf("\n");
    treeMiddleVisit1(root);
    printf("\n");
    treeMiddleVisit2(root);
    printf("\n");
    printf("\n");
    treeEndVisit1(root);
    printf("\n");
    treeEndVisit2(root);
    printf("\n");
    
    return 0;
}
