#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE=30000020;
const int maxn=100001;
int bufpos;
char buf[MAXSIZE];
void init(){
    #ifdef LOCAL
        freopen("291.txt","r",stdin);
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
typedef long long ll;
const ll mod=998244353;
ll power(ll x,ll y){
	ll t=x,res=1;
	while(y){
		if (y%2)
			(res*=t)%=mod;
		(t*=t)%=mod;
		y/=2;
	}
	return res;
}
ll pls(ll x,ll y){
    return (x*(1-y)+(1-x)*y)%mod;
}
struct atom{
	ll prob1,prob2;
	atom(){
	    prob1=prob2=0;
	}
	atom(ll prob1,ll prob2):prob1(prob1),prob2(prob2){}
	atom operator +(const atom& rhs)const{
		return atom(pls(prob1,rhs.prob1),pls(prob2,rhs.prob2));
	}
	atom& operator +=(const atom& rhs){
        return *this=(*this)+rhs;
	}
};
struct segtree{
    int n;
    atom t[maxn*4];
    int w[maxn*20];
    void init(int n){
        this->n=n;
    }
    int cur;
    void clear(){
        for(int i=1;i<=cur;i++)
            t[w[i]].prob1=t[w[i]].prob2=0;
        cur=0;
    }
    int p;
    atom v;
    void update(int o,int l,int r){
        if (l==r){
            t[w[++cur]=o]+=v;
            return;
        }
        int mid=(l+r)/2;
        if (p<=mid)
            update(o*2,l,mid);
        else update(o*2+1,mid+1,r);
        t[w[++cur]=o]=t[o*2]+t[o*2+1];
    }
    void update(int p,atom& v){
        this->p=p;
        this->v=v;
        update(1,1,n);
    }
    int ql,qr;
    atom query(int o,int l,int r){
        if (ql<=l && qr>=r){
            //printf("on %d %d %lld\n",l,r,t[o].prob1);
            return t[o];
        }
        int mid=(l+r)/2;
        atom res;
        if (ql<=mid)
            res+=query(o*2,l,mid);
        if (qr>mid)
            res+=query(o*2+1,mid+1,r);
        return res;
    }
    atom query(int l,int r){
        ql=l,qr=r;
        return query(1,1,n);
    }
}t;
struct query{
	int typ,p,l,r;
	atom w;
}a[maxn],b[maxn];
bool comp1(const query& x,const query& y){
	return x.l==y.l?x.typ<y.typ:x.l<y.l;
}
bool comp2(const query& x,const query& y){
    return x.r==y.r?x.typ<y.typ:x.r>y.r;
}
ll ans[maxn];
int n;
void cdq(int l,int r){
	if (l==r)
		return;
	int mid=(l+r)/2;
	cdq(l,mid);
	cdq(mid+1,r);
	int cur=0;
	for(int i=l;i<=mid;i++)
		if (a[i].typ==1)
			b[++cur]=a[i];
	for(int i=mid+1;i<=r;i++)
		if (a[i].typ==2)
			b[++cur]=a[i];
    t.clear();
	sort(b+1,b+cur+1,comp1);
	for(int i=1;i<=cur;i++){
        if (!b[i].l)
            continue;
        if (b[i].typ==1){
            //printf("%d %d %lld\n",b[i].l,b[i].r,b[i].w.prob1);
            t.update(b[i].r,b[i].w);
        }else{
            atom x=t.query(b[i].l,b[i].r-1),y=t.query(b[i].r,n);
            //if (b[i].l==1 && b[i].r==5)
                //printf("qaq=%lld\n",x.prob1);
            ans[b[i].p]=pls(ans[b[i].p],pls(x.prob1,y.prob2));
        }
	}
	sort(b+1,b+cur+1,comp2);
	t.clear();
	for(int i=1;i<=cur;i++){
        if (b[i].typ==1)
            t.update(b[i].l,b[i].w);
        else ans[b[i].p]=pls(ans[b[i].p],t.query(b[i].l+1,b[i].r).prob1);
	}
}
bool flag[maxn];
bool isq[maxn];
int main(){
	init();
	n=readint();
	int m=readint();
	t.init(n);
	for(int i=1;i<=m;i++){
        a[i].typ=readint(),a[i].l=readint(),a[i].r=readint();
        a[i].p=i;
        if (a[i].typ==1){
            ll t=power(a[i].r-a[i].l+1,mod-2);
            a[i].w=atom(t,t*2%mod);
            flag[i]=!flag[i-1];
        }else a[i].l--,flag[i]=flag[i-1],isq[i]=true;
	}
	//puts("WTF");
	cdq(1,m);
	for(int i=1;i<=m;i++){
        if (!isq[i])
            continue;
        //printf("%lld\n",ans[i]);
        if (a[i].l || !flag[i])
            ans[i]=(1-ans[i])%mod;
        printf("%lld\n",(ans[i]+mod)%mod);
	}
}

