#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set> 
#include <algorithm>

using namespace std;

struct KeyHash {
     size_t operator()(const string &str) const {  // djb2
            size_t result = 5381;
            for (int i{}; i < str.size(); ++i) {
                result = ((result << 5) + result) + int(str.at(i)); 
            }
            return result;
        }
};

struct Node { 
    Node(string const& word) 
        : word{word} {}
    Node(string const& word, Node* prev) 
        : word{word}, prev{prev} {} 
    string word;
    vector<string> neighbors;
    Node* prev;
};

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.

// typedef vector<string> Dictionary;
// typedef set<string> Dictionary;
typedef unordered_set<string, hash<string>> Dictionary;
// typedef unordered_set<string, KeyHash> Dictionary;

string const alphabet {"abcdefghijklmnopqrstuvwz"};

// void find_neighbors(const Dictionary &dict, Node &node) {
//     string word = node.word;
//     for (int i{}; i < static_cast<int>(word.size()); ++i) {  // 4
//         string temp = word;
//         for (char const& c : alphabet) {                     // 25
//             temp.at(i) = c;
//             if (temp != word) {
//                 for (string const& s : dict) {               // 500 000
//                     if (temp == s) {
//                         node.neighbors.push_back(temp);
//                     }
//                 }
//             }   
//         }
//     }
// }

// void find_neighbors(const Dictionary &dict, Node &node) {
//     for (const string &str : dict) {
//         string word = node.word;
//         string temp = str;
//         int sum{};
//         if (temp != word) {
//             for(int i{}; i < word.size(); ++i) {
//                 if (temp.at(i) == word.at(i))
//                     ++sum;
//             }
//             if (sum >= (str.size() - 1))
//                 node.neighbors.push_back(str);
//         }
//     }
// }

void find_neighbors(const Dictionary &dict, Node &node) {
    for (int i{}; i < static_cast<int>(node.word.size()); ++i) { 
        string word = node.word;
        for (const char &c : alphabet) {                     
            word.at(i) = c;
            auto it = dict.find(word);
            if (it != dict.end())
                node.neighbors.push_back(word);
        }
    }
}

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(Dictionary dict, const string &from, const string &to) {
    vector<string> result;
    queue<Node> queue;
    
    Node begin{from};
    queue.push(begin);
    while (!queue.empty()) {
        Node curr = queue.front();
        queue.pop();
        find_neighbors(dict, curr);
        for (string neighbor : curr.neighbors) {
            if (neighbor == to) {
                Node* curr_ptr = new Node(curr);
                result.insert(result.begin(), to);
                result.insert(result.begin(), curr_ptr->word);
                while (curr_ptr->word != from) {
                    result.insert(result.begin(), curr_ptr->prev->word);
                    curr_ptr = curr_ptr->prev;
                } 
                return result;
            }
            else {
                dict.erase(neighbor);
                //dict.erase(remove(dict.begin(), dict.end(), neighbor));
                queue.push(Node{neighbor, new Node(curr)});
            }
        }
    }
    return result;
    
    // vector<string> result;
    // queue<pair<Node, vector<string>>> queue;

    // Node begin{from};
    // result.push_back(from);
    // queue.push({begin, result});
    // while (!queue.empty()) {
    //     Node curr = queue.front().first;
    //     result = queue.front().second;
    //     queue.pop();
    //     find_neighbors(dict, curr);
    //     for (string neighbor : curr.neighbors) {
    //         if (neighbor == to) {
    //             result.push_back(to);
    //             return result;
    //         }
    //         else {
    //             vector<string> temp = result;
    //             temp.push_back(neighbor);
    //             dict.erase(remove(dict.begin(), dict.end(), neighbor));
    //             queue.push({Node{neighbor}, temp});
    //         }
    //     }
    // }
    // vector<string> empty{};
    // return empty;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(Dictionary dict, const string &word) {
    vector<string> result;
    queue<Node> queue;

    Node begin{word};
    queue.push(begin);
    while (!queue.empty()) {
        Node curr = queue.front();
        queue.pop();
        find_neighbors(dict, curr);
        for (const string &neighbor : curr.neighbors) {
            //dict.erase(remove(dict.begin(), dict.end(), neighbor));
            dict.erase(neighbor);
            queue.push(Node{neighbor, new Node(curr)});
        }
        if (queue.empty()) {
            Node* curr_ptr = new Node(curr);
            result.push_back(curr_ptr->word);
            while (curr_ptr->prev->word != word) {
                result.push_back(curr_ptr->prev->word);
                curr_ptr = curr_ptr->prev;
            } 
        }
    }
    result.push_back(word);
    return result;
}


/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
    string line;
    //vector<string> result;
    Dictionary result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.insert(line);
        //result.push_back(line);
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
