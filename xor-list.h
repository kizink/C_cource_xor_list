#ifndef XOR_LIST_H
#define XOR_LIST_H
struct Node{
  long long data;
  struct Node *ptr;
};

struct Xorlist{
  struct Node *p1;
  struct Node *p2;
  struct Node *head;
  struct Node *tail;
  long long size;
  long long curr_pos;
};

struct Node *xor_ptr(struct Node *a, struct Node *b);
int next(struct Xorlist* l);
int prev(struct Xorlist *l);
int move_to(struct Xorlist *l, long long pos);
int insert(struct Xorlist *l, long long pos, long long data);
int erase(struct Xorlist* l, long long pos);
void delete_xor_list(struct Xorlist *l);
void print_xor_list(struct Xorlist *l);
void init_xor_list(struct Xorlist *l);
#endif
