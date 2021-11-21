struct Node* l_root=NULL;                    //Root of the left tree obtained after splitting
struct Node* r_root=NULL;                    //Root of the right tree obtained after splitting

void treapSplit(struct Node* root, int pivot)
{
    if(search(root,pivot)!=NULL){   //if element is already present in the treap
    root=delete_Node(root,pivot);        //deleting the node
    //Assign maximum possible priority to the node with key value 'pivot'
    //So that, when x is inserted into the treap, it becomes the root node (so as to obey Max-Heap property)
    root=Insert(root,pivot,0);  
    l_root = root;             //left sub-tree including the node across which split was performed
    r_root = root->right;      //right sub-tree
    root->right = NULL;            
    root = NULL;

    //assigning the priority to the element at the Head node so as to ensure the max-Heap property
    if(l_root->left!=NULL && l_root->right!=NULL){   
    if(l_root->left->pr>l_root->right->pr){
        l_root->pr = l_root->left->pr + 1;
    }
    else{
        l_root->pr = l_root->right->pr+1;
    }
    }
    else if(l_root->left==NULL && l_root->right!=NULL){
        l_root->pr = l_root->right->pr+1;
    }
    else if(l_root->left!=NULL && l_root->right==NULL){
        l_root->pr = l_root->left->pr+1;
    }
    else{
        l_root->pr = 1;
    }
    }
    else{
    //Assign maximum possible priority to the node with key value 'pivot'
    //So that, when x is inserted into the treap, it becomes the root node (so as to obey Max-Heap property)

    root=Insert(root,pivot,0);

    l_root = root->left;   //left subtree
    r_root = root->right;  //right subtree
    root->left = NULL;
    root->right = NULL;
    }
}
