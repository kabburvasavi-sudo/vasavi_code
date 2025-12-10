#include <iostream>
using namespace std;

int maxLoanProfit(int W, int loans[], int returns[], int n) {
    int dp[20][100]; // simple static DP table (adjust limits as needed)

    // initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (loans[i-1] <= w)
                dp[i][w] = max(dp[i-1][w],
                               dp[i-1][w - loans[i-1]] + returns[i-1]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[n][W];
}

int main() {
    int n = 4;                          // number of applicants
    int loanLimit = 10;                 // total money available (Capacity W)

    int loans[]   = {4, 5, 3, 6};       // loan amounts requested
    int returns[] = {7, 9, 4, 8};       // expected returns (profit)

    cout << "\nLoan Distribution Optimization\n";
    cout << "--------------------------------\n";

    int maxProfit = maxLoanProfit(loanLimit, loans, returns, n);

    cout << "Maximum Profit the Bank Can Earn = " << maxProfit << endl;

    return 0;
}
