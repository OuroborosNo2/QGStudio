#include"LinkStack.c"
//#include<stdio.h>
//#include<stdlib.h>
#include<string.h>

void infixToPostfix(ElemType *infix,ElemType *postfix);
int calculate(ElemType *postfix);

int main(){
    while(1){
        ElemType infix[100] = "";//中缀表达式
        int length_infix = 0;
        ElemType postfix[100] = "";//后缀表达式
        while(1){
        system("cls");
        printf("**************************************\n");
        printf("*            四则运算计算器          *\n");
        printf("**************************************\n");
        printf("\n");
        printf("请输入表达式（0~9，+，-，*，/，以回车结束）：\n");
        printf("infix: %s",infix);
        char c = getch();
        char *last = &infix[length_infix-1];
        if(c == 13){//回车 ('\r')
            int i;
            int num=0;
            for(i=0;i<length_infix;i++){
                if(infix[i]=='('){
                    num++;
                }else if(infix[i]==')'){
                    num--;
                }
            }
            if(num!=0){
                printf("\n左右括号必须匹配\n");
                system("pause");
                continue;
            }
            break;
        }
        switch(c){
            case 8://回退
                if(length_infix>0){
                    *last = '\0';
                    length_infix--;
                }
                break;
            case '0':case '1':case '2':case '3':case '4':
            case '5':case '6':case '7':case '8':case '9':
                if(*last != ')'){//数字前不能跟右括号
                    infix[length_infix] = c;
                    infix[length_infix+1] = '\0';
                    length_infix++;
                }
                break;
            case '+':case '-':case '*':case '/':
                if(*last!='+' && *last!='-' && *last!='*' && *last!='/' && *last!='('){//运算符前只能跟数字或右括号
                    infix[length_infix] = c;
                    infix[length_infix+1] = '\0';
                    length_infix++;
                }
                break;
            case '(':
                if(*last == '+' || *last == '-' || *last == '*' || *last == '/'){//左括号前只能跟运算符
                    infix[length_infix] = c;
                    infix[length_infix+1] = '\0';
                    length_infix++;
                }
                break;
            case ')':
                if(*last != '+' || *last != '-' || *last != '*' || *last != '/'){//右括号前不能跟运算符
                    infix[length_infix] = c;
                    infix[length_infix+1] = '\0';
                    length_infix++;
                }
                break;
        }

    }
        infixToPostfix(infix,postfix);
        printf("\npostfix: %s\n",postfix);
        printf("result: %d\n",calculate(postfix));
        system("pause");
    }
    return 1;
}
void infixToPostfix(ElemType *infix,ElemType *postfix){//中缀转后缀
    LinkStack *s;
    initLStack(&s);
    int i;
    int t=0;
    
    //注意！结合律在这里不适用，运算顺序不同可能会因为0的出现导致结果不同
    
    for(i=0;i<strlen(infix);i++){
        char c = infix[i];
        if(c>='0' && c<='9'){//数字直接输出
            postfix[t++] = c;
        }else if(c=='+' || c=='-'){
            while(1){//若当前运算符优先级低于栈顶，则一直出栈，直到当前运算符入栈
                char top;
                if(isEmptyLStack(s)){
                    pushLStack(s,c);
                    break;
                }
                getTopLStack(s,&top);
                if(top=='('){
                    pushLStack(s,c);
                    break;
                }else{
                    popLStack(s,&postfix[t++]);
                }
             }
        }else if(c=='*' || c=='/' || c=='('){//优先级高，直接入栈
            while(1){
                char top;
                if(isEmptyLStack(s)){
                    pushLStack(s,c);
                    break;
                }
                getTopLStack(s,&top);
                if(top=='(' || top=='+' || top=='-'){
                    pushLStack(s,c);
                    break;
                }else{
                    popLStack(s,&postfix[t++]);
                }
            }
        }else if(c==')'){
            char top;
            getTopLStack(s,&top);
            while(top != '('){//一直出栈直到左括号
                popLStack(s,&postfix[t++]);
                getTopLStack(s,&top);
            }
            char no_use;//左括号不输出
            popLStack(s,&no_use);
        }
    }
    while(!isEmptyLStack(s)){//一直出栈直到空
        popLStack(s,&postfix[t++]);
    }
    destroyLStack(s);
}
int calculate(ElemType *postfix){
    LinkStack *s;
    initLStack(&s);
    int i;
    for(i=0;i<strlen(postfix);i++){
        char c = postfix[i];
        if(c=='+' || c=='-' || c=='*' || c=='/'){
            char active;//主动数
            char passive;//被动数
            char result;
            popLStack(s,&passive);
            popLStack(s,&active);
            switch(c){
                case '+':
                    result = (active-'0')+(passive-'0')+'0';
                    break;
                case '-':
                    result = (active-'0')-(passive-'0')+'0';
                    break;
                case '*':
                    result = (active-'0')*(passive-'0')+'0';
                    break;
                case '/':
                    result = (active-'0')/(passive-'0')+'0';
                    break;
            }
            pushLStack(s,result);
        }else{//运算结果可能是多位数，char无法储存，故不判断0~9，直接以其ascii码作为数值
            pushLStack(s,c);
        }
    }
    char finalResult;
    popLStack(s,&finalResult);
    return finalResult-'0';
}