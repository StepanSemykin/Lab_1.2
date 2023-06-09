#include<iostream>
#include<iomanip>
#include<stack>
#include<ctime>
#include<vector>

using namespace std;

struct TreeNode
{
	int data;
	int height = 0;
	TreeNode* right, * left;
};

class MySet
{
	private:
		TreeNode* root;

		void _clear(TreeNode* root) 
		{
			if (root->left) _clear(root->left);
			if (root->right) _clear(root->right); 
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

		void update_height(TreeNode* node) 
		{
			node->height = max(get_height(node->left), get_height(node->right)) + 1;
		}

		int get_balance(const TreeNode* node) 
		{
			return (node == nullptr) ? 0 : get_height(node->right) - get_height(node->left);
		}

		void swap(TreeNode* a, TreeNode* b) 
		{
			int a_data = a->data;
			a->data = b->data;
			b->data = a_data;
		}

		void right_rotate(TreeNode* node) 
		{
			swap(node, node->left);
			TreeNode* buffer = node->right;
			node->right = node->left;
			node->left = node->right->left;
			node->right->left = node->right->right;
			node->right->right = buffer;
			update_height(node->right);
			update_height(node);
		}

		void left_rotate(TreeNode* node)
		{
			swap(node, node->right);
			TreeNode* buffer = node->left;
			node->left = node->right;
			node->right = node->left->right;
			node->left->right = node->left->left;
			node->left->left = buffer;
			update_height(node->left);
			update_height(node);
		}

		void balance(TreeNode* node) 
		{
			int balance = get_balance(node);
			if (balance == -2) 
			{
				if (get_balance(node->left) == 1) left_rotate(node->left);
				right_rotate(node);
			}
			else if (balance == 2) 
			{
				if (get_balance(node->right) == -1) right_rotate(node->right);
				left_rotate(node);
			}
		}

		TreeNode* _insert(TreeNode* root, int val, bool& insert)
		{
			if (!root) 
			{
				root = new TreeNode();
				root->data = val;
				root->left = nullptr;
				root->right = nullptr;
				return root;
			}
			if (val > root->data) 
			{
				root->right = _insert(root->right, val, insert);
			}
			if (val < root->data) 
			{
				root->left = _insert(root->left, val, insert);
			}
			update_height(root);
			balance(root);
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

		static int get_height(const TreeNode* node) 
		{
			return node == nullptr ? -1 : node->height;
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
	MySet a;
	a.insert(8);
	a.insert(5);
	a.insert(3);
	a.insert(4);
	a.insert(2);
	a.insert(7);
	a.insert(9);
	a.insert(11);
	a.insert(12);
	a.insert(6);

	a.print();
	cout << endl;

	//a.erase(8);
	//a.insert(13);
	//a.print();
	//cout << endl << endl;

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
