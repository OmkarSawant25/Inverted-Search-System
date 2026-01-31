# Inverted Search System (C)

## 📌 Project Overview

The **Inverted Search System** is a command-line based text indexing application written in **C**, designed to efficiently index and search unique words across multiple text files. The system builds an **inverted index** using a **hash table combined with linked lists**, enabling fast lookup of words and their occurrences across files.

This project demonstrates strong fundamentals of **data structures**, **file handling**, **modular programming**, and **memory management** in C, making it ideal for academic evaluation and technical portfolios.

---

## ✨ Key Features

* ✅ **File Validation**

  * Accepts only `.txt` files
  * Rejects empty files
  * Avoids duplicate file inputs

* 🗂 **Dynamic Database Creation**

  * Builds the inverted index at runtime
  * Automatically categorizes words using a hash table

* 🔍 **Word Search**

  * Search for a word to find:

    * Number of files containing it
    * File-wise word frequency

* 📊 **Database Display**

  * Displays the entire inverted index in a readable format

* 💾 **Save Database**

  * Persist the current database to a backup file

* 🔄 **Update / Load Database**

  * Reload database from a previously saved backup file

---

## 🧠 Data Structure Architecture

### Hash Table

* Size: **27 slots**
* Indexing Logic:

  * `0 – 25` → Words starting with `a` to `z`
  * `26` → Words starting with special characters or digits

### Node Hierarchy

| Component     | Description                                                          |
| ------------- | -------------------------------------------------------------------- |
| **Main Node** | Stores a unique word, file count, and link to sub-nodes              |
| **Sub Node**  | Stores file name, word count in that file, and link to next sub-node |

### Relationship Diagram (Conceptual)

```
Hash Table [27]
     |
     v
 Main Node (word)
     |
     v
 Sub Node -> Sub Node -> NULL
```

---

## 🧩 Project Structure

```
Inverted_Search/
│
├── main.c        // Menu-driven execution logic
├── validate.c    // File validation (extension, empty, duplicates)
├── database.c    // Create, search, display, save, update database
├── helper.c      // Utility/helper functions
├── header.h      // Structures, macros, function declarations
└── README.md
```

---

## ⚙️ Installation & Compilation

### Prerequisites

* GCC Compiler (Linux recommended)

### Compile the Project

```bash
gcc main.c database.c helper.c validate.c -o inverted_search
```

### Run the Executable

```bash
./inverted_search file1.txt file2.txt file3.txt
```

> ⚠️ **Note:** At least one valid `.txt` file must be provided as a command-line argument.

---

## 📋 Menu Options

Once the program starts, you will be presented with an interactive menu:

| Option | Description                        |
| ------ | ---------------------------------- |
| 1      | Create Database                    |
| 2      | Display Database                   |
| 3      | Search Word                        |
| 4      | Save Database to File              |
| 5      | Update / Load Database from Backup |
| 6      | Exit                               |

---

## 💾 Backup File Format

The database is saved in a structured text format for easy reloading:

```
#index;word;file_count;file_name;word_count;file_name;word_count;#
```

### Example

```
#0;hello;2;file1.txt;3;file2.txt;1;#
```

This format allows accurate reconstruction of the hash table, main nodes, and sub-nodes.

---

## 👨‍💻 Author

**Omkar Ashok Sawant**
Final Year Engineering Student
Embedded Systems & Linux Systems Programming Enthusiast

---

## 🚀 Learning Outcomes

* Practical implementation of **Inverted Indexing**
* Strong understanding of **Hash Tables & Linked Lists**
* Modular C programming with multiple source files
* Real-world use of **file I/O and persistence**

---

## 📄 License

This project is intended for **educational and academic use**.

---

⭐ *If you find this project helpful, consider starring the repository!*
