struct Node{                            //struct Node which
    int key;                            //stores the key value of the node
    int pr;                             //stores the priority of each node
    struct Node* left;                  //pointer to the left child
    struct Node* right;                 //pointer to the right child
};

struct Node* l_root=NULL;                    //Root of the left tree obtained after splitting
struct Node* r_root=NULL;                    //Root of the right tree obtained after splitting

struct Node* New_Node(int k,int p){                              //New Node containing key and priority
    struct Node*New = (struct Node*)malloc(sizeof(struct Node)); 
    New->key = k;                                                
    New->left = NULL;                                            
    New->right = NULL;
    New->pr = p;
    return New;
}
