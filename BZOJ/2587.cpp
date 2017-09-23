#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
const int MAXSIZE=30000020;
const int INF=0x3f3f3f3f;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
    #ifdef LOCAL
        freopen("2587.txt","r",stdin);
    #endif
    buf[fread(buf,1,MAXSIZE,stdin)]='\0';
    bufpos=0;
}
#if NEG
int readint(){
    bool isneg;
    int val=0;
    for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
    bufpos+=(isneg=buf[bufpos]=='-');
    for(;isdigit(buf[bufpos]);bufpos++)
        val=val*10+buf[bufpos]-'0';
    return isneg?-val:val;
}
#else
int readint(){
    int val=0;
    for(;!isdigit(buf[bufpos]);bufpos++);
    for(;isdigit(buf[bufpos]);bufpos++)
        val=val*10+buf[bufpos]-'0';
    return val;
}
#endif
char readchar(){
    for(;isspace(buf[bufpos]);bufpos++);
    return buf[bufpos++];
}
int readstr(char* s){
    int cur=0;
    for(;isspace(buf[bufpos]);bufpos++);
    for(;!isspace(buf[bufpos]);bufpos++)
        s[cur++]=buf[bufpos];
    s[cur]='\0';
    return cur;
}
int cnt[1000002],tmp[1000002],a[1000002],b[1000002],f[1000002],g[1000002],lst[1000002];
int nxt[1000002],first[1000002],nxt2[1000002],first2[1000002];
void add(int p,int v){
    nxt[v]=first[p];
    first[p]=v;
}
void add2(int p,int v){
    nxt2[v]=first2[p];
    first2[p]=v;
}
struct cmp{
    bool operator ()(const int &x,const int &y){
        return f[x]<f[y] || (f[x]==f[y] && g[x]>g[y]);
    }
};
typedef __gnu_pbds::priority_queue<int,cmp> heap;
heap q;
heap::point_iterator it[1000001];  
int main(){
    init();
    int n=readint();
    for(int i=1;i<=n;i++)
        tmp[i]=readint(),cnt[tmp[i]]++;
    for(int i=n;i;i--)
        cnt[i]+=cnt[i+1];
    for(int i=1;i<=n;i++)
        b[cnt[tmp[i]]]=i,a[cnt[tmp[i]]--]=tmp[i];
    int now=0;
    //for(int i=1;i<=n;i++)
        //printf("%d ",a[i]);
    for(int i=1;i<=n;i++){ //g[j]+j<=i
        //puts("WTF");
        for(int to=first2[i];to;to=nxt2[to]){
            if (g[to]+to<i){
                if (f[to]>=f[now])
                    now=to;
            }else {
                //printf("adding %d\n",to);
                it[to]=q.push(to);
            }
        }
        //puts("233");
        for(int j=first[i];j;j=nxt[j]){
            if (j+a[j+1]>i)
                continue;
            //printf("%d\n",j);
            q.erase(it[j]);
            if (f[j]>f[now] || (f[j]==f[now] && j>now))
                now=j;
        }
        //puts("tat");
        if (q.empty()){
            if (!now && i<a[1]){
                g[i]=INF;
                continue;
            }
            f[i]=f[now]+1;
            g[i]=i-now;
            lst[i]=now;
        }else{
            int x=q.top();
            if (f[x]==f[now]){
                f[i]=f[x]+1;
                if (i-now<g[x])
                    g[i]=i-now,lst[i]=now;
                else g[i]=g[x],lst[i]=x;
            }else if (f[x]<f[now])
                f[i]=f[now]+1,g[i]=i-now,lst[i]=now;
            else f[i]=f[x]+1,g[i]=g[x],lst[i]=x;
        }
        //puts("qwq");
        //printf("f[%d]=%d\n",i,f[i]);
        if (g[i]+i<=n)
            add(g[i]+i,i);
        if (i<n && i+a[i+1]<=n)
            add2(i+a[i+1],i);
    }
    printf("%d\n",f[n]);
    for(int i=n;i;){
        int w=lst[i];
        printf("%d ",i-w);
        while(i>w){
            printf("%d ",b[i]);
            i--;
        }
        putchar('\n');
    }
}