#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;

struct RMQ{
	const int INT_MAX = numeric_limits<int>::max();
	int n;
	vector<int> rangeMin;
	vector<int> rangeMax;
	RMQ(vector<int>& arr){
		n = arr.size();
		rangeMin.resize(n*4);
		rangeMax.resize(n*4);
		init(arr, 0, n-1, 1, rangeMin);
		for(int &n : arr) n *= -1;
		init(arr, 0, n-1, 1, rangeMax);
	}
	int init(const vector<int>& arr, int left, int right, int node, vector<int> &range){
		if(left == right)
			return range[node] = arr[left];

		int mid = (left + right) /2;
		int leftVal = init(arr, left, mid, node*2, range);
		int rightVal = init(arr, mid+1, right, node*2+1, range);

		return range[node] = min(leftVal, rightVal);
	}
	int getVal(int l, int r, int n, int ll, int rl, vector<int> &range){
		if(ll>r || rl<l) return INT_MAX;
		if(ll>=l && rl<=r) return range[n];
		int m = (ll+rl)/2;
		return min(getVal(l, r, n*2, ll, m, range), getVal(l, r, n*2+1, m+1, rl, range));
	}
};

int main(){
	vector<int> v;
	int n;
	cin >> n;
	while(n--){
		int s, cnt;
		cin >> s >> cnt;
		vector<int> v(s);
		for(int i=0;i<s;i++) cin >> v[i];
		RMQ rmq(v);
		while(cnt--){
			int l, r;
			cin >> l >> r;
			cout << -1*rmq.getVal(l, r, 1, 0, s-1, rmq.rangeMax) - rmq.getVal(l, r, 1, 0, s-1, rmq.rangeMin) << endl;
		}
	}

	return 0;
}
