// frame.hpp
#pragma once
#include "visit_state.hpp"

namespace algo::core {

template <class Node, class It>
struct Frame {
    Node* node;
    It it;
    It end;
    VisitState state = VisitState::Enter;
};

} // namespace algo::core