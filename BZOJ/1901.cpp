#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,f,t) for(int i=(f);i<=(t);i++)
#define WTF
using namespace std;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
void init(){
    #ifdef LOCAL
        freopen("1901.txt","r",stdin);
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
char readchar(){
    for(;isspace(buf[bufpos]);bufpos++);
    return buf[bufpos++];
}
const int maxn=10001;
const int maxm=10001;
struct segkth{
    private:
        static const int maxt=16*16*(maxn+maxm);
        struct node{
            int sum,lson,rson;
            node(){
                sum=lson=rson=0;
            }
        };
        node t[maxt];
        int n,cur;
        int p,v;
        void update(int& o,int l,int r){
            if (!o)
                o=++cur;
            t[o].sum+=v;
            //printf("o=%d,l=%d,r=%d\n",o,l,r);
            if (l==r)
                return;
            int m=(l+r)/2;
            if (p<=m)
                update(t[o].lson,l,m);
            else update(t[o].rson,m+1,r);
        }
    public:
        void init(int n,int maxv){
            this->n=maxv;
            cur=n;
        }
        void ins(int c,int x){
            p=x,v=1;
            update(c,1,n);
        }
        void del(int c,int x){
            p=x,v=-1;
            update(c,1,n);
        }
        int kth(int k,int* add,int addc,int* dec,int decc){
            int l=1,r=n,mid;
            while(l<r){
                //printf("l=%d,r=%d\n",l,r);
                mid=(l+r)/2;
                int sz=0;
                rep(i,1,addc)
                    sz+=t[t[add[i]].lson].sum;
                rep(i,1,decc)
                    sz-=t[t[dec[i]].lson].sum;
                if (sz>=k){ //left
                    rep(i,1,addc)
                        add[i]=t[add[i]].lson;
                    rep(i,1,decc)
                        dec[i]=t[dec[i]].lson;
                    r=mid;
                }else{  //right
                    k-=sz;
                    rep(i,1,addc)
                        add[i]=t[add[i]].rson;
                    rep(i,1,decc)
                        dec[i]=t[dec[i]].rson;
                    l=mid+1;
                }
            }
            return l;
        }
}t;
struct bit{
    private:
        static const int maxw=18;
        int n;
        int val[maxn];
        int add[maxw],dec[maxw];
        inline int lowbit(int x){
            return x&-x;
        }
    public:
        void init(int n,int *a,int maxv){
            this->n=n;
            t.init(n,maxv);
            memcpy(val,a,sizeof(val));
            rep(i,1,n)
                for(int j=i;j<=n;j+=lowbit(j))
                    t.ins(j,val[i]);
        }
        void modify(int p,int v){
            //WTF;
            for(int i=p;i<=n;i+=lowbit(i))
                t.del(i,val[p]),t.ins(i,v);
            val[p]=v;
        }
        int kth(int l,int r,int k){
            //WTF;
            int addc=0,decc=0;
            for(int i=r;i;i-=lowbit(i))
                add[++addc]=i;
            for(int i=l-1;i;i-=lowbit(i))
                dec[++decc]=i;
            //WTF;
            return t.kth(k,add,addc,dec,decc);
        }
}b;
int a[maxn];
int nums[maxn+maxm],cur;
struct query{
    char c;
    int i,j,k;
}q[maxm];
int main(){
    init();
    //WTF;
    int n=readint(),m=readint();
    rep(i,1,n)
        a[i]=readint(),nums[++cur]=a[i];
    rep(i,1,m){
        q[i].c=readchar(),q[i].i=readint(),q[i].j=readint();
        if (q[i].c=='Q')
            q[i].k=readint();
        else nums[++cur]=q[i].j;
    }
    //WTF;
    sort(nums+1,nums+cur+1);
    cur=unique(nums+1,nums+cur+1)-nums-1;
    rep(i,1,n)
        a[i]=lower_bound(nums+1,nums+cur+1,a[i])-nums;
    //WTF;
    b.init(n,a,cur);
    //WTF;
    rep(i,1,m){
        //WTF;
        if (q[i].c=='Q'){
            printf("%d\n",nums[b.kth(q[i].i,q[i].j,q[i].k)]);
        }
        else {
            //WTF;
            b.modify(q[i].i,lower_bound(nums+1,nums+cur+1,q[i].j)-nums);
        }
    }
}
