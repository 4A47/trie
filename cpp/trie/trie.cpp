#include <string.h>
#include <iostream>

#include "trie.h"

Trie::Trie()
{
    root = new Node();
    string_count = 0;
    current_node = nullptr;
    case_sensitive = false;
}

bool Trie::contains(const char *str)
{
    current_node = get_node(str);

    if(current_node)
        if(current_node->is_string) return true;

    return false;
}

void Trie::dfs(Node *node, std::map<Node*, bool> &visited, std::vector<char*> &strings)
{
    visited[node] = true;

    if(node->is_string)
{
        char *str = trace_string(node);
        if(str) strings.push_back(str);
    }

    for(const auto& [key, n]: node->children)
    {
        if(visited.count(n) == 0) 
            dfs(n, visited, strings);
    }
}

Node *Trie::get_node(const char *str)
{
    current_node = root;
    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if(current_node->children.count(str[i]) > 0)
        {
            current_node = current_node->children[str[i]];
            if(i + 1 == len) return current_node;
        }
        else if(!case_sensitive && current_node->children.count(char(str[i] - 32)) > 0)
        {
            current_node = current_node->children[char(str[i] - 32)];
            if(i + 1 == len) return current_node;
        }
        else
            break;
    }

    return nullptr;
}

void Trie::insert(const char *str)
{
    int len = strlen(str);
    current_node = root;

    for(int i = 0; i < len; i++)
    {
        if(current_node->children.count(str[i]) == 0)
        {
            Node *node = new Node();
            node->parent = current_node;
            node->c = str[i];
            node->depth = i + 1;
            current_node->children[node->c] = node;
        }

        current_node = current_node->children[str[i]];

        if(i + 1 == len)
        {
            current_node->is_string = true;
            string_count++;
        }
    }
}

void Trie::_remove(Node *node, char key)
{
    free(node->children[key]);
    node->children.erase(key);

    if(node->children.size() > 0)
        return;
    
    _remove(node->parent, node->c);
}
        

void Trie::remove(const char *str)
{
    current_node = get_node(str);

    if(current_node)
    {
        if(!current_node->children.empty())
            current_node->is_string = false;
        else
            _remove(current_node->parent, current_node->c);

        string_count--;
    }
}

std::vector<char*> Trie::starts_with(const char *str)
{
    current_node = get_node(str);

    if(current_node)
        return strings_from_node(current_node);

    return {};
}

std::vector<char*> Trie::strings_from_node(Node *node)
{
    std::vector<char*> strings;
    std::map<Node*, bool> visited;

    dfs(node, visited, strings);

    return strings;
}

char* Trie::trace_string(Node *node)
{
    current_node = node;

    char *str;
    str = (char*)malloc(sizeof(char) * node->depth + 1);

    if(str)
        str[node->depth] = 0;
    else
        return nullptr;

    for(int i = node->depth; i > 0; i--)
    {
        str[i - 1] = current_node->c;
        current_node = current_node->parent;
    }

    return str;
}
