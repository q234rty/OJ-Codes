#include <bits/stdc++.h>
using namespace std;
const int INF=100000;
struct tag{
	int l,r;
	tag():l(0),r(INF){}
	tag(int x):l(x),r(x){}
	tag(int l,int r):l(l),r(r){}
	tag operator +(const tag& rhs)const{
		if (r<rhs.l)
			return rhs.l;
		if (rhs.r<l)
			return rhs.r;
		return tag(max(l,rhs.l),min(r,rhs.r));
	}
	tag& operator +=(const tag& rhs){
		return *this=*this+rhs;
	}
};
const int maxn=2000001;
struct segtree{
	int n;
	tag tagv[maxn*4];
	void build(int o,int l,int r){
		if (l==r){
			tagv[o]=0;
			return;
		}
		int mid=(l+r)/2;
		build(o*2,l,mid);
		build(o*2+1,mid+1,r);
	}
	void init(int n){
		this->n=n;
		build(1,0,n-1);
	}
	void pushdown(int o){
		tagv[o*2]+=tagv[o];
		tagv[o*2+1]+=tagv[o];
		tagv[o]=tag();
	}
	int ul,ur;
	tag v;
	void update(int o,int l,int r){
		if (ul<=l && ur>=r){
			tagv[o]+=v;
			return;
		}
		int mid=(l+r)/2;
		pushdown(o);
		if (ul<=mid)
			update(o*2,l,mid);
		if (ur>mid)
			update(o*2+1,mid+1,r);
	}
	void update(int op,int l,int r,int h){
		ul=l,ur=r;
		v=op==1?tag(h,INF):tag(0,h);
		update(1,0,n-1);
	}
	int* ans;
	void dfs(int o,int l,int r,tag t=tag()){
		if (l==r){
			ans[l]=(tagv[o]+t).l;
			return;
		}
		int mid=(l+r)/2;
		tag w=tagv[o]+t;
		dfs(o*2,l,mid,w);
		dfs(o*2+1,mid+1,r,w);
	}
	void query(int *ans){
		this->ans=ans;
		dfs(1,0,n-1);
	}
}t;
void buildWall(int n,int m,int *op,int *l,int *r,int *h,int *ans){
	t.init(n);
	for(int i=0;i<m;i++)
		t.update(op[i],l[i],r[i],h[i]);
	t.query(ans);
}
