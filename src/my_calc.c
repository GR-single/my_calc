#include"../include/my_link.h"
#define NUMBER        0
#define DOT           1
#define OTHER_CHAR    2
#define LEFT_BRACKET  1
#define RIGHT_BRACKET 2
#define OP_ADD        3
#define OP_SUB        4
#define OP_RIDE       6
#define OP_DIV        7


int type_of(char c){
    int res = 0;
    if(c == '.')return DOT;
    if(c>='0' && c<='9')return NUMBER;
    return OTHER_CHAR;
}

double * parse_number_string(char * number_string){
    double num = 0;
    int dot_flag = 0;
    int afdot_num_n = 10;
    for(int i=0;number_string[i]!='\0';i++){
        if(type_of(number_string[i]) == DOT){
            dot_flag = 1;
        }
        else if(dot_flag == 0) {
            num = num * 10 + number_string[i] - 48; 
        }
        else if(dot_flag == 1) {
            num = num +  (number_string[i] - 48.0) / afdot_num_n;
            afdot_num_n *= 10;
        }
    }
    double * res = (double *)malloc(sizeof(double));
    *res = num;
    return res;
}

int parse_expression(char * expression, plink_node p_n){
    int res_n = 0;
    char number_string[10];
    int number_i = 0;
    int e_n = strlen(expression);
    for(int i=0; i < e_n+1; i++){
        switch(type_of(expression[i])){
            case DOT:
            case NUMBER: {
                number_string[number_i++] = expression[i];
                break;
            }
            case OTHER_CHAR: {
                number_string[number_i] = '\0';
                if(number_i != 0){
                    p_n[res_n].content_type = NUMBER;
                    p_n[res_n].pcontent = parse_number_string(number_string);
                    res_n++;
                }
                switch(expression[i]){
                    case '(':{
                        p_n[res_n].content_type = LEFT_BRACKET;
                        break;
                    }
                    case ')':{
                        p_n[res_n].content_type = RIGHT_BRACKET;
                        break;
                    }
                    case '+':{
                        p_n[res_n].content_type = OP_ADD;
                        break;
                    }
                    case '-':{
                        p_n[res_n].content_type = OP_SUB;
                        break;
                    }
                    case '*':{
                        p_n[res_n].content_type = OP_RIDE;
                        break;
                    }
                    case '/':{
                        p_n[res_n].content_type = OP_DIV;
                        break;
                    }
                    default:break;
                }
                res_n++;
                number_i = 0;
                break;
            }
            default: break;
        }
    }

    return res_n - 1;
}

int generate_flag(pmy_stack m_s, int type_of_current){
    if(m_s->stack_length == 0)return 1;
    if(type_of_current == LEFT_BRACKET)return 1;
    int type_of_s_top = m_s->stack_top->content_type;
    if(type_of_current - type_of_s_top > 1)return 1;
    return 0;
}

void expr_infix_to_suffix(plink_node expr_node_table, int expr_node_n, plink_node expr_node_suffix){
    my_stack s_1;
    memset(&s_1, 0, sizeof(my_stack));
    int su_i = 0;
    for(int in_i = 0; in_i < expr_node_n; in_i++){
        switch(expr_node_table[in_i].content_type){
            case NUMBER: {
                expr_node_suffix[su_i] = expr_node_table[in_i];
                expr_node_suffix[su_i].pcontent = (double *)malloc(sizeof(double));
                *(double *)(expr_node_suffix[su_i].pcontent) = *(double *)(expr_node_table[in_i].pcontent);
                su_i++;
                break;
            }
            default: {
                while(1){
                    int flag = generate_flag(&s_1, expr_node_table[in_i].content_type);
                    if(flag) {
                        push(&s_1, expr_node_table+in_i);
                        break;
                    }
                    else {
                        link_node t_l_n;
                        memset(&t_l_n, 0, sizeof(link_node));
                        pop(&s_1, &t_l_n);
                        if(t_l_n.content_type != LEFT_BRACKET) {
                            expr_node_suffix[su_i] = t_l_n;
                            su_i++;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
    }
    while(s_1.stack_length != 0){
        link_node t_l_n;
        memset(&t_l_n, 0, sizeof(link_node));
        pop(&s_1, &t_l_n);
        expr_node_suffix[su_i] = t_l_n;
        su_i++;
    }
}

double parse_suffix(plink_node expr_node_suffix, int expr_node_n){
    double res = 0;
    my_stack s_1;
    memset(&s_1, 0, sizeof(my_stack));
    for(int su_i = 0; su_i < expr_node_n; su_i++){
        switch(expr_node_suffix[su_i].content_type){
            case NUMBER:{
                push(&s_1, expr_node_suffix+su_i);
                break;
            }
            case OP_ADD:{
                link_node t_l_n;
                memset(&t_l_n, 0, sizeof(link_node));
                pop(&s_1, &t_l_n);
                double op_num_1 = *(double *)(t_l_n.pcontent);
                pop(&s_1, &t_l_n);
                double op_num_2 = *(double *)(t_l_n.pcontent);
                *(double *)(t_l_n.pcontent) = op_num_1 + op_num_2;
                push(&s_1, &t_l_n);
                break;
            }
            case OP_SUB:{
                link_node t_l_n;
                memset(&t_l_n, 0, sizeof(link_node));
                pop(&s_1, &t_l_n);
                double op_num_1 = *(double *)(t_l_n.pcontent);
                pop(&s_1, &t_l_n);
                double op_num_2 = *(double *)(t_l_n.pcontent);
                *(double *)(t_l_n.pcontent) = op_num_2 - op_num_1;
                push(&s_1, &t_l_n);
                break;
            }
            case OP_RIDE:{
                link_node t_l_n;
                memset(&t_l_n, 0, sizeof(link_node));
                pop(&s_1, &t_l_n);
                double op_num_1 = *(double *)(t_l_n.pcontent);
                pop(&s_1, &t_l_n);
                double op_num_2 = *(double *)(t_l_n.pcontent);
                *(double *)(t_l_n.pcontent) = op_num_1 * op_num_2;
                push(&s_1, &t_l_n);
                break;
            }
            case OP_DIV:{
                link_node t_l_n;
                memset(&t_l_n, 0, sizeof(link_node));
                pop(&s_1, &t_l_n);
                double op_num_1 = *(double *)(t_l_n.pcontent);
                pop(&s_1, &t_l_n);
                double op_num_2 = *(double *)(t_l_n.pcontent);
                *(double *)(t_l_n.pcontent) = op_num_2 / op_num_1;
                push(&s_1, &t_l_n);
                break;
            }
            default:break;
        }
    }
    link_node l_n;
    pop(&s_1, &l_n);
    return *(double *)(l_n.pcontent);
}

void run_my_calc(char * expression){
    
    link_node expr_node_table[30];
    link_node expr_node_suffix[30];
    memset(expr_node_table,0,sizeof(link_node)*30);
    memset(expr_node_suffix,0,sizeof(link_node)*30);
    int expr_node_n = parse_expression(expression, expr_node_table);
    expr_infix_to_suffix(expr_node_table, expr_node_n, expr_node_suffix);
    double res = parse_suffix(expr_node_suffix, expr_node_n);
    printf(">>%f\n", res);
    for(int i=0;i<expr_node_n;i++){
        if(expr_node_table[i].pcontent!=NULL){
            free(expr_node_table[i].pcontent);
        }
        if(expr_node_suffix[i].pcontent!=NULL){
            free(expr_node_suffix[i].pcontent);
        }
    }
}


int main(int argc, char * argv[]){
    printf("welcome to my calc.\n");
    while(1){
        printf(">:");
        char expression[50];
        scanf("%s", expression);
        if(expression[0] == 'q')break;
        run_my_calc(expression);
    }
    printf("bye.\n");
    return 0;
}