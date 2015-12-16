#include<iostream>
#include<utility>
#include<cstdlib>

using namespace std;

template<class K,class E>
class BST;

template<class K,class E>
class TreeNode{
friend class BST<K,E>;
public:
    TreeNode(pair<K,E>,TreeNode* =0,TreeNode* =0,TreeNode* =0);
    pair<K,E> data;
    TreeNode<K,E> *leftChild,*rightChild,*parent;
};

template<class K,class E>
TreeNode<K,E>::TreeNode(pair<K,E> d,TreeNode* l,TreeNode* r,TreeNode* pa){
    data = d;
    leftChild = l;
    rightChild = r;
    parent = pa;
}

template<class K,class E>       //no memory release
class BST{
public:
    BST(){
        header = new TreeNode<K,E>(pair<K,E>());    //header node
        header->rightChild = header;
    }
    BST(TreeNode<K,E> & tn);
    TreeNode<K,E>* rootNode(){
        return header->leftChild;
    }
    pair<K,E>* Get(const K& k);
    pair<K,E>* Get(TreeNode<K,E>*,const K&);
    void Insert(const pair<K,E> &thePair,int =0);
    TreeNode<K,E>* rInorderSuccessor(TreeNode<K,E>*);
    TreeNode<K,E>* PreorderSuccessor(TreeNode<K,E>*);
private:
    TreeNode<K,E>* header;
};

template<class K,class E>
BST<K,E>::BST(TreeNode<K,E> & tn){
    header->leftChild = &tn;
}

template<class K,class E>
pair<K,E>* BST<K,E>::Get(const K& k){
    return Get(rootNode(),k);
}

template<class K,class E>
pair<K,E>* BST<K,E>::Get(TreeNode<K,E>* p,const K& k){
    if(!p) return 0;
    if(k < p->data.first) return Get(p->leftChild,k);
    if(k > p->data.first) return Get(p->rightChild,k);
    return &p->data;
}

template<class K,class E>
void BST<K,E>::Insert(const pair<K,E> &thePair,int mode){
    TreeNode<K,E> *p = rootNode(),*pp =0;
    while(p){
        pp = p;
        if(thePair.first < p->data.first) p = p->leftChild;
        else if(thePair.first > p->data.first) p = p->rightChild;
        else{
            if(!mode)
                p->data.second = thePair.second;
            else
                p->data.second += thePair.second;
            return;
        }
    }
    p = new TreeNode<K,E>(thePair);
    //cout << p<<endl;
    if(rootNode()){
        if(thePair.first < pp->data.first){
            pp->leftChild = p;
        }
        else pp->rightChild = p;

        p->parent = pp;
    }else{
        header->leftChild = p;
        p->parent = header;
    }
}

template<class K,class E>//end case have problem
TreeNode<K,E>* BST<K,E>::rInorderSuccessor(TreeNode<K,E>* cur){     //reverse inorder successor start from rightmost to leftmost
    TreeNode<K,E> *temp=0;
    if(cur->leftChild){
        temp = cur->leftChild;
        while(temp->rightChild){
            temp = temp->rightChild;
        }
    }else{
        if(cur->parent){   //check have parent
            if(cur == cur->parent->rightChild){         //rightChild
                temp = cur->parent;
            }else{                                      //leftChild
                while(cur->parent && cur == cur->parent->leftChild){
                    cur = cur->parent;
                }
                if(cur->parent){
                    cur = cur->parent;
                }
                if(cur->rightChild != cur){         //check whether cur is header node
                    temp = cur;
                }else{
                    temp = 0;
                }
            }
        }else temp =0;
    }
    return temp;
}

template<class K,class E>
TreeNode<K,E>* BST<K,E>::PreorderSuccessor(TreeNode<K,E>* cur){
    if(cur->leftChild){
        return cur->leftChild;                  //have leftChild
    }else{
        if(cur->rightChild) return cur->rightChild;
        if(cur->parent && cur == cur->parent->rightChild){
            cur = cur->parent;
            while(cur == cur->parent->rightChild){      //last node need to trace back to root (right child tree trace back)
                cur = cur->parent;
            }
            cur = cur->parent;

        }
        while(!cur->rightChild && cur->parent){         //left child tree trace back
            cur = cur->parent;
        }
        if(cur->parent){
            return cur->rightChild;
        }else return 0;                         //header node
    }

}


class PolyBST : public BST<int,double>{
    friend ostream& operator<<(ostream& ,PolyBST&);
public:
    PolyBST& operator+(PolyBST &);
    PolyBST& operator-(PolyBST &);
    PolyBST& operator*(double);
    PolyBST& operator*(PolyBST &);
    void setTerm(const int&,const double&,int =0);

};


      //waste time ---deep tree
PolyBST& PolyBST::operator+(PolyBST & p2){
    TreeNode<int,double> *tn1 = this->rootNode(),*tn2 = p2.rootNode();
    PolyBST *p3 = new PolyBST;
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
            p3->setTerm(tn1->data.first,tn1->data.second+tn2->data.second);
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

PolyBST& PolyBST::operator-(PolyBST &p2){
    PolyBST *p3 = &(p2 * -1);
    return *this+*p3;
}


PolyBST& PolyBST::operator*(double x){
    TreeNode<int,double>* curT= this->rootNode();
    PolyBST *p1 = new PolyBST;
    while(curT){
        p1->setTerm(curT->data.first,curT->data.second*x);
        curT = this->PreorderSuccessor(curT);
    }

    return *p1;

}

PolyBST& PolyBST::operator*(PolyBST &p2){
    PolyBST *p3 = new PolyBST;
    TreeNode<int,double> *curT1,*curT2;
    curT1 = this->rootNode();
    while(curT1){
        curT2 = p2.rootNode();
        while(curT2){
            p3->setTerm(curT1->data.first + curT2->data.first,curT1->data.second * curT2->data.second , 1);
            curT2 = p2.PreorderSuccessor(curT2);
        }
        curT1 = this->PreorderSuccessor(curT1);
    }
    return *p3;
}



void PolyBST::setTerm(const int& exp,const double& coe,int mode){     //mode 1 --- add coefficient
    this->Insert( pair<int,double>(exp,coe),mode );
}


ostream& operator<<(ostream& os,PolyBST&p1){
    if(!p1.rootNode()){
        os<<"0"<<endl;
        return os;
    }else{
        TreeNode<int,double>* cur=p1.rootNode();
        while(cur->rightChild){     //get the max term
            cur = cur->rightChild;
        }
        /****print first term****/
        if(cur->data.second){                   //if coefficient is 0 don't print any thing
            if(cur->data.second < 0){
                os << "-"<<-cur->data.second;   //print coefficient and if negative print -
            }else{
                os << cur->data.second;
            }
            os << "*x^" <<cur->data.first;      //print exponent
        }
        /****end of first term****/
        while(cur = p1.rInorderSuccessor(cur)){ //print other terms
            if(cur->data.second){                   //if coefficient is 0 don't print any thing
                if(cur->data.second < 0){
                    os << " - "<<-cur->data.second; //print coefficient and if negative print -
                }else{
                    os << " + "<<cur->data.second;  //print coefficient and if positive print +
                }
                if(cur->data.first >0)              //if exponent is 0 ,don't need to print exponent
                os << "*x^" <<cur->data.first;      //print exponent
            }
        }
        return os;
    }
}


int main(){
//    pair<int,double> pr(1,1.4),pr1(2,1.1),pr2(3,2);
//    pair<int,double> pr(8,0),pr1(7,0),pr2(20,0),pr3(15,0),pr4(28,0),pr5(30,0),pr6(25,0),pr7(24,0),pr8(26,0);
//    pair<int,double> pr(50,0),pr1(51,0),pr2(48,0),pr3(49,0),pr4(46,0),pr5(47,0),pr6(44,0),pr7(45,0),pr8(43,0);
    PolyBST<int,double> poly,poly1;
//    poly.Insert(pr);
//    poly.Insert(pr1);
//    poly.Insert(pr2);
//    poly.Insert(pr3);
//    poly.Insert(pr4);
//    poly.Insert(pr5);
//    poly.Insert(pr6);
//    poly.Insert(pr7);
//    poly.Insert(pr8);

//    poly.Insert(pr1);
//    poly.Insert(pr);
//    poly.Insert(pr2);
    poly.setTerm(1,1.4);
    poly.setTerm(2,1.1);
    poly.setTerm(3,2);
    poly1.Insert(pair<int,double>(2,2));
    poly1.Insert(pair<int,double>(0,1.3));
    poly1.Insert(pair<int,double>(5,6.2));
    cout << "poly1  " << poly1<<endl;
    cout << "poly   " << poly<<endl;
    cout << "poly*2 " << poly * 2.0<<endl;

    cout << "poly1 + poly " <<poly1 + poly<<endl;
    cout << endl <<endl;
    cout << "poly1  " << poly1<<endl;
    cout << "poly   " << poly<<endl;
    cout << "poly1 * poly " << poly1 * poly<<endl;
    return 0;
}
