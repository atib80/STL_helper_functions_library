#define CATCH_CONFIG_MAIN

#include <crtdbg.h>
#include <chrono>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../includes/catch.hpp"
// #include <windows.h>
#include "../src/stl_helper_functions.hpp"

using namespace std;
using namespace std::chrono;
using namespace std::string_literals;
using namespace cpp::experimental;

static random_device rd{};

long long get_random_number(const long long lower_bound,
                            const long long upper_bound) {
  static mt19937 rand_engine{rd()};

  uniform_int_distribution<long long> num_distr(lower_bound, upper_bound);

  return num_distr(rand_engine);
}

// TEST_CASE("int say_slow(const size_t, const char*, Args...)",
//	"Testing correct work of global template function int say_slow(const
// size_t time_delay_in_ms, const char* format_string, Args... args)"
//)
//{
//	const char* printed_message = "The word 'apple' consists of 5
// characters.\n";
//
//	auto const length = strlen(printed_message);
//
//	char buffer[512];
//
//	auto const formatted_string_length = snprintf(buffer, sizeof(buffer) /
// sizeof(buffer[0]), 	                                              "The word
// '%s' consists of %d characters.\n", "apple", 5);
//
//	auto const ret_val = say_slow(5, "The word '%s' consists of %d
// characters.\n", "apple", 5);
//
//	REQUIRE(length == formatted_string_length);
//
//	REQUIRE(length == ret_val);
//}
//
// TEST_CASE("int say_slow(const size_t, const wchar_t*, Args...)",
//	"Testing correct work of global template function int say_slow(const
// size_t time_delay_in_ms, const wchar_t* format_string, Args... args)"
//)
//{
//	const wchar_t* printed_message = L"The word 'apple' consists of 5
// characters.\n";
//
//	auto const length = wcslen(printed_message);
//
//	wchar_t buffer[512];
//
//	auto const formatted_string_length = _snwprintf(buffer, sizeof(buffer) /
// sizeof(buffer[0]), 	                                                L"The
// word '%s' consists of %d characters.\n", L"apple", 5);
//
//	auto const ret_val = say_slow(5, L"The word '%s' consists of %d
// characters.\n", L"apple", 5);
//
//	REQUIRE(length == formatted_string_length);
//
//	REQUIRE(length == ret_val);
//}
//
// TEST_CASE("int say(const char* format_string, Args... args)",
//	"Testing correct work of global template function int say(const char*
// format_string, Args... args)")
//{
//	const char* printed_message = "The word 'apple' consists of 5
// characters.\n";
//
//	auto const length = strlen(printed_message);
//
//	char buffer[512];
//
//	auto const formatted_string_length = snprintf(buffer, sizeof(buffer) /
// sizeof(buffer[0]), 	                                              "The word
// '%s' consists of %d characters.\n", "apple", 5);
//
//	auto const ret_val = say("The word '%s' consists of %d characters.\n",
//"apple", 5);
//
//	REQUIRE(length == formatted_string_length);
//
//	REQUIRE(length == ret_val);
//}
//
// TEST_CASE("int say(const wchar_t* format_string, Args... args)",
//	"Testing correct work of global template function int say(const wchar_t*
// format_string, Args... args)")
//{
//	const wchar_t* printed_message = L"The word 'apple' consists of 5
// characters.\n";
//
//	auto const length = wcslen(printed_message);
//
//	wchar_t buffer[512];
//
//	auto const formatted_string_length = _snwprintf(buffer, sizeof(buffer) /
// sizeof(buffer[0]), 	                                                L"The
// word '%s' consists of %d characters.\n", L"apple", 5);
//
//	auto const ret_val = say(L"The word '%s' consists of %d characters.\n",
// L"apple", 5);
//
//	REQUIRE(length == formatted_string_length);
//
//	REQUIRE(length == ret_val);
//}

TEST_CASE(
    "size_t len(T src, const size_t max_allowed_string_length = "
    "max_string_length)",
    "Testing global function len)") {
  const char* src1 = "Hello World!\n";
  REQUIRE(len(src1) == strlen(src1));

  const wchar_t* src2 = L"\tHello there, my friend!\n";
  REQUIRE(len(src2) == wcslen(src2));

  const char16_t* src3 = u"\tHello there, my friend!\n";
  u16string src3_str{src3};
  REQUIRE(len(src3) == src3_str.length());

  const char32_t* src4 = U"\tHello there, my friend!\n";
  u32string src4_str{src4};
  REQUIRE(len(src4) == src4_str.length());

  string src5{"Hello World!\n"};
  REQUIRE(len(src5) == src5.length());

  wstring src6{L"\tHello there, my friend!\n"};
  REQUIRE(len(src6) == src6.length());

  u16string src7{u"Hello World!\n"};
  REQUIRE(len(src7) == src7.length());

  u32string src8{U"\tHello there, my friend!\n"};
  REQUIRE(len(src8) == src8.length());
}

TEST_CASE("bool trim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool trim_in_place(CharPointerType "
          "mutable_char_buffer)") {
  char char_buffer[64] = "\t Hello World!\t \n";

  const char* char_str = "Hello World!";

  REQUIRE(trim_in_place(char_buffer));

  REQUIRE(strcmp(char_buffer, char_str) == 0);

  wchar_t wchar_t_buffer[64] = L" \t Hello World!\t \n";

  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(trim_in_place(wchar_t_buffer));

  REQUIRE(wcscmp(wchar_t_buffer, wchar_t_str) == 0);

  char16_t char16_t_buffer[64] = u" \t Hello World!\t \n";

  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(trim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);

  char32_t char32_t_buffer[64] = U" \t Hello World!\t \n";

  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(trim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
}

TEST_CASE("bool ltrim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool "
          "ltrim_in_place(CharPointerType mutable_char_buffer)") {
  char char_buffer[64] = "\t Hello World!";

  const char* char_str = "Hello World!";

  REQUIRE(ltrim_in_place(char_buffer));

  REQUIRE(strcmp(char_buffer, char_str) == 0);

  wchar_t wchar_t_buffer[64] = L" \t Hello World!";

  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(ltrim_in_place(wchar_t_buffer));

  REQUIRE(wcscmp(wchar_t_buffer, wchar_t_str) == 0);

  char16_t char16_t_buffer[64] = u" \t Hello World!";

  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(ltrim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);

  char32_t char32_t_buffer[64] = U" \t Hello World!";

  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(ltrim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
}

TEST_CASE("bool rtrim_in_place(CharPointerType mutable_char_buffer)",
          "Testing global function template bool "
          "rtrim_in_place(CharPointerType mutable_char_buffer)") {
  char char_buffer[64] = "Hello World!\t\n";

  const char* char_str = "Hello World!";

  REQUIRE(rtrim_in_place(char_buffer));

  REQUIRE(strcmp(char_buffer, char_str) == 0);

  wchar_t wchar_t_buffer[64] = L"Hello World!\t\n";

  const wchar_t* wchar_t_str = L"Hello World!";

  REQUIRE(rtrim_in_place(wchar_t_buffer));

  REQUIRE(wcscmp(wchar_t_buffer, wchar_t_str) == 0);

  char16_t char16_t_buffer[64] = u"Hello World!\t\n";

  const char16_t* char16_t_str = u"Hello World!";

  REQUIRE(rtrim_in_place(char16_t_buffer));

  u16string src_u16string{char16_t_buffer};
  u16string dst_u16string{char16_t_str};

  REQUIRE(src_u16string == dst_u16string);

  char32_t char32_t_buffer[64] = U"Hello World!\t\n";

  const char32_t* char32_t_str_dst = U"Hello World!";

  REQUIRE(rtrim_in_place(char32_t_buffer));

  u32string src_u32string{char32_t_buffer};
  u32string dst_u32string{char32_t_str_dst};

  REQUIRE(src_u32string == dst_u32string);
}

TEST_CASE("auto trim(ConstCharPointerType src)",
          "Testing global function auto trim(ConstCharPointerType src)") {
  const char* src_char = " \t Hello World!\t \n";

  const string src_string{" \t Hello World!\t \n"};

  const string dst_string{"Hello World!"};

  string output_string{trim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = trim(src_string);

  REQUIRE(output_string == dst_string);

  const wchar_t* src_wchar_t = L" \t Hello World!\t \n";

  const wstring src_wstring{L" \t Hello World!\t \n"};

  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{trim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = trim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);

  const char16_t* src_char16_t = u" \t Hello World!\t \n";

  const u16string src_u16string{u" \t Hello World!\t \n"};

  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{trim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = trim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);

  const char32_t* src_char32_t = U" \t Hello World!\t \n";

  const u32string src_u32string{U" \t Hello World!\t \n"};

  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{trim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = trim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
}

TEST_CASE("auto ltrim(ConstCharPointerType src)",
          "Testing global function auto ltrim(ConstCharPointerType src)") {
  const char* src_char = " \t Hello World!";

  const string src_string{" \t Hello World!"};

  const string dst_string{"Hello World!"};

  string output_string{ltrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = ltrim(src_string);

  REQUIRE(output_string == dst_string);

  const wchar_t* src_wchar_t = L" \t Hello World!";

  const wstring src_wstring{L" \t Hello World!"};

  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{ltrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = ltrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);

  const char16_t* src_char16_t = u" \t Hello World!";

  const u16string src_u16string{u" \t Hello World!"};

  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{ltrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = ltrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);

  const char32_t* src_char32_t = U" \t Hello World!";

  const u32string src_u32string{U" \t Hello World!"};

  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{ltrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = ltrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
}

TEST_CASE("auto rtrim(ConstCharPointerType src)",
          "Testing global function auto rtrim(ConstCharPointerType src)") {
  const char* src_char = "Hello World!\t \n";

  const string src_string{"Hello World!\t \n"};

  const string dst_string{"Hello World!"};

  string output_string{rtrim(src_char)};

  REQUIRE(output_string == dst_string);

  output_string = rtrim(src_string);

  REQUIRE(output_string == dst_string);

  const wchar_t* src_wchar_t = L"Hello World!\t \n";

  const wstring src_wstring{L"Hello World!\t \n"};

  const wstring dst_wstring{L"Hello World!"};

  wstring output_wstring{rtrim(src_wchar_t)};

  REQUIRE(output_wstring == dst_wstring);

  output_wstring = rtrim(src_wstring);

  REQUIRE(output_wstring == dst_wstring);

  const char16_t* src_char16_t = u"Hello World!\t \n";

  const u16string src_u16string{u"Hello World!\t \n"};

  const u16string dst_u16string{u"Hello World!"};

  u16string output_u16string{rtrim(src_char16_t)};

  REQUIRE(output_u16string == dst_u16string);

  output_u16string = rtrim(src_u16string);

  REQUIRE(output_u16string == dst_u16string);

  const char32_t* src_char32_t = U"Hello World!\t \n";

  const u32string src_u32string{U"Hello World!\t \n"};

  const u32string dst_u32string{U"Hello World!"};

  u32string output_u32string{rtrim(src_char32_t)};

  REQUIRE(output_u32string == dst_u32string);

  output_u32string = rtrim(src_u32string);

  REQUIRE(output_u32string == dst_u32string);
}

// TEST_CASE("int u16_strcmp(const char16_t* str1, const char16_t* str2)",
//	"Testing global function int u16_strcmp(const char16_t* str1, const
// char16_t* str2)")
//{
//
//	const char16_t* str1 = u"apple";
//	const char16_t* str2 = u"apple";
//
//	REQUIRE(str_compare(str1, str2) == 0);
//
//	REQUIRE(str_compare(u16string(u"apple"), u16string(u"banana")) < 0);
//}
//
// TEST_CASE("int u32_strcmp(const char32_t* str1, const char32_t* str2)",
//	"Testing global function int u32_strcmp(const char32_t* str1, const
// char32_t* str2)")
//{
//	REQUIRE(str_compare(U"apple", U"apple") == 0);
//
//	REQUIRE(str_compare(U"apple", U"banana") < 0);
//}

// TEST_CASE("int u16_strncmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare)", 	"Testing global function int
// u16_strncmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare)"
//)
//{
//	REQUIRE(str_compare_n(u"apple", u"appLE", 3) == 0);
//
//	REQUIRE(str_compare_n(u"apple", u"banana", 3) < 0);
//}
//
// TEST_CASE("int u32_strncmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare)", 	"Testing global function int
// u32_strncmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare)"
//)
//{
//	REQUIRE(str_compare_n(U"apple", U"appLE", 3) == 0);
//
//	REQUIRE(str_compare_n(U"apple", U"banana", 3) < 0);
//}
//
// TEST_CASE("int u16_stricmp(const char16_t* str1, const char16_t* str2, const
// std::locale& loc = std::locale{})", 	"Testing global function int
// u16_stricmp(const char16_t* str1, const char16_t* str2, const std::locale&
// loc = std::locale{})"
//)
//{
//	REQUIRE(str_compare_i(u"apple", u"apple") == 0);
//
//	REQUIRE(str_compare_i(u"apple", u"banana") < 0);
//}
//
// TEST_CASE("int u32_stricmp(const char32_t* str1, const char32_t* str2, const
// std::locale& loc = std::locale{})", 	"Testing global function int
// u32_stricmp(const char32_t* str1, const char32_t* str2, const std::locale&
// loc = std::locale{})"
//)
//{
//	REQUIRE(str_compare_i(U"apple", U"apple") == 0);
//
//	REQUIRE(str_compare_i(U"apple", U"banana") < 0);
//}
//
// TEST_CASE(
//	"int u16_strnicmp(const char16_t* str1, const char16_t* str2, size_t
// number_of_characters_to_compare, const std::locale& loc = std::locale{})"
//	,
//	"Testing global function int u16_strnicmp(const char16_t* str1, const
// char16_t* str2, size_t number_of_characters_to_compare, const std::locale&
// loc = std::locale{})"
//)
//{
//	REQUIRE(str_compare_n_i(u"apple", u"apple", 3) == 0);
//
//	REQUIRE(str_compare_n_i(u"apple", u"banana", 3) < 0);
//}
//
// TEST_CASE(
//	"int u32_strnicmp(const char32_t* str1, const char32_t* str2, size_t
// number_of_characters_to_compare, const std::locale& loc = std::locale{})"
//	,
//	"Testing global function int u32_strnicmp(const char32_t* str1, const
// char32_t* str2, size_t number_of_characters_to_compare, const std::locale&
// loc = std::locale{})"
//)
//{
//	REQUIRE(str_compare_n_i(U"apple", U"apple", 3) == 0);
//
//	REQUIRE(str_compare_n_i(U"apple", U"banana", 3) < 0);
//}

/*
TEST_CASE("char16_t* u16_strcpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)", "Testing global
function char16_t* u16_strcpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)"
)
{
                char16_t src[128];

                char16_t dst[64] = u"\tHello World!\n";

                REQUIRE(trim(dst));

                REQUIRE(str_copy(src, sizeof(src)/sizeof(src[0]), dst) !=
nullptr);

                REQUIRE(str_compare(src, u"Hello World!") == 0);
}

TEST_CASE("char32_t* u32_strcpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)", "Testing global
function char32_t* u32_strcpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)"
)
{
                char32_t src[128];

                char32_t dst[64] = U"\tHello World!\n";

                REQUIRE(trim(dst));

                REQUIRE(u32_strcpy(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

                REQUIRE(u32_strcmp(src, U"Hello World!") == 0);
}

TEST_CASE(
                "char16_t* u16_strncpy(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src, const size_t
number_of_characters_to_copy)"
                ,
                "Testing global function char16_t* u16_strncpy(char16_t* dst,
const size_t dst_capacity_in_number_of_characters, const char16_t* src, const
size_t number_of_characters_to_copy)"
)
{
                char16_t src[128];

                char16_t dst[64] = u"\tHello World!\n";

                REQUIRE(trim(dst));

                REQUIRE(u16_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5)
!= nullptr);

                REQUIRE(u16_strncmp(src, u"Hello World!", 5) == 0);
}

TEST_CASE(
                "char32_t* u32_strncpy(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src, const size_t
number_of_characters_to_copy)"
                ,
                "Testing global function char32_t* u32_strncpy(char32_t* dst,
const size_t dst_capacity_in_number_of_characters, const char32_t* src, const
size_t number_of_characters_to_copy)"
)
{
                char32_t src[128];

                char32_t dst[64] = U"\tHello World!\n";

                REQUIRE(trim(dst));

                REQUIRE(u32_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5)
!= nullptr);

                REQUIRE(u32_strncmp(src, U"Hello World!", 5) == 0);
}

TEST_CASE("char16_t* u16_strcat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)", "Testing global
function char16_t* u16_strcat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)"
)
{
                char16_t src[512] = u" \t Hello World!\t \n";

                const char16_t* dst = u" How are you today?";

                REQUIRE(trim(src));

                REQUIRE(u16_strcat(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

                REQUIRE(u16_strcmp(src, u"Hello World! How are you today?") ==
0);
}

TEST_CASE("char32_t* u32_strcat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)", "Testing global
function char32_t* u32_strcat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)"
)
{
                char32_t src[512] = U" \t Hello World!\t \n";

                const char32_t* dst = U" How are you today?";

                REQUIRE(trim(src));

                REQUIRE(u32_strcat(src, sizeof(src) / sizeof(src[0]), dst) !=
nullptr);

                REQUIRE(u32_strcmp(src, U"Hello World! How are you today?") ==
0);
}

TEST_CASE(
                "char16_t* u16_strncat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src, const size_t
number_of_characters_to_concatenate)"
                ,
                "Testing global function char16_t* u16_strncat(char16_t* dst,
const size_t dst_capacity_in_number_of_characters, const char16_t* src, const
size_t number_of_characters_to_concatenate)"
)
{
                char16_t src[512] = u" \t Hello World!\t \n";

                const char16_t* dst = u" How are you today?";

                REQUIRE(trim(src));

                REQUIRE(u16_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4)
!= nullptr);

                REQUIRE(u16_strcmp(src, u"Hello World! How") == 0);
}

TEST_CASE(
                "char32_t* u32_strncat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src, const size_t
number_of_characters_to_concatenate)"
                ,
                "Testing global function char32_t* u32_strncat(char32_t* dst,
const size_t dst_capacity_in_number_of_characters, const char32_t* src, const
size_t number_of_characters_to_concatenate)"
)
{
                char32_t src[512] = U" \t Hello World!\t \n";

                const char32_t* dst = U" How are you today?";

                REQUIRE(trim(src));

                REQUIRE(u32_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4)
!= nullptr);

                REQUIRE(u32_strcmp(src, U"Hello World! How") == 0);
}

TEST_CASE("const char16_t* u16_strstr(const char16_t* src, const char16_t*
needle)", "Testing global function const char16_t* u16_strstr(const char16_t*
src, const char16_t* needle)")
{
                const char16_t* src = u"Hello World! How are you today?";

                const char16_t* needle = u"today";

                REQUIRE(u16_strstr(src, needle) != nullptr);
}

TEST_CASE("const char32_t* u32_strstr(const char32_t* src, const char32_t*
needle)", "Testing global function const char32_t* u32_strstr(const char32_t*
src, const char32_t* needle)")
{
                const char32_t* src = U"Hello World! How are you today?";

                const char32_t* needle = U"today";

                REQUIRE(u32_strstr(src, needle) != nullptr);
}

TEST_CASE("char16_t* u16_strstr(char16_t* src, const char16_t* needle)",
                "Testing global function char16_t* u16_strstr(char16_t* src,
const char16_t* needle)")
{
                char16_t src[512] = u" \t Hello World!\t \n";

                const char16_t* dst = u"World";

                REQUIRE(trim(src));

                REQUIRE(u16_strstr(src, dst) != nullptr);
}

TEST_CASE("char32_t* u32_strstr(char32_t* src, const char32_t* needle)",
                "Testing global function char32_t* u32_strstr(char32_t* src,
const char32_t* needle)")
{
                char32_t src[512] = U" \t Hello World!\t \n";

                const char32_t* dst = U"World";

                REQUIRE(trim(src));

                REQUIRE(u32_strstr(src, dst) != nullptr);
}

TEST_CASE(
                "const char16_t* u16_strstri(const char16_t* src, const
char16_t* needle, const std::locale& loc = std::locale{})", "Testing global
function const char16_t* u16_strstri(const char16_t* src, const char16_t*
needle, const std::locale& loc = std::locale{})"
)
{
                const char16_t* src = u"Hello World! How are you TODAY?";

                const char16_t* needle = u"today";

                REQUIRE(u16_strstri(src, needle) != nullptr);
}

TEST_CASE(
                "const char32_t* u32_strstri(const char32_t* src, const
char32_t* needle, const std::locale& loc = std::locale{})", "Testing global
function const char32_t* u32_strstri(const char32_t* src, const char32_t*
needle, const std::locale& loc = std::locale{})"
)
{
                const char32_t* src = U"Hello World! How are you TODAY?";

                const char32_t* needle = U"today";

                REQUIRE(u32_strstri(src, needle) != nullptr);
}

TEST_CASE("char16_t* u16_strstri(char16_t* src, const char16_t* needle, const
std::locale& loc = std::locale{})", "Testing global function char16_t*
u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc =
std::locale{})"
)
{
                char16_t src[512] = u" \t Hello World!\t \n";

                const char16_t* dst = u"Hello World!";

                REQUIRE(trim(src));

                REQUIRE(u16_strstri(src, dst) != nullptr);
}

TEST_CASE("char32_t* u32_strstri(char32_t* src, const char32_t* needle, const
std::locale& loc = std::locale{})", "Testing global function char32_t*
u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc =
std::locale{})"
)
{
                char32_t src[512] = U" \t Hello World!\t \n";

                const char32_t* dst = U"Hello World!";

                REQUIRE(trim(src));

                REQUIRE(u32_strstri(src, dst) != nullptr);
}

TEST_CASE("StringType trim(const StringType& str)",
                "Testing global template function StringType trim(const
StringType& str)")
{
                const string src{"\t Hello World!\t \n"};

                const string dst{trim(src)};

                REQUIRE(dst == string{ "Hello World!" });
}

TEST_CASE("StringType ltrim(const StringType& str)",
                "Testing global template function StringType ltrim(const
StringType& str)")
{
                const wstring src{L"\t Hello World!\t \n"};

                const wstring dst{ltrim(src)};

                REQUIRE(dst == wstring{ L"Hello World!\t \n" });
}

TEST_CASE("StringType rtrim(const StringType& str)",
                "Testing global template function StringType rtrim(const
StringType& str)")
{
                const u32string src{U"\t Hello World!\t \n"};

                const u32string dst{rtrim(src)};

                REQUIRE(dst == u32string{ U"\t Hello World!" });
}

TEST_CASE("vector<string> split(const char* source, const char needle_char, int
const max_count = -1)", "Testing global function vector<std::string> split(const
char* source, const char needle_char, int const max_count = -1)"
)
{
                const char*
source{"apple|banana|cabbage|lemon|orange|pepper|plum"};

                const char needle_char{'|'};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == "apple");

                REQUIRE(parts[3] == "lemon");

                REQUIRE(parts.back() == "plum");
}

TEST_CASE("vector<wstring> split(const wchar_t* source, const wchar_t
needle_char, int const max_count = -1)", "Testing global function
vector<wstring> split(const wchar_t* source, const wchar_t needle_char, int
const max_count = -1)"
)
{
                const wchar_t*
source{L"apple|banana|cabbage|lemon|orange|pepper|plum"};

                const wchar_t needle_char{L'|'};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == L"apple");

                REQUIRE(parts[3] == L"lemon");

                REQUIRE(parts.back() == L"plum");
}

TEST_CASE("vector<u16string> split(const char16_t* source, const char16_t
needle_char, int const max_count = -1)", "Testing global function
vector<u16string> split(const char16_t* source, const char16_t needle_char, int
const max_count = -1)"
)
{
                const char16_t*
source{u"apple|banana|cabbage|lemon|orange|pepper|plum"};

                const char16_t needle_char{u'|'};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == u"apple");

                REQUIRE(parts[3] == u"lemon");

                REQUIRE(parts.back() == u"plum");
}

TEST_CASE("vector<u32string> split(const char32_t* source, const char32_t
needle_char, int const max_count = -1)", "Testing global function
vector<u32string> split(const char32_t* source, const char32_t needle_char, int
const max_count = -1)"
)
{
                const char32_t*
source{U"apple|banana|cabbage|lemon|orange|pepper|plum"};

                const char32_t needle_char{U'|'};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == U"apple");

                REQUIRE(parts[3] == U"lemon");

                REQUIRE(parts.back() == U"plum");
}

TEST_CASE("vector<string> split(const char* source, const char* needle, const
int max_count = -1)", "Testing global function vector<string> split(const char*
source, const char* needle, const int max_count = -1)")
{
                const char*
source{"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                const char* needle_char{":|:"};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == "apple");

                REQUIRE(parts[3] == "lemon");

                REQUIRE(parts.back() == "plum");
}

TEST_CASE("vector<wstring> split(const wchar_t* source, const wchar_t* needle,
const int max_count = -1)", "Testing global function vector<wstring> split(const
wchar_t* source, const wchar_t* needle, const int max_count = -1)"
)
{
                const wchar_t*
source{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                const wchar_t* needle_char{L":|:"};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == L"apple");

                REQUIRE(parts[3] == L"lemon");

                REQUIRE(parts.back() == L"plum");
}

TEST_CASE("vector<u16string> split(const char16_t* source, const char16_t*
needle, const int max_count = -1)", "Testing global function vector<u16string>
split(const char16_t* source, const char16_t* needle, const int max_count = -1)"
)
{
                const char16_t*
source{u"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                const char16_t* needle_char{u":|:"};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == u"apple");

                REQUIRE(parts[3] == u"lemon");

                REQUIRE(parts.back() == u"plum");
}

TEST_CASE("vector<u32string> split(const char32_t* source, const char32_t*
needle, const int max_count = -1)", "Testing global function vector<u32string>
split(const char32_t* source, const char32_t* needle, const int max_count = -1)"
)
{
                const char32_t*
source{U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                const char32_t* needle_char{U":|:"};

                auto const parts{split(source, needle_char)};

                REQUIRE(parts.front() == U"apple");

                REQUIRE(parts[3] == U"lemon");

                REQUIRE(parts.back() == U"plum");
}

TEST_CASE(
                "vector<StringType> split(const StringType& source, const
typename StringType::value_type needle_char, size_t const max_count =
StringType::npos)"
                ,
                "Testing global template function vector<StringType> split(const
StringType& source, const typename StringType::value_type needle_char, size_t
const max_count = StringType::npos)"
)
{
                const wstring src{L"apple | banana | cabbage | lemon | orange |
pepper | plum"};

                auto parts{split(src, L'|')};

                for (auto& part : parts) part = trim(part);

                REQUIRE(parts.front() == L"apple");

                REQUIRE(parts[3] == L"lemon");

                REQUIRE(parts.back() == L"plum");
}

TEST_CASE(
                "vector<StringType> split(const StringType& source, const
typename StringType::const_pointer_type needle, size_t const max_count =
StringType::npos)"
                ,
                "Testing global template function vector<StringType> split(const
StringType& source, const typename StringType::const_pointer_type needle, size_t
const max_count = StringType::npos)"
)
{
                const u16string
src{u"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                auto parts{split(src, u":|:")};

                REQUIRE(parts.front() == u"apple");

                REQUIRE(parts[3] == u"lemon");

                REQUIRE(parts.back() == u"plum");
}

TEST_CASE(
                "vector<StringType> split(const StringType& source, const
StringType& needle, size_t const max_count = StringType::npos)"
                ,
                "Testing global template function vector<StringType> split(const
StringType& source, const StringType& needle, size_t const max_count =
StringType::npos)"
)
{
                const u32string
src{U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};

                const u32string needle{U":|:"};

                auto parts{split(src, needle)};

                REQUIRE(parts.front() == U"apple");

                REQUIRE(parts[3] == U"lemon");

                REQUIRE(parts.back() == U"plum");
}
*/

TEST_CASE(
    "bool str_starts_with(T, const U, const bool = false, const std::locale& = "
    "std::locale{})",
    "Testing global function template bool str_starts_with(T src, const U "
    "needle, const bool ignore_case = false, const std::locale& loc = "
    "std::locale{})") {
  const char* src_cstr{"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_cstr, "Apple"));

  REQUIRE(str_starts_with(src_cstr, "apPLE", true));

  REQUIRE(str_starts_with(src_cstr, 'A'));

  REQUIRE(str_starts_with(src_cstr, 'a', true));

  const wchar_t* src_wcstr{L"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_wcstr, L"Apple"));

  REQUIRE(str_starts_with(src_wcstr, L"apPLE", true));

  REQUIRE(str_starts_with(src_wcstr, L'A'));

  REQUIRE(str_starts_with(src_wcstr, L'a', true));

  const char16_t* src_u16cstr{
      u"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u16cstr, u"Apple"));

  REQUIRE(str_starts_with(src_u16cstr, u"apPLE", true));

  REQUIRE(str_starts_with(src_u16cstr, u'A'));

  REQUIRE(str_starts_with(src_u16cstr, u'a', true));

  const char32_t* src_u32cstr{
      U"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u32cstr, U"Apple"));

  REQUIRE(str_starts_with(src_u32cstr, U"apPLE", true));

  REQUIRE(str_starts_with(src_u32cstr, U'A'));

  REQUIRE(str_starts_with(src_u32cstr, U'a', true));
}

TEST_CASE(
    "bool str_starts_with(const StringType&, const typename "
    "StringType::value_type, const bool = false, const std::locale& = "
    "std::locale{})",
    "Testing global function template bool str_starts_with(const StringType& src, const typename StringType::value_type start_char,\
		                     const bool ignore_case = false,\
		                     const std::locale& loc = std::locale{})") {
  const string src_string{"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_string, 'A'));

  REQUIRE(str_starts_with(src_string, 'a', true));

  const wstring src_wstring{L"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_wstring, L'A'));

  REQUIRE(str_starts_with(src_wstring, L'a', true));

  const u16string src_u16string{
      u"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u16string, u'A'));

  REQUIRE(str_starts_with(src_u16string, u'a', true));

  const u32string src_u32string{
      U"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u32string, U'A'));

  REQUIRE(str_starts_with(src_u32string, U'a', true));
}

TEST_CASE(
    "bool str_starts_with(const StringType&, typename "
    "StringType::const_pointer, const bool = false, const std::locale& = "
    "std::locale{})",
    "Testing global function template bool str_starts_with(const StringType& "
    "src, typename StringType::const_pointer start_tag, const bool ignore_case "
    "= false, const std::locale& loc = std::locale{})") {
  const string src_string{"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_string, "Apple"));

  REQUIRE(str_starts_with(src_string, "aPPLE", true));

  const wstring src_wstring{L"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_wstring, L"Apple"));

  REQUIRE(str_starts_with(src_wstring, L"aPPLE", true));

  const u16string src_u16string{
      u"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u16string, u"Apple"));

  REQUIRE(str_starts_with(src_u16string, u"aPPLE", true));

  const u32string src_u32string{
      U"Apple is one my favorite, most beloved fruits."};

  REQUIRE(str_starts_with(src_u32string, U"Apple"));

  REQUIRE(str_starts_with(src_u32string, U"aPPLE", true));
}

TEST_CASE(
    "bool str_starts_with(const StringType&, const StringType&, const bool = "
    "false, const std::locale& = std::locale{})",
    "bool str_starts_with(const StringType& src, const StringType& start_tag, "
    "const bool ignore_case = false, const std::locale& loc = std::locale{})") {
  const string src_string{"Apple is one my favorite, most beloved fruits."};

  const string needle_string{"Apple"};

  REQUIRE(str_starts_with(src_string, needle_string));

  REQUIRE(str_starts_with(src_string, string{"aPPLE"}, true));

  const wstring src_wstring{L"Apple is one my favorite, most beloved fruits."};

  const wstring needle_wstring{L"Apple"};

  REQUIRE(str_starts_with(src_wstring, needle_wstring));

  REQUIRE(str_starts_with(src_wstring, wstring{L"aPPLE"}, true));

  const u16string src_u16string{
      u"Apple is one my favorite, most beloved fruits."};

  const u16string needle_u16string{u"Apple"};

  REQUIRE(str_starts_with(src_u16string, needle_u16string));

  REQUIRE(str_starts_with(src_u16string, u16string{u"aPPLE"}, true));

  const u32string src_u32string{
      U"Apple is one my favorite, most beloved fruits."};

  const u32string needle_u32string{U"Apple"};

  REQUIRE(str_starts_with(src_u32string, needle_u32string));

  REQUIRE(str_starts_with(src_u32string, u32string{U"aPPLE"}, true));
}

TEST_CASE(
    "auto str_index_of(T, const U, const size_t = 0u, const bool = false, "
    "const std::locale& = std::locale{})",
    "Testing global function template auto str_index_of(T src, const U needle, "
    "const size_t start_pos = 0u, const bool ignore_case = false, const "
    "std::locale& loc = std::locale{})") {
  const char* src_cstr{"Hello World!"};

  REQUIRE(6u == str_index_of(src_cstr, "World"));

  REQUIRE(6u == str_index_of(src_cstr, "world", 0u, true));

  REQUIRE(6u == str_index_of("Hello World!", "World"));

  REQUIRE(6u == str_index_of("Hello World!", "world", 0u, true));

  REQUIRE(6u == str_index_of(src_cstr, 'W'));

  REQUIRE(6u == str_index_of(src_cstr, 'w', 0u, true));

  const wchar_t* src_wcstr{L"Hello World!"};

  REQUIRE(6u == str_index_of(src_wcstr, L"World"));

  REQUIRE(6u == str_index_of(src_wcstr, L"world", 0u, true));

  REQUIRE(6u == str_index_of(L"Hello World!", L"World"));

  REQUIRE(6u == str_index_of(L"Hello World!", L"world", 0u, true));

  REQUIRE(6u == str_index_of(src_wcstr, L'W'));

  REQUIRE(6u == str_index_of(src_wcstr, L'w', 0u, true));

  const char16_t* src_u16cstr{u"Hello World!"};

  REQUIRE(6u == str_index_of(src_u16cstr, u"World"));

  REQUIRE(6u == str_index_of(src_u16cstr, u"world", 0u, true));

  REQUIRE(6u == str_index_of(u"Hello World!", u"World"));

  REQUIRE(6u == str_index_of(u"Hello World!", u"world", 0u, true));

  REQUIRE(6u == str_index_of(src_u16cstr, u'W'));

  REQUIRE(6u == str_index_of(src_u16cstr, u'w', 0u, true));

  const char32_t* src_u32cstr{U"Hello World!"};

  REQUIRE(6u == str_index_of(src_u32cstr, U"World"));

  REQUIRE(6u == str_index_of(src_u32cstr, U"world", 0u, true));

  REQUIRE(6u == str_index_of(U"Hello World!", U"World"));

  REQUIRE(6u == str_index_of(U"Hello World!", U"world", 0u, true));

  REQUIRE(6u == str_index_of(src_u32cstr, U'W'));

  REQUIRE(6u == str_index_of(src_u32cstr, U'w', 0u, true));
}

TEST_CASE("bool has_key(const ContainerType& container,const KeyType& key)",
          "Testing global function template bool has_key(const ContainerType& "
          "container,const KeyType& key)") {
  set<int> unique_numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_set<int> unique_numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multiset<int> numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_multiset<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_key(unique_numbers1, 5));
  REQUIRE(!has_key(unique_numbers1, 15));
  REQUIRE(has_key(unique_numbers2, 5));
  REQUIRE(!has_key(unique_numbers2, 15));

  REQUIRE(has_key(unique_number_labels1, "five"));
  REQUIRE(!has_key(unique_number_labels1, "fifteen"));
  REQUIRE(has_key(unique_number_labels2, "five"));
  REQUIRE(!has_key(unique_number_labels2, "fifteen"));

  REQUIRE(has_key(numbers1, 5));
  REQUIRE(!has_key(numbers1, 15));
  REQUIRE(has_key(numbers2, 5));
  REQUIRE(!has_key(numbers2, 15));

  REQUIRE(has_key(number_labels1, "five"));
  REQUIRE(!has_key(number_labels1, "fifteen"));
  REQUIRE(has_key(number_labels2, "five"));
  REQUIRE(!has_key(number_labels2, "fifteen"));
}

TEST_CASE(
    "bool has_value(const ContainerType& container, const ValueType& value)",
    "Testing global function template bool has_value(const ContainerType& "
    "container, const ValueType& value)") {
  array<int, 10> ar{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  deque<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  forward_list<int> fl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> dl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  REQUIRE(has_value(ar, 5));
  REQUIRE(!has_value(ar, 15));
  REQUIRE(has_value(v, 5));
  REQUIRE(!has_value(v, 15));
  REQUIRE(has_value(d, 5));
  REQUIRE(!has_value(d, 15));
  REQUIRE(has_value(fl, 5));
  REQUIRE(!has_value(fl, 15));
  REQUIRE(has_value(dl, 5));
  REQUIRE(!has_value(dl, 15));

  set<int> unique_numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_set<int> unique_numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  map<string, int> unique_number_labels1{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_map<string, int> unique_number_labels2{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  multiset<int> numbers1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unordered_multiset<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multimap<string, int> number_labels1{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};
  unordered_multimap<string, int> number_labels2{
      {"one", 1},   {"two", 2},   {"three", 3}, {"one", 1},  {"five", 5},
      {"three", 3}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10}};

  REQUIRE(has_value(unique_numbers1, 5));
  REQUIRE(!has_value(unique_numbers1, 15));
  REQUIRE(has_value(unique_numbers2, 5));
  REQUIRE(!has_value(unique_numbers2, 15));

  REQUIRE(has_value(unique_number_labels1, 5));
  REQUIRE(!has_value(unique_number_labels1, 15));
  REQUIRE(has_value(unique_number_labels2, 5));
  REQUIRE(!has_value(unique_number_labels2, 15));

  REQUIRE(has_value(numbers1, 5));
  REQUIRE(!has_value(numbers1, 15));
  REQUIRE(has_value(numbers2, 5));
  REQUIRE(!has_value(numbers2, 15));

  REQUIRE(has_value(number_labels1, 5));
  REQUIRE(!has_value(number_labels1, 15));
  REQUIRE(has_value(number_labels2, 5));
  REQUIRE(!has_value(number_labels2, 15));
}

TEST_CASE(
    "bool has_item(ForwardIterType first, ForwardIterType last, ValueType&& "
    "value)",
    "Testing global function template bool has_value(ForwardIterType first, "
    "ForwardIterType last, ValueType&& value)") {
  array<int, 10> ar{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  deque<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  forward_list<int> fl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> dl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

// TEST_CASE(
//		"typename StringType::size_type index_of(const StringType& text,
// const typename StringType::value_type needle_char, const size_t start_pos =
// 0u, bool ignore_case = false,\ const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function typename StringType::size_type
// index_of(const StringType& text, const typename StringType::value_type
// needle_char, const size_t start_pos = 0u, bool ignore_case = false,\ const
// std::locale& loc = std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		wstring::size_type correct_index = src.find(L'b');
//
//		REQUIRE(index_of(src, L'b') == correct_index);
//
//		correct_index = src.find(L'b');
//
//		REQUIRE(index_of(src, L'B', 0, true) == correct_index);
//}
//
// TEST_CASE(
//		"typename StringType::size_type index_of(const StringType& text,
// const typename StringType::const_pointer needle, const size_t start_pos = 0u,
// bool ignore_case = false,\ const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function typename StringType::size_type
// index_of(const StringType& text, const typename StringType::const_pointer
// needle, const size_t start_pos = 0u, bool ignore_case = false,\ const
// std::locale& loc = std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		wstring::size_type correct_index = src.find(L"banana");
//
//		REQUIRE(index_of(src, L"banana") == correct_index);
//
//		correct_index = src.find(L"cabbage");
//
//		REQUIRE(index_of(src, L"CaBbaGE", 0, true) == correct_index);
//}
//
// TEST_CASE(
//		"typename StringType::size_type index_of(const StringType& text,
// const StringType& needle, bool ignore_case = false, const std::locale& loc =
// std::locale{})"
//		,
//		"Testing global template function typename StringType::size_type
// index_of(const StringType& text, const StringType& needle, bool ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		const wstring needle{L"banana"};
//
//		wstring::size_type correct_index = src.find(needle);
//
//		REQUIRE(index_of(src, needle) == correct_index);
//
//		correct_index = src.find(L"cabbage");
//
//		REQUIRE(index_of(src, wstring{ L"cabbage" }) == correct_index);
//
//		REQUIRE(index_of(src, wstring{ L"CaBbaGe" }, 0, true) ==
// correct_index);
//}
//
// TEST_CASE(
//		"bool contains(const StringType& text, const typename
// StringType::value_type needle_char, const size_t start_pos = 0u, bool
// ignore_case = false, const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function bool contains(const
// StringType& text, const typename StringType::value_type needle_char, const
// size_t
// start_pos = 0u,bool ignore_case = false, const std::locale& loc =
// std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		REQUIRE(contains(src, L'b'));
//
//		REQUIRE(!contains(src, L'x'));
//
//		REQUIRE(contains(src, L'B', 0, true));
//
//		REQUIRE(!contains(src, L'X', 0, true));
//}
//
// TEST_CASE(
//		"bool contains(const StringType& text, typename
// StringType::const_pointer needle, const size_t start_pos = 0u, bool
// ignore_case = false, const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function bool contains(const
// StringType& text, typename StringType::const_pointer needle, const size_t
// start_pos = 0u,
// bool ignore_case = false, const std::locale& loc = std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		REQUIRE(contains(src, L"banana"));
//
//		REQUIRE(contains(src, L"CaBbaGE", 0, true));
//
//		REQUIRE(!contains(src, L"pear"));
//
//		REQUIRE(!contains(src, L"PEAR", 0, true));
//}
//
// TEST_CASE(
//		"bool contains(const StringType& text, const StringType& needle,
// bool ignore_case = false, const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function bool contains(const
// StringType& text, const StringType& needle, bool ignore_case = false, const
// std::locale&
// loc = std::locale{})"
//)
//{
//		const wstring
// src{L"apple,banana,cabbage,lemon,orange,pepper,plum"};
//
//		const wstring needle{L"banana"};
//
//		REQUIRE(contains(src, needle));
//
//		REQUIRE(contains(src, wstring{L"CaBbAgE"}, true));
//
//		REQUIRE(!contains(src, wstring{ L"pear" }));
//}
//
// TEST_CASE(
//		"bool ends_with(const StringType& text, const typename
// StringType::value_type end_char, bool ignore_case = false, const std::locale&
// loc = std::locale{})"
//		,
//		"Testing global template function bool ends_with(const
// StringType& text, const typename StringType::value_type end_char, bool
// ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//		const wstring src{L"Apples"};
//
//		REQUIRE(ends_with(src, L's'));
//
//		REQUIRE(ends_with(src, L'S', true));
//}
//
// TEST_CASE(
//		"bool ends_with(const StringType& src, const typename
// StringType::const_pointer end_tag, bool ignore_case = false, const
// std::locale& loc = std::locale{})"
//		,
//		"Testing global template function bool ends_with(const
// StringType& src, const typename StringType::const_pointer end_tag, bool
// ignore_case =
// false, const std::locale& loc = std::locale{})"
//)
//{
//		const u32string src{U"Apple is one my favorite, most beloved
// fruits."};
//
//		REQUIRE(ends_with(src, U"fruits."));
//
//		REQUIRE(ends_with(src, U"FrUiTs.", true));
//}
//
// TEST_CASE(
//		"bool ends_with(const StringType& src, const StringType&
// end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})"
//		,
//		"Testing global template function bool ends_with(const
// StringType& src, const StringType& end_tag, bool ignore_case = false, const
// std::locale&
// loc = std::locale{})"
//)
//{
//		const u32string src{U"Apple is one my favorite, most beloved
// fruits."};
//
//		const u32string needle{U"fruits."};
//
//		REQUIRE(ends_with(src, needle));
//
//		REQUIRE(ends_with(src, u32string{ U"FrUiTs." }, true));
//}
//
// TEST_CASE("void unused_args(Args&&... args)",
//		"Testing global template function void unused_args(Args&&...
// args)")
//{
//		const int number{42};
//
//		const wchar_t* important_message = L"Number 42 is the meaning of
// life.";
//
//		struct NumberInfo
//		{
//				NumberInfo() : number{42}, message{L"Number 42
// is the meaning of life."}
//				{
//				}
//
//				NumberInfo(const int num, const wchar_t* msg) :
// number{num}, message{msg}
//				{
//				}
//
//				const int number;
//
//				const wchar_t* message;
//		} num_info;
//
//		unused_args(number, important_message, num_info);
//}
//
// TEST_CASE("bool has_key(const map<KeyType, ValueType>& container, const
// typename map<KeyType, ValueType>::key_type& key)", "Testing global template
// function bool has_key(const map<KeyType, ValueType>& container, const
// typename map<KeyType, ValueType>::key_type& key)")
//{
//		const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//		const auto parts{split(src, L':')};
//
//		const map<wstring, size_t> fruit_count = [&]()
//		{
//				map<wstring, size_t> fruits{};
//
//				for (size_t i = 0; i < parts.size(); i += 2)
//				{
//						fruits[parts[i]] = stoul(parts[i
//+ 1]);
//				}
//
//				return fruits;
//		}();
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (fruit_count.find(random_fruit) != cend(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, L"grapefruit"));
//}
//
// TEST_CASE("bool has_key(map<KeyType, ValueType>& container, const typename
// map<KeyType, ValueType>::key_type& key)", "Testing global template function
// bool has_key(map<KeyType, ValueType>& container, const typename map<KeyType,
// ValueType>::key_type& key)")
//{
//		const wstring src{
// L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//		const auto parts{ split(src, L':') };
//
//		auto fruit_count = map<wstring, size_t>{};
//
//		for (size_t i = 0; i < parts.size(); i += 2)
//		{
//				fruit_count[parts[i]] = std::stoul(parts[i +
// 1]);
//		}
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{ rd() };
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//		if (fruit_count.find(random_fruit) != end(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, L"orange"));
//
//		REQUIRE(!has_key(fruit_count, L"grapefruit"));
//}
//
// TEST_CASE("bool has_key(const multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(const multimap<KeyType, ValueType>& container,
// const typename multimap<KeyType, ValueType>::key_type& key)")
//{
//		const wstring
// src{L"apple:10:banana:20:cherries:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//		const auto parts{split(src, L':')};
//
//		const multimap<wstring, size_t> fruit_count = [&]()
//		{
//				multimap<wstring, size_t> fruits{};
//
//				for (size_t i = 0; i < parts.size(); i += 2)
//				{
//						fruits.insert(make_pair(parts[i],
// stoul(parts[i + 1])));
//				}
//
//				return fruits;
//		}();
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (fruit_count.find(random_fruit) != cend(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
// TEST_CASE("bool has_key(multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(multimap<KeyType, ValueType>& container, const
// typename multimap<KeyType, ValueType>::key_type& key)")
//{
//		const wstring src{
// L"apple:10:banana:20:cherries:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//		const auto parts{ split(src, L':') };
//
//
//		auto fruit_count = multimap<wstring, size_t>{};
//
//		for (size_t i = 0; i < parts.size(); i += 2)
//		{
//				fruit_count.insert(make_pair(parts[i],
// stoul(parts[i
//+ 1])));
//		}
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{ rd() };
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//		if (fruit_count.find(random_fruit) != end(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
//
// TEST_CASE("bool has_key(const unordered_map<KeyType, ValueType>& container,
// const typename unordered_map<KeyType, ValueType>::key_type& key)", "Testing
// global template function bool has_key(const unordered_map<KeyType,
// ValueType>& container, const typename unordered_map<KeyType,
// ValueType>::key_type& key)"
//)
//{
//		const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//		const auto parts{split(src, L':')};
//
//		const unordered_map<wstring, size_t> fruit_count = [&]()
//		{
//				unordered_map<wstring, size_t> fruits{};
//
//				for (size_t i = 0; i < parts.size(); i += 2)
//				{
//						fruits[parts[i]] = stoul(parts[i
//+ 1]);
//				}
//
//				return fruits;
//		}();
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (fruit_count.find(random_fruit) != cend(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_key(unordered_map<KeyType, ValueType>& container, const
// typename unordered_map<KeyType, ValueType>::key_type& key)", "Testing global
// template function bool has_key(unordered_map<KeyType, ValueType>& container,
// const typename unordered_map<KeyType, ValueType>::key_type& key)")
//{
//		const wstring src{
// L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70" };
//
//		const auto parts{ split(src, L':') };
//
//		auto fruit_count = unordered_map<wstring, size_t>{};
//
//		for (size_t i = 0; i < parts.size(); i += 2)
//		{
//				fruit_count[parts[i]] = std::stoul(parts[i +
// 1]);
//		}
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{ rd() };
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{ random_fruits[num_distr(rand_engine)]
//};
//
//		if (fruit_count.find(random_fruit) != end(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, L"orange" ));
//
//		REQUIRE(!has_key(fruit_count, wstring{ L"grapefruit" }));
//}
//
//
// TEST_CASE("bool has_key(const unordered_multimap<KeyType, ValueType>&
// container, const typename unordered_multimap<KeyType, ValueType>::key_type&
// key)", "Testing global template function bool has_key(const
// unordered_multimap<KeyType, ValueType>& container, const typename
// unordered_multimap<KeyType, ValueType>::key_type& key)"
//)
//{
//		const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//		const auto parts{split(src, L':')};
//
//		const unordered_multimap<wstring, size_t> fruit_count = [&]()
//		{
//				unordered_multimap<wstring, size_t> fruits{};
//
//				for (size_t i = 0; i < parts.size(); i += 2)
//				{
//						fruits.insert(make_pair(parts[i],
// stoul(parts[i + 1])));
//				}
//
//				return fruits;
//		}();
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (fruit_count.find(random_fruit) != cend(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_key(unordered_multimap<KeyType, ValueType>& container,
// const typename unordered_multimap<KeyType, ValueType>::key_type& key)",
// "Testing global template function bool has_key(unordered_multimap<KeyType,
// ValueType>& container, const typename unordered_multimap<KeyType,
// ValueType>::key_type& key)")
//{
//		const wstring
// src{L"apple:10:banana:20:cabbage:30:lemon:40:orange:50:pepper:60:plum:70"};
//
//		const auto parts{split(src, L':')};
//
//		auto fruit_count = unordered_multimap<wstring, size_t>{};
//
//		for (size_t i = 0; i < parts.size(); i += 2)
//		{
//				fruit_count.insert(make_pair(parts[i],
// std::stoul(parts[i + 1])));
//		}
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (fruit_count.find(random_fruit) != end(fruit_count))
//		{
//				REQUIRE(has_key(fruit_count, random_fruit));
//		}
//		else
//		{
//				REQUIRE(!has_key(fruit_count, random_fruit));
//		}
//
//		REQUIRE(has_key(fruit_count, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(fruit_count, L"grapefruit" ));
//}
//
// TEST_CASE("bool has_value(const ContainerType& container, const typename
// ContainerType::value_type& search_value)", "Testing global template function
// bool has_value(const ContainerType& container, const typename
// ContainerType::value_type& search_value)"
//)
//{
//		const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut"};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		REQUIRE(has_value(parts, L"orange"));
//
//		REQUIRE(!has_value(parts, wstring{ L"grapefruit" }));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (find(cbegin(parts), cend(parts), random_fruit) !=
// cend(parts)) 				REQUIRE(has_value(parts,
// random_fruit));
//
//		else
//				REQUIRE(!has_value(parts, random_fruit));
//}
//
// TEST_CASE("bool has_value(ContainerType& container, const typename
// ContainerType::value_type& search_value)", "Testing global template function
// bool has_value(ContainerType& container, const typename
// ContainerType::value_type& search_value)"
//)
//{
//		const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut"};
//
//		const wstring needle{L":|:"};
//
//		auto parts{split(src, needle)};
//
//		REQUIRE(has_value(parts, L"orange"));
//
//		REQUIRE(!has_value(parts, wstring{ L"grapefruit" }));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (find(begin(parts), end(parts), random_fruit) != end(parts))
//				REQUIRE(has_value(parts, random_fruit));
//
//		else
//				REQUIRE(!has_value(parts, random_fruit));
//}
//
// TEST_CASE("bool has_key(const set<ValueType>& container, const typename
// set<ValueType>::key_type& item)", "Testing global template function bool
// has_key(const set<ValueType>& container, const typename
// set<ValueType>::key_type& item)")
//{
//		const wstring src{
//				L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//		};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		const set<wstring> all_fruits = [&]()
//		{
//				set<wstring> fruits{};
//
//				for (const auto& fruit : parts)
//				{
//						fruits.insert(fruit);
//				}
//
//				return fruits;
//		}();
//
//		REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (all_fruits.find(random_fruit) != cend(all_fruits))
//				REQUIRE(has_key(all_fruits, random_fruit));
//
//		else
//				REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_value(const multiset<ValueType>& container, const
// typename multiset<ValueType>::key_type& item)", "Testing global template
// function bool has_value(const multiset<ValueType>& container, const typename
// multiset<ValueType>::key_type& item)")
//{
//		const wstring src{
//				L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//		};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		const multiset<wstring> all_fruits = [&]()
//		{
//				multiset<wstring> fruits{};
//
//				for (const auto& fruit : parts)
//				{
//						fruits.insert(fruit);
//				}
//
//				return fruits;
//		}();
//
//		REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (all_fruits.find(random_fruit) != cend(all_fruits))
//				REQUIRE(has_key(all_fruits, random_fruit));
//
//		else
//				REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_key(const unordered_set<ValueType>& container, const
// typename unordered_set<ValueType>::key_type& item)", "Testing global template
// function bool has_key(const unordered_set<ValueType>& container, const
// typename unordered_set<ValueType>::key_type& item)")
//{
//		const wstring src{
//				L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//		};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		const unordered_set<wstring> all_fruits = [&]()
//		{
//				unordered_set<wstring> fruits{};
//
//				for (const auto& fruit : parts)
//				{
//						fruits.insert(fruit);
//				}
//
//				return fruits;
//		}();
//
//		REQUIRE(has_key(all_fruits, wstring{ L"orange" }));
//
//		REQUIRE(!has_key(all_fruits, L"grapefruit" ));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (all_fruits.find(random_fruit) != cend(all_fruits))
//				REQUIRE(has_key(all_fruits, random_fruit));
//
//		else
//				REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE("bool has_key(const unordered_multiset<ValueType>& container, const
// typename unordered_multiset<ValueType>::key_type&  item)", "Testing global
// template function bool has_key(const unordered_multiset<ValueType>&
// container, const typename unordered_multiset<ValueType>::key_type& item)"
//)
//{
//		const wstring src{
//				L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:pineapple:|:plum:|:walnut:|:lemon:|:apricot:|:plum"
//		};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		const unordered_multiset<wstring> all_fruits = [&]()
//		{
//				unordered_multiset<wstring> fruits{};
//
//				for (const auto& fruit : parts)
//				{
//						fruits.insert(fruit);
//				}
//
//				return fruits;
//		}();
//
//		REQUIRE(has_key(all_fruits, L"orange"));
//
//		REQUIRE(!has_key(all_fruits, wstring{ L"grapefruit" }));
//
//		const vector<wstring> random_fruits{
//				L"apple", L"apricot", L"banana", L"orange",
// L"grapefruit", L"lemon", L"pear", L"pineapple", L"plum", L"walnut"
//		};
//
//		mt19937 rand_engine{rd()};
//
//		auto const num_distr = uniform_int_distribution<unsigned>(0,
// random_fruits.size() - 1);
//
//		const auto random_fruit{random_fruits[num_distr(rand_engine)]};
//
//		if (all_fruits.find(random_fruit) != cend(all_fruits))
//				REQUIRE(has_key(all_fruits, random_fruit));
//
//		else
//				REQUIRE(!has_key(all_fruits, random_fruit));
//}
//
// TEST_CASE(
//		"string get_type_name(T&& arg) | wstring get_type_name_w(T&&
// arg) | void show_var_info(const T& arg) | void show_var_info_w(const T& arg)
//||
// bool check_data_types_for_equality(Args&&... args)"
//		,
//		"Testing global template functions: get_type_name,
// get_type_name_w, show_var_info, show_var_info_w and
// check_data_types_for_equality"
//)
//{
//		const wstring
// src{L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum"};
//
//		const wstring needle{L":|:"};
//
//		const auto parts{split(src, needle)};
//
//		cout << '\n' << get_type_name(src) << '\n';
//
//		wcout << get_type_name_w(needle) << L'\n';
//
//		const string info_message{"Hello World!"};
//
//		show_var_info(info_message);
//
//		show_var_info_w(src);
//
//		show_var_info_w(needle);
//
//		cout << "\ncheck_data_types_for_equality(src : wstring, needle :
// wstring) -> " << boolalpha << check_data_types_for_equality(src, needle) <<
//'\n';
//
//		cout << "\ncheck_data_types_for_equality(src : wstring, parts :
// vector<wstring>) -> " << check_data_types_for_equality(src, parts) << '\n';
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//		auto const result_u16string{
// to_u16string(static_cast<short>(12345)) };
//
//
//
//		string result_string(cbegin(result_u16string),
// cend(result_u16string));
//
//
//
//		cout << "\nto_u16string(12345) = \"" << result_string << "\"\n";
//
//		REQUIRE(u16string{ u"12345" } == result_u16string);
//
//		const auto float_to_u16string{ to_u16string(7.51735f) };
//
//		REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//		result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//		cout << "to_u16string(7.51735f) = \"" << result_string <<
//"\"\n";
//
//}
//
// TEST_CASE("u16string to_u16string(const unsigned short value)", "Testing
// correct functionality of global conversion function: u16string
// to_u16string(const unsigned short value)")
//{
//		auto const result_u16string{ to_u16string(static_cast<unsigned
// short>(12345)) };
//
//		const string result_string(cbegin(result_u16string),
// cend(result_u16string));
//
//		cout << "\nto_u16string(12345) = \"" << result_string << "\"\n";
//
//		REQUIRE(u16string{ u"12345" } == result_u16string);
//
//}
//
// TEST_CASE("float stof(const u16string& str, size_t* pos = nullptr, int base =
// 10, bool ignore_leading_white_space_characters = true), u16string
// to_u16string(float value)", "Testing correct functionality of global
// conversion functions: stof, to_u16string")
//{
//		size_t end_pos{};
//		// add code (function) for rounding to N decimal digits
//		auto const float_value { stof(u"7.53", &end_pos, 10) };
//
//		cout << "\nstof(u\"7.53\") = " << float_value << '\n' <<
//"end_pos = " << end_pos << '\n';
//
//		REQUIRE(float_value == 7.53);
//
//		const auto float_to_u16string{ to_u16string(float_value) };
//
//		REQUIRE(float_to_u16string == u"7.53");
//
//
//}

// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
//
// TEST_CASE("u16string to_u16string(const short value)", "Testing correct
// functionality of global conversion function: u16string to_u16string(const
// short value)")
//{
//	auto const result_u16string{ to_u16string(static_cast<short>(12345)) };
//
//	string result_string(cbegin(result_u16string), cend(result_u16string));
//
//	cout << "\nto_u16string(12345)=\"" << result_string << "\"\n";
//
//	REQUIRE(u16string{ u"12345" } ==
// to_u16string(static_cast<short>(12345)));
//
//	const auto float_to_u16string{ to_u16string(7.51735f) };
//
//	REQUIRE(u16string{ u"7.51735" } == float_to_u16string);
//
//	result_string.assign(cbegin(float_to_u16string),
// cend(float_to_u16string));
//
//	cout << "to_u16string(7.51735f)=\"" << result_string << "\"\n";
//
//
//}
