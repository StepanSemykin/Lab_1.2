#include<iostream>
#include<iomanip>
#include<stack>
#include<ctime>
#include<vector>

using namespace std;

struct TreeNode
{
	int data;
	TreeNode* right, * left;
};

class MySet
{
	private:
		TreeNode* root;

		void _clear(TreeNode* root)
		{
			if (root)
			{
				_clear(root->left);
				_clear(root->right);
				delete root;
			}
			root = nullptr;
		}

		TreeNode* _copy(TreeNode* other)
		{
			if (!other) return nullptr;
			TreeNode* tmp = new TreeNode;
			tmp->data = other->data;
			tmp->left = _copy(other->left);
			tmp->right = _copy(other->right);
			return tmp;
		}

		void _print(TreeNode* root, int indent = 0) const
		{
			if (!root) return;
			_print(root->right, indent + 4);
			cout << std::setw(indent) << ' ' << root->data << endl;
			_print(root->left, indent + 4);
		}

		TreeNode* _insert(TreeNode* root, int val, bool& insert)
		{
			if (!root)
			{
				TreeNode* tmp = new TreeNode();
				tmp->data = val;
				tmp->left = nullptr;
				tmp->right = nullptr;
				root = tmp;
				insert = true;
			}

			else if (root->data > val) root->left = _insert(root->left, val, insert);
			else if (root->data < val) root->right = _insert(root->right, val, insert);
			else insert = false;
			return root;
		}

		//TreeNode* _contains(TreeNode* root, int val, bool& contains) const
		//{
		//	if (!root)
		//	{
		//		//contains = false;
		//		return nullptr;
		//	}
		//	if (root->data == val)
		//	{
		//		contains = true;
		//		return root;
		//	}
		//	else if (root->data > val) root->left = _contains(root->left, val, contains);
		//	else root->right = _contains(root->right, val, contains);
		//}
		
		bool _contains(TreeNode* root, int val) const
		{
			if (!root)
			{
				return false;
			}
			if (root->data == val)
			{
				return true;
			}
			else if (root->data > val) _contains(root->left, val);
			else _contains(root->right, val);
		}

		TreeNode* get_min(TreeNode* root) const
		{
			if (!root->left) return root;
			get_min(root->left);
		}

		TreeNode* _erase(TreeNode* root, int val, bool& erase)
		{
			if (!root) return nullptr;

			if (root->data > val) root->left = _erase(root->left, val, erase);
			else if (root->data < val) root->right = _erase(root->right, val, erase);
			else if (root->left && root->right)
			{
				root->data = get_min(root->right)->data;
				root->right = _erase(root->right, root->data, erase);
			}
			else
			{
				if (root->left) root = root->left;
				else if (root->right) root = root->right;
				else
				{
					delete root;
					root = nullptr;
				}

			}
			return root;
		}

		void KLP(const TreeNode* root) const
		{
			if (!root) return;
			cout << root->data << " ";
			KLP(root->left);
			KLP(root->right);
		}

	public:
		MySet() 
		{
			root = nullptr;
		}

		MySet(const MySet& m)
		{
			root = _copy(m.root);
		}

		~MySet()
		{
			_clear(root);
		}

		void clear()
		{
			_clear(root);
		}

		MySet& operator = (const MySet& m)
		{
			if (!root) root = _copy(m.root);
			else 
			{
				_clear(root);
				root = _copy(m.root);
			}
			return *this;
		}

		void print() const
		{
			_print(root);
		}

		bool insert(int val)
		{
			bool insert;
			root = _insert(root, val, insert);
			return insert;
		}

		bool contains(int val) const
		{
			return _contains(root, val);
		}

		bool erase(int val)
		{
			bool erase;
			root = _erase(root, val, erase);
			return erase;
		}

		MySet intersection(const MySet& m)
		{
			MySet c;
			stack<TreeNode*> stack;
			TreeNode* tmp = m.root;
			while (!stack.empty() || tmp != nullptr)
			{
				if (tmp)
				{
					stack.push(tmp);
					tmp = tmp->left;
				}
				else
				{
					tmp = stack.top();
					stack.pop();
					if (contains(tmp->data) == true) c.insert(tmp->data);
					tmp = tmp->right;
				}
			}
			return c;
		}

		MySet difference(const MySet& m)
		{
			MySet c;
			c.root = _copy(root);
			stack<TreeNode*> stack;
			TreeNode* tmp = m.root;
			while (!stack.empty() || tmp != nullptr)
			{
				if (tmp)
				{
					stack.push(tmp);
					tmp = tmp->left;
				}
				else
				{
					tmp = stack.top();
					stack.pop();
					if (contains(tmp->data) == true) c.erase(tmp->data);
					tmp = tmp->right;
				}
			}
			return c;
		}
};

size_t lcg() 
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

//double average_100(const double* arr)
//{
//
//}

int main()
{
	MySet el_1000, el_10000, el_100000;
	vector<int> el_1000_, el_10000_, el_100000_;
	double seconds = 0;

	/*Множество 1000 эл*/
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 1000; ++j)
		{
			
			el_1000.insert(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert 1000 el " << seconds / 100 << endl;

	/*Множество 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 10000; ++j)
		{

			el_10000.insert(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert 10000 el " << seconds / 100 << endl;

	/*Множество 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 100000; ++j)
		{

			el_100000.insert(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert 100000 el " << seconds / 100 << endl;

	/*Вектор 1000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 1000; ++j)
		{

			el_1000_.push_back(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert 1000 el " << seconds / 100 << endl;

	/*Вектор 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 10000; ++j)
		{

			el_10000_.push_back(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert 10000 el " << seconds / 100 << endl;

	/*Вектор 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 100; ++i)
	{
		clock_t start = clock();
		for (size_t j = 0; j < 100000; ++j)
		{

			el_100000_.push_back(lcg());
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert 100000 el " << seconds / 100 << endl;

	/*0000000000000000000000000000000000000000000000000000000000000000000000000*/

	/*Множество 1000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_1000.contains(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET find in 1000 el " << seconds / 1000 << endl;

	/*Множество 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_10000.contains(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET find in 10000 el " << seconds / 1000 << endl;

	/*Множество 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_100000.contains(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET find in 100000 el " << seconds / 1000 << endl;

	/*Вектор 1000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		int val = lcg();
		clock_t start = clock();
		for (size_t j = 0; j < 1000; ++j)
		{
			if (el_1000_[i] == val) break;
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR find in 1000 el " << seconds / 1000 << endl;

	/*Вектор 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		int val = lcg();
		clock_t start = clock();
		for (size_t j = 0; j < 10000; ++j)
		{
			if (el_10000_[i] == val) break;
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR find in 10000 el " << seconds / 1000 << endl;

	/*Вектор 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		int val = lcg();
		clock_t start = clock();
		for (size_t j = 0; j < 100000; ++j)
		{
			if(el_100000_[i] == val) break;
		}
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR find in 100000 el " << seconds / 1000 << endl;

	/*0000000000000000000000000000000000000000000000000000000000000000000000000*/

	/*Множество 1000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_1000.insert(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert el in 1000 el " << seconds / 1000 << endl;

	/*Множество 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_10000.insert(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert el in 10000 el " << seconds / 1000 << endl;

	/*Множество 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_100000.insert(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average SET insert el in 100000 el " << seconds / 1000 << endl;

	/*Вектор 1000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_1000_.push_back(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert el in 1000 el " << seconds / 1000 << endl;

	/*Вектор 10000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_10000_.push_back(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert el in 10000 el " << seconds / 1000 << endl;

	/*Вектор 100000 эл*/
	seconds = 0;
	for (size_t i = 0; i < 1000; ++i)
	{
		clock_t start = clock();
		el_100000_.push_back(lcg());
		clock_t end = clock();
		seconds += (double)(end - start) / CLOCKS_PER_SEC;
	}
	cout.precision(6);
	cout << "Average VECTOR insert el in 100000 el " << seconds / 1000 << endl;



	//MySet a, b, c;
	//a.insert(5);
	//a.insert(8);
	//a.insert(3);
	//a.insert(4);
	//a.insert(2);
	//a.insert(7);
	//a.insert(9);
	//a.insert(11);
	//a.insert(12);
	//a.insert(6);
	//a.insert(10);

	//a.print();
	//cout << endl;

	//b.insert(5);
	//b.insert(2);
	//b.insert(15);
	//b.insert(1);
	//b.insert(7);
	//b.insert(99);

	//b.print();
	//cout << endl;

	//c = a.difference(b);
	//c.print();

	return 0;
}
