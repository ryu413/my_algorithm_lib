#pragma once

namespace algo::core::engine {

/**
 * @brief 帰りがけ処理
 * 
 * @tparam Frame 
 * @tparam Post 
 * @param f 
 */
template <class Frame, class Post>
auto handle_exit(Frame& f, Post) -> void
{
    Post::on_exit(f.node);
}

} // namespace algo::core::engine