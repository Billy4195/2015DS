#include <iostream>
/*except practice*/
using namespace std;

int checkZero(int,int,int);

int main(){
	try{
		cout << checkZero(-1,-1,-1)<<endl;
	}catch(int n){
		if(n==1){
			cout<<"All smaller than zero"<<endl;
		}else if(n==2){
			cout<<"All equal to zero"<<endl;
		}
	}


}

int checkZero(int a,int b,int c){
	if(a < 0 && b < 0 && c < 0){
		throw 1;
	}else if(a == 0 && b == 0 && c == 0){
		throw 2;
	}
	return a+b*c+b/c;
}
