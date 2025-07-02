#include <iostream> 
#include <vector>

using namespace std;

int getMaxValue(vector<vector<int>>& b){
    int t = 0;
    for(vector<int> v : b){
        for(int n : v){
            t = max(t, n);
        }
    }

    return t;
}

void moveLeft(vector<vector<int>>& b){
    for(int h=0;h<(int)b.size();h++){
        int p = 0;
        for(int w=0;w<(int)b.size();w++){
            if(b[h][w] != 0){
                b[h][p] = b[h][w];
                if(w != p)
                    b[h][w] = 0;
                
                p++;
            }
        }
    }
}

void sumLeft(vector<vector<int>>& b){
    for(int h=0;h<(int)b.size();h++){
        for(int w=1;w<(int)b.size();w++){
            if(b[h][w-1] != b[h][w]) continue;

            b[h][w-1] *= 2;
            b[h][w] = 0;
        }
    }
}

void moveRight(vector<vector<int>>& b){
    for(int h=0;h<(int)b.size();h++){
        int p = b.size()-1;
        for(int w=b.size()-1;w>=0;w--){
            if(b[h][w] != 0){
                b[h][p] = b[h][w];
                if(w != p)
                    b[h][w] = 0;

                p--;
            }
        }
    }
}

void sumRight(vector<vector<int>>& b){
    for(int h=0;h<(int)b.size();h++){
        for(int w=b.size()-1;w>0;w--){
            if(b[h][w-1] != b[h][w]) continue;

            b[h][w] *= 2;
            b[h][w-1] = 0;
        }
    }
}

void moveUp(vector<vector<int>>& b){
    for(int w=0;w<(int)b.size();w++){
        int p = 0;
        for(int h=0;h<(int)b.size();h++){
            if(b[h][w] != 0){
                b[p][w] = b[h][w];
                if(h != p)
                    b[h][w] = 0;

                p++;
            }
        }
    }
}

void sumUp(vector<vector<int>>& b){
    for(int w=0;w<(int)b.size();w++){
        for(int h=0;h<(int)b.size()-1;h++){
            if(b[h][w] != b[h+1][w]) continue;

            b[h][w] *= 2;
            b[h+1][w] = 0;
        }
    }
}

void moveDown(vector<vector<int>>& b){
    for(int w=0;w<(int)b.size();w++){
        int p = b.size()-1;
        for(int h=b.size()-1;h>=0;h--){
            if(b[h][w] != 0){
                b[p][w] = b[h][w];
                if(h != p)
                    b[h][w] = 0;

                p--;
            }
        }
    }
}

void sumDown(vector<vector<int>>& b){
    for(int w=0;w<(int)b.size();w++){
        for(int h=b.size()-1;h>0;h--){
            if(b[h][w] != b[h-1][w]) continue;

            b[h][w] *= 2;
            b[h-1][w] = 0;
        }
    }
}

void printBoard(vector<vector<int>>& b){
    cout << "--------------------------" << endl;
    for(vector<int> v : b){
        for(int n : v){
            cout << n << " ";
        }
        cout << endl;
    }
}

int run(vector<vector<int>> b, int d, int c){
    c--;
    
    //0:left, 1:right, 2:up, 3:down
    if(d == 0){
        moveLeft(b);
        sumLeft(b);
        moveLeft(b);
    }else if(d == 1){
        moveRight(b);
        sumRight(b);
        moveRight(b);
    }else if(d == 2){
        moveUp(b);
        sumUp(b);
        moveUp(b);
    }else{
        moveDown(b);
        sumDown(b);
        moveDown(b);
    }

    
    if(c == 0) return getMaxValue(b);

    int result = 0;
    for(int i=0;i<4;i++){
        result = max(result, run(b, i, c));
    }

    return result;
}

int main(){
    int size;
    int result = 0;
    vector<vector<int>> board;

    cin >> size;

    for(int i=0;i<size;i++){
        vector<int> temp;
        for(int j=0;j<size;j++){
            int v;
            cin >> v;
            temp.push_back(v);
        }
        board.push_back(temp);
    }

    for(int i=0;i<4;i++){
        result = max(result, run(board, i, 5));
    }

    cout << result << endl;

    return 0;
}