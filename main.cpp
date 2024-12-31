// 23i-0532 Taha Ahmed
// 23i-0802 Zara Tahir
// 23i-0062 Ruhan Kamran
// Taha EVP_ASYM_CIPHER_do_all_provided
// Zara ASN1_R_THE_ASN1_OBJECT_IDENTIFIER_IS_NOT_KNOWN_FOR_THIS_MD
// Ruhan OSSL_FUNC_kem_get_ctx_params_fn

#include <iostream>
#include "AVL.h"
#include "rbtree.h"
#include "B Tree.h"
#include "CSVreader.h"
#include <filesystem>
#include <stack>
#include <queue>
// #include "SHA256.h"
using namespace std;

void showtreeMenu()
{
    cout << R"(
                                        =======================================
                                                Tree COMMAND MENU
                                        =======================================
                                        1. Select records in a range
                                        2. Update all records according to name
                                        3. Delete all records according to name
                                        4. Delete only the first record for a name
                                        5. Select for a roll number range
                                        6. Update for a roll number range
                                        0. Exit Menu
                                        =======================================
)";
}

void showAtreeMenu()
{
    cout << R"(
      ===============================================================================================================================
                                                Tree COMMAND MENU
      ===============================================================================================================================
                                        1. Select records within a range
                                        2. Select all records where a specific field starts with a value and ends with another value
                                        3. Select all records within a field's range (e.g., identifiers 'A-001' to 'A-100')
                                        4. Select all records where a field follows a specific pattern
                                        5. Update all records according to a specific field
                                        6. Update all records within a field's range
                                        0. Exit Menu
      ===============================================================================================================================
    Enter your choice: )";
}

void showMenu()
{
    cout << R"(
                                        =======================================
                                                REPOSITORY MANAGEMENT TOOL
                                        =======================================
                                        1. Initialize Repository
                                        2. Create a Branch
                                        3. Switch Branch
                                        4. Commit Changes
                                        5. Display All Branches
                                        6. Delete a Branch
                                        7. Delete an Entry within a Branch
                                        8. Visualize Tree Structure
                                        9. Display Commit History
                                        10. Display Current Branch
                                        11. Save Repository
                                        12. Load Repository
                                        0. Exit
                                        =======================================
)";
}
// num = str.substr(str.find('(') + 1, str.find(')') - str.find('(') - 1)
//  num = stoi(num)
int main()
{
    // important variables
    int rows = 0, cols = 0;
    string *head;
    string **data;

    string *RBbranches = new string[10]{"main", "", "", "", "", "", "", "", "", ""}; // names of the branches
    string *AVLbranches = new string[10]{"main", "", "", "", "", "", "", "", "", ""};
    // Reading CSV
    if (!readFile("Example Data.csv", data, head, rows, cols))
    {
        return 1;
    }

    // inputtting the main column tree
    cout << "Please Enter the Column you want to make the Tree for: \n";
    for (int i = 0; i < cols; i++)
    {
        cout << i + 1 << ". " << head[i] << " \n";
    }
    int n;
    cout << "\nEnter the Column Number: ";
    cin >> n;
    n--;
    cout << "You have selected: " << head[n] << endl;

    // Creating folder
    string folderName = *(head + n) + "(main)";

    // Asking for the choice of the Hash of Tree
    bool allow;
    cout << "Do you want to use SHA-256 or Secret Hash for Hashing? [1 : SHA-256 / 0 : Secret Hash] : ";
    cin >> allow;

    cout << "Number of rows:" << rows << endl;
    cout << "Number of columns:" << cols << endl;

    // Creating the Trees
    AVL AVLtree[10] = {{folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}};
    rbtree RBtree[10] = {{folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}, {folderName, allow}};
    int AVLb = 0;
    int AVLc = 0;
    int RBb = 0;
    int RBc = 0;
    stack<string> logs;
    queue<string> commits;
    int curr = 0;
    int selector = 0;
    // until the system runs
    int stop = 1;
    while (stop != 0)
    {
        showMenu();
        cout << "Enter your choice: ";
        cin >> stop;
        // keep track of the current tree
        switch (stop)
        {
        case 1: // Initializing the Repository
        {
            cout << "Which tree do you want to make?\n1. AVL Tree\n2. RB Tree\n3. B Tree\n";
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1: // AVL Tree
            {
                if (!AVLtree[0].root)
                {
                    logs.push("Initialized Repository for AVL Tree");
                    curr = choice;
                    selector = choice;
                    cout << "Creating AVL Tree\n";
                    AVLbranches[AVLb] = folderName;
                    AVLtree[AVLb].makeFolder(folderName);
                    for (int i = 1; i < rows; i++)
                    {
                        cout << "Creating File Number : " << i << endl;
                        AVLtree[AVLb].insert(data[i - 1][n], data[i - 1], cols, i);
                        cout << "File made for : " << data[i - 1][n] << endl;
                    }
                    AVLtree[AVLb].inOrder(AVLtree[AVLb].root);
                    AVLb++;
                    cout << "Repository Initialized\n";
                }
                else
                {
                    cout << "Repository already initialized\n";
                }
                break;
            }
            case 2: // RB Tree
            {
                if (!RBtree[0].root)
                {
                    logs.push("Initialized Repository for RB Tree");
                    curr = choice;
                    cout << "Creating Red Black Tree \n";
                    RBbranches[RBb] = folderName;
                    RBtree[RBb].makeFolder(folderName);
                    for (int i = 1; i < rows; i++)
                    {
                        cout << "Creating File Number : " << i << endl;
                        RBtree[RBb].insert(data[i - 1][n], data[i - 1], cols, i);
                        cout << "File made for : " << data[i - 1][n] << endl;
                    }
                    RBtree[RBb].inOrder(RBtree[RBb].root);
                    RBb++;
                    cout << "Repository Initialized\n";
                }
                else
                {
                    cout << "Repository already initialized\n";
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 2: // Brnahcing
        {
            cout << curr << endl;
            switch (curr)
            {
            case 1:
            {

                if (AVLb == 0) // stil empty
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else if (AVLb == 10) // maxed out
                {
                    cout << "Maximum Branches Reached\n";
                    break;
                }
                else
                {
                    cout << "Enter the name of the Branch: ";
                    cin >> AVLbranches[AVLb];
                    cin.ignore();
                    AVLbranches[AVLb] = *(head + n) + "(" + AVLbranches[AVLb] + ")";
                    logs.push(AVLbranches[AVLb] + " Branch Created for AVL Tree");
                    AVLtree[AVLb].makeFolder(AVLbranches[AVLb]);
                    cout << "Creating Branch for AVL Tree\n";
                    AVLtree[AVLb] = AVLtree[AVLc];
                    AVLc = AVLb;
                    cout << "switched to branch " << AVLbranches[AVLb] << endl;
                    AVLb++;
                }
                break;
            }
            case 2:
            {

                if (RBb == 0) // still empty
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else if (RBb == 10) // max limit
                {
                    cout << "Maximum Branches Reached\n";
                    break;
                }
                else // creaating new branmcxh
                {
                    cout << "Enter the name of the Branch: ";
                    cin >> RBbranches[RBb];
                    cin.ignore();
                    RBbranches[RBb] = *(head + n) + "(" + RBbranches[RBb] + ")";
                    logs.push(RBbranches[RBb] + "Branch Created for RB Tree");
                    RBtree[RBb].makeFolder(RBbranches[RBb]);
                    cout << "Creating Branch for RB Tree\n";
                    RBtree[RBb] = RBtree[RBc];
                    RBc = RBb;
                    cout << "switched to branch " << RBbranches[RBb] << endl;
                    RBb++;
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }

        case 3: // switching branches
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Branches for AVL Tree are: \n";
                    for (int i = 0; i < AVLb; i++)
                    {
                        cout << i + 1 << ". " << AVLbranches[i] << endl;
                    }
                    cout << endl;
                    int num = 0;
                    cout << "Enter the Branch Number to switch: ";
                    cin >> num;
                    num--;
                    if (num < AVLb && num > 0)
                    {
                        AVLc = num;
                        cout << "switched to branch " << AVLbranches[AVLc] << endl;
                        logs.push("Switched to Branch " + AVLbranches[AVLc] + " in AVL Tree");
                    }
                    else
                    {
                        cout << "Invalid Branch Number\n";
                    }
                }
                break;
            }
            case 2:
            {
                if (RBb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Branches for RB Tree are: \n";
                    for (int i = 0; i < RBb; i++)
                    {
                        cout << i + 1 << ". " << RBbranches[i] << endl;
                    }
                    cout << endl;
                    int num = 0;
                    cout << "Enter the Branch Number to Switch: ";
                    cin >> num;
                    num--;
                    if (num < RBb && num > 0)
                    {
                        RBc = num;
                        cout << "switched to branch " << RBbranches[RBc] << endl;
                        logs.push("Switched to Branch " + RBbranches[RBc] + " in RB Tree");
                    }
                    else
                    {
                        cout << "Invalid Branch Number\n";
                    }
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 4: // Comittting Changes
        {
            switch (curr)
            {
            case 1:
            {
                int query = 0;
                showAtreeMenu();
                cin >> query;

                switch (query)
                {
                case 1:
                {
                    string start, end;
                    cout << "Enter the starting value: ";
                    cin >> start;
                    cin.ignore();
                    cout << "Enter the ending value: ";
                    cin >> end;
                    AVLtree[AVLc].RangeSearch(start, end);
                    break;
                }
                case 2:
                {
                    string wildcardthingy;
                    cout << "Enter the pattern (use '%' as wildcard): ";
                    cin >> wildcardthingy;
                    AVLtree[AVLc].patternSearch(wildcardthingy);
                    break;
                }
                case 3:
                {
                    string start, end;
                    cout << "Enter the starting value: ";
                    cin >> start;
                    cout << "Enter the ending value: ";
                    cin >> end;
                    AVLtree[AVLc].rangeSearch(start, end);
                    break;
                }
                case 4:
                {
                    string pattern;
                    cout << "Enter the pattern to search for: ";
                    cin >> pattern;
                    AVLtree[AVLc].strpatternSearch(pattern);
                    cout << endl;

                    break;
                }
                case 5:
                {

                    int columnToSearchIndex, columnToChangeIndex;
                    string searchVal, modifiedVal;

                    cout << "Choose a column to search by:\n";
                    for (int i = 0; i < cols; ++i)
                    {
                        cout << i + 1 << ". " << head[i] << endl;
                    }

                    cout << "Enter the number corresponding to the column to search by: ";
                    cin >> columnToSearchIndex;
                    columnToSearchIndex--;

                    // vaidity check
                    if (columnToSearchIndex < 0 || columnToSearchIndex >= cols)
                    {
                        cout << "Invalid column selection!" << endl;
                        break;
                    }

                    // gttin usrs choice for the column to updatiof
                    cout << "Choose a column to update:\n";
                    for (int i = 0; i < cols; ++i)
                    {
                        cout << i + 1 << ". " << head[i] << endl;
                    }
                    cout << "Enter the number corresponding to the column to update: ";
                    cin >> columnToChangeIndex;
                    columnToChangeIndex--;

                    if (columnToChangeIndex < 0 || columnToChangeIndex >= cols)
                    {
                        cout << "Invalid column selection!" << endl;
                        break;
                    }

                    cout << "Enter the value to search for in column " << head[columnToSearchIndex] << ": ";
                    cin.ignore();
                    getline(cin, searchVal);
                    cout << "Enter the new value for column " << head[columnToChangeIndex] << ": ";
                    getline(cin, modifiedVal);

                    bool result = AVLtree[AVLc].updateNode(AVLtree[AVLc].root, columnToSearchIndex, columnToChangeIndex, searchVal, modifiedVal);
                    if (result)
                    {
                        cout << "Update successful.\n";
                    }
                    else
                    {
                        cout << "Update failed. Node not found.\n";
                    }
                    break;
                }
                case 6:
                {
                    int searcher, updater;
                    string startValue, endValue, newValue;

                    cout << "Choose a column to search by:\n";
                    for (int i = 0; i < cols; ++i)
                    {
                        cout << i + 1 << ". " << head[i] << endl;
                    }

                    cout << "Enter the number corresponding to the column to search by: ";
                    cin >> searcher;
                    searcher--;

                    if (searcher < 0 || searcher >= cols)
                    {
                        cout << "Invalid column selection!" << endl;
                        break;
                    }

                    cout << "Enter the number corresponding to the column to update: ";
                    cin >> updater;
                    updater--;

                    if (updater < 0 || updater >= cols)
                    {
                        cout << "Invalid column selection!" << endl;
                        break;
                    }

                    cout << "Enter the start value for column " << head[searcher] << ": ";
                    cin.ignore();
                    getline(cin, startValue);

                    cout << "Enter the end value for column " << head[searcher] << ": ";
                    getline(cin, endValue);

                    cout << "Enter the new value for column " << head[updater] << ": ";
                    getline(cin, newValue);

                    bool result = AVLtree[AVLc].updateRange(AVLtree[AVLc].root, searcher, updater, startValue, endValue, newValue);
                    if (result)
                    {
                        cout << "Update successful for the specified range.\n";
                    }
                    else
                    {
                        cout << "Update failed. No nodes found in the specified range.\n";
                    }
                    break;
                }
                case 0:
                {
                    cout << "Exiting Menu.\n";
                    break;
                }
                }
                break;
            }
            case 2:
            {
                string str1, str2;
                int num = 0;
                int num1 = 0;
                int num2 = 0;
                int num3 = 0;
                int numx = 0;
                showtreeMenu();
                cout << endl;
                cout << "please enter a choice: ";
                cin >> num;
                cout << endl;
                switch (num)
                {
                case 1:
                {
                    cout << "please enter k: ";
                    cin >> num3;
                    cout << endl;
                    cout << "Enter lower range: ";
                    cin >> num1;
                    cout << endl;
                    cout << "Enter upper range: ";
                    cin >> num2;
                    cout << endl;
                    RBtree[RBc].rangebynum(num1, num2, num3);
                    RBtree[RBc].printLL();
                    break;
                }
                case 2:
                {
                    cout << "Enter student name: ";
                    cin >> str1;
                    cout << endl;
                    RBtree[RBc].update_all(str1);
                    break;
                }

                case 3:
                {
                    cout << "Enter student name: ";
                    cin >> str1;
                    cout << endl;
                    RBtree[RBc].delete_all(str1);
                    break;
                }
                case 4:
                {
                    cout << "Enter student name: ";
                    cin >> str1;
                    cout << endl;
                    RBtree[RBc].delete_at(str1);
                    break;
                }
                case 5:
                {
                    cout << "Enter start roll number: ";
                    cin >> str1;
                    cout << endl;
                    cout << "Enter end roll number: ";
                    cin >> str2;
                    RBtree[RBc].rangebyrollnum(str1, str2);
                    RBtree[RBc].printLL();
                    cout << endl;
                    break;
                }

                case 6:
                {
                    cout << "Enter column head: ";
                    cin >> str1;
                    for (int i = 0; i < cols; i++)
                    {
                        if (head[i] == str1)
                        {
                            numx = i;
                            break;
                        }
                    }
                    cout << endl;
                    cout << "Enter what u wanna set it as: ";
                    cin >> str2;
                    RBtree[RBc].set(numx, str2);
                    cout << endl;
                    break;
                }

                    /*  case 8:
                          cout << "Enter start roll number: ";
                          cin >> str1;
                          cout << endl;
                          cout << "Enter end roll number: ";
                          cin >> str2;
                          cout << endl;
                          break;

                      case 9:
                          cout << "Enter start roll number: ";
                          cin >> str1;
                          cout << endl;
                          cout << "Enter end roll number: ";
                          cin >> str2;
                          cout << endl;
                          break;*/
                case 0:
                {
                    cout << "Exiting Menu.\n";
                    break;
                }
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 5: // display of the branches
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0)
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    logs.push("Displaying All Branches for AVL Tree");
                    cout << "Branches for AVL Tree are: \n";
                    for (int i = 0; i < AVLb; i++)
                    {
                        cout << i + 1 << ". " << AVLbranches[i] << endl;
                    }
                }
                break;
            }
            case 2:
            {
                if (RBb == 0)
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    logs.push("Displaying All Branches for RB Tree");
                    cout << "Branches for RB Tree are: \n";
                    for (int i = 0; i < RBb; i++)
                    {
                        cout << i + 1 << ". " << RBbranches[i] << endl;
                    }
                }
                break;
            }

            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 6: // Deleton of the Branches
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Branches for AVL Tree are: \n";
                    for (int i = 0; i < AVLb; i++)
                    {
                        cout << i + 1 << ". " << AVLbranches[i] << endl;
                    }
                    cout << endl;
                    int num = 0;
                    cout << "Enter the Branch Number to be Deleted: ";
                    cin >> num;
                    num--;
                    if (num < AVLb && num > 0)
                    {
                        AVLc = num;
                        cout << "switched to branch " << AVLbranches[AVLc] << endl;
                        if (filesystem::exists(AVLbranches[AVLc]))
                        {
                            // Remove the folder and all its contents
                            std::uintmax_t removedCount = filesystem::remove_all(AVLbranches[AVLc]);
                            std::cout << "Successfully deleted '" << AVLbranches[AVLc] << "' with "
                                      << removedCount << " items removed." << std::endl;
                            AVLb--;
                            logs.push("Deleted Branch " + AVLbranches[AVLc] + " in AVL Tree");
                            for (int i = AVLc; i < AVLb; i++)
                            {
                                AVLbranches[i] = AVLbranches[i + 1];
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid Branch Number\n";
                    }
                }
                break;
            }
            case 2:
            {
                if (RBb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Branches for RB Tree are: \n";
                    for (int i = 0; i < RBb; i++)
                    {
                        cout << i + 1 << ". " << RBbranches[i] << endl;
                    }
                    cout << endl;
                    int num = 0;
                    cout << "Enter the Branch Number to be Deleted: ";
                    cin >> num;
                    num--;
                    if (num < RBb && num > 0)
                    {
                        RBc = num;
                        cout << "switched to branch " << RBbranches[RBc] << endl;
                        if (filesystem::exists(RBbranches[RBc]))
                        {
                            // Remove the folder and all its contents
                            std::uintmax_t removedCount = filesystem::remove_all(RBbranches[RBc]);
                            std::cout << "Successfully deleted '" << RBbranches[RBc] << "' with "
                                      << removedCount << " items removed." << std::endl;
                            RBb--;
                            logs.push("Deleted Branch " + RBbranches[RBc] + " in RB Tree");
                            for (int i = RBc; i < RBb; i++)
                            {
                                RBbranches[i] = RBbranches[i + 1];
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid Branch Number\n";
                    }
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 7: // Deleting an entry of the current Branch
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Enter the name of the Entry to be Deleted: ";
                    string name;
                    cin >> name;
                    AVLtree[AVLc].deletion(name);
                    logs.push("Deleted Entry " + name + " in AVL Tree");
                }
                break;
            }
            case 2:
            {
                if (RBb == 0)
                {
                    cout << "Please Initialize the Repository first\n";
                }
                else
                {
                    cout << "Enter the name of the Entry to be Deleted: ";
                    string name;
                    cin >> name;
                    RBtree[RBc].delete_val(name);
                    logs.push("Deleted Entry " + name + " in RB Tree");
                }
            }
            }
            break;
        }
        case 8: // Visualizing the Tree
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    AVLtree[AVLc].visualize();
                }
                break;
            }

            case 2:
            {
                if (RBb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    RBtree[RBc].visualize();
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        case 9: // Displaying the logs
        {
            if (logs.empty())
            {
                cout << "No Logs to Display\n";
            }
            else
            {
                cout << "Commit History: \n";
                while (!logs.empty())
                {
                    cout << logs.top() << endl;
                    commits.push(logs.top());
                    logs.pop();
                }
                while (commits.size())
                {
                    logs.push(commits.front());
                    commits.pop();
                }
            }
            break;
        }
        case 10: // Displaying the current branch
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Current Branch for AVL Tree is: " << AVLbranches[AVLc] << endl;
                }
                break;
            }

            case 2:
            {
                if (RBb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    cout << "Current Branch for RB Tree is: " << RBbranches[RBc] << endl;
                }
                break;
            }
            }
            break;
        }
        case 11: // Saving the Repository
        {
            switch (curr)
            {
            case 1:
            {
                if (AVLb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    AVLtree[AVLc].save(AVLtree[AVLc].root);
                }
                break;
            }

            case 2:
            {
                if (RBb == 0) // empty repository
                {
                    cout << "Please Initialize the Repository first\n";
                    break;
                }
                else
                {
                    RBtree[RBc].save(RBtree[RBc].root);
                }
                break;
            }
            case 3:
            {
            }
            }

            break;
        }
        case 12: // Branch Switching
        {
            switch (curr)
            {
            case 1:
            {
                cout << "Switching to Another Repository : ";
                if (RBtree[0].root)
                {
                    cout << "Switched to " << RBbranches[0] << endl;
                    curr = 1;
                    logs.push("Swtiched Repo to " + RBbranches[0] + " Repository");
                }
                else
                {
                    cout << " No other Repository Exists\n";
                }
                break;
            }

            case 2:
            {
                cout << "Switching to Another Repository : ";
                if (AVLtree[0].root)
                {
                    cout << "Switched to " << AVLbranches[0] << endl;
                    curr = 1;
                    logs.push("Swtiched Repo to " + AVLbranches[0] + " Repository");
                }
                else
                {
                    cout << "No other Repository Exists\n";
                }
                break;
            }
            case 3:
            {
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
            }
            break;
        }
        }
    }

    delete[] head;
    for (int i = 0; i < rows - 1; i++)
    {
        delete[] data[i];
    }

    return 0;
}