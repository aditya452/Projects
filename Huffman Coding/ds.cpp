#include <bits/stdc++.h>
using namespace std;

// A Huffman tree node
class Node {
public:
    char data;        //value of character
    int freq;         //frequency of character

    // Left and right child
    Node *left, *right;

    Node(char d, int f)
    {
        left = right = NULL;
        data = d;
        freq = f;
    }
};

// For comparison of
// two heap nodes (needed in min heap)
class compare {
public:
    bool operator()(Node* l, Node* r)

    {
        return (l->freq > r->freq);
    }
};

void printCodes(Node* root, string s)   //Print Huffman tree
{

    if (root == NULL)
        return;

    printCodes(root->left, s + "0");
    if (root->data != '*')
        cout << root->data << ": " << s << endl;
    printCodes(root->right, s + "1");
}

void print_minheap(priority_queue<Node*, vector<Node*>, compare > minHeap){
    while(minHeap.size() != 0){
        cout<<minHeap.top()->data<<": "<<minHeap.top()->freq<<endl;
        minHeap.pop();
    }
    cout<<endl;
}

void HuffmanCodes(unordered_map<char, int> mp)     //builds huffman tree
{
    Node *left, *right, *new_node;

    // Create a min heap 
    priority_queue<Node*, vector<Node*>, compare > minHeap; 
    //minheap minHeap;

    for(auto x: mp){
        minHeap.push(new Node(x.first, x.second));
    }

    cout<<"After inserting in minheap"<<endl;
    print_minheap(minHeap);

    while (minHeap.size() != 1) {

        //extracting least frequent element
        left = minHeap.top();    
        minHeap.pop();

        //extracting 2nd least frequent element
        right = minHeap.top();
        minHeap.pop();

        // Create a new node with frequency equal to the sum of the
        // two nodes frequencies.
        new_node = new Node('*', left->freq + right->freq);
        
        //Make the two least frequency nodes as left and right children
        // of this new node
        new_node->left = left;
        new_node->right = right;

        //Add this new node to the min heap
        minHeap.push(new_node);
    }

    cout<<"New codes are: "<<endl;
    printCodes(minHeap.top(), "");  // Print Huffman tree
}

int main()
{
    string s = "BCAADDDCCACACAC";
    
    unordered_map<char, int> mp; //used for storing frequency of characters
    for(int i = 0; i < s.length(); i++){
        mp[s[i]]++;
    }
    cout<<"After inserting in unordered map"<<endl;
    for(auto x: mp){
        cout<<x.first<<": "<<x.second<<endl;
    }
    cout<<endl;
    HuffmanCodes(mp);

    return 0;
}
