// Jacob McLemore
// 6/22/2025

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

// 1. Define the Course Structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// 2. Define the Binary Search Tree Node Structure
struct Node {
    Course course;
    Node* left;
    Node* right;
};

// 3. Declare root pointer for BST
Node* root = nullptr;

// 4. Function prototypes matching definitions
Node* insertCourse(Node* node, Course course);
Node* searchBST(Node* node, const string& courseNumber);
void printInOrder(Node* node);

// 5. Main Function
int main() {
    char input;

    do {
        // Display Menu
        cout << "\nWelcome to the course planner!" << endl;
        cout << "Enter a selection below:" << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;

        cin >> input;

        switch (input) {
        case '1': {
            cout << "Enter filename: ";
            string filename;
            cin >> filename;

            ifstream iFile(filename);
            if (!iFile.is_open()) {
                cout << "Error opening file: " << filename << endl;
                break;
            }

            // First Pass: Reads lines and collects course numbers
            vector<string> lines;
            set<string> courseNumberSet;
            string line;
            while (getline(iFile, line)) {
                if (!line.empty()) {
                    lines.push_back(line);

                    stringstream ss(line);
                    string courseNumber;
                    getline(ss, courseNumber, ',');
                    courseNumberSet.insert(courseNumber);
                }
            }
            iFile.close();

            // Second Pass: Parses lines into Course objects and inserts
            for (const string& line : lines) {
                vector<string> parts;
                stringstream ss(line);
                string part;
                while (getline(ss, part, ',')) {
                    parts.push_back(part);
                }

                if (parts.size() >= 2) {
                    Course c;
                    c.courseNumber = parts[0];
                    c.courseTitle = parts[1];

                    for (size_t j = 2; j < parts.size(); ++j) {
                        if (courseNumberSet.find(parts[j]) != courseNumberSet.end()) {
                            c.prerequisites.push_back(parts[j]);
                        }
                        else if (!parts[j].empty()) {
                            cout << "Warning: Prerequisite not found in course list: " << parts[j] << endl;
                        }
                    }
                    root = insertCourse(root, c);
                }
            }

            cout << "Courses loaded successfully.\n";
            break;
        }
        case '2':
            printInOrder(root);
            break;

        case '3': {
            cout << "Enter course number to search: ";
            string courseNumber;
            cin >> courseNumber;

            Node* result = searchBST(root, courseNumber);
            if (result != nullptr) {
                cout << result->course.courseNumber << ": " << result->course.courseTitle << endl;
                if (!result->course.prerequisites.empty()) {
                    cout << "Prerequisites: ";
                    for (size_t i = 0; i < result->course.prerequisites.size(); ++i) {
                        cout << result->course.prerequisites[i];
                        if (i < result->course.prerequisites.size() - 1)
                            cout << ", ";
                    }
                    cout << endl;
                }
                else {
                    cout << "Prerequisites: None" << endl;
                }
            }
            else {
                cout << "Course not found." << endl;
            }
            break;
        }

        case '9':
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid selection. Please try again." << endl;
            break;
        }

    } while (input != '9');

    return 0;
}

// 6. Inserts course into BST
Node* insertCourse(Node* node, Course course) {
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->course = course;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (course.courseNumber < node->course.courseNumber) {
        node->left = insertCourse(node->left, course);
    }
    else {
        node->right = insertCourse(node->right, course);
    }
    return node;
}

// 7. Searchs BST for a course number
Node* searchBST(Node* node, const string& courseNumber) {
    if (node == nullptr) {
        return nullptr;
    }
    if (courseNumber == node->course.courseNumber) {
        return node;
    }
    if (courseNumber < node->course.courseNumber) {
        return searchBST(node->left, courseNumber);
    }
    else {
        return searchBST(node->right, courseNumber);
    }
}

// 8. In-order traversal to print courses
void printInOrder(Node* node) {
    if (node == nullptr) return;

    printInOrder(node->left);
    cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;
    printInOrder(node->right);
}
