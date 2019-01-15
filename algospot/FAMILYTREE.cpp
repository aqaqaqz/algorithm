#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution{
	int n;
	int people;
	int cnt;
	unordered_map<int, vector<int>> m;
	unordered_map<int, pair<int, int>> rm;

	void makeRelationMap(int p, int d){
		for(int n : m[p]){
			rm[n] = pair<int, int>(p, d+1);
			makeRelationMap(n, d+1);
		}
	}
public:
	void run(){
		cin >> n;
		while(n--){
			m.clear();
			rm.clear();

			cin >> people >> cnt;
			int temp;
			for(int i=0;i<people-1;i++){
				cin >> temp;
				m[temp].push_back(i+1);
			}

			rm[0] = pair<int, int>(-1, 0);
			makeRelationMap(0, 0);

			while(cnt--){
				int a, b;
				cin >> a >> b;
				pair<int, int> c1, c2;
				c1 = rm[a];
				c2 = rm[b];

				int result = 0;

				while(c1.second != c2.second){
					if(c1.second > c2.second){
						a = c1.first;
						c1 = rm[c1.first];
					}else{
						b = c2.first;
						c2 = rm[c2.first];
					}
					result++;
				}
				while(a != b){
					a = c1.first;
					c1 = rm[c1.first];
					b = c2.first;
					c2 = rm[c2.first];

					result += 2;
				}

				cout << result << endl;
			}
		}
	}
};

int main(){
	Solution s;
	s.run();

	return 0;
}
