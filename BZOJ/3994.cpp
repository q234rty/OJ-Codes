#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
void init(){
    #ifdef LOCAL
        freopen("3994.txt","r",stdin);
    #endif // LOCAL
    buf[fread(buf,1,MAXSIZE,stdin)]='\0';
    bufpos=0;
}
int readint(){
    int val=0;
    for(;!isdigit(buf[bufpos]);bufpos++);
    for(;isdigit(buf[bufpos]);bufpos++)
        val=val*10+buf[bufpos]-'0';
    return val;
}
const int maxn=1000000;
int prime[maxn+1],cur=0,u[maxn+1],c[maxn+1],d[maxn+1];
int sumu[maxn+1];
long long g[maxn+1];
bool notprime[maxn+1];
void sieve(){
    notprime[1]=true;
    u[1]=d[1]=1; //c(1) is undefined
    for(int i=2;i<=maxn;i++){
        if (!notprime[i]){
            prime[++cur]=i;
            u[i]=-1;
            c[i]=1;
            d[i]=2;
            //continue;
        }
        for(int j=1;j<=cur && i*prime[j]<=maxn;j++){
            int t=i*prime[j];
            notprime[t]=true;
            if (i%prime[j]==0){
                d[t]=d[i]/(c[i]+1)*(c[i]+2);
                c[t]=c[i]+1;
                u[t]=0;
                break;
            }
            u[t]=-u[i];
            d[t]=d[i]*d[prime[j]];
            c[t]=1;
        }
    }
    for(int i=1;i<=maxn;i++)
        sumu[i]=sumu[i-1]+u[i],g[i]=g[i-1]+d[i];
}
int main(){
    init();
    sieve();
    int t=readint();
    while(t--){
        int n=readint(),m=readint(),w=min(n,m),nxt;
        long long ans=0;
        for(int i=1;i<=w;i=nxt+1){
            nxt=min(n/(n/i),m/(m/i));
            ans+=(sumu[nxt]-sumu[i-1])*g[n/i]*g[m/i];
        }
        printf("%lld\n",ans);
    }
}
