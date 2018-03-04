#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=20000020;
const int mod=998244353;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("290.txt","r",stdin);
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
const int maxn=500004;
const int maxm=maxn*4;
ll h[maxn];
struct graph{
	int n,m;
	struct edge{
		int to,next;
		bool del;
	}e[maxm];
	int first[maxn],cnt[maxn];
	void init(int n){
		this->n=n;
		memset(first,0,(n+1)*4);
		memset(cnt,0,(n+1)*4);
		m=1;
	}
	void addedge(int from,int to){
		e[++m]=(edge){to,first[from],0};
		first[from]=m;
	}
	bool vis[maxn];
	void dfs(int u,int fa){
		vis[u]=1;
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			if (!vis[v])
				dfs(v,u);
			else if (v!=fa && !e[i].del){
				e[i].del=e[i^1].del=1;
				cnt[v]--,cnt[u]++;
				// printf("233 %d %d\n",v,u);
			}
		}
	}
	void dfs2(int u){
		vis[u]=1;
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			if (!vis[v]){
				dfs2(v);
				// if (u==8 && v==2)
					// printf("%d %d\n",u,v);
				cnt[u]+=cnt[v];
				if (cnt[v])
					e[i].del=e[i^1].del=1;
			}
		}
	}
	int deg[maxn];
	ll work(){
		memset(vis,0,n+1);
		dfs(1,0);
		memset(vis,0,n+1);
		dfs2(1);
		memset(deg,0,(n+1)*4);
		for(int i=1;i<=n;i++)
			if (cnt[i]>=2)
				return 0;
		for(int i=2;i<=m;i++)
			if (!e[i].del)
				deg[e[i].to]++;
			// else printf("%d\n",e[i].to);
		ll ans=1;
		for(int i=1;i<=n;i++){
			// printf("deg[%d]=%d\n",i,deg[i]);
			ans=(ans*h[deg[i]])%mod;
		}
		return ans;
	}
}g;
int main(){
	init();
	h[0]=h[1]=1;
	for(int i=2;i<=500000;i++)
		h[i]=(h[i-1]+h[i-2]*(i-1))%mod;
	int T=readint();
	while(T--){
		int n=readint(),m=readint();
		g.init(n);
		while(m--){
			int u=readint(),v=readint();
			g.addedge(u,v);
			g.addedge(v,u);
		}
		printf("%lld\n",g.work());
	}
}