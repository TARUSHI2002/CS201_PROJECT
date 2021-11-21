struct Node* delete_Node(struct Node* root,int val)    //function to delete a node
{
    if(search(root,val)==NULL)                         //Check if element to be deleted is present or not
    {
     printf("Element to be deleted not present in Treap. exiting...\n");
     return root;
    } 
    
    if(root==NULL)                                     //if treap is empty
    return root;

    if(val < root->key)                               //if key is in left sub-tree
    root->left = delete_Node(root->left,val);

    else if(val > root->key)                          //if key is in right sub-tree
    root->right = delete_Node(root->right, val);


    //If key is at Root

    //If the left child of the key is NULL
    else if(root->left == NULL)
    {
        //Make right child as root node
        struct Node* temp = root->right;
        //root=NULL;
        free(root);
        root=temp;
        //return root;
    }

    //If the right child of the key is NULL
    else if(root->right == NULL)
    {
        //Make left child as root node 
        struct Node* temp = root->left;
        //root=NULL;
        free(root);
        root=temp;
        //return root;
    }

    //If both left and right child of the root(key) are not NULL
    //maintaining the heap property and deleting the node
    else if(root->left->pr < root->right->pr)               
    {
        root = leftRotate(root);                      
        root->left = delete_Node(root->left,val);
    }
    else
    {
        root = rightRotate(root);
        root->right = delete_Node(root->right, val);
    }
    return root;        //returning the root
}
