#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("891A.txt","r",stdin);
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
int a[2003];
int main(){
	init();
	int n=readint(),ans=n+1;
	// puts("WTF");
	for(int i=1;i<=n;i++){
		a[i]=readint();
		int now=0;
		for(int j=i;j;j--){
			now=__gcd(now,a[j]);
			if (now==1){
				ans=min(ans,i-j+1);
				break;
			}
		}
	}
	// puts("WTF");
	if (ans>n)
		return puts("-1"),0;
	if (ans==1){
		int qwq=n;
		for(int i=1;i<=n;i++)
			qwq-=(a[i]==1);
		printf("%d\n",qwq);
		return 0;
	}
	printf("%d",ans-1+n-1);
}