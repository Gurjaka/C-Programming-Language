<div align="center">

<img alt="C" src="assets/C_Programming_Language.svg" width="120px"/>

# <samp>C-Programming-Language</samp>

![GitHub Repo stars](https://img.shields.io/github/stars/Gurjaka/C-Learning?style=for-the-badge&labelColor=2e3440&color=5e81ac) ![GitHub last commit](https://img.shields.io/github/last-commit/Gurjaka/C-Learning?style=for-the-badge&labelColor=2e3440&color=5e81ac) ![GitHub repo size](https://img.shields.io/github/repo-size/Gurjaka/C-Learning?style=for-the-badge&labelColor=2e3440&color=5e81ac)

## <samp>Welcome to the **C-Programming-Language** repository! This is my personal journey of learning the C. It contains my practice programs, experiments, and notes as I explore C concepts and improve my skills.</samp>

</div>

## 📝 Table of Contents

- 🎯 [Introduction](#-introduction)
- 🤔 [Why This Repository](#-why-this-repository)
- 🚀 [Getting Started](#-getting-started)
- 🗂️ [Directory Structure](#%EF%B8%8F-directory-structure)
- 🖥️ [Tmux](#tmux)
- 🤝 [Contributing](#-contributing)
- 📜 [License](#-license)

---

## 🎯 Introduction

C is a powerful and widely-used programming language, known for its efficiency and close-to-hardware capabilities. This repository is my personal sandbox to:

- Understand C syntax and concepts.
- Practice problem-solving using C.
- Experiment with different coding techniques and tools.

---

## 🤔 Why This Repository

This repository is primarily for my learning and self-improvement. By sharing my progress publicly, I hope to:

- Document my journey in a structured way.
- Receive constructive feedback from the community.
- Help others who might be starting their own journey in C.

---


## 📚 Book Reference

The book I will be following and referencing throughout this repository is the [C Programming Language - 2nd Edition (OCR)](https://seriouscomputerist.atariverse.com/media/pdf/book/C%20Programming%20Language%20-%202nd%20Edition%20(OCR).pdf). This book will serve as the primary guide for the C programming concepts, examples, and exercises found in this repository.

---

## 🚀 Getting Started

If you're here to follow along or try out the programs, you'll need:

- A C compiler such as GCC or Clang.
- A text editor or IDE of your choice (e.g., Vim, Visual Studio Code, etc.).

### Clone the Repository

```bash
git clone https://github.com/Gurjaka/C-Programming-Language.git
cd C-Programming-Language
```

### Compile and Run a Program

Navigate to the directory containing the program you want to run and compile it using:

```bash
cc program_name.c -o ./compiled/program_name
./compiled/program_name
```

For example:

```bash
cc hello_world.c -o ./compiled/hello_world
./compiled/hello_world
```

---

## 🗂️ Directory Structure

The directory structure of this repository is as follows:

```
C-Programming-Language/
├── assets
├── LICENSE
├── readme.md
├── src
│   ├── 1.0-non-book-related
│   ├── 1.1-getting-started
│   ├── 1.2-variables-arithmetic-expressions
│   ├── 1.3-for-statement
│   ├── 1.5-character-input-output
│   ├── 1.6-arrays
│   ├── 1.7-functions
│   ├── 1.8-arguments-call-by-value
│   ├── 1.9-character-arrays
│   ├── 1.10-external-variables-and-scope
├── tasks
│   ├── Chapter-1:Tutorial-Introduction
│   ├── Chapter-2:Types-Operators-Expressions
│   ├── Chapter-3:Control-Flow
│   ├── Chapter-4:Functions-Program-Structure
│   ├── Chapter-5:Pointers-Arrays
│   ├── Chapter-6:Structures
│   ├── Chapter-7:Input-Output
│   └── Chapter-8:The-UNIX-System-Interface
└── tmux.sh
```

> Note: Each chapter includes its exercises and compiled programs.
> The "Tasks" directory contains Markdown files with descriptions for the exercises.

---

## 🖥️ Tmux

The tmux.sh script sets up a custom tmux session for an organized development environment. It creates a tmux session named "C", splits the terminal window into multiple panes for different tasks, and launches relevant programs in each pane. This setup allows the user to code, track tasks, compile and run a programs simultaneously in a single terminal session.

Layout:
```bash
 _________________________________
|                     |           |
|         CODE        |           |
|         NVIM        |   TASKS   |
|                     |   NVIM    |
|_____________________|           |
|                     |           |
|         GCC         |           |
|_____________________|___________|
```

--- 

## 🤝 Contributing

While this is a personal learning project, contributions are welcome if you'd like to:

- Suggest improvements to my code.
- Share insights or tips for better coding practices.
- Point out mistakes or bugs.

Feel free to fork the repository, make your changes, and open a pull request. Please include clear comments explaining your changes.

---

## 📜 License

This repository is licensed under the MIT License. Feel free to use, modify, and distribute the code in this repository. See the [LICENSE](LICENSE) file for details.

---

<p align="center">
  <strong>Thanks for visiting!</strong> 😊
</p>
