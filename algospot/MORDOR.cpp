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
	RMQ(const vector<int>& arr){
		n = arr.size();
		rangeMin.resize(n*4);
		rangeMax.resize(n*4);
		init(arr, 0, n-1, 1, "min");
		init(arr, 0, n-1, 1, "max");
	}
	int init(const vector<int>& arr, int left, int right, int node, string type){
		if(left == right){
			if("min" == type)
				return rangeMin[node] = arr[left];
			else
				return rangeMax[node] = arr[left];
		}
		int mid = (left + right) /2;
		int leftVal = init(arr, left, mid, node*2, type);
		int rightVal = init(arr, mid+1, right, node*2+1, type);

		if("min" == type)
			return rangeMin[node] = min(leftVal, rightVal);
		else
			return rangeMax[node] = max(leftVal, rightVal);
	}
	int getVal(int l, int r, int n, int ll, int rl, string type){
		if(ll>r || rl<l) return ("min"==type?INT_MAX:0);
		if(ll>=l && rl<=r) return ("min"==type?rangeMin[n]:rangeMax[n]);
		int m = (ll+rl)/2;
		if("min" == type)
			return min(getVal(l, r, n*2, ll, m, type), getVal(l, r, n*2+1, m+1, rl, type));
		else
			return max(getVal(l, r, n*2, ll, m, type), getVal(l, r, n*2+1, m+1, rl, type));
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
			cout << rmq.getVal(l, r, 1, 0, s-1, "max") - rmq.getVal(l, r, 1, 0, s-1, "min") << endl;
		}
	}

	return 0;
}
