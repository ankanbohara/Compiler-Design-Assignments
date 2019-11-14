#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define     pb      push_back
#define     f       first
#define     s       second    
#define     all(a)  a.begin(),a.end()
#define     present(container, element) (container.find(element) != container.end()) //for set and map
#define     cpresent(container, element) (find(all(container),element) != container.end()) //for vectors
#define     len(container) ll(container.length())
/*Rules :
1. E --> E + T
2. E --> T
3. T --> T * F
4. T --> F
5. F --> (E)
6. F -->id
*/
vector<string> convert_string_to_list(string s)
{
	int n = len(s);
	vector<string>v;
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
class BottomUpParsing
{
	map < pair<int,string>,string> M;
	vector<string>terminals = {"id","+","*","(",")","$"};
	vector<string>non_terminals = {"E","T","F"};
	vector< pair<string,string> >rules = {{"E","E+T"},{"E","T"},{"T","T*F"},{"T","F"},{"F","(E)"},{"F","id"}};
	public:
		void initialize_parse_table()
		{
			pair<int,string>p;

			/*First Row of the table*/
			p.f = 0;
			p.s = "id";M[p] = "s5";
			p.s = "(";M[p] = "s4";
			p.s = "E";M[p] = "1";
			p.s = "T";M[p] = "2";
			p.s = "F";M[p] = "3";

			/*Second Row of the table*/
			p.f = 1;
			p.s = "+";M[p] = "s6";
			p.s = "$";M[p] = "accept";

			/*Third Row of the table*/
			p.f = 2;
			p.s = "+";M[p] = "r2";
			p.s = "*";M[p] = "s7";
			p.s = ")";M[p] = "r2";
			p.s = "$";M[p] = "r2";

			/*Fourth Row of the table*/
			p.f = 3;
			p.s = "+";M[p] = "r4";
			p.s = "*";M[p] = "r4";
			p.s = ")";M[p] = "r4";
			p.s = "$";M[p] = "r4";

			/*Fifth Row of the table*/
			p.f = 4;
			p.s = "id";M[p] = "s5";
			p.s = "(";M[p] = "s4";
			p.s = "E";M[p] = "8";
			p.s = "T";M[p] = "2";
			p.s = "F";M[p] = "3";

			/*Fifth row of the table*/
			p.f = 5;
			p.s = "+";M[p] = "r6";
			p.s = "*";M[p] = "r6";
			p.s = ")";M[p] = "r6";
			p.s = "$";M[p] = "r6";

			/*Sixth row of the table*/
			p.f = 6;
			p.s = "id";M[p] = "s5";
			p.s = "(";M[p] = "s4";
			p.s = "T";M[p] = "9";
			p.s = "F";M[p] = "3";

			/*Seventh row of the table*/
			p.f = 7;
			p.s = "id";M[p] = "s5";
			p.s = "(";M[p] = "s4";
			p.s = "F";M[p] = "10";

			/*Eighth row of the table*/
			p.f = 8;
			p.s = "+";M[p] = "s6";
			p.s = ")";M[p] = "s11";

			/*Nineth row of the table*/
			p.f = 9;
			p.s = "+";M[p] = "r1";
			p.s = "*";M[p] = "s7";
			p.s = ")";M[p] = "r1";
			p.s = "$";M[p] = "r1";

			/*Tenth row of the table*/
			p.f = 10;
			p.s = "+";M[p] = "r3";
			p.s = "*";M[p] = "r3";
			p.s = ")";M[p] = "r3";
			p.s = "$";M[p] = "r3";


			/*Eleventh row of the table*/
			p.f = 11;
			p.s = "+";M[p] = "r5";
			p.s = "*";M[p] = "r5";
			p.s = ")";M[p] = "r5";
			p.s = "$";M[p] = "r5";
		}
		void parse(vector<string>v)
		{
			stack<int>st;
			st.push(0);
			int ip = 0;
			string a = v[ip];
			while(1)
			{
				int s = st.top();
				pair<int,string>p = {s,a};
				if(present(M,p))
				{
					string action = M[p];
					if(action[0]=='s')
					{
						string t = action.substr(action.find('s')+1);
						st.push(stoi(t));
						a = v[++ip];	
					}
					else if(action[0]=='r')
					{
						int rule_no = stoi(action.substr(action.find('r')+1));
						string rule_antecedent = rules[rule_no-1].f;
						vector<string>rule_consequent = convert_string_to_list(rules[rule_no-1].s);
						int pop_cnt = rule_consequent.size();
						while(pop_cnt--)
						{
							st.pop();
						}
						st.push(stoi(M[{st.top(),rule_antecedent}]));
						cout<<rule_antecedent<<"-->"<<rules[rule_no-1].s<<endl;
					}
					else if(action[0]=='a')
					{
						cout<<"Parsing successfully completed\n";
						return;
					}
				}
				else
				{
					cout<<p.f<<" "<<p.s<<endl;
					while(!st.empty())
					{
						cout<<st.top()<<endl;
						st.pop();
					}
					cout<<"Error occurred in parsing";
					return;
				}
			}
		}

};
int main(int argc, char const *argv[])
{	
	BottomUpParsing bp;
	bp.initialize_parse_table();
	string s;
	getline(cin,s);
	s += "$";
	vector<string>v = convert_string_to_list(s);
	bp.parse(v);
	return 0;
}
