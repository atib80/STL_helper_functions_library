#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <optional>
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

#ifdef _MSC_VER
#include <Strsafe.h>
#define SNPRINTF StringCchPrintfA
#define SNWPRINTF StringCchPrintfW
#else
#define SNPRINTF snprintf
#define SNWPRINTF snwprintf
#endif

#define PRINT_VAR_NAME(arg) std::cout << #arg << ' '
#define PRINT_VAR_NAMEW(arg) std::wcout << #arg << L' '

namespace stl::helper {

static constexpr const char* __stl_helper_utility_library_version__{
    "0.0.1-devel"};

enum class string_type { cstr, wstr, u16_str, u32_str };

template <typename T>
constexpr const std::type_info& get_type_id(T&& t) {
  return typeid(std::forward<T>(t));
}

template <typename T>
std::string get_type_name(T&& t) {
  return std::string{get_type_id(std::forward<T>(t)).name()};
}

template <typename T>
std::wstring get_type_name_wstr(T&& t) {
  const std::string cstr{get_type_id(std::forward<T>(t)).name()};

  return std::wstring{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T>
std::u16string get_type_name_u16str(T&& t) {
  const std::string cstr{get_type_id(std::forward<T>(t)).name()};

  return std::u16string{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T>
std::u32string get_type_name_u32str(T&& t) {
  const std::string cstr{get_type_id(std::forward<T>(t)).name()};

  return std::u32string{std::cbegin(cstr), std::cend(cstr)};
}

template <typename T, typename... T0_TN>
struct is_all_of;

template <typename T>
struct is_all_of<T> : std::true_type {};

template <typename T, typename... T1_TN>
struct is_all_of<T, T, T1_TN...> : is_all_of<T, T1_TN...> {};

template <typename T, typename T0, typename... T1_TN>
struct is_all_of<T, T0, T1_TN...> : std::false_type {};

template <typename T, typename First, typename... Rest>
inline constexpr bool is_all_of_v = is_all_of<T, First, Rest...>::value;

template <typename T>
constexpr bool are_data_types_equal(T&&) {
  return true;
}

template <typename T, typename U, typename... Args>
constexpr bool are_data_types_equal(T&& arg1, U&&, Args&&... args) {
  if constexpr (0 == sizeof...(Args))
    return std::is_same_v<T, U>;
  return std::is_same_v<T, U> &&
         are_data_types_equal(std::forward<T>(arg1),
                              std::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
constexpr bool check_data_types_for_equality(T&& arg1,
                                             U&& arg2,
                                             Args&&... args) {
  if constexpr (0 == sizeof...(Args))
    return std::is_same_v<T, U>;

  return are_data_types_equal(std::forward<T>(arg1), std::forward<U>(arg2),
                              std::forward<Args>(args)...);
}

template <typename T, typename... T0_TN>
struct is_anyone_of;

template <typename T>
struct is_anyone_of<T> : std::false_type {};

template <typename T, typename... T1_TN>
struct is_anyone_of<T, T, T1_TN...> : std::true_type {};

template <typename T, typename T0, typename... T1_TN>
struct is_anyone_of<T, T0, T1_TN...> : is_anyone_of<T, T1_TN...> {};

template <typename T, typename First, typename... Rest>
inline constexpr bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

template <typename T>
constexpr bool is_any_of(T&&) {
  return false;
}

template <typename T, typename U, typename... Args>
constexpr bool is_any_of(T&& arg1, U&&, Args&&... args) {
  if constexpr (0 == sizeof...(Args))
    return std::is_same_v<T, U>;
  return std::is_same_v<T, U> ||
         is_any_of(std::forward<T>(arg1), std::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
constexpr bool check_if_type_is_identical_to(T&& arg1,
                                             U&& arg2,
                                             Args&&... args) {
  if constexpr (0 == sizeof...(Args))
    return std::is_same_v<T, U>;

  return is_any_of(std::forward<T>(arg1), std::forward<U>(arg2),
                   std::forward<Args>(args)...);
}

template <typename T>
using has_key_type_t = decltype(std::declval<typename T::key_type>());

template <typename T, typename = void>
struct has_key_type : std::false_type {};

template <typename T>
struct has_key_type<T, std::void_t<has_key_type_t<T>>> : std::true_type {};

template <typename T>
constexpr const bool has_key_type_v = has_key_type<T>::value;

template <typename T>
using has_value_type_t = decltype(std::declval<typename T::value_type>());

template <typename T, typename = void>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<has_value_type_t<T>>> : std::true_type {};

template <typename T>
constexpr const bool has_value_type_v = has_value_type<T>::value;

template <typename T, typename = void>
struct has_mapped_type : std::false_type {};

template <typename T>
struct has_mapped_type<T, std::void_t<typename T::mapped_type>>
    : std::true_type {};

template <typename T>
constexpr const bool has_mapped_type_v = has_mapped_type<T>::value;

template <typename T, typename U>
using has_find_member_function_t =
    decltype(std::declval<T&>().find(std::declval<U>()));

template <typename T, typename U, typename = void>
struct has_find_member_function : std::false_type {};

template <typename T, typename U>
struct has_find_member_function<T,
                                U,
                                std::void_t<has_find_member_function_t<T, U>>>
    : std::true_type {};

template <typename T, typename U>
constexpr const bool has_find_member_function_v =
    has_find_member_function<T, U>::value;

template <typename StreamType, typename T>
using has_output_stream_operator_type_t =
    decltype(std::declval<StreamType&>() << std::declval<T>());

template <typename StreamType, typename T, typename = void>
struct has_output_stream_operator : std::false_type {};

template <typename StreamType, typename T>
struct has_output_stream_operator<
    StreamType,
    T,
    std::void_t<has_output_stream_operator_type_t<StreamType, T>>>
    : std::true_type {};

template <typename StreamType, typename T>
constexpr const bool has_output_stream_operator_v =
    has_output_stream_operator<StreamType, T>::value;

template <typename T>
using has_operator_dereference_t = decltype(std::declval<T&>().operator*());

template <typename T, typename = void>
struct has_operator_dereference : std::false_type {};

template <typename T>
struct has_operator_dereference<T, std::void_t<has_operator_dereference_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_operator_dereference_v =
    has_operator_dereference<T>::value;

template <typename T>
using is_operator_not_equals_defined_t =
    decltype(std::declval<T&>().operator!=(std::declval<T>()));

template <typename T, typename = void>
struct is_operator_not_equals_defined : std::false_type {};

template <typename T>
struct is_operator_not_equals_defined<
    T,
    std::void_t<is_operator_not_equals_defined_t<T>>> : std::true_type {};

template <typename T>
constexpr const bool is_operator_not_equals_defined_v =
    is_operator_not_equals_defined<T>::value;

template <typename T, typename U = T>
using check_equality_t = decltype(std::declval<T>() == std::declval<U>());

template <typename T, typename U = T, typename = void>
struct check_equality : std::false_type {};

template <typename T, typename U>
struct check_equality<T, U, std::void_t<check_equality_t<T, U>>>
    : std::true_type {};

template <typename T, typename U = T>
constexpr const bool check_equality_v = check_equality<T, U>::value;

template <typename T, typename U = T>
using is_operator_less_than_defined_t =
    decltype(std::declval<T>() < std::declval<U>());

template <typename T, typename U, typename = void>
struct is_operator_less_than_defined : std::false_type {};

template <typename T, typename U>
struct is_operator_less_than_defined<
    T,
    U,
    std::void_t<is_operator_less_than_defined_t<T, U>>> : std::true_type {};

template <typename T, typename U>
constexpr const bool is_operator_less_than_defined_v =
    is_operator_less_than_defined<T, U>::value;

template <typename T>
using has_begin_member_function_t = decltype(std::declval<T&>().begin());

template <typename T, typename = void>
struct has_begin_member_function : std::false_type {};

template <typename T>
struct has_begin_member_function<T, std::void_t<has_begin_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_begin_member_function_v =
    has_begin_member_function<T>::value;

template <typename T>
using has_end_member_function_t = decltype(std::declval<T&>().end());

template <typename T, typename = void>
struct has_end_member_function : std::false_type {};

template <typename T>
struct has_end_member_function<T, std::void_t<has_end_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_end_member_function_v =
    has_end_member_function<T>::value;

template <typename T>
using has_cbegin_member_function_t = decltype(std::declval<T&>().cbegin());

template <typename T, typename = void>
struct has_cbegin_member_function : std::false_type {};

template <typename T>
struct has_cbegin_member_function<T,
                                  std::void_t<has_cbegin_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_cbegin_member_function_v =
    has_cbegin_member_function<T>::value;

template <typename T>
using has_cend_member_function_t = decltype(std::declval<T&>().cend());

template <typename T, typename = void>
struct has_cend_member_function : std::false_type {};

template <typename T>
struct has_cend_member_function<T, std::void_t<has_cend_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_cend_member_function_v =
    has_cend_member_function<T>::value;

template <typename T>
void show_var_info(const T& arg, std::ostream& os) {
  os << "\nName: ";
  PRINT_VAR_NAME(arg);
  os << "\nType: " << get_type_name(arg) << "\nValue: " << arg << '\n';
}

template <typename Runnable>
class run_at_scope_exit {
  Runnable& callable;

 public:
  run_at_scope_exit(Runnable& callable_object) : callable{callable_object} {}
  ~run_at_scope_exit() { callable(); }
};

#define TOKEN_PASTE(x, y) x##y
#define SetUpRunAtScopeExitObject(lambda_name, instance_name, ...) \
  auto lambda_name = [&]() { __VA_ARGS__; };                       \
  run_at_scope_exit<decltype(lambda_name)> instance_name{lambda_name};

#define SetUpTaskToRunAtScopeExit(next_counter_value, ...)   \
  SetUpRunAtScopeExitObject(                                 \
      TOKEN_PASTE(auto_generated_func_, next_counter_value), \
      TOKEN_PASTE(auto_generated_instance_, next_counter_value), __VA_ARGS__)

#define Auto(...) SetUpTaskToRunAtScopeExit(__COUNTER__, __VA_ARGS__)

template <typename... Runnable>
class run_task_at_scope_exit {
  std::initializer_list<Runnable...> callable_tasks;

 public:
  run_task_at_scope_exit(Runnable&&... callable_objects)
      : callable_tasks{std::forward<Runnable>(callable_objects)...} {}
  ~run_task_at_scope_exit() {
    for (auto& task : callable_tasks)
      task();
  }
};

template <typename... Runnable>
auto create_tasks_to_run_at_scope_exit(Runnable&&... tasks) {
  return run_task_at_scope_exit<Runnable...>{std::forward<Runnable>(tasks)...};
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

  SNPRINTF(output_buffer_sp.get(), buffer_size, format_string, args...);

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

  SNWPRINTF(output_buffer_sp.get(), buffer_size, format_string, args...);

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

  SNPRINTF(output_buffer_sp.get(), buffer_size, format_string, args...);

  return printf("%s", output_buffer_sp.get());
}

template <typename... Args>
int say(const wchar_t* format_string, Args... args) {
  auto const buffer_size = _scwprintf(format_string, args...) + 1;

  std::unique_ptr<wchar_t[], wchar_t_buffer_deleter> output_buffer_sp(
      new wchar_t[buffer_size], wchar_t_buffer_deleter{});

  if (!output_buffer_sp)
    return -1;

  SNWPRINTF(output_buffer_sp.get(), buffer_size, format_string, args...);

  return wprintf(L"%ls", output_buffer_sp.get());
}

template <typename T>
constexpr inline void swap(T& first, T& second, std::true_type) noexcept(
    std::is_nothrow_move_constructible_v<T>&&
        std::is_nothrow_move_assignable_v<T>) {
  T tmp{std::move(first)};
  first = std::move(second);
  second = std::move(tmp);
}

template <typename T>
constexpr inline void swap(T& first, T& second, std::false_type) noexcept(
    std::is_nothrow_copy_constructible_v<T>&&
        std::is_nothrow_copy_assignable_v<T>) {
  T tmp{first};
  first = second;
  second = tmp;
}

template <typename T>
constexpr inline void swap(T& first, T& second) {
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
    *--dst_last = *--src_last;
  }

  return dst_last;
}

template <typename T>
struct is_valid_char_type {
  static constexpr const bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
constexpr const bool is_valid_char_type_v = is_valid_char_type<T>::value;

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

template <typename CharType,
          typename = std::enable_if_t<is_valid_char_type_v<CharType>>>
bool is_ws_char(const CharType ch) {
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
  static constexpr bool value = 1u == std::rank_v<T> &&
                                is_valid_char_type_v<std::remove_extent_t<T>> &&
                                !std::is_const_v<std::remove_extent_t<T>>;
};

template <typename T>
constexpr const bool is_non_const_char_array_type_v =
    is_non_const_char_array_type<T>::value;

template <typename T>
struct is_const_char_array_type {
  static constexpr bool value = 1u == std::rank_v<T> &&
                                is_valid_char_type_v<std::remove_extent_t<T>> &&
                                std::is_const_v<std::remove_extent_t<T>>;
};

template <typename T>
constexpr const bool is_const_char_array_type_v =
    is_const_char_array_type<T>::value;

template <typename T>
struct is_char_pointer_type {
  static constexpr const bool value =
      is_non_const_char_pointer_type_v<T> || is_const_char_pointer_type_v<T>;
};

template <typename T>
constexpr const bool is_char_pointer_type_v = is_char_pointer_type<T>::value;

template <typename T>
struct is_char_array_type {
  static constexpr const bool value =
      is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T>;
};

template <typename T>
constexpr const bool is_char_array_type_v = is_char_array_type<T>::value;

template <typename T>
struct remove_all_decorations {
  using dt = std::decay_t<T>;

  using mt1 = std::conditional_t<std::is_const_v<dt> || std::is_volatile_v<dt>,
                                 std::remove_cv_t<dt>,
                                 dt>;
  using mt2 = std::
      conditional_t<std::is_array_v<mt1>, std::remove_all_extents_t<mt1>, mt1>;
  using mt3 = std::
      conditional_t<std::is_pointer_v<mt2>, std::remove_pointer_t<mt2>, mt2>;
  using mt4 = std::conditional_t<std::is_reference_v<mt3>,
                                 std::remove_reference_t<mt3>,
                                 mt3>;
  using type =
      std::conditional_t<std::is_const_v<mt4> || std::is_volatile_v<mt4>,
                         std::remove_cv_t<mt4>,
                         mt4>;
};

template <typename T>
using remove_all_decorations_t = typename remove_all_decorations<T>::type;

template <typename T>
struct is_valid_string_type {
  static constexpr const bool value =
      is_anyone_of_v<remove_all_decorations_t<T>,
                     std::string,
                     std::wstring,
                     std::u16string,
                     std::u32string>;
};

template <typename T>
constexpr const bool is_valid_string_type_v = is_valid_string_type<T>::value;

template <typename T>
struct is_valid_string_view_type {
  static constexpr const bool value =
      is_anyone_of_v<remove_all_decorations_t<T>,
                     std::string_view,
                     std::wstring_view,
                     std::u16string_view,
                     std::u32string_view>;
};

template <typename T>
constexpr const bool is_valid_string_view_type_v =
    is_valid_string_view_type<T>::value;

template <typename T, typename = void>
struct get_char_type {
  using type = remove_all_decorations_t<T>;
  static_assert(is_valid_char_type_v<type>,
                "Underlying type is not an intrinsic character type!");
};

template <typename T>
struct get_char_type<
    T,
    std::void_t<has_value_type_t<remove_all_decorations_t<T>>>> {
  using type = typename remove_all_decorations_t<T>::value_type;
  static_assert(is_valid_char_type_v<type>,
                "Underlying type is not an intrinsic character type!");
};

template <typename T>
using get_char_type_t = typename get_char_type<T>::type;

template <typename T>
struct add_const_pointer_to_char_type {
  using type = std::add_const_t<
      std::add_pointer_t<std::add_const_t<get_char_type_t<T>>>>;
};

template <typename T>
using add_const_pointer_to_char_type_t =
    typename add_const_pointer_to_char_type<T>::type;

static constexpr size_t not_found_index{std::string::npos};

template <typename T,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<is_valid_char_type_v<T>>>
size_t len(T (&arr)[ARRAY_SIZE]) {
  size_t length{};

  while (arr[length])
    length++;

  return length;
}

template <typename T,
          typename = std::enable_if_t<is_char_pointer_type_v<T> ||
                                      is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
size_t len(const T& src) {
  if constexpr (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>)
    return src.length();

  if (nullptr == src)
    return 0U;

  size_t length{};

  while (src[length])
    length++;

  return length;
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T>>>

bool trim_in_place(
    T src,
    const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_non_const_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

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

  last_char_pos = std::find_if(rstart, rlast, [&trimmed_chars](const auto ch) {
                    return trimmed_chars.find(ch) == std::cend(trimmed_chars);
                  }).base();

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

template <typename T, typename = std::enable_if_t<is_valid_string_type_v<T>>>
bool trim_in_place(
    T& src,
    const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

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

  if constexpr (is_non_const_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

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

template <typename T, typename = std::enable_if_t<is_valid_string_type_v<T>>>
bool ltrim_in_place(
    T& src,
    const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

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

  if constexpr (is_non_const_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

  const auto str_len{len(src)};

  if (0U == str_len)
    return false;

  const auto rstart{std::make_reverse_iterator(src + str_len)};
  const auto rlast{std::make_reverse_iterator(src)};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const T last_char_pos =
      std::find_if(rstart, rlast, [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      }).base();

  if (src + str_len == last_char_pos)
    return false;

  *last_char_pos = static_cast<char_type>('\0');

  return true;
}

template <typename T, typename = std::enable_if_t<is_valid_string_type_v<T>>>
bool rtrim_in_place(
    T& src,
    const add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

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

template <typename T,
          typename = std::enable_if_t<is_char_array_type_v<T> ||
                                      is_char_pointer_type_v<T>>>

std::basic_string<get_char_type_t<T>> trim(
    const T src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return std::basic_string<char_type>{};
  }

  std::basic_string<char_type> source_str{src};

  if (0U == source_str.length())
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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>

std::basic_string<get_char_type_t<T>> trim(
    const T& src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (0U == src.length())
    return std::basic_string<char_type>{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return std::basic_string<char_type>{};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return std::basic_string<char_type>{first, last};
}

template <typename T,
          typename = std::enable_if_t<is_char_array_type_v<T> ||
                                      is_char_pointer_type_v<T>>>

std::basic_string<get_char_type_t<T>> ltrim(
    const T src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return std::basic_string<char_type>{};
  }

  if (0U == len(src))
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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>

std::basic_string<get_char_type_t<T>> ltrim(
    const T& src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (0U == src.length())
    return std::basic_string<char_type>{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  const auto last{std::cend(src)};

  if (first == last)
    return std::basic_string<char_type>{};

  return std::basic_string<char_type>{first, last};
}

template <typename T,
          typename = std::enable_if_t<is_char_array_type_v<T> ||
                                      is_char_pointer_type_v<T>>>

std::basic_string<get_char_type_t<T>> rtrim(
    const T src,
    add_const_pointer_to_char_type_t<get_char_type_t<T>> chars_to_trim =
        default_whitespace_chars_v<get_char_type_t<T>>) {
  using char_type = get_char_type_t<T>;

  if (nullptr == src)
    return std::basic_string<char_type>{};

  const auto src_len{len(src)};

  if (0U == src_len)
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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>

std::basic_string<get_char_type_t<T>> rtrim(
    const T& src,
    add_const_pointer_to_char_type_t<typename T::value_type> chars_to_trim =
        default_whitespace_chars_v<typename T::value_type>) {
  using char_type = typename T::value_type;

  if (0U == src.length())
    return std::basic_string<char_type>{};

  std::basic_string<char_type> source_str{src};

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

template <typename SrcIterType,
          typename DstIterType,
          typename = std::enable_if_t<check_equality_v<
              typename std::iterator_traits<SrcIterType>::value_type,
              typename std::iterator_traits<DstIterType>::value_type>>>
constexpr bool starts_with(const SrcIterType src_first,
                           const SrcIterType src_last,
                           const DstIterType dst_first,
                           const DstIterType dst_last,
                           const bool is_find_whole_dst_range = true) {
  if (src_first == src_last || dst_first == dst_last)
    return false;

  const SrcIterType found_iter{
      is_find_whole_dst_range
          ? std::search(src_first, src_last, dst_first, dst_last)
          : std::find_first_of(src_first, src_last, dst_first, dst_last)};
  return src_first == found_iter;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
                  is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
                  is_valid_char_type_v<get_char_type_t<U>>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
bool str_starts_with(T src,
                     const U needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

  if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == needle)
      return false;
  }

  const size_t src_len{len(src)};

  if (0U == src_len)
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

    if (0U == needle_len || needle_len > src_len)
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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_starts_with(const T& src,
                     const get_char_type_t<T> start_char,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_starts_with(const T& src,
                     const get_char_type_t<T>* needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if (nullptr == needle)
    return false;

  const auto src_len{src.length()};
  const auto needle_len{len(needle)};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return 0u == src.find(needle);

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < needle_len; i++) {
      if (f.tolower(src[i]) != f.tolower(needle[i]))
        return false;
    }

    return true;
  }

  for (size_t i{}; i < needle_len; i++) {
    if (std::tolower(src[i]) != std::tolower(needle[i]))
      return false;
  }

  return true;
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_starts_with(const T& src,
                     const T& needle,
                     const bool ignore_case = false,
                     const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return 0u == src.find(needle);

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < needle_len; i++) {
      if (f.tolower(src[i]) != f.tolower(needle[i]))
        return false;
    }

    return true;
  }

  for (size_t i{}; i < needle_len; i++) {
    if (std::tolower(src[i]) != std::tolower(needle[i]))
      return false;
  }

  return true;
}

template <typename SrcIterType,
          typename DstIterType,
          typename = std::enable_if_t<check_equality_v<
              typename std::iterator_traits<SrcIterType>::value_type,
              typename std::iterator_traits<DstIterType>::value_type>>>
constexpr size_t index_of(const SrcIterType src_first,
                          const SrcIterType src_last,
                          const DstIterType dst_first,
                          const DstIterType dst_last,
                          const bool is_find_whole_dst_range = true) {
  if (src_first == src_last || dst_first == dst_last)
    return not_found_index;

  const SrcIterType found_iter{
      is_find_whole_dst_range
          ? std::search(src_first, src_last, dst_first, dst_last)
          : std::find_first_of(src_first, src_last, dst_first, dst_last)};

  if (src_last == found_iter)
    return not_found_index;
  return static_cast<size_t>(std::distance(src_first, found_iter));
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
                  is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
                  is_valid_char_type_v<get_char_type_t<U>>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
typename std::basic_string<get_char_type_t<T>>::size_type str_index_of(
    const T src,
    const U needle,
    const size_t start_pos = 0u,
    const bool ignore_case = false,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<U>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return std::basic_string<char_type>::npos;
  }

  if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == needle)
      return std::basic_string<char_type>::npos;
  }

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    const size_t src_len{len(src)};

    if (0U == src_len)
      return std::basic_string<char_type>::npos;

    if (!ignore_case) {
      std::basic_string_view<char_type> src_str_view{src, src_len};
      return src_str_view.find(needle, start_pos);
    }

    std::basic_string<char_type> src_str{src};
    char_type needle_lc{needle};

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
    const auto src_len{len(src)};
    const auto needle_len{len(needle)};

    if (0U == src_len || 0U == needle_len || needle_len > src_len)
      return std::basic_string<char_type>::npos;

    std::basic_string_view<char_type> src_sv{src, src_len};
    std::basic_string_view<char_type> needle_sv{needle, needle_len};

    if (!ignore_case)
      return src_sv.find(needle_sv, start_pos);

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

    return src_str.find(needle_str, start_pos);
  }
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
typename std::basic_string<get_char_type_t<T>>::size_type str_index_of(
    const T& src,
    const get_char_type_t<T> needle_char,
    const size_t start_pos = 0u,
    const bool ignore_case = false,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if (0U == src.length())
    return std::basic_string<char_type>::npos;

  if (!ignore_case)
    return src.find(needle_char, start_pos);

  std::basic_string<char_type> src_lc{src};
  char_type needle_char_lc{needle_char};

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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
typename std::basic_string<get_char_type_t<T>>::size_type str_index_of(
    const T& src,
    const get_char_type_t<T>* needle,
    const size_t start_pos = 0u,
    const bool ignore_case = false,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if (nullptr == needle)
    return false;

  const auto text_len{src.length()};
  const auto needle_len{len(needle)};

  if (0U == text_len || 0U == needle_len || needle_len > text_len)
    return std::basic_string<char_type>::npos;

  if (!ignore_case)
    return src.find(needle, start_pos);

  std::basic_string<char_type> src_lc{src};
  std::basic_string<char_type> needle_str{needle};

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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
typename std::basic_string<get_char_type_t<T>>::size_type str_index_of(
    const T& src,
    const T& needle,
    const size_t start_pos = 0u,
    const bool ignore_case = false,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0U == src_len || 0U == needle_len || needle_len > src_len)
    return std::basic_string<char_type>::npos;

  if (!ignore_case)
    return src.find(needle, start_pos);

  std::basic_string<char_type> src_lc{src};
  std::basic_string<char_type> needle_lc{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });
    std::transform(std::cbegin(needle_lc), std::cend(needle_lc),
                   std::begin(needle_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(
        std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
    std::transform(
        std::cbegin(needle_lc), std::cend(needle_lc), std::begin(needle_lc),
        [](const auto ch) { return static_cast<char_type>(std::tolower(ch)); });
  }

  return src_lc.find(needle_lc, start_pos);
}

template <typename SrcIterType,
          typename DstIterType,
          typename = std::enable_if_t<check_equality_v<
              typename std::iterator_traits<SrcIterType>::value_type,
              typename std::iterator_traits<DstIterType>::value_type>>>
constexpr bool contains(const SrcIterType src_first,
                        const SrcIterType src_last,
                        const DstIterType dst_first,
                        const DstIterType dst_last,
                        const bool is_find_whole_dst_range = true) {
  if (src_first == src_last || dst_first == dst_last)
    return false;

  const SrcIterType found_iter{
      is_find_whole_dst_range
          ? std::search(src_first, src_last, dst_first, dst_last)
          : std::find_first_of(src_first, src_last, dst_first, dst_last)};

  return src_last != found_iter;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
            is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
            is_valid_char_type_v<get_char_type_t<
                U>>)&&(std::is_same_v<get_char_type_t<T>, get_char_type_t<U>>)>>
bool str_contains(const T src,
                  const U needle,
                  size_t start_pos = 0u,
                  bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

  if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == needle)
      return false;
  }

  const auto src_len{len(src)};

  if (0U == src_len)
    return false;

  if constexpr (is_valid_char_type_v<std::remove_cv_t<U>>) {
    if (!ignore_case)
      return src + src_len != std::find(src + start_pos, src + src_len, needle);

    std::basic_string<char_type> src_str{src};
    char_type needle_lc{needle};

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

    if (0U == needle_len || needle_len > src_len)
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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_contains(const T& src,
                  const get_char_type_t<T> needle_char,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;
  if (0u == src.length())
    return false;

  if (!ignore_case)
    return std::basic_string<char_type>::npos !=
           src.find(needle_char, start_pos);

  std::basic_string<char_type> src_lc{src};
  char_type needle_char_lc{needle_char};

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

  return std::basic_string<char_type>::npos !=
         src_lc.find(needle_char_lc, start_pos);
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_contains(const T& src,
                  const get_char_type_t<T>* needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if (nullptr == needle)
    return false;

  const auto src_len{src.length()};
  const auto needle_len{len(needle)};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return src.find(needle, start_pos) != T::npos;

  std::basic_string<char_type> src_lc{src};
  std::basic_string<char_type> needle_str{needle};

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

  return T::npos != src_lc.find(needle_str, start_pos);
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_contains(const T& src,
                  const T& needle,
                  const size_t start_pos = 0u,
                  const bool ignore_case = false,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const auto src_len{src.length()};
  const auto needle_len{needle.length()};

  if (0u == src_len || 0u == needle_len || needle_len > src_len)
    return false;

  if (!ignore_case)
    return std::basic_string<char_type>::npos != src.find(needle, start_pos);

  const auto& f = std::use_facet<std::ctype<char_type>>(loc);

  std::basic_string<char_type> src_lc{src};
  std::basic_string<char_type> needle_lc{needle};

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

  return std::basic_string<char_type>::npos !=
         src_lc.find(needle_lc, start_pos);
}

template <typename SrcIterType,
          typename DstIterType,
          typename = std::enable_if_t<check_equality_v<
              typename std::iterator_traits<SrcIterType>::value_type,
              typename std::iterator_traits<DstIterType>::value_type>>>
constexpr bool ends_with(const SrcIterType src_first,
                         const SrcIterType src_last,
                         DstIterType dst_first,
                         const DstIterType dst_last,
                         const bool is_find_whole_dst_range = true) {
  if (src_first == src_last || dst_first == dst_last)
    return false;

  SrcIterType target_iter{src_last};
  if (is_find_whole_dst_range) {
    std::advance(target_iter, -std::distance(dst_first, dst_last));
    return target_iter == std::search(src_first, src_last, dst_first, dst_last);
  }

  --target_iter;
  while (dst_first != dst_last) {
    if (*dst_first == *target_iter)
      return true;

    ++dst_first;
  }

  return false;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
            is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
            is_valid_char_type_v<get_char_type_t<
                U>>)&&(std::is_same_v<get_char_type_t<T>, get_char_type_t<U>>)>>
bool str_ends_with(const T src,
                   const U needle,
                   bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == src)
      return false;
  }

  if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == needle)
      return false;
  }

  const auto src_len{len(src)};

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
        if (f.tolower(src[i]) != f.tolower(needle[j]))
          return false;
      }

      return true;
    }

    for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
      if (std::tolower(src[i]) != std::tolower(needle[j]))
        return false;
    }

    return true;
  }
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_ends_with(const T& src,
                   const get_char_type_t<T> end_char,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

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

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_ends_with(const T& src,
                   const get_char_type_t<T>* needle,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if (nullptr == needle)
    return false;

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
      if (f.tolower(src[i]) != f.tolower(needle[j]))
        return false;
    }

    return true;
  }

  for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
    if (std::tolower(src[i]) != std::tolower(needle[j]))
      return false;
  }

  return true;
}

template <typename T,
          typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                      is_valid_string_view_type_v<T>>>
bool str_ends_with(const T& src,
                   const T& needle,
                   const bool ignore_case = false,
                   const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

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
      if (f.tolower(src[i]) != f.tolower(needle[j]))
        return false;
    }

    return true;
  }

  for (size_t i{expected_start_pos_of_end_tag}, j{}; i < src_len; i++, j++) {
    if (std::tolower(src[i]) != std::tolower(needle[j]))
      return false;
  }

  return true;
}

template <typename... Args>
void unused_args(Args&&...) {}

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
          typename = std::enable_if_t<
              has_find_member_function_v<ContainerType, KeyType>>>
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

  } else if constexpr (has_value_type_v<ContainerType> &&
                       check_equality_v<typename ContainerType::value_type,
                                        std::remove_reference_t<ValueType>>) {
    if constexpr (is_operator_less_than_defined_v<
                      typename ContainerType::value_type>) {
      if (std::is_sorted(std::cbegin(container), std::cend(container)))
        return std::binary_search(std::cbegin(container), std::cend(container),
                                  std::forward<ValueType>(value));
    }

    return std::find(std::cbegin(container), std::cend(container),
                     std::forward<ValueType>(value)) != std::cend(container);
  }
}

template <typename T,
          size_t N,
          typename U,
          typename =
              std::enable_if_t<check_equality_v<T, std::remove_reference_t<U>>>>
bool has_value(const std::array<T, N>& container, U&& value) {
  if constexpr (is_operator_less_than_defined_v<T>) {
    if (std::is_sorted(std::cbegin(container), std::cend(container)))
      return std::binary_search(std::cbegin(container), std::cend(container),
                                std::forward<U>(value));
  }

  return std::cend(container) != std::find(std::cbegin(container),
                                           std::cend(container),
                                           std::forward<U>(value));
}

template <typename T,
          size_t N,
          typename U,
          typename =
              std::enable_if_t<check_equality_v<T, std::remove_reference_t<U>>>>
bool has_value(const T (&arr)[N], U&& value) {
  if constexpr (is_operator_less_than_defined_v<T>) {
    if (std::is_sorted(arr, arr + N))
      return std::binary_search(arr, arr + N, std::forward<U>(value));
  }

  return arr + N != std::find(arr, arr + N, std::forward<U>(value));
}

template <
    typename ContainerType,
    typename KeyType,
    typename MappedType,
    typename = std::enable_if_t<
        has_key_type_v<ContainerType> && has_mapped_type_v<ContainerType> &&
        std::is_convertible_v<KeyType, typename ContainerType::key_type> &&
        std::is_convertible_v<MappedType, typename ContainerType::mapped_type>>>
bool has_kv_pair(const ContainerType& container,
                 const std::pair<KeyType, MappedType>& key_value_pair) {
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

template <typename ForwardIterType,
          typename ItemType,
          typename = std::enable_if_t<std::is_convertible_v<
              std::remove_reference_t<ItemType>,
              typename std::iterator_traits<ForwardIterType>::value_type>>>
bool has_item(const ForwardIterType first,
              const ForwardIterType last,
              ItemType&& item) {
  if constexpr (is_operator_less_than_defined_v<typename std::iterator_traits<
                    ForwardIterType>::value_type>) {
    if (std::is_sorted(first, last))
      return std::binary_search(first, last, std::forward<ItemType>(item));
  }

  return last != std::find(first, last, std::forward<ItemType>(item));
}

template <typename T,
          size_t ARRAY_SIZE1,
          size_t ARRAY_SIZE2,
          typename = std::enable_if_t<is_valid_char_type_v<T>>>
int str_compare(T (&arr1)[ARRAY_SIZE1], T (&arr2)[ARRAY_SIZE2]) {
  const size_t arr1_len{len(arr1)};
  const size_t arr2_len{len(arr2)};

  if (0U == arr1_len)
    return 0U == arr2_len ? 0 : -static_cast<int>(arr2[0]);
  if (0U == arr2_len)
    return 0U == arr1_len ? 0 : static_cast<int>(arr1[0]);

  size_t const number_of_characters_to_compare{std::min(arr1_len, arr2_len)};

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (arr1[i] != arr2[i])
      return static_cast<int>(arr1[i] - arr2[i]);
  }

  return static_cast<int>(arr1[i] - arr2[i]);
}

template <typename T,
          size_t ARRAY_SIZE,
          typename U,
          typename = std::enable_if_t<
              is_valid_char_type_v<T> &&
              (is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
               is_valid_string_view_type_v<U>)&&std::
                  is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
int str_compare(T (&src1)[ARRAY_SIZE], const U& src2) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  const size_t number_of_characters_to_compare{std::min(src1_len, src2_len)};

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_char_type_v<U> &&
              (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
               is_valid_string_view_type_v<T>)&&std::
                  is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
int str_compare(const T& src1, U (&src2)[ARRAY_SIZE]) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  const size_t number_of_characters_to_compare{std::min(src1_len, src2_len)};

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
         is_valid_string_view_type_v<
             T>)&&(is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare(const T& src1, const U& src2) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  size_t const number_of_characters_to_compare{std::min(src1_len, src2_len)};
  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <typename T,
          size_t ARRAY_SIZE1,
          size_t ARRAY_SIZE2,
          typename = std::enable_if_t<is_valid_char_type_v<T>>>
int str_compare_n(T (&arr1)[ARRAY_SIZE1],
                  T (&arr2)[ARRAY_SIZE2],
                  size_t number_of_characters_to_compare) {
  const size_t arr1_len{len(arr1)};
  const size_t arr2_len{len(arr2)};

  if (0U == arr1_len)
    return 0U == arr2_len ? 0 : -static_cast<int>(arr2[0]);
  if (0U == arr2_len)
    return 0U == arr1_len ? 0 : static_cast<int>(arr1[0]);

  if (arr1_len < number_of_characters_to_compare ||
      arr2_len < number_of_characters_to_compare)
    number_of_characters_to_compare = std::min(arr1_len, arr2_len);

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (arr1[i] != arr2[i])
      return static_cast<int>(arr1[i] - arr2[i]);
  }

  return static_cast<int>(arr1[i] - arr2[i]);
}

template <typename T,
          size_t ARRAY_SIZE,
          typename U,
          typename = std::enable_if_t<
              is_valid_char_type_v<T> &&
              (is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
               is_valid_string_view_type_v<U>)&&std::
                  is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
int str_compare_n(T (&src1)[ARRAY_SIZE],
                  const U& src2,
                  size_t number_of_characters_to_compare) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src2_len)
    return static_cast<int>(src1[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare)
    number_of_characters_to_compare = std::min(src1_len, src2_len);

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_char_type_v<U> &&
              (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
               is_valid_string_view_type_v<T>)&&std::
                  is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
int str_compare_n(const T& src1,
                  U (&src2)[ARRAY_SIZE],
                  size_t number_of_characters_to_compare) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return -static_cast<int>(src2[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare)
    number_of_characters_to_compare = std::min(src1_len, src2_len);

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
         is_valid_string_view_type_v<
             T>)&&(is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_n(const T& src1,
                  const U& src2,
                  size_t number_of_characters_to_compare) {
  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare)
    number_of_characters_to_compare = std::min(src1_len, src2_len);

  size_t i{};

  for (; i < number_of_characters_to_compare; ++i) {
    if (src1[i] != src2[i])
      return static_cast<int>(src1[i] - src2[i]);
  }

  return static_cast<int>(src1[i] - src2[i]);
}

template <typename T,
          size_t ARRAY_SIZE1,
          size_t ARRAY_SIZE2,
          typename = std::enable_if_t<is_valid_char_type_v<T>>>
int str_compare_i(T (&arr1)[ARRAY_SIZE1],
                  T (&arr2)[ARRAY_SIZE2],
                  const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<T>;

  const size_t arr1_len{len(arr1)};
  const size_t arr2_len{len(arr2)};

  if (0U == arr1_len)
    return 0U == arr2_len ? 0 : -static_cast<int>(arr2[0]);
  if (0U == arr2_len)
    return 0U == arr1_len ? 0 : static_cast<int>(arr1[0]);

  const size_t number_of_characters_to_compare{std::min(arr1_len, arr2_len)};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(arr1[i])};
      const auto ch2{f.tolower(arr2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(arr1[i]) - f.tolower(arr2[i]));

  } else {
    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(arr1[i])};
      const auto ch2{std::tolower(arr2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(arr1[i]) - std::tolower(arr2[i]));
  }
}

template <typename T,
          size_t ARRAY_SIZE,
          typename U,
          typename = std::enable_if_t<
              is_valid_char_type_v<T> &&
              (is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
               is_valid_string_view_type_v<U>)&&std::
                  is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
int str_compare_i(T (&src1)[ARRAY_SIZE],
                  const U& src2,
                  const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<T>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src2_len)
    return static_cast<int>(src1[0]);

  const size_t number_of_characters_to_compare{std::min(src1_len, src2_len)};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(src1[i]) - f.tolower(src2[i]));

  } else {
    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(src1[i]) - std::tolower(src2[i]));
  }
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_char_type_v<U> &&
              (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
               is_valid_string_view_type_v<T>)&&std::
                  is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
int str_compare_i(const T& src1,
                  U (&src2)[ARRAY_SIZE],
                  const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<U>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return -static_cast<int>(src2[0]);

  const size_t number_of_characters_to_compare{std::min(src1_len, src2_len)};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(src1[i]) - f.tolower(src2[i]));

  } else {
    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(src1[i]) - std::tolower(src2[i]));
  }
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
         is_valid_string_view_type_v<
             T>)&&(is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_i(const T& src1,
                  const U& src2,
                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  size_t const number_of_characters_to_compare{std::min(src1_len, src2_len)};
  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(src1[i])};
      const auto ch2{f.tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(f.tolower(src1[i]) - f.tolower(src2[i]));

  } else {
    size_t i{};

    for (; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(src1[i])};
      const auto ch2{std::tolower(src2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }

    return static_cast<int>(std::tolower(src1[i]) - std::tolower(src2[i]));
  }
}

template <typename T,
          size_t ARRAY_SIZE1,
          size_t ARRAY_SIZE2,
          typename = std::enable_if_t<is_valid_char_type_v<T>>>
int str_compare_n_i(T (&arr1)[ARRAY_SIZE1],
                    T (&arr2)[ARRAY_SIZE2],
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<T>;

  const size_t arr1_len{len(arr1)};
  const size_t arr2_len{len(arr2)};

  if (0U == arr1_len)
    return 0U == arr2_len ? 0 : -static_cast<int>(arr2[0]);
  if (0U == arr2_len)
    return 0U == arr1_len ? 0 : static_cast<int>(arr1[0]);

  if (arr1_len < number_of_characters_to_compare ||
      arr2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(arr1_len, arr2_len);
  }

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{f.tolower(arr1[i])};
      const auto ch2{f.tolower(arr2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  } else {
    for (size_t i{}; i < number_of_characters_to_compare; ++i) {
      const auto ch1{std::tolower(arr1[i])};
      const auto ch2{std::tolower(arr2[i])};
      if (ch1 != ch2)
        return static_cast<int>(ch1 - ch2);
    }
  }

  return 0;
}

template <typename T,
          size_t ARRAY_SIZE,
          typename U,
          typename = std::enable_if_t<
              is_valid_char_type_v<T> &&
              (is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
               is_valid_string_view_type_v<U>)&&std::
                  is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
int str_compare_n_i(T (&src1)[ARRAY_SIZE],
                    const U& src2,
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<T>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src2_len)
    return static_cast<int>(src1[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(src1_len, src2_len);
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

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_char_type_v<U> &&
              (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
               is_valid_string_view_type_v<T>)&&std::
                  is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
int str_compare_n_i(const T& src1,
                    U (&src2)[ARRAY_SIZE],
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = std::remove_cv_t<U>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return -static_cast<int>(src2[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(src1_len, src2_len);
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

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_char_pointer_type_v<T> || is_valid_string_type_v<T> ||
         is_valid_string_view_type_v<
             T>)&&(is_char_pointer_type_v<U> || is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
int str_compare_n_i(const T& src1,
                    const U& src2,
                    size_t number_of_characters_to_compare,
                    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  const size_t src1_len{len(src1)};
  const size_t src2_len{len(src2)};

  if (0U == src1_len)
    return 0U == src2_len ? 0 : -static_cast<int>(src2[0]);
  if (0U == src2_len)
    return 0U == src1_len ? 0 : static_cast<int>(src1[0]);

  if (src1_len < number_of_characters_to_compare ||
      src2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = std::min(src1_len, src2_len);
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
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_copy(T (&dst)[ARRAY_SIZE],
                const U& src,
                const str_copy_behavior copy_options =
                    str_copy_behavior::disallow_partial_copy,
                size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;

  const size_t src_len{len(src)};

  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < src_len + 1) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0U;

    const auto no_of_chars_to_copy{ARRAY_SIZE - 1};
    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy, dst);
    dst[no_of_chars_to_copy] = static_cast<char_type>('\0');
    return no_of_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cend(sv), dst);
  dst[src_len] = static_cast<char_type>('\0');
  return src_len;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_copy(
    T dst,
    const size_t dst_capacity_in_number_of_characters,
    const U& src,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const auto src_len{len(src)};
  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (0U == src_len || nullptr == dst)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < src_len + 1) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0U;

    const auto no_of_chars_to_copy{dst_capacity_in_number_of_characters - 1};

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy, dst);

    dst[no_of_chars_to_copy] = static_cast<char_type>('\0');

    return no_of_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cend(sv), dst);

  dst[src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U>)&&std::is_same_v<get_char_type_t<T>,
                                                          get_char_type_t<U>>>>
size_t str_copy(T& dst, const U& src, size_t* required_dst_capacity = nullptr) {
  const auto src_len{len(src)};
  if (required_dst_capacity)
    *required_dst_capacity = src_len + 1U;

  if (0U == src_len)
    return 0U;

  dst.assign(src);
  return src_len;
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              is_valid_char_type_v<U> &&
              std::is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
size_t str_copy(T& dst,
                U (&src)[ARRAY_SIZE],
                size_t* required_dst_capacity = nullptr) {
  const auto src_len{len(src)};
  if (required_dst_capacity)
    *required_dst_capacity = src_len + 1;
  dst.assign(src);
  return src_len;
}

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_copy_n(T (&dst)[ARRAY_SIZE],
                  const U& src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options =
                      str_copy_behavior::disallow_partial_copy,
                  size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;

  const auto src_len{len(src)};

  if (required_dst_capacity)
    *required_dst_capacity =
        std::min(number_of_characters_to_copy, src_len) + 1;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  const auto noctc{std::min(number_of_characters_to_copy, src_len)};

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0U;

    auto const no_chars_to_copy = ARRAY_SIZE - 1;

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_chars_to_copy, dst);

    dst[no_chars_to_copy] = static_cast<char_type>('\0');

    return no_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cbegin(sv) + noctc, dst);

  dst[noctc] = static_cast<char_type>('\0');

  return noctc;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_copy_n(
    T dst,
    size_t dst_capacity_in_number_of_characters,
    const U& src,
    size_t number_of_characters_to_copy,
    str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  const size_t noctc{std::min(number_of_characters_to_copy, src_len)};
  const size_t ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (nullptr == dst || 0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0U;

    const size_t no_chars_to_copy{dst_capacity_in_number_of_characters - 1};

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_chars_to_copy, dst);

    dst[no_chars_to_copy] = static_cast<char_type>('\0');

    return no_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cbegin(sv) + noctc, dst);

  dst[noctc] = static_cast<char_type>('\0');

  return noctc;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U>)&&std::is_same_v<get_char_type_t<T>,
                                                          get_char_type_t<U>>>>
size_t str_copy_n(T& dst,
                  const U& src,
                  size_t number_of_characters_to_copy =
                      std::basic_string<get_char_type_t<T>>::npos,
                  size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  number_of_characters_to_copy = src_len < number_of_characters_to_copy
                                     ? src_len
                                     : number_of_characters_to_copy;

  if (required_dst_capacity)
    *required_dst_capacity = number_of_characters_to_copy + 1;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  dst.assign(std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_copy);

  return number_of_characters_to_copy;
}

template <typename T,
          typename U,
          size_t ARRAY_SIZE,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              is_valid_char_type_v<U> &&
              std::is_same_v<get_char_type_t<T>, std::remove_cv_t<U>>>>
size_t str_copy_n(T& dst,
                  U (&src)[ARRAY_SIZE],
                  size_t number_of_characters_to_copy =
                      std::basic_string<get_char_type_t<T>>::npos,
                  size_t* required_dst_capacity = nullptr) {
  const size_t src_len{len(src)};
  if (required_dst_capacity)
    *required_dst_capacity = src_len + 1;
  if (0U == src_len)
    return 0U;
  number_of_characters_to_copy = src_len < number_of_characters_to_copy
                                     ? src_len
                                     : number_of_characters_to_copy;
  dst.assign(src, src + number_of_characters_to_copy);
  return number_of_characters_to_copy;
}

enum class str_append_behavior {
  disallow_partial_append,
  allow_partial_append,
  do_not_append_return_required_dst_buffer_capacity_only
};

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_append(T (&dst)[ARRAY_SIZE],
                  const U& src,
                  const str_append_behavior append_options =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;
  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};
  const size_t ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ARRAY_SIZE < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return 0U;

    const size_t no_of_chars_to_copy{ARRAY_SIZE - dst_len - 1};

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy,
              dst + dst_len);

    dst[ARRAY_SIZE - 1] = static_cast<char_type>('\0');

    return no_of_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cend(sv), dst + dst_len);

  dst[dst_len + src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_append(T dst,
                  size_t dst_capacity_in_number_of_characters,
                  const U& src,
                  str_append_behavior append_behavior =
                      str_append_behavior::disallow_partial_append,
                  size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};
  const size_t ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (nullptr == dst || 0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (append_behavior ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (append_behavior == str_append_behavior::disallow_partial_append)
      return 0U;

    const size_t no_of_chars_to_copy{dst_capacity_in_number_of_characters -
                                     dst_len - 1};

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy,
              dst + dst_len);

    dst[dst_capacity_in_number_of_characters - 1] =
        static_cast<char_type>('\0');

    return no_of_chars_to_copy;
  }

  std::copy(std::cbegin(sv), std::cend(sv), dst + dst_len);

  dst[dst_len + src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
               is_char_pointer_type_v<T> ||
               is_char_array_type_v<T>)&&(is_valid_string_type_v<U> ||
                                          is_valid_string_view_type_v<U> ||
                                          is_char_pointer_type_v<U> ||
                                          is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
std::basic_string<get_char_type_t<T>> str_append(
    const T& dst,
    const U& src,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;
  const size_t dst_len{len(dst)};
  const size_t src_len{len(src)};

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == dst)
      return {};
  }

  std::basic_string<char_type> final_str{dst};

  if (0U == src_len)
    return final_str;

  final_str += src;

  return final_str;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U> || is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_append(T& dst,
                  const U& src,
                  size_t* required_dst_capacity = nullptr) {
  const size_t dst_len{len(dst)};
  const size_t src_len{len(src)};

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  if (0U == src_len)
    return 0U;

  dst += src;

  return src_len;
}

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_append_n(T (&dst)[ARRAY_SIZE],
                    const U& src,
                    size_t number_of_characters_to_append =
                        std::basic_string<std::remove_cv_t<T>>::npos,
                    const str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;

  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};

  number_of_characters_to_append =
      std::min(src_len, number_of_characters_to_append);
  const size_t ret_val{dst_len + number_of_characters_to_append + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (ret_val > ARRAY_SIZE) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return 0U;

    number_of_characters_to_append = ARRAY_SIZE - dst_len - 1;

    std::copy(std::cbegin(src),
              std::cbegin(src) + number_of_characters_to_append, dst + dst_len);

    dst[ARRAY_SIZE - 1] = static_cast<char_type>('\0');

    return number_of_characters_to_append;
  }

  std::copy(std::cbegin(src), std::cbegin(src) + number_of_characters_to_append,
            dst + dst_len);

  dst[dst_len + number_of_characters_to_append] = static_cast<char_type>('\0');

  return number_of_characters_to_append;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_append_n(T dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const U& src,
                    size_t number_of_characters_to_append =
                        std::basic_string<get_char_type_t<T>>::npos,
                    str_append_behavior append_options =
                        str_append_behavior::disallow_partial_append,
                    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};

  number_of_characters_to_append =
      std::min(number_of_characters_to_append, src_len);

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + number_of_characters_to_append + 1;

  if (nullptr == dst)
    return 0U;

  if (0U == src)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  const size_t required_dst_capacity_in_ch_count{
      dst_len + number_of_characters_to_append + 1};

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return number_of_characters_to_append;

  if (dst_capacity_in_number_of_characters <
      required_dst_capacity_in_ch_count) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return 0U;

    number_of_characters_to_append =
        dst_capacity_in_number_of_characters - dst_len - 1;

    std::copy(std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_append,
              dst + dst_len);

    dst[dst_capacity_in_number_of_characters - 1] =
        static_cast<char_type>('\0');

    return number_of_characters_to_append;
  }

  std::copy(std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_append,
            dst + dst_len);
  dst[dst_len + number_of_characters_to_append] = static_cast<char_type>('\0');
  return number_of_characters_to_append;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
               is_char_pointer_type_v<T> ||
               is_char_array_type_v<T>)&&(is_valid_string_type_v<U> ||
                                          is_valid_string_view_type_v<U> ||
                                          is_char_pointer_type_v<U> ||
                                          is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
std::basic_string<get_char_type<T>> str_append_n(
    const T& dst,
    const U& src,
    size_t number_of_characters_to_append =
        std::basic_string<get_char_type<T>>::npos,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == dst)
      return {};
  }

  std::basic_string<char_type> str{dst};

  const size_t src_len{len(src)};

  number_of_characters_to_append = src_len < number_of_characters_to_append
                                       ? src_len
                                       : number_of_characters_to_append;

  if (required_dst_capacity)
    *required_dst_capacity = str.length() + number_of_characters_to_append + 1;

  if (0U == src_len)
    return str;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  str += sv.substr(0, number_of_characters_to_append);

  return str;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U> || is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_append_n(T& dst,
                    const U& src,
                    size_t number_of_characters_to_append =
                        std::basic_string<get_char_type<T>>::npos,
                    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;
  const size_t src_len{len(src)};
  number_of_characters_to_append = src_len < number_of_characters_to_append
                                       ? src_len
                                       : number_of_characters_to_append;

  if (required_dst_capacity)
    *required_dst_capacity = dst.length() + number_of_characters_to_append + 1;

  if (0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  dst += sv.substr(0, number_of_characters_to_append);

  return src_len;
}

enum class str_prepend_behaviour {
  disallow_partial_prepend,
  allow_partial_prepend,
  do_not_prepend_return_required_dst_buffer_capacity_only
};

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_prepend(T (&dst)[ARRAY_SIZE],
                   const U& src,
                   const str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;

  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};

  const size_t required_dst_size{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_size;

  if (0U == src_len)
    return 0U;

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only)
    return required_dst_size;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (ARRAY_SIZE < required_dst_size) {
    if (prepend_options == str_prepend_behaviour::disallow_partial_prepend)
      return 0U;

    const size_t no_of_chars_to_copy{ARRAY_SIZE - dst_len - 1};

    std::copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy, dst);

    dst[dst_len + no_of_chars_to_copy] = static_cast<char_type>('\0');

    return no_of_chars_to_copy;
  }

  std::copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

  std::copy(std::cbegin(sv), std::cend(sv), dst);

  dst[dst_len + src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_prepend(T dst,
                   size_t dst_capacity_in_number_of_characters,
                   const U& src,
                   str_prepend_behaviour prepend_options =
                       str_prepend_behaviour::disallow_partial_prepend,
                   size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;
  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};

  const size_t required_dst_size{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_size;

  if (nullptr == dst || 0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only)
    return required_dst_size;

  if (dst_capacity_in_number_of_characters < required_dst_size) {
    if (prepend_options == str_prepend_behaviour::disallow_partial_prepend)
      return 0U;

    const size_t no_of_chars_to_copy{dst_capacity_in_number_of_characters -
                                     dst_len - 1};

    std::copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

    std::copy(std::cbegin(sv), std::cbegin(sv) + no_of_chars_to_copy, dst);

    dst[dst_len + no_of_chars_to_copy] = static_cast<char_type>('\0');

    return no_of_chars_to_copy;
  }

  std::copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

  std::copy(std::cbegin(sv), std::cend(sv), dst);

  dst[dst_len + src_len] = static_cast<char_type>('\0');

  return src_len;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
               is_char_pointer_type_v<T> ||
               is_char_array_type_v<T>)&&(is_valid_string_type_v<U> ||
                                          is_valid_string_view_type_v<U> ||
                                          is_char_pointer_type_v<U> ||
                                          is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
std::basic_string<get_char_type_t<T>> str_prepend(
    const T& dst,
    const U& src,
    size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const size_t dst_len{len(dst)};
  const size_t src_len{len(src)};

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  std::basic_string_view<char_type> dv{}, sv{};
  std::basic_string<char_type> dst_str{}, src_str{};

  if constexpr (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>)
    dv.assign(dst);
  else if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == dst)
      dv.assign(dst_str);
    else
      dv.assign(dst, dst_len);
  } else
    dv.assign(dst, dst_len);

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == src)
      sv.assign(src_str);
    else
      sv.assign(src, src_len);
  } else
    sv.assign(src, src_len);

  std::basic_string<char_type> final_str{std::cbegin(sv), std::cend(sv)};

  final_str.append(std::cbegin(dv), std::cend(dv));

  return final_str;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U> || is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
void str_prepend(T& dst,
                 const U& src,
                 size_t* required_dst_capacity = nullptr) {
  const size_t dst_len{dst.length()};
  const size_t src_len{len(src)};

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == src)
      return;
  }

  dst.insert(std::begin(dst), src);
}

template <
    typename T,
    size_t ARRAY_SIZE,
    typename U,
    typename = std::enable_if_t<
        is_valid_char_type_v<T> && !std::is_const_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<std::remove_cv_t<T>, get_char_type_t<U>>>>
size_t str_prepend_n(T (&dst)[ARRAY_SIZE],
                     const U& src,
                     size_t number_of_characters_to_prepend =
                         std::basic_string<std::remove_cv_t<T>>::npos,
                     const str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  using char_type = std::remove_cv_t<T>;
  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};

  number_of_characters_to_prepend = src_len < number_of_characters_to_prepend
                                        ? src_len
                                        : number_of_characters_to_prepend;
  const size_t ret_val{dst_len + number_of_characters_to_prepend + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only)
    return ret_val;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (ARRAY_SIZE < ret_val) {
    if (prepend_options == str_prepend_behaviour::disallow_partial_prepend)
      return 0U;

    const size_t nocp{ARRAY_SIZE - dst_len - 1};

    std::copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

    std::copy(std::cbegin(sv), std::cbegin(sv) + nocp, dst);

    dst[nocp + dst_len] = static_cast<char_type>('\0');

    return nocp;
  }
  std::copy_backward(dst, dst + dst_len,
                     dst + dst_len + number_of_characters_to_prepend);

  std::copy(std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_prepend,
            dst);

  dst[number_of_characters_to_prepend + dst_len] = static_cast<char_type>('\0');

  return number_of_characters_to_prepend;
}

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        is_non_const_char_pointer_type_v<T> &&
        (is_char_array_type_v<U> || is_char_pointer_type_v<U> ||
         is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_prepend_n(T dst,
                     size_t dst_capacity_in_number_of_characters,
                     const U& src,
                     size_t number_of_characters_to_prepend =
                         std::basic_string<get_char_type_t<T>>::npos,
                     str_prepend_behaviour prepend_options =
                         str_prepend_behaviour::disallow_partial_prepend,
                     size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;
  const size_t src_len{len(src)};
  const size_t dst_len{len(dst)};
  number_of_characters_to_prepend = src_len < number_of_characters_to_prepend
                                        ? src_len
                                        : number_of_characters_to_prepend;
  const size_t required_dst_size{dst_len + number_of_characters_to_prepend + 1};

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_size;

  if (nullptr == dst || 0U == src_len)
    return 0U;

  std::basic_string_view<char_type> sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else
    sv.assign(src, src_len);

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only)
    return required_dst_size;

  if (dst_capacity_in_number_of_characters <
      dst_len + number_of_characters_to_prepend + 1) {
    if (prepend_options == str_prepend_behaviour::disallow_partial_prepend)
      return 0U;

    const size_t nocp{dst_capacity_in_number_of_characters - dst_len - 1};

    std::copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

    std::copy(std::cbegin(sv), std::cbegin(sv) + nocp, dst);

    dst[dst_len + nocp] = static_cast<char_type>('\0');

    return nocp;
  }

  std::copy_backward(dst, dst + dst_len,
                     dst + dst_len + number_of_characters_to_prepend);

  std::copy(std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_prepend,
            dst);

  dst[dst_len + number_of_characters_to_prepend] = static_cast<char_type>('\0');

  return number_of_characters_to_prepend;
}

// TODO: implement rest of str_prepend_n funtion templates

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
               is_char_pointer_type_v<T> ||
               is_char_array_type_v<T>)&&(is_valid_string_type_v<U> ||
                                          is_valid_string_view_type_v<U> ||
                                          is_char_pointer_type_v<U> ||
                                          is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
std::basic_string<get_char_type_t<T>> str_prepend_n(
    const T& dst,
    const U& src,
    size_t number_of_characters_to_prepend =
        std::basic_string<get_char_type_t<T>>::npos) {
  using char_type = get_char_type_t<T>;
  const size_t dst_len{len(dst)};
  const size_t src_len{len(src)};

  number_of_characters_to_prepend = src_len < number_of_characters_to_prepend
                                        ? src_len
                                        : number_of_characters_to_prepend;

  std::basic_string_view<char_type> dv{}, sv{};
  std::basic_string<char_type> dst_str{}, src_str{};

  if constexpr (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>)
    dv.assign(dst);
  else if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == dst)
      dv.assign(dst_str);
    else
      dv.assign(dst, dst_len);
  } else
    dv.assign(dst, dst_len);

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == src)
      sv.assign(src_str);
    else
      sv.assign(src, src_len);
  } else
    sv.assign(src, src_len);

  std::basic_string<char_type> final_str{
      std::cbegin(sv), std::cbegin(sv) + number_of_characters_to_prepend};

  final_str.append(std::cbegin(dv), std::cend(dv));

  return final_str;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_valid_string_type_v<T> && !std::is_const_v<T> &&
              (is_valid_string_type_v<U> || is_valid_string_view_type_v<U> ||
               is_char_pointer_type_v<U> || is_char_array_type_v<U>)&&std::
                  is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
void str_prepend_n(T& dst,
                   const U& src,
                   size_t number_of_characters_to_prepend =
                       std::basic_string<get_char_type_t<T>>::npos) {
  using char_type = get_char_type_t<T>;

  const size_t src_len{len(src)};

  number_of_characters_to_prepend = src_len < number_of_characters_to_prepend
                                        ? src_len
                                        : number_of_characters_to_prepend;

  std::basic_string_view<char_type> sv{};
  std::basic_string<char_type> src_str{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    sv.assign(src);
  else if constexpr (is_char_pointer_type_v<U>) {
    if (nullptr == src)
      sv.assign(src_str);
    else
      sv.assign(src, src_len);
  } else
    sv.assign(src, src_len);

  dst.insert(std::begin(dst), std::cbegin(sv),
             std::cbegin(sv) + number_of_characters_to_prepend);
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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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

    std::copy(src, src + nocti, dst + position_index_in_dst);

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
    typename U,
    typename = std::enable_if_t<
        (is_non_const_char_pointer_type_v<T> ||
         is_non_const_char_array_type_v<T>)&&(is_valid_string_type_v<U> ||
                                              is_char_pointer_type_v<U> ||
                                              is_char_array_type_v<U>)&&std::
            is_same_v<get_char_type_t<T>, get_char_type_t<U>>>>
size_t str_replace_first(T& dst,
                         const size_t dst_capacity,
                         const U& needle,
                         const U& replace,
                         size_t* required_dst_capacity = nullptr) {
  using char_type = get_char_type_t<T>;

  const auto dst_len{len(dst)};
  const auto needle_len{len(needle)};
  const auto replace_len{len(replace)};

  if (0U == needle_len || 0U == replace_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + 1;
    return 0U;
  }

  if (needle_len > dst_len) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + 1;

    return 0U;
  }

  const auto start_pos = str_index_of(dst, needle);

  if (not_found_index == start_pos) {
    if (required_dst_capacity)
      *required_dst_capacity = dst_len + 1;

    return 0U;
  }

  const auto rdc{dst_len - needle_len + replace_len + 1};

  if (dst_capacity < rdc) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0U;
  }

  std::basic_string_view<char_type> replace_sv{};

  if constexpr (is_valid_string_type_v<U> || is_valid_string_view_type_v<U>)
    replace_sv.assign(replace);
  else
    replace_sv.assign(replace, replace_len);

  if (needle_len == replace_len) {
    std::copy(std::cbegin(replace_sv), std::cend(replace_sv), dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1U;
  }

  if (needle_len < replace_len) {
    const auto noctm{replace_len - needle_len};

    // if needle_len == 2 and replace_len == 10, all the characters in
    // the upper part of dst ( characters with positions >= dst +
    // start_pos + needle_len characters ) have to be moved 'noctm' (8)
    // character positions toward the end of dst.

    std::copy_backward(dst + start_pos + needle_len, dst + dst_len,
                       dst + dst_len + noctm);

    dst[dst_len + noctm] = static_cast<char_type>('\0');

    std::copy(std::cbegin(replace_sv), std::cend(replace_sv), dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1U;
  }

  // needle_len > replace_len
  const auto noctm{needle_len - replace_len};

  // if needle_len == 10 and replace_len == 2, all the characters in
  // the upper part of dst ( characters with positions >= dst +
  // start_pos + needle_len characters ) have to be moved 'noctm' (8)
  // character positions toward dst
  // + start_pos + replace_len.

  for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = static_cast<char_type>('\0');

  std::copy(std::cbegin(replace_sv), std::cend(replace_sv), dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1U;
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
    std::copy(replace, replace + replace_len, dst + start_pos);

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

    std::copy(replace, replace + replace_len, dst + start_pos);

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

  std::copy(replace, replace + replace_len, dst + start_pos);

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
    std::copy(replace, replace + replace_len, dst + start_pos);

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

    std::copy(replace, replace + replace_len, dst + start_pos);

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

  std::copy(replace, replace + replace_len, dst + start_pos);

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
    std::copy(replace, replace + replace_len, dst + start_pos);

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

    std::copy(replace, replace + replace_len, dst + start_pos);

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

  std::copy(replace, replace + replace_len, dst + start_pos);

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

template <typename T,
          typename U,
          typename = std::enable_if_t<
              (is_non_const_char_array_type_v<T> ||
               is_non_const_char_pointer_type_v<
                   T>)&&(is_char_array_type_v<U> ||
                         is_char_pointer_type_v<
                             U>)&&(std::is_same_v<get_char_type_t<T>,
                                                  get_char_type_t<U>>)>>
get_char_type_t<T>* str_replace_nth(T src,
                                    U needle,
                                    const size_t nth_index = 1) {
  // using char_type = get_char_type_t<T>;
  unused_args(src, needle, nth_index);

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
  unused_args(src, needle);
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
  unused_args(src, needle);
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
  unused_args(src, needle, number_of_copies_to_replace);
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
  unused_args(src, needle, number_of_copies_to_replace);
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
  unused_args(src, needle);
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
  unused_args(src, needle);
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
  unused_args(src, needle);
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
  unused_args(src, needle);
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
  unused_args(src, needle, number_of_copies_to_erase);
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
  unused_args(src, needle, number_of_copies_to_erase);
  return nullptr;
}

template <
    typename T,
    typename U,
    std::enable_if_t<(is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
        is_char_array_type_v<U> ||
        is_char_pointer_type_v<U>)&&(std::is_same_v<get_char_type_t<T>,
                                                    get_char_type_t<U>>)>>
const get_char_type_t<T>* strstr(const T& src, const U& needle) {
  using char_type = get_char_type_t<T>;
  using return_type = const char_type*;
  const std::basic_string_view<char_type> sv{src, len(src)},
      nv{needle, len(needle)};

  const size_t pos{sv.find(nv)};
  return std::basic_string_view<char_type>::npos != pos
             ? static_cast<return_type>(&src[0] + pos)
             : nullptr;
}

template <
    typename T,
    typename U,
    std::enable_if_t<
        (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>)&&(
            is_valid_string_type_v<U> ||
            is_valid_string_view_type_v<
                U>)&&(std::is_same_v<get_char_type_t<T>, get_char_type_t<U>>)>>
decltype(std::declval<T&>().find(std::declval<T>())) strstr(const T& src,
                                                            const U& needle) {
  return src.find(needle);
}

template <
    typename T,
    typename U,
    std::enable_if_t<(is_char_array_type_v<T> || is_char_pointer_type_v<T>)&&(
        is_char_array_type_v<U> ||
        is_char_pointer_type_v<U>)&&(std::is_same_v<get_char_type_t<T>,
                                                    get_char_type_t<U>>)>>
const get_char_type_t<T>* strstri(const T& src,
                                  const U& needle,
                                  const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;
  using return_type = const char_type*;
  const std::basic_string<char_type> src_lc{src}, needle_lc{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

    std::transform(std::cbegin(needle_lc), std::cend(needle_lc),
                   std::begin(needle_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [](const auto ch) { return std::tolower(ch); });

    std::transform(std::cbegin(needle_lc), std::cend(needle_lc),
                   std::begin(needle_lc),
                   [](const auto ch) { return std::tolower(ch); });
  }

  const size_t pos{src_lc.find(needle_lc)};
  return std::basic_string<char_type>::npos != pos
             ? static_cast<return_type>(&src[0] + pos)
             : nullptr;
}

template <
    typename T,
    typename U,
    std::enable_if_t<
        (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>)&&(
            is_valid_string_type_v<U> ||
            is_valid_string_view_type_v<
                U>)&&(std::is_same_v<get_char_type_t<T>, get_char_type_t<U>>)>>
decltype(std::declval<T&>().find(std::declval<T>()))
strstri(const T& src, const U& needle, const std::locale& loc = std::locale{}) {
  using char_type = typename T::value_type;
  std::basic_string<char_type> src_lc{src};
  std::basic_string<char_type> needle_lc{needle};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);

    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

    std::transform(std::cbegin(needle_lc), std::cend(needle_lc),
                   std::begin(needle_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(std::cbegin(src_lc), std::cend(src_lc), std::begin(src_lc),
                   [](const auto ch) { return std::tolower(ch); });

    std::transform(std::cbegin(needle_lc), std::cend(needle_lc),
                   std::begin(needle_lc),
                   [](const auto ch) { return std::tolower(ch); });
  }

  return src_lc.find(needle_lc);
}

template <typename T,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> to_lower_case(
    const T& str,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == str)
      return {};
  }

  std::basic_string<char_type> str_lc{str};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(str_lc), std::cend(str_lc), std::begin(str_lc),
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(std::cbegin(str_lc), std::cend(str_lc), std::begin(str_lc),
                   [](const auto ch) { return std::tolower(ch); });
  }

  return str_lc;
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T> ||
                                      is_valid_string_type_v<T>>>
void to_lower_case_in_place(T& str, const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  size_t str_len{len(str)};
  char_type* first{&str[0]};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(first, first + str_len, first,
                   [&f](const auto ch) { return f.tolower(ch); });

  } else {
    std::transform(first, first + str_len, first,
                   [](const auto ch) { return std::tolower(ch); });
  }
}

template <typename T,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> to_upper_case(
    const T& str,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == str)
      return {};
  }

  std::basic_string<char_type> str_lc{str};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(std::cbegin(str_lc), std::cend(str_lc), std::begin(str_lc),
                   [&f](const auto ch) { return f.toupper(ch); });

  } else {
    std::transform(std::cbegin(str_lc), std::cend(str_lc), std::begin(str_lc),
                   [](const auto ch) { return std::toupper(ch); });
  }

  return str_lc;
}

template <typename T,
          typename = std::enable_if_t<is_non_const_char_array_type_v<T> ||
                                      is_non_const_char_pointer_type_v<T> ||
                                      is_valid_string_type_v<T>>>
void to_upper_case_in_place(T& str, const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  size_t str_len{len(str)};
  char_type* first{&str[0]};

  if (std::has_facet<std::ctype<char_type>>(loc)) {
    const auto& f = std::use_facet<std::ctype<char_type>>(loc);
    std::transform(first, first + str_len, first,
                   [&f](const auto ch) { return f.toupper(ch); });

  } else {
    std::transform(first, first + str_len, first,
                   [](const auto ch) { return std::toupper(ch); });
  }
}

template <typename T,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> to_title_case(
    const T& str,
    const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;

  std::basic_string<char_type> final_str{str};

  bool is_new_sentence{true};

  std::optional<decltype(
      std::use_facet<std::ctype<char_type>>(std::declval<std::locale>()))>
      f{};

  if (std::has_facet<std::ctype<char_type>>(loc))
    f = std::use_facet<std::ctype<char_type>>(loc);

  for (auto& ch : final_str) {
    if (static_cast<char_type>('.') == ch) {
      is_new_sentence = true;
      continue;
    }

    if (is_new_sentence && !is_ws_char(ch)) {
      if (f.has_value())
        ch = f.toupper(ch);
      else
        ch = std::toupper(ch);

      is_new_sentence = false;
    }
  }

  return final_str;
}

template <typename T,
          typename = std::enable_if_t<is_char_array_type_v<T> ||
                                      is_char_pointer_type_v<T> ||
                                      is_valid_string_type_v<T>>>
void to_title_case_in_place(T& str, const std::locale& loc = std::locale{}) {
  using char_type = get_char_type_t<T>;
  std::optional<decltype(
      std::use_facet<std::ctype<char_type>>(std::declval<std::locale>()))>
      f{};

  if (std::has_facet<std::ctype<char_type>>(loc))
    f = std::use_facet<std::ctype<char_type>>(loc);

  size_t str_len{len(str)};
  char_type* first{&str[0]};
  bool is_new_sentence{true};

  for (char_type *first{&str[0]}, last{&str[0] + str_len}; first != last;
       ++first) {
    if (static_cast<char_type>('.') == *first) {
      is_new_sentence = true;
      continue;
    }

    if (is_new_sentence && !is_ws_char(*first)) {
      if (f.has_value())
        *first = f.toupper(*first);
      else
        *first = std::toupper(*first);

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

template <typename T,
          typename FormatStringType = const char*,
          typename = std::enable_if_t<
              has_output_stream_operator_v<
                  std::basic_ostream<get_char_type_t<FormatStringType>>,
                  std::remove_reference_t<T>> &&
              is_valid_char_type_v<get_char_type_t<FormatStringType>> &&
              is_anyone_of_v<get_char_type_t<FormatStringType>, char, wchar_t>>>
std::basic_string<get_char_type_t<FormatStringType>> num_to_str(
    T&& data,
    FormatStringType format_string = nullptr) {
  using char_type = get_char_type_t<FormatStringType>;
  using data_type = remove_all_decorations_t<T>;

  static constexpr const size_t buf_size{32};

  static char_type buffer[buf_size]{};

  if (nullptr != format_string) {
    if constexpr (!std::is_integral_v<data_type> &&
                  !std::is_floating_point_v<data_type>) {
      std::basic_ostringstream<char_type> oss{};
      oss << std::forward<T>(data);
      return oss.str();
    } else if constexpr (std::is_same_v<char_type, char>)
      SNPRINTF(buffer, buf_size, format_string, std::forward<T>(data));
    else
      SNWPRINTF(buffer, buf_size, format_string, std::forward<T>(data));
  }

  if constexpr (std::is_integral_v<data_type>) {
    if constexpr (std::is_signed_v<data_type>) {
      const long long value{std::forward<T>(data)};
      if constexpr (std::is_same_v<char_type, char>)
        SNPRINTF(buffer, buf_size, "%lld", value);
      else
        SNWPRINTF(buffer, buf_size, L"%lld", value);
    } else {
      const unsigned long long value{std::forward<T>(data)};
      if constexpr (std::is_same_v<char_type, char>)
        SNPRINTF(buffer, buf_size, "%llu", value);
      else
        SNWPRINTF(buffer, buf_size, L"%llu", value);
    }
  } else if constexpr (std::is_floating_point_v<data_type>) {
    if constexpr (std::is_same_v<float, data_type>) {
      if constexpr (std::is_same_v<char_type, char>)
        SNPRINTF(buffer, buf_size, "%f", std::forward<T>(data));
      else
        SNWPRINTF(buffer, buf_size, L"%f", std::forward<T>(data));
    } else if constexpr (std::is_same_v<double, data_type>) {
      if constexpr (std::is_same_v<char_type, char>)
        SNPRINTF(buffer, buf_size, "%lf", std::forward<T>(data));
      else
        SNWPRINTF(buffer, buf_size, L"%lf", std::forward<T>(data));
    } else {
      if constexpr (std::is_same_v<char_type, char>)
        SNPRINTF(buffer, buf_size, "%Lf", std::forward<T>(data));
      else
        SNWPRINTF(buffer, buf_size, L"%Lf", std::forward<T>(data));
    }
  } else {
    static char buffer[128]{};
    SNPRINTF(buffer, 128,
             "Provided data type [%s] is not a valid primitive integral or "
             "floating point number type!",
             typeid(data_type).name());
    throw std::invalid_argument{buffer};
  }

  return buffer;
}

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

template <
    typename T,
    typename U,
    typename = std::enable_if_t<
        (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
         is_char_array_type_v<T> ||
         is_char_pointer_type_v<
             T>)&&(is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U> || is_char_array_type_v<U> ||
                   is_char_pointer_type_v<
                       U>)&&(std::is_same_v<get_char_type_t<T>,
                                            get_char_type_t<U>>)>>
std::vector<std::basic_string<get_char_type_t<T>>> split(
    const T& source,
    const U& needle,
    const bool split_on_whole_needle = true,
    const bool ignore_empty_string = true,
    size_t const max_count = std::basic_string<get_char_type_t<T>>::npos) {
  using char_type = get_char_type_t<T>;
  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == source)
      return {};
  }
  const std::basic_string_view<char_type> sv{source};
  const size_t source_len{sv.length()};
  if (0U == source_len)
    return {};

  const std::basic_string_view<char_type> nv{needle};
  const size_t needle_len{split_on_whole_needle ? nv.length() : 1U};

  if (0U == needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    std::vector<std::basic_string<char_type>> parts(upper_limit);
    for (size_t i{}; i < upper_limit; i++)
      parts[i].assign({1, sv[i]});
    return parts;
  }

  std::vector<std::basic_string<char_type>> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current = split_on_whole_needle
                               ? sv.find(nv.data(), prev)
                               : sv.find_first_of(nv.data(), prev);

    if (std::basic_string<char_type>::npos == current)
      break;

    if (parts.size() == max_count)
      break;

    if (current - prev > 0 || !ignore_empty_string) {
      if (current - prev > 0)
        parts.emplace_back(std::cbegin(sv) + prev, std::cbegin(sv) + current);
      else if (!ignore_empty_string)
        parts.emplace_back();

      number_of_parts++;
    }

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (parts.size() < max_count) {
    if (prev < source_len)
      parts.emplace_back(std::cbegin(sv) + prev, std::cend(sv));
    else if (!ignore_empty_string)
      parts.emplace_back();
  }

  return parts;
}

template <
    typename IteratorType,
    typename NeedleType,
    typename = std::enable_if_t<
        is_valid_char_type_v<
            typename std::iterator_traits<IteratorType>::value_type> &&
        std::is_same_v<typename std::iterator_traits<IteratorType>::value_type,
                       get_char_type_t<NeedleType>>>>
std::vector<
    std::basic_string<typename std::iterator_traits<IteratorType>::value_type>>
split(IteratorType first,
      IteratorType last,
      const NeedleType& needle,
      const bool split_on_whole_needle = true,
      const bool ignore_empty_string = true,
      const size_t max_count = std::numeric_limits<size_t>::max()) {
  using char_type = typename std::iterator_traits<IteratorType>::value_type;
  std::vector<std::basic_string<char_type>> parts{};

  if (first == last)
    return parts;

  std::basic_string_view<char_type> sv{first, std::distance(first, last)};

  const size_t source_len{sv.length()};

  if (0u == source_len)
    return parts;

  std::basic_string<char_type> needle_str{};
  std::basic_string_view<char_type> nv{};
  size_t needle_len{};

  if constexpr (is_char_array_type_v<NeedleType> ||
                is_char_pointer_type_v<NeedleType>) {
    needle_len = len(needle);
    nv.assign(needle, needle_len);
  } else if constexpr (is_valid_string_type_v<NeedleType> ||
                       is_valid_string_view_type_v<NeedleType>) {
    nv.assign(needle);
    needle_len = needle.length();

  } else if constexpr (is_valid_char_type_v<NeedleType>) {
    needle_str.assign(1, needle);
    nv.assign(needle_str);
    needle_len = 1;
  }

  if (0U == needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    std::vector<std::basic_string<char_type>> parts(upper_limit);
    for (size_t i{}; i < upper_limit; i++)
      parts[i].assign({1, sv[i]});
    return parts;
  }

  if (!split_on_whole_needle)
    needle_len = 1U;

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current = split_on_whole_needle
                               ? sv.find(nv.data(), prev)
                               : sv.find_first_of(nv.data(), prev);

    if (std::basic_string<char_type>::npos == current)
      break;

    if (parts.size() == max_count)
      break;

    if (current - prev > 0 || !ignore_empty_string) {
      if (current - prev > 0)
        parts.emplace_back(std::cbegin(sv) + prev, std::cbegin(sv) + current);
      else if (!ignore_empty_string)
        parts.emplace_back();

      number_of_parts++;
    }

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (parts.size() < max_count) {
    if (prev < source_len)
      parts.emplace_back(std::cbegin(sv) + prev, std::cend(sv));
    else if (!ignore_empty_string)
      parts.emplace_back();
  }

  return parts;
}

template <typename SrcIterType,
          typename DstIterType,
          std::enable_if_t<check_equality_v<
              typename std::iterator_traits<SrcIterType>::value_type,
              typename std::iterator_traits<DstIterType>::value_type>>>
std::vector<std::pair<SrcIterType, SrcIterType>> split(
    const SrcIterType src_first,
    const SrcIterType src_last,
    const DstIterType needle_first,
    const DstIterType needle_last,
    const bool split_on_whole_sequence = true,
    const bool ignore_empty_sequence = true,
    const size_t max_count = std::numeric_limits<size_t>::max()) {
  if (src_first == src_last)
    return {};

  std::vector<std::pair<SrcIterType, SrcIterType>> parts{};
  SrcIterType prev{src_first};
  size_t number_of_parts{};

  if (needle_first == needle_last) {
    const size_t source_len{
        static_cast<size_t>(std::distance(src_first, src_last))};
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    parts.reserve(upper_limit);
    SrcIterType last_element{prev};
    std::advance(last_element, upper_limit);

    while (prev != last_element) {
      const SrcIterType first{prev};
      ++prev;
      parts.emplace_back(first, prev);
    }

    return parts;
  }

  const size_t needle_sequence_len{
      split_on_whole_sequence
          ? static_cast<size_t>(std::distance(needle_first, needle_last))
          : 1U};

  SrcIterType next;

  while (prev != src_last) {
    if (split_on_whole_sequence)
      next = std::search(prev, src_last, needle_first, needle_last);
    else
      next = std::find_first_of(prev, src_last, needle_first, needle_last);

    if (src_last == next)
      break;

    if ((std::distance(prev, next) > 0 || !ignore_empty_sequence) &&
        (number_of_parts < max_count)) {
      parts.emplace_back(prev, next);
      number_of_parts++;
    }

    prev = next;
    std::advance(prev, needle_sequence_len);
  }

  if ((std::distance(prev, src_last) > 0 || !ignore_empty_sequence) &&
      (number_of_parts < max_count)) {
    parts.emplace_back(prev, src_last);
    number_of_parts++;
  }

  return parts;
}

template <typename T,
          typename U,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> join_helper(const T&, U&& arg) {
  using char_type = get_char_type_t<T>;
  std::basic_ostringstream<char_type> oss{};
  oss << std::forward<U>(arg);
  return oss.str();
}

template <typename T,
          typename U,
          typename... Args,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> join_helper(const T& needle,
                                                  U&& arg,
                                                  Args&&... args) {
  using char_type = get_char_type_t<T>;
  std::basic_ostringstream<char_type> oss{};
  oss << std::forward<U>(arg) << needle
      << join_helper(needle, std::forward<Args>(args)...);
  return oss.str();
}

template <typename T,
          typename... Args,
          typename = std::enable_if_t<
              is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
              is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
std::basic_string<get_char_type_t<T>> join(const T& needle, Args&&... args) {
  using char_type = get_char_type_t<T>;
  std::basic_string<char_type> result{
      join_helper(needle, std::forward<Args>(args)...)};
  return result;
}

template <typename ContainerType,
          typename NeedleType,
          typename = std::enable_if_t<
              (is_char_pointer_type_v<NeedleType> ||
               is_char_array_type_v<NeedleType> ||
               is_valid_string_type_v<NeedleType> ||
               is_valid_string_view_type_v<
                   NeedleType>)&&has_cbegin_member_function_v<ContainerType> &&
              has_cend_member_function_v<ContainerType> &&
              has_output_stream_operator_v<
                  std::basic_ostream<get_char_type_t<NeedleType>>,
                  typename ContainerType::value_type>>>
std::basic_string<get_char_type_t<NeedleType>> str_join(
    const ContainerType& items,
    const NeedleType& needle) {
  using char_type = get_char_type_t<NeedleType>;
  std::basic_ostringstream<char_type> oss{};

  auto first = items.cbegin(items);
  const auto last = items.cend(items);

  while (first != last) {
    oss << *first << needle;
    ++first;
  }

  std::basic_string<char_type> result{oss.str()};
  const size_t needle_len{needle.length()};
  result.erase(result.length() - needle_len, needle_len);

  return result;
}

template <
    typename FwIterType,
    typename NeedleType,
    typename = std::enable_if_t<(
        is_char_pointer_type_v<NeedleType> ||
        is_char_array_type_v<NeedleType> ||
        is_valid_string_type_v<NeedleType> ||
        is_valid_string_view_type_v<
            NeedleType>)&&has_output_stream_operator_v<std::
                                                           basic_ostream<
                                                               get_char_type_t<
                                                                   NeedleType>>,
                                                       typename std::
                                                           iterator_traits<
                                                               FwIterType>::
                                                               value_type>>>
std::basic_string<get_char_type_t<NeedleType>>
str_join(FwIterType first, const FwIterType last, const NeedleType& needle) {
  using char_type = get_char_type_t<NeedleType>;
  std::basic_ostringstream<char_type> oss{};

  while (first != last) {
    oss << *first << needle;
    ++first;
  }

  std::basic_string<char_type> result{oss.str()};
  const size_t needle_len{needle.length()};
  result.erase(result.length() - needle_len, needle_len);

  return result;
}

}  // namespace stl::helper
