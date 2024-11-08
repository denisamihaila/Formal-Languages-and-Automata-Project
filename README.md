# 🔄 Formal Languages and Automata Project

## Overview

This project focuses on **Formal Languages and Automata Theory** and implements various types of finite automata and related algorithms. It showcases the use of theoretical computer science principles applied to automata theory, particularly in recognizing and processing formal languages.

The project includes implementations of deterministic, non-deterministic, and lambda-non-deterministic finite automata, as well as conversions and algorithms for automata optimization. This project is an excellent demonstration of foundational concepts in theoretical computer science, with applications in language processing and computational linguistics.

## 🚀 Features

- **Deterministic Finite Automata (DFA)**: A classical DFA implementation that processes strings deterministically.
- **Non-Deterministic Finite Automata (NFA)**: Allows multiple potential transitions for processing each input symbol.
- **Lambda-Non-Deterministic Finite Automata (λ-NFA)**: Implements transitions without consuming input symbols.
- **NFA to DFA Transformation**: Converts non-deterministic automata into deterministic automata for simplified processing.
- **DFA Minimization**: Optimizes DFA by reducing the number of states while preserving functionality.
- **Pushdown Automaton (PDA)**: A stack-based automaton capable of recognizing context-free languages.
- **Finite State Transducer (FST)**: Extends finite automata by producing output symbols, useful in tasks like string translation.
- **CYK Algorithm**: Implements the Cocke–Younger–Kasami algorithm for parsing strings within a context-free grammar.

## 📂 Project Structure

The project is organized into classes and modules, each representing a specific type of automaton or algorithm.

### 🔹 Classes and Modules

- **DFA (Deterministic Finite Automaton)**: Handles deterministic state transitions based on input symbols.
- **NFA (Non-Deterministic Finite Automaton)**: Manages non-deterministic transitions where multiple transitions may exist for a given symbol.
- **Lambda-NFA (λ-NFA)**: Extends NFA with epsilon (λ) transitions, allowing transitions that don’t consume input.
- **NFAtoDFA**: Implements the subset construction algorithm to convert NFA to DFA.
- **DFAMinimizer**: Minimizes the DFA by merging equivalent states to improve efficiency.
- **PDA (Pushdown Automaton)**: A stack-based automaton that processes strings of a context-free language.
- **FST (Finite State Transducer)**: Produces output symbols based on state transitions, extending the functionality of basic automata.
- **CYK Parser**: Implements the CYK algorithm for recognizing strings in a context-free grammar.

Each module is designed to be modular and reusable, allowing each automaton type to be tested and extended independently.

## 📝 Usage

Each automaton or algorithm has been implemented to allow for isolated testing. To test a specific feature, follow these steps:

1. Choose the automaton type or algorithm you want to test (e.g., DFA, NFA, PDA).
2. Configure the input based on the requirements of that automaton (e.g., alphabet, transitions, initial state, final states).
3. Run the automaton or algorithm to observe its behavior on the given input.

### Example Flow

1. **DFA**: Configure states, transitions, initial and final states, and test if a string is accepted by the automaton.
2. **NFA to DFA Conversion**: Create an NFA, then use the NFAtoDFA module to convert it into an equivalent DFA.
3. **PDA**: Set up a stack-based automaton to recognize context-free language patterns.
4. **CYK Algorithm**: Provide a context-free grammar and test if a string belongs to the language.

## ✨ Code Highlights

This project demonstrates several key concepts and techniques in automata theory and C++ programming:

1. **Object-Oriented Design**: Each automaton type is encapsulated in a class with relevant methods and data.
2. **Efficiency**: DFA minimization and NFA to DFA conversion are optimized for performance, making complex automata more manageable.
3. **Algorithmic Complexity**: The CYK algorithm and PDA implementation showcase efficient handling of context-free languages.
4. **Modularity**: Each automaton and algorithm can be tested independently, allowing for clear, modular code.
5. **Memory Management**: Uses C++ constructs to manage memory effectively, particularly for large state machines and grammars.

## 🔧 Future Improvements

Potential improvements to expand functionality and flexibility:

- **Visualization of Automata**: Add graphical representation to visualize state transitions and processing steps.
- **Interactive User Interface**: Provide a simple UI for users to input strings, select automaton types, and see results.
- **Support for Additional Automata**: Extend the project to include Turing machines or additional parsing algorithms.
- **Performance Enhancements**: Optimize memory and processing for large automata and grammars.

