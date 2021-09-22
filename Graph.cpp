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
        Node(const std::string &s) : value{s}, Adj_List{}, weight{1}, distance{-1}, prev{nullptr}, visited{false} {}
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

    std::vector<std::string> Find_Shortest(const std::string &from, const std::string &to);
    std::vector<std::string> Find_Longest(std::string const &);
    std::vector<Node *> Dijkstra(std::string const &from, std::string const &);
    void ISS(const std::string &);
    Node *find(std::string const &);
    std::vector<Node *> Node_List;
    void insert(const std::string &valuep);
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

    graph.ISS("aula");

    std::vector<Graph::Node *> path = graph.Dijkstra("aula", "jama");
    if (path.size() > 0)
    {
        for (auto it = std::make_reverse_iterator(path.end()); it != std::make_reverse_iterator(path.begin()); it++)
        {
            if(it != std::make_reverse_iterator(path.begin()+1))
            {
                std::cout << (*it)->value << "-->";
            }
            else
                std::cout << (*it)->value << std::endl;
        }
    }
    else
    std::cout << "No Path! mofo" << std::endl;
}

/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
    string line;
    vector<string> result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.push_back(line);
    }

    return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const vector<string> &chain) {
    if (chain.empty()) {
        cout << "ingen lösning" << endl;
    } else {
        cout << chain.size() << " ord" << endl;
        print_chain(chain);
    }
}

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}