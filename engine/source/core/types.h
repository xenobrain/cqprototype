#ifndef ENGINE_CORE_TYPES_H
#define ENGINE_CORE_TYPES_H

#include <cmath>
#include <cstdint>
#include <cstddef>

#include <array>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

namespace xc {

auto static constexpr PI = 3.14159265358979323846f;
auto static constexpr RAD2DEG = 360.f / (PI * 2.f);
auto static constexpr DEG2RAD = PI / 180.f;

template<typename T> struct color_t { T r, g, b, a; };
using color = color_t<std::uint8_t>;

namespace colors {

auto static constexpr WHITE =               color{255, 255, 255, 0};
auto static constexpr BLACK =               color{  0,   0,   0, 255};
auto static constexpr CORNFLOWER_BLUE =     color{100, 149, 237, 255};
}

template<typename T> struct rectangle_t { T x, y, w, h; };
using rectangle = rectangle_t<float>;

template<typename T, std::size_t N> struct vector;
template<typename T> struct vector<T,1> { T x; };
template<typename T> struct vector<T,2> { T x, y; };
using vector2 = vector<float,2>;

auto constexpr op_add = [](auto a, auto b) -> decltype(a + b) { return a + b; };
auto constexpr op_sub = [](auto a, auto b) -> decltype(a - b) { return a - b; };
auto constexpr op_mul = [](auto a, auto b) -> decltype(a * b) { return a * b; };
auto constexpr op_div = [](auto a, auto b) -> decltype(a / b) { return a / b; };

template<typename T> auto consteval op_sqrt(T a) -> T {
    auto constexpr lambda = [](T x, T current, T previous, auto&& lambda) -> T {
        return current == previous
            ? current
            : lambda(x, 0.5 * (current + x / current), current, lambda);
    };

    return a >= 0 && a < std::numeric_limits<decltype(a)>::infinity()
        ? lambda(a, a, 0, lambda)
        : std::numeric_limits<decltype(a)>::quiet_NaN();
};

template<typename A, typename B, class Op> auto constexpr map(Op const& op, vector<A,2> const& a, B const b) -> vector<A,2> { return {op(a.x, b), op(a.y, b)}; }
template<typename A, typename B, class Op> auto constexpr map(Op const& op, A a, vector<B,2> const& b) -> vector<B,2> { return {op(a, b.x), op(a, b.y)}; }
template<typename A, class Op> auto constexpr map(Op const& op, vector<A,2> const& a, vector<A,2> const& b) -> vector<A,2> { return {op(a.x, b.x), op(a.y, b.y)}; }

template<typename A, typename B, class Op> auto constexpr fold(A const a, vector<B,1> const& b, Op const& op) { return op(a, b.x); }
template<typename A, typename B, class Op> auto constexpr fold(A const a, vector<B,2> const& b, Op const& op) { return op(op(a, b.x), b.y); }

template<typename A, typename B> auto constexpr operator+(A const& a, B const& b) { return map(op_add, a, b); }
template<typename A, typename B> auto constexpr operator-(A const& a, B const& b) { return map(op_sub, a, b); }
template<typename A, typename B> auto constexpr operator*(A const& a, B const& b) { return map(op_mul, a, b); }
template<typename A, typename B> auto constexpr operator/(A const& a, B const& b) { return map(op_div, a, b); }
template<typename A, typename B> auto constexpr operator+=(A& a, B const& b) { return a = a + b; }
template<typename A, typename B> auto constexpr operator-=(A& a, B const& b) { return a = a - b; }
template<typename A, typename B> auto constexpr operator*=(A& a, B const& b) { return a = a * b; }
template<typename A, typename B> auto constexpr operator/=(A& a, B const& b) { return a = a / b; }

template<typename T> auto constexpr length_sq(vector<T,2> const& a) { return a.x * a.x + a.y * a.y; }
template<typename T> auto constexpr length(vector<T,2> const& a) { return std::sqrt(length_sq(a)); }
template<typename T> auto constexpr normalize(vector<T,2> const& a) { return a / length(a); }

template<typename T, class Op> auto constexpr sum(vector<T,2> const& a, Op const& op) { return op(a.x, a.y); }
template<typename T> auto constexpr cross(vector<T,2> const& a, vector<T,2> const& b) { return a.x * b.y - a.y * b.x; }
template<typename T> auto constexpr up(T radians) -> vector<T,2> { return {std::sin(radians), -std::cos(radians)}; }
template<typename T> auto constexpr forward(T radians) -> vector<T,2> { return {std::cos(radians), std::sin(radians)}; }
template<typename T, std::size_t N> auto constexpr dot(vector<T,N> const& a, vector<T,N> const& b) { return sum(a * b, op_add); }
template<class A, class B, class C> auto constexpr lerp(A a, B b, C c) { return a * (1 - c) + b * c; }

template<typename T> auto consteval radius_of_rectangle(T const width, T const height) ->T {
    return op_sqrt((width / 2) * (height / 2) * 2);
}

template<std::size_t N> auto consteval hash(char const (&string)[N], std::size_t count = N - 1) -> std::uint32_t {
    return count ? (hash(string, count - 1) ^ string[count - 1]) * 16777619u : 2166136261u;
}

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

auto constexpr remap = [](auto value, auto r1_begin, auto r1_end, auto r2_begin, auto r2_end) {
    return r2_begin + (value - r1_begin) * (r2_end - r2_begin) / (r1_end - r1_begin);
};

}

#endif // ENGINE_CORE_TYPES_H
