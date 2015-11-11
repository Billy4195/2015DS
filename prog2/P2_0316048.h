#include <iostream>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;


struct item{
    char *a;
    int i;
    int n;
    item(char *a_,int i_,int n_){
        a = new char[strlen(a_)+1];
        for(int i=0;i<strlen(a_);i++){
            a[i] = a_[i];
        }
        a[strlen(a_)] = '\0';
        i = i_;
        n = n_;
    }
    item(){}
    item operator=(const item& it){
        (*this).a = new char[strlen(it.a)+1];
        for(int i=0;i<strlen(it.a);i++){
            a[i] = it.a[i];
        }
        a[strlen(it.a)] = '\0';
        (*this).i =it.i;
        (*this).n =it.n;
		
		return *this;
    }
};

void non_recursive_perm(char *a, int i, int n){
    stack<item> stk;
    stk.push(item(a,i,n));
    item tmp;

    while(stk.size()){
        tmp = stk.top();
        stk.pop();
        if(tmp.i == tmp.n){//print
            cout << tmp.a << endl;
        }else{              //push
            for(int j=tmp.n;j>=tmp.i;j--){
                swap(tmp.a[j],tmp.a[tmp.i]);
                stk.push(item(tmp.a,(tmp.i)+1,tmp.n));
                swap(tmp.a[j],tmp.a[tmp.i]);
            }
        }

    }
}
