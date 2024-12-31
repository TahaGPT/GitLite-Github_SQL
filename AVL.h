#include <iostream>
#include "Node.h"
#include "link.h"
#include "SHA256.h"
using namespace std;

int cols = 0;
int rows = 0;

class AVL
{
public:
    Node *root;
    string path;
    bool sha;
    int modulo;
    string different;
    string deleted = "";
    AVL(string foldername, bool allow) : path(foldername), sha(allow)
    {
        different = computeSHA256("Hackie Chan");
        if (!sha)
        {
            modulo = (different.length()) % 29;
        }
        else
        {
            modulo = 0;
        }
        // cout << "AVL : " << foldername << " with Hash : " << different << endl;
        root = NULL;
    }

    AVL(const AVL &other)
    {
        path = other.path;
        sha = other.sha;
        modulo = other.modulo;
        different = other.different;
        deleted = other.deleted;
        root = copyTree(other.root);
        inOrderCreation(root);
    }

    Node *copyTree(Node *node)
    {
        if (!node)
            return nullptr;
        Node *thenewnode = new Node(*node);
        thenewnode->left = copyTree(node->left);
        thenewnode->right = copyTree(node->right);
        return thenewnode;
    }

    void inOrderCreation(Node *node)
    {
        if (node)
        {
            inOrderCreation(node->left);
            cout << "Setting Path for " << path << endl;
            node->setMainPath(path);
            inOrderCreation(node->right);
        }
    }
    void save(Node *node)
    {
        if (node)
        {
            save(node->left);
            cout << "Setting Path for " << path << endl;
            node->saveToFile();
            save(node->right);
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

    AVL &operator=(const AVL &other)
    {
        if (this == &other)
            return *this; // Avoid self-assignment

        deleteSubtree(root); // Free current resources
        sha = other.sha;
        deleted = other.deleted;
        modulo = other.modulo;
        different = other.different;
        root = copyTree(other.root); // Deep copy the other tree
        cout << "copying Paths\n";
        inOrderCreation(root);
        return *this;
    }

    // void RangeSearch(string start, string end)
    // {
    //     theRangeSearch(root, start, end);
    // }
    // void theRangeSearch(Node *root, string &start, string &end)
    // {

    //     SLinkedList list;

    //     if (root == NULL)
    //     {
    //         return;
    //     }

    //     // Range search using string comparison
    //     if (root->data >= start && root->data <= end)
    //     {
    //         list.insert(root->data);
    //     }

    //     // Recurse to the left and right
    //     theRangeSearch(root->left, start, end);
    //     theRangeSearch(root->right, start, end);
    // }

    // // void strpatternSearch(string start, string end)
    // // {
    // //     // Call the PatternSearcher function, passing the root and range (start, end)
    // //     PatternSearcher(root, start, end);
    // // }

    // // void PatternSearcher(Node *root, string start, string end)
    // // {
    // //     // This list will collect the results of the pattern search
    // //     SLinkedList list;

    // //     if (root == NULL)
    // //     {
    // //         return;
    // //     }

    // //     // Check if the data falls within the range
    // //     if (root->data.substr(0, start.size()) == start && root->data.substr(root->data.size() - end.size()) == end)
    // //     {
    // //         list.insert(root->data); // Add matching node's data to the linked list
    // //     }

    // //     // Continue searching recursively in the left and right subtrees
    // //     PatternSearcher(root->left, start, end);
    // //     PatternSearcher(root->right, start, end);

    // //     // Print out the list of found data (if you want to see the results)
    // //    // list.print(); // Assuming print() is implemented in the SLinkedList class
    // // }

    // void strpatternSearch(const string &pattern)
    // {
    //     // Call the PatternSearcher function, passing the root and the pattern
    //     PatternSearcher(root, pattern);
    // }

    // void PatternSearcher(Node *root, const string &pattern)
    // {
    //     // This list will collect the results of the pattern search
    //     SLinkedList list;

    //     if (root == NULL)
    //     {
    //         return;
    //     }

    //     // Check if the data contains the pattern
    //     if (root->data.find(pattern) != string::npos)
    //     {
    //         list.insert(root->data); // Add matching node's data to the linked list
    //     }

    //     // Continue searching recursively in the left and right subtrees
    //     PatternSearcher(root->left, pattern);
    //     PatternSearcher(root->right, pattern);

    //     // Print out the list of found data (if you want to see the results)
    // }

    // bool isMatching(const char *word, const char *pattern)
    // {
    //     if (*pattern == '\0')
    //     {
    //         return (*word == '\0');
    //     }

    //     if (*pattern == '%')
    //     {
    //         if (isMatching(word, pattern + 1))
    //         {
    //             return true;
    //         }

    //         if (*word != '\0' && isMatching(word + 1, pattern))
    //         {
    //             return true;
    //         }
    //     }
    //     else if (*word == *pattern)
    //     {
    //         return isMatching(word + 1, pattern + 1);
    //     }

    //     return false;
    // }

    // int findingLenght(const char *word)
    // {
    //     int length = 0;
    //     while (word[length] != '\0')
    //     {
    //         length++;
    //     }
    //     return length;
    // }

    // //     void patternSearch(char start, char end)
    // //     {
    // //         char pattern[2] = {start, end};
    // //         thePatternSearch(root, pattern[0], pattern[1]);
    // //     }

    // //     void thePatternSearch(Node *root, char &start, char &end)

    // //     {
    // //     SLinkedList list;

    // //     // Base condition: if the root is NULL, return
    // //     if (root == NULL) {
    // //         return;
    // //     }

    // //     // If the data matches the pattern (i.e., starts with start and ends with end)
    // //     // or if there are wildcards in the start and end
    // //     if (isMatching(root->data.c_str(), "%") ||  // Check if any string matches %
    // //         (root->data[0] >= start && root->data[0] <= end)) {  // Matching first character range
    // //         list.insert(root->data);
    // //     }

    // //     // Recursive calls for left and right subtrees
    // //     thePatternSearch(root->left, start, end);
    // //     thePatternSearch(root->right, start, end);
    // // }

    // void patternSearch(const string &pattern)
    // {
    //     // This will collect the results of the pattern search
    //     SLinkedList list;

    //     thePatternSearch(root, pattern, list);

    //     // Optionally print or handle the resulting list
    //     // list.print();  // Assuming print() is implemented in SLinkedList
    // }

    // void thePatternSearch(Node *root, const string &pattern, SLinkedList &list)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     // If the current node's data matches the pattern
    //     if (isMatchingPattern(root->data, pattern))
    //     {
    //         list.insert(root->data);
    //     }

    //     // Recur for left and right children
    //     thePatternSearch(root->left, pattern, list);
    //     thePatternSearch(root->right, pattern, list);
    // }

    // bool isMatchingPattern(const string &word, const string &pattern)
    // {
    //     size_t wLen = word.size(), pLen = pattern.size();
    //     size_t wIdx = 0, pIdx = 0;

    //     while (wIdx < wLen && pIdx < pLen)
    //     {
    //         if (pattern[pIdx] == '%')
    //         {
    //             // Skip continuous % characters in the pattern
    //             while (pIdx < pLen && pattern[pIdx] == '%')
    //             {
    //                 ++pIdx;
    //             }
    //             // If % is at the end of the pattern, match the rest of the word
    //             if (pIdx == pLen)
    //                 return true;

    //             // Attempt to match the rest of the pattern
    //             while (wIdx < wLen && word[wIdx] != pattern[pIdx])
    //             {
    //                 ++wIdx;
    //             }
    //         }
    //         else if (word[wIdx] == pattern[pIdx])
    //         {
    //             // Characters match, move to the next character
    //             ++wIdx;
    //             ++pIdx;
    //         }
    //         else
    //         {
    //             return false; // Mismatch
    //         }
    //     }

    //     // Ensure both word and pattern are fully consumed
    //     return wIdx == wLen && pIdx == pLen;
    // }

    // bool compare(const string &a, const string &b)
    // {
    //     size_t i = 0;
    //     while (i < a.length() && i < b.length())
    //     {
    //         if (a[i] < b[i])
    //             return true;
    //         if (a[i] > b[i])
    //             return false;
    //         i++;
    //     }
    //     return a.length() < b.length();
    // }

    // // Function to check if a value is within the range [start, end]
    // bool isInRange(const string &value, const string &start, const string &end)
    // {
    //     return !compare(value, start) && !compare(end, value);
    // }
    // // Range search function
    // void ranger(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     if (isInRange(root->data, start, end))
    //     {
    //         list.insert(root->data);
    //     }

    //     ranger(root->left, start, end, list);
    //     ranger(root->right, start, end, list);
    // }

    // // Wrapper function for range search
    // void rangeSearch(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     ranger(root, start, end, list);
    // } // Range search function
    // void ranger(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     if (isInRange(root->data, start, end))
    //     {
    //         list.insert(root->data);
    //     }

    //     ranger(root->left, start, end, list);
    //     ranger(root->right, start, end, list);
    // }

    // // Wrapper function for range search
    // void Searching(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     ranger(root, start, end, list);
    // }

    // void rangeSearch(string start, string end)
    // {
    //     SLinkedList list;
    //     Searching(root, start, end, list);
    //     // list.print();
    // }

    // void RangeSearch(string start, string end)
    // {
    //     theRangeSearch(root, start, end);
    // }
    // void theRangeSearch(Node *root, string &start, string &end)
    // {

    //     SLinkedList list;

    //     if (root == NULL)
    //     {
    //         return;
    //     }

    //     // Range search using string comparison
    //     if (root->data >= start && root->data <= end)
    //     {
    //         list.insert(root->data);
    //     }

    //     // Recurse to the left and right
    //     theRangeSearch(root->left, start, end);
    //     theRangeSearch(root->right, start, end);
    // }

    // void strpatternSearch(const string &pattern)
    // {
    //     // Call the PatternSearcher function, passing the root and the pattern
    //     PatternSearcher(root, pattern);
    // }

    // void PatternSearcher(Node *root, const string &pattern)
    // {
    //     // This list will collect the results of the pattern search
    //     SLinkedList list;

    //     if (root == NULL)
    //     {
    //         return;
    //     }

    //     // Check if the data contains the pattern
    //     if (root->data.find(pattern) != string::npos)
    //     {
    //         list.insert(root->data); // Add matching node's data to the linked list
    //     }

    //     // Continue searching recursively in the left and right subtrees
    //     PatternSearcher(root->left, pattern);
    //     PatternSearcher(root->right, pattern);

    //     // Print out the list of found data (if you want to see the results)
    // }

    // void Visualize(Node *root, bool right, string spacing = "")
    // {
    //     if (root != nullptr)
    //     {
    //         cout << spacing;
    //         if (right)
    //         {
    //             cout << "R--------------";
    //             spacing += "           ";
    //         }
    //         else
    //         {
    //             cout << "L--------------";
    //             spacing += "|          ";
    //         }

    //         // Print node data and height
    //         cout << root->data << "(H=" << root->height << ")" << endl;

    //         // Recursive calls for left and right children
    //         Visualize(root->left, false, spacing);
    //         Visualize(root->right, true, spacing);
    //     }
    // }

    // void visualize()
    // {
    //     if (root)
    //         Visualize(root, true);
    // }

    void Visualize(Node *root, bool last, string spacing = "")
    {
        if (root != nullptr)
        {
            cout << spacing;

            // Print the branch direction and update spacing
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

            // Print node data and height
            cout << root->data << "(H=" << root->height << ")" << endl;

            // Recursive calls for children
            Visualize(root->left, false, spacing); // Left child
            Visualize(root->right, true, spacing); // Right child
        }
    }

    void visualize()
    {
        if (root)
            Visualize(root, true);
    }

    void RangeSearch(string start, string end)
    {
        SLinkedList list;
        theRangeSearch(root, start, end, list);
    }

    void theRangeSearch(Node *root, const string &start, const string &end, SLinkedList &list)
    {
        if (root == NULL)
        {
            return;
        }

        // Check if current node is within the range and add it to the list
        if (root->data >= start && root->data <= end)
        {
            list.insert(root->data);
        }

        // Recur for the left subtree only if root->data > start
        if (root->data > start)
        {
            theRangeSearch(root->left, start, end, list);
        }

        // Recur for the right subtree only if root->data < end
        if (root->data < end)
        {
            theRangeSearch(root->right, start, end, list);
        }
    }
    void strpatternSearch(const string &pattern)
    {
        // Call the PatternSearcher function, passing the root and the pattern
        PatternSearcher(root, pattern);
    }

    void PatternSearcher(Node *root, const string &pattern)
    {
        // This list will collect the results of the pattern search
        SLinkedList list;

        if (root == NULL)
        {
            return;
        }

        string prefix = pattern.substr(0, pattern.size() - 1);
        // Check if the data contains the pattern
        if (root->data.find(prefix) == 0)
        {
            list.insert(root->data); // Add matching node's data to the linked list
        }

        // Continue searching recursively in the left and right subtrees
        PatternSearcher(root->left, pattern);
        PatternSearcher(root->right, pattern);

        // Print out the list of found data (if you want to see the results)
    }
    void patternSearch(const string &pattern)
    {
        // This will collect the results of the pattern search
        SLinkedList list;

        thePatternSearch(root, pattern, list);

        // Optionally print or handle the resulting list
        // list.print();  // Assuming print() is implemented in SLinkedList
    }

    void thePatternSearch(Node *root, const string &pattern, SLinkedList &list)
    {
        if (root == nullptr)
        {
            return;
        }

        // If the current node's data matches the pattern
        if (isMatchingPattern(root->data, pattern))
        {
            list.insert(root->data);
        }

        // Recur for left and right children
        thePatternSearch(root->left, pattern, list);
        thePatternSearch(root->right, pattern, list);
    }

    bool isMatchingPattern(const string &word, const string &pattern)
    {
        size_t wLen = word.size(), pLen = pattern.size();
        size_t wIdx = 0, pIdx = 0;

        while (wIdx < wLen && pIdx < pLen)
        {
            if (pattern[pIdx] == '%')
            {
                // Skip continuous % characters in the pattern
                while (pIdx < pLen && pattern[pIdx] == '%')
                {
                    ++pIdx;
                }
                // If % is at the end of the pattern, match the rest of the word
                if (pIdx == pLen)
                    return true;

                // Attempt to match the rest of the pattern
                while (wIdx < wLen && word[wIdx] != pattern[pIdx])
                {
                    ++wIdx;
                }
            }
            else if (word[wIdx] == pattern[pIdx])
            {
                // Characters match, move to the next character
                ++wIdx;
                ++pIdx;
            }
            else
            {
                return false; // Mismatch
            }
        }

        // Ensure both word and pattern are fully consumed
        return wIdx == wLen && pIdx == pLen;
    }

    bool compare(const string &a, const string &b)
    {
        size_t i = 0;
        while (i < a.length() && i < b.length())
        {
            if (a[i] < b[i])
                return true;
            if (a[i] > b[i])
                return false;
            i++;
        }
        return a.length() < b.length();
    }

    // Function to check if a value is within the range [start, end]
    bool isInRange(const string &value, const string &start, const string &end)
    {
        return !compare(value, start) && !compare(end, value);
    }
    // Range search function
    void ranger(Node *root, const string &start, const string &end, SLinkedList &list)
    {
        if (root == nullptr)
        {
            return;
        }

        if (isInRange(root->data, start, end))
        {
            list.insert(root->data);
        }

        ranger(root->left, start, end, list);
        ranger(root->right, start, end, list);
    }

    // Wrapper function for range search
    void Searching(Node *root, const string &start, const string &end, SLinkedList &list)
    {
        ranger(root, start, end, list);
    }

    void rangeSearch(string start, string end)
    {
        SLinkedList list;
        Searching(root, start, end, list);
        // list.print();
    }

    bool updateRange(Node *root, int searcher, int columnToUpdateIndex, const string &startValue, const string &endValue, const string &modified)
    {
        if (root == NULL)
        {
            return false; // No records to update
        }

        bool updated = false;

        if (root->datas[searcher] >= startValue && root->datas[searcher] <= endValue)
        {
            root->datas[columnToUpdateIndex] = modified;

            // root->hash = hash<std::string>{}(root->datas[columnToUpdateIndex]); // Recompute hash based on updated data
            // root->mod29 = root->hash % 29;                                      // Recompute mod29 based on the updated hash

            root->saveToFile(); // Save the updated record

            updated = true;
            cout << "Updated record: " << root->datas[columnToUpdateIndex] << endl;
        }

        bool leftUpdated = updateRange(root->left, searcher, columnToUpdateIndex, startValue, endValue, modified);
        bool rightUpdated = updateRange(root->right, searcher, columnToUpdateIndex, startValue, endValue, modified);

        updated = updated || leftUpdated || rightUpdated;
        return updated;
    }

    bool compareStrings(const string &str1, const string &str2)
    {
        return str1 == str2; // Direct string comparison using the '==' operator
    }

    void copyString(string &thiss, const string &that)
    {
        thiss = that; // Directly assign the source string to the destination string
    }

    bool updateNode(Node *root, int columnToSearchIndex, int columnToChangeIndex, const std::string &searchVal, const std::string &modifiedVal)
    {
        if (root == NULL)
        {
            cout << "Node not found!" << endl;
            return false;
        }

        // Check if the search value matches the value in the specified column
        if ((root->datas[columnToSearchIndex] == searchVal))
        {
            // Update the value in the specified column
            copyString(root->datas[columnToChangeIndex], modifiedVal);

            // Recalculate the hash and mod29 (you can replace this with your hash calculation logic)
            root->hash = std::hash<std::string>{}(root->datas[columnToChangeIndex]); // Recompute hash based on updated data
            root->mod29 = root->hash % 29;                                           // Recompute mod29 based on the updated hash



            cout << "Node updated successfully!" << endl;
            return true; // Return true when the update is successful
        }

        if (searchVal < root->datas[columnToSearchIndex]) // Compare lexicographically
        {
            return updateNode(root->left, columnToSearchIndex, columnToChangeIndex, searchVal, modifiedVal);
        }
        else
        {
            return updateNode(root->right, columnToSearchIndex, columnToChangeIndex, searchVal, modifiedVal);
        }
    }

    // void patternSearch(const string &pattern)
    // {
    //     // This will collect the results of the pattern search
    //     SLinkedList list;

    //     thePatternSearch(root, pattern, list);

    //     // Optionally print or handle the resulting list
    //     // list.print();  // Assuming print() is implemented in SLinkedList
    // }

    // void thePatternSearch(Node *root, const string &pattern, SLinkedList &list)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     // If the current node's data matches the pattern
    //     if (isMatchingPattern(root->data, pattern))
    //     {
    //         list.insert(root->data);
    //     }

    //     // Recur for left and right children
    //     thePatternSearch(root->left, pattern, list);
    //     thePatternSearch(root->right, pattern, list);
    // }

    // bool isMatchingPattern(const string &word, const string &pattern)
    // {
    //     size_t wLen = word.size(), pLen = pattern.size();
    //     size_t wIdx = 0, pIdx = 0;

    //     while (wIdx < wLen && pIdx < pLen)
    //     {
    //         if (pattern[pIdx] == '%')
    //         {
    //             // Skip continuous % characters in the pattern
    //             while (pIdx < pLen && pattern[pIdx] == '%')
    //             {
    //                 ++pIdx;
    //             }
    //             // If % is at the end of the pattern, match the rest of the word
    //             if (pIdx == pLen)
    //                 return true;

    //             // Attempt to match the rest of the pattern
    //             while (wIdx < wLen && word[wIdx] != pattern[pIdx])
    //             {
    //                 ++wIdx;
    //             }
    //         }
    //         else if (word[wIdx] == pattern[pIdx])
    //         {
    //             // Characters match, move to the next character
    //             ++wIdx;
    //             ++pIdx;
    //         }
    //         else
    //         {
    //             return false; // Mismatch
    //         }
    //     }

    //     // Ensure both word and pattern are fully consumed
    //     return wIdx == wLen && pIdx == pLen;
    // }

    // bool compare(const string &a, const string &b)
    // {
    //     size_t i = 0;
    //     while (i < a.length() && i < b.length())
    //     {
    //         if (a[i] < b[i])
    //             return true;
    //         if (a[i] > b[i])
    //             return false;
    //         i++;
    //     }
    //     return a.length() < b.length();
    // }

    // // Function to check if a value is within the range [start, end]
    // bool isInRange(const string &value, const string &start, const string &end)
    // {
    //     return !compare(value, start) && !compare(end, value);
    // }
    // // Range search function
    // void ranger(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     if (root == nullptr)
    //     {
    //         return;
    //     }

    //     if (isInRange(root->data, start, end))
    //     {
    //         list.insert(root->data);
    //     }

    //     ranger(root->left, start, end, list);
    //     ranger(root->right, start, end, list);
    // }

    // // Wrapper function for range search
    // void Searching(Node *root, const string &start, const string &end, SLinkedList &list)
    // {
    //     ranger(root, start, end, list);
    // }

    // void rangeSearch(string start, string end)
    // {
    //     SLinkedList list;
    //     Searching(root, start, end, list);
    //     // list.print();
    // }

    int normalize(int a, int b)
    {
        return a >= b ? a : b;
    }

    Node *myInsert(Node *&curr, string d, size_t HashOfData, string *list, int c, int r)
    {
        if (curr == NULL)
        {
            curr = new Node(d, HashOfData, list, c, path, r, different, modulo);
            cout << "No Segementation Fault for " << d << endl;
        }
        else if (HashOfData < curr->hash)
        {
            curr->left = myInsert(curr->left, d, HashOfData, list, c, r);
            // curr->left->setParentPath(curr->myPath);
            cout << "Parent set for " << d << endl;
            curr->setLeftChildPath(curr->left->myPath);
            cout << "Left Child set for " << curr->data << endl;

            if (getHeight(curr->left) - getHeight(curr->right) >= 2)
            {
                if (HashOfData < curr->left->hash)
                {
                    curr = SRL(curr);
                }
                else
                {
                    curr = DRL(curr);
                }
            }
        }

        else
        {
            curr->right = myInsert(curr->right, d, HashOfData, list, c, r);
            // curr->right->setParentPath(curr->myPath);
            cout << "Parent set for " << d << endl;
            curr->setRightChildPath(curr->right->myPath);
            cout << "Right Child set for " << curr->data << endl;

            if (getHeight(curr->right) - getHeight(curr->left) >= 2)
            {
                if (HashOfData >= curr->right->hash)
                {
                    curr = SRR(curr);
                }
                else
                {
                    curr = DRR(curr);
                }
            }
        }

        curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
        return curr;
    }

    // Node *myInsert(Node *&curr, string d, size_t HashOfData, string *list, int c, int r)
    // {
    //    if (curr == NULL)
    //    {
    //        // Create a new node
    //        curr = new Node(d, HashOfData, list, c, path, r);
    //        cout << "Node created for " << d << " with hash " << HashOfData << endl;
    //        return curr;
    //    }

    //    if (HashOfData < curr->hash)
    //    {
    //        // Insert into the left subtree
    //        if (curr->left == NULL)
    //        {
    //            curr->left = new Node(d, HashOfData, list, c, path, r);
    //            cout << "Node created for " << d << " with hash " << HashOfData << endl;
    //         //    curr->left->setParentPath(curr->myPath);    // Set parent for the newly created node
    //            curr->setLeftChildPath(curr->left->myPath); // Update current node's left child path
    //            cout << "Left child and parent set for " << d << endl;
    //        }
    //        else
    //        {
    //            curr->left = myInsert(curr->left, d, HashOfData, list, c, r);
    //        }

    //        // Perform rotations if necessary
    //        if (getHeight(curr->left) - getHeight(curr->right) >= 2)
    //        {
    //            if (HashOfData < curr->left->hash)
    //            {
    //                curr = SRL(curr); // Single Right Rotation
    //            }
    //            else
    //            {
    //                curr = DRL(curr); // Double Right Rotation
    //            }
    //        }
    //    }
    //    else if (HashOfData > curr->hash)
    //    {
    //        // Insert into the right subtree
    //        if (curr->right == NULL)
    //        {
    //            curr->right = new Node(d, HashOfData, list, c, path, r);
    //            cout << "Node created for " << d << " with hash " << HashOfData << endl;
    //         //    curr->right->setParentPath(curr->myPath);     // Set parent for the newly created node
    //            curr->setRightChildPath(curr->right->myPath); // Update current node's right child path
    //            cout << "Right child and parent set for " << d << endl;
    //        }
    //        else
    //        {
    //            curr->right = myInsert(curr->right, d, HashOfData, list, c, r);
    //        }

    //        // Perform rotations if necessary
    //        if (getHeight(curr->right) - getHeight(curr->left) >= 2)
    //        {
    //            if (HashOfData >= curr->right->hash)
    //            {
    //                curr = SRR(curr); // Single Left Rotation
    //            }
    //            else
    //            {
    //                curr = DRR(curr); // Double Left Rotation
    //            }
    //        }
    //    }

    //    // Update height of the current node
    //    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    //    return curr;
    // }

    // Node* myInsert(Node*& curr, string d, size_t HashOfData, string* list, int c, int r) {
    //     if (curr == nullptr) {
    //         curr = new Node(d, HashOfData, list, c, path, r);
    //         cout << "Node created for " << d << " with hash " << HashOfData << endl;
    //         return curr;
    //     }

    //     if (HashOfData < curr->hash) {
    //         curr->left = myInsert(curr->left, d, HashOfData, list, c, r);

    //         // Perform rotations if necessary
    //         if (getHeight(curr->left) - getHeight(curr->right) >= 2) {
    //             if (HashOfData < curr->left->hash) {
    //                 curr = SRL(curr);
    //             }
    //             else {
    //                 curr = DRL(curr);
    //             }
    //         }
    //     }
    //     else if (HashOfData > curr->hash) {
    //         curr->right = myInsert(curr->right, d, HashOfData, list, c, r);

    //         // Perform rotations if necessary
    //         if (getHeight(curr->right) - getHeight(curr->left) >= 2) {
    //             if (HashOfData >= curr->right->hash) {
    //                 curr = SRR(curr);
    //             }
    //             else {
    //                 curr = DRR(curr);
    //             }
    //         }
    //     }

    //     // Update height
    //     curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    //     // Update paths for the current node and its children
    //     updatePaths(curr);

    //     return curr;
    // }

    int getHeight(Node *node)
    {
        return (node == NULL) ? -1 : node->height;
    }

    void insert(string d, string *arr, int c, int r)
    {
        // if (root)
        // {
        //     root->setParentPath("");
        // }
        string temp = d;
        // for (int i = 0; i < c; i++)
        // {
        //     temp += *(arr + i);
        // }
        size_t HashOfData = std::hash<string>{}(temp);
        myInsert(root, d, HashOfData, arr, c, r);
    }

    int getBalance(Node *N)
    {
        if (N == NULL)
        {
            return 0;
        }

        int leftHeight = (N->left == NULL) ? -1 : N->left->height;
        int rightHeight = (N->right == NULL) ? -1 : N->right->height;

        return leftHeight - rightHeight;
    }

    // Node *myDeletion(Node *&root, string key)
    // {
    //     size_t HashOfData = std::hash<string>{}(key);

    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     if (HashOfData < root->hash)
    //         root->left = myDeletion(root->left, key);
    //     else if (HashOfData > root->hash)
    //         root->right = myDeletion(root->right, key);
    //     else
    //     {
    //         if ((root->left == NULL) || (root->right == NULL))
    //         {
    //             Node *temp = root->left ? root->left : root->right;
    //             if (temp == NULL)
    //             {
    //                 temp = root;

    //                 root = NULL;
    //             }
    //             else
    //                 *root = *temp;
    //             delete temp;
    //         }
    //         else
    //         {
    //             Node *temp = mininode(root->right);
    //             root->data = temp->data;
    //             root->hash = temp->hash;
    //             root->right = myDeletion(root->right, temp->data);
    //         }
    //     }

    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //     int balance = getBalance(root);

    //     if (balance > 1 && getBalance(root->left) >= 0)
    //         return SRL(root);

    //     if (balance > 1 && getBalance(root->left) < 0)
    //     {
    //         //root->left = SRR(root->left);
    //         return DRL(root);
    //     }

    //     if (balance < -1 && getBalance(root->right) <= 0)
    //         return SRR(root);

    //     if (balance < -1 && getBalance(root->right) > 0)
    //     {
    //         //root->right = SRL(root->right);
    //         return DRR(root);
    //     }

    //     return root;
    // }

    // Node *mininode(Node *node)
    // {
    //     Node *current = node;
    //     while (current->left != NULL)
    //         current = current->left;
    //     return current;
    // }

    //     Node* myDeletion(Node*& root, string key)
    // {
    //     size_t HashOfData = std::hash<string>{}(key);

    //     // If tree is empty
    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     // Locate the node to be deleted
    //     if (HashOfData < root->hash)
    //         root->left = myDeletion(root->left, key);
    //     else if (HashOfData > root->hash)
    //         root->right = myDeletion(root->right, key);
    //     else
    //     {
    //         // Node with the key found
    //         // Case 1: No child or one child
    //         if (root->left == NULL || root->right == NULL)
    //         {
    //             Node* temp = root->left ? root->left : root->right;

    //             // No child case
    //             if (temp == NULL)
    //             {
    //                 temp = root;
    //                 root = NULL;
    //             }
    //             // One child case
    //             else
    //             {
    //                 *root = *temp;  // Copy the contents of the non-null child
    //             }

    //             delete temp;
    //         }
    //         // Case 2: Two children
    //         else
    //         {
    //             // Find in-order successor (smallest in right subtree)
    //             Node* successor = mininode(root->right);

    //             // Copy successor's data to this node
    //             root->data = successor->data;
    //             root->hash = successor->hash;

    //             // Delete the successor
    //             root->right = myDeletion(root->right, successor->data);
    //         }
    //     }

    // If the tree had only one node, return
    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     // Update height of current node
    //     root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //     // Balance the tree
    //     int balance = getBalance(root);

    //     // Left Heavy
    //     if (balance > 1)
    //     {
    //         if (getBalance(root->left) >= 0)
    //             return SRL(root);  // Left-Left case
    //         else
    //             return DRL(root);  // Left-Right case
    //     }

    //     // Right Heavy
    //     if (balance < -1)
    //     {
    //         if (getBalance(root->right) <= 0)
    //             return SRR(root);  // Right-Right case
    //         else
    //             return DRR(root);  // Right-Left case
    //     }

    //     return root;
    // }

    // Find the minimum node in a subtree (leftmost node)
    // Node* mininode(Node* node)
    // {
    //     Node* current = node;
    //     while (current->left != NULL)
    //         current = current->left;
    //     return current;
    // }

    // void preOrder(Node *root)
    // {
    //     if (root != NULL)
    //     {
    //         cout << root->data << " ";
    //         preOrder(root->left);
    //         preOrder(root->right);
    //     }
    // }

    // void deletion(string d)
    // {
    //     myDeletion(root, d);
    // }

    // Node *SRL(Node *haha)
    // {
    //     if (haha == NULL || haha->left == NULL)
    //     {

    //         return haha;
    //     }
    //     Node *hehe = haha->left;
    //     haha->left = hehe->right;
    //     hehe->right = haha;
    //     haha->height = max(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = max(getHeight(hehe->left), getHeight(hehe->right)) + 1;
    //     return hehe;
    // }

    // Node *DRL(Node *haha)
    // {
    //     haha->left = SRR(haha->left);
    //     return SRL(haha);
    // }

    // Node *SRR(Node *haha)
    // {
    //     if (haha == NULL || haha->right == NULL)
    //     {
    //         return haha;
    //     }

    //     Node *hehe = haha->right;

    //     haha->right = hehe->left;
    //     hehe->left = haha;

    //     haha->height = max(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = max(getHeight(hehe->left), getHeight(hehe->right)) + 1;

    //     return hehe;
    // }

    // Node *DRR(Node *haha)
    // {
    //     haha->right = SRL(haha->right);
    //     return SRR(haha);
    // }

    // void inorder(Node *haha)
    // {
    //     if (haha == NULL)
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         inorder(haha->left);
    //        // cout << haha->data << " ";
    //         cout << haha->data << " | " << haha->hash << ",  ";

    //         inorder(haha->right);
    //     }
    // }

    // bool search(string d)
    // {
    //     size_t HashOfData = std::hash<string>{}(d);

    //     Node *temp = root;
    //     while (temp != NULL)
    //     {
    //         if (temp->hash == HashOfData)
    //         {
    //             return true;
    //         }
    //         else if (temp->hash > HashOfData)
    //         {
    //             temp = temp->left;
    //         }
    //         else
    //         {
    //             temp = temp->right;
    //         }
    //     }
    //     return false;
    // }

    // Node *myDeletion(Node *&root, string sth)
    // {
    //     size_t key = hash<string>{}(sth);
    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     if (key < root->hash)
    //         root->left = myDeletion(root->left, sth);
    //     else if (key > root->hash)
    //         root->right = myDeletion(root->right, sth);
    //     else
    //     {
    //         if ((root->left == NULL) || (root->right == NULL))
    //         {
    //             Node *temp = root->left ? root->left : root->right;
    //             if (temp == NULL)
    //             {
    //                 temp = root;
    //                 root = NULL;
    //             }
    //             else
    //                 *root = *temp;
    //             // 5. Deleting a File
    //             if (remove((temp->myPath).c_str()) == 0)
    //             {
    //                 cout << "\nFile '" << temp->myPath << "' deleted successfully." << endl;
    //             }
    //             else
    //             {
    //                 cout << "\nError deleting file!" << endl;
    //             }
    //             delete temp;

    //         }
    //         else
    //         {
    //             Node *temp = mininode(root->left);
    //             root->hash = temp->hash;
    //             root->data = temp->data;
    //             root->left = myDeletion(root->left, temp->data);
    //         }
    //     }

    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //     int balance = getBalance(root);

    //     if (balance > 1 && getBalance(root->left) >= 0)
    //         return SRR(root);

    //     if (balance > 1 && getBalance(root->left) < 0)
    //     {
    //         root->left = SRL(root->left);
    //         return SRR(root);
    //     }

    //     if (balance < -1 && getBalance(root->right) <= 0)
    //         return SRL(root);

    //     if (balance < -1 && getBalance(root->right) > 0)
    //     {
    //         root->right = SRR(root->right);
    //         return SRL(root);
    //     }

    //     return root;
    // }

    // Node *myDeletion(Node *&root, string sth)
    // {
    //     if (root == NULL)
    //     {
    //         return root;
    //     }
    //     size_t key = hash<string>{}(sth);
    //     size_t searcher = std::hash<string>{}(root->data);

    //     if (key < searcher)
    //     {
    //         cout << "Searching left" << endl;
    //         root->left = myDeletion(root->left, sth);
    //         if (root->left)
    //         {
    //             root->setLeftChildPath(root->left->myPath);
    //         }
    //         else
    //         {
    //             root->setLeftChildPath("");
    //         }
    //     }
    //     else if (key > searcher)
    //     {
    //         cout << "Searching right" << endl;
    //         root->right = myDeletion(root->right, sth);
    //         if (root->right)
    //         {
    //             root->setRightChildPath(root->right->myPath);
    //         }
    //         else{
    //             root->setRightChildPath("");
    //         }
    //     }

    //     else
    //     {
    //         cout << "file Found" << endl;
    //         if ((root->left == NULL) || (root->right == NULL))
    //         {
    //             Node *temp = root->left ? root->left : root->right;

    //             // Case of leaf node or node with one child
    //             if (temp == NULL)
    //             {
    //                 temp = root;
    //                 root = NULL;
    //             }
    //             else
    //             {
    //             cout << "File Deletion\n";
    //                 cout << "Node with one child" << endl;
    //                 // Before copying contents, store the paths
    //                 string oldPath = root->myPath;
    //                 root->data = temp->data;
    //                 root->hash = temp->hash;
    //                 for (int i = 0; i < cols; i++)
    //                 {
    //                     root->datas[i] = temp->datas[i];
    //                 }

    //                     // Restore the original path for the current node
    //                     root->myPath = oldPath;

    //                 // Update child paths for the new position
    //                 if (root->left)
    //                     root->setLeftChildPath(root->left->myPath);
    //                 if (root->right)
    //                     root->setRightChildPath(root->right->myPath);
    //             }

    //             // Delete the file
    //             if (temp->myPath != "" && filesystem::exists(temp->myPath))
    //             {
    //                 filesystem::remove(temp->myPath);
    //             }
    //             else
    //             {
    //                 cout << "\nError deleting file!" << endl;
    //             }
    //             cout << "Deleted file: " << temp->myPath << endl;
    //             delete temp;
    //         }
    //         else
    //         {
    //             // Node with two children
    //             Node *temp = mininode(root->left);

    //             // Store old paths before updating
    //             string oldPath = root->myPath;
    //             string oldLeftPath = root->left ? root->left->myPath : "";
    //             string oldRightPath = root->right ? root->right->myPath : "";

    //             root->data = temp->data;
    //             root->hash = temp->hash;
    //             for (int i = 0; i < cols; i++)
    //             {
    //                 root->datas[i] = temp->datas[i];
    //             }

    //             // Restore paths
    //             root->myPath = oldPath;
    //             if (root->left)
    //                 root->setLeftChildPath(oldLeftPath);
    //             if (root->right)
    //                 root->setRightChildPath(oldRightPath);

    //             root->left = myDeletion(root->left, temp->data);
    //         }
    //     }

    //     if (root == NULL)
    //     {
    //         return root;
    //     }

    //     // Update height
    //     root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //     // Get balance factor
    //     int balance = getBalance(root);

    //     // Left Left Case
    //     if (balance > 1 && getBalance(root->left) >= 0)
    //         return SRR(root);

    //     // Left Right Case
    //     if (balance > 1 && getBalance(root->left) < 0)
    //     {
    //         root->left = SRL(root->left);
    //         return SRR(root);
    //     }

    //     // Right Right Case
    //     if (balance < -1 && getBalance(root->right) <= 0)
    //         return SRL(root);

    //     // Right Left Case
    //     if (balance < -1 && getBalance(root->right) > 0)
    //     {
    //         root->right = SRR(root->right);
    //         return SRL(root);
    //     }

    //     return root;
    // }

    Node *myDeletion(Node *&root, string sth)
    {
        if (root == NULL)
        {
            return root;
        }
        size_t key = hash<string>{}(sth);
        // size_t checker = hash<string>{}(root->data);

        if (key < root->hash)
        {
            root->left = myDeletion(root->left, sth);
            if (root->left)
            {
                root->setLeftChildPath(root->left->myPath);
            }
            else
            {
                root->setLeftChildPath("");
            }
        }
        else if (key > root->hash)
        {
            root->right = myDeletion(root->right, sth);
            if (root->right)
            {
                root->setRightChildPath(root->right->myPath);
            }
            else
            {
                root->setRightChildPath("");
            }
        }
        else
        {
            cout << "File Found" << endl;
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    root->copySh(temp);
                }
                if (!deleted.empty() && filesystem::exists(deleted))
                {
                    cout << "the file is deleted" << endl;
                    filesystem::remove(deleted);
                    // if (root && !rename(root->myPath.c_str(), tempPath.c_str()))
                    // {
                    //     cout << "File Renamed" << endl;
                    // }
                    // else
                    // {
                    //     cout << "File not Renamed" << endl;
                    // }
                    deleted = "";
                }

                delete temp;
            }
            else
            {
                Node *temp = mininode(root->left);
                deleted = root->myPath;
                root->copy(temp);
                string rot = "ll";
                if (root && !rename(root->myPath.c_str(), rot.c_str()))
                {
                    cout << "File Renamed" << endl;
                }
                else
                {
                    cout << "File not Renamed" << endl;
                }

                if (temp && !rename(temp->myPath.c_str(), root->myPath.c_str()))
                {
                    cout << "File Renamed" << endl;
                }
                else
                {
                    cout << "File not Renamed" << endl;
                }

                if (!rename(rot.c_str(), temp->myPath.c_str()))
                {
                    cout << "File Renamed" << endl;
                }
                else
                {
                    cout << "File not Renamed" << endl;
                }

                root->left = myDeletion(root->left, temp->data);
            }
        }

        if (root == NULL)
        {
            return root;
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateright(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = rotateleft(root->left);
            return rotateright(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateleft(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rotateright(root->right);
            return rotateleft(root);
        }

        return root;
    }

    Node *SRL(Node *haha)
    {
        if (haha == nullptr || haha->left == nullptr)
        {
            return haha; // Nothing to rotate
        }

        Node *hehe = haha->left;

        // Perform rotation
        haha->left = hehe->right;
        hehe->right = haha;

        // Update heights
        haha->height = max(getHeight(haha->left), getHeight(haha->right)) + 1;
        hehe->height = max(getHeight(hehe->left), getHeight(hehe->right)) + 1;

        // Update paths
        if (haha->left)
        {
            haha->setLeftChildPath(haha->left->myPath);
            // haha->left->setParentPath(haha->myPath); // Update parent of left child
        }
        else
        {
            haha->setLeftChildPath("");
        }

        if (haha->right)
            haha->setRightChildPath(haha->right->myPath);
        else
            haha->setRightChildPath("");

        if (hehe->left)
        {
            hehe->setLeftChildPath(hehe->left->myPath);
            // hehe->left->setParentPath(hehe->myPath); // Update parent of left child
        }
        else
        {
            hehe->setLeftChildPath("");
        }

        hehe->setRightChildPath(haha->myPath);
        // haha->setParentPath(hehe->myPath); // Update parent for haha

        return hehe;
    }

    // Node *SRL(Node *haha)
    // {
    //     if (haha == NULL || haha->left == NULL)
    //     {
    //         return haha;
    //     }

    //     Node *hehe = haha->left;
    //     string originalParentPath = haha->myPath;
    //     string originalLeftChildPath = hehe->myPath;

    //     // Perform rotation
    //     haha->left = hehe->right;
    //     hehe->right = haha;

    //     // Update heights
    //     haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;

    //     // Update paths while maintaining original node paths
    //     haha->myPath = originalParentPath;
    //     hehe->myPath = originalLeftChildPath;

    //     // Update child paths
    //     if (haha->left)
    //         haha->setLeftChildPath(haha->left->myPath);
    //     if (haha->right)
    //         haha->setRightChildPath(haha->right->myPath);

    //     if (hehe->left)
    //         hehe->setLeftChildPath(hehe->left->myPath);
    //     if (hehe->right)
    //         hehe->setRightChildPath(haha->myPath);

    //     return hehe;
    // }

    Node *SRR(Node *haha)
    {
        if (haha == nullptr || haha->right == nullptr)
        {
            return haha; // Nothing to rotate
        }

        Node *hehe = haha->right;

        // Perform rotation
        haha->right = hehe->left;
        hehe->left = haha;

        // Update heights
        haha->height = max(getHeight(haha->left), getHeight(haha->right)) + 1;
        hehe->height = max(getHeight(hehe->left), getHeight(hehe->right)) + 1;

        // Update paths
        if (haha->left)
        {
            haha->setLeftChildPath(haha->left->myPath);
            // haha->left->setParentPath(haha->myPath); // Update parent of left child
        }
        else
        {
            haha->setLeftChildPath("");
        }

        if (haha->right)
        {
            haha->setRightChildPath(haha->right->myPath);
            // haha->right->setParentPath(haha->myPath); // Update parent of right child
        }
        else
        {
            haha->setRightChildPath("");
        }

        if (hehe->right)
        {
            hehe->setRightChildPath(hehe->right->myPath);
            // hehe->right->setParentPath(hehe->myPath); // Update parent of right child
        }
        else
        {
            hehe->setRightChildPath("");
        }

        hehe->setLeftChildPath(haha->myPath);
        // haha->setParentPath(hehe->myPath); // Update parent for haha

        return hehe;
    }

    // Node *SRR(Node *haha)
    // {
    //     if (haha == NULL || haha->right == NULL)
    //     {
    //         return haha;
    //     }

    //     Node *hehe = haha->right;
    //     string originalParentPath = haha->myPath;
    //     string originalRightChildPath = hehe->myPath;

    //     // Perform rotation
    //     haha->right = hehe->left;
    //     hehe->left = haha;

    //     // Update heights
    //     haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;

    //     // Update paths while maintaining original node paths
    //     haha->myPath = originalParentPath;
    //     hehe->myPath = originalRightChildPath;

    //     // Update child paths
    //     if (haha->left)
    //         haha->setLeftChildPath(haha->left->myPath);
    //     if (haha->right)
    //         haha->setRightChildPath(haha->right->myPath);

    //     if (hehe->left)
    //         hehe->setLeftChildPath(haha->myPath);
    //     if (hehe->right)
    //         hehe->setRightChildPath(hehe->right->myPath);

    //     return hehe;
    // }

    Node *rotateright(Node *y)
    {
        Node *x = y->left;
        Node *tt = x->right;

        x->right = y;
        y->left = tt;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node *rotateleft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node *mininode(Node *node)
    {
        Node *current = node;
        while (current->right != NULL)
            current = current->right;
        return current;
    }

    void preOrder(Node *haha)
    {
        if (haha != NULL)
        {
            cout << haha->data << ":" << haha->hash << " ";
            preOrder(haha->left);
            preOrder(haha->right);
        }
    }

    void deletion(string d)
    {
        myDeletion(root, d);
        // if (deleted != "" && deletedNode && !rename(deletedNode->myPath.c_str(), deleted.c_str()))
        // {
        //     deleted = "";
        //     deletedNode = NULL;
        // }
        // else
        // {
        //     cout << "File not Renamed" << endl;
        // }
    }

    // Node *SRL(Node *haha)
    // {
    //     if (haha == NULL || haha->left == NULL)
    //     {

    //         return haha;
    //     }
    //     Node *hehe = haha->left;
    //     haha->left = hehe->right;
    //     hehe->right = haha;
    //     haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;
    //     return hehe;
    // }

    // Node *SRL(Node *haha)
    // {
    //     if (haha == NULL || haha->left == NULL)
    //     {
    //         return haha;
    //     }

    //     Node *hehe = haha->left;

    //     // Perform rotation
    //     haha->left = hehe->right;
    //     hehe->right = haha;

    //     // Update heights
    //     haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;

    //     // Update paths
    //     // haha->setParentPath(hehe->myPath);
    //     if (haha->left)
    //         haha->setLeftChildPath(haha->left->myPath);
    //     if (haha->right)
    //         haha->setRightChildPath(haha->right->myPath);

    //     if (hehe->left)
    //         hehe->setLeftChildPath(hehe->left->myPath);
    //     if (hehe->right)
    //         hehe->setRightChildPath(hehe->right->myPath);

    //     return hehe;
    // }

    Node *DRL(Node *haha)
    {
        haha->left = SRR(haha->left);
        return SRL(haha);
    }

    // Node *SRR(Node *haha)
    // {
    //     if (haha == NULL || haha->right == NULL)
    //     {
    //         return haha;
    //     }

    //     Node *hehe = haha->right;

    //     // Perform rotation
    //     haha->right = hehe->left;
    //     hehe->left = haha;

    //     // Update heights
    //     haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
    //     hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;

    //     // Update paths
    //     // haha->setParentPath(hehe->myPath);
    //     if (haha->left)
    //         haha->setLeftChildPath(haha->left->myPath);
    //     if (haha->right)
    //         haha->setRightChildPath(haha->right->myPath);

    //     if (hehe->left)
    //         hehe->setLeftChildPath(hehe->left->myPath);
    //     if (hehe->right)
    //         hehe->setRightChildPath(hehe->right->myPath);

    //     return hehe;
    // }

    Node *DRR(Node *haha)
    {
        haha->right = SRL(haha->right);
        return SRR(haha);
    }

    void inOrder(Node *haha)
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
            cout << haha->data << ":" << haha->hash << endl;
            inOrder(haha->right);
        }
    }

    bool search(string you)
    {
        size_t d = hash<string>{}(you);
        Node *temp = root;
        while (temp != NULL)
        {
            if (temp->hash == d)
            {
                return true;
            }
            else if (temp->hash > d)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return false;
    }

    void postOrder(Node *haha)
    {

        if (haha == NULL)
        {
            return;
        }
        else
        {
            postOrder(haha->left);
            postOrder(haha->right);
            // cout << haha->data << " ";
            cout << haha->data << ":" << haha->hash << " ";
        }
    }

    void deleteSubtree(Node *node)
    {
        if (node == nullptr)
            return;

        // Recursively delete left and right subtrees
        deleteSubtree(node->left);
        deleteSubtree(node->right);

        // Delete the current node
        delete node;
    }
    // Destructor
    ~AVL()
    {
        deleteSubtree(root);
    }
};

// #pragma once
// #include <iostream>
// #include <cmath>
// using namespace std;

// struct Node
// {
// 	int data;
// 	Node* left;
// 	Node* right;
// 	int height;

// 	Node(int d) : data(d), height(-1)
// 	{
// 		left = right = NULL;
// 	}
// };

// class AVL
// {
// private:

// public:
// 	Node* root;
// 	AVL()
// 	{
// 		root = NULL;
// 	}

// 	int normalize(int a, int b)
// 	{
// 		return a >= b ? a : b;
// 	}

// 	//Node* myInsert(Node* &curr, int d)
// 	//{
// 	//	if (curr == NULL)
// 	//	{
// 	//		curr = new Node(d);
// 	//	}
// 	//	else if (d < curr->data)
// 	//	{
// 	//		curr->left = myInsert(curr->left, d);
// 	//		if (curr->left->height - curr->right->height == 2 || curr->left->height - curr->right->height == -2)
// 	//		{
// 	//			if (d < curr->left->data)
// 	//			{
// 	//				curr = SRL(curr);
// 	//			}
// 	//			else
// 	//			{
// 	//				curr = DRL(curr);
// 	//			}
// 	//		}
// 	//	}
// 	//	else if (d > curr->data)
// 	//	{
// 	//		curr->right = myInsert(curr->right, d);
// 	//		if (curr->right->height - curr->left->height == 2 || curr->right->height - curr->left->height == -2)
// 	//		{
// 	//			if (d >= curr->right->data)
// 	//			{
// 	//				curr = SRR(curr);
// 	//			}
// 	//			else
// 	//			{
// 	//				curr = DRR(curr);
// 	//			}
// 	//		}
// 	//	}

// 	//	//curr->height = normalize(curr->left->height, curr->right->height) + 1;
// 	//	curr->height = normalize(getHeight(curr->left), getHeight(curr->right)) + 1;
// 	//	if(curr==nullptr)
// 	//		cout << "NULL\n";
// 	//	return curr;
// 	//}

// 	Node* myInsert(Node* &curr, int d)

// 	{
// 		if (curr == NULL)
// 		{
// 			curr = new Node(d);
// 		}
// 		else if (d < curr->data)

// 		{
// 			curr->left = myInsert(curr->left, d);

// 			if (getHeight(curr->left) - getHeight(curr->right) >= 2)
// 			{
// 				if (d < curr->left->data)
// 				{
// 					curr = SRL(curr);
// 				}

// 				else
// 				{
// 					curr = DRL(curr);
// 				}
// 			}
// 		}

// 		else if (d > curr->data)
// 		{
// 			curr->right = myInsert(curr->right, d);

// 			if (getHeight(curr->right) - getHeight(curr->left) >= 2)
// 			{
// 				if (d >= curr->right->data)
// 				{
// 					curr = SRR(curr);
// 				}
// 				else
// 				{
// 					curr = DRR(curr);
// 				}
// 			}
// 		}

// 		curr->height = normalize(getHeight(curr->left), getHeight(curr->right)) + 1;
// 		return curr;
// 	}

// 	int getHeight(Node* node) {
// 		return (node == NULL) ? -1 : node->height;
// 	}

// 	void insert(int d)
// 	{
// 		myInsert(root, d);
// 	}

// 	int getBalance(Node* N) {
// 		if (N == nullptr)
// 			return 0;
// 		return N->left->height - N->right->height;
// 	}

// 	Node* myDeletion(Node* root, int key) {

// 		if (root == nullptr)
// 			return root;
// 		if (key == root->data) {
// 			if ((root->left == nullptr) || (root->right == nullptr)) {
// 				Node* temp;
// 				if (root->left)
// 				{
// 					temp = root->left;
// 				}
// 				else
// 				{
// 					temp = root->right;
// 				}

// 				if (temp == nullptr) {
// 					temp = root;
// 					root = nullptr;
// 				}
// 				else
// 					*root = *temp;
// 				delete temp;
// 				temp = NULL;
// 			}
// 			else {

// 				Node* temp = root->right;
// 				while (temp->left != NULL)
// 				{
// 					temp = temp->left;
// 				}
// 				root->data = temp->data;
// 				root->right = myDeletion(root->right, temp->data);
// 			}
// 		}

// 		else if (key < root->data)
// 			root->left = myDeletion(root->left, key);

// 		else
// 			root->right = myDeletion(root->right, key);

// 		if (root == nullptr)
// 			return root;

// 		//root->height = normalize(root->left->height, root->right->height) + 1;
// 		root->height = normalize(getHeight(root->left), getHeight(root->right)) + 1;

// 		int balance = getBalance(root);

// 		if (balance > 1 && getBalance(root->left) >= 0)
// 			return SRR(root);

// 		if (balance > 1 &&
// 			getBalance(root->left) < 0) {
// 			root->left = SRL(root->left);
// 			return SRR(root);
// 		}

// 		if (balance < -1 &&
// 			getBalance(root->right) <= 0)
// 			return SRL(root);

// 		if (balance < -1 &&
// 			getBalance(root->right) > 0) {
// 			root->right = SRR(root->right);
// 			return SRL(root);
// 		}

// 		return root;
// 	}

// 	void preOrder(Node* root) {
// 		if (root != nullptr) {
// 			cout << root->data << " ";
// 			preOrder(root->left);
// 			preOrder(root->right);
// 		}
// 	}

// 	void deletion(int d)
// 	{
// 		myDeletion(root, d);
// 	}

// 	Node* SRL(Node* haha)
// 	{
// 		Node* hehe = haha->left;
// 		haha->left = hehe->right;
// 		hehe->right = haha;
// 		//haha->height = normalize(haha->left->height, haha->right->height) + 1;
// 		haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
// 		//hehe->height = normalize(hehe->left->height, hehe->right->height) + 1;
// 		hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;
// 		return hehe;
// 	}

// 	Node* DRL(Node* haha)
// 	{
// 		haha->left = SRR(haha->left);
// 		return SRL(haha);
// 	}

// 	Node* SRR(Node* haha)
// 	{
// 		Node* hehe = haha->right;
// 		haha->right = hehe->left;
// 		hehe->left = haha;
// 		//haha->height = normalize(haha->left->height, haha->right->height) + 1;
// 		haha->height = normalize(getHeight(haha->left), getHeight(haha->right)) + 1;
// 		//hehe->height = normalize(hehe->left->height, hehe->right->height) + 1;
// 		hehe->height = normalize(getHeight(hehe->left), getHeight(hehe->right)) + 1;
// 		return hehe;
// 	}

// 	Node* DRR(Node* haha)
// 	{
// 		haha->right = SRL(haha->right);
// 		return SRR(haha);
// 	}

// 	void inOrder(Node* haha)
// 	{
// 		if (haha == NULL)
// 		{
// 			return;
// 		}
// 		else
// 		{
// 			inOrder(haha->left);
// 			cout << haha->data << " ";
// 			inOrder(haha->right);
// 		}
// 	}

// 	void postOrder(Node* haha)
// 	{
// 		if (haha == NULL)
// 		{
// 			return;
// 		}
// 		else
// 		{
// 			postOrder(haha->left);
// 			postOrder(haha->right);
// 			cout << haha->data << " ";
// 		}
// 	}

// 	int small(Node* haha)
// 	{
// 		if (haha == NULL)
// 		{
// 			return -1;
// 		}
// 		else
// 		{
// 			while (haha->left != NULL)
// 			{
// 				haha = haha->left;
// 			}
// 		}
// 		return haha->data;
// 	}

// 	int large(Node* haha)
// 	{
// 		if (haha == NULL)
// 		{
// 			return -1;
// 		}
// 		else
// 		{
// 			while (haha->right != NULL)
// 			{
// 				haha = haha->right;
// 			}
// 		}
// 		return haha->data;
// 	}

// 	bool checkAVL(Node* haha)
// 	{
// 		if (haha->left == NULL && haha->right == NULL)
// 		{
// 			return getBalance(haha) < 2 && getBalance(haha) > -2;
// 		}
// 		else
// 		{
// 			return getBalance(haha->left) - getBalance(haha->right) < 2 && getBalance(haha->left) - getBalance(haha->right) > -2;
// 		}
// 	}

// 	bool isPrime(int num) {

// 		if (num <= 1) {
// 			return false;
// 		}

// 		for (int i = 2; i <= std::sqrt(num); ++i) {
// 			if (num % i == 0) {
// 				return false;
// 			}
// 		}

// 		return true;
// 	}

// 	void Q2(Node* curr)
// 	{
// 		if (curr == NULL)
// 		{
// 			return;
// 		}
// 		else
// 		{
// 			if (curr->data & 1 && !isPrime(curr->data))
// 			{
// 				SRR(curr);
// 			}
// 			else if (!isPrime(curr->data))
// 			{
// 				SRL(curr);
// 			}
// 		}
// 		Q2(curr->left);
// 		Q2(curr->right);
// 	}
// };
