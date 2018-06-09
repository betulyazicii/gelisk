//
//  main.c
//  Homework5
//
//  Created by Betul Yazıcı on 26.05.2018.
//  Copyright © 2018 Betul Yazıcı. All rights reserved.
//
#include <stddef.h>
#include <string.h>
#include<stdio.h>
#include<ctype.h>

#define MAX 50  //number of stack size and input element size

typedef struct STACK
{
    int data[MAX];
    int top;
}Stack;

int findPriorityGivenExpression(char); // return priority of symbol
void initialize(Stack *);//initialize stack
int isEmpty(Stack *);// control stack empty or not
int isFull(Stack *);// control stack full or not
int pop(Stack *);// pop get elements to stack top elements
void push(Stack *,int);
int top(Stack *);   //value of the top element
void convertInfixToPostfix(char infix[],char postfix[]);
void resolvePostfixOperation(char postfix[]);

int main()
{
    
    char postfix[MAX];
   //char infix[MAX];
    char inputString[MAX]="z = 3 + 14 * 5;" ;
    //char inputString[MAX];
    printf("Enter an infix expression(eg: 5+2*4): formatted");
   // gets(inputString);
   
    const char delimiters[] = "=";
    char * infix = strdup(inputString);
    char * result;
    result = strsep(&infix, delimiters);
    convertInfixToPostfix(infix,postfix);
    printf("\nPostfix expression: %s\n",postfix);
    resolvePostfixOperation(postfix);
    
    
}
void resolvePostfixOperation(char postfix[]){
    Stack stack;
    initialize(&stack);
    int i=0,op1,op2;
    char ch;
    
    while( (ch=postfix[i++]) != '\0'){
        if(isdigit(ch))
            push(&stack,ch-'0'); /* Push the operand */
        else if (ch != ' '){
            op2=pop(&stack);
            op1=pop(&stack);
            
        }
        switch(ch)
        {
            case '+':push(&stack,op1+op2);break;
            case '-':push(&stack,op1-op2);break;
            case '*':push(&stack,op1*op2);break;
            case '/':push(&stack,op1/op2);break;
                
        }
    }
    
    printf("\n Result after Evaluation: %d\n",stack.data[stack.top]);
    

    
    
}

int stopControl(int i,char infix[]){
    if(i<MAX && infix[i] !='\0' && infix[i] !=';')
        return 0;
    else return 1;
}
void convertInfixToPostfix(char infix[],char postfix[])
{
    Stack stack;
    char x,token;
    int i=0,j=0;    //i-index of infix,j-index of postfix
    initialize(&stack);
 
    while(!stopControl(i,infix))
    {
        token=infix[i];
        if(isalnum(token))
            postfix[j++]=token;
        else
            if(token=='(')
                push(&stack,'(');
            else
                if(token==')')
                    while((x=pop(&stack))!='(')
                        postfix[j++]=x;
        
                    else
                {
                    while(findPriorityGivenExpression(token)<=findPriorityGivenExpression(top(&stack))&&!isEmpty(&stack))
                    {
                        x=pop(&stack);
                        postfix[j++]=x;
                    }
                    push(&stack,token);
                }
        i++;
    }
    
    while(!isEmpty(&stack))
    {
        x=pop(&stack);
        postfix[j++]=x;
    }
    postfix[j]='\0';
}

int findPriorityGivenExpression(char x)
{
    if(x=='(')
        return 0;
    if(x=='+'||x=='-')
        return 1;
    if(x=='*'||x=='/'||x=='%')
        return 2;
    
    return 3;
}

void initialize(Stack *s)
{
    s->top=-1;
    
}

int isEmpty(Stack *s)
{
    if(s->top==-1)
        return 1;
    
    return 0;
}

int isFull(Stack *s)
{
    if(s->top==MAX-1)
        return 1;
    
    return 0 ;
}

void push(Stack *s,int x)
{
    s->top=s->top+1;
    s->data[s->top]=x;
}

int pop(Stack *s)
{
    int x;
    x=s->data[s->top];
    s->top=s->top-1;
    return x ;
}

int top(Stack *p)
{
    return (p->data[p->top]);
}
