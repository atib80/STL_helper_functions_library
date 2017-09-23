#define CATCH_CONFIG_MAIN

#include "stl_helper_functions.hpp"
#include "catch.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <chrono>


using namespace std;
using namespace std::chrono;
using namespace string_literals;
using namespace std::helper;

TEST_CASE("int say_slow(const size_t, const char*, Args...)",
	"Testing correct work of global template function int say_slow(const size_t time_delay_in_ms, const char* format_string, Args... args)"
)
{
	const char* printed_message = "The word 'apple' consists of 5 characters.\n";

	auto const length = strlen(printed_message);

	char buffer[512];

	auto const formatted_string_length = snprintf(buffer, sizeof(buffer) / sizeof(buffer[0]),
	                                              "The word '%s' consists of %d characters.\n", "apple", 5);

	auto const ret_val = say_slow(5, "The word '%s' consists of %d characters.\n", "apple", 5);

	REQUIRE(length == formatted_string_length);

	REQUIRE(length == ret_val);
}

TEST_CASE("int say_slow(const size_t, const wchar_t*, Args...)",
	"Testing correct work of global template function int say_slow(const size_t time_delay_in_ms, const wchar_t* format_string, Args... args)"
)
{
	const wchar_t* printed_message = L"The word 'apple' consists of 5 characters.\n";

	auto const length = wcslen(printed_message);

	wchar_t buffer[512];

	auto const formatted_string_length = _snwprintf(buffer, sizeof(buffer) / sizeof(buffer[0]),
	                                                L"The word '%s' consists of %d characters.\n", L"apple", 5);

	auto const ret_val = say_slow(5, L"The word '%s' consists of %d characters.\n", L"apple", 5);

	REQUIRE(length == formatted_string_length);

	REQUIRE(length == ret_val);
}

TEST_CASE("int say(const char* format_string, Args... args)",
	"Testing correct work of global template function int say(const char* format_string, Args... args)")
{
	const char* printed_message = "The word 'apple' consists of 5 characters.\n";

	auto const length = strlen(printed_message);

	char buffer[512];

	auto const formatted_string_length = snprintf(buffer, sizeof(buffer) / sizeof(buffer[0]),
	                                              "The word '%s' consists of %d characters.\n", "apple", 5);

	auto const ret_val = say("The word '%s' consists of %d characters.\n", "apple", 5);

	REQUIRE(length == formatted_string_length);

	REQUIRE(length == ret_val);
}

TEST_CASE("int say(const wchar_t* format_string, Args... args)",
	"Testing correct work of global template function int say(const wchar_t* format_string, Args... args)")
{
	const wchar_t* printed_message = L"The word 'apple' consists of 5 characters.\n";

	auto const length = wcslen(printed_message);

	wchar_t buffer[512];

	auto const formatted_string_length = _snwprintf(buffer, sizeof(buffer) / sizeof(buffer[0]),
	                                                L"The word '%s' consists of %d characters.\n", L"apple", 5);

	auto const ret_val = say(L"The word '%s' consists of %d characters.\n", L"apple", 5);

	REQUIRE(length == formatted_string_length);

	REQUIRE(length == ret_val);
}

TEST_CASE("bool trim(char* mutable_source_string_buffer)",
	"Testing global function bool trim(char* source_string_buffer)")
{
	char src[512] = " \t Hello World!\t \n";

	const char* dst = "Hello World!";

	REQUIRE(trim(src));

	REQUIRE(strcmp(src, dst) == 0);
}

TEST_CASE("bool trim(wchar_t* mutable_source_string_buffer)",
	"Testing global function bool trim(wchar_t* mutable_source_string_buffer)")
{
	wchar_t src[512] = L" \t Hello World!\t \n";

	const wchar_t* dst = L"Hello World!";

	REQUIRE(trim(src));

	REQUIRE(wcscmp(src, dst) == 0);
}

TEST_CASE("bool trim(char16_t* mutable_source_string_buffer)",
	"Testing global function bool trim(char16_t* mutable_source_string_buffer)")
{
	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u"Hello World!";

	REQUIRE(trim(src));

	u16string src_wstring{src};
	u16string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("bool trim(char32_t* mutable_source_string_buffer)",
	"Testing global function bool trim(char32_t* mutable_source_string_buffer)")
{
	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U"Hello World!";

	REQUIRE(trim(src));

	u32string src_wstring{src};
	u32string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}


TEST_CASE("bool ltrim(char* mutable_source_string_buffer)",
	"Testing global function bool trim(char* mutable_source_string_buffer)")
{
	char src[512] = " \t Hello World!\t \n";

	const char* dst = "Hello World!\t \n";

	REQUIRE(ltrim(src));

	REQUIRE(strcmp(src, dst) == 0);
}

TEST_CASE("bool ltrim(wchar_t* mutable_source_string_buffer)",
	"Testing global function bool trim(wchar_t* mutable_source_string_buffer)")
{
	wchar_t src[512] = L" \t Hello World!\t \n";

	const wchar_t* dst = L"Hello World!\t \n";

	REQUIRE(ltrim(src));

	REQUIRE(wcscmp(src, dst) == 0);
}

TEST_CASE("bool ltrim(char16_t* mutable_source_string_buffer)",
	"Testing global function bool trim(char16_t* mutable_source_string_buffer)")
{
	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u"Hello World!\t \n";

	REQUIRE(ltrim(src));

	u16string src_wstring{src};
	u16string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("bool ltrim(char32_t* mutable_source_string_buffer)",
	"Testing global function bool trim(char32_t* mutable_source_string_buffer)")
{
	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U"Hello World!\t \n";

	REQUIRE(ltrim(src));

	u32string src_wstring{src};
	u32string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("bool rtrim(char* mutable_source_string_buffer)",
	"Testing global function bool rtrim(char* mutable_source_string_buffer)")
{
	char src[512] = " \t Hello World!\t \n";

	const char* dst = " \t Hello World!";

	REQUIRE(rtrim(src));

	REQUIRE(strcmp(src, dst) == 0);
}

TEST_CASE("bool rtrim(wchar_t* mutable_source_string_buffer)",
	"Testing global function bool rtrim(wchar_t* mutable_source_string_buffer)")
{
	wchar_t src[512] = L" \t Hello World!\t \n";

	const wchar_t* dst = L" \t Hello World!";

	REQUIRE(rtrim(src));

	REQUIRE(wcscmp(src, dst) == 0);
}

TEST_CASE("bool rtrim(char16_t* mutable_source_string_buffer)",
	"Testing global function bool rtrim(char16_t* mutable_source_string_buffer)")
{
	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u" \t Hello World!";

	REQUIRE(rtrim(src));

	const u16string src_wstring{src};

	const u16string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("bool rtrim(char32_t* mutable_source_string_buffer)",
	"Testing global function bool rtrim(char32_t* mutable_source_string_buffer)")
{
	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U" \t Hello World!";

	REQUIRE(rtrim(src));

	const u32string src_wstring{src};

	const u32string dst_wstring{dst};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("string trim(const char* src)", "Testing global function string trim(const char* src)")
{
	const char* src = " \t Hello World!\t \n";

	const string dst_string{"Hello World!"};

	const string src_string{trim(src)};

	REQUIRE(src_string == dst_string);
}

TEST_CASE("wstring trim(const wchar_t* src)", "Testing global function wstring trim(const wchar_t* src)")
{
	const wchar_t* src = L" \t Hello World!\t \n";

	const wstring dst_wstring{L"Hello World!"};

	const wstring src_wstring{trim(src)};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("u16string trim(const char16_t* src)", "Testing global function u16string trim(const char16_t* src)")
{
	const char16_t* src = u" \t Hello World!\t \n";

	const u16string dst_u16string{u"Hello World!"};

	const u16string src_u16string{trim(src)};

	REQUIRE(src_u16string == dst_u16string);
}

TEST_CASE("u32string trim(const char32_t* src)", "Testing global function u32string trim(const char32_t* src)")
{
	const char32_t* src = U" \t Hello World!\t \n";

	const u32string dst_u32string{U"Hello World!"};

	const u32string src_u32string{trim(src)};

	REQUIRE(dst_u32string == src_u32string);
}

TEST_CASE("string ltrim(const char* src)", "Testing global function string ltrim(const char* src)")
{
	const char* src = " \t Hello World!\t \n";

	const string dst_string{"Hello World!\t \n"};

	const string src_string{ltrim(src)};

	REQUIRE(src_string == dst_string);
}

TEST_CASE("wstring ltrim(const wchar_t* src)", "Testing global function wstring ltrim(const wchar_t* src)")
{
	const wchar_t* src = L" \t Hello World!\t \n";

	const wstring dst_wstring{L"Hello World!\t \n"};

	const wstring src_wstring{ltrim(src)};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("u16string ltrim(const char16_t* src)", "Testing global function u16string ltrim(const char16_t* src)")
{
	const char16_t* src = u" \t Hello World!\t \n";

	const u16string dst_u16string{u"Hello World!\t \n"};

	const u16string src_u16string{ltrim(src)};

	REQUIRE(src_u16string == dst_u16string);
}

TEST_CASE("u32string ltrim(const char32_t* src)", "Testing global function u32string ltrim(const char32_t* src)")
{
	const char32_t* src = U" \t Hello World!\t \n";

	const u32string dst_u32string{U"Hello World!\t \n"};

	const u32string src_u32string{ltrim(src)};

	REQUIRE(dst_u32string == src_u32string);
}

TEST_CASE("string rtrim(const char* src)", "Testing global function string rtrim(const char* src)")
{
	const char* src = " \t Hello World!\t \n";

	const string dst_string{" \t Hello World!"};

	const string src_string{rtrim(src)};

	REQUIRE(src_string == dst_string);
}

TEST_CASE("wstring rtrim(const wchar_t* src)", "Testing global function wstring rtrim(const wchar_t* src)")
{
	const wchar_t* src = L" \t Hello World!\t \n";

	const wstring dst_wstring{L" \t Hello World!"};

	const wstring src_wstring{rtrim(src)};

	REQUIRE(src_wstring == dst_wstring);
}

TEST_CASE("u16string rtrim(const char16_t* src)", "Testing global function u16string rtrim(const char16_t* src)")
{
	const char16_t* src = u" \t Hello World!\t \n";

	const u16string dst_u16string{u" \t Hello World!"};

	const u16string src_u16string{rtrim(src)};

	REQUIRE(src_u16string == dst_u16string);
}

TEST_CASE("u32string rtrim(const char32_t* src)", "Testing global function u32string rtrim(const char32_t* src)")
{
	const char32_t* src = U" \t Hello World!\t \n";

	const u32string dst_u32string{U" \t Hello World!"};

	const u32string src_u32string{rtrim(src)};

	REQUIRE(dst_u32string == src_u32string);
}

TEST_CASE("size_t u16_strlen(const char16_t* src)", "Testing global function size_t u16_strlen(const char16_t* src)")
{
	const char16_t* src = u"Hello World!\n";

	REQUIRE(u16_strlen(src) == 13);
}

TEST_CASE("size_t u32_strlen(const char32_t* src)", "Testing global function size_t u32_strlen(const char32_t* src)")
{
	const char32_t* src = U"Hello World!\n";

	REQUIRE(u32_strlen(src) == 13);
}

TEST_CASE("int u16_strcmp(const char16_t* str1, const char16_t* str2)",
	"Testing global function int u16_strcmp(const char16_t* str1, const char16_t* str2)")
{
	REQUIRE(u16_strcmp(u"apple", u"apple") == 0);

	REQUIRE(u16_strcmp(u"apple", u"banana") < 0);
}

TEST_CASE("int u32_strcmp(const char32_t* str1, const char32_t* str2)",
	"Testing global function int u32_strcmp(const char32_t* str1, const char32_t* str2)")
{
	REQUIRE(u32_strcmp(U"apple", U"apple") == 0);

	REQUIRE(u32_strcmp(U"apple", U"banana") < 0);
}

TEST_CASE("int u16_strncmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare)",
	"Testing global function int u16_strncmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare)")
{
	REQUIRE(u16_strncmp(u"apple", u"appLE", 3) == 0);
	
	REQUIRE(u16_strncmp(u"apple", u"banana", 3) < 0);
}

TEST_CASE("int u32_strncmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare)",
	"Testing global function int u32_strncmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare)")
{
	REQUIRE(u32_strncmp(U"apple", U"appLE", 3) == 0);

	REQUIRE(u32_strncmp(U"apple", U"banana", 3) < 0);
}

TEST_CASE("int u16_stricmp(const char16_t* str1, const char16_t* str2, const std::locale& loc = std::locale{})",
	"Testing global function int u16_stricmp(const char16_t* str1, const char16_t* str2, const std::locale& loc = std::locale{})")
{

	REQUIRE(u16_stricmp(u"apple", u"apple") == 0);

	REQUIRE(u16_stricmp(u"apple", u"banana") < 0);

}

TEST_CASE("int u32_stricmp(const char32_t* str1, const char32_t* str2, const std::locale& loc = std::locale{})", 
	"Testing global function int u32_stricmp(const char32_t* str1, const char32_t* str2, const std::locale& loc = std::locale{})")
{

	REQUIRE(u32_stricmp(U"apple", U"apple") == 0);

	REQUIRE(u32_stricmp(U"apple", U"banana") < 0);

}

TEST_CASE("int u16_strnicmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare, const std::locale& loc = std::locale{})", 
	"Testing global function int u16_strnicmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare, const std::locale& loc = std::locale{})")
{

	REQUIRE(u16_strnicmp(u"apple", u"apple", 3) == 0);

	REQUIRE(u16_strnicmp(u"apple", u"banana", 3) < 0);

}

TEST_CASE("int u32_strnicmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare, const std::locale& loc = std::locale{})", 
	"Testing global function int u32_strnicmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare, const std::locale& loc = std::locale{})")
{

	REQUIRE(u32_strnicmp(U"apple", U"apple", 3) == 0);

	REQUIRE(u32_strnicmp(U"apple", U"banana", 3) < 0);

}

TEST_CASE("char16_t* u16_strcpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)", 
	"Testing global function char16_t* u16_strcpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)")
{

	char16_t src[128];

	char16_t dst[64] = u"\tHello World!\n";

	REQUIRE(trim(dst));

	REQUIRE(u16_strcpy(src, sizeof(src)/sizeof(src[0]), dst) != nullptr);

	REQUIRE(u16_strcmp(src, u"Hello World!") == 0);

}

TEST_CASE("char32_t* u32_strcpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)",
	"Testing global function char32_t* u32_strcpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)")
{

	char32_t src[128];

	char32_t dst[64] = U"\tHello World!\n";

	REQUIRE(trim(dst));

	REQUIRE(u32_strcpy(src, sizeof(src) / sizeof(src[0]), dst) != nullptr);

	REQUIRE(u32_strcmp(src, U"Hello World!") == 0);

}

TEST_CASE("char16_t* u16_strncpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_copy)", 
"Testing global function char16_t* u16_strncpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_copy)")
{

	char16_t src[128];

	char16_t dst[64] = u"\tHello World!\n";

	REQUIRE(trim(dst));

	REQUIRE(u16_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5) != nullptr);

	REQUIRE(u16_strncmp(src, u"Hello World!", 5) == 0);

}

TEST_CASE("char32_t* u32_strncpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_copy)",
	"Testing global function char32_t* u32_strncpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_copy)")
{

	char32_t src[128];

	char32_t dst[64] = U"\tHello World!\n";

	REQUIRE(trim(dst));

	REQUIRE(u32_strncpy(src, sizeof(src) / sizeof(src[0]), dst, 5) != nullptr);

	REQUIRE(u32_strncmp(src, U"Hello World!", 5) == 0);

}

TEST_CASE("char16_t* u16_strcat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)",
	"Testing global function char16_t* u16_strcat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)")
{

	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u" How are you today?";

	REQUIRE(trim(src));

	REQUIRE(u16_strcat(src, sizeof(src) / sizeof(src[0]), dst) != nullptr);

	REQUIRE(u16_strcmp(src, u"Hello World! How are you today?") == 0);

}

TEST_CASE("char32_t* u32_strcat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)",
	"Testing global function char32_t* u32_strcat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)")
{

	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U" How are you today?";

	REQUIRE(trim(src));

	REQUIRE(u32_strcat(src, sizeof(src) / sizeof(src[0]), dst) != nullptr);

	REQUIRE(u32_strcmp(src, U"Hello World! How are you today?") == 0);

}

TEST_CASE("char16_t* u16_strncat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_concatenate)",
	"Testing global function char16_t* u16_strncat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_concatenate)")
{

	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u" How are you today?";

	REQUIRE(trim(src));

	REQUIRE(u16_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4) != nullptr);

	REQUIRE(u16_strcmp(src, u"Hello World! How") == 0);

}

TEST_CASE("char32_t* u32_strncat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_concatenate)",
	"Testing global function char32_t* u32_strncat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_concatenate)")
{

	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U" How are you today?";

	REQUIRE(trim(src));

	REQUIRE(u32_strncat(src, sizeof(src) / sizeof(src[0]), dst, 4) != nullptr);

	REQUIRE(u32_strcmp(src, U"Hello World! How") == 0);

}

TEST_CASE("const char16_t* u16_strstr(const char16_t* src, const char16_t* needle)",
	"Testing global function const char16_t* u16_strstr(const char16_t* src, const char16_t* needle)")
{
	const char16_t* src = u"Hello World! How are you today?";

	const char16_t* needle = u"today";

	REQUIRE(u16_strstr(src, needle) != nullptr);
}

TEST_CASE("const char32_t* u32_strstr(const char32_t* src, const char32_t* needle)", 
	"Testing global function const char32_t* u32_strstr(const char32_t* src, const char32_t* needle)")
{

	const char32_t* src = U"Hello World! How are you today?";

	const char32_t* needle = U"today";

	REQUIRE(u32_strstr(src, needle) != nullptr);

}

TEST_CASE("char16_t* u16_strstr(char16_t* src, const char16_t* needle)", 
	"Testing global function char16_t* u16_strstr(char16_t* src, const char16_t* needle)")
{

	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u"World";

	REQUIRE(trim(src));

	REQUIRE(u16_strstr(src, dst) != nullptr);

}

TEST_CASE("char32_t* u32_strstr(char32_t* src, const char32_t* needle)", 
	"Testing global function char32_t* u32_strstr(char32_t* src, const char32_t* needle)")
{

	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U"World";

	REQUIRE(trim(src));

	REQUIRE(u32_strstr(src, dst) != nullptr);

}

TEST_CASE("const char16_t* u16_strstri(const char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{})", 
 "Testing global function const char16_t* u16_strstri(const char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{})")
{

	const char16_t* src = u"Hello World! How are you TODAY?";

	const char16_t* needle = u"today";

	REQUIRE(u16_strstri(src, needle) != nullptr);

}

TEST_CASE("const char32_t* u32_strstri(const char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{})", 
 "Testing global function const char32_t* u32_strstri(const char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{})")
{

	const char32_t* src = U"Hello World! How are you TODAY?";

	const char32_t* needle = U"today";

	REQUIRE(u32_strstri(src, needle) != nullptr);

}

TEST_CASE("char16_t* u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{})", 
 "Testing global function char16_t* u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{})")
{

	char16_t src[512] = u" \t Hello World!\t \n";

	const char16_t* dst = u"Hello World!";

	REQUIRE(trim(src));

	REQUIRE(u16_strstri(src, dst) != nullptr);

}

TEST_CASE("char32_t* u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{})", 
 "Testing global function char32_t* u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{})")
{

	char32_t src[512] = U" \t Hello World!\t \n";

	const char32_t* dst = U"Hello World!";

	REQUIRE(trim(src));

	REQUIRE(u32_strstri(src, dst) != nullptr);

}

TEST_CASE("StringType trim(const StringType& str)", "Testing global template function StringType trim(const StringType& str)")
{
	const string src{ "\t Hello World!\t \n" };
	
	const string dst{ trim(src) };

	REQUIRE(dst == string{ "Hello World!" });
}

TEST_CASE("StringType ltrim(const StringType& str)", "Testing global template function StringType ltrim(const StringType& str)")
{
	const wstring src{ L"\t Hello World!\t \n" };
	
	const wstring dst{ ltrim(src) };

	REQUIRE(dst == wstring{ L"Hello World!\t \n" });

}

TEST_CASE("StringType rtrim(const StringType& str)", "Testing global template function StringType rtrim(const StringType& str)")
{
	const u32string src{ U"\t Hello World!\t \n" };
	
	const u32string dst{ rtrim(src) };

	REQUIRE(dst == u32string{ U"\t Hello World!" });

}

TEST_CASE("vector<string> split(const char* source, const char needle_char, int const max_count = -1)", 
		"Testing global function vector<std::string> split(const char* source, const char needle_char, int const max_count = -1)")
{
	const char* source{ "apple|banana|cabbage|lemon|orange|pepper|plum" };
	
	const char needle_char{'|'};

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == "apple");
	
	REQUIRE(parts[3] == "lemon");
	
	REQUIRE(parts.back() == "plum");

}

TEST_CASE("vector<wstring> split(const wchar_t* source, const wchar_t needle_char, int const max_count = -1)",
	"Testing global function vector<wstring> split(const wchar_t* source, const wchar_t needle_char, int const max_count = -1)")
{
	const wchar_t* source{ L"apple|banana|cabbage|lemon|orange|pepper|plum" };

	const wchar_t needle_char{ L'|' };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == L"apple");

	REQUIRE(parts[3] == L"lemon");

	REQUIRE(parts.back() == L"plum");

}

TEST_CASE("vector<u16string> split(const char16_t* source, const char16_t needle_char, int const max_count = -1)",
	"Testing global function vector<u16string> split(const char16_t* source, const char16_t needle_char, int const max_count = -1)")
{
	const char16_t* source{ u"apple|banana|cabbage|lemon|orange|pepper|plum" };

	const char16_t needle_char{ u'|' };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == u"apple");

	REQUIRE(parts[3] == u"lemon");

	REQUIRE(parts.back() == u"plum");

}

TEST_CASE("vector<u32string> split(const char32_t* source, const char32_t needle_char, int const max_count = -1)",
	"Testing global function vector<u32string> split(const char32_t* source, const char32_t needle_char, int const max_count = -1)")
{
	const char32_t* source { U"apple|banana|cabbage|lemon|orange|pepper|plum" };

	const char32_t needle_char { U'|' };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == U"apple");

	REQUIRE(parts[3] == U"lemon");

	REQUIRE(parts.back() == U"plum");

}

TEST_CASE("vector<string> split(const char* source, const char* needle, const int max_count = -1)",
	"Testing global function vector<string> split(const char* source, const char* needle, const int max_count = -1)")
{
	const char* source{ "apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const char* needle_char{ ":|:" };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == "apple");

	REQUIRE(parts[3] == "lemon");

	REQUIRE(parts.back() == "plum");

}

TEST_CASE("vector<wstring> split(const wchar_t* source, const wchar_t* needle, const int max_count = -1)",
	"Testing global function vector<wstring> split(const wchar_t* source, const wchar_t* needle, const int max_count = -1)")
{
	const wchar_t* source{ L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const wchar_t* needle_char{ L":|:" };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == L"apple");

	REQUIRE(parts[3] == L"lemon");

	REQUIRE(parts.back() == L"plum");

}

TEST_CASE("vector<u16string> split(const char16_t* source, const char16_t* needle, const int max_count = -1)",
	"Testing global function vector<u16string> split(const char16_t* source, const char16_t* needle, const int max_count = -1)")
{
	const char16_t* source{ u"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const char16_t* needle_char{ u":|:" };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == u"apple");

	REQUIRE(parts[3] == u"lemon");

	REQUIRE(parts.back() == u"plum");
}

TEST_CASE("vector<u32string> split(const char32_t* source, const char32_t* needle, const int max_count = -1)",
	"Testing global function vector<u32string> split(const char32_t* source, const char32_t* needle, const int max_count = -1)")
{
	const char32_t* source{ U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const char32_t* needle_char{ U":|:" };

	auto const parts{ split(source, needle_char) };

	REQUIRE(parts.front() == U"apple");

	REQUIRE(parts[3] == U"lemon");

	REQUIRE(parts.back() == U"plum");

}

TEST_CASE("vector<StringType> split(const StringType& source, const typename StringType::value_type needle_char, size_t const max_count = StringType::npos)", 
   "Testing global template function vector<StringType> split(const StringType& source, const typename StringType::value_type needle_char, size_t const max_count = StringType::npos)")
{
	const wstring src{ L"apple | banana | cabbage | lemon | orange | pepper | plum" };

	auto parts{ split(src, L'|') };

	for (auto& part : parts) part = trim(part);

	REQUIRE(parts.front() == L"apple");

	REQUIRE(parts[3] == L"lemon");

	REQUIRE(parts.back() == L"plum");

}

TEST_CASE("vector<StringType> split(const StringType& source, const typename StringType::const_pointer_type needle, size_t const max_count = StringType::npos)",
	"Testing global template function vector<StringType> split(const StringType& source, const typename StringType::const_pointer_type needle, size_t const max_count = StringType::npos)")
{
	const u16string src{ u"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	auto parts{ split(src, u":|:") };

	REQUIRE(parts.front() == u"apple");

	REQUIRE(parts[3] == u"lemon");

	REQUIRE(parts.back() == u"plum");

}

TEST_CASE("vector<StringType> split(const StringType& source, const StringType& needle, size_t const max_count = StringType::npos)",
	"Testing global template function vector<StringType> split(const StringType& source, const StringType& needle, size_t const max_count = StringType::npos)")
{
	const u32string src{ U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const u32string needle{ U":|:" };

	auto parts{ split(src, needle) };

	REQUIRE(parts.front() == U"apple");

	REQUIRE(parts[3] == U"lemon");

	REQUIRE(parts.back() == U"plum");

}

// TODO: add missing source code for remaining TEST_CASEs

TEST_CASE("bool starts_with(const StringType& src, const typename StringType::value_type start_char, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool starts_with(const StringType& src, const typename StringType::value_type start_char, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"Apple is one my favorite, most beloved fruits." };

	REQUIRE(starts_with(src, L'A'));

	REQUIRE(starts_with(src, L'a', true));

}


TEST_CASE("bool starts_with(const StringType& src, const typename StringType::const_pointer start_tag, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool starts_with(const StringType& src, const typename StringType::const_pointer start_tag, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const u16string src{ u"Apple is one my favorite, most beloved fruits." };

	REQUIRE(starts_with(src, u"Apple"));

	REQUIRE(starts_with(src, u"aPPLE", true));

}

TEST_CASE("bool starts_with(const StringType& src, const StringType& start_tag, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool starts_with(const StringType& src, const StringType& start_tag, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const u32string src{ U"Apple is one my favorite, most beloved fruits." };

	const u32string needle{ U"Apple" };

	REQUIRE(starts_with(src, needle));

	REQUIRE(starts_with(src, u32string{ U"aPPLE" }, true));

}

TEST_CASE("typename StringType::size_type index_of(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u, bool ignore_case = false,\
	const std::locale& loc = std::locale{})", 
	"Testing global template function typename StringType::size_type index_of(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u, bool ignore_case = false,\
	const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	wstring::size_type correct_index = src.find(L'b');

	REQUIRE(index_of(src, L'b') == correct_index);

	correct_index = src.find(L'b');

	REQUIRE(index_of(src, L'B', 0, true) == correct_index);

}

TEST_CASE("typename StringType::size_type index_of(const StringType& text, const typename StringType::const_pointer needle, const size_t start_pos = 0u, bool ignore_case = false,\
	const std::locale& loc = std::locale{})",
	"Testing global template function typename StringType::size_type index_of(const StringType& text, const typename StringType::const_pointer needle, const size_t start_pos = 0u, bool ignore_case = false,\
	const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	wstring::size_type correct_index = src.find(L"banana");

	REQUIRE(index_of(src, L"banana") == correct_index);

	correct_index = src.find(L"cabbage");

	REQUIRE(index_of(src, L"CaBbaGE", 0, true) == correct_index);

}

TEST_CASE("typename StringType::size_type index_of(const StringType& text, const StringType& needle, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function typename StringType::size_type index_of(const StringType& text, const StringType& needle, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	const wstring needle{ L"banana" };

	wstring::size_type correct_index = src.find(needle);

	REQUIRE(index_of(src, needle) == correct_index);

	correct_index = src.find(L"cabbage");

	REQUIRE(index_of(src, wstring{ L"cabbage" }) == correct_index);

	REQUIRE(index_of(src, wstring{ L"CaBbaGe" }, 0, true) == correct_index);

}

TEST_CASE("bool contains(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool contains(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u,\
		 bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	REQUIRE(contains(src, L'b'));

	REQUIRE(!contains(src, L'x'));

	REQUIRE(contains(src, L'B', 0, true));

	REQUIRE(!contains(src, L'X', 0, true));

}

TEST_CASE("bool contains(const StringType& text, typename StringType::const_pointer needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool contains(const StringType& text, typename StringType::const_pointer needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	REQUIRE(contains(src, L"banana"));

	REQUIRE(contains(src, L"CaBbaGE", 0, true));

	REQUIRE(!contains(src, L"pear"));

	REQUIRE(!contains(src, L"PEAR", 0, true));
}

TEST_CASE("bool contains(const StringType& text, const StringType& needle, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool contains(const StringType& text, const StringType& needle, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"apple,banana,cabbage,lemon,orange,pepper,plum" };

	const wstring needle{ L"banana" };

	REQUIRE(contains(src, needle));

	REQUIRE(contains(src, wstring{L"CaBbAgE"}, true));

	REQUIRE(!contains(src, wstring{ L"pear" }));

}

TEST_CASE("bool ends_with(const StringType& text, const typename StringType::value_type end_char, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool ends_with(const StringType& text, const typename StringType::value_type end_char, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const wstring src{ L"Apples" };

	REQUIRE(ends_with(src, L's'));

	REQUIRE(ends_with(src, L'S', true));

}

TEST_CASE("bool ends_with(const StringType& src, const typename StringType::const_pointer end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool ends_with(const StringType& src, const typename StringType::const_pointer end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const u32string src{ U"Apple is one my favorite, most beloved fruits." };

	REQUIRE(ends_with(src, U"fruits."));

	REQUIRE(ends_with(src, U"FrUiTs.", true));
}

TEST_CASE("bool ends_with(const StringType& src, const StringType& end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})",
	"Testing global template function bool ends_with(const StringType& src, const StringType& end_tag, bool ignore_case = false, const std::locale& loc = std::locale{})")
{
	const u32string src{ U"Apple is one my favorite, most beloved fruits." };

	const u32string needle{ U"fruits." };

	REQUIRE(ends_with(src, needle));

	REQUIRE(ends_with(src, u32string{ U"FrUiTs." }, true));

}

TEST_CASE("void unused_args(Args&&... args)",
	"Testing global template function void unused_args(Args&&... args)")
{
	int number{ 42 };
	const wchar_t* important_message = L"Number 42 is the meaning of life.";

	struct NumberInfo
	{
		NumberInfo() : number{ 42 }, message{ L"Number 42 is the meaning of life." } { }
		
		NumberInfo(int num, const wchar_t* msg) : number{ num }, message{ msg } { }
			
		int number;

		const wchar_t* message;

	} num_info;

	unused_args(number, important_message, num_info);

}

TEST_CASE("bool has_value(const T& container, const typename T::value_type& item)",
	"Testing global template function bool has_value(const T& container, const typename T::value_type& item)")
{
	const wstring src{ L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const wstring needle{ L":|:" };

	const auto parts{ split(src, needle) };

	REQUIRE(has_value(parts, L"orange"));

	REQUIRE(!has_value(parts, L"grapefruit"));

}

TEST_CASE("bool has_value(T& container, const typename T::value_type& item)",
	"Testing global template function bool has_value(T& container, const typename T::value_type& item)")
{
	const u32string src{ U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const u32string needle{ U":|:" };

	auto parts{ split(src, needle) };

	REQUIRE(has_value(parts, U"orange"));

	REQUIRE(!has_value(parts, U"grapefruit"));

}

TEST_CASE("bool has_key(const T& container, const typename T::key_type& key)",
	"Testing global template function bool has_key(const T& container, const typename T::key_type& key)")
{
	const wstring src{ L"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const wstring needle{ L":|:" };

	const auto parts{ split(src, needle) };

	const set<wstring> fruits{cbegin(parts), cend(parts)};

	REQUIRE(has_value(fruits, L"orange"));
	
	REQUIRE(!has_value(fruits, L"pear"));

}

TEST_CASE("bool has_key(T& container, const typename T::key_type& key)",
	"Testing global template function bool has_key(T& container, const typename T::key_type& key)")
{
	const u32string src{ U"apple:|:banana:|:cabbage:|:lemon:|:orange:|:pepper:|:plum" };

	const u32string needle{ U":|:" };

	auto parts{ split(src, needle) };

	map<u32string, size_t> ordered_fruits{};

	static random_device rd{};

	mt19937 rand_engine{ rd() };

	auto const num_distr = uniform_int_distribution<>(1, 10);
		
	for (auto const& fruit : parts)
	{
		ordered_fruits[fruit] = num_distr(rand_engine);

	}

	REQUIRE(has_key(ordered_fruits, U"orange" ));

	REQUIRE(!has_key(ordered_fruits, U"pear" ));

}
