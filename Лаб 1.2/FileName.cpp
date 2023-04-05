#include<iostream>
#include<iomanip>

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

		TreeNode* _contains(TreeNode* root, int val, bool& contains) const
		{
			if (!root)
			{
				contains = false;
				return nullptr;
			}
			if (root->data == val)
			{
				contains = true;
				return root;
			}
			else if (root->data > val) root->left = _contains(root->left, val, contains);
			else root->right = _contains(root->right, val, contains);
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
				/*if (root->left && root->right)
				{
					root->data = get_min(root->right)->data;
					root->right = _erase(root->right, root->data, erase);*/
					// = get_min(root);
					//tmp->data = get_min(root)->data;
					//root = root->right;
					//root->left = tmp;

					//TreeNode* tmp = root->right;
					//tmp->data = root->right->data;

					//TreeNode* tmp1 = root->left;
					//tmp1->data = root->left->data;
					//delete root->right;
					//root = get_min(root->right);
					//root->data = get_min(root->right)->data;
					//root->right = tmp;
					//root->left = tmp1;
					//delete get_min(root);


				//}
				if (root->left)
				{
					root = root->left;
					//delete root->left;
				}
				else if (root->right)
				{
					root = root->right;
					//delete root->right;
				}

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
			bool contains;
			_contains(root, val, contains);
			return contains;
		}

		bool erase(int val)
		{
			bool erase;
			root = _erase(root, val, erase);
			return erase;
		}
};

int main()
{
	MySet a;
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
	cout << endl << endl << endl << endl;

	a.erase(8);
	a.print();



	//cout << a.contains(5) << endl;
	//cout << a.contains(88) << endl;

	return 0;
}
