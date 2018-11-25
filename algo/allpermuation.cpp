#include <string>
#include <vector>
#include <iostream>
#include <utility>


using namespace std;

void perm(int n, vector<int> &v, int it, int &res){
	if(n==0){
		res++;
		//for(auto& w : v) cout << w << " "; cout << endl;
		return;
	} 
	for(int i=it;i<n+1;i++,it++){
		//v.push_back(i);
		perm(n-i,v,it,res);
		//v.pop_back();
	}
	return;
}


int main(){
	int n=5;
	int res=0;
	vector<int> v;
	perm(n,v,1, res);
	cout << res << endl;
	return 0;}

