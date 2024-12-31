// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>

// #define MAX_ROWS 1000
// #define MAX_COLS 100

// class CSVReader
// {
// private:
//     string data[MAX_ROWS][MAX_COLS];
//     string headers[MAX_COLS];
//     int rows;
//     int cols;

// public:
//     CSVReader() : rows(0), cols(0) {}

//     // bool readFile(const string &filename)
//     // {
//     //     ifstream file(filename);
//     //     if (!file.is_open())
//     //     {
//     //         cerr << "Cannot open file" << endl;
//     //         return false;
//     //     }

//     //     string line;
//     //     rows = 0;

//     //     while (getline(file, line) && rows < MAX_ROWS)
//     //     {
//     //         stringstream ss(line);
//     //         string cell;
//     //         int currentCol = 0;

//     //         while (getline(ss, cell, ',') && currentCol < MAX_COLS)
//     //         {
//     //             data[rows][currentCol] = cell;
//     //             ++currentCol;
//     //         }

//     //         cols = max(cols, currentCol);
//     //         ++rows;
//     //     }

//     //     file.close();
//     //     return true;
//     // }

//     // void displayData()
//     // {
//     //     for (int i = 0; i < rows; ++i)
//     //     {
//     //         for (int j = 0; j < cols; ++j)
//     //         {
//     //             cout << data[i][j] << "\t";
//     //         }
//     //         cout << endl;
//     //     }
//     // }

//     // void writeFilteredData(const string &outputFile, int filterCol, const string &filterValue)
//     // {
//     //     ofstream outFile(outputFile);
//     //     if (!outFile.is_open())
//     //     {
//     //         cerr << "Cannot open output file" << endl;
//     //         return;
//     //     }

//     //     for (int i = 0; i < rows; ++i)
//     //     {
//     //         if (filterCol < cols && data[i][filterCol] == filterValue)
//     //         {
//     //             for (int j = 0; j < cols; ++j)
//     //             {
//     //                 outFile << data[i][j];
//     //                 if (j < cols - 1)
//     //                     outFile << ",";
//     //             }
//     //             outFile << endl;
//     //         }
//     //     }

//     //     outFile.close();
//     // }

//     bool readFile(const string &filename)
//     {
//         ifstream file(filename);
//         if (!file.is_open())
//         {
//             cerr << "Cannot open file" << endl;
//             return false;
//         }

//         string line;
//         bool isFirstLine = true;
//         rows = 0;

//         while (getline(file, line) && rows < MAX_ROWS)
//         {
//             stringstream ss(line);
//             string cell;
//             int currentCol = 0;

//             if (isFirstLine)
//             {
//                 // Process headers
//                 while (getline(ss, cell, ',') && currentCol < MAX_COLS)
//                 {
//                     headers[currentCol] = cell;
//                     ++currentCol;
//                 }
//                 cols = currentCol;
//                 isFirstLine = false;
//             }
//             else
//             {
//                 // Process data rows
//                 while (getline(ss, cell, ',') && currentCol < MAX_COLS)
//                 {
//                     data[rows][currentCol] = cell;
//                     ++currentCol;
//                 }
//                 ++rows;
//             }
//         }

//         file.close();
//         return true;
//     }

//     void displayHeaders()
//     {
//         for (int j = 0; j < cols; ++j)
//         {
//             cout << headers[j] << "\t";
//         }
//         cout << endl;
//     }

//     void displayData()
//     {
//         for (int i = 0; i < rows; ++i)
//         {
//             for (int j = 0; j < cols; ++j)
//             {
//                 cout << data[i][j] << "\t";
//             }
//             cout << endl;
//         }
//     }

//     void writeFilteredData(const string &outputFile, int filterCol, const string &filterValue)
//     {
//         ofstream outFile(outputFile);
//         if (!outFile.is_open())
//         {
//             cerr << "Cannot open output file" << endl;
//             return;
//         }

//         // Write headers
//         for (int j = 0; j < cols; ++j)
//         {
//             outFile << headers[j];
//             if (j < cols - 1)
//                 outFile << ",";
//         }
//         outFile << endl;

//         // Write filtered data
//         for (int i = 0; i < rows; ++i)
//         {
//             if (filterCol < cols && data[i][filterCol] == filterValue)
//             {
//                 for (int j = 0; j < cols; ++j)
//                 {
//                     outFile << data[i][j];
//                     if (j < cols - 1)
//                         outFile << ",";
//                 }
//                 outFile << endl;
//             }
//         }

//         outFile.close();
//     }

//     int getRowCount() const { return rows; }
//     int getColumnCount() const { return cols; }
// };

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool readFile(const string &filename, string **&data, string *&headers, int &rows, int &cols)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Cannot open file" << endl;
        return false;
    }

    // First pass: Determine the number of rows and columns
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        int tempCols = 0;

        while (getline(ss, cell, ','))
        {
            ++tempCols;
        }

        cols = max(cols, tempCols);
        ++rows;
    }

    // Reset file to beginning
    file.clear();
    file.seekg(0);

    // Allocate memory for headers and data
    headers = new string[cols];
    data = new string *[rows - 1]; // Exclude header row

    for (int i = 0; i < rows - 1; ++i)
    {
        data[i] = new string[cols];
    }

    // Second pass: Read the file and populate the arrays
    bool isFirstLine = true;
    int currentRow = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        int currentCol = 0;

        if (isFirstLine)
        {
            // Read headers
            while (getline(ss, cell, ',') && currentCol < cols)
            {
                headers[currentCol] = cell;
                ++currentCol;
            }
            isFirstLine = false;
        }
        else
        {
            // Read data rows
            while (getline(ss, cell, ',') && currentCol < cols)
            {
                data[currentRow][currentCol] = cell;
                ++currentCol;
            }
            ++currentRow;
        }
    }
    file.close();
    return true;
}

void displayHeaders(string *&headers, int &cols)
{
    for (int j = 0; j < cols; ++j)
    {
        cout << headers[j] << "\t";
    }
    cout << endl;
}

void displayData(string **&data, string *&headers, int &rows, int &cols)
{
    for (int i = 0; i < rows - 1; ++i) // Exclude header row
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}

void writeFilteredData(const string &outputFile, int filterCol, const string &filterValue, string **&data, string *&headers, int &rows, int &cols)
{
    ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        cerr << "Cannot open output file" << endl;
        return;
    }

    // Write headers
    for (int j = 0; j < cols; ++j)
    {
        outFile << headers[j];
        if (j < cols - 1)
            outFile << ",";
    }
    outFile << endl;

    // Write filtered data
    for (int i = 0; i < rows - 1; ++i)
    {
        if (filterCol < cols && data[i][filterCol] == filterValue)
        {
            for (int j = 0; j < cols; ++j)
            {
                outFile << data[i][j];
                if (j < cols - 1)
                    outFile << ",";
            }
            outFile << endl;
        }
    }

    outFile.close();
}

int getRowCount()  { return rows - 1; } // Exclude header row
int getColumnCount()  { return cols; }
