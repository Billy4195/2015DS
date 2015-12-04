#include<sstream>
#include<iostream>
#include<cstdlib>

//environment  codeblocks 13.12

using namespace std;

class TreeNode{
    friend class BT;
public:
    TreeNode(int,TreeNode* = 0,TreeNode* = 0 ,TreeNode* = 0);
    TreeNode(TreeNode* = 0,TreeNode* = 0,TreeNode* =0);
    inline void setparent(TreeNode* p){
        parent = p;
    }
    inline void setchild(TreeNode* l,TreeNode* r){
        leftchild = l;
        rightchild = r;
    }
private:
    int data;
    TreeNode *parent,*leftchild,*rightchild;
};

TreeNode::TreeNode(int d,TreeNode *p,TreeNode *l,TreeNode *r){
    data = d;
    parent = p;
    leftchild = l;
    rightchild = r;
}
TreeNode::TreeNode(TreeNode *p,TreeNode *l,TreeNode *r){
    parent = p;
    leftchild = l;
    rightchild = r;
}

class BT{
public:
    BT(const char *a);
    void inorder();
    TreeNode* InorderSuccessor(TreeNode *);
private:
    TreeNode *root;
};

BT::BT(const char *a){
    int num;
    int temp_int;
    int nodenum;
    TreeNode **allnode;     //store all the node temporary
    stringstream ss;        //store input text
    ss << a;
    ss >> num;          // input the tree level
    nodenum = (1 << num) - 1;//count the node number

    allnode = new TreeNode*[nodenum];
    //for(int i=0;i< nodenum;i++){
    int i= 0;
    while(ss >> temp_int){
        if(temp_int != -1){
            allnode[i] = new TreeNode(temp_int);
        }else{
            allnode[i] = 0;
        }
        i++;
    }
    nodenum = i;
    //}
    allnode[0]->setchild(allnode[1],allnode[2]);
    for(int i=1;i< nodenum ;i++){
        if(allnode[i]){
            allnode[i]->setparent(allnode[(i-1)/2]);            // set parentnode
            if(i*2+1 <nodenum && i*2+2 < nodenum){              //check not exceed
                allnode[i]->setchild(allnode[i*2+1],allnode[i*2+2]);    //set childnode
            }
        }
    }
    root = allnode[0];                 //set root
/*********************test for input ******************************/
//for(int i = 0;i < nodenum;i++){
//    cout << allnode[i] <<" ";
//    if(allnode[i]){
//        cout << allnode[i]->data << " " << allnode[i]->parent << " " << allnode[i]->leftchild << " " << allnode[i]->rightchild;
//    }
//    cout <<endl;
//}
/**********************end of test input***************************/
    delete [] allnode;                 //release allnode
}

void BT::inorder(){
    TreeNode * cur = root;
    while(cur->leftchild){
        cur = cur->leftchild;
    }
    while(cur){
        cout << cur->data << " ";
        cur = InorderSuccessor(cur);
    }
    cout << endl;
}
TreeNode* BT::InorderSuccessor(TreeNode * cur){
    TreeNode *temp;
    if(cur->rightchild){
        temp = cur->rightchild;
        while(temp->leftchild){
            temp = temp->leftchild;
        }
    }else{
        if(cur == cur->parent->leftchild){  //leftchild
            temp = cur->parent;
        }else{
            if(cur->parent != root && cur->parent == cur->parent->parent->leftchild){
                temp = cur->parent->parent;     //rightchild
            }else{
                temp = 0;                       //last node
            }
        }
    }
    return temp;
}
