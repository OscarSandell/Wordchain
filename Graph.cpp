#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iterator>

struct Graph
{
    struct Node
    {
      
        Node(const std::string &s) : value{s}, Adj_List{}, weight{1}, distance{-1}, prev{nullptr}, visited{false} {}
        Node(const Node &);
        Node operator=(const Node &);
        std::string value;
        std::vector<Node *> Adj_List;
        int weight;
        int distance;
        Node *prev;
        bool visited;
    };

    Graph() : Node_List{} {}
    ~Graph()
    {
        for (auto &&i : Node_List)
        {
            delete i;
        }
    }

    std::vector<std::string> Find_Shortest(const std::string &, const std::string &);
    std::vector<std::string> Find_Longest(std::string const &);
    std::vector<Node*> Dijkstra(std::string const &, std::string const &);
    std::vector<Node*> BFS(std::string const &);
    void ISS(const std::string &);
    Node *find(std::string const &);
    std::vector<Node *> Node_List;
    void insert(const std::string &;
};

void Graph::ISS(std::string const &first)
{
    for (auto &&i : Node_List)
    {
        if (i->value == first)
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

Graph::Node *Graph::find(std::string const &target)
{
    auto result = std::find_if(Node_List.begin(), Node_List.end(), [&target](Node *node)
                               { return node->value == target; });
    if (result == Node_List.end())
    {
        std::cout << "No such node" << std::endl;
        return nullptr;
    }
    return *result;
}

bool distance_comparison(Graph::Node *a, Graph::Node *b)
{
    //return vänster +1 < höger
    if (a->distance + 1 > 0 && b->distance == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Graph::Node *> Graph::Dijkstra(std::string const &from, std::string const &to)
{
    auto lambda = [](Node *a, Node *b)
    { return a->distance > b->distance; };
    std::priority_queue<Node *, std::vector<Node *>, decltype(lambda)> queue(lambda);
    std::vector<Node *> path{};
    queue.push(find(from));
    while (!queue.empty())
    {
        Node *current = queue.top();
        queue.pop();
        if (current->visited)
            continue;
        current->visited = true;
        if (current->value == to)
        {
            path.push_back(current);
            while (current->prev != nullptr)
            {
                path.push_back(current->prev);
                current = current->prev;
            }
            return path;
        }
        for (auto n : current->Adj_List)
        {
            if (current->distance + 1 < n->distance || n->distance == -1)
            {
                n->distance = current->distance + 1;
                n->prev = current;
            }
            queue.push(n);
        }
    }
    return path;
}

std::vector<Graph::Node *> Graph::BFS(std::string const &from)
{
    ISS(from);
    
}

std::vector<std::string> Graph::Find_Shortest(const std::string &from, const std::string &to)
{
    ISS(from);
    std::vector<Graph::Node *> path = Dijkstra(from, to);
    std::vector<std::string> wordChain{};
    for (auto it = std::make_reverse_iterator(path.end()); it != std::make_reverse_iterator(path.begin()); it++)
    {
        wordChain.push_back((*it)->value);
    }
    return wordChain;
}

std::vector<std::string> Graph::Find_Longest(std::string const & a)
{
    std::cout << "Implementera denna " << std::endl;
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

/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
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
Graph read_dictionary()
{
    std::string line;
    //std::vector<std::string> result;
    Graph Temp{};
    while (std::getline(std::cin, line))
    {
        if (line == "#")
            break;

        Temp.insert(line);
    }
    return Temp;
    //return std::vector<std::string>(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const std::vector<std::string> &chain)
{
    if (chain.empty())
        return;

    std::vector<std::string>::const_iterator i = chain.begin();
    std::cout << *i;

    for (++i; i != chain.end(); ++i)
        std::cout << " -> " << *i;

    std::cout << std::endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const std::vector<std::string> &chain)
{
    if (chain.empty())
    {
        std::cout << "ingen lösning" << std::endl;
    }
    else
    {
        std::cout << chain.size() << " ord" << std::endl;
        print_chain(chain);
    }
}

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(Graph &graph)
{

    std::string line;
    while (std::getline(std::cin, line))
    {
        size_t space = line.find(' ');
        if (space != std::string::npos)
        { //find shortest path
            std::string first = line.substr(0, space);
            std::string second = line.substr(space + 1);
            std::vector<std::string> path = graph.Find_Shortest(first, second);

            std::cout << first << " " << second << ": ";
            print_answer(path);
        }
        else
        { //find longest path
            std::vector<std::string> chain = graph.Find_Longest(line);

            std::cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main()
{
    //std::vector<std::string> dict = read_dictionary();
    Graph graph = read_dictionary();
    //read_questions(dict);
    read_questions(graph);
    return 0;
}