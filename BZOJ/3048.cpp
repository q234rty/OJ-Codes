#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
const int maxn=100001;
struct segtree{
	int sumv[maxn*4];
	int n;
	int kth(int k){
		int o=1,l=1,r=n;
		while(l<r){
			int mid=(l+r)/2;
			if(k<=sumv[o*2])
				o*=2,r=mid;
			else k-=sumv[o*2],o=o*2+1,l=mid+1;
		}
		return l;
	}
	int ql,qr;
	int query(int o,int l,int r){
        	if (ql<=l && qr>=r)
            		return sumv[o];
        	int mid=(l+r)/2;
        	int ans=0;
        	if (ql<=mid)
            		ans+=query(o*2,l,mid);
        	if (qr>mid)
            		ans+=query(o*2+1,mid+1,r);
        	return ans;
	}
	int rank(int x){
        	ql=1,qr=x;
        	return query(1,1,n);
	}
	int p,v;
	void add(int o,int l,int r){
		if (l==r){
			sumv[o]+=v;
			return;
		}
		int mid=(l+r)/2;
		if (p<=mid)
			add(o*2,l,mid);
		else add(o*2+1,mid+1,r);
		sumv[o]+=v;
	}
	void add(int p,int v){
		this->p=p;
		this->v=v;
		add(1,1,n);
	}
}t;
int a[maxn],lst[maxn],nxt[maxn];
int now[maxn];
int nums[maxn],cur;
pair<int,int> x[maxn];
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    k++;
    t.n=n;
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),nums[i]=a[i];
    cur=n;
    sort(nums+1,nums+cur+1);
    cur=unique(nums+1,nums+cur+1)-nums-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(nums+1,nums+cur+1,a[i])-nums;
    for(int i=1;i<=n;i++)
        x[i].first=a[i],x[i].second=i;
    sort(x+1,x+n+1);
    for(int i=1;i<=n;i++){
        lst[i]=now[a[i]];
        nxt[now[a[i]]]=i;
        now[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
        if (!nxt[i]){
            //printf("%d\n",i);
            t.add(i,1);
        }
    int ans=0;
    for(int i=n;i>=1;i--){
        int q=t.rank(i),y=q>k?t.kth(q-k):0;
        int r=upper_bound(x+1,x+n+1,make_pair(a[i],i))-x-1,l=upper_bound(x+1,x+n+1,make_pair(a[i],y))-x-1;
        //printf("i=%d q=%d y=%d l=%d r=%d\n",i,q,y,l,r);
        ans=max(ans,r-l);
        if (lst[i])
            t.add(lst[i],1);
    }
    printf("%d",ans);
}
