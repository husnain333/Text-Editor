#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<iomanip>
using namespace std;
///////// class for node of the tree for huffman compression
class node
{
public:
    char data;
    bool word = 0;
    node* arr[26];   ///// the whole alphabets
    node()
    {

        for (int i = 0; i < 26; i++)
        {

            arr[i] = nullptr;;
        }
    }
};

/////////helper function to return the index of the used character
int indexno(char x)
{
    switch (x)
    {
    case 'A':
    case 'a':
        return 0;
        break;
    case 'B':
    case 'b':
        return 1;
        break;
    case 'C':
    case 'c':
        return 2;
        break;
    case 'D':
    case 'd':
        return 3;
        break;
    case 'E':
    case 'e':
        return 4;
    case 'F':
    case 'f':
        return 5;
        break;
    case 'G':
    case 'g':
        return 6;
        break;
    case 'H':
    case 'h':
        return 7;
        break;
    case 'I':
    case 'i':
        return 8;
        break;
    case 'J':
    case 'j':
        return 9;
        break;
    case 'K':
    case 'k':
        return 10;
        break;
    case 'L':
    case 'l':
        return 11;
        break;
    case 'M':
    case 'm':
        return 12;
        break;
    case 'N':
    case 'n':
        return 13;
        break;
    case 'O':
    case 'o':
        return 14;
        break;
    case 'P':
    case 'p':
        return 15;
        break;
    case 'Q':
    case 'q':
        return 16;
        break;
    case 'R':
    case 'r':
        return 17;
        break;
    case 'S':
    case 's':
        return 18;
        break;
    case 'T':
    case 't':
        return 19;
        break;
    case 'U':
    case 'u':
        return 20;
        break;
    case 'V':
    case 'v':
        return 21;
        break;
    case 'W':
    case 'w':
        return 22;
        break;
    case 'X':
    case 'x':
        return 23;
        break;
    case 'Y':
    case 'y':
        return 24;
        break;
    case 'Z':
    case 'z':
        return 25;
        break;

    default:
        return 0;
    }
}
/////////// the trie tree classs
class tree
{

public:
    node* root;
    tree()
    {

        root = new node;

    }
    ////// insertion
    void insert(string str, node* leaf, int num)
    {
        if (num < str.length())
        {
            int ind = indexno(str[num]);
            if (leaf->arr[ind] == NULL)
            {
                leaf->arr[ind] = new node;
                leaf->arr[ind]->data = str[num];
            }
            if (num == str.length() - 1)
            {
                leaf->arr[ind]->word = true;
            }
            leaf = leaf->arr[ind];
            num++;

            insert(str, leaf, num);
        }
    }
    // searching for a particular word
    int search(string str, node* leaf, int num)
    {
        if (num < str.length() - 1)
        {
            int ind = indexno(str[num]);
            if (leaf->arr[ind] == NULL)
            {

                return 0;
            }
            else
            {
                /*if (num == str.length() - 1)
                {

                    if (leaf->arr[ind]->word != true)
                    {
                        return 0;
                    }
                }*/
                if (leaf->arr[ind]->data == str[num])
                {
                    leaf = leaf->arr[ind];
                    num++;
                    int x = search(str, leaf, num);
                    return x;
                }
            }
        }
        else if (num < str.length())
        {
            int ind = indexno(str[num]);
            if (leaf->arr[ind] != NULL)
            {
                if (leaf->arr[ind]->word != true)
                {
                    return 0;
                }
                else
                    return 1;
            }
            else return 0;
        }


    }

    //// loading the treee
    void loadtree()
    {
        fstream dics;

        dics.open("Dictionary.txt", ios::in); //open a file to perform read operation using file object
        if (dics.is_open())
        {   //checking whether the file is open
            string str;
            while (getline(dics, str))//read data from file object and put it into string.
            {
                insert(str, this->root, 0);

            }
            dics.close(); //close the file object.
        }

    }
    string giveword(string str, node* leaf, int num, string ret, int no, int level)
    {
        while (num < str.length())
        {
            int ind = indexno(str[num]);
            if (leaf->arr[ind] == NULL)
            {

                return "Not Found1";
            }
            else
            {

                ret += str[num];
                leaf = leaf->arr[ind];
                num++;
            }
            if (num == str.length())
            {
                num = num - 1;
                break;
            }
        }
        if (leaf->word == 1 && num != str.length() - 1)
        {
            return ret;
        }
        else
        {
            num++;
            int x = 0;
            for (int i = 0; i < 26; i++)
            {

                if (leaf->arr[i] != NULL)
                {
                    if (num == level + str.length())
                    {
                        if (x == no)
                        {
                            x++;
                            ret += leaf->arr[i]->data;
                            leaf = leaf->arr[i];
                            break;
                        }
                        else
                        {
                            x++;
                        }
                    }
                    else
                    {
                        ret += leaf->arr[i]->data;
                        leaf = leaf->arr[i];
                        break;
                    }
                }
            }
            string temp = giveword(str, leaf, num, ret, no, level);
            return temp;
        }



    }
    ////// the suggestions fuction that will return the needed suggestions
    string* giveSuggestion(string str, int& c1)
    {
        string* arrstr;
        arrstr = new string[10];
        int count = 0;
        if (search(str, root, 0) == 1)
        {
            arrstr[count] = str;
            cout << count + 1 << " : " << arrstr[count];
            cout << endl;
            count++;
        }
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                string temp;
                arrstr[count] = giveword(str, root, 0, temp, j, 0);
                if (arrstr[count] != "Not Found1" && arrstr[count] != str)
                {
                    for (int k = 0; k < count; k++)
                    {
                        string str11 = arrstr[k];
                        for (int l = k + 1; l < count; l++)
                        {
                            if (str11 == arrstr[l] && k != l)
                            {
                                c1 = count;
                                return arrstr;
                            }
                        }
                    }
                    cout << count + 1 << " : " << arrstr[count];
                    cout << endl;
                    count++;
                }

                if (count == 9 || arrstr[count] == str)
                {

                    c1 = count;
                    return arrstr;
                }
            }

        }
    }

    ///// main function for input on the console with the continue editing features for the console
    string input()
    {
        char arr[50];
        string fstr;
        string* str1;
        string str;
        string temp11;
        string temp22;
        int choose1,choose2; ///// choose 1 for continue and new text option and choose 2 for encoded decoded text
        cout << setw(45)<<"/////////////////////--------NOTEPAD++-----------/////////////\n\n";
        cout << "-------CHOOSE-----\n";
        cout << "1 : CONTNUE EDITING\n2 : NEW TEXT\n";
    
        while (true)
        {
            cout << "choose : ";
            cin >> choose1;
            if (cin.fail())
            {
                cout << "Invalid input:\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            if (choose1==1||choose1==2)
            {
                break;
            }
            else
            {
                cout << "Invalid input:\n";
            }
        }
        if (choose1 == 1)
        {
            cout << "///////----CONTINUE EDITING ----////////\n\n";
            cout << "-------CHOOSE-----\n";
            cout << "1 : LATEST ENCODED TEXT\n2 : LATEST UN ENCODED TEXT\n";

            while (true)
            {
                cout << "choose : ";
                cin >> choose2;
                if (cin.fail())
                {
                    cout << "Invalid input:\n";
                    cin.clear();
                    cin.ignore();
                    continue;
                }
                if (choose2 == 1 || choose2 == 2)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input:\n";
                }
            }
            if (choose2 == 1) ///////// chosing the continue editing option and the latestencoded option
            {
                
                string str123;
                fstream file;
                file.open("continue1.txt", ios::in);
                getline( file,str123);
                file.close();
                fstr = str123;
                if (fstr.length() != 0)
                {
                    cout << "Enter Text Onword : ";
                    fstr += ' ';
                    cout << fstr;
                }
                else
                {
                    cout << "No compressed data found \n";
                    cout << "Enter TEXT : ";
                }
                cin.ignore();
            }
            else if (choose2 == 2) ///////// chosing the continue editing option and the latest not encoded option
            {
                
                fstream file;
                file.open("continue.txt", ios::in);
                getline(file, fstr);
                file.close();
                if (fstr.length() != 0)
                {
                    cout << "Enter Text Onword : ";
                    fstr += ' ';
                    cout << fstr;
                }
                else
                {
                    cout << "No compressed data found \n";
                    cout << "Enter TEXT : ";
                }
                cin.ignore();
            }
        }
        else if (choose1 == 2) //////// new text option
        {
            cin.ignore();
            cout << "ENTER TEXT : ";
        }
        for (int i = 0; i < 50; i++)
        {

            string temp1;
            /*_kbhit();
            if (_kbhit())
            {
                cout << "\nyes\n";
            }*/

            getline(cin, temp1);
            int count1 = 0, count2 = 0, count3 = 0;
            for (int j = temp1.length() - 1; j >= 0; j--)
            {
                if (temp1[j] == ' ')
                {
                    count2 = 1;
                    break;
                }
                if (temp1[j] < 65 || (temp1[j] > 90 && temp1[j] < 97) || (temp1[j] > 122))
                {
                    count3 = 1;
                }
                
                count1++;
            }
            if (count3 == 1)
            {
                cout << fstr;
                str = "";
                continue;
            }
            if (count2 != 0)
            {
                for (int j = 0; j < temp1.length(); j++)
                {
                    if (j < temp1.length() - count1)
                    {
                        fstr += temp1[j];
                    }
                    else
                    {
                        str += temp1[j];
                    }
                }
            }
            else
            {

                str += temp1;

            }
            cout << "0 : No one\n";
            int num = 0;
            str1 = giveSuggestion(str, num);
            if (num == 0)
            {

            }
            cout << num + 1 << " : sentence Completed : \n";
            int inp;
        
            while (true)
            {
                cout << "choose : ";
                cin >> inp;
                if (cin.fail())
                {
                    cout << "Invalid input:\n";
                    cin.clear();
                    cin.ignore();
                    continue;
                }
                if (inp >= 0 && inp <= num + 1)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input:\n";
                }
            }
          

            if ((inp >= 0 && inp <= num + 1))
            {

                if (inp == 0)
                {
                    fstr += str;
                    cout << fstr;
                    str = "";
                    cin.ignore();
                    continue;
                }
                else if (inp > 0 && inp <= num)
                {
                    str = str1[inp - 1];
                    fstr += str;
                    cout << fstr;
                    int x3 = 0;

                   
                    while (true)
                    {
                        cout << "\n1 : Sentence completed\n";
                        cout << "2 : Not completed\n";
                        cin >> x3;
                        if (cin.fail())
                        {
                            cout << "Invalid input:\n";
                            cin.clear();
                            cin.ignore();
                            continue;
                        }
                        if (x3 >0 && x3 < 3 )
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid input:\n";
                        }
                    }

             

                    if (x3 == 1)
                    {
                        return fstr;
                    }
                    else if (x3 == 2)
                    {
                        fstr += " ";
                        cout << fstr;
                        str = "";
                        cin.ignore();
                        continue;
                    }

                }
                else if (inp == num + 1)
                {
                    fstr += str;
                    
                    return fstr;
                }
            }
        }
    }
};
////////decoding struct to decode the whole sentenes
struct decode {
    int decodeArray[INT16_MAX];
    int decodeIndex;
    decode()
    {
        decodeIndex = 0;
    }
};
//////////////////////////Byte class
class Byte {
public:
    //// bytes array to get value in file
    int** bytes;
    int byteSize[26];
    decode D;
    void byteInitialiser()   /// initialise the char array
    {
        bytes = new int* [26];
    }
    void fillByte(int index, int arr[], int size)  ///// fill the bytes array at the respective index of the character so we know whats the code for specific alphabets for encoding
    {
        bytes[index] = new int[size];
        byteSize[index] = size;
        for (int i = 0; i < size; i++)
        {
            bytes[index][i] = arr[i];
        }

    }
    void printByteArray(int index)//////////// print the specific bytes stored for specific alphabets at their respectives indexes for example if its A then the encode bytes for A will be stored at index ) of the 2D array
    {
        fstream comp;
        comp.open("CompressionFile.txt", ios::app);
        for (int i = 0; i < byteSize[index]; i++)
        {
            cout << bytes[index][i];
            comp << bytes[index][i];  //// cout in the file
            D.decodeArray[D.decodeIndex++] = bytes[index][i];

        }
        comp.close();
    }
    void printBytes(int arr[], int n)   ///// this is needed for only compression to know the codes of every alphabet used
    {
        for (int i = 0; i < n; i++)
        {
            cout << arr[i];
        }
        cout << endl;
    }
    //// only for debudgging
    /*void displayDecode()
    {
    for(int i=0;i<D.decodeIndex;i++)
    {
    cout<<D.decodeArray[i];
    }
    }*/
};

//////// nodes used in the huffman tree they have left right children but also a pointer that links another node to it
struct queueNode
{
    int freq;  /// the value of that character in the node the number of times used
    char data;  /// the character saved in the node
    queueNode* left;
    queueNode* right;
    queueNode* next; /// the link
    queueNode()
    {
        left = NULL;
        right = NULL;
        next = NULL;

    }
};

class priority_queue  //// priority tree class that will make the huffman tree and will help in making it
{
public:
    int num;
    // int v;
    queueNode* front; ///// the starting node
    priority_queue()
    {
        front = NULL;
        num = 0;
        //   v=1;

    }
    void enqueue(int data, int freq)  //// adding nodes
    {
        num++;

        queueNode* temp, * curr, * pre = NULL;

        temp = new queueNode;
        temp->data = data;
        temp->freq = freq;

        if (front == NULL || freq <= front->freq)
        {
            temp->next = front;
            front = temp;
        }

        else
        {
            curr = front;

            while (curr && freq >= curr->freq)
            {
                pre = curr;
                curr = curr->next;
            }

            temp->next = pre->next;
            pre->next = temp;
        }
    }

    void enqueueNode(queueNode* temp)  //// the function that will enqueue the extra node in the queue that will have a tree beneath it with all the characters
    {


        num++;
        queueNode* curr, * pre = NULL;

        if (front == NULL || temp->freq <= front->freq)
        {
            temp->next = front;
            front = temp;
        }

        else
        {
            curr = front;

            while (curr && temp->freq >= curr->freq)
            {
                pre = curr;
                curr = curr->next;
            }

            temp->next = pre->next;
            pre->next = temp;
        }
    }

    queueNode* dequeue() {
        num--;
        queueNode* temp;
        if (front == NULL) {
            cout << "\nEMPTY";
            return 0;
        }
        if (front->next == NULL) {
            temp = front;
            front = NULL;
            return temp;
            free(temp);

        }
        else {
            temp = front;
            front = front->next;
            return temp;
            free(temp);

        }
    }

    bool isEmpty() {
        return !front;
    }
    void display() {

        queueNode* temp = front;

        while (temp != NULL) {
            cout << endl;
            cout << temp->data << " = " << temp->freq << endl;
            temp = temp->next;
        }
    }

    queueNode* getFront()
    {
        return front;

    }

    int isLeaf(queueNode* obj)  //// function that will tell if a certain node is a leaf node or not
    {
        if (obj->left == NULL && obj->right == NULL)
        {
            return true;
        }
        return false;
    }

};

////////////// the huffman tree class
class huffmanTree
{

public:
    priority_queue queue; //// the queue node to tell that this treee has a separate queue for its separate functions
    int size;
    queueNode* root;
    Byte B;

    huffmanTree()
    {
        size = 0;
        root = NULL;
        B.byteInitialiser();
    }

    void filling(char arr[], int n, int num[], int n1)  //// n and n1 are alph and the priority queue gets ready here
    {

        for (int i = 0; i < n1; i++)
        {

            queue.enqueue(arr[i], num[i]);
            size++;
        }
    }

    void treeMaking() //////////// this will make a huffman tree with all its frequencies and values for us
    {
        while (queue.num > 1)
        {
            queueNode* new1 = new queueNode;
            queueNode* left = new queueNode;
            queueNode* right = new queueNode;
            left = queue.dequeue();
            right = queue.dequeue();
            new1->freq = left->freq + right->freq;
            new1->left = left;
            new1->right = right;
            // cout<<"freq"<<new1->freq<<endl;
            new1->data = '\0';
            queue.enqueueNode(new1);
        }



    }

    void makeRoot()   //// to make the front of queue the root of this tree
    {
        root = queue.getFront();

    }
    queueNode* getRoot()  /// function to get root to use in parameters
    {
        return root;
    }
    void preorder(queueNode* obj) const  //// only to check if our tree insertion has been done correctly
    {
        if (obj != NULL)
        {
            cout << obj->freq << " ";
            preorder(obj->left);
            preorder(obj->right);
        }
    }


    void printCode(queueNode* root, int arr[], int n) ///// this function will fill the array of every specific alphabet and will also print it all the alphabets are stored in leaf nodes
    {     /// and the path to them is their code 0 for left and 1 for right
        if (root->left)
        {
            arr[n] = 0;

            printCode(root->left, arr, n + 1);

        }
        if (root->right)
        {
            arr[n] = 1;

            printCode(root->right, arr, n + 1);
        }

        if (queue.isLeaf(root))
        {

            cout << root->data << " | ";
            B.printBytes(arr, n);
            //// character to check
            int x1 = 0;
            x1 = root->data;
            if (x1 >= 65 && x1 <= 90)
            {
                x1 = x1 - 65;
            }
            else if (x1 >= 97 && x1 <= 122)
            {
                x1 = x1 - 97;
            }
            B.fillByte(x1, arr, n);

        }
    }

    void displayHuffman()
    {
        queue.display();
        treeMaking();
        //queue.display();
        makeRoot();
        // preorder(getRoot());

        cout << "\n CODE :\n";
        int arr[70], n = 0;

        printCode(getRoot(), arr, n);

    }
    ///////////////////////////////////////////DECODING/////////////////////////////////////////////////////////////
    void decodeHuffman(queueNode* root,string &str)
    {
        static int number = 0;

        if (queue.isLeaf(root))
        {
            cout << root->data;
            str += root->data;
            //cout<<number<<" ";
            decodeHuffman(getRoot(),str);
        }

        else if (B.D.decodeArray[number] == 1 && number < B.D.decodeIndex)
        {
            number++;
            decodeHuffman(root->right,str);
        }
        else if (B.D.decodeArray[number] == 0 && number < B.D.decodeIndex)
        {
            number++;
            decodeHuffman(root->left,str);
        }


    }

};
void incode(huffmanTree* tree, string s)
{
    int numOfchar;
    numOfchar = s.length();  /// how many characters there should be
    char* alphabet;
    char* alphabet2;
    alphabet = new char[numOfchar];
    alphabet2 = new char[numOfchar];
    int alph = 0;
    int alph2 = 0;
    int* freq;
    freq = new int[numOfchar];
    bool use = false;
    fstream recordUncompressed;
    recordUncompressed.open("recordUncompressed.txt", ios::app);
    recordUncompressed << s << endl;
    recordUncompressed.close();
    for (int i = 0; i < numOfchar; i++)
    {
        if (s[i] != 32)  /// space askey
        {
            ///// for the first letter
            if (i == 0)
            {
                alphabet[alph] = s[i];

                freq[alph] = 0;

                for (int j = i; j < numOfchar; j++)
                {
                    if (alphabet[alph] == s[j])
                    {
                        freq[alph] += 1;


                    }
                }
                alph++;


            }

            else
            {
                for (int j = 0; j < alph; j++)
                {
                    if (s[i] == alphabet[j])
                    {
                        use = true;
                    }
                }

                if (use != true)
                {
                    alphabet[alph] = s[i];

                    freq[alph] = 0;
                    for (int j = i; j < numOfchar; j++)
                    {
                        if (alphabet[alph] == s[j])
                        {
                            freq[alph] += 1;
                        }

                    }
                    alph++;
                }
                use = false;
            }

        }
    }

    ////// letters separately in array
    for (int i = 0; i < numOfchar; i++)
    {
        if (s[i] != 32)
        {
            alphabet2[alph2++] = s[i];
        }
    }
    /////// letters in separate arrays
    for (int i = 0; i < alph; i++)
    {
        cout << i << "-" << alphabet[i] << " " << freq[i] << endl;
    }
    tree->filling(alphabet, alph, freq, alph);
    cout << endl;
    tree->displayHuffman();

    ////////////// for debugging
    /*cout<<"\nfor debugging = \n";
    for(int i=0;i<alph2;i++)
    {
    cout<<" "<<alphabet2[i];
    }
    */
    cout << "\nSENTENCE CODE : ";

    for (int i = 0; i < alph2; i++)
    {
        //// character to check
        ///// A=0
        int x1 = 0;
        x1 = alphabet2[i];
        if (x1 >= 65 && x1 <= 90)
        {
            x1 = x1 - 65;
        }
        else if (x1 >= 97 && x1 <= 122)
        {
            x1 = x1 - 97;
        }
        tree->B.printByteArray(x1);
    }
    cout << endl << endl;
    fstream comp;
    comp.open("CompressionFile.txt", ios::app);
    comp << endl;
    comp.close();
}

int main()    /// main function
{
    tree t1;
    t1.loadtree();
    huffmanTree tree;
    //string *str=t1.giveSuggestion("h");
    string str1 = t1.input();
    cout << str1 << endl;
    //// reading file one by one and storing the word in string s
    int choice;
    cout << "Enter : \n1 : To store sentence for later use \n2 : To Store data in compressed form\n";


    while (true)
    {
        cout << "choose : ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input:\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        if (choice == 1 || choice == 2)
        {
            break;
        }
        else
        {
            cout << "Invalid input:\n";
        }
    }
    if (choice == 1)
    {
        fstream file;
        file.open("continue.txt", ios::out);
        file << str1;
        file.close();
    }
    else if (choice == 2)
    {

        
        string s = str1;
        string str;
        incode(&tree, s);
        cout << "\nUncompressed Form OF data will be\n";
        tree.decodeHuffman(tree.getRoot(),str);
        
        fstream file;
        file.open("continue1.txt", ios::out);
        file << str;
        file.close();
    }


    cout << endl;

    system("pause");
    return 0;
}

