#pragma once

#include "core/frame.hpp"
#include "core/visit_state.hpp"
#include "core/engine/handle_enter.hpp"
#include "core/engine/handle_exit.hpp"
#include "core/engine/push_child.hpp"
#include "core/engine/advance_parent.hpp"

namespace algo::core::engine {

template <
    class Node,
    class ChildrenFn,
    class Pre,
    class Post
>
auto run(Node* root, ChildrenFn children) -> void {
    if (!root) return;

    using Range = decltype(children(root));
    using It = decltype(std::declval<Range>().begin());
    using FrameT = algo::core::Frame<Node, It>;

    std::vector<FrameT> stack;
    auto r = children(root);
    stack.push_back({root, r.begin(), r.end(), VisitState::Enter});

    while (!stack.empty()) {
        auto& f = stack.back();

        if (f.state == VisitState::Enter) {
            handle_enter<FrameT, ChildrenFn, Pre>(f, children, stack);
            continue;
        }

        handle_exit<FrameT, Post>(f, Post{});
        stack.pop_back();
        advance_parent<FrameT, ChildrenFn>(stack, children);
    }
}

} // namespace algo::core::engine