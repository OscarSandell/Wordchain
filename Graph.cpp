#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

struct Graph
{
    struct Node
    {
        /*struct Edge
        {
            Edge(const std::string & to,int weightp):weight{}
            int weight;
            std::string name_of_node_we_go_to;
        };*/
        Node(const std::string &s) : value{s}, Adj_List{},weight{1},distance{-1},prev{nullptr},visited{false}{}
        std::string value;
        std::vector<Node *> Adj_List;
        int weight;
        int distance;
        Node* prev;
        bool visited;
    };

    Graph():Node_List{}{}
    ~Graph()
    {
        for (auto &&i : Node_List)
        {
            delete i;
        }
    }

    std::vector<std::string> Find_Shortest(const std::string &from, const std::string &to);
    std::vector<std::string> Find_Longest(std::string const &);
    bool Dijkstra(std::string const & from,std::string const &);
    void ISS(const std::string &);
    Node* find(std::string const &);
    std::vector<Node *> Node_List;
    void insert(const std::string &valuep);
};

void Graph::ISS(std::string const & first)
{
    for (auto &&i : Node_List)
    {
        if(i->value == first)
        {
            i->distance = 0;
        }
        else
        {
            i->distance = -1;
        }
        i->prev = nullptr;
        i->visited = false;
    }
    
}

Graph::Node* Graph::find(std::string const & target)
{
    auto result = std::find_if(Node_List.begin(),Node_List.end(),[&target](Node* node){return node->value == target;});
    if(result == Node_List.end())
    {
        std::cout << "No such node" << std::endl;
        return nullptr;
    }
    return *result;
}


bool distance_comparison(Graph::Node*a,Graph::Node* b)
{
    //return vänster +1 < höger
    if(a->distance +1 > 0 && b->distance == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Graph::Dijkstra(std::string const & from, std::string const & to)
{
    auto lambda= [](Node*a,Node*b){return a->distance > b->distance;};
    std::priority_queue<Node*,std::vector<Node*>,decltype(lambda)> queue(lambda);
    queue.push(find(from));
    while(!queue.empty())
    {
        Node* current = queue.top();
        queue.pop();
        if(current->visited) continue;
        current->visited = true;
        
        for(auto n : current->Adj_List)
        {
            if(current->distance +1 < n->distance || n->distance == -1 )
            {
                n->distance = current->distance + 1;
                n->prev = current;
            }
            queue.push(n);
        }
        //if(current->value == to) return true; 
    }
    //return false;
}

void Graph::insert(const std::string &valuep)
{
    Node *node{new Node{valuep}};
    Node_List.push_back(node);
    for (auto a : Node_List)
    {
        int diff{0};
        for (size_t i{}; i < valuep.size(); i++)
        {
            if (valuep[i] != a->value[i])
            {
                diff++;
            }
        }
        if (diff < 2 && diff > 0)
        {
            node->Adj_List.push_back(a);
            a->Adj_List.push_back(node);
        }
    }
}

void read_file(Graph &graph)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "#")
            break;
        graph.insert(line);
    }
}

std::vector<std::string> Graph::Find_Shortest(std::string const & from,std::string const & to)
{
    Node* f = find(from);
    Node* t = find(to);
    std::stack<Node*>nodes{};
    while(t != f->prev)
    {
        nodes.push(t);
        std::cout << "T value " << t->value << " t->prev " << t->prev << std::endl; 
        t = t->prev;
    }
    std::vector<std::string> node_values{};
    while(!nodes.empty())
    {
        node_values.push_back(nodes.top()->value);
        nodes.pop();
    }
    return node_values;

}


std::vector<std::string> Graph::Find_Longest(std::string const & to)
{

}

int main()
{
    Graph graph{};
    read_file(graph);

    for (auto a : graph.Node_List)
    {
        std::cout << "Utgår ifrån : " << a->value << std::endl ;
        for (size_t i = 0; i < a->Adj_List.size(); i++)
        {
            std::cout << a->Adj_List[i]->value << " ";
        }
        std::cout << std::endl;
    }
    graph.ISS("aula");
    for (auto a : graph.Node_List)
    {
        std::cout << "Node : " << a->value << " Har distance = "<< a->distance << std::endl ;
        std::cout << std::endl;
    }
    bool test = graph.Dijkstra("aula","jama");
    if(test)
    {
        std::cout << "Det fanns en väg" << std::endl;
    }
    else
    {
        std::cout << "det fans ej en väg" << std::endl;
    }
    std::vector<std::string> path = graph.Find_Shortest("aula","jama");
    std::cout << " Kortaste vägen är " << path.size() << std::endl;

}