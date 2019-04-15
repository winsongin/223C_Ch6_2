#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *left;
struct tnode *talloc(void);
struct key *binsearch(char *, struct key*, int);
int getword(char *, int);   /* word frequency count */

struct tnode {     /* the tree node: */
  char *word;           /* points to the text */
  int count;            /* number of occurrences */
  struct tnode *left;   /* left child */
  struct tnode *right;  /* right child */
};

struct key *binsearch(char * word, struct key* tab, int n){
  int cond;
  struct key *low = &tab[0];
  struct key *high = &tab[n];
  struct key *mid;
   while (low < high) {
     mid = low + (high-low) / 2;
     if ((cond = strcmp(word, mid->word)) < 0)
     high = mid;
     else if (cond > 0)
     low = mid + 1;
     else
     return mid;
   }
   return NULL;
}

int main(){
  struct tnode *root;
  char word[MAXWORD];
  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0])){
      root = addtree(root, word);
    }
  treeprint(root);
  return 0;
}

struct tnode *addtree(struct tnode *p, char *w)   {
  int cond;
  if (p == NULL) {     /* a new word has arrived */
    p = talloc();    /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  }
  else if ((cond = strcmp(w, p->word)) == 0){
    p->count++;
  }      /* repeated word */
  else if (cond < 0){   /* less than into left subtree */
    p->left = addtree(p->left, w);
  }
  else{             /* greater than into right subtree */
    p->right = addtree(p->right, w);
  }
  return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p){
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

/* talloc:  make a tnode */
struct tnode *talloc(void){
  return (struct tnode *) malloc(sizeof(struct tnode));
}
