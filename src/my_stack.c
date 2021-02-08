#include"../include/my_link.h"


void push(pmy_stack m_s, plink_node s_p_n){
    if(m_s->stack_length == 0){
        m_s->stack_top = (plink_node)(malloc(sizeof(link_node)));
        m_s->stack_length++;
        m_s->stack_top->next = NULL;
        m_s->stack_top->pre = NULL;
        m_s->stack_top->content_type = s_p_n->content_type;
        m_s->stack_top->pcontent = NULL;
        if(s_p_n->pcontent != NULL) {
            m_s->stack_top->pcontent = malloc(sizeof(double));
            *(double *)(m_s->stack_top->pcontent) = *(double *)(s_p_n->pcontent);
        }
    }
    else {
        m_s->stack_length++;
        m_s->stack_top->next = (plink_node)(malloc(sizeof(link_node)));
        plink_node old_top = m_s->stack_top;
        m_s->stack_top = m_s->stack_top->next;
        m_s->stack_top->pre = old_top;
        m_s->stack_top->content_type = s_p_n->content_type;
        m_s->stack_top->pcontent = s_p_n->pcontent;
        if(m_s->stack_top->pcontent != NULL){
            m_s->stack_top->pcontent = (double *)malloc(sizeof(double));
            *(double *)(m_s->stack_top->pcontent) = *(double *)(s_p_n->pcontent);
        }
        m_s->stack_top->next = NULL;
    }
}

int pop(pmy_stack m_s, plink_node d_p_n){
    if(m_s->stack_length == 0){
        printf("stack empty.\n");
        return 1;
    }
    else {
        d_p_n->content_type = m_s->stack_top->content_type;
        plink_node old_top = m_s->stack_top;
        m_s->stack_top = old_top->pre;
        if(old_top->pcontent != NULL){
            d_p_n->pcontent = malloc(sizeof(double));
            *(double *)(d_p_n->pcontent) = *(double *)(old_top->pcontent);
            free(old_top->pcontent);
        }
        free(old_top);
        m_s->stack_length--;
        if(m_s->stack_length!=0)
        m_s->stack_top->next = NULL;
        return 0;
    }
    return 0;
}