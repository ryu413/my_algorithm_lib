#include "core/basic_recursion_engine.hpp"
#include "search/dfs.hpp"

using namespace algo::core;
using namespace algo::dfs;

int main() {
    Node a{1}, b{2}, c{3};

    a.children = {&b, &c};
    b.children = {};
    c.children = {};

    algo::core::basic_node_recursion<Node, decltype(children), Pre, Post>(
        &a,
        children
    );
}