#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
    #ifdef LOCAL
        freopen("4137.txt","r",stdin);
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
const int maxn=100005;
struct trie{
    struct node{
        int sum,ls,rs;
    }t[maxn*21];
    int cur;
    void clear(){
        cur=ver=0;
    }
    int rt[maxn],ver;
    void insert(int x){
        t[++cur]=t[rt[ver]];
        int o=rt[++ver]=cur;
        for(int i=17;i>=0;i--){
            t[o].sum++;
            int &v=(x>>i&1)?t[o].rs:t[o].ls;
            t[++cur]=t[v];
            o=v=cur;
        }
        t[o].sum++;
    }
    int query(int l,int r,int x){
        // printf("query %d %d %d\n",l,r,x);
        int lo=rt[l-1],ro=rt[r],ans=0;
        for(int i=17;i>=0;i--){
            if (x>>i&1){
                if (t[t[ro].ls].sum>t[t[lo].ls].sum)
                    lo=t[lo].ls,ro=t[ro].ls,ans|=1<<i;
                else lo=t[lo].rs,ro=t[ro].rs;
            }else{
                if (t[t[ro].rs].sum>t[t[lo].rs].sum)
                    lo=t[lo].rs,ro=t[ro].rs,ans|=1<<i;
                else lo=t[lo].ls,ro=t[ro].ls;
            }
        }
        // puts("after query");
        return ans;
    }
}t;
struct query{
    int l,r,x,ans;
}w[maxn];
struct item{
    int p,v;
    bool operator <(const item& rhs)const{
        return p<rhs.p;
    }
};
int ans[maxn];
struct segtree{
    int n;
    vector<int> q[maxn*4];
    vector<item> a[maxn*4];
    int p;
    item it;
    void update(int o,int l,int r){
        // printf("update %d %d %d\n",o,l,r);
        a[o].push_back(it);
        if (l==r)
            return;
        int mid=(l+r)/2;
        if (p<=mid)
            update(o*2,l,mid);
        else update(o*2+1,mid+1,r);
    }
    int ql,qr,id;
    void addq(int o,int l,int r){
        if (ql<=l && qr>=r){
            q[o].push_back(id);
            return;
        }
        int mid=(l+r)/2;
        if (ql<=mid)
            addq(o*2,l,mid);
        if (qr>mid)
            addq(o*2+1,mid+1,r);
    }
    void work(int o){
        t.clear();
        sort(a[o].begin(),a[o].end());
        for(int i=0;i<a[o].size();i++)
            t.insert(a[o][i].v);
        for(int i=0;i<q[o].size();i++){
            query & qwq=w[q[o][i]];
            int l=lower_bound(a[o].begin(),a[o].end(),(item){qwq.l,0})-a[o].begin()+1,
                r=upper_bound(a[o].begin(),a[o].end(),(item){qwq.r,0})-a[o].begin();
            if (l>r)
                continue;
            qwq.ans=max(qwq.ans,t.query(l,r,qwq.x));
        }
    }
    void work(){
        for(int i=1;i<=4*n;i++)
            if (q[i].size() && a[i].size())
                work(i);
    }
}s;
int main(){
    init();
    int n=readint(),m=readint();
    s.n=m+1;
    for(int i=1;i<=n;i++)
        t.insert(readint());
    // puts("WTF");
    int day=1,cur=0;
    for(int o=1;o<=m;o++){
        int op=readint();
        if (!op){
            int p=readint(),v=readint();
            s.p=++day,s.it=(item){p,v};
            s.update(1,1,s.n);
        }else{
            int l=readint(),r=readint(),x=readint(),d=readint();
            // printf("query %d %d %d %d\n",l,r,x,d);
            w[++cur]=(query){l,r,x,t.query(l,r,x)};
            if (!d)
                continue;
            s.ql=max(day-d+1,1),s.qr=day,s.id=cur;
            s.addq(1,1,s.n);
        }
    }
    // puts("WTF");
    s.work();
    // printf("cur=%d\n",cur);
    for(int i=1;i<=cur;i++)
        printf("%d\n",w[i].ans);
}