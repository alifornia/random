#include <iostream>
#include <vector>


using namespace std;

class Point{
    int x, y;
};
typedef vector<Point> points;


int main(){
	points p;
    p.push_back({-1,2});
    return 0;
}
