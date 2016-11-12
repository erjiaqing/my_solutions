#include <bits/stdc++.h>
using namespace std;

namespace uoj_0098{

struct element{
	int type, val;
	string name;
};

struct line{
	int type, end;
	string s, for_1, for_2, for_3;
	vector<element> sc, for_1c, for_2c, for_3c;
};

struct function{
	string name;
	vector<string> arguments;
	vector<line> body;
};

struct variable{
	int val, type;
	vector<int> dimension;
};

struct procedure_exit{
	int status, val;
	procedure_exit(){}
	procedure_exit(int _s, int _v):
		status(_s), val(_v){}
};

int memory[1 << 22], alloc_top;
queue<int> inputbuf;
vector<function> functions;
map<string, variable> variable_table;
map<string, int> function_table;

int get_val(const element &e)
{
	if (e.type == 3) return e.val; // immediate
	return memory[e.val]; // pointer
}

bool valid_char(char c)
{
	if ('a' <= c && c <= 'z') return true;
	if ('A' <= c && c <= 'Z') return true;
	if ('0' <= c && c <= '9') return true;
	if (c == '_') return true;
	return false;
}

bool valid_char2(char c)
{
	return valid_char(c) || (c == '#' || c == ':' || c == '.');
}

bool blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == 0);
}

int operators(const string &op)
{
	if (op == ".!") return 5; //unary op !
	if (op == ".+") return 6; //unary op +
	if (op == ".-") return 7; //unary op -
	if (op == "@") return 20; // function call
	if (op == "*") return 31; // mul
	if (op == "/") return 32; // div
	if (op == "%") return 33; // mod
	if (op == "+") return 41; // add
	if (op == "-") return 42; // minus
	if (op == "<=") return 51; // leq
	if (op == ">=") return 52; // geq
	if (op == "<") return 53; // less
	if (op == ">") return 54; // great
	if (op == "==") return 60; // eq
	if (op == "!=") return 61; // neq
	if (op == "^") return 70; // logic xor
	if (op == "&&") return 80; // logic and
	if (op == "||") return 90; // logic or
	if (op == "=") return 105; // assign
	if (op == ",") return 120; // split
	if (op == "<<") return 130; // output
	if (op == ">>") return 131; // input
	if (op == "(") return 160; // left
	return 0;
}

int operator2(const string s)
{
	//if (op == "=") return 110;
	return operators(s) + 5;
}

int call_function(string name, vector<int> arguments, int assignmemory, map<string, variable> vars);
procedure_exit call_procedure(const vector<line> &body, int begin_line, int end_line, int assignmemory, map<string, variable> vars);
void assign_memory(string s, int &assignmemory, map<string, variable> &vars);
void process_declare(string s, int &assignmemory, map<string, variable> &vars);

// Simulator

int eval_operator(const element &a, const element &b, const element &_op)
{
	int op = _op.val;
	if (op == 5) return get_val(a) == 0;
	if (op == 6) return get_val(a);
	if (op == 7) return -get_val(a);
	if (op == 31) return get_val(a) * get_val(b);
	if (op == 32) return get_val(a) / get_val(b);
	if (op == 33) return get_val(a) % get_val(b);
	if (op == 41) return get_val(a) + get_val(b);
	if (op == 42) return get_val(a) - get_val(b);
	if (op == 51) return get_val(a) <= get_val(b);
	if (op == 52) return get_val(a) >= get_val(b);
	if (op == 53) return get_val(a) < get_val(b);
	if (op == 54) return get_val(a) > get_val(b);
	if (op == 60) return get_val(a) == get_val(b);
	if (op == 61) return get_val(a) != get_val(b);
	if (op == 70) return (!!get_val(a)) ^ (!!get_val(b));
	if (op == 80) return get_val(a) && get_val(b);
	if (op == 90) return get_val(a) || get_val(b);
	if (op == 105) return memory[a.val] = get_val(b);
	if (op == 130)
	{
		if (b.name == "endl") cout << endl;
		else cout << get_val(b);
		return 0;
	}
	if (op == 131)
	{
		memory[b.val] = inputbuf.front();
		inputbuf.pop();
		return 0;
	}
	return 0;
}

element array_to_variable(const string name, const vector<int> arg, map<string, variable> vars)
{
	variable var = vars[name];
	int cur = arg[0];
	for (int i = 1; i < (int)arg.size(); i++)
	{
		cur *= var.dimension[i];
		cur += arg[i];
	}
	element ele;
	ele.type = 0;
	ele.val = var.val + cur;
	return ele;
}

int evaluate_statement(vector<element> statement, int assignmemory, map<string, variable> vars/*, string note = "", bool flg = false*/)
{
	stack<element> sta;
//	if (flg)
//		cout << "Now " << note << endl;
	for (element e : statement)
	{
		if (e.type == 4) // operators
		{
			if (e.val == 20) // call function
			{
				element rval = sta.top();sta.pop();
				if (rval.name == "putchar")
				{
					element lval = sta.top();
					cout << char(get_val(lval));
				} else
				{
					auto _ = function_table.find(rval.name);
					if (_ == function_table.end()) // array
					{
						variable var = variable_table[rval.name];
						vector<int> arg;
						int dim = var.dimension.size();
						for (int i = 0; i < dim; i++)
						{
							arg.push_back(get_val(sta.top()));
							sta.pop();
						}
						for (int i = 0, j = dim - 1; i < j; i++, j--)
							swap(arg[i], arg[j]);
						sta.push(array_to_variable(rval.name, arg, vars));
					} else
					{
						element res;
						vector<int> arg;
						int argc = functions[_->second].arguments.size();
						for (int i = 0; i < argc; i++)
						{
							arg.push_back(get_val(sta.top()));
							sta.pop();
						}
						for (int i = 0, j = argc - 1; i < j; i++, j--)
							swap(arg[i], arg[j]);
						res.type = 3; // immidate
						res.val = call_function(rval.name, arg, assignmemory, vars);
						sta.push(res);
					}
				}
			} else if (e.val == 120)
			{
				continue;
			} else if (e.val < 10)
			{
				element rval = sta.top();sta.pop();
				element res;
				res.type = 3;
				res.val = eval_operator(rval, rval, e);
				sta.push(res);
			} else
			{
				element rval = sta.top();sta.pop();
				element lval = sta.top();sta.pop();
				element res;
				res.type = 3;
				res.val = eval_operator(lval, rval, e);
				sta.push(res);
			}
		} else
		{
			if (e.type != 2) sta.push(e);
			else
			{
				if (function_table.find(e.name) == function_table.end()) // variables or array
				{
					e.val = vars.find(e.name)->second.val;
					e.type = 0; // variable
	//				cerr << "get val " << e.name << " @ " << e.val << endl;
				}
				sta.push(e);
			}
		}
	}
	return get_val(sta.top());
}

procedure_exit run_procedure(const vector<line> &body, int begin_line, int end_line, int assignmemory, map<string, variable> vars)
{
	int if_true;
	for (int i = begin_line; i <= end_line; i++)
	{
//		cerr << "Current: Line " << i << " : " << body[i].s << endl;
		if (body[i].type == 0 || body[i].type == -3)
		{
			int ret = evaluate_statement(body[i].sc, assignmemory, vars);
			if (body[i].type == -3)
				return procedure_exit(1, ret);
		}
		else if (body[i].type == -1) // begin
		{
			auto res = run_procedure(body, i + 1, body[i].end, assignmemory, vars);
			if (res.status)
				return res;
			i = body[i].end;
		} else if (body[i].type == -2) // end
			continue;
		else if (body[i].type == -4) // declare
		{
			process_declare(body[i].s, assignmemory, vars);
		} else if (body[i].type == 1) // for
		{
			int cmem = assignmemory;
			auto cvar = vars;
			// s1
			if (body[i].for_1.substr(0, 4) == "int ")
				process_declare(body[i].for_1.substr(4), cmem, cvar);
			else if (body[i].for_1c.size())
				evaluate_statement(body[i].for_1c, cmem, cvar);
			// s2
			for (; body[i].for_2c.size() == 0 ||
					evaluate_statement(body[i].for_2c, cmem, cvar); )
			{
				auto res = run_procedure(body, i + 1, body[i].end, cmem, cvar);
				if (res.status)
					return res;
				if (body[i].for_3.substr(0, 4) != "int " && body[i].for_3c.size())
					evaluate_statement(body[i].for_3c, cmem, cvar);
//				cerr << memory[101] << endl;
				// No for_3c for for_3c should be appended to for_2c
			}
			i = body[i].end;
		} else if (body[i].type == 2) // if
		{
			if (evaluate_statement(body[i].sc, assignmemory, vars))
			{
				if_true = 1;
				auto res = run_procedure(body, i + 1, body[i].end, assignmemory, vars);
				if (res.status)
					return res;
			} else {
				if_true = 0;
			}
			i = body[i].end;
		} else if (body[i].type == 3) // else
		{
			if (if_true == 0)
			{
				auto res = run_procedure(body, i + 1, body[i].end, assignmemory, vars);
				if (res.status)
					return res;
			}
			i = body[i].end;
		}
	}
	return procedure_exit(0, 0);
}

int call_function(string func, vector<int> args, int assignmemory, map<string, variable> vars)
{
//	cerr << "Current: Func " << func << endl;
	auto f = functions[function_table[func]];
	for (int i = 0; i < (int) f.arguments.size(); i++)
	{
		variable tvar;
		tvar.type = 2;
		tvar.val = assignmemory++;
		vars[f.arguments[i]] = tvar;
		memory[tvar.val] = args[i];
	}
	auto ret = run_procedure(f.body, 0, f.body.size() - 1, assignmemory, vars);
	return ret.val;
}

// Precompile
void process(string s, vector<line> &sp)
{
	string buf;
	for (int i = 0; i < (int)s.size();)
	{
		buf = "";
		line tins;
		tins.type = 0;
		if (blank(s[i]))
		{
			i++;
			continue;
		} else if (s[i] == '{')
		{
			buf += s[i];
			tins.type = -1;
			tins.s = buf;
			sp.push_back(tins);
			i++;
		} else if (s[i] == '}')
		{
			buf += s[i];
			tins.type = -2;
			tins.s = buf;
			sp.push_back(tins);
			i++;
		} else if (s.substr(i, 3) == "for" && (!valid_char(s[i + 3])))
		{
			tins.type = 1; // for
			int ti = i, te = i, cc = 0;
			while (s[ti] != '(') ti++;
//			ti++;
			te = ti + 1;
			cc = 1;
			while (cc)
			{
				if (s[te] == '(') cc++;
				else if (s[te] == ')') cc--;
				te++;
			}
			ti++;te--;
			while (s[ti] != ';')
				tins.for_1 += s[ti++];
			ti++;
			while (s[ti] != ';')
				tins.for_2 += s[ti++];
			ti++;
			while (ti < te)
				tins.for_3 += s[ti++];
			sp.push_back(tins);
			i = te + 1;
		} else if (s.substr(i, 2) == "if" && (!valid_char(s[i + 2])))
		{
			tins.type = 2; // else
			int ti = i, cc = 0;
			while (s[ti] != '(') ti++;
			ti++;
			cc = 1;
			tins.s = "(";
			while (cc)
			{
				tins.s += s[ti];
				if (s[ti] == '(') cc++;
				else if (s[ti] == ')') cc--;
				ti++;
			}
			i = ti;
			sp.push_back(tins);
		} else if (s.substr(i, 4) == "else" && (!valid_char(s[i + 4])))
		{
			tins.s = "else";
			tins.type = 3;
			i = i + 4;
			sp.push_back(tins);
		} else if (s.substr(i, 5) == "while" && (!valid_char(s[i + 5])))
		{
			tins.type = 1;
			int ti = i, cc = 0;
			while (s[ti] != '(') ti++;
			tins.for_2 = "(";
			ti++;
			cc = 1;
			while (cc)
			{
				tins.for_2 += s[ti];
				if (s[ti] == '(') cc++;
				else if (s[ti] == ')') cc--;
				ti++;
			}
			sp.push_back(tins);
			i = ti;
		} else if (s.substr(i, 6) == "return" && (!valid_char(s[i + 6])))
		{
			tins.type = -3;
			i += 6;
			while (s[i] != ';')
				tins.s += s[i++];
			i++;
			sp.push_back(tins);
		} else if (s.substr(i, 3) == "int" && (!valid_char(s[i + 3])))
		{
			tins.type = -4;
			i += 3;
			while (!valid_char(s[i])) i++;
			while (s[i] != ';')
				tins.s += s[i++];
			i++;
			sp.push_back(tins);
		} else
		{
			tins.type = 0;
			while (s[i] != ';')
				tins.s += s[i++];
			i++;
			sp.push_back(tins);
		}
	}
}

void process_declare_core(string s, int &alloc_ptr, map<string, variable> &var)
{
	string name = "";
	variable v;
	int i = 0;
	for (; !valid_char(s[i]); i++);
	for (; valid_char(s[i]); i++) name += s[i];
	int sz = 1;
	for (; i < (int) s.size();)
	{
		if ('0' <= s[i] && s[i] <= '9')
		{
			int cur = 0;
			while ('0' <= s[i] && s[i] <= '9')
			{
				cur *= 10;
				cur += s[i] - '0';
				i++;
			}
			sz *= cur;
			v.dimension.push_back(cur);
		} else {
			i++;
		}
	}
	v.type = 2;
	v.val = alloc_ptr;
	var[name] = v;
//	cerr << "Dim " << name << " @ " << alloc_ptr << " size " << sz << endl;
	memset(memory + alloc_ptr, 0, sizeof(int) * sz);
	alloc_ptr += sz;
}

void process_declare(string s, int &alloc_ptr, map<string, variable> &var)
{
	for (int i = 0; i < (int) s.size();)
	{
		if (blank(s[i]))
		{
			i++;
			continue;
		}
		string tmp;
		while (s[i] != ',' && s[i] != ';' && i < (int) s.size())
		{
			tmp += s[i];
			i++;
		}
		process_declare_core(tmp, alloc_ptr, var);
		i++;
	}
}

int process_range(vector<line> &f, int beg, int flg)
{
	for (int i = beg; i < (int) f.size(); i++)
	{
		if (f[i].type <= 0 && f[i].s[0] != '{')
		{
			if (flg) return i;
			else continue;
		}
		else if (f[i].s[0] == '{')
		{
			int cc = 1, j;
			for (j = i + 1; cc; j++)
			{
				if (f[j].s[0] == '{') cc++;
				else if (f[j].s[0] == '}') cc--;
			}
			f[i].end = j - 1;
			if (flg) return f[i].end;
		} else
		{
			f[i].end = process_range(f, i + 1, 1);
			if (flg) return f[i].end;
		}
	}
	return 0;
}

void process_function(string s)
{
	string buf = "";
	for (int i = 0; i < (int) s.size(); )
	{
		if (blank(s[i]))
		{
			i++;
			continue;
		}
		i += 4; // "int "
		function tfun;
		string func_head, func_body;
		while (s[i - 1] != ')' && s[i - 1] != ';')
			func_head += s[i++];
		if (s[i - 1] == ';') // variable
		{
			process_declare(func_head, alloc_top, variable_table);
			continue;
		}
		int _j = 0;
		while (blank(func_head[_j])) _j++;
		for (; _j < (int) func_head.size(); _j++)
		{
			if (func_head[_j] == '(' || blank(func_head[_j])) break;
			tfun.name += func_head[_j];
		}
		_j++;
		for (; _j < (int) func_head.size(); )
		{
//			int &ti = _j;
			if (!valid_char(func_head[_j]))
			{
				_j++;
				continue;
			} else {
				_j = _j + 4;
				while (blank(func_head[_j])) _j++;
				string tmp;
				while (valid_char(func_head[_j]))
					tmp += func_head[_j++];
				tfun.arguments.push_back(tmp);
			}
		}
		int cc = 0;
		while (s[i] != '{') i++;
		i++;cc = 1;
		func_body = "{";
		while (cc)
		{
			if (s[i] == '{') cc++;
			else if (s[i] == '}') cc--;
			func_body += s[i++];
		}
		process(func_body, tfun.body);
		function_table[tfun.name] = functions.size();
		functions.push_back(tfun);
	}
}

string pre_compiler1(string s)
{
	// Trim
	string ts = "";
	for (int i = 0; i < (int)s.size(); i++)
	{
		if (!blank(s[i])) ts += s[i];
		else
		{
			if (ts.size() == 0) continue;
			if (valid_char(ts[ts.size() - 1]) && valid_char(s[i + 1]))
				ts += " ";
		}
	}
	s = ts;
	ts = "";
	for (int i = 0; s[i]; i++)
	{
		if (s.substr(i, 2) == "][")
		{
			ts += ",";
			i++;
		}
		else if (s[i] == '[') ts += "(";
		else if (s[i] == ']') ts += ")";
		else
			ts += s[i];
	}
	return ts;
}

string pre_compiler2(string s)
{
	string ts = "", last_name = "";
	for (int i = 0; s[i]; i++)
	{
		last_name = "";
		if (valid_char(s[i]))
		{
			while (valid_char(s[i])) last_name += s[i++];
			if (s[i] == '(')
			{
				int cc = 1;
				int ri = i + 1;
				while (cc)
				{
					if (s[ri] == ')') cc--;
					else if (s[ri] == '(') cc++;
					ri++;
				}
				ts += "(" + pre_compiler2(s.substr(i + 1, ri - i - 2)) + ")@" + last_name;
				i = ri;
			} else {
				ts += last_name;
			}
			i--;
		} else
			ts += s[i];
	}
	return ts;
}

string pre_compile(string s)
{
	return pre_compiler2(pre_compiler1(s));
}

// Compiler
void compile(vector<element> &compiled, string s)
{
	stack<string> oper;
	int last = 0;
	for (int i = 0; i < (int)s.size(); i++)
	{
		if ('0' <= s[i] && s[i] <= '9')
		{
			int cur = 0;
			for (; '0' <= s[i] && s[i] <= '9'; i++)
				cur = cur * 10 + s[i] - '0';
			element tins;
			tins.type = 3;tins.val = cur;
			compiled.push_back(tins);
			i--;
		} else if (s[i] == '(')
		{
			oper.push("(");
		} else if (s[i] == ')')
		{
			while (oper.top() != "(") {
				element tins;
				tins.type = 4;
				tins.val = operators(oper.top());
				oper.pop();
				compiled.push_back(tins);
			}
			oper.pop();
		} else if (valid_char(s[i]))
		{
			string str = "";
			while (valid_char(s[i]))
				str += s[i++];
			i--;
			element tins;
			tins.type = 2;
			tins.name = str;
			compiled.push_back(tins);
		} else if (!blank(s[i]))
		{
			string tsi = "";
			if (last == 0 || (!valid_char(last) && last != ')'))
				tsi = ".";
//			tsi += s[i];
			if (operators(tsi + s.substr(i, 2)))
			{
				tsi += s.substr(i, 2);
				i++;
			} else
			{
				tsi += s[i];
			}
			while (oper.size() && operators(tsi) / 10 >= operator2(oper.top()) / 10)
			{
				element tins;
				tins.type = 4;
				tins.val = operators(oper.top());
				oper.pop();
				compiled.push_back(tins);
			}
			oper.push(tsi);
		} else continue;
		last = s[i];
	}
	while (oper.size())
	{
		element tins;
		tins.type = 4;
		tins.val = operators(oper.top());
		oper.pop();
		compiled.push_back(tins);
	}
}
// End compiler
//

void testoutput()
{
	for (auto var : variable_table)
	{
		cout << "Global Variable: " << var.first;
		for (int i : var.second.dimension) cout << "[" << i << "]";
		cout << " @ " << var.second.val << endl;
	}
	cout << "Funtions:\n";
	for (int i = 0; i < (int) functions.size(); i++)
	{
		cout << "Name: " << functions[i].name << endl;
		cout << "Args: ";
		for (int j = 0; j < functions[i].arguments.size(); j++)
			cout << functions[i].arguments[j] << " ";
		cout << endl;
		for (int j = 0; j < functions[i].body.size(); j++)
		{
			auto &l = functions[i].body[j];
			cout << "LL" << j << ":";
			if (l.type <= 0)
			{
				if (l.type == -4)
					cout << "<DIM> ";
				else if (l.type == -3)
					cout << "<RET> ";
				cout << l.s;
				cout << "\n";
				if (l.type == -1)
					cout << " [END = " << l.end << "]\n";
				for (auto r : l.sc)
				{
					if (r.type <= 2)
						cout << "<OBJ " << r.name << ">";
					else if (r.type == 3)
						cout << "<NUM " << r.val << ">";
					else if (r.type == 4)
						cout << "<OPER " << r.val << ">";
				}
				cout << endl;
			} else if (l.type == 1) // for
			{
				cout << "<FOR> " << l.for_1 << ";" << l.for_2 << ";" << l.for_3 << "; [END = " << l.end << "]\n";
				cout << "<FOR 1> : ";
				for (auto r : l.for_1c)
				{
					if (r.type <= 2)
						cout << "<OBJ " << r.name << ">";
					else if (r.type == 3)
						cout << "<NUM " << r.val << ">";
					else if (r.type == 4)
						cout << "<OPER " << r.val << ">";
				}
				cout << endl;
				cout << "<FOR 2> : ";
				for (auto r : l.for_2c)
				{
					if (r.type <= 2)
						cout << "<OBJ " << r.name << ">";
					else if (r.type == 3)
						cout << "<NUM " << r.val << ">";
					else if (r.type == 4)
						cout << "<OPER " << r.val << ">";
				}
				cout << endl;
				cout << "<FOR 3> : ";
				for (auto r : l.for_3c)
				{
					if (r.type <= 2)
						cout << "<OBJ " << r.name << ">";
					else if (r.type == 3)
						cout << "<NUM " << r.val << ">";
					else if (r.type == 4)
						cout << "<OPER " << r.val << ">";
				}
				cout << endl;
			} else if (l.type == 2)
			{
				cout << "<IF > " << l.s << "; [END = " << l.end << "]\n";
				for (auto r : l.sc)
				{
					if (r.type <= 2)
						cout << "<OBJ " << r.name << ">";
					else if (r.type == 3)
						cout << "<NUM " << r.val << ">";
					else if (r.type == 4)
						cout << "<OPER " << r.val << ">";
				}
				cout << endl;
			} else if (l.type == 3) // else
			{
				cout << "<ELSE>\n";
			}
		}
		cout << endl;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int Tvar;
	cin >> Tvar;
	for (int i = 0; i < Tvar; i++)
	{
		int t;
		cin >> t;
		inputbuf.push(t);
	}
	string s = "", tss = "";
	while (!cin.eof() && getline(cin, tss))
	{
		if (tss == "" || tss[0] == '#' || tss.substr(0, 6) == "using ") continue;
		s += tss;
	}
	process_function(s);
	for (int i = 0; i < (int)functions.size(); i++)
	{
		process_range(functions[i].body, 0, 0);
		for (int j = 0; j < (int) functions[i].body.size(); j++)
		{
			if (functions[i].body[j].type < 0 && functions[i].body[j].type != -3) continue;
//			cerr << "Compiling... Func " << i << ", line " << j << endl;
			functions[i].body[j].s = pre_compile(functions[i].body[j].s);
			functions[i].body[j].for_1 = pre_compile(functions[i].body[j].for_1);
			functions[i].body[j].for_2 = pre_compile(functions[i].body[j].for_2);
			functions[i].body[j].for_3 = pre_compile(functions[i].body[j].for_3);
			compile(functions[i].body[j].for_1c, functions[i].body[j].for_1);
			compile(functions[i].body[j].for_2c, functions[i].body[j].for_2);
			compile(functions[i].body[j].for_3c, functions[i].body[j].for_3);
			compile(functions[i].body[j].sc, functions[i].body[j].s);
		}
	}
//	testoutput();
	call_function("main", vector<int>(), alloc_top, variable_table);
	return 0;
}

}

int main()
{
	return uoj_0098::main();
}
