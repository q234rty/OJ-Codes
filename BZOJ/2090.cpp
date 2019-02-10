#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("2090.txt","r",stdin);
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
inline void tense(int &x,int y){
	if (x<y)
		x=y;
}
struct bit{
	int n;
	int t[maxn];
	void add(int p,int v){
		for(;p<=n;p+=p&-p)
			tense(t[p],v);
	}
	int query(int p){
		int ans=0;
		for(;p;p-=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b1;
struct tib{
	int n;
	int t[maxn];
	void add(int p,int v){
		for(;p;p-=p&-p)
			tense(t[p],v);
	}
	int query(int p){
		int ans=0;
		for(;p<=n;p+=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b2;
int a[maxn],dp[maxn],qwq[maxn];
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
		tense(dp[i],b1.query(a[i]-1)+1);
		tense(dp[i],b2.query(a[i]+1)+1);
		tense(dp[i],qwq[a[i]]+1);
		char now=s[(dp[i]-1)%k+1];
		if (now=='=')
			tense(qwq[a[i]],dp[i]);
		else if (now=='<')
			b1.add(a[i],dp[i]);
		else b2.add(a[i],dp[i]);
		// printf("dp[%d]=%d\n",i,dp[i]);
		tense(ans,dp[i]);
	}
	printf("%d",ans);
}
