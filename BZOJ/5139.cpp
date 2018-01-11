#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
    #ifdef LOCAL
        freopen("5139.txt","r",stdin);
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
int n;
int a[100003],cnt[100003];
bool check(int x){
    for(int i=0;i<=n;i++)
        cnt[i]=0;
    for(int i=1;i<x;i++)
        cnt[a[i]]++;
    int sum=0;
    for(int i=0;i<=n;i++){
        if (cnt[i] && sum+n-x<i)
            return false;
        sum+=cnt[i];
    }
    return true;
}
int main(){
    init();
    n=readint();
    for(int i=1;i<=n;i++)
        a[i]=readint();
    int l=1,r=n;
    while(l<r){
        int mid=(l+r+1)/2;
        if (check(mid))
            l=mid;
        else r=mid-1;
    }
    printf("%d",n-l);
}