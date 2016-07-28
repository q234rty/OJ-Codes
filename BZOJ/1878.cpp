#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXSIZE=30000020;
int bufpos;
char buf[MAXSIZE];
void init(){
    #ifdef LOCAL
        freopen("1878.txt","r",stdin);
    #endif // LOCAL
    buf[fread(buf,1,MAXSIZE,stdin)]='\0';
    bufpos=0;
}
int readint(){
    bool isneg;
    int val=0;
    for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
    bufpos+=(isneg=(buf[bufpos]=='-'))?1:0;
    for(;isdigit(buf[bufpos]);bufpos++)
        val=val*10+buf[bufpos]-'0';
    return isneg?-val:val;
}
struct bit{
    int t[50001];
    int n;
    void init(int n){
        this->n=n;
        memset(t,0,sizeof(t));
    }
    inline int lowbit(int x){
        return (x&(-x));
    }
    int sum(int x){
        int ret=0;
        for(int i=x;i>0;i-=lowbit(i))
            ret+=t[i];
        return ret;
    }
    void add(int p,int v){
        for(int i=p;i<=n;i+=lowbit(i))
            t[i]+=v;
        //for(int i=1;i<=n;i++)
        	//printf("%d ",t[i]);
    }
}t;
int nxt[50001];
int now[1000001];
bool app[1000001];
int a[50001];
struct query{
    int l,r,p;
    bool operator <(const query& rhs)const{
        return l<rhs.l;
    }
};
query q[200001];
int ans[200001];
int main(){
    init();
    int n=readint();
    t.init(n);
    for(int i=1;i<=n;i++)
        a[i]=readint();
    int m=readint();
    for(int i=1;i<=m;i++){
        q[i].l=readint(),q[i].r=readint(),q[i].p=i;
    }
    sort(q+1,q+m+1);
    memset(now,-1,sizeof(now));
    for(int i=n;i>=1;i--){
        nxt[i]=now[a[i]];
        now[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if (!app[a[i]])
            t.add(i,1),app[a[i]]=true;
    }
    q[0].l=1;
    for(int i=1;i<=m;i++){
        for(int j=q[i-1].l;j<q[i].l;j++)
            if (nxt[j]!=-1)
                t.add(nxt[j],1);

        ans[q[i].p]=t.sum(q[i].r)-t.sum(q[i].l-1);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}
