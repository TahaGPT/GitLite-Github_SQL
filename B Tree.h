// #pragma once
// #include <iostream>
// #include <queue>
// using namespace std;

// struct BNode
// {
//     int *key;
//     BNode **children;
//     int tot;
//     bool f;

//     BNode(int nn, bool leafing)
//     {
//         key = new int[nn - 1];
//         children = new BNode *[nn];
//         tot = 0;
//         f = leafing;

//         for (int i = 0; i < nn; i++)
//         {
//             children[i] = NULL;
//         }
//     }

//     ~BNode()
//     {
//         delete[] key;

//         if (!f)
//         {
//             for (int i = 0; i <= tot; i++)
//             {
//                 delete children[i];
//             }
//         }
//         delete[] children;
//     }
// };

// class BTree
// {
// private:
//     BNode *root;
//     int order;

//     // Helper method to find the predecessor
//     int findPredecessor(BNode *node, int idx)
//     {
//         BNode *current = node->children[idx];
//         while (!current->f)
//         {
//             current = current->children[current->tot];
//         }
//         return current->key[current->tot - 1];
//     }

//     // Helper method to find the successor
//     int findSuccessor(BNode *node, int idx)
//     {
//         BNode *current = node->children[idx + 1];
//         while (!current->f)
//         {
//             current = current->children[0];
//         }
//         return current->key[0];
//     }

//     // Borrow from left sibling
//     void borrowFromLeft(BNode *parent, int idx)
//     {
//         BNode *child = parent->children[idx];
//         BNode *leftSibling = parent->children[idx - 1];

//         // Move parent key to child
//         child->key[child->tot] = parent->key[idx - 1];
//         child->tot++;

//         // Move left sibling's last key to parent
//         parent->key[idx - 1] = leftSibling->key[leftSibling->tot - 1];
//         leftSibling->tot--;

//         // Move left sibling's last child to child (if not leaf)
//         if (!child->f)
//         {
//             child->children[child->tot] = leftSibling->children[leftSibling->tot];
//         }
//     }

//     // Borrow from right sibling
//     void borrowFromRight(BNode *parent, int idx)
//     {
//         BNode *child = parent->children[idx];
//         BNode *rightSibling = parent->children[idx + 1];

//         // Move parent key to child
//         child->key[child->tot] = parent->key[idx];
//         child->tot++;

//         // Move right sibling's first key to parent
//         parent->key[idx] = rightSibling->key[0];

//         // Shift right sibling keys left
//         for (int i = 0; i < rightSibling->tot - 1; i++)
//         {
//             rightSibling->key[i] = rightSibling->key[i + 1];
//         }
//         rightSibling->tot--;

//         // Move right sibling's first child to child (if not leaf)
//         if (!child->f)
//         {
//             child->children[child->tot] = rightSibling->children[0];
//             for (int i = 0; i < rightSibling->tot; i++)
//             {
//                 rightSibling->children[i] = rightSibling->children[i + 1];
//             }
//         }
//     }

//     // Merge nodes
//     void merge(BNode *parent, int idx)
//     {
//         BNode *child = parent->children[idx];
//         BNode *rightSibling = parent->children[idx + 1];

//         // Move parent key to child
//         child->key[child->tot] = parent->key[idx];
//         child->tot++;

//         // Copy keys from right sibling
//         for (int i = 0; i < rightSibling->tot; i++)
//         {
//             child->key[child->tot] = rightSibling->key[i];
//             child->tot++;
//         }

//         // Copy children from right sibling (if not leaf)
//         if (!child->f)
//         {
//             for (int i = 0; i <= rightSibling->tot; i++)
//             {
//                 child->children[child->tot] = rightSibling->children[i];
//                 child->tot++;
//             }
//         }

//         // Remove parent key and right sibling
//         for (int i = idx; i < parent->tot - 1; i++)
//         {
//             parent->key[i] = parent->key[i + 1];
//         }
//         for (int i = idx + 1; i <= parent->tot; i++)
//         {
//             parent->children[i] = parent->children[i + 1];
//         }
//         parent->tot--;

//         delete rightSibling;
//     }

//     // Internal delete method
//     void deleteKey(BNode *node, int data)
//     {
//         int idx = 0;
//         while (idx < node->tot && data > node->key[idx])
//         {
//             idx++;
//         }

//         if (idx < node->tot && data == node->key[idx])
//         {
//             // Key found in this node
//             if (node->f)
//             {
//                 // Leaf node
//                 for (int i = idx; i < node->tot - 1; i++)
//                 {
//                     node->key[i] = node->key[i + 1];
//                 }
//                 node->tot--;
//             }
//             else
//             {
//                 // Non-leaf node
//                 if (node->children[idx]->tot > (order / 2 - 1))
//                 {
//                     // Predecessor exists
//                     int pred = findPredecessor(node, idx);
//                     node->key[idx] = pred;
//                     deleteKey(node->children[idx], pred);
//                 }
//                 else if (node->children[idx + 1]->tot > (order / 2 - 1))
//                 {
//                     // Successor exists
//                     int succ = findSuccessor(node, idx);
//                     node->key[idx] = succ;
//                     deleteKey(node->children[idx + 1], succ);
//                 }
//                 else
//                 {
//                     // Merge children
//                     merge(node, idx);
//                     deleteKey(node->children[idx], data);
//                 }
//             }
//         }
//         else
//         {
//             // Key not in this node
//             if (node->f)
//             {
//                 // Key not found in tree
//                 return;
//             }

//             // Determine which child to recurse into
//             bool lastChild = (idx == node->tot);
//             if (node->children[idx]->tot == (order / 2 - 1))
//             {
//                 // Not enough keys in child, need to borrowNext or merge
//                 if (idx > 0 && node->children[idx - 1]->tot > (order / 2 - 1))
//                 {
//                     // Borrow from left sibling
//                     borrowFromLeft(node, idx);
//                 }
//                 else if (idx < node->tot && node->children[idx + 1]->tot > (order / 2 - 1))
//                 {
//                     // Borrow from right sibling
//                     borrowFromRight(node, idx);
//                 }
//                 else
//                 {
//                     // Merge with a sibling
//                     if (idx > 0)
//                     {
//                         merge(node, idx - 1);
//                         idx--;
//                     }
//                     else
//                     {
//                         merge(node, idx);
//                     }
//                 }
//             }

//             // Recursive delete
//             if (lastChild && idx > node->tot)
//             {
//                 deleteKey(node->children[idx - 1], data);
//             }
//             else
//             {
//                 deleteKey(node->children[idx], data);
//             }
//         }

//         // Adjust root if needed
//         if (root->tot == 0 && !root->f)
//         {
//             BNode *temp = root;
//             root = root->children[0];
//             delete temp;
//         }
//     }

//     // Inorder traversal helper
//     void inorderTraversal(BNode *node)
//     {
//         if (node == NULL)
//             return;

//         for (int i = 0; i < node->tot; i++)
//         {
//             if (!node->f)
//                 inorderTraversal(node->children[i]);
//             cout << node->key[i] << " ";
//         }

//         if (!node->f)
//             inorderTraversal(node->children[node->tot]);
//     }

//     // Preorder traversal helper
//     void preorderTraversal(BNode *node)
//     {
//         if (node == NULL)
//             return;

//         for (int i = 0; i < node->tot; i++)
//         {
//             cout << node->key[i] << " ";
//             if (!node->f)
//                 preorderTraversal(node->children[i]);
//         }

//         if (!node->f)
//             preorderTraversal(node->children[node->tot]);
//     }

//     // Postorder traversal helper
//     void postorderTraversal(BNode *node)
//     {
//         if (node == NULL)
//             return;

//         for (int i = 0; i < node->tot; i++)
//         {
//             if (!node->f)
//                 postorderTraversal(node->children[i]);
//         }

//         if (!node->f)
//             postorderTraversal(node->children[node->tot]);

//         for (int i = 0; i < node->tot; i++)
//         {
//             cout << node->key[i] << " ";
//         }
//     }

//     // Search helper method
//     bool searchKey(BNode *node, int data)
//     {
//         int i = 0;
//         while (i < node->tot && data > node->key[i])
//         {
//             i++;
//         }

//         if (i < node->tot && data == node->key[i])
//         {
//             return true;
//         }

//         if (node->f)
//         {
//             return false;
//         }

//         return searchKey(node->children[i], data);
//     }

// public:
//     BTree(int n)
//     {
//         root = NULL;
//         order = n;
//     }

//     void insert(int data)
//     {

//         // cout << "entering: " << data << endl;

//         if (root == NULL)
//         {
//             root = new BNode(order, true);
//             root->key[0] = data;
//             root->tot = 1;
//         }
//         else
//         {
//             if (root->tot == order - 1)
//             {
//                 BNode *temp = new BNode(order, false);
//                 temp->children[0] = root;

//                 split(temp, 0);
//                 root = temp;
//             }

//             currentlynotfull(root, data);
//         }
//     }

//     void split(BNode *node, int ind)

//     {
//         int themid = node->tot / 2;
//         // cout << "mid" << themid << endl;

//         int evenmid = (node->tot / 2) + 1;
//         // cout << "evenmid" << evenmid << endl;

//         BNode *newchld = node->children[ind];
//         BNode *temp = new BNode(order, newchld->f);

//         for (int i = evenmid; i < newchld->tot; i++)

//         {
//             temp->key[temp->tot] = newchld->key[i];
//             temp->tot++;
//         }

//         if (!newchld->f)

//         {
//             for (int i = evenmid; i <= newchld->tot; i++)
//             {
//                 temp->children[i - themid - 1] = newchld->children[i];
//             }
//         }

//         newchld->tot = themid;

//         for (int i = node->tot; i > ind; i--)
//         {
//             node->children[i + 1] = node->children[i];
//         }
//         node->children[ind + 1] = temp;

//         for (int i = node->tot - 1; i >= ind; i--)

//         {
//             node->key[i + 1] = node->key[i];
//         }
//         node->key[ind] = newchld->key[themid];
//         node->tot++;
//     }

//     void currentlynotfull(BNode *node, int data)
//     {
//         int i = node->tot - 1;

//         if (node->f)
//         {
//             while (i >= 0 && data < node->key[i])
//             {
//                 node->key[i + 1] = node->key[i];
//                 i--;
//             }
//             node->key[i + 1] = data;
//             node->tot++;

//             /* cout << "nserted " << data << endl;
//              for (int j = 0; j < node->tot; j++)
//              {
//                  cout << node->key[j] << " ";

//              }
//              cout << endl;*/
//         }
//         else
//         {

//             while (i >= 0 && data < node->key[i])
//             {
//                 i--;
//             }
//             i++;

//             if (node->children[i]->tot == order - 1)
//             {

//                 // cout << "slpitig at " << i << endl;
//                 split(node, i);
//                 if (data > node->key[i])

//                 {
//                     i++;
//                 }
//             }

//             currentlynotfull(node->children[i], data);
//         }
//     }

//     // Existing insert method remains the same as in previous implementation

//     // New delete method
//     void remove(int data)
//     {
//         if (root == NULL)
//             return;
//         deleteKey(root, data);
//     }

//     // Inorder traversal
//     void inorder()
//     {
//         inorderTraversal(root);
//         cout << endl;
//     }

//     // Preorder traversal
//     void preorder()
//     {
//         preorderTraversal(root);
//         cout << endl;
//     }

//     // Postorder traversal
//     void postorder()
//     {
//         postorderTraversal(root);
//         cout << endl;
//     }

//     // Level order traversal
//     void levelorder()
//     {
//         if (root == NULL)
//             return;

//         queue<BNode *> q;
//         q.push(root);

//         while (!q.empty())
//         {
//             int levelSize = q.size();
//             for (int i = 0; i < levelSize; i++)
//             {
//                 BNode *current = q.front();
//                 q.pop();

//                 // Print keys in current node
//                 for (int j = 0; j < current->tot; j++)
//                 {
//                     cout << current->key[j] << " ";
//                 }

//                 // Add children to queue
//                 if (!current->f)
//                 {
//                     for (int j = 0; j <= current->tot; j++)
//                     {
//                         q.push(current->children[j]);
//                     }
//                 }
//             }
//             cout << endl;
//         }
//     }

//     // Search method
//     bool search(int data)
//     {
//         if (root == NULL)
//             return false;
//         return searchKey(root, data);
//     }
//     // Existing print method remains the same

//     ~BTree()
//     {
//         delete root;
//     }
// };

// // Main function to demonstrate usage
#pragma once
#include <iostream>
#include <queue>
using namespace std;

struct BNode
{
    int *key;
    BNode **children;
    int tot;
    bool f;

    BNode(int nn, bool leafing)
    {
        key = new int[nn - 1];
        children = new BNode *[nn];
        tot = 0;
        f = leafing;

        for (int i = 0; i < nn; i++)
        {
            children[i] = NULL;
        }
    }

    ~BNode()
    {
        delete[] key;

        if (!f)
        {
            for (int i = 0; i <= tot; i++)
            {
                if (children[i] != NULL)
                    delete children[i];
            }
        }
        delete[] children;
    }
};

class BTree
{
private:
    BNode *root;
    int order;

    
    int find(BNode *node, int key)
    {
        int pos = 0;
        while (pos < node->tot && node->key[pos] < key)
            pos++;
        return pos;
    }

    
    int findPredecessor(BNode *node, int idx)
    {
        BNode *current = node->children[idx];
        while (!current->f)
        {
            current = current->children[current->tot];
        }
        return current->key[current->tot - 1];
    }

    
    int findSuccessor(BNode *node, int idx)
    {
        BNode *current = node->children[idx + 1];
        while (!current->f)
        {
            current = current->children[0];
        }
        return current->key[0];
    }

    
    void fillNode(BNode *node, int idx)
    {
        
        if (idx != 0 && node->children[idx - 1]->tot > (order / 2 - 1))
        {
            borrowPrev(node, idx);
        }
        
        else if (idx != node->tot && node->children[idx + 1]->tot > (order / 2 - 1))
        {
            borrowNext(node, idx);
        }
        
        else
        {
            if (idx != node->tot)
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    
    void borrowPrev(BNode *node, int idx)
    {
        BNode *child = node->children[idx];
        BNode *sibling = node->children[idx - 1];

        
        for (int i = child->tot - 1; i >= 0; i--)
            child->key[i + 1] = child->key[i];

        
        child->key[0] = node->key[idx - 1];

        
        if (!child->f)
        {
            for (int i = child->tot; i >= 0; i--)
                child->children[i + 1] = child->children[i];
            child->children[0] = sibling->children[sibling->tot];
        }

        
        node->key[idx - 1] = sibling->key[sibling->tot - 1];

        child->tot++;
        sibling->tot--;
    }

    
    void borrowNext(BNode *node, int idx)
    {
        BNode *child = node->children[idx];
        BNode *sibling = node->children[idx + 1];

        
        child->key[child->tot] = node->key[idx];

        
        if (!child->f)
            child->children[child->tot + 1] = sibling->children[0];

        
        node->key[idx] = sibling->key[0];

        
        for (int i = 1; i < sibling->tot; i++)
            sibling->key[i - 1] = sibling->key[i];

        
        if (!sibling->f)
        {
            for (int i = 1; i <= sibling->tot; i++)
                sibling->children[i - 1] = sibling->children[i];
        }

        child->tot++;
        sibling->tot--;
    }

    
    void merge(BNode *node, int idx)
    {
        BNode *child = node->children[idx];
        BNode *sibling = node->children[idx + 1];

        
        child->key[child->tot] = node->key[idx];
        child->tot++;

        
        for (int i = 0; i < sibling->tot; i++)
            child->key[child->tot + i] = sibling->key[i];

        
        if (!child->f)
        {
            for (int i = 0; i <= sibling->tot; i++)
                child->children[child->tot + i] = sibling->children[i];
        }

        
        child->tot += sibling->tot;

        
        for (int i = idx + 1; i < node->tot; i++)
            node->key[i - 1] = node->key[i];

        
        for (int i = idx + 2; i <= node->tot; i++)
            node->children[i - 1] = node->children[i];

        node->tot--;

        
        delete sibling;

        
        if (node == root && node->tot == 0)
        {
            delete root;
            root = child;
        }
    }

    
    void deletion(BNode *node, int key)
    {
        int idx = find(node, key);

        
        if (idx < node->tot && node->key[idx] == key)
        {
            if (node->f)
            {
                
                for (int i = idx; i < node->tot - 1; i++)
                    node->key[i] = node->key[i + 1];
                node->tot--;
            }
            else
            {
                
                if (node->children[idx]->tot > (order / 2 - 1))
                {
                    
                    int pred = findPredecessor(node, idx);
                    node->key[idx] = pred;
                    deletion(node->children[idx], pred);
                }
                else if (node->children[idx + 1]->tot > (order / 2 - 1))
                {
                    
                    int succ = findSuccessor(node, idx);
                    node->key[idx] = succ;
                    deletion(node->children[idx + 1], succ);
                }
                else
                {
                    
                    merge(node, idx);
                    deletion(node, key);
                }
            }
        }
        else
        {
            
            if (node->f)
                return; 

            
            bool lastChild = (idx == node->tot);
            BNode *targetChild = node->children[lastChild ? idx - 1 : idx];

            
            if (targetChild->tot == (order / 2 - 1))
            {
                fillNode(node, lastChild ? idx - 1 : idx);
            }

            
            if (lastChild && idx > node->tot)
                deletion(node->children[idx - 1], key);
            else
                deletion(node->children[idx], key);
        }
    }

    
    void inorderTraversal(BNode *node)
    {
        if (node == NULL)
            return;

        for (int i = 0; i < node->tot; i++)
        {
            if (!node->f)
                inorderTraversal(node->children[i]);
            cout << node->key[i] << " ";
        }

        if (!node->f)
            inorderTraversal(node->children[node->tot]);
    }

public:
    BTree(int n)
    {
        root = NULL;
        order = n;
    }

    
    void insert(int data)
    {
        if (root == NULL)
        {
            root = new BNode(order, true);
            root->key[0] = data;
            root->tot = 1;
        }
        else
        {
            if (root->tot == order - 1)
            {
                BNode *temp = new BNode(order, false);
                temp->children[0] = root;

                split(temp, 0);
                root = temp;
            }

            currentlynotfull(root, data);
        }
    }

    
    void split(BNode *node, int ind)
    {
        int themid = node->tot / 2;
        int evenmid = (node->tot / 2) + 1;

        BNode *newchld = node->children[ind];
        BNode *temp = new BNode(order, newchld->f);

        for (int i = evenmid; i < newchld->tot; i++)
        {
            temp->key[temp->tot] = newchld->key[i];
            temp->tot++;
        }

        if (!newchld->f)
        {
            for (int i = evenmid; i <= newchld->tot; i++)
            {
                temp->children[i - themid - 1] = newchld->children[i];
            }
        }

        newchld->tot = themid;

        for (int i = node->tot; i > ind; i--)
        {
            node->children[i + 1] = node->children[i];
        }
        node->children[ind + 1] = temp;

        for (int i = node->tot - 1; i >= ind; i--)
        {
            node->key[i + 1] = node->key[i];
        }
        node->key[ind] = newchld->key[themid];
        node->tot++;
    }

    void currentlynotfull(BNode *node, int data)
    {
        int i = node->tot - 1;

        if (node->f)
        {
            while (i >= 0 && data < node->key[i])
            {
                node->key[i + 1] = node->key[i];
                i--;
            }
            node->key[i + 1] = data;
            node->tot++;
        }
        else
        {
            while (i >= 0 && data < node->key[i])
            {
                i--;
            }
            i++;

            if (node->children[i]->tot == order - 1)
            {
                split(node, i);
                if (data > node->key[i])
                {
                    i++;
                }
            }

            currentlynotfull(node->children[i], data);
        }
    }

    
    void remove(int key)
    {
        if (root == NULL)
            return;

        
        deletion(root, key);

        
        if (root->tot == 0 && !root->f)
        {
            BNode *oldRoot = root;
            root = root->children[0];
            delete oldRoot;
        }
    }

    
    void inorder()
    {
        inorderTraversal(root);
        cout << endl;
    }

    
};

