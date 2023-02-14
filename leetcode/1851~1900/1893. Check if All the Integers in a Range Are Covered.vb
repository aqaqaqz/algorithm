class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector<bool> temp(51, false);
        for(vector<int>& v : ranges){
            for(int i=v[0];i<=v[1];i++)
                temp[i] = true;
        }
        
        bool result = true;
        for(int i=left;i<=right;i++)
            result &= temp[i];
        
        return result;
    }
};