#include <cstdio>
#include <cstring>
using namespace std;
int dp[2][4201];
int main(){
    int n,p;
    scanf("%d%d",&n,&p);
    int cur=1;
    memset(dp[0],0,sizeof(dp[0]));
    dp[0][1]=1;
    for(int i=2;i<=n;i++){
        memset(dp[cur],0,sizeof(dp[cur]));
        for(int j=1;j<=i;j++)
            dp[cur][j]=(dp[cur][j-1]+dp[cur^1][i-j+1])%p;
        cur^=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        (ans+=dp[cur^1][i])%=p;
    printf("%d",ans*2%p);
}
