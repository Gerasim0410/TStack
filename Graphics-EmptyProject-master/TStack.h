#pragma once
#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class TStack {
	T *arr;
	int size;
	int num;
public:
	TStack(int _size = 10000) {
		if (_size <= 0) throw _size;
		size = _size;
		arr = new T[size];
		num = -1;
	}
	TStack(const TStack& st) {
		size = st.size;
		arr = new T[size];
		num = st.num;
		for (int i = 0; i <= num; i++) arr[i] = st.arr[i];
	}
	TStack& operator= (const TStack& st) {
		if (this != &st) {
			delete[] arr;
			size = st.size;
			arr = new T[size];
			num = st.num;
			for (int i = 0; i <= num; i++) arr[i] = st.arr[i];
		}
		return *this;
	}
	bool IsEmpty()const {
		if (num == -1) return true;
		return false;
	}
	bool IsFull()const {
		if (num == size - 1) return true;
		return false;
	}
	void push(T el) {
		if (num == size - 1) throw num;
		else {
			arr[num + 1] = el;
			num++;
		}
	}
	T pop() {
		if (num == 0) throw num;
		else {
			num--;
			return arr[num + 1];
		}
	}
	T top() {
		if (num == size - 1) throw num;
		else {
			return arr[num + 1];
		}
	}
	void Clear() {
		num = -1;
	}
};

class TCalculator {
	string expr, postfix;
	TStack<char> stcc, stdd;
public:
	TCalculator():stcc(100) {}
	void SetExpression(const string& _expr) {
		expr = _expr;
	}
	string GetExpr() {
		return expr;
	}
	bool CheckBrackets(){
		stcc.Clear();
		for (int i = 0; i < expr.size(); i++) {
			if (expr[i] == '(') stcc.push('(');
			if (expr[i] == ')') {
				if (stcc.IsEmpty()) return false;
				stcc.pop();
			}
			return stcc.IsEmpty();
		}
	}
	int Prior(char c) {
		if (c == '(') return 0;
		if (c == '+') return 1;
		if (c == '-') return 1;
		if (c == '/') return 2;
		if (c == '*') return 2;
		if (c == '^') return 3;
	}
	void ToPostfix() {
		string str = "(";
		str += expr += ")";
		postfix = " ";
		stcc.Clear();
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '(') stcc.push('(');
			if (str[i] >= '0' && str[i] <= 9 || str[i] == '.') {
				char t = stcc.pop();
				while (t != '(') {
					postfix += t;
					t = stcc.pop();
				}
			}
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
				char t = stcc.pop();
				postfix += ' ';
				while (Prior(str[i]) <= Prior(t)) {
					postfix += t;
					char t = stcc.pop();
				}
				stcc.push(t);
				stcc.push(str[i]);
			}
		}
	}
	double Calculate() {
		stdd.Clear();
		for (int i = 0; i < postfix.size(); i++) {
			if (postfix[i] <= '9' && postfix[i] >= '0' || postfix[i] == '.') {
				char *tmp;
				double d = strtod(&postfix[i], &tmp);
				stdd.push(d);
				int k = tmp - &postfix[i];
				i += k - 1;
			}
			if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double op1, op2 = stdd.pop();
				op1 = stdd.pop();
				if (postfix[i] = '+') {
					double res = op1 + op2;
					stdd.push(res);
				}
				if (postfix[i] = '-') {
					double res = op1 - op2;
					stdd.push(res);
				}
				if (postfix[i] = '*') {
					double res = op1 * op2;
					stdd.push(res);
				}
				if (postfix[i] = '/') {
					double res = op1 / op2;
					stdd.push(res);
				}
				if (postfix[i] = '^') {
					double res = pow(op1, op2);
					stdd.push(res);
				}
			}
		}
		return stdd.pop();
	}
};
