#include <iostream>
//evaluate polynomial by Honer rule
using namespace std;

int Honer(int *arr,int n,int x,int &cnt);
int main(){
	int cnt=0;
	int arr[]={3,0,2,0,5};
	cout << Honer(arr,5,0,cnt)<<endl;
    cout << "Count: " << cnt;
	return 0;
}

int Honer(int *arr,int n,int x,int &cnt){
	if(n==2){
		cnt++;
		return arr[0]*x+arr[1];
	}else{
		cnt++;
		return Honer(arr,n-1,x,cnt)*x+arr[n-1];
	}
}
