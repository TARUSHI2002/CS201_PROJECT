struct Node* Insert(struct Node* Head,int k,int p)    //function to insert a new node
{
    if(Head==NULL)                                    //if Head node is NULL create a new node and return it
    {
    struct Node*New = (struct Node*)malloc(sizeof(struct Node));
    New->key = k;
    New->left = NULL;
    New->right = NULL;
    if(p==0){
    New->pr = 1e9;
    }
    else{
    New->pr = rand();
    }
    return New;
    }
    else if(Head->key<k)                          //if key is greater than the Head node's Key
    {
        Head->right=Insert(Head->right,k,p);      //Insert key in right sub-tree
        if(Head->right->pr>Head->pr){             //Fix Heap property if violated
         Head=leftRotate(Head);   
        }
    }
    else{                                         //if key is less than the Head node's key
        Head->left=Insert(Head->left,k,p);        //Insert key in left sub-tree
        if(Head->left->pr>Head->pr){              //Fix Heap property if violated
        Head=rightRotate(Head);
        }
    }
    return Head;                                 //returning the Head node
}