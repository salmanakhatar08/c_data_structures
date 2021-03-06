/* Infix to Postfix conversion and its evaluation */ 

#include < stdio.h > 
#include < conio.h >
void push(char m, int * t, char * stk) {
  if ( * t == 99)
    printf("\nStack is full.");
  else {
    ( * t) ++;
    stk[ * t] = m;
  }
}
/////////////////////
char pop(char * stk, int * t) {
  char n;
  if ( * t == -1)
    return (-1);
  else {
    n = stk[ * t];
    ( * t) --;
    return (n);
  }
}
/////////////////////
void push_val(int m, int * t, int * stk) {
  if ( * t == 99)
    printf("\nStack is full.");
  else {
    ( * t) ++;
    stk[ * t] = m;
  }
}
///////////////////
int pop_val(int * stk, int * t) {
  int n;
  if ( * t == -1)
    return;
  else {
    n = stk[ * t];
    ( * t) --;
    return (n);
  }
}
//////////////
//////////////
int priority(char ele) {
  int prio;
  if (ele == '*' || ele == '/' || ele == '%')
    prio = 4;
  else if (ele == '+' || ele == '-')
    prio = 3;
  else if (ele == '(')
    prio = 2;
  else
    prio = 1;
  return (prio);
}
////////////////////
void eve_post(char * post) {
  int stack[100], i = 0, op1, op2, top = -1, exp, n;
  while (post[i] != '\0') {
    if (post[i] >= 97 && post[i] <= 123) {
      printf("\nEnter value of %c: ", post[i]);
      scanf("%d", & n);
      push_val(n, & top, stack);
      i++;
    } else {
      op1 = pop_val(stack, & top);
      op2 = pop_val(stack, & top);
      switch (post[i]) {
      case '+':
        exp = op2 + op1;
        break;
      case '-':
        exp = op2 - op1;
        break;
      case '/':
        exp = op2 / op1;
        break;
      case '*':
        exp = op2 * op1;
        break;
      default:
        printf("\nOperator not found.");
      }
      push_val(exp, & top, stack);
      i++;
    }
  }
  printf("\nAnswer from post-fix expression is: %d", pop_val(stack, & top));
}
////////////////////
void main() {
  char n, n1, infix[100], postfix[100], stack[100];
  int top = -1, j = 0, k = 0;
  clrscr();
  printf("\nEnter infix string: ");
  gets(infix);
  while (infix[j] != '\0') {
    if (infix[j] == ' ' || infix[j] == '\t') {
      j++;
      continue;
    } else if ((infix[j] >= 97 && infix[j] <= 123) || (infix[j] >= 65 && infix[j] <= 91) || (infix[j] >= 48 && infix[j] <= 57)) {
      postfix[k] = infix[j];
      k++;
      j++;
    } else if (infix[j] == '+' || infix[j] == '-' || infix[j] == '*' || infix[j] == '/' || infix[j] == '%') {
      if (top == -1)
        push(infix[j], & top, & stack[0]);
      else {
        n = (char) pop(stack, & top);
        while (priority(n) >= priority(infix[j])) {
          postfix[k] = n;
          k++;
          n = (char) pop(stack, & top);
        }
        push(n, & top, & stack[0]);
        push(infix[j], & top, stack);
      }
      j++;
    } else if (infix[j] == '(') {
      push(infix[j], & top, stack);
      j++;
    } else if (infix[j] == ')') {
      n1 = (char) pop(stack, & top);
      while (n1 != '(') {
        postfix[k] = n1;
        k++;
        n1 = (char) pop(stack, & top);
      }
      j++;
    } else
      j = j;
  }
  while (top != -1) {
    n1 = (char) pop(stack, & top);
    postfix[k] = n1;
    k++;
  }
  printf("Postfix string: ");
  postfix[k] = NULL;
  puts(postfix);
  eve_post(postfix);
  getch();
}