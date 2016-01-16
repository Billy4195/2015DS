#include <iostream>

using namespace std;

void permutation(int);

int main(){
    int n;
    while(1){
        cout << "Input n: ";
        cin >> n;
        permutation(n);
    }
    return 0;
}


void permutation(int n){
    bool *arr = new bool[n];
    bool check,cur,car;
    for(int i=0;i<n;i++){
        arr[i] = 0;
    }
    for(int i=0;i<n;i++){
        cout <<"F";
    }
    cout<<endl;
    cur=1;
    check=0;
    car = 1;
    int i;
    while(!check){

        i = 0;
        do{
            car = arr[i] & cur;
            //cout << "car :"<<car<<endl;
            arr[i] = cur ^ arr[i];
            cur = car;i++;
            if(i== n-1 && (arr[i] & car)){
                check = 1;
                break;
            }
        }while(car);
        if(!check){
            for(int j=0;j<n;j++){
//                cout << arr[j];
                if(arr[j]){
                    cout <<"T";
                }else{
                    cout <<"F";
                }
            }
            cout << endl;
        }
        cur = 1;
    }
}
