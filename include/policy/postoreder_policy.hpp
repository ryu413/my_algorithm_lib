#pragma once

namespace algo{

    
struct Pre {
    static void on_enter(Node* n) { visit(n); }
};

struct Post {
    static void on_exit(Node* n) {}
};

} // namespace algo