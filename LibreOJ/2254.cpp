#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("2254.txt","r",stdin);
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
ll ans[50001],now;
int a[50001],cnt[2][50001],pl[50001];
struct query{
	int p,sgn,l1,l2;
	bool operator <(const query& rhs)const{
		return pl[l1]!=pl[rhs.l1]?pl[l1]<pl[rhs.l1]:l2<rhs.l2;
	}
}q[200001];
void update(int p,int v,int sgn){
	now+=sgn*cnt[p^1][v];
	cnt[p][v]+=sgn;
}
int main(){
	init();
	int n=readint(),cur=0;
	for(int i=1;i<=n;i++)
		a[i]=readint();
	int m=readint();
	for(int i=1;i<=m;i++){
		int l1=readint()-1,r1=readint(),l2=readint()-1,r2=readint();
		if (l1)
			q[++cur]=(query){i,-1,l1,r2};
		if (l2)
			q[++cur]=(query){i,-1,l2,r1};
		if (l1 && l2)
			q[++cur]=(query){i,1,l1,l2};
		q[++cur]=(query){i,1,r1,r2};
	}
	int sz=sqrt(n)+0.5;
	for(int i=1;i<=n;i++)
		pl[i]=(i-1)/sz+1;
	sort(q+1,q+cur+1);
	int l1=0,l2=0;
	for(int i=1;i<=cur;i++){
		while(l1<q[i].l1)
			update(0,a[++l1],1);
		while(l1>q[i].l1)
			update(0,a[l1--],-1);
		while(l2<q[i].l2)
			update(1,a[++l2],1);
		while(l2>q[i].l2)
			update(1,a[l2--],-1);
		ans[q[i].p]+=now*q[i].sgn;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
}