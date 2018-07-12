#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=100000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("891C.txt","r",stdin);
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
const int maxn=500002;
struct dsu{
	int fa[maxn],rk[maxn];
	pair<int,int> stk[maxn*20];
	int tp;
	void init(int n){
		for(int i=1;i<=n;i++)
			fa[i]=i,rk[i]=0;
		tp=0;
	}
	void revert(int ver){
		while(tp!=ver){
			int x=stk[tp].first,y=stk[tp].second;
			if (x>0)
				fa[x]=y;
			else rk[-x]=y;
			tp--;
		}
	}
	int getf(int x){
		while(fa[x]!=x)
			x=fa[x];
		return x;
	}
	bool mer(int x,int y){
		x=getf(x),y=getf(y);
		if (x==y)
			return false;
		if (rk[x]>rk[y])
			swap(x,y);
		stk[++tp]=make_pair(x,fa[x]);
		stk[++tp]=make_pair(-y,rk[y]);
		fa[x]=y;
		rk[y]=max(rk[y],rk[x]+1);
		return true;
	}
}d;
struct edge{
	int u,v,w,id;
	bool operator <(const edge& rhs)const{
		return w<rhs.w;
	}
}e[maxn];
int to[maxn],lst[maxn];
struct query{
	int id;
	vector<int> a;
};
vector<query> q[maxn];
bool ans[maxn];
int main(){
	init();
	int n=readint(),m=readint();
	for(int i=1;i<=m;i++)
		e[i].id=i,e[i].u=readint(),e[i].v=readint(),e[i].w=readint();
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++){
		to[e[i].id]=i;
		lst[i]=e[i].w==e[i-1].w?lst[i-1]:i;
	}
	int cnt=readint();
	for(int i=1;i<=cnt;i++){
		ans[i]=1;
		int k=readint();
		while(k--){
			int p=to[readint()];
			if (q[lst[p]].empty() || q[lst[p]].back().id!=i)
				q[lst[p]].push_back((query){i});
			q[lst[p]].back().a.push_back(p);
		}
	}
	d.init(n);
	for(int i=1;i<=m;i++){
		if (q[i].size()){
			for(const auto& u:q[i]){
				int ver=d.tp;
				for(const auto& v:u.a){
					if (!d.mer(e[v].u,e[v].v)){
						ans[u.id]=0;
						break;
					}
				}
				d.revert(ver);
			}
		}
		d.mer(e[i].u,e[i].v);
	}
	for(int i=1;i<=cnt;i++)
		puts(ans[i]?"YES":"NO");
}
