#include <iostream>
/*Exception practice 2*/
using namespace std;

int sum(int *,int);

int main(){
	int arr[]={1,4,2};
	try{
        cout << sum(arr,-1);
    }catch(const char* str){        //need const char
        cout << str <<endl;
	}

}

int sum(int *arr,int n){
	if(n < 0){
		throw "n should not be less than 0";
	}
	int sum = 0;
	for(int i= 0;i<=n-1;i++){
		sum += arr[i];
	}
	return sum;
}
