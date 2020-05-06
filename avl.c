#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
void PrintInorder(AVLNodePtr node) 
{ 
     if (node == NULL) {
          return; }
  
     /* first recur on left child */
     PrintInorder(node->child[0]); 
  
     /* then print the data of node */
     printf("in order : %d  ", node->key);
     if(node->child[0])printf("child 0 : %d  ",node->child[0]->key);
     else printf("child 0 NULL ");
     if(node->child[1])printf("child 1 : %d  ",node->child[1]->key);
     else printf("child 1 NULL ");
      printf("\n ");
  
     /* now recur on right child */
     PrintInorder(node->child[1]); 
} 
/****
  Student1 name: ----- -----
  Student2 name: ----- -----
  
  Student1 ID: ----- -----
  Student2 ID: ----- -----
****/


// Do not change this. You can use but do not touch.
int _max( int x, int y ){
    return (x < y) ? y : x;
}

// Do not change this. You can use but do not touch.
int _abs( int x ){
    return (x < 0) ? -x : x;
}

int height(AVLNodePtr root) 
{ 
    if (root == NULL) 
        return -1; 
    return root->height; 
} 
// Update heights 
void Update_Heights (AVLNodePtr root){
    root->height=_max(height(root->child[0]),height(root->child[1]))+1;
}
// Operations implementation
AVLNodePtr avl_search( AVLNodePtr root, int x ){
   if (root == NULL) 
        return NULL;
  
    if (root->key == x) 
        return root; 
  
    /* then recur on left sutree */
    if(avl_search(root->child[0], x)!=NULL)
        return avl_search(root->child[0], x); 
  
    /* node is not found in left, so recur on right subtree */
    else return avl_search(root->child[1], x);  
}
//help func for insert
//-------------------------------------------------------
AVLNodePtr Left_Rotate (AVLNodePtr root){
    AVLNodePtr B_node , A_node ; // like we did in class .
    A_node=root ; B_node=A_node->child[1];

    // Perform rotation 
    A_node->child[1]=B_node->child[0];
    B_node->child[0]=A_node;

    // Update heights 
    Update_Heights(A_node); Update_Heights(B_node);
    root=B_node;
    //printf("left rotete with-%d ",root->key);PrintInorder(root);printf(" end left rotete\n ");
    return root ; 
}
AVLNodePtr Right_Rotate (AVLNodePtr root){
    AVLNodePtr B_node , A_node ; // like we did in class .
    B_node=root ; A_node=B_node->child[0];

    // Perform rotation 
    B_node->child[0]=A_node->child[1];
    A_node->child[1]=B_node;

    // Update heights 
    Update_Heights(B_node); Update_Heights(A_node);
    root=A_node;
    return root ; 
}
AVLNodePtr Balance( AVLNodePtr root){
    //printf("in b:%s\n",root->key);
    AVLNodePtr temp=NULL ; 
    //printf("root : %d height(root->child[0]) : %d height(root->child[1]) %d .\n",root->key, height(root->child[0]),height(root->child[1]));
    if(_abs(height(root->child[0])-height(root->child[1]))<=1)
        return root ; 
    else { if (height(root->child[0])>height(root->child[1])){
            temp=root->child[0];
             if(height(temp->child[0])<height(temp->child[1])){
                root->child[0] =Left_Rotate(temp);}
                return Right_Rotate(root);
        }
            else {
             temp=root->child[1];
             if(height(temp->child[0])>height(temp->child[1])){
                root->child[1] =Right_Rotate(temp);}
                return Left_Rotate(root); 
                
                
         }   
 }
}

//---------------------------------------------------------------------------
AVLNodePtr avl_insert( AVLNodePtr root, int x ){
    AVLNodePtr temp;
    if(root==NULL)
        return new_avl_node(x);
    if(x<=root->key){
        temp=avl_insert(root->child[0],x);
        root->child[0]=temp;
        root->height=temp->height+1;
    }
    else{
        temp=avl_insert(root->child[1],x);
        root->child[1]=temp;
        root->height=temp->height+1;
    }
    return Balance(root); 
}
//help func to delete 
//----------------------------------------------
AVLNodePtr minValueNode( AVLNodePtr root ){
    
    if(root->child[0]==NULL)
        return root; 
    else
        return minValueNode (root->child[0]);
}

//------------------------------------------------
AVLNodePtr avl_delete( AVLNodePtr root, int x ){
    AVLNodePtr temp =NULL;
   if (root == NULL) 
        return root; 
    else {if ( x < root->key ) 
        root->child[0] = avl_delete(root->child[0], x);
    else {if( x > root->key ) 
        root->child[1] = avl_delete(root->child[1], x);
    else{
     if((root->child[0] == NULL) || (root->child[1] == NULL) ) 
        { 
            temp = root->child[0] ? root->child[0] : root->child[1]; 
             // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else {// One child case 
             *root = *temp; // Copy the contents of  // the non-empty child
            free(temp); }
        }  
    
        else
        {   
            // node with two children: Get the inorder successor (smallest in the right subtree) 
             temp = minValueNode(root->child[1]); 
            // switch between the inorder successor's data to this node 
// Copy the inorder successor's data to this node 
            root->key = temp->key; 
  
            // Delete the inorder successor 
            root->child[1] = avl_delete(root->child[1], temp->key); 
        }
    }
    }
    }
    // If the tree had only one node then return 
    if (root == NULL) {
      return root; }
  
    // UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + _max(height(root->child[0]), height(root->child[1])); 
    return Balance(root);
   
}


AVLNodePtr avl_join( AVLNodePtr root1, AVLNodePtr xnode, AVLNodePtr root2 ){
   if(_abs(height(root1)-height(root2))<=1){
       xnode->child[0]=root1;
       xnode->child[1]=root2;
       Update_Heights(xnode);
       return xnode ; 
   }
   if(height(root1)<height(root2)){
        root2->child[0]=avl_join(root1,xnode,root2->child[0]);//printf("before b:%s\n",root->key);
        Update_Heights(root2);
        return Balance(root2);
   }
    else {
        root1->child[1]=avl_join(root1->child[1],xnode,root2);
        Update_Heights(root1);
        return Balance(root1);
    }

}

AVLNodePtr avl_split( AVLNodePtr root, int x, AVLNodePtr trees_out[2] ){
    AVLNodePtr temp =NULL;
   if(x>root->key){
        temp=avl_split(root->child[1],x,trees_out);
        trees_out[0]=avl_join(root->child[0],root,trees_out[0]);
        return temp;}
    else{
        if(x<root->key){
            temp=avl_split(root->child[0],x,trees_out);
            trees_out[1]=avl_join(trees_out[1],root,root->child[1]);
            return temp;
        }

        else { 
                trees_out[0]=root->child[0];
                trees_out[1]=root->child[1];
                return root;
        }
    }
}

AVLNodePtr new_avl_node( int x ){

    AVLNodePtr v = malloc(sizeof(AVLNode));
    if(!v) return NULL ;
    v->key=x;
    v->height=0;
    v->child[0]=NULL ;
    v->child[1]=NULL ;
    return v ; 
}

void delete_avl_tree( AVLNodePtr root ){
      if (root == NULL) return; 
    /* first delete both subtrees */
    delete_avl_tree(root->child[0]); 
    delete_avl_tree(root->child[1]); 
    /* then delete the node */
    free(root); 
}
