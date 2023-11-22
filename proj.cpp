#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;


int maxProfit(int length, int width, vector<vector<int>> &prices){
    vector<vector<int>> dp(length + 1, vector<int>(width + 1)); // stores max profit
    int l = 0;
    for (int i = 1; i <= length; i++){ // calculates profit of subrectangles
        int w = 0;
        if (i == 50)
            printf("here");
        for (int j = 1; j <= width; j++){
            dp[i][j] = max({dp[i][j-1] + dp[i][j-w], // price of the previous piece + price of the remaining piece
                            dp[i-1][j] + dp[1][j],  // price of piece (i-1) * j dimensions + price of 1 * j piece
                            dp[i-1][j] + dp[i-l][j-w],
                            prices[i][j] } );
            if (dp[i][j] != dp[i][j-1])
                w = j;
            if (dp[i][j] != dp[i-1][j])
                l = i;
        }
    }
    return dp[length][width];
}


int main(){
    int length, width, types;
    int l, w, price;

    cin >> length >> width >> types;

    vector<vector<int>> prices(length + 1, vector<int>(width + 1));

    for (int i = 0; i < types; i++){ // gets sizes and prices
        cin >> l >> w >> price;
        
        if (l <= length && w <= width) // if (l x w) within the slab's dimensions
            prices[l][w] = price; 

        // symmetric matrix -> 1x2 = 2x1
        if (w <= length && l <= width)  // if (w x l) within the slab's dimensions
            prices[w][l] = price;
    }
    
    printf("%d\n", maxProfit(length, width, prices));
    return 0;
}
