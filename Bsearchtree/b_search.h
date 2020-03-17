#define MAX 10
#define BEGIN_H 0
#define R_NUM 50
struct t_node {
    int key;
    struct t_node *left;
    struct t_node *right;
    struct t_node *p;
};
typedef struct t_node t_node;

struct t_bst {
    t_node *root;
    int elemnt;
};
typedef struct t_bst t_bst;

