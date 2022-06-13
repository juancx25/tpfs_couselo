#ifndef BTREE_BASE_H_INCLUDED
#define BTREE_BASE_H_INCLUDED

#define t_elem_btree int
typedef struct _btn {
    t_elem_btree value;
    struct _btn *left;
    struct _btn *right;
} btn;

btn* btn_new(t_elem_btree value);
void btn_free(btn** node);
btn** btn_find(btn** node, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree));
int btn_isLeaf(btn *node);
int btn_count(btn *node);
int btn_insert(btn **node, btn *newNode);
int btn_insert_value(btn **node, int value);
int _btn_level(btn *node, t_elem_btree value, int level, int cmp(t_elem_btree, t_elem_btree));
int btn_level(btn* root, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree));
int _max(int a, int b);
t_elem_btree btn_height(btn *node);
void btn_inorder(btn *node, void btn_do(btn*, void*), void* ctx);
void btn_postorder(btn *node, void btn_do(btn*, void*), void* ctx);
void btn_preorder(btn *node, void btn_do(btn*, void*), void* ctx);

#endif // BTREE_BASE_H_INCLUDED
