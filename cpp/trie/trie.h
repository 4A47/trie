#include <map>
#include <vector>

struct Node
{
    Node *parent;
    std::map<char, Node*> children;
    int depth;
    char c;
    bool is_string;
};

class Trie
{
    Node *root;
    Node *current_node;

    void _remove(Node *node, char key);
    void dfs(Node* node, std::map<Node*, bool> &visited, std::vector<char*> &strings);
    Node *get_node(const char *str);
    std::vector<char*> strings_from_node(Node *node);
    char switch_case(char c);
    char *trace_string(Node *node);

public:
    int string_count;
    bool case_sensitive;

    Trie();

    bool contains(const char *str);
    void insert(const char *str);
    void remove(const char *str);
    std::vector<char*> starts_with(const char *str);
};
