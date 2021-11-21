struct Node* rightRotate(struct Node* y)  //Function to right rotate the sub-tree rooted at y 
{
    struct Node* x = y->left;              //x=left child of y node
    struct Node* z = x->right;             //z=right child of x node

    //Right Rotation
    x->right = y;
    y->left = z;

    return x;                             //returning the new parent node of the subtree
}
