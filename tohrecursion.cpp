#include <iostream>
#include <vector>
using namespace std;

class disk
{
    public:
        char ch;
        unsigned int len;
        
        disk(unsigned int l, char c = '#')
        {
            len = l;
            ch = c;
        }
};

class node
{
    public:
        disk* data;
        node* next;
        
        node()
        {
            data = nullptr;
            next = nullptr;
        }
        
        node(disk* s)
        {
            data = s;
            next = nullptr;
        }
        
        void print()
        {
            for (unsigned int i=0; i<data->len; i++)
            {
                cout<< data->ch;
            }
        }
};

class Stack
{
    node* top;
    unsigned int size;
    string tag;
    public:
        Stack(string t)
        {
            top = new node();
            tag = t;
            size = 0;
        }
        Stack(node* data)
        {
            top = data;
            size = 1;
        }
        
        node* peek() const {return top;}
        string get_tag() const {return tag;}
        
        void push(node* n)
        {
            if (size > 0)
            {    
                if (top->data->len > n->data->len)
                {
                    n->next = top;
            
                    top = n;
                }
            }
            else
            {
                top = n;
            }
            size++;
            
            
        }
        void pop()
        {
            if (size > 1)
            {
                node* temp = top;
            
                top = top->next;
            
                delete temp;
            }
            else if (size == 1)
            {
                node* temp = top;
                
                top = nullptr;
                
                delete temp;
            }
            
            size--;
        }
        
        void print()
        {
            if (size > 0)
            {
                node* temp = top;
            
                while (temp != nullptr)
                {
                    temp->print();
                    cout<< endl;
                    temp = temp->next;
                }
            }
            cout<< "______"<< tag;
        }
        
};
// ##################################
// recursive solution of ToH
// for n disks, a total of 2^n-1 moves required
vector<Stack> rods;
size_t steps = 0;

void print_scene()
{
    // print the state
    for (size_t i=0; i<3; i++)
    {
        rods[i].print();
        cout<< endl << endl;
    }
    cout<< "----------------" << endl
        << "- step " << steps << endl
        << "----------------" << endl
                              << endl;
    steps++;
}

void towerofhanoi(size_t n, size_t from, size_t to, size_t aux)
{
    if (n == 0)
        return;
        
    towerofhanoi(n-1, from, aux, to);
    
    // move n (1) from 'from' to 'to'
    // - copy the top disk before deleting
    node* tobemoved = new node( rods[from].peek()->data );
    // - delete it
    rods[from].pop();
    // - move the copy to the new rod
    rods[to].push(tobemoved);
    
    // trivial info
    cout<< "move from" << rods[from].get_tag() << " to" << rods[to].get_tag() << endl << endl;
    
    print_scene();
    
    towerofhanoi(n-1, aux, to, from);
}

// ---------- MAIN FUNCTION --------
int main()
{
    rods.push_back(Stack(" A"));
    rods.push_back(Stack(" B"));
    rods.push_back(Stack(" C"));
    
    size_t n=3; // amount of disks
    
    for (size_t i=n; i>=1; i--)
        rods[0].push(new node(new disk(i)));
    
    print_scene();
    towerofhanoi(n, 0, 2, 1);
    /* 
    0, 2, 1 indicates the beginning
    of the recursion,
    meaning, from A to C using B
       0 = 'A'
       1 = 'B'
       2 = 'C'
    */
    
    return 0;
}