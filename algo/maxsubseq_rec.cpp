#include <iostream>
#include <vector>
using namespace std;

<<<<<<< HEAD
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
=======
int maxfinder(vector<int> a, int l, int r)
{
	if (a.size() == 0)
		return -1;
	int sum = 0;
	int maxs = 0;
	for (int i = 0; i < a.size(); i++)
	{
		sum += a[i];
		if (sum < 0)
			sum = 0;
		else
			maxs = max(sum, maxs);
	}
	return maxs;
}
int maxfinder_DQ(vector<int> a, int l, int r)
{
	if (a.size() == 0)
		return -1;
	cout << l << " - " << r << endl;
	if (l == r)
	{
		if (a[l] > 0)
			return a[l];
		else
			return 0;
	}
	int lsum = 0;
	int rsum = 0;
	int c = (l + r) / 2;
	lsum += maxfinder_DQ(a, l, c);
	rsum += maxfinder_DQ(a, c + 1, r);
	int lcsum = 0;
	int max_lcsum = 0;
	int crsum = 0;
	int max_crsum = 0;
	for (int i = c; i >= l; i--)
	{
		lcsum += a[i];
		if (lcsum > max_lcsum)
			max_lcsum = lcsum;
	}
	for (int i = c + 1; i <= r; i++)
	{
		crsum += a[i];
		if (crsum > max_crsum)
			max_crsum = crsum;
	}

	cout << "max: " << max(max(lsum, rsum), max_lcsum + max_crsum) << endl;
	return max(max(lsum, rsum), max_lcsum + max_crsum);
}

int main()
{
	static const int arr[] = {+2, -9, +5, 0, -3, +12, -1};
	static const int arr2[] = {};

	vector<int> v(arr, arr + sizeof arr / sizeof arr[0]);
	vector<int> v2(arr2, arr2 + sizeof arr2 / sizeof arr2[0]);

	cout << maxfinder_DQ(v, 0, v.size() - 1) << endl;
	cout << maxfinder(v, 0, v.size() - 1) << endl;
	cout << maxfinder_DQ(v2, 0, v2.size() - 1) << endl;
	cout << maxfinder(v2, 0, v2.size() - 1) << endl;

>>>>>>> refs/remotes/origin/master
	return 0;
}
