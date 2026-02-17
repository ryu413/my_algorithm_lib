#pragma once

#include <iostream>
#include <vector>

namespace algo::dfs {

struct Node {
    int id;
    std::vector<Node*> children;
};

auto children = [](Node* n) -> std::vector<Node*> {
    return n -> children;
};

struct Pre {
    static void on_enter(Node* n) {
        std::cout << "enter: " << n->id << "\n";
    }
};

struct Post {
    static void on_exit(Node* n) {
        std::cout << "exit: " << n->id << "\n";
    }
};

template <class Node>
struct NodeTraits {
    using node_type = Node;
};




}