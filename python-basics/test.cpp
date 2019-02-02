#include <vector>
#include <iostream>
using namespace std; 
  
long int ss( vector<int> arr) 
{ 
    long int result = 0; 
    int n = arr.size();
  
    for (int i=0; i<n; i++){
        if(arr[i]<0) i=-i;
        result += (arr[i] * (i+1) * (n-i)); 
        }
  
    return result ; 
} 
  
int main() 
{ 
    vector<int> arr={ -1,1}; 


    cout << ss(arr) << endl; 
    return 0; 
}