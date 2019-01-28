class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int result = 0;
        for(int i=0;i<(int)A.size()-2;i++){
            int dis = A[i+1]-A[i];
            int pos = i+1;
            while((pos+1)<A.size() && (A[pos+1]-A[pos]==dis)) pos++;
            long long len = pos-i+1;
            if(len > 2){
                i = pos;
                result += ((len-2)*(len-1))/2;
            }
        }
        return result;
    }
};