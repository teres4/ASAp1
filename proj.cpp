#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;


int getLastC(int row, int column, vector<vector<int>> &dp){
    if (column <= 1)
        return 0;
    while (column > 1 && dp[row][column] == dp[row][column - 1]){
        column--;
    }
    return column;
    
    // if (column <= 0)
    //     return 0;
    
    // if (dp[row][column] != dp[row][column - 1])
    //     return column;
    
    // return getLastC(row, column - 1, dp);

}

int getLastR(int row, int column, vector<vector<int>> dp){
    if (row <= 1)
        return 0;

    while (row > 1 && dp[row][column] == dp[row - 1][column])
        row--;
    return row;
    // if (row <= 0)
    //     return 0;
    // if (dp[row][column] != dp[row - 1][column])
    //     return row;
    
    // return getLastR(row - 1, column, dp);

} 


int maxProfit(int length, int width, vector<vector<int>> &prices){
    vector<vector<int>> dp(length + 1, vector<int>(width + 1)); // stores max profit
    int l = 0;
    for (int i = 1; i <= length; i++){ // calculates profit of subrectangles
        int w = 0;
        for (int j = 1; j <= width; j++){
            w = getLastC(i, j - 1, dp);
            l = getLastR(i - 1, j, dp);

            dp[i][j] = max({dp[i][j-1] + dp[i][j-w], // price of the previous piece + price of the remaining piece
                            dp[i-1][j] + dp[1][j],  // price of piece (i-1) * j dimensions + price of 1 * j piece
                            dp[i-1][j] + dp[i-l][j-w],
                            dp[i-1][j] + dp[i-l][j],
                            prices[i][j] } );
            // if (dp[i][j] != dp[i][j-1])
            //     w = j;
            // if (dp[i][j] != dp[i-1][j])
            //     l = i;
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
