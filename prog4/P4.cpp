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
    PolyBST<K,E>& operator+(PolyBST<K,E> &);
    PolyBST<K,E>& operator*(double);

};

template<class K,class E>       //waste time ---deep tree
PolyBST<K,E>& PolyBST<K,E>::operator+(PolyBST<K,E> &p2){//not finished
    TreeNode<K,E> *tn1 = this->root,*tn2 = p2.root;
    PolyBST<K,E> *p3 = new PolyBST<K,E>;
    while(tn1 && tn1->rightChild){             //get the max term
        tn1 = tn1->rightChild;
    }
    while(tn2 && tn2->rightChild){             //get the max term
        tn2 = tn2->rightChild;
    }
    while(tn1 && tn2){
        if(tn1->data.first > tn2->data.first){      //if p1's term greater than p2's
            p3->Insert(tn1->data);                  //put p1's term into p3
            tn1 = this->rInorderSuccessor(tn1);     //next p1 term
        }else if(tn1->data.first < tn2->data.first){//if p2's term greater than p1's
            p3->Insert(tn2->data);                  //put p2's term into p3
            tn2 = p2.rInorderSuccessor(tn2);        //next p2 term
        }else{                                      //add p1's term and p2's term then put into p3
            p3->Insert(pair<K,E>(tn1->data.first,tn1->data.second+tn2->data.second));
            tn1 = this->rInorderSuccessor(tn1);     //next p1 and p2 term
            tn2 = p2.rInorderSuccessor(tn2);
        }

    }
    while(tn1){      //if p1 have more term
        p3->Insert(tn1->data);                  //put p1's term into p3
        tn1 = this->rInorderSuccessor(tn1);     //next p1 term
    }
    while(tn2){      //if p2 have more term
        p3->Insert(tn2->data);                  //put p2's term into p3
        tn2 = p2.rInorderSuccessor(tn2);        //next p2 term
    }

    return *p3;
}

template<class K,class E>           //it will change this's value
PolyBST<K,E>& PolyBST<K,E>::operator*(double x){
    TreeNode<K,E>* curT= this->root;
    while(curT->rightChild){            //get the max term
        curT = curT->rightChild;
    }
    while(curT){
        curT->data.second *= x;         //coefficient multiply a const number
        curT = this->rInorderSuccessor(curT);   //next term
    }
    return *this;

}

template<class Ko,class Eo>
ostream& operator<<(ostream& os,PolyBST<Ko,Eo>&p1){
    if(!p1.root){
        os<<"0"<<endl;
        return os;
    }else{
        TreeNode<Ko,Eo>* cur=p1.root;
        while(cur->rightChild){     //get the max term
            cur = cur->rightChild;
        }
        /****print max term****/
        if(cur->data.second < 0){
            os << "-"<<-cur->data.second;   //print coefficient and if negative print -
        }else{
            os << cur->data.second;
        }
        os << "*x^" <<cur->data.first;      //print exponent
        /****end of max term****/
        while(cur = p1.rInorderSuccessor(cur)){ //print other terms
            if(cur->data.second < 0){
                os << " - "<<-cur->data.second; //print coefficient and if negative print -
            }else{
                os << " + "<<cur->data.second;  //print coefficient and if positive print +
            }
            if(cur->data.first >0)              //if exponent is 0 ,don't need to print exponent
            os << "*x^" <<cur->data.first;      //print exponent
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
    poly1.Insert(pair<int,double>(2,2));
    poly1.Insert(pair<int,double>(0,1.3));
    poly1.Insert(pair<int,double>(5,6.2));
    //cout << poly.Get(2)->second <<endl;
    cout << "poly1  " << poly1<<endl;
    cout << "poly   " << poly<<endl;
    cout << "poly*2 " << poly * 2.0<<endl;
    poly = poly1 + poly;
    cout << " poly1 + poly " <<poly <<endl;
    return 0;
}
