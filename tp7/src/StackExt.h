# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
	stack<T>s;
	stack<T>min;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return s.empty();
}

template <class T>
T& StackExt<T>::top() {
	return s.top();
}

template <class T>
void StackExt<T>::pop() {

	if(top() == min.top())
	{
		min.pop();
	}

	s.pop();


}

template <class T>
void StackExt<T>::push(const T& val) {

	s.push(val);

	if(min.empty())
	{
		min.push(val);
	}
	else
	{
	if(val <= min.top())
	{
		min.push(val);
	}
	}

}

template <class T>
T& StackExt<T>::findMin() {
	return min.top();
}
