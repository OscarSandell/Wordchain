#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iterator>
#include <unordered_set>
#include <unordered_map>

//Denna funkar,

std::vector<std::string> Find_Shortest(std::string const &from, std::string const &to, std::unordered_set<std::string> &set)
{
    std::unordered_map<std::string, std::string> visited{};
    std::queue<std::string> queue{};
    queue.push(from);
    std::vector<std::string> path{};
    visited[from] = "";
    while (!queue.empty())
    {
        std::string current{queue.front()};
        queue.pop();
        std::string temp{current};
        for (auto &&i : temp)
        {
            for (i = 'a'; i < 'z' + 1; ++i)
            {
                if (temp != current)
                {
                    auto goal = visited.find(temp);
                    if (goal == visited.end())
                    {
                        auto it = set.find(temp);
                        if (it != set.end())
                        {
                            visited[temp] = current;
                            if (temp == to)
                            {
                                while (temp != from)
                                {
                                    path.push_back(temp);
                                    temp = visited[temp];
                                }
                                path.push_back(temp);
                                return path;
                            }
                            queue.push(temp);
                        }
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
    std::unordered_map<std::string, std::string> visited{};
    std::queue<std::string> queue{};
    queue.push(from);
    std::vector<std::string> path{};
    visited[from] = "";
    std::string last{};
    while (!queue.empty())
    {
        std::string current{queue.front()};
        queue.pop();
        last = current;
        std::string temp{current};
        for (auto &i : temp)
        {
            for (i = 'a'; i < 'z' + 1; ++i)
            {
                if (temp != current)
                {
                    auto goal = visited.find(temp);
                    if (goal == visited.end())
                    {
                        auto it = set.find(temp);
                        if (it != set.end())
                        {
                            visited[temp] = current;
                            queue.push(temp);
                        }
                    }
                }
            }
            temp = current;
        }
    }

 
    std::cout << "Letat igenom alla noder" << std::endl;
    while (last != from)
    {
        path.push_back(last);
        last = visited[last];
    }
    path.push_back(last);
    return path;
}

std::vector<std::string> Find_Path(std::string const &from, std::string const &to, std::unordered_set<std::string> &set)
{
    std::unordered_map<std::string, std::string> visited{};
    std::queue<std::string> queue{};
    queue.push(from);
    std::vector<std::string> path{};
    visited[from] = "";
    std::string last{};
    while (!queue.empty())
    {
        std::string current{queue.front()};
        queue.pop();
        last = current;
        std::string temp{current};
        for (auto &i : temp)
        {
            for (i = 'a'; i < 'z' + 1; ++i)
            {
                if (temp != current)
                {
                    auto goal = visited.find(temp);
                    if (goal == visited.end())
                    {
                        auto it = set.find(temp);
                        if (it != set.end())
                        {
                            //iffa här
                            visited[temp] = current;
                            if (to != "" && temp == to)
                            {
                                while (temp != from)
                                {
                                    path.push_back(temp);
                                    temp = visited[temp];
                                }
                                path.push_back(temp);
                                return path;
                            }
                            queue.push(temp);
                        }
                    }
                    /*auto goal = visited.find(temp);
                    if (goal == visited.end())
                    {
                        auto it = set.find(temp);
                        if (it != set.end())
                        {
                            visited[temp] = current;
                            
                            queue.push(temp);
                        }
                    }*/
                }
            }
            temp = current;
        }
    }

 
    if (to == "")
    {
        std::cout << "Letat igenom alla noder" << std::endl;
        while (last != from)
        {
            path.push_back(last);
            last = visited[last];
        }
        path.push_back(last);
        return path;
    }
    return path;
}

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
template<typename iterator>
//void print_chain(const std::vector<std::string> &chain)
void print_chain(iterator begin,iterator end)
{
    //if (chain.empty())
    if(begin == end)
        return;

   // std::vector<std::string>::const_iterator i = chain.begin();
    //std::cout << *i;
    std::cout << *begin;
    //for (++i; i != chain.end(); ++i)
     //   std::cout << " -> " << *i;
    for (++begin; begin != end; ++begin)
        std::cout << " -> " << *begin;

    std::cout << std::endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
template<typename iterator>
//void print_answer(const std::vector<std::string> &chain)
void print_answer(iterator begin,iterator end,size_t i)

{
    //f (chain.empty())
     if(begin == end)
    {
        std::cout << "ingen lösning" << std::endl;
    }
    else
    {
        //std::cout << chain.size() << " ord" << std::endl;
        std::cout << i << " ord" << std::endl;
        //print_chain(chain);
        print_chain(begin,end);
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
            //std::vector<std::string> path = Find_Shortest(first, second, set);
            std::vector<std::string> chain = Find_Path(first,second ,set);
            std::cout << first << " " << second << ": ";
            print_answer(chain.begin(),chain.end(),chain.size());
        }
        else
        { //find longest path
            //std::vector<std::string> chain = Find_Longest(line, set);
            std::vector<std::string> chain = Find_Path(line,"" ,set);
            std::cout << line << ": ";
            print_answer(std::make_reverse_iterator(chain.end()),std::make_reverse_iterator(chain.begin()),chain.size());
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