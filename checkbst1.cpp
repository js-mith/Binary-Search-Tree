#include<iostream>
#include<climits>
#include "binarysearchtree.h"
#include<queue>
using namespace std;

BinaryTreeNode<int> *takeinputlevelwise(){
     int rootdata;

    cout << "enter the data" << endl;
    cin>>rootdata;

    if(rootdata == -1){
        return NULL;
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootdata);
    queue<BinaryTreeNode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(pendingnodes.size() != 0){
        BinaryTreeNode<int> *front = pendingnodes.front();
        pendingnodes.pop();
        cout << "enter the left child of " << front-> data << endl;
        int leftchilddata;
        cin>>leftchilddata;
        if(leftchilddata != -1){
            BinaryTreeNode<int> *child = new BinaryTreeNode<int>(leftchilddata);
            front->left = child;
            pendingnodes.push(child);
        }
         cout << "enter the right child of " << front-> data << endl;
        int rightchilddata;
        cin>>rightchilddata;
        if(rightchilddata != -1){
            BinaryTreeNode<int> *child = new BinaryTreeNode<int>(rightchilddata);
            front->right = child;
            pendingnodes.push(child);
        }
    }
    return root;
}

void printTree(BinaryTreeNode<int> *root){
    if(root == NULL){
        return;
    }
    cout << root -> data << " : ";
    if(root -> left != NULL){
        cout << " L " << root -> left ->data;
    }
    if(root ->right != NULL){
        cout << " R " << root -> right -> data;
    }

    cout << endl;
    printTree(root -> left);
    printTree(root -> right);
}

void printBetweenK1K2(BinaryTreeNode<int>*root , int k1,int k2){
    if(root == NULL){
        return ;
    }
   if(root -> data >= k1 && root -> data <= k2){
    cout << root -> data << endl;
   }
   if(root -> data > k1){
    printBetweenK1K2(root -> left ,k1,k2);
   }
   if(root -> data<=k2){
    printBetweenK1K2(root->right , k1,k2 );
   }
}
int maximum(BinaryTreeNode<int> * root){
    if(root == NULL){
        return INT_MIN;
    }
    return max(root -> data, max(maximum(root -> left), maximum(root -> right)));

}
int minimum(BinaryTreeNode<int> *root){
    if(root == NULL){
        return INT_MAX;
    }
   return min(root -> data , min(minimum(root -> left) , minimum(root -> right)));
}
bool isBST(BinaryTreeNode<int> *root){
    if(root == NULL){
        return true;
    }
    int leftmax = maximum(root-> left);
    int rightmin = minimum(root -> right);
    bool output = (root -> data >  leftmax) && (root -> data <= rightmin) && isBST(root -> left) &&isBST(root -> right);
    return output;
   
}
class IsBSTReturn{
    public:
    bool isBST;
    int minimum;
    int maximum;
};
IsBSTReturn isbst2(BinaryTreeNode<int> * root){
    if(root == NULL){
        IsBSTReturn output;
    
    output.isBST = true;
    output.minimum = INT_MAX;
    output.maximum = INT_MIN;
    return output;
    }
    IsBSTReturn leftoutput = isbst2(root -> left);
    IsBSTReturn rightoutput = isbst2(root -> right);
    int minimum = min(root -> data , min(leftoutput.minimum , rightoutput.minimum));
    int maximum = max(root -> data, max(leftoutput.maximum, rightoutput.maximum));
    bool isBSTFinal = (root -> data > leftoutput.maximum) && (root -> data <= rightoutput.minimum) && leftoutput.isBST && rightoutput.isBST;
    IsBSTReturn output;
    output.isBST = isBSTFinal;
    output.minimum = minimum;
    output.maximum = maximum;
    return output;
}
bool isBST3(BinaryTreeNode<int>*root , int min = INT_MIN , int max = INT_MAX){
    if(root ==NULL){
        return true;
    }
    if(root -> data< min || root -> data > max){
        return false;
    }
    bool isleftok = isBST3(root -> left , min , root -> data -1);
    bool isrightok = isBST3(root -> right , root -> data , max);
    return isleftok && isrightok;
}

// 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
// 4 2 6 1 3 5 7 -1 -1 -1 -1 -1 -1 -1 -1 
// 4 2 6 1 30 5 7 -1 -1 -1 -1 -1 -1 -1 -1 
int main(){
    BinaryTreeNode<int> * root = takeinputlevelwise();
    printTree(root);
   // printBetweenK1K2(root,2,6);
    cout << "check BST  1 : " << isBST(root) << endl;
    cout << isBST3(root) << endl;
       
    isbst2(root);
    
 

    return 0;
    delete root;
    


}