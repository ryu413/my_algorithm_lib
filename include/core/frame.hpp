/// @file frame.hpp
#pragma once

#include "recursion_primitives.hpp"

namespace algo::recursion {

/**
 * @brief 
 * @details 再帰関数のスタックフレームを手動で再現
 * @tparam Node 
 * @tparam It 
 */
template <class Node, class It>
struct Frame {
    Node*       current;
    int         depth;
    It          it;
    It          end;
    PhaseKind   phase;      // 実行時フェーズ    (1byte)
    ControlKind control;    // 実行時コントロール (1byte)
};

} // namespace algo::recursion