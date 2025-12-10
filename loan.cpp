int maxLoanProfit(int W, vector& loans, vector& returns, int n){
    vector> dp(n+1, vector(W+1,0));
    for(int i=1;i<=n;i++){
        for(int w=0;w<=W;w++){
            if(loans[i-1]<=w)
                dp[i][w]=max(dp[i-1][w], dp[i-1][w-loans[i-1]]+returns[i-1]);
            else dp[i][w]=dp[i-1][w];
        }
    }
    return dp[n][W];
}
