# MyVector - Custom C++ STL-like Container 🚀

A fully functional, generic dynamic array implementation written completely from scratch in modern C++. 

This project was created as a deep dive into the internal mechanics of the C++ Standard Template Library (STL). Instead of relying on `std::vector`, I built this container to thoroughly understand dynamic memory allocation, object lifecycles, and advanced C++ semantics.

## 🧠 Core Concepts Explored & Implemented

This project is not just a simple array wrapper; it strictly follows C++ best practices and implements crucial language features:

* **Dynamic Memory Management:** Raw pointer manipulation, handling heap allocations safely, and preventing memory leaks.
* **The Rule of Five:** Full and correct implementation of:
  * Destructor
  * Copy Constructor
  * Copy Assignment Operator
  * Move Constructor (`noexcept`)
  * Move Assignment Operator (`noexcept`)
* **Templates (Generic Programming):** The container is fully generic (`template <typename T>`) and works with any data type, including complex objects.
* **Explicit Object Lifecycle Control:** Using manual destructor calls (`this->_data[i].~T()`) for `pop_back()` and `clear()` to ensure zero-overhead capacity management without memory leaks (especially for non-trivial types like `std::string`).
* **Iterator Support:** Custom `begin()` and `end()` pointers, allowing the container to seamlessly work with C++11 range-based for loops (`for (auto& item : vec)`).
* **Exception Safety:** Careful ordering of operations (e.g., in `reserve()` and assignment operators) to ensure that if an allocation fails, the original data remains intact.

## 🛠️ API / Supported Methods

The container mirrors the core functionality of `std::vector`:

* **Element Access:** `operator[]`, `front()`, `back()`, `data()`
* **Modifiers:** `push_back()`, `pop_back()`, `insert()`, `erase()`, `clear()`
* **Capacity:** `size()`, `capacity()`, `empty()`, `reserve()`, `shrink_to_fit()`

## 💻 Quick Usage Example

```
#include <iostream>
#include <string>
#include "MyVector.hpp"

int main() {
    // Initialization with initializer_list
    MyVector<std::string> words = {"Hello", "World"};
    
    // Dynamic resizing
    words.push_back("from");
    words.push_back("MyVector!");

    // Range-based for loop support
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    // Output: Hello World from MyVector!
    
    // Capacity management
    words.reserve(100); 
    std::cout << "\nCapacity: " << words.capacity(); // 100
    
    words.shrink_to_fit();
    std::cout << "\nCapacity after shrink: " << words.capacity(); // 4

    return 0;
}
```

