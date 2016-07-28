#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXSIZE=10000020;
const int INF=0x3f3f3f3f;
int bufpos;
char buf[MAXSIZE];
void init(){
    #ifdef LOCAL
        freopen("4326.txt","r",stdin);
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
const int maxn=300001;
const int maxq=300001;
const int maxm=600001;
struct query{
    int u,v,lc,len;
    bool operator < (const query& rhs)const{
        return len>rhs.len;
    }
};
struct edge{
    int to,cost,next;
};
struct graph{
    int n,m;
    edge e[maxm];
    int first[maxn];
    int dep[maxn],fa[maxn],top[maxn],sz[maxn],son[maxn],mark[maxn],dist[maxn],w[maxn],val[maxn],b[maxn];
    query q[maxq];
    int cur;
    void init(int n){
        this->n=n;
        m=0;
        memset(first,0,sizeof(first));
    }
    void addedge(int from,int to,int cost){
        e[++m]=(edge){to,cost,first[from]};
        first[from]=m;
    }
    void dfs(int u){
        sz[u]=1;
        for(int i=first[u];i;i=e[i].next){
            int v=e[i].to;
            if (dep[v])
                continue;
            fa[v]=u;
            dep[v]=dep[u]+1;
            dist[v]=dist[u]+e[i].cost;
            w[v]=e[i].cost;
            dfs(v);
            sz[u]+=sz[v];
            if (!son[u] || sz[v]>sz[son[u]])
                son[u]=v;
        }
    }
    void dfs2(int u,int tp){
        top[u]=tp;
        b[++cur]=u;
        if (son[u])
            dfs2(son[u],tp);
        for(int i=first[u];i;i=e[i].next){
            int v=e[i].to;
            if (!top[v])
                dfs2(v,v);
        }
    }
    void prepare(){
        dep[1]=1;
        dist[1]=0;
        fa[1]=-1;
        dfs(1);
        cur=0;
        dfs2(1,1);
        cur=0;
    }
    int lca(int u,int v){
        for(;top[u]!=top[v];u=fa[top[u]])
            if (dep[top[u]]<dep[top[v]])
                swap(u,v);
        return dep[u]<dep[v]?u:v;
    }
    void addquery(int u,int v){  //O(log n)
        int lc=lca(u,v);
        q[++cur]=(query){u,v,lc,dist[u]+dist[v]-2*dist[lc]};
    }
    int num,mmax;
    bool check(int x){  //O(n)
        memset(mark,0,sizeof(mark));
        memset(val,0,sizeof(val));
        num=mmax=0;
        for(int i=1;q[i].len>x && i<=cur;i++){
            num++;
            mark[q[i].u]++;
            mark[q[i].v]++;
            mark[q[i].lc]-=2;
        }
        //puts("WTF");
        for(int i=n;i>=2;i--){
            val[b[i]]+=mark[b[i]];
            if (val[b[i]]==num)
                mmax=max(mmax,w[b[i]]);
            val[fa[b[i]]]+=val[b[i]];
        }
        //printf("check(%d)=%d\n",x,(q[1].len-mmax)<=x);
        return (q[1].len-mmax)<=x;
    }
    int get(){ //O(nlogn)
        sort(q+1,q+cur+1);
        //binary search
        int low=0,high=q[1].len+1;
        while(low<high){
            int mid=(low+high)/2;
            if (check(mid))
                high=mid;
            else low=mid+1;
        }
        return low;
    }
}g;
extern int main2(void) __asm__ ("_main2");
int main2(){
    init();
    int n=readint(),m=readint();
    g.init(n);
    for(int i=1;i<=n-1;i++){
        int x=readint(),y=readint(),z=readint();
        g.addedge(x,y,z);
        g.addedge(y,x,z);
    }
    g.prepare();
    //puts("WTF");
    for(int i=1;i<=m;i++){
        int u=readint(),v=readint();
        g.addquery(u,v);
    }
    //puts("WTF");
    printf("%d\n",g.get());
    exit(0);
}
int main() {
    int size = 256 << 20;  // 256Mb
    char *p = (char *)malloc(size) + size;
    __asm__ __volatile__(
        "movl  %0, %%esp\n"
        "pushl $_exit\n"
        "jmp _main2\n"
        :: "r"(p));
}
