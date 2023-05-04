#include <iostream>
#include <queue>
using namespace std;

#include<climits>
#include<cmath>



template <typename T>
class BinaryTreeNode {
   public:
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(T data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    ~BinaryTreeNode() {
        if (left) delete left;
        if (right) delete right;
    }
};


class BSTreturn
{
    
    public:
    int min,max,height;
    bool isBST;
    
};
BSTreturn helper(BinaryTreeNode<int>* root)
{
    if(root==NULL)
    {
        
        BSTreturn ans;
        ans.min=INT_MAX;
        ans.max=INT_MIN;
        ans.height=0;
        ans.isBST=true;
        return ans;
    }
    
    
    BSTreturn Left = helper(root->left); 
    BSTreturn Right = helper(root->right);
    
    if(!(Left.isBST && Left.max < root->data))
        Left.isBST=false;
    
    if(!(Right.isBST && Right.min > root->data))
        Right.isBST=false;
    
    
    if(!Left.isBST || !Right.isBST ||  root->data >Right.min ||  root->data <Left.max)
    {
        if(Left.height>Right.height)
        {
            Left.isBST=false;
            return Left;
            
        }
        
        else
        {
            Right.isBST=false;
            return Right;
        }
        
    }
    BSTreturn ans;
    ans.isBST=true;
    ans.min=min(Left.min,min(root->data,Right.min));
    ans.max=max(Left.max,max(root->data,Right.max));
    ans.height=max(Left.height,Right.height)+1;
    return ans;
    
    
    
}

int largestBSTSubtree(BinaryTreeNode<int> *root) {
    // Write your code here
	 return helper(root).height;
}




BinaryTreeNode<int>* takeInput() {
    int rootData;
    
    cin >> rootData;
    if (rootData == -1) {
        return NULL;
    }
    BinaryTreeNode<int>* root = new BinaryTreeNode<int>(rootData);
    queue<BinaryTreeNode<int>*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode<int>* currentNode = q.front();
        q.pop();
        int leftChild, rightChild;
       
        cin >> leftChild;
        if (leftChild != -1) {
            BinaryTreeNode<int>* leftNode = new BinaryTreeNode<int>(leftChild);
            currentNode->left = leftNode;
            q.push(leftNode);
        }
        
        cin >> rightChild;
        if (rightChild != -1) {
            BinaryTreeNode<int>* rightNode =
                new BinaryTreeNode<int>(rightChild);
            currentNode->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

int main() {
    BinaryTreeNode<int>* root = takeInput();
    cout << largestBSTSubtree(root);
    delete root;
}