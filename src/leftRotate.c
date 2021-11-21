struct Node* leftRotate(struct Node* x)  //Function to left rotate the sub-tree rooted at x 
{
    struct Node* y = x->right;           //y=right child of x node
    struct Node* z = y->left;            //z=left child of y node

    //Left Rotation
    y->left = x;                         
    x->right = z;

    return y;                           //returning the new parent node of the sub-tree
}
