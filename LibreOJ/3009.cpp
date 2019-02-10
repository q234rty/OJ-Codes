#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("3009.txt","r",stdin);
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
const int maxn=1000002;
inline void tense(pii &x,pii y){
	if (x<y)
		x=y;
}
struct bit{
	int n;
	pii t[maxn];
	void add(int p,pii v){
		for(;p<=n;p+=p&-p)
			tense(t[p],v);
	}
	pii query(int p){
		pii ans;
		for(;p;p-=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b1;
struct tib{
	int n;
	pii t[maxn];
	void add(int p,pii v){
		for(;p;p-=p&-p)
			tense(t[p],v);
	}
	pii query(int p){
		pii ans;
		for(;p<=n;p+=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b2;
inline pii inc(pii x){
	x.first++;
	return x;
}
int a[maxn],dp[maxn],lst[maxn],stk[maxn];
pii qwq[maxn];
char s[maxn];
int main(){
	init();
	int n=readint(),k=readint();
	for(int i=1;i<=n;i++)
		a[i]=readint();
	for(int i=1;i<=k;i++)
		s[i]=readchar();
	b1.n=b2.n=maxn-1;
	int ans=0;
	for(int i=1;i<=n;i++){
		pii lol;
		tense(lol,inc(b1.query(a[i]-1)));
		tense(lol,inc(b2.query(a[i]+1)));
		tense(lol,inc(qwq[a[i]]));
		dp[i]=lol.first,lst[i]=lol.second;
		// printf("dp[%d]=%d lst[%d]=%d\n",i,dp[i],i,lst[i]);
		lol.second=i;
		char now=s[(dp[i]-1)%k+1];
		if (now=='=')
			tense(qwq[a[i]],lol);
		else if (now=='<')
			b1.add(a[i],lol);
		else b2.add(a[i],lol);
		// printf("dp[%d]=%d lst[%d]=%d\n",i,dp[i],i,lst[i]);
		if (dp[i]>dp[ans])
			ans=i;
	}
	printf("%d\n",dp[ans]);
	int cur=0;
	while(ans){
		stk[++cur]=ans;
		ans=lst[ans];
	}
	for(int i=cur;i;i--)
		printf("%d ",a[stk[i]]);
}
