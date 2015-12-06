#include<iostream>
#include<utility>

using namespace std;

template<class K,class E>
class BST;

template<class K,class E>
class TreeNode{
friend class BST<K,E>;
public:
    TreeNode(pair<K,E>,TreeNode* =0,TreeNode* =0,TreeNode* =0);
//private:
    pair<K,E> data;
    TreeNode *leftChild,*rightChild,*parent;
};

template<class K,class E>
TreeNode<K,E>::TreeNode(pair<K,E> d,TreeNode* l,TreeNode* r,TreeNode* pa){
    data = d;
    leftChild = l;
    rightChild = r;
    parent = pa;
}

template<class K,class E>
class BST{
public:
    BST(){root = 0;}
    BST(TreeNode<K,E> & tn);
    pair<K,E>* Get(const K& k);
    pair<K,E>* Get(TreeNode<K,E>*,const K&);
    void Insert(const pair<K,E> &thePair);
    TreeNode<K,E>* rInorderSuccessor(TreeNode<K,E>*);
//private:
    TreeNode<K,E>* root;
};

template<class K,class E>
BST<K,E>::BST(TreeNode<K,E> & tn){
    root = &tn;
}

template<class K,class E>
pair<K,E>* BST<K,E>::Get(const K& k){
    return Get(root,k);
}

template<class K,class E>
pair<K,E>* BST<K,E>::Get(TreeNode<K,E>* p,const K& k){
    if(!p) return 0;
    if(k < p->data.first) return Get(p->leftChild,k);
    if(k > p->data.first) return Get(p->rightChild,k);
    return &p->data;
}

template<class K,class E>
void BST<K,E>::Insert(const pair<K,E> &thePair){
    TreeNode<K,E> *p = root,*pp =0;
    while(p){
        pp = p;
        if(thePair.first < p->data.first) p = p->leftChild;
        else if(thePair.first > p->data.first) p = p->rightChild;
        else{
            p->data.second = thePair.second;
            return;
        }
    }
    p = new TreeNode<K,E>(thePair);
    //cout << p<<endl;
    if(root){
        if(thePair.first < pp->data.first){
            pp->leftChild = p;
        }
        else pp->rightChild = p;

        p->parent = pp;
    }else{
        root = p;
    }
}

template<class K,class E>
TreeNode<K,E>* BST<K,E>::rInorderSuccessor(TreeNode<K,E>* cur){
    TreeNode<K,E> *temp;
    if(cur->leftChild){
        temp = cur->leftChild;
        while(temp->rightChild){
            temp = temp->rightChild;
        }
    }else{
        if(cur->parent && cur == cur->parent->rightChild){  //leftchild
            temp = cur->parent;
        }else{
            if(cur->parent && cur->parent->parent && cur->parent != root && cur->parent == cur->parent->parent->rightChild){
                temp = cur->parent->parent;     //rightchild
            }else{
                temp = 0;                       //last node
            }
        }
    }
    return temp;
}

template<class K,class E>
class PolyBST : public BST<K,E>{
    template<class Ko,class Eo>
    friend ostream& operator<<(ostream& ,PolyBST<Ko,Eo>&);
public:
//    PolyBST<K,E> operator+(PolyBST<K,E> &p1);

};

//template<class K,class E>
//PolyBST<K,E> PolyBST<K,E>::operator+(PolyBST<K,E> &p1){
//
//}

template<class Ko,class Eo>
ostream& operator<<(ostream& os,PolyBST<Ko,Eo>&p1){   // not finished
    if(!p1.root){
        os<<"0"<<endl;
        return os;
    }else{
        TreeNode<Ko,Eo>* cur=p1.root;
        //os << "OWO" <<cur->rightChild;
        while(cur->rightChild){
            cur = cur->rightChild;
        }
        //os << cur;
        if(cur->data.second < 0){
            os << "-"<<-cur->data.second;
        }else{
            os << cur->data.second;
        }
        os << "*x^" <<cur->data.first;

        while(cur = p1.rInorderSuccessor(cur)){
            if(cur->data.second < 0){
                os << " - "<<-cur->data.second;
            }else{
                os << " + "<<cur->data.second;
            }
            os << "*x^" <<cur->data.first;
        }
        return os;
    }
}

int main(){
    pair<int,double> pr(1,1.4),pr1(2,1.1),pr2(3,2);
    TreeNode<int,double> tn(pr);
    PolyBST<int,double> poly,poly1;
    poly.Insert(pr1);
    poly.Insert(pr);
    poly.Insert(pr2);
    cout << poly.Get(2)->second <<endl;
    cout << poly;
    return 0;
}
