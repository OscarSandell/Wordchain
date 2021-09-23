#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iterator>
#include <unordered_set>
#include <unordered_map>

struct Node
{

    Node(const std::string &s) : value{s}, Adj_List{}, weight{1}, distance{-1}, prev{nullptr}, visited{false} {}
    Node(const std::string &s, Node *node) : value{s}, Adj_List{}, weight{1}, distance{-1}, prev{node}, visited{false} {}
    Node(const Node &);
    Node operator=(const Node &);
    std::string value;
    std::vector<Node *> Adj_List;
    int weight;
    int distance;
    Node *prev;
    bool visited;
};

std::vector<std::string> Find_Shortest(std::string const &from, std::string const &to, std::unordered_set<std::string> &set)
{
    std::unordered_map<std::string, std::string> visited{};
   /* auto lambda = [](Node *a, Node *b)
    { return a->distance > b->distance; };
    std::priority_queue<Node *, std::vector<Node *>, decltype(lambda)> queue(lambda);*/
    std::queue<std::string> queue {};
    queue.push(from);
    std::vector<std::string> path{};
    visited[from] = "";
    while (!queue.empty())
    {
        std::cout << "Kön är: " << queue.size() << std::endl;
        std::string current = queue.front();
        queue.pop();
        auto V = visited.find(current);
        if (V != visited.end())
            continue;
        //current->visited = true;
        
        //visited[current] = "";
        if (current == to)
        {
            /*while(current != from)
            {
                std::cout << "HEJ" << std::endl;
                path.push_back(current);
                current = visited[current];
            }*/
            while(current != "")
            {
                std::cout << "HEJ" << std::endl;
                path.push_back(visited[current]);
                current = visited[current];
            }
            
            path.push_back(current);
            return path;
        }
        

        std::string temp{current};
        for (auto &&i : temp)
        {
            for (i = 'a'; i < 'z' + 1; ++i)
            {
                if (temp != current)
                {
                    auto it = set.find(temp);
                    if (it != set.end())
                    {
                        auto goal = visited.find(temp);
                        if (goal != visited.end())
                        {   
                            visited[temp]=current;
                        }
                            queue.push(temp);
                    }
                }
            }
            temp = current;
        }
        
    }
    return path;
}


std::vector<std::string> Find_Longest(std::string const &from, std::unordered_set<std::string> &set)
{
    auto lambda = [](Node *a, Node *b)
    { return a->distance > b->distance; };
    std::priority_queue<Node *, std::vector<Node *>, decltype(lambda)> queue(lambda);
    std::vector<std::string> path{};
    Node *last{nullptr};
    queue.push(new Node(from));
    while (!queue.empty())
    {
        Node *current = queue.top();
        last = current;
        queue.pop();
        /* if (current->visited)
            continue; */

        current->visited = true;

        std::string temp{current->value};
        for (auto &&i : temp)
        {
            for (i = 'a'; i < 'z' + 1; ++i)
            {
                if (temp != current->value)
                {
                    auto it = set.find(temp);
                    if (it != set.end())
                    {
                        Node *n = new Node(temp);
                        if (current->distance + 1 < n->distance || n->distance == -1)
                        {
                            n->distance = current->distance + 1;
                            n->prev = current;
                        }
                        queue.push(n);
                    }
                }
            }
            temp = current->value;
        }
    }
    path.push_back(last->value);
    while (last->prev != nullptr)
    {
        path.push_back(last->prev->value);
        last = last->prev;
    }
    return path;
}

//unordered_set<std::string>
/*
std::vector<Graph::Node *> Graph::BFS(std::string const &from)
{
    std::queue<Node *> queue{};
    Node *last{nullptr};
    Node *start{find(from)};
    queue.push(start);
    start->visited = true;
    Node *current{nullptr};
    while (!queue.empty())
    {
        current = queue.front();
        last = current;
        queue.pop();

        
        for (auto &&i : current->Adj_List)
        {
            if (!i->visited)
            {
                queue.push(i);
                i->distance = current->distance + 1;
                i->prev = current;
                i->visited = true;
            }
        }
    }
    std::vector<Node *> path{};
    path.push_back(last);
    while (last->prev != nullptr)
    {
        path.push_back(last->prev);
        last = last->prev;
    }
    return path;
}
*/
/* std::vector<std::string> Find_Shortest(const std::string &from, const std::string &to, std::unordered_set<std::string> &set)
{
    std::vector<std::string> wordChain = Dijkstra(from, to, set);
    //std::vector<std::string> wordChain{};
    for (auto it = std::make_reverse_iterator(path.end()); it != std::make_reverse_iterator(path.begin()); it++)
    {
        wordChain.push_back((*it)->value);
    }
    return wordChain;
} */

/*
std::vector<std::string> Graph::Find_Longest(std::string const &from)
{
    ISS(from);
    std::vector<Graph::Node *> path = BFS(from);
    std::vector<std::string> wordChain{};
    for (auto &&i : path)
    {
        wordChain.push_back(i->value);
    }
    return wordChain;
}*/

/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
void read_dictionary(std::unordered_set<std::string> &set)
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "#")
            break;

        set.insert(line);
    }
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
void read_questions(std::unordered_set<std::string> &set)
{

    std::string line;
    while (std::getline(std::cin, line))
    {
        size_t space = line.find(' ');
        if (space != std::string::npos)
        { //find shortest path
            std::string first = line.substr(0, space);
            std::string second = line.substr(space + 1);
            std::vector<std::string> path = Find_Shortest(first, second, set);

            std::cout << first << " " << second << ": ";
            print_answer(path);
        }
        else
        { //find longest path
            std::vector<std::string> chain = Find_Longest(line, set);

            std::cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main()
{
    //std::vector<std::string> dict = read_dictionary();
    std::unordered_set<std::string> set{};
    read_dictionary(set);
    //std::cout << "Grafen e klar" << std::endl;
    //read_questions(dict);
    read_questions(set);
    return 0;
}