#pragma once

#include "engine/engine.hpp"

namespace algo::core {

template <
    class Node,
    class ChildrenFn,
    class Pre,
    class Post
>
auto basic_node_recursion(Node* root, ChildrenFn children) -> void
{
    engine::run<Node, ChildrenFn, Pre, Post>(root, children);
}

} // namespace algo::core