#pragma once

#include <vector>

#include "core/frame.hpp"
#include "core/visit_state.hpp"

namespace algo::core::engine {

/**
 * @brief 親に戻った後の処理
 * 
 * @tparam Frame 
 * @tparam ChildrenFn 
 * @param stack 
 * @param children 
 */
template <class Frame, class ChildrenFn>
void advance_parent(std::vector<Frame>& stack, ChildrenFn children) {
    if (stack.empty()) return;

    auto& parent = stack.back();
    if (parent.it == parent.end) {
        parent.state = VisitState::Exit;
    } else {
        auto* child = *parent.it++;
        auto r = children(child);
        stack.push_back({child, r.begin(), r.end(), VisitState::Enter});
    }
}

} // namespace algo::core::engine