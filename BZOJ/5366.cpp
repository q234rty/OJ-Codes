#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("5366.txt","r",stdin);
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
ll c3(ll n){
	return n*(n-1)*(n-2);
}
struct qwq{
	int t[1002][1002];
	void init(){
		memset(t,0,sizeof(t));
	}
	void add(int x1,int y1,int x2,int y2,int v){
		if (x1>x2 || y1>y2)
			return;
		t[x1][y1]+=v;
		t[x1][y2+1]-=v;
		t[x2+1][y1]-=v;
		t[x2+1][y2+1]+=v;
	}
	void get(){
		for(int i=1;i<=1000;i++)
			for(int j=1;j<=1000;j++)
				t[i][j]+=t[i-1][j]+t[i][j-1]-t[i-1][j-1];
	}
	int * operator [](int x){
		return t[x];
	}
}a,b,c,d;
int main(){
	init();
	int T=readint();
	while(T--){
		int n=readint();
		a.init(),b.init(),c.init(),d.init();
		while(n--){
			int x1=readint(),y1=readint(),x2=readint(),y2=readint();
			a.add(x1,y1,x2,y2,1);
			b.add(x1+1,y1,x2,y2,1);
			c.add(x1,y1+1,x2,y2,1);
			d.add(x1+1,y1+1,x2,y2,1);
		}
		a.get(),b.get(),c.get(),d.get();
		ll ans=0;
		for(int i=1;i<=1000;i++)
			for(int j=1;j<=1000;j++)
				ans+=c3(a[i][j])-c3(b[i][j])-c3(c[i][j])+c3(d[i][j]);
		printf("%lld\n",ans/6);
	}
}