#include <iostream>
#include <string>
#include <stack>

using namespace std;


int main(){
    char bit;
    stack<char> stk;

    cin.get(bit);
    //cout << bit <<"Q"<<endl;
    while(!cin.eof()){
        while(bit != '\n'){
            if( (bit >= 'A' && bit <= 'z') || (bit>='0' && bit <='9') ){
                cout <<bit;
                if(!stk.empty() && (stk.top() == '*' || stk.top() == '/') ){
                    cout << stk.top();
                    stk.pop();
                }
            }else if(bit == '*' || bit == '/'){
                if(!stk.empty() && (stk.top() == '*' || stk.top() == '/') ){
                    cout << stk.top();
                    stk.pop();
                }
                stk.push(bit);
            }else if(bit == '+' || bit == '-'){
                if(!stk.empty() && (stk.top() == '+' || stk.top() == '-') ){
                    cout << stk.top();
                    stk.pop();
                }
                stk.push(bit);
            }else if(bit == '('){
                stk.push(bit);
            }else if(bit == ')'){
                while(stk.top() != '('){
                    cout << stk.top();
                    stk.pop();
                }
                stk.pop();
            }
            cin.get(bit);
    //        cout << bit <<"OWO" <<endl;
        }
        while(stk.size()){
            cout << stk.top();
            stk.pop();
        }
        cout << endl;
    cin.get(bit);
    }
    return 0;
}
