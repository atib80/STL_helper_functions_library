#ifndef _STL_HELPER_FUNCTIONS_H_
#define _STL_HELPER_FUNCTIONS_H_

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <Strsafe.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cwchar>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define STL_HELPER_UTILITY_MAJOR_VERSION 1
#define STL_HELPER_UTILITY_MINOR_VERSION 1

#define PRINT_VAR_NAME(arg) std::cout << #arg << ' '
#define PRINT_VAR_NAMEW(arg) std::wcout << #arg << L' '

namespace cpp {
namespace experimental {
enum class string_type { cstr, wstr, u16_str, u32_str };

template <typename T>
constexpr const std::type_info& get_type_id(const T&) {
  return typeid(T);
}

template <typename T>
std::string get_type_name(T&&) {
  return std::string{typeid(T).name()};
}

template <typename T>
std::wstring get_type_name_wstr(T&&) {
  const std::string cstr{typeid(T).name()};

  return std::wstring{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T>
std::u16string get_type_name_u16str(T&&) {
  const std::string cstr{typeid(T).name()};

  return std::u16string{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T>
std::u32string get_type_name_u32str(T&&) {
  const std::string cstr{typeid(T).name()};

  return std::u32string{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T, typename... Rest>
struct is_all_of : std::true_type {};

template <typename T, typename First>
struct is_all_of<T, First> : std::is_same<T, First> {};

template <typename T, typename First, typename... Rest>
struct is_all_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same_v<T, First> &&
                                 is_all_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
inline constexpr bool is_all_of_v = is_all_of<T, First, Rest...>::value;

template <typename T>
constexpr bool are_data_types_equal(const T&) {
  return true;
}

template <typename T, typename U, typename... Args>
constexpr bool are_data_types_equal(const T& arg1,
                                    const U&,
                                    const Args&... args) {
  return std::is_same_v<T, U> && are_data_types_equal(arg1, args...);
}

template <typename T, typename U, typename... Args>
constexpr bool check_data_types_for_equality(const T& arg1,
                                             const U& arg2,
                                             const Args&... args) {
  return check_data_types_for_equality(arg1, arg2, args...);
}

template <typename T, typename... Rest>
struct is_anyone_of : std::false_type {};

template <typename T, typename First>
struct is_anyone_of<T, First> : std::is_same<T, First> {};

template <typename T, typename First, typename... Rest>
struct is_anyone_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same_v<T, First> ||
                                 is_anyone_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
inline constexpr bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

template <typename T>
void show_var_info(const T& arg, std::ostream& os) {
  os << "\nName: ";
  PRINT_VAR_NAME(arg);
  os << "\nType: " << get_type_name(arg) << "\nValue: " << arg << '\n';
}

template <typename T>
void show_var_info_w(const T& arg, std::wostream& wos) {
  wos << L"\nName: ";
  PRINT_VAR_NAMEW(arg);
  wos << L"\nType: " << get_type_name(arg) << L"\nValue: " << arg << '\n';
}

struct char_buffer_deleter {
  using pointer_type = char*;

  void operator()(const pointer_type pointer) const noexcept {
    delete[] pointer;
  }
};

struct wchar_t_buffer_deleter {
  using pointer_type = wchar_t*;

  void operator()(const pointer_type pointer) const noexcept {
    delete[] pointer;
  }
};

template <typename... Args>
int say_slow(const size_t time_delay_in_ms,
             const char* format_string,
             Args... args) {
  auto const buffer_size = _scprintf(format_string, args...) + 1;

  std::unique_ptr<char[], char_buffer_deleter> output_buffer_sp(
      new char[buffer_size], char_buffer_deleter{});

  if (!output_buffer_sp)
    return -1;

  StringCchPrintfA(output_buffer_sp.get(), buffer_size, format_string, args...);

  int final_ret_val{};

  for (size_t i{}; i < strlen(output_buffer_sp.get()); ++i) {
    const int ret_val{printf("%c", output_buffer_sp.get()[i])};

    if (ret_val < 0)
      return final_ret_val;

    final_ret_val += ret_val;

    std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));
  }

  return final_ret_val;
}

template <typename... Args>
int say_slow(const size_t time_delay_in_ms,
             const wchar_t* format_string,
             Args... args) {
  auto const buffer_size = _scwprintf(format_string, args...) + 1;

  std::unique_ptr<wchar_t[], wchar_t_buffer_deleter> output_buffer_sp(
      new wchar_t[buffer_size], wchar_t_buffer_deleter{});

  if (!output_buffer_sp)
    return -1;

  StringCchPrintfW(output_buffer_sp.get(), buffer_size, format_string, args...);

  int final_ret_val{};

  for (size_t i = 0; i < wcslen(output_buffer_sp.get()); ++i) {
    const int ret_val{wprintf(L"%c", output_buffer_sp.get()[i])};

    if (ret_val < 0)
      return final_ret_val;

    final_ret_val += ret_val;

    std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));
  }

  return final_ret_val;
}

template <typename... Args>
int say(const char* format_string, Args... args) {
  auto const buffer_size = _scprintf(format_string, args...) + 1;

  std::unique_ptr<char[], char_buffer_deleter> output_buffer_sp(
      new char[buffer_size], char_buffer_deleter{});

  if (!output_buffer_sp)
    return -1;

  StringCchPrintfA(output_buffer_sp.get(), buffer_size, format_string, args...);

  return printf("%s", output_buffer_sp.get());
}

template <typename... Args>
int say(const wchar_t* format_string, Args... args) {
  auto const buffer_size = _scwprintf(format_string, args...) + 1;

  std::unique_ptr<wchar_t[], wchar_t_buffer_deleter> output_buffer_sp(
      new wchar_t[buffer_size], wchar_t_buffer_deleter{});

  if (!output_buffer_sp)
    return -1;

  StringCchPrintfW(output_buffer_sp.get(), buffer_size, format_string, args...);

  return wprintf(L"%ls", output_buffer_sp.get());
}

template <typename T>
void swap(T& first, T& second, std::true_type) noexcept {
  std::cout << "swap by moving the contents of first and second\n";

  T tmp{std::move(first)};
  first = std::move(second);
  second = std::move(tmp);
}

template <typename T>
void swap(T& first, T& second, std::false_type) {
  std::cout << "swap by copying the contents of first and second\n";

  T tmp{first};
  first = second;
  second = tmp;
}

template <typename T>
void swap(T& first, T& second) {
  swap(first, second,
       std::conditional_t < std::is_nothrow_move_constructible_v<T> &&
           std::is_nothrow_move_assignable_v<T>,
       std::true_type, std::false_type > {});
}

template <typename BiDirIter1, typename BiDirIter2>
constexpr inline BiDirIter2 copy_backward(BiDirIter1 src_first,
                                          BiDirIter1 src_last,
                                          BiDirIter2 dst_last) {
  if (src_first == src_last)
    return dst_last;

  while (src_first != src_last) {
    *(--dst_last) = *(--src_last);
  }

  return dst_last;
}

template <typename CharType,
          typename = std::enable_if_t<
              is_anyone_of_v<CharType, char, wchar_t, char16_t, char32_t>>>
bool is_ws_char(CharType ch) {
  switch (ch) {
    case static_cast<CharType>(' '):
    case static_cast<CharType>('\n'):
    case static_cast<CharType>('\r'):
    case static_cast<CharType>('\t'):
    case static_cast<CharType>('\v'):
    case static_cast<CharType>('\f'):
      return true;

    default:
      return false;
  }
}

template <typename CharType>
struct default_whitespace_chars {};

template <>
struct default_whitespace_chars<char> {
  static constexpr const char* value = " \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<wchar_t> {
  static constexpr const wchar_t* value = L" \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<char16_t> {
  static constexpr const char16_t* value = u" \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<char32_t> {
  static constexpr const char32_t* value = U" \t\n\f\v\r";
};

template <typename CharType>
constexpr const CharType* default_whitespace_chars_v =
    default_whitespace_chars<CharType>::value;

template <typename T>
struct get_char_type_from_char_pointer_or_char_array {
  using type = std::remove_cv_t<
      std::remove_pointer_t<std::remove_cv_t<std::decay_t<T>>>>;
};

template <typename T>
using get_char_type_t =
    typename get_char_type_from_char_pointer_or_char_array<T>::type;

template <typename T>
struct is_valid_char_type {
  static constexpr const bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
constexpr const bool is_valid_char_type_v = is_valid_char_type<T>::value;

template <typename T>
struct is_non_const_char_pointer_type {
  static constexpr const bool value = is_anyone_of_v<T,
                                                     char*,
                                                     wchar_t*,
                                                     char16_t*,
                                                     char32_t*,
                                                     char* const,
                                                     wchar_t* const,
                                                     char16_t* const,
                                                     char32_t* const>;
};

template <typename T>
constexpr const bool is_non_const_char_pointer_type_v =
    is_non_const_char_pointer_type<T>::value;

template <typename T>
struct is_const_char_pointer_type {
  static constexpr const bool value = is_anyone_of_v<T,
                                                     const char*,
                                                     const wchar_t*,
                                                     const char16_t*,
                                                     const char32_t*,
                                                     const char* const,
                                                     const wchar_t* const,
                                                     const char16_t* const,
                                                     const char32_t* const>;
};

template <typename T>
constexpr const bool is_const_char_pointer_type_v =
    is_const_char_pointer_type<T>::value;

template <typename T>
struct is_non_const_char_array_type {
  static constexpr bool value =
      std::is_array_v<T> && 1u == std::rank_v<T> && !std::is_const_v<T>;
};

template <typename T>
constexpr const bool is_non_const_char_array_type_v =
    is_non_const_char_array_type<T>::value;

template <typename T>
struct is_const_char_array_type {
  static constexpr bool value =
      std::is_array_v<T> && 1u == std::rank_v<T> && std::is_const_v<T>;
};

template <typename T>
constexpr const bool is_const_char_array_type_v =
    is_const_char_array_type<T>::value;

template <typename T>
struct is_valid_string_type {
  static constexpr const bool value = is_anyone_of_v<
      std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<T>>>,
      std::string,
      std::wstring,
      std::u16string,
      std::u32string>;
};

template <typename T>
constexpr const bool is_valid_string_type_v = is_valid_string_type<T>::value;

template <typename T>
struct add_const_pointer_to_char_type {
  using type = std::add_const_t<
      std::add_pointer_t<std::add_const_t<get_char_type_t<T>>>>;
};

template <typename T>
using add_const_pointer_to_char_type_t =
    typename add_const_pointer_to_char_type<T>::type;

static constexpr size_t max_string_length{std::string::npos};

template <
    typename T,
    typename = std::enable_if_t<
        is_const_char_array_type_v<T> || is_non_const_char_array_type_v<T> ||
        is_const_char_pointer_type_v<T> ||
        is_non_const_char_pointer_type_v<T> || is_valid_string_type_v<T>>>
size_t len(T src, size_t max_allowed_string_length = max_string_length) {
  if constexpr (is_valid_string_type_v<T>) {
    return src.length() > max_allowed_string_length ? max_allowed_string_length
                                                    : src.length();
  } else {
    if (nullptr == src)
      return 0u;

    size_t length{};

    while (*src++) {
      ++length;

      if (max_allowed_string_length == length)
        return max_allowed_string_length;
    }

    return length;
  }
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T>>>

bool trim_in_place(
    T src,
    const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  const auto str_len{len(src)};

  if (!str_len)
    return false;

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const T first_char_pos{
      std::find_if(src, src + str_len, [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  T last_char_pos{src + str_len};

  if (first_char_pos == last_char_pos) {
    *src = static_cast<char_type>('\0');
    return true;
  }

  const auto rstart{std::make_reverse_iterator(src + str_len)};
  const auto rlast{std::make_reverse_iterator(first_char_pos)};

  last_char_pos =
      std::find_if(rstart, rlast,
                   [&trimmed_chars](const auto ch) {
                     return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                   })
          .base();

  if (src == first_char_pos) {
    if (src + str_len == last_char_pos)
      return false;

    *last_char_pos = static_cast<char_type>('\0');

    return true;
  }

  std::copy(first_char_pos, last_char_pos, src);
  src[static_cast<typename std::iterator_traits<T>::difference_type>(
      last_char_pos - first_char_pos)] = static_cast<char_type>('\0');
  return true;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool trim_in_place(
    StringType& src,
    const add_const_pointer_to_char_type_t<typename StringType::value_type>
        chars_to_trim =
            default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  const auto str_len{src.length()};

  if (!str_len)
    return false;

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first_char_pos{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  auto last_char_pos{std::cend(src)};

  if (first_char_pos == last_char_pos) {
    src.clear();
    return true;
  }

  last_char_pos =
      std::find_if(std::crbegin(src), std::crend(src),
                   [&trimmed_chars](const auto ch) {
                     return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                   })
          .base();

  if (std::cbegin(src) == first_char_pos) {
    if (std::cend(src) == last_char_pos)
      return false;

    src.clear();
    return true;
  }

  std::basic_string<char_type> output{};
  output.reserve(last_char_pos - first_char_pos + 1);
  output.assign(first_char_pos, last_char_pos);
  src = std::move(output);
  return true;
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T>>>
bool ltrim_in_place(
    T src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  const auto str_len{len(src)};

  if (!str_len)
    return false;

  const T last_char_pos{src + str_len};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const T first_char_pos{
      std::find_if(src, last_char_pos, [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first_char_pos == src)
    return false;

  if (first_char_pos == last_char_pos) {
    *src = static_cast<char_type>('\0');
    return true;
  }

  std::copy(first_char_pos, last_char_pos, src);
  src[static_cast<typename std::iterator_traits<T>::difference_type>(
      last_char_pos - first_char_pos)] = static_cast<char_type>('\0');

  return true;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool ltrim_in_place(
    StringType& src,
    const add_const_pointer_to_char_type_t<typename StringType::value_type>
        chars_to_trim =
            default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  const auto str_len{src.length()};

  if (!str_len)
    return false;

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first_char_pos{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first_char_pos == std::cend(src)) {
    src.clear();
    return true;
  } else if (std::cbegin(src) != first_char_pos) {
    src.erase(std::cbegin(src), first_char_pos);
    return true;
  }

  return false;
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T>>>

bool rtrim_in_place(
    T src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  const auto str_len{len(src)};

  if (0 == str_len)
    return false;

  const auto rstart{std::make_reverse_iterator(src + str_len)};
  const auto rlast{std::make_reverse_iterator(src)};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const T last_char_pos =
      std::find_if(rstart, rlast,
                   [&trimmed_chars](const auto ch) {
                     return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                   })
          .base();

  if (src + str_len == last_char_pos)
    return false;

  *last_char_pos = static_cast<char_type>('\0');

  return true;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool rtrim_in_place(
    StringType& src,
    const add_const_pointer_to_char_type_t<typename StringType::value_type>
        chars_to_trim =
            default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  const auto str_len{src.length()};

  if (!str_len)
    return false;

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto last_char_pos =
      std::find_if(std::crbegin(src), std::crend(src),
                   [&trimmed_chars](const auto ch) {
                     return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                   })
          .base();

  if (std::cend(src) == last_char_pos)
    return false;

  src.erase(last_char_pos, std::cend(src));
  return true;
}

template <
    typename T,
    typename = std::enable_if_t<
        is_const_char_array_type_v<T> || is_non_const_char_array_type_v<T> ||
        is_const_char_pointer_type_v<T> || is_non_const_char_pointer_type_v<T>>>

auto trim(T src,
          add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
              default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (nullptr == src)
    return std::basic_string<char_type>{};

  std::basic_string<char_type> source_str{src};

  if (0 == source_str.length())
    return std::basic_string<char_type>{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(std::cbegin(source_str), std::cend(source_str),
                                [&trimmed_chars](const auto ch) {
                                  return trimmed_chars.find(ch) ==
                                         std::cend(trimmed_chars);
                                })};

  if (first == std::cend(source_str))
    return std::basic_string<char_type>{};

  const auto last{std::find_if(std::crbegin(source_str), std::crend(source_str),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return std::basic_string<char_type>(first, last);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>

auto trim(const StringType& src,
          add_const_pointer_to_char_type_t<typename StringType::value_type>
              chars_to_trim =
                  default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  if (0 == src.length())
    return StringType{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return StringType{};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return StringType(first, last);
}

template <
    typename T,
    typename = std::enable_if_t<
        is_const_char_array_type_v<T> || is_non_const_char_array_type_v<T> ||
        is_const_char_pointer_type_v<T> || is_non_const_char_pointer_type_v<T>>>

auto ltrim(T src,
           add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
               default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (nullptr == src)
    return std::basic_string<char_type>{};

  if (0 == len(src))
    return std::basic_string<char_type>{};

  std::basic_string<char_type> source_str{src};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(std::cbegin(source_str), std::cend(source_str),
                                [&trimmed_chars](const auto ch) {
                                  return trimmed_chars.find(ch) ==
                                         std::cend(trimmed_chars);
                                })};

  if (first == std::cbegin(source_str))
    return source_str;

  const auto last{std::cend(source_str)};

  if (first == last)
    return std::basic_string<char_type>{};

  return std::basic_string<char_type>(first, last);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>

auto ltrim(const StringType& src,
           add_const_pointer_to_char_type_t<
               typename StringType::value_type> chars_to_trim =
               default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  if (0 == src.length())
    return StringType{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cbegin(src))
    return src;

  const auto last{std::cend(src)};

  if (first == last)
    return StringType{};

  return StringType(first, last);
}

template <
    typename T,
    typename = std::enable_if_t<
        is_const_char_array_type_v<T> || is_non_const_char_array_type_v<T> ||
        is_const_char_pointer_type_v<T> || is_non_const_char_pointer_type_v<T>>>

auto rtrim(T src,
           add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
               default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (nullptr == src)
    return std::basic_string<char_type>{};

  const auto src_len{len(src)};

  if (0 == src_len)
    return std::basic_string<char_type>{};

  std::basic_string<char_type> source_str{src};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto last{std::find_if(std::crbegin(source_str), std::crend(source_str),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  source_str.erase(last, cend(source_str));

  return source_str;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>

auto rtrim(const StringType& src,
           add_const_pointer_to_char_type_t<
               typename StringType::value_type> chars_to_trim =
               default_whitespace_chars_v<typename StringType::value_type>) {
  using char_type = typename StringType::value_type;

  StringType source_str{src};

  if (0 == source_str.length())
    return StringType{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto last{std::find_if(std::rbegin(source_str), std::rend(source_str),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  source_str.erase(last, end(source_str));

  return source_str;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U> ||
                   is_valid_char_type_v<get_char_type_t<
                       U>>)&&(std::is_same_v<get_char_type_t<T>,
                                             get_char_type_t<U>>)>>
bool str_starts_with(T src,
                     const U needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if (nullptr == src)
    return false;

  const size_t src_len{len(src)};

  if (0 == src_len)
    return false;

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    if (!ignore_case)
      return needle == src[0];

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);
      return f.tolower(src[0]) == f.tolower(needle);
    }

    return std::tolower(src[0]) == std::tolower(needle);

  } else {
    const size_t needle_len{len(needle)};

    if (0 == needle_len || needle_len > src_len)
      return false;

    if (!ignore_case) {
      for (size_t i{}; i < needle_len; i++) {
        if (src[i] != needle[i])
          return false;
      }

      return true;
    }

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);

      for (size_t i{}; i < needle_len; i++) {
        if (src[i] == needle[i])
          continue;

        if (f.tolower(src[i]) != f.tolower(needle[i]))
          return false;
      }

      return true;
    }

    for (size_t i{}; i < needle_len; i++) {
      if (src[i] == needle[i])
        continue;

      if (std::tolower(src[i]) != std::tolower(needle[i]))
        return false;
    }

    return true;
  }
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_starts_with(const StringType& src,
                     const typename StringType::value_type start_char,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  if (0u == src.length())
    return false;

  if (!ignore_case)
    return start_char == src[0];

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    return f.tolower(src[0]) == f.tolower(start_char);
  }

  return std::tolower(src[0]) == std::tolower(start_char);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_starts_with(const StringType& src,
                     typename StringType::const_pointer needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const auto needle_len{len(needle)};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return 0u == src.find(needle);

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < needle_len; i++) {
      if (src[i] == needle[i])
        continue;

      if (f.tolower(src[i]) != f.tolower(needle[i]))
        return false;
    }

    return true;
  }

  for (size_t i{}; i < needle_len; i++) {
    if (src[i] == needle[i])
      continue;

    if (std::tolower(src[i]) != std::tolower(needle[i]))
      return false;
  }

  return true;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_starts_with(const StringType& src,
                     const StringType& needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return 0u == src.find(needle);

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < needle_len; i++) {
      if (src[i] == needle[i])
        continue;

      if (f.tolower(src[i]) != f.tolower(needle[i]))
        return false;
    }

    return true;
  }

  for (size_t i{}; i < needle_len; i++) {
    if (src[i] == needle[i])
      continue;

    if (std::tolower(src[i]) != std::tolower(needle[i]))
      return false;
  }

  return true;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U> ||
                   is_valid_char_type_v<get_char_type_t<
                       U>>)&&(std::is_same_v<get_char_type_t<T>,
                                             get_char_type_t<U>>)>>
size_t str_index_of(T src,
                    const U needle,
                    const size_t start_pos = 0u,
                    const bool ignore_case = false,
                    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if (nullptr == src)
    return std::basic_string<char_type>::npos;

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    const size_t src_len{len(src)};

    if (0 == src_len)
      return std::basic_string<char_type>::npos;

    if (!ignore_case) {
      std::basic_string_view<char_type> src_str_view{src, src_len};
      return src_str_view.find(needle, start_pos);
    }

    std::basic_string<char_type> src_str{src};
    auto needle_lc{needle};

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);

      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str),
                     [&f](const auto ch) { return f.tolower(ch); });
      needle_lc = f.tolower(needle);

    } else {
      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });

      needle_lc = static_cast<char_type>(std::tolower(needle));
    }

    return src_str.find(needle_lc, start_pos);

  } else {
    if (nullptr == needle)
      return std::basic_string<char_type>::npos;

    std::basic_string<char_type> src_str{src};
    std::basic_string<char_type> needle_str{needle};

    const auto src_len{src_str.length()};
    const auto needle_len{needle_str.length()};

    if (0 == src_len || 0 == needle_len || needle_len > src_len)
      return std::basic_string<char_type>::npos;

    if (!ignore_case)
      return src_str.find(needle_str, start_pos);

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);
      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str),
                     [&f](const auto ch) { return f.tolower(ch); });
      std::transform(std::cbegin(needle_str), std::cend(needle_str),
                     std::begin(needle_str),
                     [&f](const auto ch) { return f.tolower(ch); });

    } else {
      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });
      std::transform(std::cbegin(needle_str), std::cend(needle_str),
                     std::begin(needle_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });
    }

    return src_str.find(needle_str, start_pos);
  }
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
auto str_index_of(const StringType& src,
                  const typename StringType::value_type needle_char,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  if (0 == src.length())
    return StringType::npos;

  if (!ignore_case)
    return src.find(needle_char, start_pos);

  StringType src_lc{src};
  auto needle_char_lc{needle_char};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });
    needle_char_lc = f.tolower(needle_char);

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
    needle_char_lc = static_cast<char_type>(std::tolower(needle_char));
  }

  return src_lc.find(needle_char_lc, start_pos);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
auto str_index_of(const StringType& src,
                  typename StringType::const_pointer needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto text_len{src.length()};
  const auto needle_len{len(needle)};

  if (0 == text_len || 0 == needle_len || needle_len > text_len)
    return StringType::npos;

  if (!ignore_case)
    return src.find(needle, start_pos);

  StringType src_lc{src};
  StringType needle_str{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });
    std::transform(std::cbegin(needle_str), std::cend(needle_str),
                   std::begin(needle_str),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
    std::transform(
        std::cbegin(needle_str), std::cend(needle_str), std::begin(needle_str),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
  }

  return src_lc.find(needle_str, start_pos);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
auto str_index_of(const StringType& src,
                  const StringType& needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0 == src_len || 0 == needle_len || needle_len > src_len)
    return StringType::npos;

  if (!ignore_case)
    return src.find(needle, start_pos);

  StringType src_lc{src};
  StringType needle_lc{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });
    std::transform(std::cbegin(needle), std::cend(needle),
                   std::begin(needle_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
    std::transform(
        std::cbegin(needle), std::cend(needle), std::begin(needle_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
  }

  return src_lc.find(needle_lc, start_pos);
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U> ||
                   is_valid_char_type_v<get_char_type_t<
                       U>>)&&(std::is_same_v<get_char_type_t<T>,
                                             get_char_type_t<U>>)>>
bool str_contains(T src,
                  const U needle,
                  size_t start_pos = 0u,
                  bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if (nullptr == src)
    return false;

  const auto src_len{len(src)};

  if (0 == src_len)
    return false;

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    if (!ignore_case)
      return src + src_len != std::find(src + start_pos, src + src_len, needle);

    std::basic_string<char_type> src_str{src};
    auto needle_lc{needle};

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);

      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str),
                     [&f](const auto ch) { return f.tolower(ch); });
      needle_lc = f.tolower(needle);
    } else {
      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });

      needle_lc = static_cast<char_type>(std::tolower(needle));
    }

    return std::basic_string<char_type>::npos !=
           src_str.find(needle_lc, start_pos);

  } else {
    const auto needle_len{len(needle)};

    if (0 == needle_len || needle_len > src_len)
      return false;

    std::basic_string_view<char_type> src_str_view(src, src_len);
    std::basic_string_view<char_type> needle_str_view(needle, needle_len);

    if (!ignore_case)
      return std::basic_string_view<char_type>::npos !=
             src_str_view.find(needle_str_view, start_pos);

    std::basic_string<char_type> src_str{src};
    std::basic_string<char_type> needle_str{needle};

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);

      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str),
                     [&f](const auto ch) { return f.tolower(ch); });

      std::transform(std::cbegin(needle_str), std::cend(needle_str),
                     std::begin(needle_str),
                     [&f](const auto ch) { return f.tolower(ch); });

    } else {
      std::transform(std::cbegin(src_str), std::cend(src_str),
                     std::begin(src_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });

      std::transform(std::cbegin(needle_str), std::cend(needle_str),
                     std::begin(needle_str), [](const auto ch) {
                       return static_cast<char_type>(std::tolower(ch));
                     });
    }

    return std::basic_string<char_type>::npos !=
           src_str.find(needle_str, start_pos);
  }
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_contains(const StringType& src,
                  const typename StringType::value_type needle_char,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;
  if (0u == src.length())
    return false;

  if (!ignore_case)
    return StringType::npos != src.find(needle_char, start_pos);

  StringType src_lc{src};
  auto needle_char_lc{needle_char};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

    needle_char_lc = f.tolower(needle_char);

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });

    needle_char_lc = static_cast<char_type>(std::tolower(needle_char));
  }

  return StringType::npos != src_lc.find(needle_char_lc, start_pos);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_contains(const StringType& src,
                  typename StringType::const_pointer needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const auto needle_len{len(needle)};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return src.find(needle, start_pos) != StringType::npos;

  StringType src_lc{src};
  StringType needle_str{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

    std::transform(std::cbegin(needle_str), std::cend(needle_str),
                   std::begin(needle_str),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });

    std::transform(
        std::cbegin(needle_str), std::cend(needle_str), std::begin(needle_str),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
  }

  return StringType::npos != src_lc.find(needle_str, start_pos);
}

template <typename StringType>
bool str_contains(const StringType& src,
                  const StringType& needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return StringType::npos != src.find(needle, start_pos);

  const auto& f = std::use_facet<std::ctype<char_type>>(loc);

  StringType src_lc{src};
  StringType needle_lc{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    std::transform(std::cbegin(src), std::cend(src), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

    std::transform(std::cbegin(needle), std::cend(needle),
                   std::begin(needle_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src), std::cend(src), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });

    std::transform(
        std::cbegin(needle), std::cend(needle), std::begin(needle_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
  }

  return StringType::npos != src_lc.find(needle_lc, start_pos);
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U> ||
                   is_valid_char_type_v<get_char_type_t<
                       U>>)&&(std::is_same_v<get_char_type_t<T>,
                                             get_char_type_t<U>>)>>
bool str_ends_with(T src,
                   const U needle,
                   bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if (nullptr == src)
    return false;

  const size_t src_len{len(src)};

  if (0u == src_len)
    return false;

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    if (!ignore_case)
      return needle == src[src_len - 1];

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);
      return f.tolower(src[src_len - 1]) == f.tolower(needle);
    }

    return std::tolower(src[src_len - 1]) == std::tolower(needle);

  } else {
    const size_t needle_len{len(needle)};

    if (0u == needle_len || needle_len > src_len)
      return false;

    const size_t expected_start_pos_of_end_tag{src_len - needle_len};

    if (!ignore_case) {
      for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len;
           i++, j++) {
        if (src[i] != needle[j])
          return false;
      }

      return true;
    }

    if (std::has_facet<std::ctype<char_type>>(loc)) {
      const auto& f = std::use_facet<std::ctype<char_type>>(loc);

      for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len;
           i++, j++) {
        if (src[i] == needle[j])
          continue;

        if (f.tolower(src[i]) != f.tolower(needle[j]))
          return false;
      }

      return true;
    }

    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (src[i] == needle[j])
        continue;

      if (std::tolower(src[i]) != std::tolower(needle[j]))
        return false;
    }

    return true;
  }
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_ends_with(const StringType& src,
                   const typename StringType::value_type end_char,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  if (0u == src.length())
    return false;

  if (!ignore_case)
    return src.back() == end_char;

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    return f.tolower(src.back()) == f.tolower(end_char);
  }

  return std::tolower(src.back()) == std::tolower(end_char);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_ends_with(const StringType& src,
                   typename StringType::const_pointer needle,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const size_t needle_len{len(needle)};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  const size_t expected_start_pos_of_end_tag{src_len - needle_len};

  if (!ignore_case) {
    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (src[i] != needle[j])
        return false;
    }

    return true;
  }

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (src[i] == needle[j])
        continue;

      if (f.tolower(src[i]) != f.tolower(needle[j]))
        return false;
    }

    return true;
  }

  for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
    if (src[i] == needle[j])
      continue;

    if (std::tolower(src[i]) != std::tolower(needle[j]))
      return false;
  }

  return true;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
bool str_ends_with(const StringType& src,
                   const StringType& needle,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const auto src_len{src.length()};
  const size_t needle_len{needle.length()};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  const size_t expected_start_pos_of_end_tag{src_len - needle_len};

  if (!ignore_case) {
    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (src[i] != needle[j])
        return false;
    }

    return true;
  }

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (src[i] == needle[j])
        continue;

      if (f.tolower(src[i]) != f.tolower(needle[j]))
        return false;
    }

    return true;
  }

  for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
    if (src[i] == needle[j])
      continue;

    if (std::tolower(src[i]) != std::tolower(needle[j]))
      return false;
  }

  return true;
}

template <typename... Args>
void unused_args(Args&&...) {}

template <typename T, typename... Args>
struct has_key_type {
  static constexpr const bool value = false;
};

template <typename T, typename... Args>
struct has_key_type<std::set<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::multiset<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::unordered_set<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::unordered_multiset<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::map<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::multimap<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::unordered_map<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_key_type<std::unordered_multimap<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
constexpr const bool has_key_type_v =
    has_key_type<std::decay_t<T>, Args...>::value;

// template <typename T>
// struct is_std_array_type {
//   static constexpr const bool value = std::is_same_v<T, std::array<typename
//   T::value_type, typename T::size>>;
// };

// template <typename T>
// struct is_std_array_type<std::array<T, N>> {
//   static constexpr const bool value = true;
// };

// template <typename T, typename... Args>
// constexpr const bool is_std_array_type_v = is_std_array_type<T, N>::value;

template <typename T, typename... Args>
struct has_value_type {
  static constexpr const bool value = false;
};

template <typename T, typename... Args>
struct has_value_type<std::vector<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::deque<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::forward_list<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::list<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::queue<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::stack<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::priority_queue<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::set<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::multiset<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::unordered_set<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_value_type<std::unordered_multiset<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
constexpr const bool has_value_type_v =
    has_value_type<std::decay_t<T>, Args...>::value;

template <typename T, typename... Args>
struct has_mapped_type {
  static constexpr const bool value = false;
};

template <typename T, typename... Args>
struct has_mapped_type<std::map<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_mapped_type<std::multimap<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_mapped_type<std::unordered_map<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct has_mapped_type<std::unordered_multimap<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
constexpr const bool has_mapped_type_v = has_mapped_type<T, Args...>::value;

template <typename T, typename... Args>
struct is_container_adapter_type {
  static constexpr const bool value = false;
};

template <typename T, typename... Args>
struct is_container_adapter_type<std::stack<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct is_container_adapter_type<std::queue<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
struct is_container_adapter_type<std::priority_queue<T, Args...>> {
  static constexpr const bool value = true;
};

template <typename T, typename... Args>
constexpr const bool is_container_adapter_type_v =
    is_container_adapter_type<std::decay_t<T>, Args...>::value;

template <typename ContainerType,
          typename KeyType,
          typename = std::enable_if_t<has_key_type_v<ContainerType>>>
bool has_key(const ContainerType& container, KeyType&& key) {
  return std::cend(container) != container.find(std::forward<KeyType>(key));
}

template <
    typename ContainerType,
    typename ValueType,
    typename = std::enable_if_t<!is_container_adapter_type_v<ContainerType> &&
                                (has_key_type_v<ContainerType> ||
                                 has_value_type_v<ContainerType> ||
                                 has_mapped_type_v<ContainerType>)>>
bool has_value(const ContainerType& container, ValueType&& value) {
  if constexpr (has_mapped_type_v<ContainerType>) {
    for (const auto& p : container) {
      if (p.second == value)
        return true;
    }

    return false;

  }

  else if constexpr (has_key_type_v<ContainerType>) {
    return std::cend(container) !=
           container.find(std::forward<ValueType>(value));

  } else if constexpr (has_value_type_v<ContainerType>) {
    if (std::is_sorted(std::cbegin(container), std::cend(container)))
      return std::binary_search(std::cbegin(container), std::cend(container),
                                std::forward<ValueType>(value));

    return std::find(std::cbegin(container), std::cend(container),
                     std::forward<ValueType>(value)) != std::cend(container);
  }
}

template <typename T, size_t N>
bool has_value(const std::array<T, N>& container, T&& value) {
  if (std::is_sorted(std::cbegin(container), std::cend(container)))
    return std::binary_search(std::cbegin(container), std::cend(container),
                              std::forward<T>(value));

  return std::cend(container) != std::find(std::cbegin(container),
                                           std::cend(container),
                                           std::forward<T>(value));
}

template <typename ContainerType,
          typename = std::enable_if_t<has_key_type_v<ContainerType> &&
                                      has_mapped_type_v<ContainerType>>>
bool has_kv_pair(const ContainerType& container,
                 const typename ContainerType::value_type& key_value_pair) {
  auto first_item_iter_pos{container.equal_range(key_value_pair.first)};
  if (std::cend(container) == first_item_iter_pos.first)
    return false;
  for (auto current{first_item_iter_pos.first};
       current != first_item_iter_pos.second; ++current) {
    if (key_value_pair.second == current->second)
      return true;
  }

  return false;
}

template <typename ForwardIterType, typename ItemType>
bool has_item(ForwardIterType first, ForwardIterType last, ItemType&& item) {
  if (std::is_sorted(first, last))
    return std::binary_search(first, last, std::forward<ItemType>(item));

  return last != std::find(first, last, std::forward<ItemType>(item));
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare(T src1, U src2) {
  if (!src1)
    return -1;
  if (!src2)
    return 1;

  const size_t str1_len{len(src1)};
  const size_t str2_len{len(src2)};

  size_t const number_of_characters_to_compare{std::min(str1_len, str2_len)};

  for (size_t i{}; i < number_of_characters_to_compare; i++, src1++, src2++) {
    if (*src1 != *src2)
      return static_cast<int>(*src1 - *src2);
  }

  return static_cast<int>(*src1 - *src2);
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
int str_compare(const StringType& src1, const StringType& src2) {
  using char_type = typename StringType::value_type;

  auto citr1{std::cbegin(src1)};
  auto citr2{std::cbegin(src2)};

  for (; citr1 != std::cend(src1) && citr2 != std::cend(src2);
       ++citr1, ++citr2) {
    if (*citr1 != *citr2)
      return static_cast<int>(*citr1 - *citr2);
  }

  const auto final_str1_ch{citr1 == std::cend(src1) ? static_cast<char_type>(0)
                                                    : *citr1};
  const auto final_str2_ch{citr2 == std::cend(src2) ? static_cast<char_type>(0)
                                                    : *citr2};

  return static_cast<int>(final_str1_ch - final_str2_ch);
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_n(T src1, U src2, size_t number_of_characters_to_compare) {
  if (!src1)
    return -1;
  if (!src2)
    return 1;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(src1_len, src2_len);
  }

  for (size_t i{}; i < number_of_characters_to_compare; src1++, src2++, i++) {
    if (*src1 != *src2)
      return static_cast<int>(*src1 - *src2);
  }

  return 0;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
int str_compare_n(const StringType& src1,
                  const StringType& src2,
                  size_t number_of_characters_to_compare) {
  const auto src1_len{src1.length()};
  const auto src2_len{src2.length()};

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(src1_len, src2_len);
  }

  for (size_t i{}; i < number_of_characters_to_compare; i++) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return 0;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_i(T src1, U src2, const std::locale& loc = std::locale{}) {
  if (!src1)
    return -1;
  if (!src2)
    return 1;

  using char_type = get_char_type_t<T>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  const size_t number_of_characters_to_compare{std::min(src1_len, src2_len)};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    size_t i{};

    for (; i < number_of_characters_to_compare; i++) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(src1[i]) - f.tolower(src2[i]));

  } else {
    size_t i{};

    for (; i < number_of_characters_to_compare; i++) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(src1[i]) - std::tolower(src2[i]));
  }
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
int str_compare_i(const StringType& src1,
                  const StringType& src2,
                  const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  auto citr1{std::cbegin(src1)};
  auto citr2{std::cbegin(src2)};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (; citr1 != std::cend(src1) && citr2 != std::cend(src2);
         ++citr1, ++citr2) {
      const auto ch1{f.tolower(*citr1)};

      const auto ch2{f.tolower(*citr2)};

      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(*citr1) - f.tolower(*citr2));

  } else {
    for (; citr1 != std::cend(src1) && citr2 != std::cend(src2);
         ++citr1, ++citr2) {
      const auto ch1{std::tolower(*citr1)};

      const auto ch2{std::tolower(*citr2)};

      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(*citr1) - std::tolower(*citr2));
  }
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T> ||
         is_non_const_char_pointer_type_v<T> ||
         is_const_char_pointer_type_v<
             T>)&&(is_non_const_char_array_type_v<U> ||
                   is_const_char_array_type_v<U> ||
                   is_non_const_char_pointer_type_v<U> ||
                   is_const_char_pointer_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_n_i(T src1,
                    U src2,
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const size_t str1_len{len(src1)};
  const size_t str2_len{len(src2)};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(str1_len, str2_len);
  }

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  } else {
    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  }

  return 0;
}

template <typename StringType,
          typename = std::enable_if_t<is_valid_string_type_v<StringType>>>
int str_compare_n_i(const StringType& src1,
                    const StringType& src2,
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  const size_t str1_len{src1.length()};
  const size_t str2_len{src2.length()};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(str1_len, str2_len);
  }

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  } else {
    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  }

  return 0;
}

enum class str_copy_behavior {
  disallow_partial_copy,
  allow_partial_copy,
  do_not_copy_return_required_dst_buffer_capacity_only
};

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        !std::is_const_v<T> &&
        (is_non_const_char_array_type_v<U> || is_const_char_array_type_v<U> ||
         is_non_const_char_pointer_type_v<U> ||
         is_const_char_pointer_type_v<U>)&&std::is_same_v<get_char_type_t<T>,
                                                          get_char_type_t<U>>>>
size_t str_copy(T (&dst)[ARRAY_SIZE],
                U src,
                const str_copy_behavior copy_options =
                    str_copy_behavior::disallow_partial_copy,
                size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < src_len + 1) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      const auto no_of_chars_to_copy{ARRAY_SIZE - 1};
      std::copy(src, src + no_of_chars_to_copy, dst);
      dst[no_of_chars_to_copy] = static_cast<char_type>('\0');
      return no_of_chars_to_copy;
    }
  }

  std::copy(src, src + src_len, dst);
  dst[src_len] = static_cast<char_type>('\0');
  return src_len;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_non_const_char_array_type_v<U> || is_const_char_array_type_v<U> ||
         is_non_const_char_pointer_type_v<U> ||
         is_const_char_pointer_type_v<U>)&&std::is_same_v<get_char_type_t<T>,
                                                          get_char_type_t<U>>>>
size_t str_copy(
    T dst,
    const size_t dst_capacity_in_number_of_characters,
    const U src,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < src_len + 1) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      const auto no_of_chars_to_copy{dst_capacity_in_number_of_characters - 1};

      std::copy(src, src + no_of_chars_to_copy, dst);

      dst[no_of_chars_to_copy] = static_cast<char_type>('\0');

      return no_of_chars_to_copy;
    }
  }

  std::copy(src, src + src_len, dst);

  dst[src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              ((is_valid_string_type_v<U> && std::is_same_v<T, U>) ||
               ((is_non_const_char_pointer_type_v<U> ||
                 is_const_char_pointer_type_v<U>)&&std::
                    is_same_v<typename T::value_type, get_char_type_t<U>>))>>
size_t str_copy(T& dst, const U& src) {
  if constexpr (is_non_const_char_pointer_type_v<U> ||
                is_const_char_pointer_type_v<U>) {
    if (nullptr == src)
      return 0u;
  }

  dst.assign(src);
  return len(src);
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              std::is_same_v<typename T::value_type, get_char_type_t<U>>>>
size_t str_copy(T& dst, U (&src)[ARRAY_SIZE]) {
  dst.assign(src);
  return ARRAY_SIZE - 1;
}

template <size_t ARRAY_SIZE>
size_t str_copy_n(char (&dst)[ARRAY_SIZE],
                  const char* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options =
                      str_copy_behavior::disallow_partial_copy,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);

  auto const noctc{std::min(number_of_characters_to_copy, src_len)};

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = ARRAY_SIZE - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = '\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = '\0';

  return noctc;
}

template <size_t ARRAY_SIZE>
size_t str_copy_n(wchar_t (&dst)[ARRAY_SIZE],
                  const wchar_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options =
                      str_copy_behavior::disallow_partial_copy,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);

  auto const noctc{std::min(number_of_characters_to_copy, src_len)};

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = ARRAY_SIZE - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = L'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = L'\0';

  return noctc;
}

template <size_t ARRAY_SIZE>
size_t str_copy_n(char16_t (&dst)[ARRAY_SIZE],
                  const char16_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options =
                      str_copy_behavior::disallow_partial_copy,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);

  auto const noctc{std::min(number_of_characters_to_copy, src_len)};

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = ARRAY_SIZE - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = u'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = u'\0';

  return noctc;
}

template <size_t ARRAY_SIZE>
size_t str_copy_n(char32_t (&dst)[ARRAY_SIZE],
                  const char32_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options =
                      str_copy_behavior::disallow_partial_copy,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);

  const auto noctc{std::min(number_of_characters_to_copy, src_len)};

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = ARRAY_SIZE - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = U'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = U'\0';

  return noctc;
}

size_t str_copy_n(
    char* dst,
    size_t dst_capacity_in_number_of_characters,
    const char* src,
    size_t number_of_characters_to_copy,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr);

size_t str_copy_n(
    wchar_t* dst,
    size_t dst_capacity_in_number_of_characters,
    const wchar_t* src,
    size_t number_of_characters_to_copy,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr);

size_t str_copy_n(
    char16_t* dst,
    size_t dst_capacity_in_number_of_characters,
    const char16_t* src,
    size_t number_of_characters_to_copy,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr);

size_t str_copy_n(
    char32_t* dst,
    size_t dst_capacity_in_number_of_characters,
    const char32_t* src,
    size_t number_of_characters_to_copy,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_copy_n(const StringType& dst,
                      const StringType& src,
                      const size_t number_of_characters_to_copy) {
  return src.substr(0, number_of_characters_to_copy);
}

template <typename StringType>
void str_copy_n(StringType& dst,
                const StringType& src,
                const size_t number_of_characters_to_copy) {
  dst.assign(src.substr(0, number_of_characters_to_copy));
}

enum class str_append_behavior {
  disallow_partial_append,
  allow_partial_append,
  do_not_append_return_required_dst_buffer_capacity_only
};

template <size_t ARRAY_SIZE>
size_t str_append(char (&dst)[ARRAY_SIZE],
                  const char* src,
                  const str_append_behavior append_options =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[ARRAY_SIZE - 1] = '\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = '\0';

  return src_len;
}

template <size_t ARRAY_SIZE>
size_t str_append(wchar_t (&dst)[ARRAY_SIZE],
                  const wchar_t* src,
                  const str_append_behavior append_options =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[ARRAY_SIZE - 1] = L'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = L'\0';

  return src_len;
}

template <size_t ARRAY_SIZE>
size_t str_append(char16_t (&dst)[ARRAY_SIZE],
                  const char16_t* src,
                  const str_append_behavior append_options =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[ARRAY_SIZE - 1] = u'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = u'\0';

  return src_len;
}

template <size_t ARRAY_SIZE>
size_t str_append(char32_t (&dst)[ARRAY_SIZE],
                  const char32_t* src,
                  const str_append_behavior append_options =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[ARRAY_SIZE - 1] = U'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = U'\0';

  return src_len;
}

size_t str_append(char* dst,
                  size_t dst_capacity_in_number_of_characters,
                  const char* src,
                  str_append_behavior append_behavior =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr);

size_t str_append(wchar_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  const wchar_t* src,
                  str_append_behavior append_behavior =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr);

size_t str_append(char16_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  const char16_t* src,
                  str_append_behavior append_behavior =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr);

size_t str_append(char32_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  const char32_t* src,
                  str_append_behavior append_behavior =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_append(const StringType& dst, const StringType& src) {
  return StringType{dst + src};
}

template <typename StringType>
void str_append(StringType& dst, const StringType& src) {
  dst += src;
}

template <size_t ARRAY_SIZE>
size_t str_append_n(char (&dst)[ARRAY_SIZE],
                    const char* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  const auto str_len{len(src)};

  const auto dst_len{len(dst)};

  auto no_of_chars_to_append{std::min(str_len, number_of_characters_to_append)};

  const size_t ret_val{dst_len + no_of_chars_to_append + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1)) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      return 0u;
    }

    if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[ARRAY_SIZE - 1] = '\0';

      return no_of_chars_to_append;
    }
  }

  copy(src, src + no_of_chars_to_append, dst + dst_len);

  dst[dst_len + no_of_chars_to_append] = '\0';

  return no_of_chars_to_append;
}

template <size_t ARRAY_SIZE>
size_t str_append_n(wchar_t (&dst)[ARRAY_SIZE],
                    const wchar_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  const auto str_len{len(src)};

  const auto dst_len{len(dst)};

  auto no_of_chars_to_append{std::min(str_len, number_of_characters_to_append)};

  const size_t ret_val{dst_len + no_of_chars_to_append + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1)) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      return 0u;
    }

    if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[ARRAY_SIZE - 1] = L'\0';

      return no_of_chars_to_append;
    }
  }

  copy(src, src + no_of_chars_to_append, dst + dst_len);

  dst[dst_len + no_of_chars_to_append] = L'\0';

  return no_of_chars_to_append;
}

template <size_t ARRAY_SIZE>
size_t str_append_n(char16_t (&dst)[ARRAY_SIZE],
                    const char16_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  const auto str_len{len(src)};

  const auto dst_len{len(dst)};

  auto no_of_chars_to_append{std::min(str_len, number_of_characters_to_append)};

  const size_t ret_val{dst_len + no_of_chars_to_append + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1)) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      return 0u;
    }

    if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[ARRAY_SIZE - 1] = u'\0';

      return no_of_chars_to_append;
    }
  }

  copy(src, src + no_of_chars_to_append, dst + dst_len);

  dst[dst_len + no_of_chars_to_append] = u'\0';

  return no_of_chars_to_append;
}

template <size_t ARRAY_SIZE>
size_t str_append_n(char32_t (&dst)[ARRAY_SIZE],
                    const char32_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  const auto str_len{len(src)};

  const auto dst_len{len(dst)};

  auto no_of_chars_to_append{std::min(str_len, number_of_characters_to_append)};

  const size_t ret_val{dst_len + no_of_chars_to_append + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1)) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return 0u;

    if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append = ARRAY_SIZE - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[ARRAY_SIZE - 1] = U'\0';

      return no_of_chars_to_append;
    }
  }

  copy(src, src + no_of_chars_to_append, dst + dst_len);

  dst[dst_len + no_of_chars_to_append] = U'\0';

  return no_of_chars_to_append;
}

size_t str_append_n(char* dst,
                    size_t dst_capacity_in_number_of_characters,
                    const char* src,
                    size_t number_of_characters_to_append,
                    str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr);

size_t str_append_n(wchar_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    const wchar_t* src,
                    size_t number_of_characters_to_append,
                    str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr);

size_t str_append_n(char16_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    const char16_t* src,
                    size_t number_of_characters_to_append,
                    str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr);

size_t str_append_n(char32_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    const char32_t* src,
                    size_t number_of_characters_to_append,
                    str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_append_n(const StringType& dst,
                        const StringType& src,
                        const size_t number_of_characters_to_append) {
  return StringType{dst += src.substr(0, number_of_characters_to_append)};
}

template <typename StringType>
void str_append_n(StringType& dst,
                  const StringType& src,
                  const size_t number_of_characters_to_append) {
  dst += src.substr(0, number_of_characters_to_append);
}

enum class str_prepend_behaviour {
  disallow_partial_prepend,
  allow_partial_prepend,
  do_not_prepend_return_required_dst_buffer_capacity_only
};

template <size_t ARRAY_SIZE>
size_t str_prepend(char (&dst)[ARRAY_SIZE],
                   const char* src,
                   const str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      ret_val = 0u;
    } else {
      /*for (auto start = 0u; start != src_len; start++)
{




                          dst[dst + dst_len +
src_len - 1 - start] = dst[dst + dst_len - 1 - start];








}*/

      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[ARRAY_SIZE - 1] = '\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend(wchar_t (&dst)[ARRAY_SIZE],
                   const wchar_t* src,
                   const str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[ARRAY_SIZE - 1] = '\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend(char16_t (&dst)[ARRAY_SIZE],
                   const char16_t* src,
                   const str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[ARRAY_SIZE - 1] = '\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend(char32_t (&dst)[ARRAY_SIZE],
                   const char32_t* src,
                   const str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = U'\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < (dst_len + src_len + 1)) {
      auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[ARRAY_SIZE - 1] = U'\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = U'\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

size_t str_prepend(char* dst,
                   size_t dst_capacity_in_number_of_characters,
                   const char* src,
                   str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr);

size_t str_prepend(wchar_t* dst,
                   size_t dst_capacity_in_number_of_characters,
                   const wchar_t* src,
                   str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr);

size_t str_prepend(char16_t* dst,
                   size_t dst_capacity_in_number_of_characters,
                   const char16_t* src,
                   str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr);

size_t str_prepend(char32_t* dst,
                   size_t dst_capacity_in_number_of_characters,
                   const char32_t* src,
                   str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_prepend(const StringType& dst, const StringType& src) {
  return StringType{src + dst};
}

template <typename StringType>
void str_prepend(StringType& dst, const StringType& src) {
  dst.insert(0, src);
}

template <size_t ARRAY_SIZE>
size_t str_prepend_n(char (&dst)[ARRAY_SIZE],
                     const char* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocp = number_of_characters_to_prepend > src_len
                  ? src_len
                  : number_of_characters_to_prepend;

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocp + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = '\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      nocp = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = '\0';

      ret_val = nocp;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = '\0';

      ret_val = nocp;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocp + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend_n(wchar_t (&dst)[ARRAY_SIZE],
                     const wchar_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocp = number_of_characters_to_prepend > src_len
                  ? src_len
                  : number_of_characters_to_prepend;

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocp + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = L'\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      nocp = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = L'\0';

      ret_val = nocp;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = L'\0';

      ret_val = nocp;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocp + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend_n(char16_t (&dst)[ARRAY_SIZE],
                     const char16_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocp = number_of_characters_to_prepend > src_len
                  ? src_len
                  : number_of_characters_to_prepend;

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocp + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = u'\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      nocp = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = u'\0';

      ret_val = nocp;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = u'\0';

      ret_val = nocp;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocp + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_prepend_n(char32_t (&dst)[ARRAY_SIZE],
                     const char32_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocp = number_of_characters_to_prepend > src_len
                  ? src_len
                  : number_of_characters_to_prepend;

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocp + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = U'\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (ARRAY_SIZE < dst_len + nocp + 1) {
      nocp = ARRAY_SIZE - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = U'\0';

      ret_val = nocp;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = U'\0';

      ret_val = nocp;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocp + 1;

  return ret_val;
}

size_t str_prepend_n(char* dst,
                     size_t dst_capacity_in_number_of_characters,
                     const char* src,
                     size_t number_of_characters_to_prepend,
                     str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr);

size_t str_prepend_n(wchar_t* dst,
                     size_t dst_capacity_in_number_of_characters,
                     const wchar_t* src,
                     size_t number_of_characters_to_prepend,
                     str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr);

size_t str_prepend_n(char16_t* dst,
                     size_t dst_capacity_in_number_of_characters,
                     const char16_t* src,
                     size_t number_of_characters_to_prepend,
                     str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr);

size_t str_prepend_n(char32_t* dst,
                     size_t dst_capacity_in_number_of_characters,
                     const char32_t* src,
                     size_t number_of_characters_to_prepend,
                     str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_prepend_n(const StringType& dst,
                         const StringType& src,
                         size_t number_of_characters_to_prepend) {
  number_of_characters_to_prepend =
      number_of_characters_to_prepend <= src.size()
          ? number_of_characters_to_prepend
          : src.size();

  StringType final_str{src.substr(0, number_of_characters_to_prepend) + dst};

  return final_str;
}

template <typename StringType>
void str_prepend_n(StringType& dst,
                   const StringType& src,
                   size_t number_of_characters_to_prepend) {
  number_of_characters_to_prepend =
      number_of_characters_to_prepend <= src.size()
          ? number_of_characters_to_prepend
          : src.size();

  dst.insert(0, src.substr(0, number_of_characters_to_prepend));
}

enum class str_insert_behaviour {
  disallow_partial_insert,
  allow_partial_insert,
  do_not_insert_return_required_dst_buffer_capacity_only
};

template <size_t ARRAY_SIZE>
size_t str_insert(char (&dst)[ARRAY_SIZE],
                  const size_t position_index_in_dst,
                  const char* src,
                  const str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + src_len + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    const auto nocti{std::min(ARRAY_SIZE - position_index_in_dst - 1, src_len)};

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = '\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert(wchar_t (&dst)[ARRAY_SIZE],
                  const size_t position_index_in_dst,
                  const wchar_t* src,
                  const str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + src_len + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    const auto nocti{std::min(ARRAY_SIZE - position_index_in_dst - 1, src_len)};

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = L'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert(char16_t (&dst)[ARRAY_SIZE],
                  const size_t position_index_in_dst,
                  const char16_t* src,
                  const str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + src_len + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    const auto nocti{std::min(ARRAY_SIZE - position_index_in_dst - 1, src_len)};

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = u'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert(char32_t (&dst)[ARRAY_SIZE],
                  const size_t position_index_in_dst,
                  const char32_t* src,
                  const str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + src_len + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    const auto nocti{std::min(ARRAY_SIZE - position_index_in_dst - 1, src_len)};

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = U'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

size_t str_insert(char* dst,
                  size_t dst_capacity_in_number_of_characters,
                  size_t position_index_in_dst,
                  const char* src,
                  str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr);

size_t str_insert(wchar_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  size_t position_index_in_dst,
                  const wchar_t* src,
                  str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr);

size_t str_insert(char16_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  size_t position_index_in_dst,
                  const char16_t* src,
                  str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr);

size_t str_insert(char32_t* dst,
                  size_t dst_capacity_in_number_of_characters,
                  size_t position_index_in_dst,
                  const char32_t* src,
                  str_insert_behaviour insert_options =
                      str_insert_behaviour::disallow_partial_insert,
                  size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_insert(const StringType& dst,
                      const size_t position_index_in_dst,
                      const StringType& src) {
  auto const dst_len{dst.size()};

  if (!dst_len && (0u == position_index_in_dst))
    return StringType{src};

  StringType final_str{dst};

  final_str.insert(position_index_in_dst, src);

  return final_str;
}

template <typename StringType>
void str_insert(StringType& dst,
                const size_t position_index_in_dst,
                const StringType& src) {
  auto const dst_len{dst.size()};

  if (!dst_len && (0u == position_index_in_dst))
    dst = src;

  dst.insert(position_index_in_dst, src);
}

template <size_t ARRAY_SIZE>
size_t str_insert_n(char (&dst)[ARRAY_SIZE],
                    const size_t position_index_in_dst,
                    const char* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocti{std::min(number_of_characters_to_insert, src_len)};

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + nocti + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocti + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti = std::min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = '\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocti + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert_n(wchar_t (&dst)[ARRAY_SIZE],
                    const size_t position_index_in_dst,
                    const wchar_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocti{std::min(number_of_characters_to_insert, src_len)};

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + nocti + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocti + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti = std::min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = L'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocti + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert_n(char16_t (&dst)[ARRAY_SIZE],
                    const size_t position_index_in_dst,
                    const char16_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocti{std::min(number_of_characters_to_insert, src_len)};

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + nocti + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocti + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti = std::min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = u'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocti + 1;

  return ret_val;
}

template <size_t ARRAY_SIZE>
size_t str_insert_n(char32_t (&dst)[ARRAY_SIZE],
                    const size_t position_index_in_dst,
                    const char32_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

  auto nocti = std::min(number_of_characters_to_insert, src_len);

  if (position_index_in_dst > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + nocti + 1;

    return 0u;
  }

  size_t ret_val;

  if (insert_options ==
      str_insert_behaviour::
          do_not_insert_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + nocti + 1;
  } else if ((insert_options ==
              str_insert_behaviour::disallow_partial_insert) &&
             (ARRAY_SIZE < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti = std::min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

    copy_backward(dst + position_index_in_dst, dst + dst_len,
                  dst + dst_len + nocti);

    copy(src, src + nocti, dst + position_index_in_dst);

    dst[dst_len + nocti] = U'\0';

    ret_val = nocti;
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + nocti + 1;

  return ret_val;
}

size_t str_insert_n(char* dst,
                    size_t dst_capacity_in_number_of_characters,
                    size_t position_index_in_dst,
                    const char* src,
                    size_t number_of_characters_to_insert,
                    str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr);

size_t str_insert_n(wchar_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    size_t position_index_in_dst,
                    const wchar_t* src,
                    size_t number_of_characters_to_insert,
                    str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr);

size_t str_insert_n(char16_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    size_t position_index_in_dst,
                    const char16_t* src,
                    size_t number_of_characters_to_insert,
                    str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr);

size_t str_insert_n(char32_t* dst,
                    size_t dst_capacity_in_number_of_characters,
                    size_t position_index_in_dst,
                    const char32_t* src,
                    size_t number_of_characters_to_insert,
                    str_insert_behaviour insert_options =
                        str_insert_behaviour::disallow_partial_insert,
                    size_t* required_dst_capacity = nullptr);

template <typename StringType>
StringType str_insert_n(const StringType& dst,
                        const size_t position_index_in_dst,
                        const StringType& src,
                        const size_t number_of_characters_to_insert) {
  const auto dst_length{dst.size()};

  const auto src_length{src.size()};

  const auto no_of_chars = min(number_of_characters_to_insert, src_length);

  if (!dst_length && (0u == position_index_in_dst))
    return StringType{src.substr(0, no_of_chars)};

  StringType final_str{dst};

  final_str.insert(position_index_in_dst, src.substr(0, no_of_chars));

  return final_str;
}

template <typename StringType>
void str_insert_n(StringType& dst,
                  const size_t position_index_in_dst,
                  const StringType& src,
                  const size_t number_of_characters_to_insert) {
  const auto dst_length{dst.size()};

  const auto src_length{src.size()};

  const auto no_of_chars = min(number_of_characters_to_insert, src_length);

  if (!dst_length && (0u == position_index_in_dst))
    dst = src.substr(0, no_of_chars);

  dst.insert(position_index_in_dst, src.substr(0, no_of_chars));
}

// enum class str_replace_behavior { no_partial_replace,
// allow_partial_place,
// do_not_replace_return_required_dst_capacity_only };

template <
    typename T,
    typename = std::enable_if_t<
        std::is_array_v<T> &&
        (std::is_same_v<std::remove_extent_t<std::remove_cv_t<T>>, char> ||
         std::is_same_v<std::remove_extent_t<std::remove_cv_t<T>>, wchar_t> ||
         std::is_same_v<std::remove_extent_t<std::remove_cv_t<T>>, char16_t> ||
         std::is_same_v<std::remove_extent_t<std::remove_cv_t<T>>, char32_t>)>>
size_t str_replace_first(T dst,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity = nullptr) {
  // using char_type = std::remove_extent_t<std::remove_cv_t<T>>;
  const size_t ARRAY_SIZE{std::size(dst)};
  auto const dst_len{len(dst)};
  auto const needle_len{len(needle)};
  auto const replace_len{len(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == std::string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((ARRAY_SIZE - 1) < rdc) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if (needle_len == replace_len) {
    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }

  if (needle_len < replace_len) {
    auto const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in
    // the upper part of dst ( characters with positions >= dst +
    // start_pos + needle_len characters ) have to be moved 'noctm' (8)
    // character positions toward the end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len + noctm);

    dst[dst_len + noctm] = '\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in
  // the upper part of dst ( characters with positions >= dst +
  // start_pos + needle_len characters ) have to be moved 'noctm' (8)
  // character positions toward dst
  // + start_pos + replace_len.

  for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = '\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

template <size_t ARRAY_SIZE>
size_t str_replace_first(wchar_t (&dst)[ARRAY_SIZE],
                         const wchar_t* needle,
                         const wchar_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{len(dst)};
  auto const needle_len{len(needle)};
  auto const replace_len{len(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == std::wstring::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((ARRAY_SIZE - 1) < rdc) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if (needle_len == replace_len) {
    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }

  if (needle_len < replace_len) {
    auto const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in
    // the upper part of dst ( characters with positions >= dst +
    // start_pos + needle_len characters ) have to be moved 'noctm' (8)
    // character positions toward the end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len + noctm);

    dst[dst_len + noctm] = L'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in
  // the upper part of dst ( characters with positions >= dst +
  // start_pos + needle_len characters ) have to be moved 'noctm' (8)
  // character positions toward dst
  // + start_pos + replace_len.

  for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = L'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

template <size_t ARRAY_SIZE>
size_t str_replace_first(char16_t (&dst)[ARRAY_SIZE],
                         const char16_t* needle,
                         const char16_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{len(dst)};
  auto const needle_len{len(needle)};
  auto const replace_len{len(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == std::u16string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((ARRAY_SIZE - 1) < rdc) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if (needle_len == replace_len) {
    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }

  if (needle_len < replace_len) {
    auto const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in
    // the upper part of dst ( characters with positions >= dst +
    // start_pos + needle_len characters ) have to be moved 'noctm' (8)
    // character positions toward the end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len + noctm);

    dst[dst_len + noctm] = u'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in
  // the upper part of dst ( characters with positions >= dst +
  // start_pos + needle_len characters ) have to be moved 'noctm' (8)
  // character positions toward dst
  // + start_pos + replace_len.

  for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = u'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

template <size_t ARRAY_SIZE>
size_t str_replace_first(char32_t (&dst)[ARRAY_SIZE],
                         const char32_t* needle,
                         const char32_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{len(dst)};
  auto const needle_len{len(needle)};
  auto const replace_len{len(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == std::u32string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((ARRAY_SIZE - 1) < rdc) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if (needle_len == replace_len) {
    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }

  if (needle_len < replace_len) {
    auto const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in
    // the upper part of dst ( characters with positions >= dst +
    // start_pos + needle_len characters ) have to be moved 'noctm' (8)
    // character positions toward the end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len + noctm);

    dst[dst_len + noctm] = U'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in
  // the upper part of dst ( characters with positions >= dst +
  // start_pos + needle_len characters ) have to be moved 'noctm' (8)
  // character positions toward dst
  // + start_pos + replace_len.

  for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = U'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

size_t str_replace_first(char* dst,
                         size_t dst_capacity_in_number_of_characters,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity = nullptr);

size_t str_replace_first(wchar_t* dst,
                         size_t dst_capacity_in_number_of_characters,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity = nullptr);

size_t str_replace_first(char16_t* dst,
                         size_t dst_capacity_in_number_of_characters,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity = nullptr);

size_t str_replace_first(char32_t* dst,
                         size_t dst_capacity_in_number_of_characters,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity = nullptr);

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_replace_nth(CharacterPointerType src,
                                     const CharacterPointerType needle,
                                     const size_t nth_index = 1) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_replace_last(CharacterPointerType src,
                                      const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_replace_all(CharacterPointerType src,
                                     const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_replace_first_n(
    CharacterPointerType src,
    const CharacterPointerType needle,
    const size_t number_of_copies_to_replace = 1) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_replace_last_n(
    CharacterPointerType src,
    const CharacterPointerType needle,
    const size_t number_of_copies_to_replace = 1) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_first(CharacterPointerType src,
                                     const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_nth(CharacterPointerType src,
                                   const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_last(CharacterPointerType src,
                                    const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_all(CharacterPointerType src,
                                   const CharacterPointerType needle) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_first_n(CharacterPointerType src,
                                       const CharacterPointerType needle,
                                       const size_t number_of_copies_to_erase) {
  return nullptr;
}

template <typename CharacterPointerType,
          typename = std::enable_if_t<
              std::is_array_v<CharacterPointerType> ||
              std::is_same_v<CharacterPointerType, char*> ||
              std::is_same_v<CharacterPointerType, wchar_t*> ||
              std::is_same_v<CharacterPointerType, char16_t*> ||
              std::is_same_v<CharacterPointerType, char32_t*>>>
CharacterPointerType str_erase_last_n(CharacterPointerType src,
                                      const CharacterPointerType needle,
                                      const size_t number_of_copies_to_erase) {
  return nullptr;
}

const char* strstr(const char* src, const char* needle);

const wchar_t* strstr(const wchar_t* src, const wchar_t* needle);

const char16_t* strstr(const char16_t* src, const char16_t* needle);

const char32_t* strstr(const char32_t* src, const char32_t* needle);

template <typename StringType>
size_t strstr(const StringType& src, const StringType& needle) {
  return src.find(needle);
}

char* strstr(char* src, const char* needle);

wchar_t* strstr(wchar_t* src, const wchar_t* needle);

char16_t* strstr(char16_t* src, const char16_t* needle);

char32_t* strstr(char32_t* src, const char32_t* needle);

template <typename StringType>
size_t strstr(StringType& src, const StringType& needle) {
  return src.find(needle);
}

const char* strstri(const char* src,
                    const char* needle,
                    const std::locale& loc = std::locale{});

const wchar_t* strstri(const wchar_t* src,
                       const wchar_t* needle,
                       const std::locale& loc = std::locale{});

const char16_t* strstri(const char16_t* src,
                        const char16_t* needle,
                        const std::locale& loc = std::locale{});

const char32_t* strstri(const char32_t* src,
                        const char32_t* needle,
                        const std::locale& loc = std::locale{});

template <typename StringType>
size_t strstri(const StringType& src,
               const StringType& needle,
               const std::locale& loc = std::locale{}) {
  StringType src_lc{src};
  StringType needle_lc{needle};

  transform(begin(src), end(src), begin(src_lc),
            [&](const char ch) { return tolower(ch, loc); });

  transform(begin(needle), end(needle), begin(needle_lc),
            [&](const char ch) { return tolower(ch, loc); });

  return src_lc.find(needle_lc);
}

char* strstri(char* src,
              const char* needle,
              const std::locale& loc = std::locale{});

wchar_t* strstri(wchar_t* src,
                 const wchar_t* needle,
                 const std::locale& loc = std::locale{});

char16_t* strstri(char16_t* src,
                  const char16_t* needle,
                  const std::locale& loc = std::locale{});

char32_t* strstri(char32_t* src,
                  const char32_t* needle,
                  const std::locale& loc = std::locale{});

template <typename StringType>
size_t strstri(StringType& src,
               const StringType& needle,
               const std::locale& loc = std::locale{}) {
  StringType src_lc{src};
  StringType needle_lc{needle};

  transform(begin(src), end(src), begin(src_lc),
            [&](const char ch) { return tolower(ch, loc); });

  transform(begin(needle), end(needle), begin(needle_lc),
            [&](const char ch) { return tolower(ch, loc); });

  return src_lc.find(needle_lc);
}

template <typename StringType>
StringType to_lower_case(const StringType& str,
                         const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  StringType final_str{str};

  transform(begin(str), end(str), begin(final_str),
            [&loc](const char_type ch) { return tolower(ch, loc); });

  return final_str;
}

template <typename StringType>
void to_lower_case_in_place(StringType& str,
                            const std::locale& loc = std::locale{}) {
  for (auto& ch : str)
    ch = tolower(ch, loc);
}

template <typename StringType>
StringType to_upper_case(const StringType& str,
                         const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  StringType final_str{str};

  transform(begin(str), end(str), begin(final_str),
            [&loc](const char_type ch) { return toupper(ch, loc); });

  return final_str;
}

template <typename StringType>
void to_upper_case_in_place(StringType& str,
                            const std::locale& loc = std::locale{}) {
  for (auto& ch : str)
    ch = toupper(ch, loc);
}

template <typename StringType>
StringType to_title_case(const StringType& str,
                         const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  StringType final_str{str};

  auto is_new_sentence{true};

  for (auto& ch : final_str) {
    if (static_cast<char_type>('\n') == ch) {
      is_new_sentence = true;
      continue;
    }

    if (is_new_sentence && !is_ws_char(ch))  // if (is_new_sentence &&
                                             // is_alphanum_char(ch)) { ... }
    {
      ch = toupper(ch, loc);
      is_new_sentence = false;
    }
  }

  return final_str;
}

template <typename StringType>
void to_title_case_in_place(StringType& str,
                            const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;

  auto is_new_sentence{true};

  for (auto& ch : str) {
    if (static_cast<char_type>('\n') == ch) {
      is_new_sentence = true;
      continue;
    }

    if (is_new_sentence && !is_ws_char(ch))  // if (is_new_sentence &&
                                             // is_alphanum_char(ch)) { ... }
    {
      ch = toupper(ch, loc);
      is_new_sentence = false;
    }
  }
}

// global conversion functions from the appropriate signed/unsigned
// integral as well as floating point types to std::u16string and
// std::u32string newer STL C++11 string types

enum class number_base { decimal, hexadecimal, octal, binary };

enum class add_number_base_sign {
  no_number_base_sign,
  prepend_in_lower_case_format,
  prepend_in_upper_case_format,
  append_in_lower_case_format,
  append_in_upper_case_format
};

std::u16string to_u16string(
    short number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    unsigned short number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    int number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    unsigned int number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    unsigned long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    long long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(
    unsigned long long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u16string to_u16string(float number,
                            int round_to_specified_number_of_digits = 6);

std::u16string to_u16string(double number,
                            int round_to_specified_number_of_digits = 6);

std::u16string to_u16string(long double number,
                            int round_to_specified_number_of_digits = 6);

std::u32string to_u32string(
    short number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    unsigned short number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    int number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    unsigned int number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    unsigned long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    long long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(
    unsigned long long number,
    number_base convert_to_number_base = number_base::decimal,
    add_number_base_sign add_number_base_sign =
        add_number_base_sign::no_number_base_sign);

std::u32string to_u32string(float number,
                            int round_to_specified_number_of_digits = 6);

std::u32string to_u32string(double number,
                            int round_to_specified_number_of_digits = 6);

std::u32string to_u32string(long double number,
                            int round_to_specified_number_of_digits = 6);

int stoi(const std::u16string& str,
         size_t* pos = nullptr,
         int base = 10,
         bool ignore_leading_white_space_characters = true);

long stol(const std::u16string& str,
          size_t* pos = nullptr,
          int base = 10,
          bool ignore_leading_white_space_characters = true);

unsigned long stoul(const std::u16string& str,
                    size_t* pos = nullptr,
                    int base = 10,
                    bool ignore_leading_white_space_characters = true);

long long stoll(const std::u16string& str,
                size_t* pos = nullptr,
                int base = 10,
                bool ignore_leading_white_space_characters = true);

unsigned long long stoull(const std::u16string& str,
                          size_t* pos = nullptr,
                          int base = 10,
                          bool ignore_leading_white_space_characters = true);

float stof(const std::u16string& str,
           size_t* pos = nullptr,
           int base = 10,
           bool ignore_leading_white_space_characters = true);

double stod(const std::u16string& str,
            size_t* pos = nullptr,
            int base = 10,
            bool ignore_leading_white_space_characters = true);

long double stold(const std::u16string& str,
                  size_t* pos = nullptr,
                  int base = 10,
                  bool ignore_leading_white_space_characters = true);

int stoi(const std::u32string& str,
         size_t* pos = nullptr,
         int base = 10,
         bool ignore_leading_white_space_characters = true);

long stol(const std::u32string& str,
          size_t* pos = nullptr,
          int base = 10,
          bool ignore_leading_white_space_characters = true);

unsigned long stoul(const std::u32string& str,
                    size_t* pos = nullptr,
                    int base = 10,
                    bool ignore_leading_white_space_characters = true);

long long stoll(const std::u32string& str,
                size_t* pos = nullptr,
                int base = 10,
                bool ignore_leading_white_space_characters = true);

unsigned long long stoull(const std::u32string& str,
                          size_t* pos = nullptr,
                          int base = 10,
                          bool ignore_leading_white_space_characters = true);

float stof(const std::u32string& str,
           size_t* pos = nullptr,
           int base = 10,
           bool ignore_leading_white_space_characters = true);

double stod(const std::u32string& str,
            size_t* pos = nullptr,
            int base = 10,
            bool ignore_leading_white_space_characters = true);

long double stold(const std::u32string& str,
                  size_t* pos = nullptr,
                  int base = 10,
                  bool ignore_leading_white_space_characters = true);

std::vector<std::string> split(const char* source,
                               char needle_char,
                               int max_count = -1);

std::vector<std::wstring> split(const wchar_t* source,
                                wchar_t needle_char,
                                int max_count = -1);

std::vector<std::u16string> split(const char16_t* source,
                                  char16_t needle_char,
                                  int max_count = -1);

std::vector<std::u32string> split(const char32_t* source,
                                  char32_t needle_char,
                                  int max_count = -1);

std::vector<std::string> split(const char* source,
                               const char* needle,
                               int max_count = -1);

std::vector<std::wstring> split(const wchar_t* source,
                                const wchar_t* needle,
                                int max_count = -1);

std::vector<std::u16string> split(const char16_t* source,
                                  const char16_t* needle,
                                  int max_count = -1);

std::vector<std::u32string> split(const char32_t* source,
                                  const char32_t* needle,
                                  int max_count = -1);

template <typename StringType>
std::vector<StringType> split(const StringType& source,
                              const typename StringType::value_type needle_char,
                              size_t const max_count = StringType::npos) {
  std::vector<StringType> parts{};

  StringType needle_st(1, needle_char);

  const size_t source_len{source.length()};
  const size_t needle_len{needle_st.length()};

  // if ((0u == source_len) || (0u == needle_len) || (needle_len >=
  // source_len)) return parts;
  if ((0u == source_len) || (0u == needle_len))
    return parts;

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (StringType::npos == current)
      break;

    number_of_parts++;

    if ((StringType::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (StringType::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((StringType::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

template <typename StringType>
std::vector<StringType> split(const StringType& source,
                              typename StringType::const_pointer needle,
                              size_t const max_count = StringType::npos) {
  std::vector<StringType> parts{};

  StringType needle_st{needle};

  const size_t source_len{source.length()};
  const size_t needle_len{needle_st.length()};

  // if ((0u == source_len) || (0u == needle_len) || (needle_len >=
  // source_len)) return parts;
  if ((0u == source_len) || (0u == needle_len))
    return parts;

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (StringType::npos == current)
      break;

    number_of_parts++;

    if ((StringType::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (StringType::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((StringType::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

template <typename StringType>
std::vector<StringType> split(const StringType& source,
                              const StringType& needle,
                              size_t const max_count = StringType::npos) {
  std::vector<StringType> parts{};

  const size_t source_len{source.length()};
  const size_t needle_len{needle.length()};

  // if ((0u == source_len) || (0u == needle_len) || (needle_len >=
  // source_len)) return parts;
  if ((0u == source_len) || (0u == needle_len))
    return parts;

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle, prev)};

    if (StringType::npos == current)
      break;

    number_of_parts++;

    if ((StringType::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (StringType::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((StringType::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

template <typename T>
std::string join_helper(const std::string&, T&& arg) {
  std::ostringstream oss{};

  oss << arg;

  return oss.str();
}

template <typename T, typename... Args>
std::string join_helper(const std::string& needle, T&& arg, Args&&... args) {
  std::ostringstream oss{};

  oss << arg << needle << join_helper(needle, args...);

  return oss.str();
}

template <typename... Args>
std::string join(const std::string& needle, Args&&... args) {
  std::string result{join_helper(needle, std::forward<Args>(args)...)};

  return result;
}

template <typename T>
std::wstring join_helper(const std::wstring&, T&& arg) {
  std::wostringstream woss{};

  woss << arg;

  return woss.str();
}

template <typename T, typename... _Args>
std::wstring join_helper(const std::wstring& needle, T&& arg, _Args&&... args) {
  std::wostringstream woss{};

  woss << arg << needle << join_helper(needle, args...);

  return woss.str();
}

template <typename... _Args>
std::wstring join(const std::wstring& needle, _Args&&... args) {
  std::wstring result{join_helper(needle, std::forward<_Args>(args)...)};

  return result;
}

using u16ostringstream = std::basic_ostringstream<char16_t>;
using u32ostringstream = std::basic_ostringstream<char32_t>;

template <typename T>
std::u16string join_helper(const std::u16string&, T&& arg) {
  u16ostringstream u16oss{};

  u16oss << arg;

  return u16oss.str();
}

template <typename T, typename... _Args>
std::u16string join_helper(const std::u16string& needle,
                           T&& arg,
                           _Args&&... args) {
  std::basic_ostringstream<char16_t> u16oss{};

  u16oss << arg << needle << join_helper(needle, args...);

  return u16oss.str();
}

template <typename... _Args>
std::u16string join(const std::u16string& needle, _Args&&... args) {
  std::u16string result{join_helper(needle, std::forward<_Args>(args)...)};

  return result;
}

template <typename T>
std::u32string join_helper(const std::u32string&, T&& arg) {
  u32ostringstream u32oss{};

  u32oss << arg;

  return u32oss.str();
}

template <typename T, typename... _Args>
std::u32string join_helper(const std::u32string& needle,
                           T&& arg,
                           _Args&&... args) {
  std::basic_ostringstream<char32_t> u32oss{};

  u32oss << arg << needle << join_helper(needle, args...);

  return u32oss.str();
}

template <typename... _Args>
std::u32string join(const std::u32string& needle, _Args&&... args) {
  std::u32string result{join_helper(needle, std::forward<_Args>(args)...)};

  return result;
}

template <typename StringType,
          typename ContainerType,
          std::enable_if_t<std::is_same_v<StringType, std::string> ||
                           std::is_same_v<StringType, std::wstring> ||
                           std::is_same_v<StringType, std::u16string> ||
                           std::is_same_v<StringType, std::u32string>>>
std::string str_join(const StringType& needle, const ContainerType& items) {
  using char_type = typename StringType::value_type;
  std::basic_ostringstream<char_type> oss{};

  auto start = std::cbegin(items);

  const auto last = std::cend(items);

  while (start != last) {
    oss << *start << needle;

    ++start;
  }

  StringType result{oss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <typename _Container>
std::wstring str_join(const std::wstring& needle, const _Container& items) {
  std::wostringstream woss{};

  auto start = std::cbegin(items);

  const auto last = std::cend(items);

  while (start != last) {
    woss << *start << needle;

    ++start;
  }

  std::wstring result{woss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <typename _Container>
std::u16string str_join(const std::u16string& needle, const _Container& items) {
  std::basic_ostringstream<char16_t> u16oss{};

  auto start = std::cbegin(items);

  const auto last = std::cend(items);

  while (start != last) {
    u16oss << *start << needle;

    ++start;
  }

  std::u16string result{u16oss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <typename _Container>
std::u32string str_join(const std::u32string& needle, const _Container& items) {
  std::basic_ostringstream<char32_t> u32oss{};

  auto start = std::cbegin(items);

  const auto last = std::cend(items);

  while (start != last) {
    u32oss << *start << needle;

    ++start;
  }

  std::u32string result{u32oss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}
}  // namespace experimental
}  // namespace cpp

#endif /* _STL_HELPER_FUNCTIONS_H_ */
