#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

void build_tree(int *preorder_root, int *inorder_root, int start,
                int finish, int *preorder_index, int *topolog,
                int *topolog_index)
{

    int i = 0;
    int root = 0;

    if (finish < start) {
        *(topolog + (*topolog_index)) = 0;
        ++(*topolog_index);
        return;
    }

    ++(*preorder_index);
    root = *(preorder_root + (*preorder_index));        // root value

    for (i = start; i <= finish; i++) {
        if (*(inorder_root + i) == root) {

            *(topolog + (*topolog_index)) = 1;
            ++(*topolog_index);

            build_tree(preorder_root, inorder_root, start, i - 1, preorder_index, topolog, topolog_index);      //left


            build_tree(preorder_root, inorder_root, i + 1, finish, preorder_index, topolog, topolog_index);     //right

        }
    }


}

void get_roots(int vol, int *roots)
{
    int i = 0;

    for (i = 0; i < vol; ++i) {
        scanf("%d", roots + i);
    }

}

void give_ans(int vol, int *topolog, int *preorder_root)
{

    int i = 0;

    printf("%d ", vol);

    for (i = 0; i < 2 * vol; i++)       //without last el in topolog
        printf("%d ", *(topolog + i));

    for (i = 0; i < vol; i++)
        printf("%d ", *(preorder_root + i));

}

int main()
{
    int vol = 0;

    int *preorder_index;
    int *preorder_root;
    int *inorder_root;

    int *topolog_index;
    int *topolog;

    scanf("%d", &vol);
    preorder_root = (int *) calloc(vol, sizeof(int));
    inorder_root = (int *) calloc(vol, sizeof(int));
    topolog = (int *) calloc(2 * vol + 1, sizeof(int)); //amount of leaves = vol + 1
    preorder_index = (int *) calloc(1, sizeof(int));
    topolog_index = (int *) calloc(1, sizeof(int));

    get_roots(vol, preorder_root);
    get_roots(vol, inorder_root);
    *preorder_index = -1;
    *topolog_index = 0;

    build_tree(preorder_root, inorder_root, 0, vol - 1, preorder_index, topolog, topolog_index); //vol-1 <=> index of last el

    give_ans(vol, topolog, preorder_root);


    return 0;
}
