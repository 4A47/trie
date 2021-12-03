#include <map>
#include <string>
#include <vector>

struct Node
{
    Node *parent;
    std::map<char, Node*> children;
    size_t depth;
    char c;
    bool is_string;

    Node(Node *parent=nullptr, char c=0, size_t depth=0);
};

class Trie
{
    Node *root;
    Node *current_node;

    std::map<std::string, std::vector<char*>*> cache;

    void _remove(Node *node, char key);
    void dfs(Node* node, std::map<Node*, bool> &visited, std::vector<char*> &strings);
    Node *get_node(const char *str);
    std::vector<char*> *strings_from_node(Node *node);
    char *trace_string(Node *node);

public:
    size_t string_count;
    bool caching;

    Trie();

    void clear_cache();
    bool contains(const char *str);
    void insert(const char *str);
    void remove(const char *str);
    std::vector<char*> find(const char *str);
};
