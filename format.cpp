// Author -- xyr2005

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;
using std::min;
using std::max;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>inline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>inline void read(_Tp &x)
{
	char ch(getchar());bool f(false);while(!isdigit(ch)) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch)) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	f&&(x=-x);
}
template <typename _Tp,typename... Args>inline void read(_Tp &t,Args &...args){read(t);read(args...);}
inline int read_str(char *s)
{
	char ch(getchar());while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;*tar=ch,ch=getchar();while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *(++tar)=ch,ch=getchar();
	return tar-s+1;
}

const int N=1000005;
const std::string dic[]={"vector","map","bitset","set","unordered_map","unordered_set","array","priority_queue","queue","stack","deque","list","pair","tuple","template"};
const std::string DIC[]={"bool","char","unsigned char","short","unsigned short","int","unsigned int","long long","unsigned long long","__int128","ll","uint","ull","_Tp","Args"};
bool mark[N];
char in_file[105];
int main(int argc,char **args)
{
	assert(argc==2);
	sprintf(in_file,"%s",args[1]);
	std::string c="clang-format ";
	int len=strlen(in_file);for(int i=0;i<len;++i) c.pb(in_file[i]);
	c+=" > ";
	std::string name=".format_";
	for(int i=0;i<16;++i)
	{
		int opt=rnd()%3;
		if(opt==0) name.pb(rnd()%10+48);
		else if(opt==1) name.pb(rnd()%26+65);
		else name.pb(rnd()%26+97);
	}
	name+=".tmp";
	c+=name;
	system(c.c_str());
	freopen(name.c_str(),"r",stdin);
	std::string s;
	while(std::getline(std::cin,s))
	{
		assert(SZ(s)<N);
		memset(mark,0,SZ(s));
		int pos=SZ(s);
		auto push=[&](int x){if(x>=0&&x<pos&&s[x]==' ') mark[x]=true;};
		for(int i=0;i+1<SZ(s);++i)
		{
			if(s[i]=='/'&&s[i+1]=='/')
			{
				pos=i;
				break;
			}
		}
		bool tag=false;
		for(int i=0;i+1<pos;++i)
		{
			tag^=s[i]=='"';
			if(tag) continue;
			if(s[i]==','||s[i]==';'||s[i]==':')
			{
				push(i-1);
				push(i+1);
			}
		}
		tag=false;
		for(int i=0;i<pos;++i)
		{
			tag^=s[i]=='"';
			if(tag) continue;
			if(i<pos&&s.substr(i,2)==" )") mark[i]=true;
			if(s[i]=='=')
			{
				if(s[i-1]==' ') mark[i-1]=true;
				if(s[i+1]==' ') mark[i+1]=true;
			}
		}
		tag=false;
		for(int i=0;i<pos;++i)
		{
			tag^=s[i]=='"';
			if(tag) continue;
			if(s[i]=='?'||s[i]=='|'||s[i]=='&'||s[i]=='!'||s[i]=='^'||s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='%'||s[i]=='<'||s[i]=='>'||s[i]=='{'||s[i]=='}'||s[i]=='['||s[i]==']'||s[i]=='(') push(i-1),push(i+1);
		}
		tag=false;
		for(int i=0;i+1<pos;++i)
		{
			tag^=s[i]=='"';
			if(tag) continue;
			std::string t(s.substr(i,2));
			if(t=="<="||t==">="||t=="=="||t=="<<"||t==">>"||t=="++"||t=="--"||t=="||"||t=="&&") push(i-1),push(i+2);
		}
		for(auto it:dic)
		{
			for(int i=0;i+SZ(it)<=pos;++i)
			{
				if(s.substr(i,SZ(it))==it)
				{
					for(int j=i+SZ(it);j<pos;++j)
					{
						if(s[j]=='>') mark[j+1]=false;
					}
				}
			}
		}
		
		for(auto it:DIC)
		{
			for(int i=0;i+SZ(it)<=pos;++i)
			{
				if(s.substr(i,SZ(it))==it)
				{
					mark[i+SZ(it)]=false;
				}
			}
		}
		for(int i=0;i<SZ(s);++i) if(!mark[i]) putchar(s[i]);
		putchar('\n');
	}
	fclose(stdin),fclose(stdout);
	c="rm ";
	c+=name;
	system(c.c_str());
	return 0;
}

