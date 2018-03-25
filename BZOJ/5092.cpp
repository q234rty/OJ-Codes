//x+(sum^x)=sum+2*(x&(~sum))
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("5092.txt","r",stdin);
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
int a[300002],f[1<<20];
int query(int x,int t){ //f[]<=t
	int ans=0;
	for(int i=19;i>=0;i--)
		if (x>>i&1){
			int qwq=ans|(1<<i);
			if (f[qwq]<=t)
				ans=qwq;
		}
	return ans;
}
int main(){
	init();
	int n=readint();
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=readint()^a[i-1];
		f[a[i]]=min(f[a[i]],i);
	}
	for(int i=0;i<20;i++)
		for(int j=0;j<(1<<20);j++)
			if (!(j>>i&1))
				f[j]=min(f[j],f[j^(1<<i)]);
	for(int i=1;i<=n;i++)
		printf("%d\n",a[i]+2*query(~a[i],i));
}