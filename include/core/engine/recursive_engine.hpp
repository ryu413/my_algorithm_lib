#pragma once

namespace algo::core::engine {

template <class Node, class ChildrenFn, class EnterFn, class ExitFn>
auto recursive_engine(
    Node*       node,
    ChildrenFn  children,
    EnterFn     enter,
    ExitFn      exit
) -> void
{
    enter(node);
    for (auto* child : children(node)) {
        recursiv_engine(child, children, enter, exit);
    }
    exit(node);
}

}

winding
terminateing conditon
unwindinig