#include <iostream>
#include <sstream>
#include <fstream>
// #include "SHA256.h"
using namespace std;

struct BNode
{
    BNode **children;
    int tot;              // total keys
    bool f;               // leaf or not
    string *datas;        // data
    string *key;          // keys
    size_t hash;          // hash of node
    string sha256;        // hash of data
    int mod29;            // for hashing
    string myPath;        // path of node
    string ParentsPath;   // path of parent
    string *ChildrenPath; // path of children
    string data;          // data
    int height;
    int cols;
    const char go[100] = "//home//taha_pc//MyFile//GitLIte//AVL.h";

    BNode(int nn, bool leafing, string path, int r, string data, string *list, int c, size_t HashOfData, int modulo)
        : tot(0), data(data), f(leafing), height(0), hash(HashOfData), sha256(""), cols(c), mod29(modulo)
    {
        cols = c;
        // datas = new string[cols];
        // for(int i=0;i<cols;i++)
        // {
        //     datas[i]=list[i];
        // }

        datas = new string[cols];
        for (int i = 0; i < cols; i++)
        {
            datas[i] = (i < sizeof(list) / sizeof(list[0])) ? list[i] : "";
        }

        key = new string[nn - 1];
        children = new BNode *[nn];
        for (int i = 0; i < nn; i++)
        {
            children[i] = NULL;
        }

        ParentsPath = "";
        ChildrenPath = new string[nn];
        string eh = to_string(r);
        myPath = path + "/" + data + "(" + eh + ")" + ".txt";
        cout << "BNode made for : " << data << endl;
        saveToFile();
    }

    BNode(const BNode &n)
    {
        tot = n.tot;
        f = n.f;
        height = n.height;
        mod29 = n.mod29;
        hash = n.hash;
        sha256 = n.sha256;
        cols = n.cols;
        data = n.data;
        datas = new string[cols];
        for (int i = 0; i < cols; i++)
        {
            datas[i] = n.datas[i];
        }
        key = new string[n.tot];
        for (int i = 0; i < n.tot; i++)
        {
            key[i] = n.key[i];
        }
        children = new BNode *[n.tot + 1];
        for (int i = 0; i < n.tot + 1; i++)
        {
            // children[i] = n.children[i];
            children[i] = (n.children[i] != NULL) ? new BNode(*n.children[i]) : NULL;
        }
        ParentsPath = n.ParentsPath;
        ChildrenPath = new string[n.tot + 1];
        for (int i = 0; i < n.tot + 1; i++)
        {
            ChildrenPath[i] = n.ChildrenPath[i];
        }
        myPath = n.myPath;
    }

    void saveToFile()
    {
        ofstream file(myPath, ios::out | ios::trunc);
        if (file.is_open())
        {
            file << "Total Keys : " << tot << endl;
            file << "Leaf : " << f << endl;
            file << "Height : " << height << endl;
            file << "Hash : " << hash << endl;
            file << "SHA256 : " << sha256 << endl;
            file << "Data : " << data << endl;
            file << "Mod29 : " << mod29 << endl;
            file << "Parents Path : " << ParentsPath << endl;
            file << "MyPath : " << myPath << endl;
            file << "Children Path : ";
            for (int i = 0; i < cols; i++)
            {
                file << "children path[" << i << "]: " << ChildrenPath[i] << "\n";
            }
            file << endl;
            file << "Data : ";
            for (int i = 0; i < cols; i++)
            {
                file << "Data[" << i << "]: " << datas[i] << "\n";
            }
            file << endl;
            file << "Keys : ";
            for (int i = 0; i < tot; i++)
            {
                file << "Key[" << i << "]: " << key[i] << "\n";
            }
            file << endl;
            file.close();
        }
        else
        {
            cout << "Error in opening file : " << myPath << endl;
        }
    }

    string readSpecificLine(const string &fileName, int lineNumber)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << fileName << endl;
            return "";
        }

        string line;
        int currentLine = 0;

        // Read lines until we reach the desired one
        while (getline(file, line))
        {
            if (++currentLine == lineNumber)
            {
                file.close();
                return line; // Return the desired line
            }
        }

        file.close();
        cerr << "Error: Line number " << lineNumber << " not found in " << fileName << endl;
        return "";
    }

    void loadFromFile(const string &fileName)
    {
        string line;
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Error: Cannot open file " << fileName << endl;
            return;
        }

        // Read each line from the file
        while (getline(file, line))
        {
            stringstream ss(line);
            string keys;
            string value;

            if (line.find(':') != string::npos)
            {
                getline(ss, keys, ':');
                getline(ss, value);
                keys = trim(keys);
                value = trim(value);

                // Map the loaded data to the respective node attributes
                if (keys == "MyPath")
                    myPath = value;
                else if (keys == "ParentsPath")
                    ParentsPath = value;
                else if (keys == "Height")
                    height = stoi(value);
                else if (keys == "Hash")
                    hash = stoull(value);
                else if (keys == "Mod29")
                    mod29 = stoi(value);
                else if (keys == "TotalKeys")
                    tot = stoi(value);
                else if (keys == "IsLeaf")
                    f = (value == "true");
                else if (keys == "SHA256")
                    sha256 = value;

                else if (keys.find("Data[") != string::npos)
                {
                    int index = stoi(keys.substr(5, keys.find(']') - 5));
                    if (index >= 0 && index < cols)
                        datas[index] = value;
                }
                else if (keys.find("Keys[") != string::npos)
                {
                    int index = stoi(keys.substr(5, keys.find(']') - 5));
                    if (index >= 0 && index < cols - 1)
                        key[index] = value;
                }
                else if (keys.find("ChildrenPath[") != string::npos)
                {
                    int index = stoi(keys.substr(13, keys.find(']') - 13));
                    if (index >= 0 && index < cols + 1)
                        ChildrenPath[index] = value;

                    else
                    {
                        cout << "Invalid index for children path" << endl;
                    }
                }
            }
        }

        file.close();
    }

    // string trim(const string &str)
    // {
    //     size_t first = str.find_first_not_of(' ');
    //     if (first==string::npos)
    //     {
    //         return str;
    //     }
    //     size_t last = str.find_last_not_of(' ');
    //     if (last < first)//Ensure that last is not smaller than first
    //     {
    //         return ""; // returnin empty string in case the string contains only spaces
    //     }
    //     return str.substr(first, (last - first + 1));
    // }

    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t"); // removes space + tab
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    void SettingMyPath(const string &newPath)
    {
        myPath = newPath;
        saveToFile(); // Update the file with the new path
    }

    void SettingKey(int index, const string &val)
    {
        if (index >= 0 && index < tot - 1)
        {
            key[index] = val;
        }
        else
        {
            cerr << "Index out of bounds for keys." << endl;
        }
    }
    string GettingKey(int index) const
    {
        if (index >= 0 && index < tot - 1)
        {
            return key[index];
        }
        else
        {
            cerr << "Index out of bounds for keys." << endl;
            return ""; // Return an empty string if index is out of bounds
        }
    }

    void SettingParentPath(const string &newParentPath)
    {
        ParentsPath = newParentPath;
        saveToFile();
    }

    void SettingData(int index, const string &value)
    {
        if (index >= 0 && index < tot)
        {
            datas[index] = value;
        }
        else
        {
            cerr << "Index out of bounds for datas." << endl;
        }
    }

    string GettingData(int index) const
    {
        if (index >= 0 && index < tot)
        {
            return datas[index];
        }
        else
        {
            cerr << "Index out of bounds for datas." << endl;
            return ""; // Return an empty string if index is out of bounds
        }
    }

    void SettingChildrenPath(int index, const string &newChildPath)
    {
        if (index >= 0 && index < tot) // Ensure index is valid
        {
            ChildrenPath[index] = newChildPath;
            saveToFile(); // Update the file with the new child path
        }
        else
        {
            cout << "Invalid index for children path" << endl;
        }
    }

    void display() const
    {
        cout << "MyPath: " << myPath << endl;
        cout << "ParentPath: " << ParentsPath << endl;
        for (int i = 0; i < tot; ++i)
        {
            cout << "ChildrenPath[" << i << "]: " << ChildrenPath[i] << endl;
        }
        cout << "Data: " << data << endl;
        cout << "Hash: " << hash << endl;
        cout << "Height: " << height << endl;
        cout << "Mod29: " << mod29 << endl;

        for (int i = 0; i < cols; i++)
        {
            cout << "Data[" << i << "]: " << datas[i] << endl;
        }
        for (int i = 0; i < tot - 1; i++)
        {
            cout << "Key[" << i << "]: " << key[i] << endl;
        }
    }

    ~BNode()
    {
        delete[] key;
        delete[] datas;
        delete[] ChildrenPath;

        if (!f && children != NULL)
        {
            for (int i = 0; i <= cols + 1; i++)
            {
                if (children[i] != NULL)
                {
                    delete children[i];
                    children[i] = NULL;
                }
            }
        }
        delete[] children;
        children = NULL;
    }
};