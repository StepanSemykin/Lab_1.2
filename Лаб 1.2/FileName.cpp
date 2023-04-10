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
		
		bool _contains(TreeNode* root, int val) const
		{
			if (!root) return false;
			if (root->data == val) return true;
			else if (root->data > val) _contains(root->left, val);
			else _contains(root->right, val);
		}

		TreeNode* get_min(TreeNode* root) const
		{
			if (!root->left) return root;
			get_min(root->left);
		}

		TreeNode* find(TreeNode* root, int val, TreeNode*& parent) const
		{
			if (!root) return nullptr;
			if (root->data == val) return root;
			else if (root->data > val)
			{
				parent = root;
				return find(root->left, val, parent);
			}
			else
			{
				parent = root;
				return find(root->right, val, parent);
			}
		}

		TreeNode* _erase(TreeNode* root, int val, bool& erase)
		{
			TreeNode* parent = nullptr;
			TreeNode* curr = root;
			curr = find(curr, val, parent);

			if (!curr)
			{
				erase = false;
				return nullptr;
			}
			if (!curr->left && !curr->right)
			{
				if (curr != root)
				{
					if (parent->left == curr) parent->left = nullptr;
					else parent->right = nullptr;
				}
				else root = nullptr;
				erase = true;
				delete curr;
			}
			else if (curr->left && curr->right)
			{
				TreeNode* tmp = get_min(curr->right);
				int tmp1 = tmp->data;
				TreeNode* tmp2 = _erase(root, tmp->data, erase);
				curr->data = tmp1;
			}
			else 
			{
				TreeNode* child = (curr->left) ? curr->left : curr->right;
				if (curr != root)
				{
					if (curr == parent->left) parent->left = child;
					else parent->right = child;
				}
				else root = child;
				erase = true;
				delete curr;
			}
			return root;
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

int main()
{
	//MySet el_1000, el_10000, el_100000;
	//vector<int> el_1000_, el_10000_, el_100000_;
	//double seconds = 0;

	//cout.setf(ios_base::fixed);

	///*Множество 1000 эл*/
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 1000; ++j)
	//	{
	//		
	//		el_1000.insert(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert 1000 el " << seconds / 100 << endl;

	///*Множество 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 10000; ++j)
	//	{

	//		el_10000.insert(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert 10000 el " << seconds / 100 << endl;

	///*Множество 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 100000; ++j)
	//	{

	//		el_100000.insert(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert 100000 el " << seconds / 100 << endl;

	///*Вектор 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 1000; ++j)
	//	{

	//		el_1000_.push_back(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert 1000 el " << seconds / 100 << endl;

	///*Вектор 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 10000; ++j)
	//	{

	//		el_10000_.push_back(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert 10000 el " << seconds / 100 << endl;

	///*Вектор 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 100; ++i)
	//{
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 100000; ++j)
	//	{

	//		el_100000_.push_back(lcg());
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert 100000 el " << seconds / 100 << endl;

	///*0000000000000000000000000000000000000000000000000000000000000000000000000*/

	///*Множество 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_1000.contains(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET find in 1000 el " << seconds / 1000 << endl;

	///*Множество 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_10000.contains(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET find in 10000 el " << seconds / 1000 << endl;

	///*Множество 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_100000.contains(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET find in 100000 el " << seconds / 1000 << endl;

	///*Вектор 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	int val = lcg();
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 1000; ++j)
	//	{
	//		if (el_1000_[i] == val) break;
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR find in 1000 el " << seconds / 1000 << endl;

	///*Вектор 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	int val = lcg();
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 10000; ++j)
	//	{
	//		if (el_10000_[i] == val) break;
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR find in 10000 el " << seconds / 1000 << endl;

	///*Вектор 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	int val = lcg();
	//	clock_t start = clock();
	//	for (size_t j = 0; j < 100000; ++j)
	//	{
	//		if(el_100000_[i] == val) break;
	//	}
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR find in 100000 el " << seconds / 1000 << endl;

	///*0000000000000000000000000000000000000000000000000000000000000000000000000*/

	///*Множество 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_1000.insert(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert el in 1000 el " << seconds / 1000 << endl;

	///*Множество 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_10000.insert(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert el in 10000 el " << seconds / 1000 << endl;

	///*Множество 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_100000.insert(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET insert el in 100000 el " << seconds / 1000 << endl;

	///*Вектор 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_1000_.push_back(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert el in 1000 el " << seconds / 1000 << endl;

	///*Вектор 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_10000_.push_back(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert el in 10000 el " << seconds / 1000 << endl;

	///*Вектор 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_100000_.push_back(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR insert el in 100000 el " << seconds / 1000 << endl;

	///*0000000000000000000000000000000000000000000000000000000000000000000000000*/

	///*Множество 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_1000.erase(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET erase el in 1000 el " << seconds / 1000 << endl;

	///*Множество 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_10000.erase(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET erase el in 10000 el " << seconds / 1000 << endl;

	///*Множество 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_100000.erase(lcg());
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average SET erase el in 100000 el " << seconds / 1000 << endl;

	///*Вектор 1000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_1000_.pop_back();
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR erase el in 1000 el " << seconds / 1000 << endl;

	///*Вектор 10000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_10000_.pop_back();
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR erase el in 10000 el " << seconds / 1000 << endl;

	///*Вектор 100000 эл*/
	//seconds = 0;
	//for (size_t i = 0; i < 1000; ++i)
	//{
	//	clock_t start = clock();
	//	el_100000_.pop_back();
	//	clock_t end = clock();
	//	seconds += (double)(end - start) / CLOCKS_PER_SEC;
	//}
	//cout.precision(6);
	//cout << "Average VECTOR erase el in 100000 el " << seconds / 1000 << endl;

	cout << endl << endl << endl << endl << endl;

	MySet a, b, c;
	a.insert(5);
	a.insert(8);
	a.insert(3);
	a.insert(4);
	a.insert(2);
	a.insert(7);
	a.insert(9);
	a.insert(11);
	a.insert(12);
	a.insert(6);
	a.insert(10);

	a.print();
	cout << endl;

	a.erase(8);
	a.insert(13);
	a.print();
	cout << endl << endl;

	b.insert(5);
	b.insert(2);
	b.insert(15);
	b.insert(1);
	b.insert(7);
	b.insert(99);

	b.print();
	cout << endl;

	c = a.difference(b);
	c.print();

	return 0;
}
