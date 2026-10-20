
/*
 * Project: CS-300 Project Two - ABCU Advising Assistance Program
 * Author: Kamarky Jimenez
 * Course: CS-300 Data Structures and Algorithms
 *
 * Program Description:
 * This C++ application is designed to assist academic advisors
 * at ABCU University with retrieving course information.
 *
 * The program reads course data from a CSV file, constructs
 * Course objects, and stores them in a vector. The vector is
 * sorted alphanumerically by course number, allowing users to
 * display the complete course catalog or search for individual
 * courses and their prerequisites using binary search.
 *
 * The application also includes input handling and data
 * validation to support reliable program behavior.
 *
 * AI Acknowledgment:
 * ChatGPT was used as a learning and development resource
 * throughout this project. AI assistance supported explanations
 * of C++ concepts, implementation planning, code review,
 * troubleshooting, and debugging.
 * 
 * AI Reference (APA 7):
 * OpenAI. (2026). ChatGPT [Large language model].
 * https://chatgpt.com/
 *
 * The development process involved writing, reviewing, testing,
 * and refining the program to better understand how data
 * structures and algorithms are applied in software development.
 */

 
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;


// Defining Course structure
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

//Display menu for ABCU Application
void displayMenu(){
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do ?" << endl;
}

//Comparison function used by sort()
bool compareCourses(const Course& a, const Course& b){
    // This compares the course numbers lexicographically, meaning character-by-character ordering.
    return a.courseNumber < b.courseNumber;
}

//Binary search function used by option 3 in the application
int binarySearch(const vector<Course>& courses, const string& target){
    int left = 0;
    int right = courses.size() - 1;
    int mid;

    while(left <= right){

        mid = (left + right) / 2;

        if(courses[mid].courseNumber == target){
            return mid;
        }
         else if(courses[mid].courseNumber < target){
            left = mid + 1;
        }     
         else {
            right = mid - 1;
        }
        
    }

    return -1;
}

//Load course function loads csv file, checks filename, validates courses, and checks for duplicates. Also creates vector of Courses.
bool loadCourses(const string& filename, vector<Course>& courses){
    
    ifstream file(filename);

    if(!file.is_open()){
        cout << "Unable to open file." << endl;
        return false;
    }

    vector<Course> tempCourses;
    string line;
    
    while(getline(file, line)){
        
        // Remove carriage return if present.
        if(!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if(tokens.size() < 2){
            cout << "Invalid course record." << endl;
            return false;
        }

        Course course;

        course.courseNumber = tokens[0];
        course.courseName = tokens[1];

        for(size_t i = 2; i < tokens.size(); i++){
            if(!tokens[i].empty()){
                course.prerequisites.push_back(tokens[i]);
                }
            }

        tempCourses.push_back(course);
    }

    // Duplicate and validation checks.
    sort(tempCourses.begin(), tempCourses.end(), compareCourses);
    
    for(size_t i = 1; i < tempCourses.size(); i++){
        if(tempCourses[i].courseNumber == tempCourses[i - 1].courseNumber){
            cout << "Duplicate course number found: " << tempCourses[i].courseNumber << endl;

            return false;
        }
    }

    for (const Course& course : tempCourses) {

        for (const string& prereq : course.prerequisites) {

            int result = binarySearch(tempCourses, prereq);

            if (result == -1) {
                cout << "Invalid prerequisite: " << prereq
                    << " for course " << course.courseNumber << endl;

                return false;
            }
        }
    }
    
    courses.swap(tempCourses);
    return true;

}

//Print course function uses binary search to find a course, print the course and its following prerequisites.
void printCourse(const vector<Course>& courses, const string& target){
    
    int index = binarySearch(courses, target);

    if(index == -1){
        cout << "Course not found." << endl;
    } 
    else {
       
        cout << courses[index].courseNumber << " - " << courses[index].courseName << endl;

        if(courses[index].prerequisites.size() != 0){
        cout << "Prerequisites: ";

        for (size_t i = 0; i < courses[index].prerequisites.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }

            cout << courses[index].prerequisites[i];
        }

        cout << endl;
    } else {
        cout << "No prerequisites required." << endl;
    }
        
    }
}

//Prints all courses sorted by course number.
void printCoursesSorted(vector<Course>& courses){
    for(const Course& course : courses){
        cout << course.courseNumber << " - " << course.courseName << endl;
    
    }
}


int main() {

    vector<Course> courses;
    int choice = 0;

    std::cout << "Welcome to the course planner." << std::endl;

    // Main event loop
    while (choice != 9) {

        displayMenu();
        
        // Handles choice errors.
        if (!(cin >> choice)) {

            if (cin.eof()) {
                break;
            }

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input." << endl;

            continue;
        }

        //Application control flow
        switch (choice) {
            case 1: {
                string filename;

                cout << "Enter file: " << endl;
                getline(cin >> ws, filename);

                if(loadCourses(filename, courses)){
                    cout << "Courses loaded successfully!" << endl;
                } else {
                    cout << "Failed to load courses." << endl;
                }

                break;
            }
            case 2:
                if(courses.empty()){
                    cout << "Please load a course file first." << endl;
                } else{
                    printCoursesSorted(courses);
                }
                
                break;

            case 3: {
                string course;
                
                if(courses.empty()){
                    cout << "Please load course file first." << endl;
                    break;
                } 

                cout << "Enter course number: (e.g CSCI400)" << endl;
                
                getline(cin >> ws, course);
                
                for(char& c : course){
                    c = toupper(c);
                }

                printCourse(courses, course);
                
                break;
            }    
            case 9:
                // Exit
                break;

            default:
                cout << "Invalid menu option." << endl;
        }

    }

    std::cout << "Thank you for using the course planner!" << std::endl;

    return 0;
}