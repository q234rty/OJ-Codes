
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=30000020;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("1487.txt","r",stdin);
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
const int maxn=100001;
struct graph{
	ll sum;
	int n,m;
	struct edge{
		int to,next,cost;
	}e[maxn*2];
	int first[maxn];
	void addedge(int from,int to,int cost){
		e[++m]=(edge){to,first[from],cost};
		first[from]=m;
	}
	bool vis[maxn];
	ll c[maxn],sz[maxn];
	ll f[maxn],g[maxn];
	void dfs(int u){
		sz[u]=c[u];
		vis[u]=1;
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			if (vis[v])
				continue;
			dfs(v);
			sz[u]+=sz[v];
			f[u]+=f[v]+sz[v]*e[i].cost;
		}
	}
	void dfs2(int u){
		vis[u]=1;
		//printf("%d\n",u);
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			//printf("%d\n",v);
			if (vis[v])
				continue;
			g[v]=g[u]+f[u]-f[v]-sz[v]*e[i].cost+(sum-sz[v])*e[i].cost;
			dfs2(v);
		}
	}
	pair<int,ll> work(int n){
		for(int i=1;i<=n;i++)
			sum+=c[i];
		dfs(1);
		memset(vis,0,sizeof(vis));
		dfs2(1);
		int ans=1;
		for(int i=2;i<=n;i++){
			//printf("%lld %lld %lld\n",sz[i],f[i],g[i]);
			if (f[ans]+g[ans]>f[i]+g[i])
				ans=i;
		}
		return make_pair(ans,f[ans]+g[ans]);
	}
}g;
int main(){
	init();
	int n=readint();
	for(int i=1;i<=n;i++)
		g.c[i]=readint();
	for(int i=1;i<n;i++){
		int x=readint(),y=readint(),z=readint();
		g.addedge(x,y,z);
		g.addedge(y,x,z);
	}
	pair<int,ll> ans=g.work(n);
	printf("%d\n%lld",ans.first,ans.second);
}