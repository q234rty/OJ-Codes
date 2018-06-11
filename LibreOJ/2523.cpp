#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=20000020;
const int mod=1000000007;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("2532.txt","r",stdin);
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
int d[2002];
ll cnt[2002];
int pw[1000002];
int main(){
	init();
	int n=readint(),q=readint(),p=readint(),cur=0;
	for(int i=1;i*i<=p;i++)
		if (p%i==0){
			d[++cur]=i;
			if (i*i!=p)
				d[++cur]=p/i;
		}
	sort(d+1,d+cur+1);
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=pw[i-1]*2;
		if (pw[i]>=mod)
			pw[i]-=mod;
	}
	while(n--)
		cnt[lower_bound(d+1,d+cur+1,__gcd(readint(),p))-d]++;
	for(int i=1;i<=cur;i++)
		for(int j=i+1;j<=cur;j++)
			if (d[j]%d[i]==0)
				cnt[i]+=cnt[j];
	for(int i=1;i<=cur;i++)
		cnt[i]=pw[cnt[i]]-1;
	for(int i=cur;i;i--){
		for(int j=i+1;j<=cur;j++)
			if (d[j]%d[i]==0)
				cnt[i]-=cnt[j];
		cnt[i]%=mod;
	}
	for(int i=cur;i;i--){
		for(int j=1;j<i;j++)
			if (d[i]%d[j]==0)
				cnt[i]+=cnt[j];
		cnt[i]=(cnt[i]%mod+mod)%mod;
	}
	while(q--)
		printf("%lld\n",cnt[lower_bound(d+1,d+cur+1,__gcd(readint(),p))-d]);
}