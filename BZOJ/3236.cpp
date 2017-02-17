#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXSIZE=40000020;
int bufpos;
char buf[MAXSIZE];
void init(){
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
struct block{
    int n,sz,num;
    int sum[321],o[321];
    int cnt[100001];
    int w[100001];
    int st[321];
    void init(int n){
        sz=sqrt(n)+0.5;
        num=(n-1)/sz+1;
        st[1]=1;
        for(int i=1;i<=n;i++)
            w[i]=(i-1)/sz+1;
        for(int i=2;i<=num;i++)
            st[i]=st[i-1]+sz;
        st[num+1]=n+1;
    }
    void update(int x,int sgn){
        if (!cnt[x])
            o[w[x]]++;
        cnt[x]+=sgn;
        sum[w[x]]+=sgn;
        if (!cnt[x])
            o[w[x]]--;
    }
    pair<int,int> query(int a,int b){
        int res1=0,res2=0;
        if (w[a]==w[b]){
            for(int i=a;i<=b;i++)
                res1+=cnt[i],res2+=!!cnt[i];
            return make_pair(res1,res2);
        }
        for(int i=w[a]+1;i<w[b];i++)
            res1+=sum[i],res2+=o[i];
        for(int i=a;i<st[w[a]+1];i++)
            res1+=cnt[i],res2+=!!cnt[i];
        for(int i=st[w[b]];i<=b;i++)
            res1+=cnt[i],res2+=!!cnt[i];
        return make_pair(res1,res2);
    }
}t;
int sz;
struct query{
    int p,l,r,a,b;
    bool operator <(const query& rhs)const{
        return l/sz!=rhs.l/sz?l/sz<rhs.l/sz:r<rhs.r;
    }
}q[1000001];
int a[100001];
pair<int,int> ans[1000001];
int main(){
    init();
    int n=readint(),m=readint();
    sz=sqrt(n)+0.5;
    for(int i=1;i<=n;i++)
        a[i]=readint();
    for(int i=1;i<=m;i++)
        q[i].p=i,q[i].l=readint(),q[i].r=readint(),q[i].a=readint(),q[i].b=readint();
    sort(q+1,q+m+1);
    int l=1,r=0;
    t.init(n);
    for(int i=1;i<=m;i++){
        while(l<q[i].l)
            t.update(a[l++],-1);
        while(r<q[i].r)
            t.update(a[++r],1);
        while(l>q[i].l)
            t.update(a[--l],1);
        while(r>q[i].r)
            t.update(a[r--],-1);
        ans[q[i].p]=t.query(q[i].a,q[i].b);
    }
    for(int i=1;i<=m;i++)
        printf("%d %d\n",ans[i].first,ans[i].second);
}
