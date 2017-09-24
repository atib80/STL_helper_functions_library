#ifndef _STL_HELPER_FUNCTIONS_H_
#define _STL_HELPER_FUNCTIONS_H_

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <typeinfo>
#include <cwchar>
#include <locale>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>


#define STL_HELPER_UTILITY_MAJOR_VERSION 1
#define STL_HELPER_UTILITY_MINOR_VERSION 0

#define PRINT_VAR_NAME(arg) std::cout << #arg << ' '
#define PRINT_VAR_NAMEW(arg) std::wcout << #arg << L' '

namespace std
{
	namespace helper
	{
		enum class string_type { cstr, wstr, u16_str, u32_str };

		/**
		 * \brief constexpr function returns RTTI data (a const reference to a type_info struct) about its single argument
		 * \tparam T template parameter T specifies compile-time data type of passed argument 'var'
		 * \param var argument of type const T& passed
		 * \return const reference to struct type_info that contains RTTI information about specified argument 'var'
		 */
		template <typename T>
		constexpr const type_info& get_type_id(const T& var)
		{
			return typeid(var);
		}

		template <typename T>
		const char* get_type_name(T&& var)
		{
			return typeid(var).name();
		}

		template <typename T>
		const wchar_t* get_type_name_w(T&& var)
		{
			const string cstr{typeid(var).name()};

			return wstring{cbegin(cstr), cend(cstr)}.c_str();
		}

		template <typename T>
		const char16_t* get_type_name_u16(T&& var)
		{
			const string cstr{typeid(var).name()};

			return u16string{cbegin(cstr), cend(cstr)}.c_str();
		}

		template <typename T>
		const char32_t* get_type_name_u32(T&& var)
		{
			const string cstr{typeid(var).name()};

			return u32string{cbegin(cstr), cend(cstr)}.c_str();
		}

		constexpr bool are_data_types_equal()
		{
			return true;
		}

		template <typename T, typename ...Args>
		constexpr bool are_data_types_equal(T&& arg, Args&&... args)
		{
			return get_type_id(arg) == are_data_types_equal(args);
		}

		template <typename T, typename U, typename ...Args>
		constexpr bool check_data_types_for_equality(const T& arg1, const U& arg2, Args&&... args)
		{
			constexpr auto result = are_data_types_equal(forward<Args>(args)...);

			return (get_type_id(arg1) == get_type_id(arg2)) == result;
		}

		template <typename T>
		void show_var_info(const T& arg)
		{
			cout << "\nName: ";
			PRINT_VAR_NAME(arg);
			cout << "\nType: " << get_type_name(arg) << "\nValue: " << arg << endl;
		}

		template <typename T>
		void show_var_info_w(const T& arg)
		{
			wcout << L"\nName: ";
			PRINT_VAR_NAMEW(arg);
			wcout << L"\nType: " << get_type_name(arg) << L"\nValue: " << arg << endl;
		}

		template <typename... Args>
		int say_slow(const size_t time_delay_in_ms, const char* format_string, Args ... args)
		{
			auto const buffer_size = _scprintf(format_string, args...) + 1;

			char* output_buffer = new char[buffer_size]{};

			if (!output_buffer) return -1;

			_snprintf(output_buffer, buffer_size, format_string, args...);

			auto sleep_on{true};

			int final_ret_val{};

			for (size_t i = 0; i < strlen(output_buffer); ++i)
			{
				auto const ret_val = printf("%c", output_buffer[i]);

				if (ret_val < 0) return final_ret_val;

				final_ret_val += ret_val;

				if (sleep_on) std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));

				if (_kbhit())
				{
					_getch();

					sleep_on = false;
				}
			}

			delete[] output_buffer;

			output_buffer = nullptr;

			return final_ret_val;
		}

		template <typename... Args>
		int say_slow(const size_t time_delay_in_ms, const wchar_t* format_string, Args ... args)
		{
			auto const buffer_size = _scwprintf(format_string, args...) + 1;

			wchar_t* output_buffer = new wchar_t[buffer_size]{};

			if (!output_buffer) return -1;

			_snwprintf(output_buffer, buffer_size, format_string, args...);

			auto sleep_on{true};

			int final_ret_val{};

			for (size_t i = 0; i < wcslen(output_buffer); ++i)
			{
				auto const ret_val = wprintf(L"%c", output_buffer[i]);

				if (ret_val < 0) return final_ret_val;

				final_ret_val += ret_val;

				if (sleep_on) std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));

				if (_kbhit())
				{
					_getch();

					sleep_on = false;
				}
			}

			delete[] output_buffer;

			output_buffer = nullptr;

			return final_ret_val;
		}

		template <typename... Args>
		int say(const char* format_string, Args ... args)
		{
			auto const buffer_size = _scprintf(format_string, args...) + 1;

			char* output_buffer = new char[buffer_size] {};

			if (!output_buffer) return -1;

			_snprintf(output_buffer, buffer_size, format_string, args...);

			auto const ret_val = printf("%s", output_buffer);

			delete[] output_buffer;

			output_buffer = nullptr;

			return ret_val;
		}

		template <typename... Args>
		int say(const wchar_t* format_string, Args ... args)
		{
			auto const buffer_size = _scwprintf(format_string, args...) + 1;

			wchar_t* output_buffer = new wchar_t[buffer_size]{};

			if (!output_buffer) return -1;

			_snwprintf(output_buffer, buffer_size, format_string, args...);

			auto const ret_val = wprintf(L"%s", output_buffer);

			delete[] output_buffer;

			output_buffer = nullptr;

			return ret_val;
		}

		bool trim(char* str);
		bool trim(wchar_t* str);
		bool trim(char16_t* str);
		bool trim(char32_t* str);

		bool ltrim(char* str);
		bool ltrim(wchar_t* str);
		bool ltrim(char16_t* str);
		bool ltrim(char32_t* str);

		bool rtrim(char* str);
		bool rtrim(wchar_t* str);
		bool rtrim(char16_t* str);
		bool rtrim(char32_t* str);

		string trim(const char* str);
		wstring trim(const wchar_t* str);
		u16string trim(const char16_t* str);
		u32string trim(const char32_t* str);

		string ltrim(const char* str);
		wstring ltrim(const wchar_t* str);
		u16string ltrim(const char16_t* str);
		u32string ltrim(const char32_t* str);

		string rtrim(const char* str);
		wstring rtrim(const wchar_t* str);
		u16string rtrim(const char16_t* str);
		u32string rtrim(const char32_t* str);

		constexpr size_t MAX_STRING_LENGTH = static_cast<size_t>((2ULL << 31ULL) - 1ULL);

		size_t u16_strlen(const char16_t* str);
		size_t u32_strlen(const char32_t* str);

		int u16_strcmp(const char16_t* str1, const char16_t* str2);
		int u32_strcmp(const char32_t* str1, const char32_t* str2);

		int u16_strncmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare);
		int u32_strncmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare);

		int u16_stricmp(const char16_t* str1, const char16_t* str2, const std::locale& loc = std::locale{});
		int u32_stricmp(const char32_t* str1, const char32_t* str2, const std::locale& loc = std::locale{});

		int u16_strnicmp(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare,
		                 const std::locale& loc = std::locale{});
		int u32_strnicmp(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare,
		                 const std::locale& loc = std::locale{});

		char16_t* u16_strcpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src);
		char32_t* u32_strcpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src);

		char16_t* u16_strncpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src,
		                      const size_t number_of_characters_to_copy);
		char32_t* u32_strncpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src,
		                      const size_t number_of_characters_to_copy);

		char16_t* u16_strcat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src);
		char32_t* u32_strcat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src);

		char16_t* u16_strncat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src,
		                      const size_t number_of_characters_to_concatenate);
		char32_t* u32_strncat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src,
		                      const size_t number_of_characters_to_concatenate);

		const char16_t* u16_strstr(const char16_t* src, const char16_t* needle);
		const char32_t* u32_strstr(const char32_t* src, const char32_t* needle);

		char16_t* u16_strstr(char16_t* src, const char16_t* needle);
		char32_t* u32_strstr(char32_t* src, const char32_t* needle);

		const char16_t* u16_strstri(const char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{});
		const char32_t* u32_strstri(const char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{});

		char16_t* u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{});
		char32_t* u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{});

		template <typename StringType>
		StringType trim(const StringType& str)
		{
			size_t begin = 0u;
			size_t end = str.size() - 1;

			using char_type = typename StringType::value_type;

			if (str.size() == 0u) return StringType{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (static_cast<char_type>(str[begin]))
				{
				case static_cast<char_type>(' '):
				case static_cast<char_type>('\t'):
				case static_cast<char_type>('\n'):
				case static_cast<char_type>('\r'):
				case static_cast<char_type>('\f'):
				case static_cast<char_type>('\v'):
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return StringType{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (static_cast<char_type>(str[end]))
				{
				case static_cast<char_type>(' '):
				case static_cast<char_type>('\t'):
				case static_cast<char_type>('\n'):
				case static_cast<char_type>('\r'):
				case static_cast<char_type>('\f'):
				case static_cast<char_type>('\v'):
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return str.substr(begin, end - begin + 1);
		}

		template <typename StringType>
		StringType ltrim(const StringType& str)
		{
			size_t begin = 0u;
			size_t const end = str.size() - 1;

			using char_type = typename StringType::value_type;

			if (str.size() == 0u) return StringType{};

			for (auto is_ws_char{true}; (is_ws_char && (begin <= end)); ++begin)
			{
				switch (static_cast<char_type>(str[begin]))
				{
				case static_cast<char_type>(' '):
				case static_cast<char_type>('\t'):
				case static_cast<char_type>('\n'):
				case static_cast<char_type>('\r'):
				case static_cast<char_type>('\f'):
				case static_cast<char_type>('\v'):
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return StringType{};

			return str.substr(begin, end - begin + 1);
		}

		template <typename StringType>
		StringType rtrim(const StringType& str)
		{
			size_t begin = 0u;
			size_t end = str.size() - 1;

			using char_type = typename StringType::value_type;

			if (str.size() == 0u) return StringType{};

			for (auto is_ws_char{true}; (is_ws_char && (end != StringType::npos)); --end)
			{
				switch (static_cast<char_type>(str[end]))
				{
				case static_cast<char_type>(' '):
				case static_cast<char_type>('\t'):
				case static_cast<char_type>('\n'):
				case static_cast<char_type>('\r'):
				case static_cast<char_type>('\f'):
				case static_cast<char_type>('\v'):
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (end == StringType::npos) return StringType{};

			return str.substr(begin, end - begin + 1);
		}

		std::vector<std::string> split(const char* source, const char needle_char, int const max_count = -1);
		std::vector<std::wstring> split(const wchar_t* source, const wchar_t needle_char, int const max_count = -1);
		std::vector<std::u16string> split(const char16_t* source, const char16_t needle_char, int const max_count = -1);
		std::vector<std::u32string> split(const char32_t* source, const char32_t needle_char, int const max_count = -1);

		std::vector<std::string> split(const char* source, const char* needle, const int max_count = -1);
		std::vector<std::wstring> split(const wchar_t* source, const wchar_t* needle, const int max_count = -1);
		std::vector<std::u16string> split(const char16_t* source, const char16_t* needle, const int max_count = -1);
		std::vector<std::u32string> split(const char32_t* source, const char32_t* needle, const int max_count = -1);

		template <typename StringType>
		std::vector<StringType> split(const StringType& source, const typename StringType::value_type needle_char,
		                              size_t const max_count = StringType::npos)
		{
			std::vector<StringType> parts{};

			size_t prev = 0, current;

			StringType needle_st(1, needle_char);

			const size_t needle_len = needle_st.size();

			if ((source.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source.size())) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source.find(needle_st, prev);

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len; // source = "apple|pear|plum|cherry|orange", needle = "|"

				if (prev >= source.size()) break;
			}
			while (StringType::npos != current);

			if (number_of_parts > 0 && prev < source.size())
			{
				if (StringType::npos == max_count) parts.emplace_back(source.substr(prev));

				else if ((StringType::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
			}

			return parts;
		}

		template <typename StringType>
		std::vector<StringType> split(const StringType& source, typename StringType::const_pointer needle,
		                              size_t const max_count = StringType::npos)
		{
			std::vector<StringType> parts{};

			size_t prev = 0, current;

			StringType needle_st{needle};

			const size_t needle_len = needle_st.size();

			if ((source.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source.size())) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source.find(needle_st, prev);

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len; // source = "apple|pear|plum|cherry|orange", needle = "|"

				if (prev >= source.size()) break;
			}
			while (StringType::npos != current);

			if (number_of_parts > 0 && prev < source.size())
			{
				if (StringType::npos == max_count) parts.emplace_back(source.substr(prev));

				else if ((StringType::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
			}

			return parts;
		}

		template <typename StringType>
		std::vector<StringType> split(const StringType& source, const StringType& needle,
		                              size_t const max_count = StringType::npos)
		{
			std::vector<StringType> parts{};

			size_t prev = 0, current;

			const size_t needle_len = needle.size();

			if ((source.size() == 0) || (needle.size() == 0) || (needle.size() >= source.size())) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source.find(needle, prev);

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len; // source = "apple|pear|plum|cherry|orange", needle = "|"

				if (prev >= source.size()) break;
			}
			while (StringType::npos != current);

			if (number_of_parts > 0 && prev < source.size())
			{
				if (StringType::npos == max_count) parts.emplace_back(source.substr(prev));

				else if ((StringType::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
			}

			return parts;
		}

		template <typename StringType>
		bool starts_with(const StringType& src, const typename StringType::value_type start_char, bool ignore_case = false,
		                 const std::locale& loc = std::locale{})
		{
			if (src.size() == 0) return false;

			if (!ignore_case)
			{
				return (src[0] == start_char);
			}

			return (std::tolower(src[0], loc) == std::tolower(start_char, loc));
		}

		template <typename StringType>
		bool starts_with(const StringType& src, typename StringType::const_pointer start_tag, bool ignore_case = false,
		                 const std::locale& loc = std::locale{})
		{
			const StringType start_word{start_tag};

			if ((src.size() == 0) || (start_word.size() == 0) || (start_word.size() > src.size())) return false;

			if (!ignore_case)
			{
				if (src.find(start_word) == 0) return true;

				return false;
			}


			StringType src_lc{src};

			StringType start_tag_lc{start_word};

			std::transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			std::transform(begin(start_word), end(start_word), begin(start_tag_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			if (src_lc.find(start_tag_lc) == 0) return true;

			return false;
		}

		template <typename StringType>
		bool starts_with(const StringType& src, const StringType& start_tag, bool ignore_case = false,
		                 const std::locale& loc = std::locale{})
		{
			if ((src.size() == 0) || (start_tag.size() == 0) || (start_tag.size() > src.size())) return false;

			if (!ignore_case)
			{
				if (src.find(start_tag) == 0) return true;

				return false;
			}

			StringType src_lc{src};

			StringType start_tag_lc{start_tag};

			std::transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			std::transform(begin(start_tag), end(start_tag), begin(start_tag_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			if (src_lc.find(start_tag_lc) == 0) return true;

			return false;
		}

		template <typename StringType>
		typename StringType::size_type index_of(const StringType& text, const typename StringType::value_type needle_char,
		                                        const size_t start_pos = 0u, bool ignore_case = false,
		                                        const std::locale& loc = std::locale{})
		{
			StringType needle_str(1, needle_char);

			if (text.size() == 0) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle_str, start_pos);
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_str_lc(1, std::tolower(needle_char, loc));

			return text_lc.find(needle_str_lc, start_pos);
		}

		template <typename StringType>
		typename StringType::size_type index_of(const StringType& text, typename StringType::const_pointer needle,
		                                        const size_t start_pos = 0u, bool ignore_case = false,
		                                        const std::locale& loc = std::locale{})
		{
			StringType needle_str{needle};

			if ((text.size() == 0) || (needle_str.size() == 0) || (needle_str.size() > text.size())) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle_str, start_pos);
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_lc{needle_str};

			std::transform(begin(needle_str), end(needle_str), begin(needle_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			return text_lc.find(needle_lc, start_pos);
		}

		template <typename StringType>
		typename StringType::size_type index_of(const StringType& text, const StringType& needle, const size_t start_pos = 0u,
		                                        bool ignore_case = false,
		                                        const std::locale& loc = std::locale{})
		{
			if ((text.size() == 0) || (needle.size() == 0) || (needle.size() > text.size())) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle, start_pos);
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_lc{needle};

			std::transform(begin(needle), end(needle), begin(needle_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			return text_lc.find(needle_lc, start_pos);
		}

		template <typename StringType>
		bool contains(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u,
		              bool ignore_case = false,
		              const std::locale& loc = std::locale{})
		{
			StringType needle_str(1, needle_char);

			if (text.size() == 0) return false;

			if (!ignore_case)
			{
				if (text.find(needle_str, start_pos) != StringType::npos) return true;

				return false;
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_str_lc(1, std::tolower(needle_char, loc));

			if (text_lc.find(needle_str_lc, start_pos) != StringType::npos) return true;

			return false;
		}

		template <typename StringType>
		bool contains(const StringType& text, typename StringType::const_pointer needle, const size_t start_pos = 0u,
		              bool ignore_case = false,
		              const std::locale& loc = std::locale{})
		{
			StringType needle_str{needle};

			if ((text.size() == 0) || (needle_str.size() == 0) || (needle_str.size() > text.size())) return false;

			if (!ignore_case)
			{
				if (text.find(needle_str, start_pos) != StringType::npos) return true;

				return false;
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_str_lc{needle_str};

			std::transform(begin(needle_str), end(needle_str), begin(needle_str_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			if (text_lc.find(needle_str_lc, start_pos) != StringType::npos) return true;

			return false;
		}

		template <typename StringType>
		bool contains(const StringType& text, const StringType& needle, bool ignore_case = false,
		              const std::locale& loc = std::locale{})
		{
			if ((text.size() == 0) || (needle.size() == 0) || (needle.size() > text.size())) return false;

			if (!ignore_case)
			{
				if (text.find(needle) != StringType::npos) return true;

				return false;
			}

			StringType text_lc{text};

			std::transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			StringType needle_lc{needle};

			std::transform(begin(needle), end(needle), begin(needle_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			if (text_lc.find(needle_lc) != StringType::npos) return true;

			return false;
		}

		template <typename StringType>
		bool ends_with(const StringType& text, const typename StringType::value_type end_char, bool ignore_case = false,
		               const std::locale& loc = std::locale{})
		{
			if (text.size() == 0) return false;

			if (!ignore_case)
			{
				return (text.back() == end_char);
			}

			return (std::tolower(text.back(), loc) == std::tolower(end_char, loc));
		}

		template <typename StringType>
		bool ends_with(const StringType& src, typename StringType::const_pointer end_tag, bool ignore_case = false,
		               const std::locale& loc = std::locale{})
		{
			const StringType end_word{end_tag};

			if ((src.size() == 0) || (end_word.size() == 0) || (end_word.size() > src.size())) return false;

			auto expected_start_pos_of_end_tag = src.size() - end_word.size();

			if (!ignore_case)
			{
				if (src.find(end_word) == expected_start_pos_of_end_tag) return true;

				return false;
			}

			StringType src_lc{src};

			StringType end_tag_lc{end_word};

			std::transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			std::transform(begin(end_word), end(end_word), begin(end_tag_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			expected_start_pos_of_end_tag = src_lc.size() - end_tag_lc.size();

			if (src_lc.find(end_tag_lc) == expected_start_pos_of_end_tag) return true;

			return false;
		}

		template <typename StringType>
		bool ends_with(const StringType& src, const StringType& end_tag, bool ignore_case = false,
		               const std::locale& loc = std::locale{})
		{
			if ((src.size() == 0) || (end_tag.size() == 0) || (end_tag.size() > src.size())) return false;

			auto expected_start_pos_of_end_tag = src.size() - end_tag.size();

			if (!ignore_case)
			{
				if (src.find(end_tag) == expected_start_pos_of_end_tag) return true;

				return false;
			}

			StringType src_lc{src};

			StringType end_tag_lc{end_tag};

			std::transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			std::transform(begin(end_tag), end(end_tag), begin(end_tag_lc), [&loc](const auto ch)
		               {
			               return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
		               });

			expected_start_pos_of_end_tag = src_lc.size() - end_tag_lc.size();

			if (src_lc.find(end_tag_lc) == expected_start_pos_of_end_tag) return true;

			return false;
		}

		template <typename ...Args>
		void unused_args(Args&&...)
		{
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const map<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const map<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const multimap<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const multimap<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_map<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_map<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_multimap<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_multimap<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(map<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(map<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(multimap<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(multimap<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_map<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_map<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_multimap<KeyType, ValueType>& container, const KeyType& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_multimap<KeyType, ValueType>& container, typename KeyType::const_pointer key)
		{
			return (container.find(key) != end(container));
		}

		template <typename ContainerType>
		bool has_value(const ContainerType& container, const typename ContainerType::value_type& search_value)
		{
			return (find(cbegin(container), cend(container), search_value) != cend(container));
		}

		template <typename ContainerType>
		bool has_value(ContainerType& container, const typename ContainerType::value_type& search_value)
		{
			return (find(begin(container), end(container), search_value) != end(container));
		}

		/*template <typename ValueType>
		bool has_value(const set<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const set<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const multiset<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const multiset<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const unordered_set<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const unordered_set<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const unordered_multiset<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(const unordered_multiset<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_value(set<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(set<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(multiset<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(multiset<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(unordered_set<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(unordered_set<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(unordered_multiset<ValueType>& container, const ValueType& item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_value(unordered_multiset<ValueType>& container, typename ValueType::const_pointer item)
		{
			return (container.find(item) != end(container));
		}*/
	}
}

#endif /* _STL_HELPER_FUNCTIONS_H_ */
