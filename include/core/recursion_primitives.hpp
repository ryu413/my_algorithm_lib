/// @file recursion_primitives.hpp
/// @brief 再帰関数系のコアプリミティブ
/// @note　変更不可 + 追加可能 + 閉じた世界の保証！
#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>


namespace algo::recursion {
// ------------------------------------------------------------
// 正常系 Phase Tag
// ------------------------------------------------------------

/// @brief 再帰下降フェーズ (子へ降りる)
struct WindingTag {};
/// @brief 終了条件フェーズ (葉ノードなど)
struct TerminatingTag {};
/// @brief 再帰上昇フェーズ (親へ戻る)
struct UnwindingTag {};

// ------------------------------------------------------------
// 正常系 Control Tag.
// Phaseに対する独立した " 行動指示 "
// ------------------------------------------------------------

/// @brief 通常 DFS のように進む
struct ContinueTag {};
/// @brief 子 node をスキップ
struct SkipTag {};
/// @brief 全体停止
struct StopTag {};
/// @brief 手動で子へ降りる
struct RecurseTag {};
/// @brief 手動で親へ戻る
struct ReturnTag {};

// ------------------------------------------------------------
// 閉じた世界の列挙体 (実行時状態)
// ------------------------------------------------------------

enum class PhaseKind : std::uint8_t {
    Winding,
    Terminating,
    Unwinding,
};

enum class ControlKind : std::uint8_t {
    Continue,
    Skip,
    Stop,
    Recurse,
    Return,
};

// ------------------------------------------------------------
// Type predicates (型集合)
// ------------------------------------------------------------
/// @brief Phase型であるか？
template <class T>
struct is_phase : std::false_type {};

template <> struct is_phase<WindingTag>      : std::true_type {};
template <> struct is_phase<TerminatingTag>  : std::true_type {};
template <> struct is_phase<UnwindingTag>    : std::true_type {};

/// @brief Phase concept.
template<class T>
concept Phase = is_phase<T>::value;

/// @brief Control型であるか？
template <class T>
struct is_control : std::false_type {};

template <> struct is_control<ContinueTag>   : std::true_type {};
template <> struct is_control<SkipTag>       : std::true_type {};
template <> struct is_control<StopTag>       : std::true_type {};
template <> struct is_control<RecurseTag>    : std::true_type {};
template <> struct is_control<ReturnTag>     : std::true_type {};

/// @brief Control concept.
template <class T>
concept PhaseControllable = is_control<T>::value;


// ------------------------------------------------------------
// enum -> Tag を「返さずに」渡すディスパッチ
// (戻り値問題・slicing/variantを全部回避)
// ------------------------------------------------------------

/// @brief PhaseKind を型レベルのタグにディスパッチする。
/// @details タグ型は返さず、コールバックに直接渡すことで slicing や型推論の問題を回避する。
template <class F>
[[nodiscard]] inline constexpr
decltype(auto) with_phase_tag(PhaseKind k, F&& f)
{
    switch (k) {
    case PhaseKind::Winding:     return std::forward<F>(f)(WindingTag{}); 
    case PhaseKind::Terminating: return std::forward<F>(f)(TerminatingTag{}); 
    case PhaseKind::Unwinding:   return std::forward<F>(f)(UnwindingTag{}); 
    }
    __builtin_unreachable();    // 閉じた世界であるからここには来ないはず
}

/// @brief PhaseKind を型レベルのタグにディスパッチする。
/// @details タグ型は返さず、コールバックに直接渡すことで slicing や型推論の問題を回避する。
template <class F>
[[nodiscard]] inline constexpr
decltype(auto) with_control_tag(ControlKind k, F&& f)
{
    switch (k) {
    case ControlKind::Continue:  return std::forward<F>(f)(ContinueTag{});
    case ControlKind::Skip:      return std::forward<F>(f)(SkipTag{});
    case ControlKind::Stop:      return std::forward<F>(f)(StopTag{});
    case ControlKind::Recurse:   return std::forward<F>(f)(RecurseTag{});
    case ControlKind::Return:    return std::forward<F>(f)(ReturnTag{});
    }
    __builtin_unreachable();    // 閉じた世界であるからここには来ないはず
}

// ------------------------------------------------------------
// Tag型 -> enum 変換 (型レベル -> 実行時)
// ------------------------------------------------------------

template <Phase P>
[[nodiscard]] inline constexpr auto to_phase_tag(P) -> PhaseKind
{
    if constexpr (std::is_same_v<P, WindingTag>) {
        return PhaseKind::Winding;
    } else if constexpr (std::is_same_v<P, TerminatingTag>) {
        return PhaseKind::Terminating;
    } else {
        static_assert(std::is_same_v<P, UnwindingTag>);
        return PhaseKind::Unwinding;
    }
}

template <PhaseControllable C>
[[nodiscard]] inline constexpr auto to_control_kind(C) -> ControlKind
{
    if constexpr (std::is_same_v<C, ContinueTag>) {
        return ControlKind::Continue;
    } else if constexpr (std::is_same_v<C, SkipTag>) {
        return ControlKind::Skip;
    } else if constexpr (std::is_same_v<C, StopTag>) {
        return ControlKind::Stop;
    } else if constexpr (std::is_same_v<C, RecurseTag>) {
        return ControlKind::Recurse;
    } else {
        static_assert(std::is_same_v<C, ReturnTag>);
        return ControlKind::Return;
    }
}

// ------------------------------------------------------------
// Callback Concept
// ------------------------------------------------------------

/// @brief Winding フェーズに対応する on() を持つか
template <class Callback, class Node>
concept WindingCallback = requires (Callback cb, Node* n, int depth) {
        { cb.on(WindingTag {}, n, depth) } -> PhaseControllable;
    };

/// @brief Unwinding フェーズに対応する on() を持つか
template <class Callback, class Node>
concept UnwindingCallback = requires (Callback cb, Node* n, int depth) {
        { cb.on(UnwindingTag {}, n, depth) } -> PhaseControllable;
    };

/// @brief Terminating フェーズに対応する on() を持つか
template <class Callback, class Node>
concept TerminatingCallback = requires (Callback cb, Node* n, int depth) {
        { cb.on(TerminatingTag {}, n, depth) } -> PhaseControllable;
    };

}   // namespace algo::recursion.