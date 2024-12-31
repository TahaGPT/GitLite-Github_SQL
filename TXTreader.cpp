#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class FileHandler
{
private:
    string filename;

public:
    // Constructor
    FileHandler(const string &fname) : filename(fname) {}

    // Write to file (creates/overwrites)
    bool writeFile()
    {
        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing" << endl;
            return false;
        }

        outFile << "Hello, File Handling!" << endl;
        outFile << "This demonstrates writing to a file." << endl;

        outFile.close();
        cout << "File written successfully." << endl;
        return true;
    }

    // Read entire file
    bool readEntireFile()
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            cerr << "Error opening file for reading" << endl;
            return false;
        }

        string content;
        cout << "File Contents:" << endl;
        while (getline(inFile, content))
        {
            cout << content << endl;
        }

        inFile.close();
        return true;
    }

    // Append to file
    bool appendToFile(const string &newContent)
    {
        ofstream appendFile(filename, ios::app);
        if (!appendFile.is_open())
        {
            cerr << "Error opening file for appending" << endl;
            return false;
        }

        appendFile << newContent << endl;
        appendFile.close();
        cout << "Content appended successfully." << endl;
        return true;
    }

    // Read file with specific operations
    bool readFileWithOperations()
    {
        fstream file(filename, ios::in | ios::out);
        if (!file.is_open())
        {
            cerr << "Error opening file for read/write" << endl;
            return false;
        }

        // Move to specific position
        file.seekg(0, ios::beg);

        // Read first line
        string firstLine;
        getline(file, firstLine);
        cout << "First Line: " << firstLine << endl;

        // Move to end and write
        file.seekp(0, ios::end);
        file << "Added via read/write stream" << endl;

        file.close();
        return true;
    }

    // Search in file
    bool searchInFile(const string &searchTerm)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file for search" << endl;
            return false;
        }

        string line;
        bool found = false;
        int lineNumber = 0;

        while (getline(file, line))
        {
            lineNumber++;
            if (line.find(searchTerm) != string::npos)
            {
                cout << "Found '" << searchTerm << "' at line "
                     << lineNumber << ": " << line << endl;
                found = true;
            }
        }

        file.close();
        return found;
    }

    // Get file size
    long getFileSize()
    {
        ifstream file(filename, ios::binary | ios::ate);
        if (!file.is_open())
        {
            cerr << "Error opening file to get size" << endl;
            return -1;
        }

        long size = file.tellg();
        file.close();
        cout << "File size: " << size << " bytes" << endl;
        return size;
    }
};

int main()
{
    FileHandler fileHandler("example.txt");

    string fileName = "example.txt";

    // 1. Creating and Writing to a File
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        outFile << "This is the first line.\n";
        outFile << "This is the second line.\n";
        outFile.close();
        cout << "File '" << fileName << "' created and written successfully." << endl;
    }
    else
    {
        cout << "Error opening file for writing!" << endl;
    }

    // 2. Reading from a File
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        string line;
        cout << "\nFile content:" << endl;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }
    else
    {
        cout << "Error opening file for reading!" << endl;
    }

    // 3. Appending to a File
    ofstream appendFile(fileName, ios::app);
    if (appendFile.is_open())
    {
        appendFile << "This is an appended line.\n";
        appendFile.close();
        cout << "\nContent appended to '" << fileName << "' successfully." << endl;
    }
    else
    {
        cout << "Error opening file for appending!" << endl;
    }

    // 4. Reading File Again
    inFile.open(fileName);
    if (inFile.is_open())
    {
        cout << "\nFile content after appending:" << endl;
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }
    else
    {
        cout << "Error opening file for reading!" << endl;
    }

    // 5. Deleting a File
    if (remove(fileName.c_str()) == 0)
    {
        cout << "\nFile '" << fileName << "' deleted successfully." << endl;
    }
    else
    {
        cout << "\nError deleting file!" << endl;
    }

    return 0;

    // Demonstrate file operations
    fileHandler.writeFile();
    fileHandler.readEntireFile();
    fileHandler.appendToFile("New line appended to file");
    fileHandler.readFileWithOperations();
    fileHandler.searchInFile("File");
    fileHandler.getFileSize();

    return 0;
}