# ABCU Advising Assistance Program

A small C++ command-line application I built for **CS-300: Data Structures and Algorithms** at Southern New Hampshire University.

The idea behind the project is simple: an academic advisor should be able to load a course catalog, see the available courses in order, and look up a course's prerequisites without searching through a CSV file manually.

## What the program does

- Reads course information from a CSV file and creates `Course` objects.
- Stores the courses in a `vector` and sorts them by course number.
- Displays the full catalog in alphanumeric order.
- Searches for individual courses using binary search and displays their prerequisites.
- Accepts course numbers in lowercase or uppercase.
- Handles common input problems, such as a missing file or an invalid menu selection.

## Getting started

You'll need a C++ compiler such as `g++`.

Compile the program from the project directory:

```bash
g++ -std=c++17 ProjectTwo.cpp -o ProjectTwo
```

Then run it:

```bash
./ProjectTwo
```

The program displays a menu:

```text
1. Load Data Structure.
2. Print Course List.
3. Print Course.
9. Exit
```

Choose **1** and enter the path to a course CSV file. Once it loads, choose **2** to view the course list or **3** to search for a course number such as `CSCI400`.

### CSV format

Each row contains a course number, a title, and optionally one or more prerequisite course numbers:

```csv
CSCI100,Introduction to Computer Science
CSCI101,Introduction to Programming in C++,CSCI100
CSCI200,Data Structures,CSCI101
```

The course CSV is read at runtime, so you can enter its filename or full path when prompted. The university-provided course data may not be included in this repository.

## How I approached it

For Project One, I compared vectors, hash tables, and binary search trees. I chose a **sorted vector** for the final application because the program mainly loads a catalog once and then reads from it. Sorting the data makes it straightforward to display every course in order, while binary search gives an efficient way to find a specific course.

Working on Project Two helped me connect those design choices to actual C++ code. I spent time learning how to parse input with `getline()` and `stringstream`, build objects from that data, pass vectors by reference, and debug issues that didn't show up as compiler errors.

## AI acknowledgment

I used ChatGPT as a learning and development resource while working on this project. It helped me discuss C++ concepts, think through the program's structure, review code, and troubleshoot errors. I worked through the implementation, tested the behavior, and made changes as I developed my understanding.

## Author

**Kamarky Jimenez**  
CS-300 — Southern New Hampshire University