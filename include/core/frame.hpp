// frame.hpp
#pragma once
#include "visit_state.hpp"
#include <variant>

namespace algo::core {

template <class Node, class It, class Extra = std::monostate>
struct Frame
{
    Node* node;
    Node* parent;
    It it;
    It end;
    VisitState state = VisitState::Enter;
    int depth;
    Extra extra;

    Frame(
        Node* node,
        It it,
        It end,
        VisitState state,
        int depth = 0
    )   :   node(node),
            parent(nullptr),
            it(it),
            end(end),
            state(state),
            depth(depth),
            extra()
    {}

};

} // namespace algo::core