#include <iostream>

using namespace std;

bool isPalin(string str){
	int str_size = str.size()-1;
	for(int i=0; i < str_size; i++){
		if(str[i] != str[str_size-i])
			return false;
	}
	return true;
}



int main(){
	string str_in;
	cin >> str_in;
	
	cout << str_in << " is: "<< isPalin(str_in) << endl;
	return 0;
}
