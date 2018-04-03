#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("5129.txt","r",stdin);
		freopen("5129.out","w",stdout);
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
const int maxn=300002;
const int maxm=600002;
const int nlgn=maxn*20;
struct graph{
	int n,m;
	struct edge{
		int to,next;
	}e[maxm];
	int first[maxn];
	void addedge(int from,int to){
		e[++m]=(edge){to,first[from]};
		first[from]=m;
	}
	int sz[maxn];
	bool vis[maxn];
	int d[maxn][21];
	int gs(int u,int fa){
		sz[u]=1;
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			if (v!=fa && !vis[v])
				sz[u]+=gs(v,u);
		}
		return sz[u];
	}
	int h;
	int ctrd(int u,int fa){
		for(int i=first[u];i;i=e[i].next){
			int v=e[i].to;
			if (v!=fa && !vis[v] && sz[v]>h)
				return ctrd(v,u);
		}
		return u;
	}
	int qwq[nlgn];
	int st[maxn],en[maxn],cur;
	int dep[maxn];
	void bfs(int s,int ly){
		cur++;
		int l=cur,r=cur;
		qwq[cur]=s;
		d[s][ly]=0;
		while(l<=r){
			int u=qwq[l++];
			for(int i=first[u];i;i=e[i].next){
				int v=e[i].to;
				if (d[v][ly]!=-1 || vis[v])
					continue;
				d[v][ly]=d[u][ly]+1;
				qwq[++r]=v;
			}
		}
		cur=r;
	}
	int f[maxn];
	int dcomp(int u,int ly){
		h=gs(u,0)/2;
		int rt=ctrd(u,0);
		vis[rt]=1;
		st[rt]=cur+1;
		dep[rt]=ly;
		bfs(rt,ly);
		en[rt]=cur;
		for(int i=first[rt];i;i=e[i].next){
			int v=e[i].to;
			if (!vis[v])
				f[dcomp(v,ly+1)]=rt;
		}
		return rt;
	}
	priority_queue<pli,vector<pli>,greater<pli> > q;
	int lim[maxn],cost[maxn];
	ll w[maxn];
	void dijkstra(int s){
		memset(w,0x3f,(n+1)*8);
		w[s]=cost[s];
		q.push(make_pair(w[s],s));
		while(!q.empty()){
			pli p=q.top();
			q.pop();
			int u=p.second,tat=u;
			while(u){
				for(int& i=st[u];i<=en[u];i++){ //看起来很像当前弧？喵啊
					int v=qwq[i];
					int dis=d[tat][dep[u]]+d[v][dep[u]];
					if (dis>lim[tat])
						break;
					if (p.first+cost[v]<w[v]){
						w[v]=p.first+cost[v];
						q.push(make_pair(w[v],v));
					}
				}
				u=f[u];
			}
		}
	}
	void work(int s){
		memset(d,-1,sizeof(d));
		dcomp(1,0);
		dijkstra(s);
	}
}g;
int main(){
	init();
	int n=g.n=readint(),s=readint();
	for(int i=1;i<n;i++){
		int u=readint(),v=readint();
		g.addedge(u,v);
		g.addedge(v,u);
	}
	for(int i=1;i<=n;i++)	
		g.lim[i]=readint(),g.cost[i]=readint();
	g.work(s);
	for(int i=1;i<=n;i++)
		printf("%lld\n",g.w[i]-g.cost[i]);
}