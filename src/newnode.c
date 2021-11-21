struct Node* New_Node(int k,int p){                              //New Node containing key and priority
    struct Node*New = (struct Node*)malloc(sizeof(struct Node)); 
    New->key = k;                                                
    New->left = NULL;                                            
    New->right = NULL;
    New->pr = p;
    return New;
}