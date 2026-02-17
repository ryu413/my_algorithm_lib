#pragma once

#include "../visit_state.hpp"

namespace algo::core::engine {

/**
 * @brief Enter・Exitの状態遷移を抽象化
 * 
 * @tparam Frame 
 * @param f 
 */
template <class Frame>
void transition_state(Frame& f) {
    if (f.state == VisitState::Enter)
        f.state = VisitState::Exit;
}

} // namespace algo::core::engine