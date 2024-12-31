#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdio>
// #include "SHA256.h"
using namespace std;

struct RNode
{
    RNode *parent;
    string color;
    // Data Storage
    string data;
    string *datas;
    // Sorting Hash
    size_t hash;
    // Murkle Hash
    string sha256;
    int mod29;
    // RNode Pointers
    RNode *left;
    RNode *right;
    // File Paths
    string myPath;
    // string ParentsPath;
    string LeftPath;
    string RightPath;
    int height;
    string mainP;
    int cols;

    // size_t computeHash(string input)
    // {
    //     return hash<string>{}(input);
    // }

    RNode(const string data, size_t HashOfData, string *list, int c, string path, int r, string sha) : data(data), height(0), hash(HashOfData)
    {
        mainP = path;
        parent = nullptr;
        color = "red";
        cols = c;
        datas = new string[cols];
        for (int i = 0; i < cols; i++)
        {
            *(datas + i) = *(list + i);
        }
        left = right = NULL;
        // ParentsPath,
        LeftPath, RightPath = "";
        sha256 = sha;
        string eh = to_string(r);
        myPath = path + "/" + data + "(" + eh + ")" + ".txt";
        string go = "//home//taha_pc//MyFile//GitLIte//AVL.h";
        cout << "RNode made for : " << data << endl;
        saveToFile();
    }

    RNode(const RNode &other) : data(other.data), hash(other.hash), sha256(other.sha256), mod29(other.mod29),
                                LeftPath(other.LeftPath.substr(other.LeftPath.find_last_of('/') + 1)), RightPath(other.RightPath.substr(other.RightPath.find_last_of('/') + 1)),
                                myPath(other.myPath.substr(other.myPath.find_last_of('/') + 1)), cols(other.cols)
    {
        // Alllocating new memory for datas and copy values
        datas = new string[cols];
        for (int i = 0; i < cols; ++i)
        {
            datas[i] = other.datas[i];
        }

        left = other.left ? new RNode(*other.left) : NULL;    // deep copy of left child
        right = other.right ? new RNode(*other.right) : NULL; // Deep copy of right child

        // left = other.left;
        // right = other.right;

        // cout << "Copy constructor called for: " << data << endl;
    }

    void setMainPath(string path)
    {
        mainP = path;
        myPath = mainP + "/" + myPath;
        LeftPath = mainP + "/" + LeftPath;
        RightPath = mainP + "/" + RightPath;
        saveToFile();
    }

    RNode &operator=(const RNode &other)
    {
        if (this == &other)
            return *this; // Avoid self-assignment

        // Free the existing memory
        delete[] datas;
        if (left)
            delete left;
        if (right)
            delete right;

        // Copy the data members
        data = other.data;
        hash = other.hash;
        sha256 = other.sha256;
        mod29 = other.mod29;
        LeftPath = other.LeftPath;
        RightPath = other.RightPath;
        myPath = other.myPath;
        height = other.height;
        cols = other.cols;

        // Allocate new memory and copy the values
        datas = new string[cols];
        for (int i = 0; i < cols; ++i)
        {
            datas[i] = other.datas[i];
        }

        left = other.left ? new RNode(*other.left) : NULL;    // deep copy of left child
        right = other.right ? new RNode(*other.right) : NULL; // Deep copy of right child

        // cout << "Copy assignment operator called for: " << data << endl;

        return *this;
    }

    void copySh(RNode *root)
    {
        if (root != NULL)
        {
            data = root->data;
            for (int i = 0; i < cols; i++)
            {
                datas[i] = root->datas[i];
            }
            hash = root->hash;
            sha256 = root->sha256;
            mod29 = root->mod29;
            myPath = root->myPath;
            cols = root->cols;
            left = root->left;
            right = root->right;
            LeftPath = root->LeftPath;
            RightPath = root->RightPath;
            saveToFile();
        }
    }

    void copy(RNode *root)
    {
        if (root != NULL)
        {
            data = root->data;
            for (int i = 0; i < cols; i++)
            {
                datas[i] = root->datas[i];
            }
            hash = root->hash;
            sha256 = root->sha256;
            mod29 = root->mod29;
            if (!rename(root->myPath.c_str(), myPath.c_str()))
            {
                cout << "File Renamed" << endl;
            }
            else
            {
                cout << "File not Renamed" << endl;
            }
            myPath = root->myPath;
            cols = root->cols;
            saveToFile();
        }
    }

    void saveToFile()
    {
        ofstream outFile(myPath, ios::out | ios::trunc);
        if (outFile.is_open())
        {
            // Write paths
            outFile << "MyPath: " << myPath << "\n";
            // outFile << "ParentPath: " << ParentsPath << "\n";
            outFile << "LeftPath: " << LeftPath << "\n";
            outFile << "RightPath: " << RightPath << "\n";

            // Write data
            outFile << "Data: " << data << "\n";
            outFile << "Hash: " << hash << "\n";
            outFile << "SHA256: " << sha256 << "\n";
            outFile << "Height: " << height << "\n";
            outFile << "Mod29: " << mod29 << "\n";
            outFile << "Color: " << color << "\n";
            // Write datas array
            for (int i = 0; i < cols; i++)
            {
                outFile << "Data[" << i << "]: " << datas[i] << "\n";
            }

            outFile.close();
        }
        else
        {
            cerr << "Error: Could not open file " << myPath << endl;
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

    void loadFromFile(const string &filePath)
    {
        ifstream inFile(filePath);
        if (!inFile.is_open())
        {
            cerr << "Error: Could not open file " << filePath << endl;
            return;
        }

        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string key, value;

            if (line.find(':') != string::npos)
            {
                getline(ss, key, ':');
                getline(ss, value);
                key = trim(key);
                value = trim(value);

                if (key == "MyPath")
                    myPath = value;
                // else if (key == "ParentPath")
                //     ParentsPath = value;
                else if (key == "LeftPath")
                    LeftPath = value;
                else if (key == "RightPath")
                    RightPath = value;
                else if (key == "Data")
                    data = value;
                else if (key == "Hash")
                    hash = stoull(value);
                else if (key == "Height")
                    height = stoi(value);
                else if (key == "Mod29")
                    mod29 = stoi(value);
                else if (key.find("Data[") != string::npos)
                {
                    int index = stoi(key.substr(5, key.find(']') - 5));
                    if (index < cols)
                        datas[index] = value;
                }
            }
        }

        inFile.close();
    }

    void setLeftChildPath(const string &leftPath)
    {
        LeftPath = leftPath;
        saveToFile(); // Update the file with new paths
    }

    void setRightChildPath(const string &rightPath)
    {
        RightPath = rightPath;
        saveToFile(); // Update the file with new paths
    }

    // void setParentPath(const string &parentPath)
    // {
    //     ParentsPath = parentPath;
    //     saveToFile(); // Update the file with the parent's path
    // }

    void display() const
    {
        cout << "MyPath: " << myPath << endl;
        // cout << "ParentPath: " << ParentsPath << endl;
        cout << "LeftPath: " << LeftPath << endl;
        cout << "RightPath: " << RightPath << endl;
        cout << "Data: " << data << endl;
        cout << "Hash: " << hash << endl;
        cout << "Height: " << height << endl;
        cout << "Mod29: " << mod29 << endl;
        cout << "Color: " << color << endl;
        for (int i = 0; i < cols; i++)
        {
            cout << "Data[" << i << "]: " << datas[i] << endl;
        }
    }

    ~RNode()
    {
        delete[] datas;
    }

private:
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }
};