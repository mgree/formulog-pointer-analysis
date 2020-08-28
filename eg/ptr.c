#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *next;
};

void print_list(struct node *l) {
  printf("[");

  for (; l != NULL; l = l->next) {
    printf("%d @ %p", l->value, l);

    if (l->next != NULL) {
      printf("; ");
    }
  }

  printf("]\n");
}

void copy(struct node *src, struct node *tgt) {
  for (; src != NULL; src = src->next, tgt = tgt->next) {
    tgt->value = src->value;
  }
}

int main(int argc, char *argv[]) {
  struct node *p = (struct node*) malloc(sizeof(struct node));
  struct node *q = (struct node*) malloc(sizeof(struct node));

  printf("p = %p\nq = %p\n", p, q);

  p->value = 12;
  p->next  = q;
  q->value = 20;
  q->next  = NULL;

  /*
  print_list(p);
  print_list(p);
  print_list(q);
  printf("p = %p\nq = %p\n", p, q);
  */
  
  copy(p, p);
  print_list(p);
  print_list(q);
  printf("p = %p\nq = %p\n", p, q);

  /*
  copy(p, q);
  print_list(p);
  print_list(q);
  printf("p = %p\nq = %p\n", p, q);
  */
  
  copy(q, p);
  print_list(p);
  print_list(q);
  printf("p = %p\nq = %p\n", p, q);

  return 0;
}
