#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct link_node {
    int content_type;
    void * pcontent;
    struct link_node * pre;
    struct link_node * next;
} link_node, * plink_node;

typedef struct my_stack {
    int stack_length;
    plink_node stack_top;
}my_stack, * pmy_stack;

void push(pmy_stack m_s, plink_node s_p_n);

int pop(pmy_stack m_s, plink_node d_p_n);