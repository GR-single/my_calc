//完美的表达式求值
#include<iostream>
using namespace std;
typedef struct node{
    double shu;
    char suanfu;
    int leixing;
    struct node *next;
}node,*pnode;

//链栈
class lzhan{
    pnode zhanding;
    int changdu;
    public:
    lzhan(){zhanding=NULL;changdu=0;}
    int iszhankong(){
        return zhanding==NULL;
    }
    void push(node data){
        pnode p;
        p=new node;
        *p=data;
        p->next=zhanding;
        zhanding=p;
        changdu++;
    }
    pnode pop(){
        if(iszhankong())return NULL;
        pnode jishan;
        jishan=zhanding;
        zhanding=zhanding->next;
        jishan->next=NULL;
        return jishan;
    }
    pnode kanding(){
        return zhanding;
    }
};
int isshu(char x){
    if(x>='0'&&x<='9'||x=='.')return 1;
    else return 0;
}
int youxian(pnode ding,char b){
    if(ding==NULL)return 1;
    char a;
    a=ding->suanfu;
    if(b=='(')return 1;
    if(b==')')return 0;
    if((b=='*'||b=='/')&&(a=='+'||a=='-'))return 1;
    if(a=='('&&b!=')'||b=='(')return 1;
    
    return 0;
}
double cifang(int x,int ci){
    int i;
    double s=1;
    for(i=0;i<ci;i++){
        s=s*x;
    }
    return s;
}
double zhuanhuan(char x[10],int k){
    int i,j;
    j=0;
    int douhao=0;
    double jieguo;
    jieguo=0;
    for(i=0;i<k;i++){
        if(x[i]=='.'){douhao=1;continue;}
        if(douhao==0){
            jieguo=jieguo*10+x[i]-48;
        }else{
            j++;
            jieguo=jieguo+(x[i]-48)/cifang(10,j);
        }
    }
    return jieguo;
}
pnode shuru(){
    pnode zu;
    zu=new node[30];
    char biaodashi[100];
    char temp[10];
    int k=0;
    cin>>biaodashi;
    int i;
    int j=0;
    for(i=0;biaodashi[i]!='\0';i++){
        if(isshu(biaodashi[i])){
            if(isshu(biaodashi[i+1]))
                temp[k++]=biaodashi[i];
            else {
                temp[k++]=biaodashi[i];
                zu[j].leixing=0;
                zu[j].shu=zhuanhuan(temp,k);
                k=0;
                j++;
            }
        }else{
            zu[j].leixing=1;
            zu[j].suanfu=biaodashi[i];
            j++;
        }
    }
    zu[j].leixing=-1;
    return zu;
}
pnode zhonghou(pnode zhong){
    lzhan z;
    pnode hou;
    hou=new node[30];
    int i,k=0;
    for(i=0;zhong[i].leixing!=-1;i++){
        if(zhong[i].leixing==0){
            hou[k++]=zhong[i];     
        }else{
            while(1){
                if(youxian(z.kanding(),zhong[i].suanfu)){
                    z.push(zhong[i]);
                    break;
                }else {
                    pnode p=z.pop();
                    if(p->suanfu!='('){
                        hou[k++]=*p;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    while(!z.iszhankong()){
        hou[k++]=*(z.pop());
    }
    hou[k++]=zhong[i];
    return hou;
}
double jisuan(pnode hou){
    int i;
    lzhan z;
    double jieguo;
    for(i=0;hou[i].leixing!=-1;i++){
        if(hou[i].leixing==0){
            z.push(hou[i]);
        }else{
            double a,b;
            char c;
            c=hou[i].suanfu;
            a=z.pop()->shu;
            b=z.pop()->shu;
            switch(c){
                case '+':{
                    jieguo=a+b;
                    node unwill;
                    unwill.leixing=0;
                    unwill.shu=jieguo;
                    z.push(unwill);
                    break;
                }
                case '-':{
                    jieguo=a-b;
                    node unwill;
                    unwill.leixing=0;
                    unwill.shu=jieguo;
                    z.push(unwill);
                    break;
                }
                case '*':{
                    jieguo=a*b;
                    node unwill;
                    unwill.leixing=0;
                    unwill.shu=jieguo;
                    z.push(unwill);
                    break;
                }
                case '/':{
                    jieguo=b/a;
                    node unwill;
                    unwill.leixing=0;
                    unwill.shu=jieguo;
                    z.push(unwill);
                    break;
                }
            }
        }
    }
    return z.pop()->shu;
}
void shuchu(pnode shuzu){
    int i;
    for(i=0;shuzu[i].leixing!=-1;i++){
        if(shuzu[i].leixing==0)cout<<shuzu[i].shu;
        if(shuzu[i].leixing==1)cout<<shuzu[i].suanfu;
    }
    cout<<endl;
}
int main(){
    pnode zbds,hbds;
    zbds=shuru();
    shuchu(zbds);
    hbds=zhonghou(zbds);
    shuchu(hbds);
    cout<<(jisuan(hbds));
    return 0;
}