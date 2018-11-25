#include <iostream>
#include <vector>
using namespace std;

int maxfinder(vector <int> a,int l, int r){
	cout << l << " - " << r << endl;
	if(l==r){
		if(a[l]>0) return a[l];
		else	return 0;
	}
	int lsum=0;
	int rsum=0;
	int c = (l+r)/2;
	lsum += maxfinder(a,l,c);
	rsum += maxfinder(a,c+1,r);
	int lcsum =0;
	int max_lcsum=0;
	int crsum =0;
	int max_crsum=0;
	for(int i=c;i>=l;i--){
		lcsum+=a[i];
		if(lcsum > max_lcsum) max_lcsum = lcsum;
	}
	for(int i=c+1;i<=r;i++){
		crsum+=a[i];
		if(crsum > max_crsum) max_crsum = crsum;
	}

	cout << "max: " << max(max(lsum,rsum), max_lcsum+max_crsum) << endl;
	return max(max(lsum,rsum),max_lcsum+max_crsum);
}

int main(){
	static const int arr[] =  {+2,-9,+5,0,-3,+12,-1};
	vector<int> v(arr, arr + sizeof arr /sizeof arr[0]) ;

	cout << maxfinder(v,0,v.size()-1) << endl;
	return 0;
}
