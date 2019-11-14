#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define     pb      push_back
#define     f       first
#define     s       second    
#define     all(a)  a.begin(),a.end()
#define     present(container, element) (container.find(element) != container.end()) //for set and map
#define     cpresent(container, element) (find(all(container),element) != container.end()) //for vectors
#define     len(container) ll(container.length())
map < pair<string,string>,string> M;
vector<string>terminals = {"id","+","*","(",")","$"};
void initialize_parse_table()
{
	pair<string,string>p;

	/*First Row*/
	p.f = "E";
	p.s = "id";
	M[p] = "TE'";
	p.s = "(";
	M[p] = "TE'";

	/*Second Row*/
	p.f = "E'";
	p.s = "+";
	M[p] = "+TE'";
	p.s = ")";
	M[p] = "";
	p.s = "$";
	M[p] = "";

	/*Third Row*/
	p.f = "T";
	p.s = "id";
	M[p] = "FT'";
	p.s = "(";
	M[p] = "FT'";

	/*Fourth Row*/
	p.f = "T'";
	p.s = "+";
	M[p] = "";
	p.s = "*";
	M[p] = "*FT'";
	p.s = ")";
	M[p] = "";
	p.s = "$";
	M[p] = "";

	/*Fifth Row*/
	p.f = "F";
	p.s = "id";
	M[p] = "id";
	p.s = "(";
	M[p] = "(E)";
}
vector<string> convert_string_to_list(string s)
{
	int n = len(s);
	vector<string>v;
	//cout<<s<<endl;
	for (int i = 0; i < n;)
	{
		/* code */
		if(s[i]=='i')
			v.pb("id");
		else if(s[i]=='*')
			v.pb("*");
		else if(s[i] == '+')
			v.pb("+");
		else if(s[i] == '(')
			v.pb("(");
		else if(s[i] == ')')
			v.pb(")");
		else if(s[i] == '$')
			v.pb("$");
		else if(s.substr(i,2)=="E'")
			v.pb("E'");
		else if(s.substr(i,2)=="T'")
			v.pb("T'");
		else if(s[i]=='T')
			v.pb("T");
		else if(s[i]=='E')
			v.pb("E");
		else if(s[i]=='F')
			v.pb("F");
		i++;
	}
	return v;
}
void parse(vector<string>v)
{
	stack<string>st;
	st.push("$");
	st.push("E");
	auto it = v.begin();
	string a = *it;
	string X = st.top();
	while(X!="$")
	{
		if(X == a)
		{
			cout<<"Matched "<<X<<" with "<<a<<endl;
			st.pop(),a = *(++it);
		}
		else if(cpresent(terminals,X))
		{
			cout<<"Stack top : "<<X<<endl;
			cout<<"Current Input Symbol : "<<a<<endl;
			cout<<"Error\n";return;
		}
		else if(!present(M,make_pair(X,a)))
		{
			cout<<"Stack top : "<<X<<endl;
			cout<<"Current Input Symbol : "<<a<<endl;
			cout<<"Error\n";return;
		}
		else
		{
			string prod = M[{X,a}];
			if(prod=="")
				cout<<X<<" --> "<<"epsilon"<<endl;
			else
				cout<<X<<" --> "<<prod<<endl;
			st.pop();
			vector<string>temp = convert_string_to_list(prod);
			reverse(all(temp));
			for(auto nt : temp)
				st.push(nt);
		}
		X = st.top();
	}
	cout<<"Parsing successfully completed"<<endl;
}
int main(int argc, char const *argv[])
{	
	initialize_parse_table();
	string s;
	getline(cin,s);
	s += "$";
	vector<string>v = convert_string_to_list(s);
	parse(v);
	return 0;
}
