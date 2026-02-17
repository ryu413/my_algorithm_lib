#pragma once

#include "engine/engine.hpp"

namespace algo::core {

template <
    class Node,
    class ChildrenFn,
    class Pre,
    class Post
>
void basic_node_recursion(Node* root, ChildrenFn children) {
    engine::run<Node, ChildrenFn, Pre, Post>(root, children);
}

} // namespace algo::core