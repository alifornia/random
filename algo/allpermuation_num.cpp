#include <string>
#include <vector>
#include <iostream>
#include <utility>


using namespace std;

int res=0;

void perm(int n, int i){
	res+=(n==0);
	while(i<n+1) perm(n-i,i++);
}


int main(){
	perm(5,1);
	cout << res << endl;
	return 0;

}

