#include <iostream>
#include "rbtreenode.h"
#include "SHA256.h"
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;

class ll
{
	struct ln
	{
		RNode *tt;
		ln *next;

		ln(RNode *n) : tt(n), next(nullptr) {}
	};
	ln *head;
	ln *tail;

public:
	ll() : head(nullptr), tail(nullptr) {}
	void insert(RNode *node)
	{
		ln *newNode = new ln(node);
		if (!head)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
	}
	void update_datas(int i, const string &str2)
	{
		ln *current = head;
		while (current != nullptr)
		{
			RNode *node = current->tt; // Access the RNode object in the tree
			if (i >= 0 && i < node->cols)
			{						   // Ensure index i is within bounds
				node->datas[i] = str2; // Update datas[i] with the new string
			}
			current = current->next;
		}
	}

	bool empty()
	{
		return head == nullptr;
	}
	void print() const
	{
		ln *current = head;
		while (current != nullptr)
		{
			RNode *node = current->tt;
			cout << "RNode Path: " << node->myPath << endl;
			cout << "Data: " << node->data << endl;
			cout << "Hash: " << node->hash << endl;
			cout << "Height: " << node->height << endl;
			cout << "Mod29: " << node->mod29 << endl;
			cout << "Color: " << node->color << endl;
			for (int i = 0; i < node->cols; ++i)
			{
				cout << "Data[" << i << "]: " << node->datas[i] << endl;
			}
			current = current->next;
			cout << endl;
		}
	}

	void clear()
	{
		ln *curr = head;
		while (curr)
		{
			ln *next = curr->next;
			delete curr;
			curr = next;
		}
		head = tail = nullptr;
	}
	~ll()
	{
		clear();
	}
};

class rbtree
{
private:
	string path;
	string parent;
	bool sha;
	int modulo;
	string different;
	string deleted = "";
	RNode *deletedNode = NULL;
	ll rangenodes;

public:
	RNode *root;
	rbtree(string foldername, bool allow) : path(foldername), sha(allow)
	{
		different = computeSHA256("Hackie Chan");
		if (!sha)
		{
			modulo = (different.length()) % 29;
		}
		cout << "AVL : " << foldername << " with Hash : " << different << endl;
		root = nullptr;
		parent = "";
	}

	rbtree(rbtree &other)
	{
		root = copycatrbtree(other.root);
	}

	RNode *copycatrbtree(RNode *n)
	{
		if (!n)
		{
			return nullptr;
		}
		RNode *nn = new RNode(*n); // calling node copy constructor
		nn->left = copycatrbtree(n->left);
		if (nn->left)
		{
			nn->left->parent = nn;
		}
		nn->right = copycatrbtree(n->right);
		if (nn->right)
		{
			nn->right->parent = nn;
		}
		return nn;
	}
	rbtree &operator=(const rbtree &other)
	{
		if (this == &other)
			return *this; // Avoid self-assignment

		deleteTree(root); // Free current resources
		sha = other.sha;
		deleted = other.deleted;
		modulo = other.modulo;
		different = other.different;
		if (other.root)
		{
			root = new RNode(*other.root);
		}
		else
		{
			root = nullptr;
		}
		inOrderCreation(root);

		return *this;
	}

	void inOrderCreation(RNode *node)
	{
		if (node)
		{
			inOrderCreation(node->left);
			cout << "Setting Path for " << path << endl;
			node->setMainPath(path);
			inOrderCreation(node->right);
		}
	}


	void makeFolder(string folderName)
	{
		path = folderName;
		if (filesystem::create_directory(folderName))
		{
			cout << "Folder created: " << folderName << endl;
		}
		else
		{
			cout << "Failed to create folder or it already exists." << endl;
		}
	}

	void printLL()
	{
		rangenodes.print();
		cout << endl
			 << endl;
	}

	void save(RNode *node)
	{
		if (node)
		{
			save(node->left);
			cout << "Setting Path for " << path << endl;
			node->saveToFile();
			save(node->right);
		}
	}

	void insert(string d, string *arr, int c, int r)
	{
		string temp = d;
		for (int i = 0; i < c; i++)
		{
			temp += *(arr + i);
		}
		size_t HashOfData = std::hash<string>{}(temp);
		myInsert(root, d, HashOfData, arr, c, r);
	}
	void myInsert(RNode *&curr, string val, size_t HashOfData, string *list, int c, int r)
	{
		RNode *temp = new RNode(val, HashOfData, list, c, path, r, different);

		if (searchbyhash(HashOfData))
		{
			cout << "Duplicate found: " << val << endl;
			return; // Don't insert if it's a duplicate
		}
		RNode *prev = nullptr;
		RNode *current = root;
		while (current)
		{
			prev = current;
			if (HashOfData < current->hash)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		temp->parent = prev;
		if (!prev)
		{

			root = temp;
			temp->setLeftChildPath("");	 // No left child
			temp->setRightChildPath(""); // No right child
		}
		else if (HashOfData < prev->hash)
		{
			prev->left = temp;
			// balance tree
			prev->setLeftChildPath(temp->myPath); // Set the left child path for the parent
		}
		else
		{
			prev->right = temp;
			prev->setRightChildPath(temp->myPath); // Set the right child path for the parent
		}
		if (temp == root)
		{
			temp->setRightChildPath(""); // Root node should not have a right child path
		}

		balancetree(temp);
	}
	void balancetree(RNode *n)
	{
		while (n->parent && n->parent->color == "red")
		{
			if (n->parent == n->parent->parent->left)
			{
				RNode *prev = n->parent->parent->right;
				if (prev && prev->color == "red")
				{ // Check if prev is null
					n->parent->color = "black";
					prev->color = "black";
					n->parent->parent->color = "red";
					n = n->parent->parent;
				}
				else
				{
					if (n == n->parent->right)
					{
						n = n->parent;
						leftrotate(n);
					}
					n->parent->color = "black";
					if (n->parent->parent)
					{
						n->parent->parent->color = "red";
						rightrotate(n->parent->parent);
					}
				}
			}
			else
			{
				RNode *prev = n->parent->parent->left;
				if (prev && prev->color == "red")
				{ // Check if prev is null
					n->parent->color = "black";
					prev->color = "black";
					n->parent->parent->color = "red";
					n = n->parent->parent;
				}
				else
				{
					if (n == n->parent->left)
					{
						n = n->parent;
						rightrotate(n);
					}
					n->parent->color = "black";
					if (n->parent->parent)
					{
						n->parent->parent->color = "red";
						leftrotate(n->parent->parent);
					}
				}
			}
			if (n == root)
				break;
		}
		root->color = "black";
	}
	size_t
	Hash(const string &input)
	{
		return std::hash<string>{}(input);
	}
	void inOrder(RNode *haha)
	{
		if (haha == NULL)
		{
			return;
		}
		else
		{
			if (haha->left == NULL)
			{
				haha->setLeftChildPath("");
			}
			if (haha->right == NULL)
			{
				haha->setRightChildPath("");
			}
			inOrder(haha->left);
			cout << haha->data << ":" << haha->hash << " ";
			inOrder(haha->right);
		}
	}
	void display()
	{
		if (root != nullptr)
		{
			inOrder(root);
		}
	}
	void rightrotate(RNode *temp2)
	{
		RNode *temp1 = temp2->left;
		temp2->left = temp1->right;

		if (temp1->right)
		{
			temp1->right->parent = temp2;
		}

		temp1->parent = temp2->parent;

		if (!temp2->parent)
		{
			root = temp1;
		}
		else if (temp2 == temp2->parent->right)
		{
			temp2->parent->right = temp1;
		}
		else
		{
			temp2->parent->left = temp1;
		}

		temp1->right = temp2;
		temp2->parent = temp1;
		temp1->setRightChildPath(temp2->myPath); // Update temp1's right child path
		if (temp1->left)
		{
			temp1->setLeftChildPath(temp1->left->myPath); // Update temp1's left child path
		}
		if (temp2->left)
		{
			temp2->setLeftChildPath(temp2->left->myPath); // Update temp2's left child path
		}
		if (temp2->right)
		{
			temp2->setRightChildPath(temp2->right->myPath); // Update temp2's right child path
		}
	}
	void leftrotate(RNode *temp2)
	{
		RNode *temp1 = temp2->right;
		temp2->right = temp1->left;

		if (temp1->left)
		{
			temp1->left->parent = temp2;
		}

		temp1->parent = temp2->parent;

		if (!temp2->parent)
		{
			root = temp1;
		}
		else if (temp2 == temp2->parent->left)
		{
			temp2->parent->left = temp1;
		}
		else
		{
			temp2->parent->right = temp1;
		}

		temp1->left = temp2;
		temp2->parent = temp1;

		// Update paths after rotation

		temp1->setLeftChildPath(temp2->myPath); // Update temp1's left child path
		if (temp1->right)
		{
			temp1->setRightChildPath(temp1->right->myPath); // Update temp1's right child path
		}

		if (temp2->left)
		{
			temp2->setLeftChildPath(temp2->left->myPath); // Update temp2's left child path
		}
		if (temp2->right)
		{
			temp2->setRightChildPath(temp2->right->myPath); // Update temp2's right child path
		}
	}
	/*void remove(string val) {
		RNode* current = root;
		RNode* prev = nullptr;
		RNode* temp2 = nullptr;
		while (current) {
			prev = current;
			if (val == current.data) {
				break;
			}
			if (val < current.data) {
				current = current.left;
			}
			else {
				current = current.right;
			}
		}
		temp2 = current;
		if (current == root) {
			if (current->right) {
				RNode* temp = prev->left;
				while (temp->right) {
					temp = temp->right;
				}
				temp->right = current->left;
				current->left = prev->left;
				root = current;
			}
			else if(current->left){
				root = current->left;
			}
			else {
				root = nullptr;
			}
			delete temp2;
			temp2 = nullptr;
			return;
		}
		else {

		}
	}*/
	RNode *search2(RNode *root, const std::string &target)
	{
		if (!root)
		{
			return nullptr;
		}
		if (root->data == target)
		{
			return root;
		}
		RNode *leftchild = search2(root->left, target);
		if (leftchild)
		{
			return leftchild;
		}
		return search2(root->right, target);
	}
	bool search(string val)
	{
		if (search2(root, val))
		{
			return true;
		}
		return false;
	}

	void Visualize(RNode *root, bool last, string spacing = "")
	{
		if (root != nullptr)
		{
			cout << spacing;

			if (last)
			{
				cout << "└────────────";
				spacing += "             ";
			}
			else
			{
				cout << "├────────────";
				spacing += "│            ";
			}

			cout << root->data << "(" << (root->color) << ")" << endl;

			Visualize(root->left, false, spacing);
			Visualize(root->right, true, spacing);
		}
	}

	void visualize()
	{
		if (root)
			Visualize(root, true);
	}

	void delete_val(string val)
	{
		RNode *curr = search2(root, val);
		if (curr == nullptr)
		{
			cout << "not found" << endl;
			return;
		}
		delete2(curr);
	}

	void delete2(RNode *curr)
	{
		RNode *temp = curr;
		string oc = temp->color;
		RNode *cc = nullptr;

		if (curr->left == nullptr)
		{
			cc = curr->right;
			moveNodes(curr, curr->right);
		}
		else if (curr->right == nullptr)
		{
			cc = curr->left;
			moveNodes(curr, curr->left);
		}
		else
		{
			temp = findmin(curr->right);
			oc = temp->color;
			cc = temp->right;
			if (temp->parent != curr)
			{
				moveNodes(temp, temp->right);
				temp->right = curr->right;
				if (temp->right)
					temp->right->parent = temp;
			}
			moveNodes(curr, temp);
			temp->left = curr->left;
			if (temp->left)
				temp->left->parent = temp;
			temp->color = curr->color;
		}

		if (!curr->myPath.empty() && filesystem::exists(curr->myPath))
		{
			filesystem::remove(curr->myPath);
		}
		delete curr;
		if (cc)
		{
			cc->parent = temp->parent;
		}
		else if (oc == "black")
		{
			deletefix3(cc); // Ensure cc is passed correctly
		}
	}

	void deletefix3(RNode *x)
	{
		while (x != root && x && x->color == "black")
		{ // Ensure x is not null
			if (x == x->parent->left)
			{
				RNode *sk = x->parent->right;
				if (sk && sk->color == "red")
				{ // Check sk
					sk->color = "black";
					x->parent->color = "red";
					leftrotate(x->parent);
					sk = x->parent->right;
				}
				if ((!sk->left || sk->left->color == "black") &&
					(!sk->right || sk->right->color == "black"))
				{ // Check children
					sk->color = "red";
					x = x->parent;
				}
				else
				{
					if (!sk->right || sk->right->color == "black")
					{
						if (sk->left)
							sk->left->color = "black";
						sk->color = "red";
						rightrotate(sk);
						sk = x->parent->right;
					}
					sk->color = x->parent->color;
					x->parent->color = "black";
					if (sk->right)
						sk->right->color = "black";
					leftrotate(x->parent);
					x = root;
				}
			}
			else
			{ // Mirror logic for right subtree
				RNode *sk = x->parent->left;
				if (sk && sk->color == "red")
				{ // Check sk
					sk->color = "black";
					x->parent->color = "red";
					rightrotate(x->parent);
					sk = x->parent->left;
				}
				if ((!sk->right || sk->right->color == "black") &&
					(!sk->left || sk->left->color == "black"))
				{ // Check children
					sk->color = "red";
					x = x->parent;
				}
				else
				{
					if (!sk->left || sk->left->color == "black")
					{
						if (sk->right)
							sk->right->color = "black";
						sk->color = "red";
						leftrotate(sk);
						sk = x->parent->left;
					}
					sk->color = x->parent->color;
					x->parent->color = "black";
					if (sk->left)
						sk->left->color = "black";
					rightrotate(x->parent);
					x = root;
				}
			}
		}
		if (x)
			x->color = "black"; // Ensure x is not null
	}

	RNode *findmin(RNode *n)
	{
		if (!n)
			return nullptr; // Handle null case
		while (n->left != nullptr)
		{
			n = n->left;
		}
		return n;
	}

	void moveNodes(RNode *on, RNode *nn)
	{
		if (on->parent == nullptr)
		{
			root = nn;
		}
		else if (on == on->parent->left)
		{
			on->parent->left = nn;
			on->parent->setLeftChildPath(nn ? nn->myPath : "");
		}
		else
		{
			on->parent->right = nn;
			on->parent->setRightChildPath(nn ? nn->myPath : "");
		}
		if (nn != nullptr)
		{
			nn->parent = on->parent;
		}
	}
	RNode *getRoot()
	{
		return root;
	}

	bool searchbyhash1(RNode *n, size_t val)
	{
		if (n == nullptr)
		{
			return false;
		}
		if (val == n->hash)
		{
			return true;
		}
		else if (val > n->hash)
		{
			return searchbyhash1(n->right, val);
		}
		else
		{
			return searchbyhash1(n->left, val);
		}
	}
	bool searchbyhash(size_t val)
	{
		return searchbyhash1(root, val);
	}

	~rbtree()
	{
		deleteTree(root);
		root = NULL;
	}
	void deleteTree(RNode *node)
	{
		if (node == nullptr)
		{
			return;
		}
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
	//////////////////////////////////////////////////////////////////////////////////////

	void update(string s, string d)
	{
		RNode *location = search2(root, d);
		if (!location)
		{
			return;
		}
		location->data = s;
	}
	void update_all(string s)
	{
		RNode *temp = root;
		while (temp)
		{
			temp = update_all2(root, s);
			if (temp)
			{
				temp->data = s;
				temp = root;
			}
			else
			{
				break;
			}
		}
	}
	RNode *update_all2(RNode *n, string target)
	{
		if (!root)
		{
			return nullptr;
		}
		if (root->data == target)
		{
			return root;
		}
		RNode *leftchild = search2(root->left, target);
		if (leftchild)
		{
			return leftchild;
		}
		return search2(root->right, target);
	}
	void delete_all(string s)
	{
		RNode *temp = root;
		while (temp)
		{
			temp = delete_all2(root, s);
			if (temp)
			{
				delete_val(s);
				temp = root;
			}
			else
			{
				break;
			}
		}
	}
	RNode *delete_all2(RNode *n, string target)
	{
		if (!root)
		{
			return nullptr;
		}
		if (root->data == target)
		{
			return root;
		}
		RNode *leftchild = search2(root->left, target);
		if (leftchild)
		{
			return leftchild;
		}
		return search2(root->right, target);
		// hash changes
	}
	void delete_at(string s)
	{
		delete_val(s);
		// we need to set a flag to check if changes are made
	}
	void rangebynum(int lower, int upper, int k)
	{
		rangenodes.clear();					// Clear previous results
		rangebynum2(root, lower, upper, k); // Call the recursive function
		if (rangenodes.empty())
		{
			cout << "No such values present" << endl;
		}
		else
		{
			cout << "Successful" << endl;
		}
	}

	void rangebynum2(RNode *node, int lower, int upper, int k)
	{
		if (node == nullptr)
			return;
		rangebynum2(node->left, lower, upper, k);
		try
		{
			int dd = stoi(node->datas[k]);
			if (dd >= lower && dd <= upper)
			{
				rangenodes.insert(node);
			}
		}
		catch (const invalid_argument &e)
		{
			// skip the node
		}
		rangebynum2(node->right, lower, upper, k);
	}
	void rangebyrollnum(const string &lower, const string &upper)
	{
		rangenodes.clear();					 // Clear previous results
		rangebyrollnum2(root, lower, upper); // Call the recursive function
		if (rangenodes.empty())
		{
			cout << "No such values present" << endl;
		}
		else
		{
			cout << "Successful" << endl;
		}
	}

	void rangebyrollnum2(RNode *node, const string &lower, const string &upper)
	{
		if (node == nullptr)
			return;

		// traverse left subtree first
		rangebyrollnum2(node->left, lower, upper);
		try
		{
			string rollNumber = node->data;

			// Separate '21i', '0066'
			size_t sign = rollNumber.find('-');
			if (sign != string::npos)
			{
				string prefix = rollNumber.substr(0, sign);
				string numberPart = rollNumber.substr(sign + 1);

				if (prefix == lower.substr(0, sign))
				{
					// Convert number part to an integer for range comparison
					int rollNum = stoi(numberPart);
					int lowerNum = stoi(lower.substr(sign + 1));
					int upperNum = stoi(upper.substr(sign + 1));

					if (rollNum >= lowerNum && rollNum <= upperNum)
					{
						//  within range, insert the node into the linked list
						rangenodes.insert(node);
					}
				}
			}
		}
		catch (const invalid_argument &e)
		{
			// skip the node
		}
		// Traverse right subtree
		rangebyrollnum2(node->right, lower, upper);
	}

	void set(int i, string str2)
	{
		rangenodes.update_datas(i, str2);
	}
	/*void delete_in_tree() {

	}*/
	// void delete_in_tree2() {
	//	while (rangenodes.head != nullptr) { // Loop until the linked list is empty
	//		RNode* nodeToDelete = rangenodes.head->tt; // Access the tree node pointer in the current linked list node
	//		if (nodeToDelete) {
	//			string value = nodeToDelete->data; // Extract the `data` value
	//			delete_val(value); // Delete the value from the tree
	//		}

	//		// Remove the current linked list node
	//		ll::ln* temp = rangenodes.head;
	//		rangenodes.head = rangenodes.head->next; // Move to the next node
	//		delete temp; // Free memory
	//	}
	//	rangenodes.tail = nullptr; // Reset the tail pointer
	//}
};
