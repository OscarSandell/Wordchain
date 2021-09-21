#include <iostream>
#include <string>
#include <vector>

struct Graph
{
    struct Node
    {
        Node(const std::string &s) : value{s}, Adj_List{}
        {
        }
        std::string value;
        std::vector<Node *> Adj_List;
    };
    Graph():Node_List{}{}
    ~Graph()
    {
        for (auto &&i : Node_List)
        {
            delete i;
        }
        
    }
    void Find_Shortest(const std::string &from, const std::string &to);
    //Find_Longest
    std::vector<Node *> Node_List;
    void insert(const std::string &valuep);
};

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
}