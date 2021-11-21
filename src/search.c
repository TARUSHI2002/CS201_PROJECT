struct Node* search(struct Node* root,int val)      //searching a node
{

    //if the root node is NULL or has a key value equal to the value searched, then return the root node
    if(root==NULL || root->key==val)
    return root;
    
    //if the root node's key value is greater than the value searched, then search for the value in left sub-tree of the root node
    if(root->key > val)
    return search(root->left,val);

    //if the root node's key value is less than the value searched, then search for the value in right sub-tree of the root
    else
    return search(root->right,val);

}