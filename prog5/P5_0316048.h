#include <iostream>
#include <list>
#include <stack>

//environment code blocks-13.12

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
}

//DFS return a stack store a component start from a vertex
stack<int> MyGraph::DFS(int st){
    bool visited[N];            //set visited check the node has visited or not
    int cnt=1;
    stack<int> stk,stk2;

    for(int i=0;i<N;i++) visited[i] = false;//initial visited

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
    int visited[N];     //use visited record the node has been to then find another component
    int index=0;
    int cnt=1;              //count the amount of components
    stack<int> stk;
    for(int i= 0;i<N;i++) visited[i] = false;//initial visited
    while(index < N){
        if(visited[index]) index++;
        else{
            stk = DFS(index);           //get the component store in stack
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
