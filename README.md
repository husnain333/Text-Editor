## Huffman Compression and Auto-complete Notepad

This C++ program implements a simple Huffman compression algorithm and an auto-complete feature for a notepad-like application. The program includes classes for the Huffman tree, trie tree, and a basic GUI implemented using Tkinter.

### Huffman Compression

#### Classes
1. **`huffmanTree` Class:** Represents the Huffman tree and includes methods for building the tree, encoding, and decoding text.
   - `filling`: Fills the priority queue with characters and their frequencies.
   - `treeMaking`: Builds the Huffman tree using the priority queue.
   - `makeRoot`: Sets the root of the Huffman tree.
   - `printCode`: Prints the Huffman codes for each character.
   - `decodeHuffman`: Decodes Huffman-encoded text.

2. **`priority_queue` Class:** Represents a priority queue for the Huffman tree nodes.
   - `enqueue`: Adds a node to the priority queue.
   - `enqueueNode`: Adds a node to the priority queue (overloaded for tree nodes).
   - `dequeue`: Removes and returns the front node.
   - `isEmpty`: Checks if the queue is empty.
   - `display`: Displays the nodes in the priority queue.

3. **`Byte` Class:** Manages bytes used for encoding characters.
   - `byteInitialiser`: Initializes the byte array.
   - `fillByte`: Fills the byte array for a specific character.
   - `printByteArray`: Prints the byte array for a specific character.

#### Compression Workflow
1. The user enters a sentence in the console.
2. The program performs Huffman compression and prints the Huffman codes.
3. The compressed data is stored in a file ("CompressionFile.txt").
4. Optionally, the user can choose to store the original sentence for later use.

### Auto-complete Notepad

#### Classes
1. **`tree` Class:** Represents a trie tree for word suggestions and includes methods for insertion, search, loading a dictionary, and providing suggestions.
   - `insert`: Inserts a word into the trie tree.
   - `search`: Searches for a word in the trie tree.
   - `loadtree`: Loads words from a dictionary file into the trie tree.
   - `giveword`: Retrieves a word suggestion based on user input.
   - `giveSuggestion`: Provides an array of word suggestions.

#### Notepad Workflow
1. The user enters text in the console.
2. The program suggests words based on the entered text using the trie tree.
3. The user can choose from the suggested words to complete the sentence.
4. The program can store the entered text or compressed data for later use.

### Usage

1. **Compression:**
   - Enter a sentence in the console.
   - Choose to store the sentence or the compressed data.
   - Compressed data is stored in "CompressionFile.txt."

2. **Auto-complete Notepad:**
   - Enter text in the console.
   - Get word suggestions based on the entered text.
   - Choose a suggestion to complete the sentence.

### File Operations

- **Dictionary File:** The program loads words from "Dictionary.txt" into the trie tree for auto-complete suggestions.
- **Storage Files:** The program stores the entered text and compressed data in "continue.txt" and "continue1.txt," respectively.

### Dependencies

- C++ Standard Library
- Tkinter (for the GUI)

### Running the Program

Compile and run the C++ program. Ensure that the "Dictionary.txt" file is available for loading words.

**Note:** This is a console-based program with basic GUI components for ease of use. Adjustments may be needed based on the user interface requirements.
