#pragma once

#include "../frame.hpp"

namespace algo::core::engine {

/**
 * @brief 親のフレームから次の子を "push"
 * 
 * @tparam Frame 
 * @tparam ChildrenFn 
 * @param parent 
 * @param children 
 * @param stack 
 * @return true 
 * @return false 
 */
template <class Frame, class ChildrenFn>
bool push_child(Frame& parent, ChildrenFn children, std::vector<Frame>& stack) {
    if (parent.it == parent.end) return false;

    auto* child = *parent.it++;
    auto r = children(child);
    stack.push_back({child, r.begin(), r.end(), VisitState::Enter});
    return true;
}

} // namespace algo::core::engine