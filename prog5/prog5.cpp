#include <iostream>
#include <list>
#include <stack>

using namespace std;

class MyGraph{
public:
    MyGraph(int ,int*);
    stack<int> DFS(int);
    void cc();
private:
    int N;
    list<int>* adjlist;
};

MyGraph::MyGraph(int n,int* mx){
    N = n;
    adjlist = new list<int>[N];
    for(int i= 0;i<N*N;i++){
        if(mx[i]){
            adjlist[i/N].push_back(i%N);
        }
    }
    for(int i=0;i<N;i++){
        for(list<int>::iterator it = adjlist[i].begin(); it != adjlist[i].end();it++){
            cout << *it <<" ";
        }
        cout <<endl;
    }

    cout << endl;
}


stack<int> MyGraph::DFS(int st){
    bool visited[N];
    int cnt=1;
    stack<int> stk,stk2;

    for(int i=0;i<N;i++) visited[i] = false;

    stk.push(st);
    stk2.push(st);
    while(!stk.empty()){
        int node = stk.top();
        int index = 0;
        int nextnode;
        bool path_check = false;
        visited[node] = true;


        list<int>::iterator it = adjlist[node].begin();
        while(it != adjlist[node].end()){
            nextnode = *it;
            if(visited[nextnode]){
                it++;
                path_check = false;
            }
            else{
                stk.push(nextnode);
                stk2.push(nextnode);
                path_check = true;
                break;
            }
        }
        if(!path_check){
            stk.pop();
        }
    }
    return stk2;
}

void MyGraph::cc(){
    int visited[N];
    int index=0;
    int cnt=1;
    stack<int> stk;
    for(int i= 0;i<N;i++) visited[i] = false;
    while(index < N){
        if(visited[index]) index++;
        else{
            stk = DFS(index);
            if(stk.size()){
                cout <<"Component#"<<cnt++<<":";
            }
            while(!stk.empty()){
                cout<<" "<<stk.top();
                visited[stk.top()] = true;
                stk.pop();
            }
            cout <<endl;
            index++;
        }
    }

}

int main(){
    int x[] = {0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0};
    int y[] = {0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,0};
    int z[] =  {0,1,0,0,0,0,0,
                1,0,1,0,0,0,0,
                0,1,0,1,0,0,0,
                0,0,1,0,0,0,0,
                0,0,0,0,0,1,1,
                0,0,0,0,1,0,0,
                0,0,0,0,1,0,0};
    MyGraph G(4, x);
    MyGraph g(4, y);
    MyGraph gr(7,z);
    G.cc();
    cout << endl;
    g.cc();
    cout << endl;
    gr.cc();

}
