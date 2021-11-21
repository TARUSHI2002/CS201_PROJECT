void inorder(struct Node*Head){    //inorder traversal
    if(Head!=NULL){                
    inorder(Head->left);                                //traversing the left subtree first
    printf("Key : %d, Priority : %d",Head->key,Head->pr);    //printing Node's key,priority
    if(Head->left){                                   
        printf(", Left child : %d",Head->left->key);       //left child's key element
    }
    else{
        printf(", Left child : NULL");
    }
    if(Head->right){
        printf(", Right child : %d",Head->right->key);    //right child's key element
    }
    else{
        printf(", Right child : NULL");
    }
    printf("\n");
    inorder(Head->right);                              //traversing the right sub-tree
    }
}
