#include <iostream>
#include <string.h>
using namespace std;

class stack_structure
{
public:
    int size;
    int top;
    char *s;
};

class stack
{
public:
    stack_structure *st = new stack_structure;

    void create(int len);
    void display();
    void push(char x);
    char pop();
    int outprecedence2(char x);
    int isOperand(char x);
    char *infix_to_postfix2(char *infix);
};

void stack ::create(int len)
{
    st->size = len;
    st->top = -1;
    st->s = new char[st->size];
}

void stack ::display()
{
    for (int i = st->top; i >= 0; i--)
    {
        cout << st->s[i] << endl;
    }
}

void stack ::push(char x)
{
    if (st->top == st->size - 1)
    {
        cout << "stack overflow" << endl;
    }
    else
    {
        st->top++;
        st->s[st->top] = x;
    }
}

char stack ::pop()
{
    int x = -1;
    if (st->top == -1)
    {
        cout << "stack underflow" << endl;
    }
    else
    {
        x = st->s[st->top--];
    }
    return x;
}

int stack ::outprecedence2(char x)
{
    if (x == '+' || x == '-')
    {
        return 1;
    }
    else if (x == '*' || x == '/')
    {
        return 3;
    }
    else if (x == '^')
    {
        return 6;
    }
    else if (x == '(')
    {
        return 7;
    }
    else if (x == ')')
    {
        return 0;
    }
}

int stack ::isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char *stack ::infix_to_postfix2(char *infix)
{
    int i = 0, j = 0;
    char *postfix;
    int length = strlen(infix);
    create(length + 2);
    push('#');
    postfix = new char[length + 2]; // ( # and /0 )because we push hash first since it will give error otehrwise
    while (infix[i] != '\0')
    {
        if (isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        else
        {
            if (outprecedence2(infix[i]) >= outprecedence2(st->s[st->top]) && infix[i] != ')' && infix[i] != '(')
            {
                push(infix[i++]);
            }
            else if (st->s[st->top] == '(')
            {
                push(infix[i++]);
            }
            else if (infix[i] == ')')
            {
                while (st->s[st->top] != '(')
                {
                    if (st->s[st->top] == '(' || st->s[st->top] == ')')
                    {
                        pop();
                    }
                    else
                    {
                        postfix[j++] = pop();
                    }
                }
            }
            else if (infix[i] == '(')
            {
                cout << "hello" << endl;
                push(infix[i++]);
            }
        }
    }
    while (st->top > 0)
    {
        if (st->s[st->top] == '(' || st->s[st->top] == ')' || st->s[st->top] == '#')
        {
            pop();
        }
        else
        {
            postfix[j++] = pop();
        }
    }
    return postfix;
}

int main()
{
    char *infix = "((a+b)*c)-d^e^f";
    stack st1;
    char *postfix = st1.infix_to_postfix2(infix);
    cout << "post is: " << postfix << endl;
}
