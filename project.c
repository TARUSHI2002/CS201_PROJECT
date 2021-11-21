#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct Node{                            //struct Node which
    int key;                            //stores the key value of the node
    int pr;                             //stores the priority of each node
    struct Node* left;                  //pointer to the left child
    struct Node* right;                 //pointer to the right child
};

struct Node* l_root=NULL;                    //Root of the left tree obtained after splitting
struct Node* r_root=NULL;                    //Root of the right tree obtained after splitting
struct Node* root2=NULL;

struct Node* New_Node(int k,int p){                              //New Node containing key and priority
    struct Node*New = (struct Node*)malloc(sizeof(struct Node)); 
    New->key = k;                                                
    New->left = NULL;                                            
    New->right = NULL;
    New->pr = p;
    return New;
}

struct Node* leftRotate(struct Node* x)  //Function to left rotate the sub-tree rooted at x 
{
    struct Node* y = x->right;           //y=right child of x node
    struct Node* z = y->left;            //z=left child of y node

    //Left Rotation
    y->left = x;                         
    x->right = z;

    return y;                           //returning the new parent node of the sub-tree
}

struct Node* rightRotate(struct Node* y)  //Function to right rotate the sub-tree rooted at y 
{
    struct Node* x = y->left;              //x=left child of y node
    struct Node* z = x->right;             //z=right child of x node

    //Right Rotation
    x->right = y;
    y->left = z;

    return x;                             //returning the new parent node of the subtree
}

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

int main(){
    srand(time(0));
    printf("Enter the number of elements you want in the treap.\n");
    int h;
    scanf("%d",&h);
    printf("Now please enter %d elements(keys) one by one-\n",h);
    struct Node*Root = NULL;
    for(int i=0;i<h;++i){
        int j;
        scanf("%d",&j);
        Root = Insert(Root,j,1);
    }
    while(1){
        printf("Choose:\n1.Insert\n2.Search\n3.Delete\n4.Split\n5.Traversal(Inorder)\n6.Exit\n");
        int i;
        scanf("%d",&i);
        if(i==1){
            int o;
            printf("Enter the number you want to insert\n");
            scanf("%d",&o);
            Root=Insert(Root,o,1);
        }
        else if(i==2){
            int o;
            printf("Enter the number you want to search\n");
            scanf("%d",&o);
            if(search(Root,o)){
                printf("Element found\n");
            }
            else{
                printf("Element not found\n");
            }
        }
        else if(i==3){
            int o;
            printf("Enter the element you want to delete\n");
            scanf("%d",&o);
	    if(search(Root,o)!=NULL) printf("Element successfully deleted, to check traverse the updated treap... \n");
            Root=delete_Node(Root,o);
        }
        else if(i==4){
            int p;
            printf("Enter the element about which you want to split the treap\n");
            scanf("%d",&p);
            if(search(Root,p)==NULL) {printf("Element not present in Treap,split can't happen. exiting...\n");}
	    else{
		   treapSplit(Root,p);
                   printf("The two treaps are-\nTreap 1\n");
                   inorder(l_root);
                   printf("\nTreap 2\n");
                   inorder(r_root);
                   printf("Choose what to do:\n1.use Treap 1 further\n2.Use Treap 2 further\n3.Merge\n");
                   int m;
                    scanf("%d",&m);
                   if(m==1){
                   Root=l_root;
                   root2=r_root;
	           else if(m==2){
                     Root=r_root;
                     root2=l_root;
                  }
                  else{
                  Root=merge(l_root,r_root);
                  }
            }
            
        }
        else if(i==5){
            printf("The inorder traversal is:\n");
            inorder(Root);
        }
        else{
            return 0;
        }
    }
  }
}
