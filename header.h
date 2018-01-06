typedef struct stack
{
        int top;
        unsigned capacity;
        char *array;

}STACK;

STACK *CreateStack(unsigned);
int isFull(STACK *);
int isEmpty(STACK *);

void push(STACK *,int);
char  pop(STACK *);
int evaluation(char exp[]);
char peek(STACK* stack);


int isOperand(char ch);
int Prec(char ch);

int infixToPostfix(char* exp);

int infixToPretfix(char* exp);

void reverse(char str[]);
