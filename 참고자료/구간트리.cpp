#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct RMQ{
	const int INT_MAX = numeric_limits<int>::max();
	int n;
	vector<int> rangeMin;
	RMQ(const vector<int>& arr){
		n = arr.size();
		rangeMin.resize(n*4);
		init(arr, 0, n-1, 1);
	}
	int init(const vector<int>& arr, int left, int right, int node){
		if(left == right)
			return rangeMin[node] = arr[left];
		int mid = (left + right) /2;
		int leftMin = init(arr, left, mid, node*2);
		int rightMin = init(arr, mid+1, right, node*2+1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	int getMin(int l, int r, int n, int ll, int rl){
		if(ll>r || rl<l) return INT_MAX;
		if(ll>=l && rl<=r) return rangeMin[n];
		int m = (ll+rl)/2;
		return min(getMin(l, r, n*2, ll, m), getMin(l, r, n*2+1, m+1, rl));
	}
	void update(int i, int v, int n, int ll, int rl){
		if(ll > i || rl < i) return;
		else if(ll <= i && rl >= i){
			rangeMin[n] = min(rangeMin[n], v);
			int m = (ll+rl)/2;
			if(ll!=rl){
				update(i, v, n*2, ll, m);
				update(i, v, n*2+1, m+1, rl);
			}
		}
	}
};

int main(){
	vector<int> v;
	for(int i=0;i<10000;i++) v.push_back(i);
	RMQ rmq(v);

	cout << rmq.getMin(15, 7771, 1, 0, rmq.n-1) << endl;
	rmq.update(20, 0, 1, 0, rmq.n-1);
	cout << rmq.getMin(15, 7771, 1, 0, rmq.n-1) << endl;

	return 0;
}
