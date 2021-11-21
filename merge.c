struct Node* merge(struct Node*T1,struct Node*T2){  //function to merge two trees splitted initially
    struct Node* root;
    //if one among two Node's is NULL return the other Node
	if(T1==NULL){                  
        return T2;
    }
    if(T2==NULL){
        return T1;
    }
    //assign the Node with higher priority as the root node and merge it's left sub-tree and right sub-tree accordingly
		if (T1->pr < T2->pr) {
        root = New_Node(T1->key,T1->pr);
        root->left = T1->left;
        root->right=merge(T1->right,T2);
	} 
    else {
		root = New_Node(T2->key,T2->pr);
        root->left = merge(T1,T2->left);
        root->right=T2->right;
	}
    return root;
}