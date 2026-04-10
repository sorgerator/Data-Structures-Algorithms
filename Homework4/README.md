[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Qx0cH72O)
# Homework 4: Improving the phonebook system
**Course**: Data Structures and Algorithms

**Due Date**: _December 22nd, 2025 by 23:59_

## The scenario

While the solution with binary search that _you already implemented_ works and the management is happy, you start thinking - this customer database often gets updated; is it not a bit “wasteful” to have to re-sort the file every time that happens, make a new file, and load it into the system? It would be a lot better if you could use a _data structure_ that is _already designed_ for _fast search_ and _retrieval_ operations.

After some thinking, it hits you: a **binary search tree**. You get to work once again.

As a reminder, here is how the CSV file ([available here](https://drive.google.com/file/d/1Rqk3sXKx79EM9S_K1tKDkZJYAjHqofud/view)) looks like: it contains records for 1,000,000 (one million) active customers, with the **first row** of the CSV file being the column names. Some example data looks like this (notice the ; separators between values):
![img.png](resources/img.png)
```
Deschamps, René;rue Suzanne Leroux;Perretdan;06346;France;+33 2 90 37 88 59
Mckee, Thomas;296 Sanders Roads Apt. 856;Hernandezburgh;18218;United States;958.718.0301
Williams, Samuel;4986 Adam Path Apt. 370;Livingstonside;31544;United States;335-608-6185x14031
Jasprica, Biserka;Vončinina 5a;Split;40769;Croatia;031 423 548
Camanni, Galasso;Strada Sgarbi, 5;Massa E Cozzile;28019;Italy;0565913896
Brown, George;Flat 1 Moore locks;South Danielmouth;E43 7SB;United Kingdom;+443069990278
Hövel, Janet;Kühnertplatz 76;Fallingbostel;04542;Germany;08945 734027
Dixon, Laura;013 Craig Throughway;Johnsonberg;46109;United States;834-480-5285
Hering, Luisa;Langering 8/8;Gräfenhainichen;26553;Germany;05971 44694
…
```

## Task 1: Create a search system using a binary search tree

It is now up to you to take [this large CSV file](https://drive.google.com/file/d/1Rqk3sXKx79EM9S_K1tKDkZJYAjHqofud/view) and make it into a _searchable system_ using **binary search trees**.

So, you get to work.

### Part 1: Implement the Entry class and file utils

You should already have the _basic outlines_ for these classes and structs created from **Homework 3**, but if not, here are the descriptions again.

For one, you need to create an **Entry** struct (in `include/Entry.h`) that will hold the relevant information for each user record. The Entry class should contain the user's surname and name, street address, city, postcode, country and phone number. Moreover, the Entry struct should _overload all comparison operators_, so you can use it in a sorting algorithm later.

Next up, you need a way to work with the input file. In the **FileUtils** class (in `src/FileUtils.cpp`) you will need to implement:

- `BinarySearchTree read_file(const std::string& file_path, int len)` → given a file path and the total number of lines, _read all lines_ from the file and return _a binary search tree_ containing the **Entry objects**.

### Part 2: Implement a binary search tree

Next up, you need to implement a `Node` struct (in `include\Node.h`) and `BinarySearchTree` class in (`src/BinarySearchTree.cpp`).

The `Node` struct should have references to the **key** - customer name and surname, and the **values** - a `std::vector` of `Entry` values (feel free to look up how **vectors** work in C++, if you are not sure). Since there are _duplicates_ in the CSV (e.g. _four (4) entries_ for “Clerc, Agnès”), the “values” property should be able to _contain multiple entries_ associated with the same name. Moreover, the Node class should contain references to the _left_ and _right_ children.

In the `src/BinarySearchTree.cpp`, implement:

- `std::vector<Entry> get(std::string searchable_name)` → given a customer name, return _a vector of Entries_ that match the name.
  - Example: for “Clerc, Agnès”, return all 4 corresponding values.
  - If an entry with a given name **does not exist**, return `nullptr`. 
  - The user will search for a name in the format “Surname, Name”.
    - You do not need to support partial matches - it is enough to support the exact name match.
  - The method should also **print out** _how many edges_ were found **on the path** towards the node (from the _root_ to _that node_).

- `void put(std::string searchable_name, Entry entry)` → given a customer name and a value (Entry object), do one of two things:
  - If the name _does not already exist_ in the tree, _add a new node_ with the initial entry in the vector of entries.
  - If the name _already exists_ in the tree, _update the vector of node values_ with the newly added entry.
- **any additional methods and properties** which are required for a binary search tree to work (recursive / private methods, additional properties, etc.)

### Part 3: Sorting the file using inorder traversal
Use **inorder traversal** to **sort** the entries _by customer name_ (surname, name). You should implement the method `void inorder_sort(const std::string& file_path)` which applies inorder traversal to the tree and **saves all entries** into a _new_ **sorted** _CSV file (`file_path`) of the same format_ as the original (same order of columns, semicolons as separators).

You **must not** use any other search algorithms or “workarounds” on the tree (e.g. moving all data into a list and sorting that list) - the picking of the next value must be done _explicitly_ using inorder traversal operations on the _tree itself_.

**You DO NOT NEED to upload the sorted file!**

### Part 4: Putting it all together

With all the required classes in place, you can get to work. Implement the search system inside the **main()** method of **src/main.cpp** file.

It is left up to you how to design the "UI / UX" of the system. You are also free to add any additional helper methods if you need them. The main logic of the system should be as follows:

- When the application is started:
    - The _unsorted_ file is loaded into a binary search tree
- The user is then asked to type in a "_Surname, Name_" combination they want to find, _or_ -1 if they want to close the program.
- If the user types in a name, the application will _try to locate the entry(ies)_ in the binary search tree.
    - If the entry is **found**, the application needs to _print out_:
      - _how many entries_ were found 
      - available details about _each entry_ in a _nicely formatted way_
      - _the number of edges_ encountered until the entry was found.
    - If the entry is _not found_, the application should print out an error message
- When a search is done, the user is prompted to enter a name again. If they enter it, the search process should repeat. If they enter -1, the application should terminate.

Here is an example of how the interaction could look like:
![img.png](resources/img_21.png)
---
![img.png](resources/img_22.png)
---
![img.png](resources/img_23.png)
## Testing the Application
You can use some of the below **expected values** from the file for testing:

- Clerc, Adrien → 2 entries, 22 edges
- Sladonja, Mira → 3 entries, 30 edges
- Dominguez, Lauren → 1 entry, 22 edges
- Singleton, Matthew → 3 entries, 28 edges
- Drub, Ismet → 1 entry, 31 edges
- Smith, John → 101 entries, 19 edges

To verify the correctness of your implementation, you can run the **unit tests** that come with this repository.

You have two ways to run tests.

1. You can run each test _individually_ by clicking on the "Run" button next to the `TEST_CASE` keywords in the `test/tests.cpp` file.

![img_19.png](resources/img_19.png)
![img.png](resources/img_20.png)

   There are 4 tests in total, so running each one individually might become tedious, but it is a good way to test out each individual piece of functionality.
2. You can run _all tests at once_ by clicking on the "Run" button next to the `add_test` command in the `CMakeLists.txt` file.

![img_4.png](resources/img_4.png)
![img_5.png](resources/img_5.png)

### Q/A: I cannot see the "Run" icon.
If you cannot see the "Run" icon (green play button) for whatever reason next to your tests, the most likely explanation is that your project is _not properly built_.

To re-build your project, click on the `CMake` icon (a triangle with another triangle in it) in the _bottom-left sidebar_ of CLion, followed by `Reload CMake Project`.

![img_7.png](resources/img_7.png)
![img_8.png](resources/img_8.png)

After the project is reloaded, you should be able to run your tests (you might need to close and re-open the test file).

If you still cannot run the tests, contact the course professor.

## Implementation Constraints

**You must not:**
- remove any of the methods in the existing files, rename them or change their signatures.

**You should:**
- implement the missing method bodies for the required functionalities, and make sure they return proper output (if any)
- implement any additional helper methods / variables / classes, if you need them for the solution.

**NOTE:** You **do not need to upload** the original and sorted files with your homework; **just upload the homework code**.

---

https://ibu.edu.ba 