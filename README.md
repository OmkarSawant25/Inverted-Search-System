# 🔍 Inverted Search System — Text Indexing Using Hash Tables in C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Concept](https://img.shields.io/badge/Concept-Data%20Structures-orange.svg)
![Build](https://img.shields.io/badge/Build-GCC-green.svg)

## 📌 Project Overview

The **Inverted Search System** is a command-line based text indexing application written in **C**, designed to efficiently index and search unique words across multiple text files. The system builds an **inverted index** using a **hash table combined with linked lists**, enabling fast lookup of words and their occurrences across files.

This project was developed as part of **Data Structures training** while pursuing the **Emertxe Certified Embedded Professional (ECEP)** course. It showcases practical implementation of core concepts such as hashing, linked lists, file handling, and modular C programming.

---

## ❓ Why This Project?

Searching for words across multiple text files becomes inefficient when done linearly. This project demonstrates how **Inverted Indexing**—a technique widely used in **search engines**—can dramatically improve search performance.

By organizing words using a **hash table** and tracking file-wise occurrences using **linked lists**, the system enables:

* Faster word lookup
* Scalable indexing for multiple files
* Efficient storage of word-to-file mappings

---

## ✨ Key Features

* ✅ **Robust File Validation**

  * Accepts only `.txt` files
  * Rejects empty files
  * Prevents duplicate file indexing

* 🗂 **Dynamic Database Creation**

  * Builds the inverted index at runtime
  * Automatically categorizes words using hash-based indexing

* 🔍 **Efficient Word Search**

  * Displays:

    * Number of files containing the word
    * File-wise word frequency

* 📊 **Database Display**

  * Visual representation of the entire inverted index

* 💾 **Database Persistence**

  * Save the database to a structured backup file
  * Reload and reconstruct the database from backup

* 🧩 **Modular Design**

  * Clean separation of validation, database logic, and helpers

---

## 🧠 Data Structure Architecture

### 🔹 Hash Table

* Size: **27 slots**
* Indexing Logic:

  * `0 – 25` → Words starting with `a` to `z`
  * `26` → Words starting with digits or special characters

### 🔹 Node Hierarchy

| Component     | Description                                                          |
| ------------- | -------------------------------------------------------------------- |
| **Main Node** | Stores a unique word, file count, and link to sub-nodes              |
| **Sub Node**  | Stores file name, word count in that file, and link to next sub-node |

### 🔹 Conceptual Structure

```
Hash Table [27]
     |
     v
 Main Node (word)
     |
     v
 Sub Node -> Sub Node -> NULL
```

This layered structure ensures efficient word indexing and quick retrieval of file-specific information.

---

## 🧩 Project Structure

```
Inverted_Search/
│
├── main.c        // Menu-driven execution and user interaction
├── validate.c    // File validation logic
├── database.c    // Create, search, display, save, update database
├── helper.c      // Utility and helper functions
├── header.h      // Structures, macros, function prototypes
└── README.md
```

---

## ⚙️ Installation & Compilation

### Prerequisites

* GCC Compiler (Linux recommended)

### Compile

```bash
gcc main.c database.c helper.c validate.c -o inverted_search
```

### Run

```bash
./inverted_search file1.txt file2.txt file3.txt
```

> ⚠️ At least one valid `.txt` file must be provided as a command-line argument.

---

## 📋 Menu Options

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

```
#index;word;file_count;file_name;word_count;file_name;word_count;#
```

### Example

```
#0;hello;2;file1.txt;3;file2.txt;1;#
```

This structured format enables accurate reconstruction of the hash table and linked lists.

---

## 🎯 Learning Outcomes

* Hands-on implementation of **Inverted Indexing**
* Deep understanding of **Hash Tables & Linked Lists**
* Practical experience with **file I/O and persistence**
* Modular and scalable C program design
* Improved problem-solving and algorithmic thinking

---

## 👤 Author

**Omkar Ashok Sawant**  
Pursuing *Emertxe Certified Embedded Professional (ECEP)*  
Embedded Systems & Linux Programming Enthusiast  

---

## 📌 Note

This project is developed for **educational and learning purposes**, focusing on efficient text indexing and search using core Data Structure concepts.

⭐ *If you find this project helpful, consider starring the repository!*
