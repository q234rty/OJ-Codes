#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=30000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
    #ifdef LOCAL
        freopen("2127.txt","r",stdin);
    #endif
    buf[fread(buf,1,MAXSIZE,stdin)]=' ';
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
long double p[1<<20];
char s[101];
int main(){
    init();
    int n=readint();
    for(int i=0;i<(1<<n);i++){
        readstr(s);
        p[i]=strtod(s,0);
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<(1<<n);j++)
            if (j>>i&1)
                p[j]+=p[j^(1<<i)];
    long double ans=0;
    for(int i=1;i<(1<<n);i++){
        long double t=1-p[(1<<n)-1-i];
        if (t<1e-11)
            return puts("INF"),0;
        t=1/t;
        if (__builtin_parity(i))
            ans+=t;
        else ans-=t;
    }
    printf("%.10Lf",ans);
}