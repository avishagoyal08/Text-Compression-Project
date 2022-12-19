#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <windows.h>
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
string ans; // global variable for case 2 to store the entire

#include <vector>

class PriorityQueue // class to implement min priority queue
{
    vector<int> pq;

public:
    bool isEmpty() // checks if the priority queue is empty
    {
        return pq.size() == 0;
    }

    int getSize() // gives the size of priority queue
    {
        return pq.size();
    }

    int getMin() // find the minimum element from the priority queue
    {
        if (isEmpty())
        {
            return 0;
        }

        return pq[0];
    }

    void insert(int element) // inserting element in a priority queue
    {
        pq.push_back(element);

        int childIndex = pq.size() - 1;

        while (childIndex > 0)
        {
            int parentIndex = (childIndex - 1) / 2;

            if (pq[childIndex] < pq[parentIndex])
            {
                int temp = pq[childIndex];
                pq[childIndex] = pq[parentIndex];
                pq[parentIndex] = temp;
            }
            else
            {
                break;
            }

            childIndex = parentIndex;
        }
    }

    int removeMin() // removing minimum element from a priority queue
    {
        // Write your code here
        if (isEmpty())
            return 0;
        int temp, minIndex;

        int ans = pq[0];
        pq[0] = pq[pq.size() - 1];
        pq.pop_back();
        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;
        // heap order property-down heapify

        while (leftChildIndex < pq.size()) // if left index is greater then right will be greater for sure
        {

            minIndex = parentIndex;
            if (pq[leftChildIndex] < pq[minIndex])
            {
                minIndex = leftChildIndex;
            }
            if (rightChildIndex < pq.size() && pq[rightChildIndex] < pq[minIndex])
            {
                minIndex = rightChildIndex;
            }
            if (minIndex == parentIndex)
                break;

            int temp = pq[minIndex];
            pq[minIndex] = pq[parentIndex];
            pq[parentIndex] = temp;

            parentIndex = minIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
        return ans;
    }
};

// A Tree node
struct Node2
{
    char ch;
    int freq;
    Node2 *left, *right;
};

// Function to allocate a new tree node
Node2 *getNode(char ch, int freq, Node2 *left, Node2 *right)
{
    Node2 *node = new Node2();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(Node2 *l, Node2 *r)
    {
        // highest priority item has lowest frequency
        return l->freq > r->freq;
    }
};

// traverse the Huffman Tree and store Huffman Codes in an unordered map
void encode(Node2 *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node2 *root, int &index, string str)
{
    if (root == nullptr)
    {
        return;
    }

    // found a leaf node
    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(string text)
{
    // count frequency of appearance of each character and store it in a map
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    // Create a priority queue to store nodes of Huffman tree;
    priority_queue<Node2 *, vector<Node2 *>, comp> pq;

    // Create a leaf node for each character and add it to the priority queue.
    for (auto pair : freq)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of highest priority(lowest frequency) from the queue
        Node2 *left = pq.top();
        pq.pop();
        Node2 *right = pq.top();
        pq.pop();

        /* Create a new internal node with these two nodes as children
        and with frequency equal to the sum  of the two nodes' frequencies.
         Add the new node to the priority queue.*/
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // root stores pointer to root of Huffman Tree
    Node2 *root = pq.top();

    // traverse the Huffman Tree and store Huffman Codes in a map
    // Also print them
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are :\n"
         << '\n';
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string was :\n"
         << text << '\n';

    // print encoded string
    string str = "";
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    cout << "\nEncoded string is :\n"
         << str << '\n';

    // traverse the Huffman Tree again and this time decode the encoded string
    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 2)
    {
        decode(root, index, str);
    }

    // working for compressor ratio

    int len1 = text.length();
    int len2 = str.length();
    cout << endl;
    cout << "Size of input string in bytes : " << len1 << endl;
    int output_bytes = ceil(double(len2 / 8.0));
    cout << "Size of output string in bytes : " << output_bytes << endl;
}

void case1_StringToCodes()
{
    system("cls");
    string text;
    cout << "Enter the text you want to encode: ";
    cin >> text;
    buildHuffmanTree(text);
}

// IMPLEMENTATION OF CASE 2

struct node
{
    char info;
    int freq;
    char *code;
    node *Llink;
    node *Rlink;
};
class BinaryTree // Coding Tree
{
private:
    node *root;

public:
    BinaryTree()
    {
        root = NULL;
    }
    void print();
    void assign_code(int i);
    void print_code(char c);
    void encode(const char str[]);
    void print_symbol(char cd[], int &f, int length);
    void decode(string cd, int size);
    friend class minHeap;
    friend class HuffmanCode;
};
class minHeap
{
private:
    BinaryTree *T; // Array of Binary Trees
    int n;         // Number of symbols
    minHeap();
    void heapify(int i);
    BinaryTree dequeue(); // Returns the first Binary Tree of the min heap and
    // then heapify the array of Binary trees in order of the
    // frequencies of their root nodes.
    void enqueue(BinaryTree b); // To insert another Binary tree  and then heapify the array of Binary trees
    void print();
    friend class HuffmanCode;
};
class HuffmanCode
{
private:
    BinaryTree HuffmanTree; // (a minimum weighted external path length tree)
public:
    HuffmanCode();
};
HuffmanCode::HuffmanCode()
{
    minHeap Heap;
    // Huffman Tree is build from bottom to top
    // The symbols with lowest frequency are at the bottom of the tree
    // that leads to longer codes for lower frequency symbols and hence
    // shorter codes for higher frequency symbol giving optimal code length

    while (Heap.T[0].root->freq > 1)
    {
        // The first two trees with min. priority (i.e. frequency) are taken and
        BinaryTree l = Heap.dequeue();
        BinaryTree r = Heap.dequeue();
        // a new tree is constructed taking the above trees as left and right sub-trees with the frequency of root node as the sum of frequencies of left & right child.
        HuffmanTree.root = new node;
        HuffmanTree.root->info = '\0';
        HuffmanTree.root->freq = l.root->freq + r.root->freq;
        HuffmanTree.root->Llink = l.root;
        HuffmanTree.root->Rlink = r.root; // then it is inserted in the array and array is heapified again

        Heap.enqueue(HuffmanTree);
    } // The process continues till only one tree is left in the array of heap.
    cout << "\nThe process is completed and Huffman Tree is obtained\n";
    HuffmanTree = Heap.T[1]; // This tree is our HuffmanTree used for coding
    delete[] Heap.T;
    cout << "\nThe symbols with their codes are as follows\n";
    HuffmanTree.assign_code(0); // Codes are assigned to the symbols
    cout << "Enter the string to be encoded by Huffman Coding: ";
    char *str;
    str = new char[30];
    cin >> str;
    HuffmanTree.encode(str);
    int length = ans.length();
    HuffmanTree.decode(ans, length);
}
minHeap ::minHeap()
{
    cout << "Enter no. of symbols:";
    cin >> n;
    T = new BinaryTree[n + 1];
    T[0].root = new node;
    T[0].root->freq = n; // Number of elements in min. Heap at any time is stored in the zeroth element of the heap
    for (int i = 1; i <= n; i++)
    {
        T[i].root = new node;
        cout << "Enter characters of string :- ";
        cin >> T[i].root->info;
        cout << "and their frequency of occurence in the string:- ";
        cin >> T[i].root->freq;
        T[i].root->code = NULL;
        T[i].root->Llink = NULL;
        T[i].root->Rlink = NULL; // Initially, all the nodes are leaf nodes and stored as an array of trees
    }
    cout << endl;
    int i = (int)(n / 2); // Heapification will be started from the PARENT element of the last ( 'n th' ) element in the heap.

    while (i > 0)
    {
        heapify(i);
        i--;
    }
}
int min(node *a, node *b)
{
    if (a->freq <= b->freq)
        return a->freq;
    else
        return b->freq;
}
void swap(BinaryTree &a, BinaryTree &b)
{
    BinaryTree c = a;
    a = b;
    b = c;
}
void minHeap::heapify(int i) // function to implement heapify property to build a heap
{
    while (1)
    {
        if (2 * i > T[0].root->freq)
            return;
        if (2 * i + 1 > T[0].root->freq)
        {
            if (T[2 * i].root->freq <= T[i].root->freq)
                swap(T[2 * i], T[i]);
            return;
        }
        int m = min(T[2 * i].root, T[2 * i + 1].root);
        if (T[i].root->freq <= m)
            return;
        if (T[2 * i].root->freq <= T[2 * i + 1].root->freq)
        {
            swap(T[2 * i], T[i]);
            i = 2 * i;
        }
        else
        {
            swap(T[2 * i + 1], T[i]);
            i = 2 * i + 1;
        }
    }
}
BinaryTree minHeap::dequeue()
{
    BinaryTree b = T[1];
    T[1] = T[T[0].root->freq];
    T[0].root->freq--;
    if (T[0].root->freq != 1)
        heapify(1);
    return b;
}
void minHeap::enqueue(BinaryTree b)

{
    T[0].root->freq++;
    T[T[0].root->freq] = b;
    int i = (int)(T[0].root->freq / 2);
    while (i > 0)
    {
        heapify(i);
        i = (int)(i / 2);
    }
}
int isleaf(node *a) // check if the node is a leaf node
{
    if (a->info == '\0')
        return 0;
    else
        return 1;
}
void BinaryTree::assign_code(int i) // assigning codes to particular alphabets
{
    if (root == NULL)
        return;
    if (isleaf(root))
    {
        root->code[i] = '\0';
        cout << root->info << "\t" << root->code << "\n";
        return;
    }
    BinaryTree l, r;
    l.root = root->Llink;
    r.root = root->Rlink;

    l.root->code = new char[i + 1];

    r.root->code = new char[i + 1];
    for (int k = 0; k < i; k++)
    {
        l.root->code[k] = root->code[k];

        r.root->code[k] = root->code[k];
    }
    l.root->code[i] = '0'; // assigning 0 for the left side
    r.root->code[i] = '1'; // assigning 1 for the right side
    i++;
    l.assign_code(i);
    r.assign_code(i);
}
void BinaryTree::encode(const char str[])
{
    if (root == NULL)
        return;
    int i = 0;
    cout << "Encoded code for the input string '" << str << "' is\n";
    while (1)
    {
        if (str[i] == '\0')
        {
            cout << endl;
            return;
        }
        print_code(str[i]); // to print the entire encoded string in a line
        i++;
    }
}
void BinaryTree::print_code(char c)
{
    int f = 0;
    if (isleaf(root))
    {
        if (c == root->info)
        {
            f = 1;
            ans = ans + root->code; // using a global string variable to store the encoded string
            cout << root->code;     // printing codes one by one
        }
        return;
    }
    BinaryTree l, r;
    l.root = root->Llink;
    if (f != 1)
        l.print_code(c);
    r.root = root->Rlink;
    if (f != 1)
        r.print_code(c);
}

int isequal(const char a[], const char b[], int length) // check if the two strings are equal or not
{
    int i = 0;
    while (i < length)
    {
        if (b[i] != a[i])
            return 0;
        i++;
    }

    if (a[i] != '\0')
        return 0;
    return 1;
}
void BinaryTree::decode(string cd, int size) // decoding the encoded string
{
    if (root == NULL)
        return;
    int i = 0;
    int length = 0;
    int f;
    char *s;
    cout << "Decoded string for the input code '" << cd << "' is\n";
    while (i < size)
    {
        f = 0;
        s = &cd[i];
        while (f == 0)
        {
            length++;
            print_symbol(s, f, length);
        }
        i = i + length;
        length = 0;
    }
    cout << endl;
}
void BinaryTree::print_symbol(char cd[], int &f, int length)

{
    if (isleaf(root))
    {
        if (isequal(root->code, cd, length))
        {
            f = 1;
            cout << root->info;
        }
        return;
    }
    BinaryTree l, r;
    l.root = root->Llink;
    if (f != 1)
        l.print_symbol(cd, f, length);
    r.root = root->Rlink;
    if (f != 1)
        r.print_symbol(cd, f, length);
}

void BinaryTree::print()
{
    if (root == NULL)
        return;
    cout << root->info << "\t" << root->freq << "\n";
    if (isleaf(root))
        return;
    BinaryTree l, r;
    l.root = root->Llink;
    r.root = root->Rlink;
    l.print();
    r.print();
}
int power(int i, int j)
{
    int n = 1;
    for (int k = 1; k <= j; k++)
        n = n * i;
    return n;
}
int ispowerof2(int i)
{
    if (i == 1)
        return 0;
    if (i == 0)
        return 1;
    while (i > 2)
    {
        if (i % 2 != 0)
            return 0;
        i = i / 2;
    }
    return 1;
}
int fn(int l)
{
    if (l == 1 || l == 0)
        return 0;
    return 2 * fn(l - 1) + 1;
}
void minHeap::print()
{
    cout << "The Heap showing the root frequencies of the Binary Trees are:\n";
    if (T[0].root->freq == 0)
    {
        cout << endl;
        return;
    }
    int level = 1;
    while (T[0].root->freq >= power(2, level)) // 2^n-1 is the max. no. of nodes in a complete tree of n levels level++
        if (level == 1)
        {
            cout << T[1].root->freq << "\n";
            return;
        }
    for (int i = 1; i <= T[0].root->freq; i++)
    {
        if (ispowerof2(i))
        {
            cout << "\n";
            level--;
        }
        for (int k = 1; k <= fn(level); k++)
            cout << " ";
        cout << T[i].root->freq << " ";
        for (int k = 1; k <= fn(level); k++)
            cout << " ";
    }
    cout << endl;
}

void case2_FrequencyToCodes()
{
    system("cls");
    HuffmanCode c;
}

void gotoxy(int x, int y) // function to manage cursor
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void welcome1() // for first welcome page
{
    int j;
    char str[] = "\n\n\n\n\n\t\t\t************************WELCOME TO PROJECT OF************************ \n\n\t\t\t*********************Avisha Goyal********************* \n\t\t\t*******************Nikita Bansal********************** \n\t\t\t*******************Samyak Jain**********************";
    for (j = 0; j < strlen(str); j++)
    {
        printf("%c", str[j]);
    }
    printf("\t\t\t\n\nPress any key to continue\n");
    getch();
    system("cls");
    gotoxy(25, 6);
    printf("  *------------------*");
}

void welcome() // welcome page 2
{

    gotoxy(25, 6);
    printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    gotoxy(25, 7);
    printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    gotoxy(25, 8);
    printf("        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    gotoxy(25, 9);
    printf("        =                 WELCOME                   =");
    gotoxy(25, 10);
    printf("        =                   TO                      =");
    gotoxy(25, 11);
    printf("        =                  TEXT                     =");
    gotoxy(25, 12);
    printf("        =                COMPRESSOR                 =");
    gotoxy(25, 13);

    printf("        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    gotoxy(25, 14);
    printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    gotoxy(25, 15);
    printf("  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    gotoxy(28, 25);

    printf(" Enter any key to continue.....");
    getch();
    system("cls");
}

int main()
{
    welcome1();
    welcome();
    cout << "Enter 1 if you would like to enter a string and wants to compress the entire string " << endl;
    cout << "Enter 2 if you would like to enter the characters with their frequency and wants to compress " << endl;
    int choice;
    cout << "Enter your choice : ";
    cin >> choice;
    if (choice == 1)
    {
        case1_StringToCodes();
    }
    else if (choice == 2)
    {
        case2_FrequencyToCodes();
    }
    else
    {
        cout << "Wrong choice" << endl;
    }
}
