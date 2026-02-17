#pragma once

#include <vector>

#include "core/frame.hpp"
#include "core/visit_state.hpp"

namespace algo::core::engine {

/**
 * @brief 行きがけ処理 + 子ノード "push"の判断
 * 
 * @tparam Frame 
 * @tparam ChildrenFn 
 * @tparam Pre 
 * @param f 
 * @param children 
 * @param stack 
 * @return true 
 * @return false 
 */
template <class Frame, class ChildrenFn, class Pre>
auto handle_enter(Frame& f, ChildrenFn children, std::vector<Frame>& stack) -> bool
{
    Pre::on_enter(f.node);

    if (f.it != f.end) {
        auto* child = *f.it++;
        auto r = children(child);
        stack.push_back({child, r.begin(), r.end(), VisitState::Enter});
        return true; // 子に降りた
    }

    f.state = VisitState::Exit;
    return false; // 子がいない
}

} // namespace algo::core::engine