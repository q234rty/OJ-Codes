#include <bits/stdc++.h>
using namespace std;
const int MAXSIZE=30000020;
int bufpos;
char buf[MAXSIZE];
void init(){
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
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
struct tag{
	ll add,curadd;
	tag(ll x=0){
		add=x;
		curadd=max(x,0LL);
	}
	tag& operator +=(const tag& rhs){
		curadd=max(curadd,add+rhs.curadd);
		add+=rhs.add;
		return *this;
	}
};
struct atom{
    ll mmax,curmax;
    atom(){
    	mmax=curmax=0;
    }
    atom(ll mmax,ll curmax){
        this->mmax=mmax,this->curmax=curmax;
    }
    atom operator +(const atom& rhs)const{
        return atom(max(mmax,rhs.mmax),max(curmax,rhs.curmax));
    }
    atom& operator +=(const atom& rhs){
    	return *this=*this+rhs;
    }
    atom operator +(const tag& x)const{
    	return atom(mmax+x.add,max(curmax,mmax+x.curadd));
    }
    atom& operator +=(const tag& x){
    	return *this=*this+x;
    }
};
const int maxn=100001;
struct segtree{
    static const int maxt=maxn*4;
    atom t[maxt];
    tag v[maxt];
    int n;
    void init(int n){
        this->n=n;
    }
    void pushdown(int o){
    	v[o*2]+=v[o];
    	t[o*2]+=v[o];
    	v[o*2+1]+=v[o];
    	t[o*2+1]+=v[o];
    	v[o]=tag();
    }
    int ul,ur,uv;
    void update(int o,int l,int r){
    	if (ul<=l && ur>=r){
    		t[o]+=uv;
    		v[o]+=uv;
    		return;
    	}
    	pushdown(o);
    	int mid=(l+r)/2;
    	if (ul<=mid)
    		update(o*2,l,mid);
    	if (ur>mid)
    		update(o*2+1,mid+1,r);
    	t[o]=t[o*2]+t[o*2+1];
    }
    int ql,qr;
    atom query(int o,int l,int r){
    	if (ql<=l && qr>=r)
    		return t[o];
    	int mid=(l+r)/2;
    	atom res;
    	res.mmax=-INF;
    	if (ql<=mid)
    		res+=query(o*2,l,mid);
    	if (qr>mid)
    		res+=query(o*2+1,mid+1,r);
    	return res+v[o];
    }
}t;
struct query{
	int p,l,r;
	bool operator <(const query& rhs)const{
		return r<rhs.r;
	}
}q[maxn];
const int delta=100000;
int now[200003];
int a[maxn];
bool vis[200003];
int lst[maxn];
ll ans[maxn];
int main(){
	init();
	int n=readint();
	t.init(n);
	for(int i=1;i<=n;i++){
		a[i]=readint();
		lst[i]=now[a[i]+delta];
		now[a[i]+delta]=i;
	}
	int m=readint();
	for(int i=1;i<=m;i++)
		q[i].p=i,q[i].l=readint(),q[i].r=readint();
	sort(q+1,q+m+1);
	int now=1;
	for(int i=1;i<=m;i++){
		while(now<=q[i].r){
			t.ul=lst[now]+1;
			t.ur=now;
			t.uv=a[now];
			t.update(1,1,n);
			now++;
		}
		t.ql=q[i].l,t.qr=q[i].r;
		ans[q[i].p]=t.query(1,1,n).curmax;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
}