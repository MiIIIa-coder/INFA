#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

struct tree_t {
    struct tree_t *left;
    struct tree_t *right;
    int data;
};

#if 0

int check(struct tree_t *top, int min, int max)
{
    int lim = 0;
    if (top == NULL)
        return 1;

    lim = top->data;
    if (lim > min && lim < max) {
        if (check(top->left, min, lim) == 0)
            return 0;

        if (check(top->right, lim, max) == 0)
            return 0;
    } else
        return 0;
    return 1;

}

int check_is_bst(struct tree_t *top)
{

    return check(top, INT_MIN, INT_MAX);

}

#endif

struct tree_t *create_root(struct tree_t *root)
{
    root = (struct tree_t*)malloc(sizeof(struct tree_t));
    root->left  = NULL;
    root->right = NULL;
    root->data = 0;

    return root;
}

void create_b_tree(struct tree_t **root, int vol, int index)
{
    int node = 0;

    if (index == vol)
        return;
    scanf("%d", &node);
    if (node == 1) {
        *root = create_root(*root);
        ++index;
        create_b_tree(&((*root)->left), vol, index);
    } //else root->left = NULL;

    if (index == vol)
        return;
    scanf("%d", &node);
    if (node == 1) {
        ++index;
        create_b_tree(&((*root)->right), vol, index);
    } //else root->right = NULL;

}

void print_b_tree(struct tree_t *root)
{

    printf("%d ", root->data);
    if (root->left != NULL) {
        print_b_tree(root->left);
    } else if (root->right != NULL)
        print_b_tree(root->right);

}


int main()
{
    struct tree_t **tree;
    int vol = 0;
    int index = 0;

    scanf("%d", &vol);

    tree = (struct tree_t **)calloc(vol, sizeof(struct tree_t *));
    create_b_tree(tree, vol, index);

    printf("\n");
    if (tree != NULL)
        print_b_tree(*tree);

    return 0;
}
