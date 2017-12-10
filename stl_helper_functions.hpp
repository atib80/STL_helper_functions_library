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
#include <memory>
#include <filesystem>

#define STL_HELPER_UTILITY_MAJOR_VERSION 1
#define STL_HELPER_UTILITY_MINOR_VERSION 0

#define PRINT_VAR_NAME(arg) std::cout << #arg << ' '
#define PRINT_VAR_NAMEW(arg) std::wcout << #arg << L' '

namespace std
{
	namespace helper
	{
		enum class string_type { cstr, wstr, u16_str, u32_str };

		template <typename T>
		constexpr const type_info& get_type_id(const T&)
		{
			return typeid(T);
		}

		template <typename T>
		string get_type_name(T&&)
		{
			return string { typeid(T).name() };
		}

		template <typename T>
		wstring get_type_name_wstr(T&&)
		{
			const string cstr{typeid(T).name()};

			return wstring { cbegin(cstr), cend(cstr) };
		}

		template <typename T>
		u16string get_type_name_u16str(T&&)
		{
			const string cstr{typeid(T).name()};

			return u16string { cbegin(cstr), cend(cstr) };
		}

		template <typename T>
		u32string get_type_name_u32str(T&&)
		{
			const string cstr{typeid(T).name()};

			return u32string { cbegin(cstr), cend(cstr) };
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

		struct char_buffer_deleter
		{
			using pointer_type = char*;

			void operator()(pointer_type pointer) const noexcept
			{
				if (pointer)
				{
					delete[] pointer;
				}
			}
		};

		struct wchar_t_buffer_deleter
		{
			using pointer_type = wchar_t*;

			void operator()(pointer_type pointer) const noexcept
			{
				if (pointer)
				{
					delete[] pointer;
				}
			}
		};

		template <typename... Args>
		int say_slow(const size_t time_delay_in_ms, const char* format_string, Args ... args)
		{
			auto const buffer_size = _scprintf(format_string, args...) + 1;

			unique_ptr<char[], char_buffer_deleter> output_buffer_sp(new char[buffer_size], char_buffer_deleter{});

			if (!output_buffer_sp) return -1;

			_snprintf(output_buffer_sp.get(), buffer_size, format_string, args...);

			auto sleep_on{true};

			int final_ret_val{};

			for (size_t i = 0; i < strlen(output_buffer_sp.get()); ++i)
			{
				auto const ret_val = printf("%c", output_buffer_sp.get()[i]);

				if (ret_val < 0) return final_ret_val;

				final_ret_val += ret_val;

				if (sleep_on) std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));

				if (_kbhit())
				{
					(void)_getch();

					sleep_on = false;
				}
			}

			return final_ret_val;
		}

		template <typename... Args>
		int say_slow(const size_t time_delay_in_ms, const wchar_t* format_string, Args ... args)
		{
			auto const buffer_size = _scwprintf(format_string, args...) + 1;

			unique_ptr<wchar_t[], wchar_t_buffer_deleter> output_buffer_sp(new wchar_t[buffer_size], wchar_t_buffer_deleter{});

			if (!output_buffer_sp) return -1;

			_snwprintf(output_buffer_sp.get(), buffer_size, format_string, args...);

			auto sleep_on{true};

			int final_ret_val{};

			for (size_t i = 0; i < wcslen(output_buffer_sp.get()); ++i)
			{
				auto const ret_val = wprintf(L"%c", output_buffer_sp.get()[i]);

				if (ret_val < 0) return final_ret_val;

				final_ret_val += ret_val;

				if (sleep_on) std::this_thread::sleep_for(std::chrono::milliseconds(time_delay_in_ms));

				if (_kbhit())
				{
					(void)_getch();

					sleep_on = false;
				}
			}

			return final_ret_val;
		}

		template <typename... Args>
		int say(const char* format_string, Args ... args)
		{
			auto const buffer_size = _scprintf(format_string, args...) + 1;

			unique_ptr<char[], char_buffer_deleter> output_buffer_sp(new char[buffer_size], char_buffer_deleter{});

			if (!output_buffer_sp) return -1;

			_snprintf(output_buffer_sp.get(), buffer_size, format_string, args...);

			auto const ret_val = printf("%s", output_buffer_sp.get());

			return ret_val;
		}

		template <typename... Args>
		int say(const wchar_t* format_string, Args ... args)
		{
			auto const buffer_size = _scwprintf(format_string, args...) + 1;

			unique_ptr<wchar_t[], wchar_t_buffer_deleter> output_buffer_sp(new wchar_t[buffer_size], wchar_t_buffer_deleter{});

			if (!output_buffer_sp) return -1;

			_snwprintf(output_buffer_sp.get(), buffer_size, format_string, args...);

			auto const ret_val = wprintf(L"%s", output_buffer_sp.get());

			return ret_val;
		}

		constexpr size_t max_string_length = static_cast<size_t>((2ULL << 31ULL) - 1ULL);

		size_t str_length(char* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(wchar_t* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(char16_t* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(char32_t* str, const size_t max_allowed_string_length = max_string_length);

		size_t str_length(const char* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(const wchar_t* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(const char16_t* str, const size_t max_allowed_string_length = max_string_length);
		size_t str_length(const char32_t* str, const size_t max_allowed_string_length = max_string_length);

		template <typename StringType>
		size_t str_length(const StringType& str, const size_t max_allowed_string_length = max_string_length)
		{
			auto const str_len{ str.size() };

			return (str_len > max_allowed_string_length ? max_allowed_string_length : str_len);
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


		bool str_starts_with(const char* src, const char start_char, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const wchar_t* src, const wchar_t start_char, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const char16_t* src, const char16_t start_char, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const char32_t* src, const char32_t start_char, bool ignore_case = false, const std::locale& loc = std::locale{});

		bool str_starts_with(const char* src, const char* start_tag, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const wchar_t* src, const wchar_t* start_tag, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const char16_t* src, const char16_t* start_tag, bool ignore_case = false, const std::locale& loc = std::locale{});
		bool str_starts_with(const char32_t* src, const char32_t* start_tag, bool ignore_case = false, const std::locale& loc = std::locale{});
		
		template <typename StringType>
		bool str_starts_with(const StringType& src, const typename StringType::value_type start_char, bool ignore_case = false,
			const std::locale& loc = std::locale{})
		{
			if (0u == src.size()) return false;

			if (!ignore_case)
			{
				return (src[0] == start_char);
			}

			return (std::tolower(start_char, loc) == std::tolower(src[0], loc) );
		}

		template <typename StringType>
		bool str_starts_with(const StringType& src, typename StringType::const_pointer start_tag, bool ignore_case = false,
			const std::locale& loc = std::locale{})
		{
			const auto start_tag_str{ start_tag };

			const auto src_len{ src.size() };
			const auto start_tag_len{ start_tag_str.size() };

			if ((0u == src_len) || (0u == start_tag_len ) || (start_tag_len > src_len)) return false;

			if (!ignore_case)
			{
				if (0u == src.find(start_tag_str)) return true;

				return false;
			}


			StringType src_lc{ src };

			StringType start_tag_lc{ start_tag_str };

			std::transform(cbegin(src), cend(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
			});

			std::transform(cbegin(start_tag_str), cend(start_tag_str), begin(start_tag_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
			});

			if (0u == src_lc.find(start_tag_lc)) return true;

			return false;
		}

		template <typename StringType>
		bool str_starts_with(const StringType& src, const StringType& start_tag, bool ignore_case = false,
			const std::locale& loc = std::locale{})
		{
			
			const auto src_len{ src.size() };
			const auto start_tag_len{ start_tag.size() };

			if ((0u == src_len) || (0u == start_tag_len) || (start_tag_len > src_len)) return false;

			if (!ignore_case)
			{
				if (0u == src.find(start_tag)) return true;

				return false;
			}

			StringType src_lc{ src };

			StringType start_tag_lc{ start_tag };

			std::transform(cbegin(src), cend(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
			});

			std::transform(cbegin(start_tag), cend(start_tag), begin(start_tag_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(std::tolower(ch, loc));
			});

			if (0u == src_lc.find(start_tag_lc)) return true;

			return false;
		}

		size_t str_index_of(const char* text, const char needle_char, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const wchar_t* text, const wchar_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const char16_t* text, const char16_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const char32_t* text, const char32_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});

		size_t str_index_of(const char* text, const char* needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const wchar_t* text, const wchar_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const char16_t* text, const char16_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});
		size_t str_index_of(const char32_t* text, const char32_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const std::locale& loc = std::locale{});

		template <typename StringType>
		typename StringType::size_type str_index_of(const StringType& text, const typename StringType::value_type needle_char,
			const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{})
		{
			const StringType needle_str(1, needle_char);

			if (0u == text.size()) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle_str, start_pos);
			}

			StringType text_lc{ text };

			transform(cbegin(text), cend(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_str_lc(1, tolower(needle_char, loc));

			return text_lc.find(needle_str_lc, start_pos);
		}

		template <typename StringType>
		typename StringType::size_type str_index_of(const StringType& text, typename StringType::const_pointer needle,
			const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{})
		{
			const StringType needle_str{ needle };

			const auto text_len{ text.size() };
			const auto needle_len{ needle_str.size() };

			if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len)) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle_str, start_pos);
			}

			StringType text_lc{ text };

			transform(cbegin(text), cend(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_lc{ needle_str };

			transform(cbegin(needle_str), cend(needle_str), begin(needle_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			return text_lc.find(needle_lc, start_pos);
		}

		template <typename StringType>
		typename StringType::size_type str_index_of(const StringType& text, const StringType& needle, const size_t start_pos = 0u,
			bool ignore_case = false, const locale& loc = locale{})
		{
			const auto text_len{ text.size() };
			const auto needle_len{ needle.size() };

			if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len)) return StringType::npos;

			if (!ignore_case)
			{
				return text.find(needle, start_pos);
			}

			StringType text_lc{ text };

			transform(cbegin(text), cend(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_lc{ needle };

			transform(cbegin(needle), cend(needle), begin(needle_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			return text_lc.find(needle_lc, start_pos);
		}

		bool str_contains(const char* src, const char needle_char, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const wchar_t* src, const wchar_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const char16_t* src, const char16_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const char32_t* src, const char32_t needle_char, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});

		bool str_contains(const char* src, const char* needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const wchar_t* src, const wchar_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const char16_t* src, const char16_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});
		bool str_contains(const char32_t* src, const char32_t* needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{});

		template <typename StringType>
		bool str_contains(const StringType& text, const typename StringType::value_type needle_char, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{})
		{
			const StringType needle_str(1, needle_char);

			if (0u == text.size()) return false;

			if (!ignore_case)
			{
				if (StringType::npos != text.find(needle_str, start_pos)) return true;

				return false;
			}

			StringType text_lc{ text };

			transform(cbegin(text), cend(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_str_lc(1, tolower(needle_char, loc));

			if (StringType::npos != text_lc.find(needle_str_lc, start_pos)) return true;

			return false;
		}

		template <typename StringType>
		bool str_contains(const StringType& text, typename StringType::const_pointer needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{})
		{
			StringType needle_str{ needle };

			const auto text_len{ text.size() };
			const auto needle_len{ needle_str.size() };

			if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len)) return false;

			if (!ignore_case)
			{
				if (text.find(needle_str, start_pos) != StringType::npos) return true;

				return false;
			}

			StringType text_lc{ text };

			transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_str_lc{ needle_str };

			transform(begin(needle_str), end(needle_str), begin(needle_str_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			if (text_lc.find(needle_str_lc, start_pos) != StringType::npos) return true;

			return false;
		}

		template <typename StringType>
		bool str_contains(const StringType& text, const StringType& needle, const size_t start_pos = 0u, bool ignore_case = false, const locale& loc = locale{})
		{
			const auto text_len{ text.size() };
			const auto needle_len{ needle.size() };

			if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len)) return false;

			if (!ignore_case)
			{
				if (StringType::npos != text.find(needle, start_pos)) return true;

				return false;
			}

			StringType text_lc{ text };

			transform(cbegin(text), cend(text), begin(text_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			StringType needle_lc{ needle };

			transform(cbegin(needle), cend(needle), begin(needle_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			if (StringType::npos != text_lc.find(needle_lc, start_pos)) return true;

			return false;
		}

		bool str_ends_with(const char* src, const char end_char, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const wchar_t* src, const wchar_t end_char, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const char16_t* src, const char16_t end_char, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const char32_t* src, const char32_t end_char, bool ignore_case = false, const locale& loc = locale{});

		bool str_ends_with(const char* src, const char* end_tag, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const wchar_t* src, const wchar_t* end_tag, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const char16_t* src, const char16_t* end_tag, bool ignore_case = false, const locale& loc = locale{});
		bool str_ends_with(const char32_t* src, const char32_t* end_tag, bool ignore_case = false, const locale& loc = locale{});

		template <typename StringType>
		bool str_ends_with(const StringType& text, const typename StringType::value_type end_char, bool ignore_case = false, const locale& loc = locale{})
		{
			if (0u == text.size()) return false;

			if (!ignore_case)
			{
				return (text.back() == end_char);
			}

			return (tolower(end_char, loc) == tolower(text.back(), loc));
		}

		template <typename StringType>
		bool str_ends_with(const StringType& src, typename StringType::const_pointer end_tag, bool ignore_case = false, const locale& loc = locale{})
		{
			const StringType end_tag_str{ end_tag };
			const auto src_len{ src.size() };
			const auto end_tag_len{ end_tag_str.size() };

			if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len)) return false;

			const auto expected_start_pos_of_end_tag = src_len - end_tag_len;

			if (!ignore_case)
			{
				if (expected_start_pos_of_end_tag == src.find(end_tag_str)) return true;

				return false;
			}

			StringType src_lc{ src };

			StringType end_tag_lc_str{ end_tag_str };

			transform(cbegin(src), cend(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			transform(cbegin(end_tag_str), cend(end_tag_str), begin(end_tag_lc_str), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			if (expected_start_pos_of_end_tag == src_lc.find(end_tag_lc_str)) return true;

			return false;
		}

		template <typename StringType>
		bool str_ends_with(const StringType& src, const StringType& end_tag, bool ignore_case = false, const locale& loc = locale{})
		{
			const auto src_len{ src.size() };
			const auto end_tag_len{ end_tag.size() };

			if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len)) return false;

			const auto expected_start_pos_of_end_tag = src_len - end_tag_len;

			if (!ignore_case)
			{
				if (expected_start_pos_of_end_tag == src.find(end_tag)) return true;

				return false;
			}

			StringType src_lc{ src };

			StringType end_tag_lc{ end_tag };

			transform(cbegin(src), cend(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			transform(cbegin(end_tag), cend(end_tag), begin(end_tag_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::value_type>(tolower(ch, loc));
			});

			if (expected_start_pos_of_end_tag == src_lc.find(end_tag_lc)) return true;

			return false;
		}

		template <typename ...Args>
		void unused_args(Args&&...)
		{
		}

		template <typename ValueType>
		bool has_key(const set<ValueType>& container, const typename set<ValueType>::key_type& item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_key(set<ValueType>& container, const typename set<ValueType>::key_type& item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_key(const multiset<ValueType>& container, const typename multiset<ValueType>::key_type item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_key(multiset<ValueType>& container, const typename multiset<ValueType>::key_type item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_key(const unordered_set<ValueType>& container, const typename unordered_set<ValueType>::key_type item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_key(unordered_set<ValueType>& container, const typename unordered_set<ValueType>::key_type item)
		{
			return (container.find(item) != end(container));
		}

		template <typename ValueType>
		bool has_key(const unordered_multiset<ValueType>& container,
			const typename unordered_multiset<ValueType>::key_type item)
		{
			return (container.find(item) != cend(container));
		}

		template <typename ValueType>
		bool has_key(unordered_multiset<ValueType>& container, const typename unordered_multiset<ValueType>::key_type item)
		{
			return (container.find(item) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const map<KeyType, ValueType>& container, const typename map<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(map<KeyType, ValueType>& container, const typename map<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const multimap<KeyType, ValueType>& container,
			const typename multimap<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(multimap<KeyType, ValueType>& container, const typename multimap<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_map<KeyType, ValueType>& container,
			const typename unordered_map<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_map<KeyType, ValueType>& container,
			const typename unordered_map<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != end(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(const unordered_multimap<KeyType, ValueType>& container,
			const typename unordered_multimap<KeyType, ValueType>::key_type& key)
		{
			return (container.find(key) != cend(container));
		}

		template <typename KeyType, typename ValueType>
		bool has_key(unordered_multimap<KeyType, ValueType>& container,
			const typename unordered_multimap<KeyType, ValueType>::key_type& key)
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

		int str_compare(const char* str1, const char* str2);
		int str_compare(const wchar_t* str1, const wchar_t* str2);
		int str_compare(const char16_t* str1, const char16_t* str2);
		int str_compare(const char32_t* str1, const char32_t* str2);

		template <typename StringType>
		int str_compare(const StringType& str1, const StringType& str2)
		{
			using char_type = typename StringType::value_type;

			auto citr1 = cbegin(str1);
			auto citr2 = cbegin(str2);

			for (; ((citr1 != cend(str1)) && (citr2 != cend(str2))); ++citr1 , ++citr2)
			{
				if (*citr1 != *citr2) return static_cast<int>(*citr1 - *citr2);
			}

			auto const final_str1_ch = (citr1 == cend(str1) ? static_cast<char_type>(0) : *citr1);
			auto const final_str2_ch = (citr2 == cend(str2) ? static_cast<char_type>(0) : *citr2);

			return static_cast<int>(final_str1_ch - final_str2_ch);
		}

		int str_compare_n(const char* str1, const char* str2, size_t number_of_characters_to_compare);
		int str_compare_n(const wchar_t* str1, const wchar_t* str2, size_t number_of_characters_to_compare);
		int str_compare_n(const char16_t* str1, const char16_t* str2, size_t number_of_characters_to_compare);
		int str_compare_n(const char32_t* str1, const char32_t* str2, size_t number_of_characters_to_compare);


		template <typename StringType>
		int str_compare_n(const StringType& str1, const StringType& str2, size_t number_of_characters_to_compare)
		{
			auto const str1_len = str1.size();
			auto const str2_len = str2.size();

			if (str1_len < number_of_characters_to_compare || str2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(str1_len, str2_len);
			}

			for (auto i = size_t{ 0u }; i < number_of_characters_to_compare; i++)
			{
				if (str1[i] != str2[i]) return static_cast<int>(str1[i] - str2[i]);
			}

			return 0;
		}

		int str_compare_i(const char* str1, const char* str2, const locale& loc = std::locale{});
		int str_compare_i(const wchar_t* str1, const wchar_t* str2, const locale& loc = std::locale{});
		int str_compare_i(const char16_t* str1, const char16_t* str2, const locale& loc = std::locale{});
		int str_compare_i(const char32_t* str1, const char32_t* str2, const locale& loc = std::locale{});


		template <typename StringType>
		int str_compare_i(const StringType& str1, const StringType& str2, const locale& loc = std::locale{})
		{
			auto citr1 = cbegin(str1);
			auto citr2 = cbegin(str2);

			for (; ((citr1 != cend(str1)) && (citr2 != cend(str2))); ++citr1 , ++citr2)
			{
				auto const ch1 = std::tolower(*citr1, loc);

				auto const ch2 = std::tolower(*citr2, loc);

				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return static_cast<int>(std::tolower(*citr1, loc) - std::tolower(*citr2, loc));
		}		

		template <typename StringType>
		int str_compare_n_i(const StringType& str1, const StringType& str2, size_t number_of_characters_to_compare,
		                    const std::locale& loc = std::locale{})
		{
			auto const str1_len = str1.size();
			auto const str2_len = str2.size();

			if (str1_len < number_of_characters_to_compare || str2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(str1_len, str2_len);
			}

			for (size_t i = 0u; i < number_of_characters_to_compare; ++str1 , ++str2 , ++i)
			{
				auto const ch1 = std::tolower(str1[i], loc);

				auto const ch2 = std::tolower(str2[i], loc);

				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return 0;
		}		

		enum class str_copy_behavior { disallow_partial_copy, allow_partial_copy, do_not_copy_return_required_dst_buffer_capacity_only };

		template <size_t ARRAY_SIZE>
		size_t str_copy(char (&dst)[ARRAY_SIZE], const char* src, const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			const auto ret_val { src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;			

			if (ARRAY_SIZE < (src_len + 1)) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy) {

					auto const no_of_chars_to_copy = ARRAY_SIZE - 1;

					copy(src, src + no_of_chars_to_copy, dst);

					dst[no_of_chars_to_copy] = '\0';

					return no_of_chars_to_copy;

				}

			}
				
			copy(src, src + src_len, dst);

			dst[src_len] = '\0';

			return src_len;	

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_copy(wchar_t (&dst)[ARRAY_SIZE], const wchar_t* src, const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			const auto ret_val{ src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < (src_len + 1)) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy) {

					auto const no_of_chars_to_copy = ARRAY_SIZE - 1;

					copy(src, src + no_of_chars_to_copy, dst);

					dst[no_of_chars_to_copy] = L'\0';

					return no_of_chars_to_copy;

				}

			}

			copy(src, src + src_len, dst);

			dst[src_len] = L'\0';

			return src_len;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_copy(char16_t (&dst)[ARRAY_SIZE], const char16_t* src, const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{

			auto const src_len = str_length(src);

			const auto ret_val{ src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < (src_len + 1)) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy) {

					auto const no_of_chars_to_copy = ARRAY_SIZE - 1;

					copy(src, src + no_of_chars_to_copy, dst);

					dst[no_of_chars_to_copy] = u'\0';

					return no_of_chars_to_copy;

				}

			}

			copy(src, src + src_len, dst);

			dst[src_len] = u'\0';

			return src_len;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_copy(char32_t (&dst)[ARRAY_SIZE], const char32_t* src, const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			const auto ret_val{ src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < (src_len + 1)) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy) {

					auto const no_of_chars_to_copy = ARRAY_SIZE - 1;

					copy(src, src + no_of_chars_to_copy, dst);

					dst[no_of_chars_to_copy] = U'\0';

					return no_of_chars_to_copy;

				}

			}

			copy(src, src + src_len, dst);

			dst[src_len] = U'\0';

			return src_len;

		}

		size_t str_copy(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src, 
						const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		size_t str_copy(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src,
						const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);
						
		size_t str_copy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, 
						const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		size_t str_copy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, 
						const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_copy(const StringType& src)
		{
			return StringType{ src };
		}

		template <typename StringTypeLeft, typename StringTypeRight = StringTypeLeft>
		void str_copy(StringTypeLeft& dst, const StringTypeRight& src)
		{
			dst.assign(src);
		}

		template <size_t ARRAY_SIZE>
		size_t str_copy_n(char(&dst)[ARRAY_SIZE], const char* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			const auto ret_val{ noctc + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {
			
				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy)				
				{
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
		size_t str_copy_n(wchar_t(&dst)[ARRAY_SIZE], const wchar_t* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			const auto ret_val{ noctc + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy)
				{
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
		size_t str_copy_n(char16_t(&dst)[ARRAY_SIZE], const char16_t* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			const auto ret_val{ noctc + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy)
				{
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
		size_t str_copy_n(char32_t(&dst)[ARRAY_SIZE], const char32_t* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			const auto ret_val{ noctc + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (copy_options == str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (copy_options == str_copy_behavior::disallow_partial_copy) return 0u;

				if (copy_options == str_copy_behavior::allow_partial_copy)
				{
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

		size_t str_copy_n(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		size_t str_copy_n(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src, const size_t number_of_characters_to_copy,
						  const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		size_t str_copy_n(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_copy,
			              const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);

		size_t str_copy_n(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_copy,
			              const str_copy_behavior copy_options = str_copy_behavior::disallow_partial_copy, size_t* required_dst_capacity = nullptr);


		template <typename StringType>
		StringType str_copy_n(const StringType& dst, const StringType& src, const size_t number_of_characters_to_copy)
		{
			
			return src.substr(0, number_of_characters_to_copy);

		}

		template <typename StringType>
		void str_copy_n(StringType& dst, const StringType& src, const size_t number_of_characters_to_copy)
		{
			dst.assign(src.substr(0, number_of_characters_to_copy));
		}

		enum class str_append_behavior {
			disallow_partial_append, allow_partial_append, do_not_append_return_required_dst_buffer_capacity_only
		};

		template <size_t ARRAY_SIZE>
		size_t str_append(char (&dst)[ARRAY_SIZE], const char* src, const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			const auto ret_val{ dst_len + src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (append_options == str_append_behavior::disallow_partial_append) return ret_val;

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
		size_t str_append(wchar_t(&dst)[ARRAY_SIZE], const wchar_t* src, const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			const auto ret_val{ dst_len + src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (append_options == str_append_behavior::disallow_partial_append) return ret_val;

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
		size_t str_append(char16_t(&dst)[ARRAY_SIZE], const char16_t* src, const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			const auto ret_val{ dst_len + src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (append_options == str_append_behavior::disallow_partial_append) return ret_val;

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
		size_t str_append(char32_t(&dst)[ARRAY_SIZE], const char32_t* src, const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			const auto ret_val{ dst_len + src_len + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if (ARRAY_SIZE < ret_val) {

				if (append_options == str_append_behavior::disallow_partial_append) return ret_val;

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
		
		size_t str_append(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src, 
						  const str_append_behavior append_behavior = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src, 
						  const str_append_behavior append_behavior = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, 
						  const str_append_behavior append_behavior = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, 
						  const str_append_behavior append_behavior = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_append(const StringType& dst, const StringType& src)
		{
			return StringType{ dst + src};
		}

		template <typename StringType>
		void str_append(StringType& dst, const StringType& src)
		{
			dst += src;
		}

		template <size_t ARRAY_SIZE>
		size_t str_append_n(char(&dst)[ARRAY_SIZE], const char* src, const size_t number_of_characters_to_append, 
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			const auto str_len{ str_length(src) };

			const auto dst_len{ str_length(dst) };			

			auto no_of_chars_to_append = min(str_len, number_of_characters_to_append);

			const size_t ret_val { dst_len + no_of_chars_to_append + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;
			
			if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1))
			{
				if (append_options == str_append_behavior::disallow_partial_append)
				{

					return 0u;

				}
				
				if (append_options == str_append_behavior::allow_partial_append)
				{
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
		size_t str_append_n(wchar_t(&dst)[ARRAY_SIZE], const wchar_t* src, const size_t number_of_characters_to_append, 
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			
			const auto str_len{ str_length(src) };

			const auto dst_len{ str_length(dst) };

			auto no_of_chars_to_append = min(str_len, number_of_characters_to_append);

			const size_t ret_val{ dst_len + no_of_chars_to_append + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1))
			{
				if (append_options == str_append_behavior::disallow_partial_append)
				{

					return 0u;

				}

				if (append_options == str_append_behavior::allow_partial_append)
				{
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
		size_t str_append_n(char16_t(&dst)[ARRAY_SIZE], const char16_t* src, const size_t number_of_characters_to_append, 
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			const auto str_len{ str_length(src) };

			const auto dst_len{ str_length(dst) };

			auto no_of_chars_to_append = min(str_len, number_of_characters_to_append);

			const size_t ret_val{ dst_len + no_of_chars_to_append + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1))
			{
				if (append_options == str_append_behavior::disallow_partial_append)
				{

					return 0u;

				}

				if (append_options == str_append_behavior::allow_partial_append)
				{
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
		size_t str_append_n(char32_t(&dst)[ARRAY_SIZE], const char32_t* src, const size_t number_of_characters_to_append, 
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr)
		{
			const auto str_len{ str_length(src) };

			const auto dst_len{ str_length(dst) };

			auto no_of_chars_to_append = min(str_len, number_of_characters_to_append);

			const size_t ret_val{ dst_len + no_of_chars_to_append + 1 };

			if (required_dst_capacity) *required_dst_capacity = ret_val;

			if (append_options == str_append_behavior::do_not_append_return_required_dst_buffer_capacity_only) return ret_val;

			if ((dst_len + no_of_chars_to_append) > (ARRAY_SIZE - 1))
			{
				if (append_options == str_append_behavior::disallow_partial_append) return 0u;				

				if (append_options == str_append_behavior::allow_partial_append)
				{
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

		size_t str_append_n(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src, const size_t number_of_characters_to_append,
						    const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append_n(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src, const size_t number_of_characters_to_append,
			                const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append_n(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, const size_t number_of_characters_to_append,
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);
		size_t str_append_n(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, const size_t number_of_characters_to_append,
							const str_append_behavior append_options = str_append_behavior::disallow_partial_append, size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_append_n(const StringType& dst, const StringType& src, const size_t number_of_characters_to_append)
		{
			return StringType {dst += src.substr(0, number_of_characters_to_append) };
		}

		template <typename StringType>
		void str_append_n(StringType& dst, const StringType& src, const size_t number_of_characters_to_append)
		{
			dst += src.substr(0, number_of_characters_to_append);
		}

		enum class str_prepend_behaviour {
			disallow_partial_prepend, allow_partial_prepend, do_not_prepend_return_required_dst_buffer_capacity_only
		};


		template <size_t ARRAY_SIZE>
		size_t str_prepend(char(&dst)[ARRAY_SIZE], const char* src, const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{

					ret_val = 0u;

				}
				else
				{
					/*for (auto start = 0u; start != src_len; start++)
					{

						dst[dst + dst_len + src_len - 1 - start] = dst[dst + dst_len - 1 - start];
						

					}*/

					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{
					auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

					copy(src, src + no_of_chars_to_copy, dst);

					dst[ARRAY_SIZE - 1] = '\0';

					ret_val = no_of_chars_to_copy;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;
		}

		template <size_t ARRAY_SIZE>
		size_t str_prepend(wchar_t(&dst)[ARRAY_SIZE], const wchar_t* src, const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{

			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{
					auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

					copy(src, src + no_of_chars_to_copy, dst);

					dst[ARRAY_SIZE - 1] = '\0';

					ret_val = no_of_chars_to_copy;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;

		}

		template <size_t ARRAY_SIZE>
		size_t str_prepend(char16_t(&dst)[ARRAY_SIZE], const char16_t* src, const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{

			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{
					auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

					copy(src, src + no_of_chars_to_copy, dst);

					dst[ARRAY_SIZE - 1] = '\0';

					ret_val = no_of_chars_to_copy;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = '\0';

					ret_val = src_len;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;

		}

		template <size_t ARRAY_SIZE>
		size_t str_prepend(char32_t(&dst)[ARRAY_SIZE], const char32_t* src, const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = U'\0';

					ret_val = src_len;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < (dst_len + src_len + 1))
				{
					auto const no_of_chars_to_copy = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

					copy(src, src + no_of_chars_to_copy, dst);

					dst[ARRAY_SIZE - 1] = U'\0';

					ret_val = no_of_chars_to_copy;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

					copy(src, src + src_len, dst);

					dst[dst_len + src_len] = U'\0';

					ret_val = src_len;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;

		}

		size_t str_prepend(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src, 
						   const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr);
		size_t str_prepend(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src,
		                   const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr);
		size_t str_prepend(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src, 
						   const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr);
		size_t str_prepend(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src, 
						   const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_prepend(const StringType& dst, const StringType& src)
		{
			return StringType{src + dst};
		}

		template <typename StringType>
		void str_prepend(StringType& dst, const StringType& src)
		{
			dst.insert(0, src);
		}

		template <size_t ARRAY_SIZE>
		size_t str_prepend_n(char (&dst)[ARRAY_SIZE], const char* src, const size_t number_of_characters_to_prepend, 
							 const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{

			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocp = number_of_characters_to_prepend > src_len ? src_len : number_of_characters_to_prepend;

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocp + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < dst_len + nocp + 1)
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = '\0';

					ret_val = nocp;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < dst_len + nocp + 1)
				{
					nocp = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = '\0';

					ret_val = nocp;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = '\0';

					ret_val = nocp;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocp + 1;

			return ret_val;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_prepend_n(wchar_t (&dst)[ARRAY_SIZE], const wchar_t* src, const size_t number_of_characters_to_prepend,
							 const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocp = number_of_characters_to_prepend > src_len ? src_len : number_of_characters_to_prepend;

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocp + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < dst_len + nocp + 1)
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = L'\0';

					ret_val = nocp;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < dst_len + nocp + 1)
				{
					nocp = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = L'\0';

					ret_val = nocp;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = L'\0';

					ret_val = nocp;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocp + 1;

			return ret_val;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_prepend_n(char16_t (&dst)[ARRAY_SIZE], const char16_t* src, const size_t number_of_characters_to_prepend,
							 const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{

			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocp = number_of_characters_to_prepend > src_len ? src_len : number_of_characters_to_prepend;

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocp + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < dst_len + nocp + 1)
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = u'\0';

					ret_val = nocp;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < dst_len + nocp + 1)
				{
					nocp = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = u'\0';

					ret_val = nocp;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = u'\0';

					ret_val = nocp;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocp + 1;

			return ret_val;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_prepend_n(char32_t (&dst)[ARRAY_SIZE], const char32_t* src, const size_t number_of_characters_to_prepend,
						     const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocp = number_of_characters_to_prepend > src_len ? src_len : number_of_characters_to_prepend;

			size_t ret_val{};

			if (prepend_options == str_prepend_behaviour::do_not_prepend_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocp + 1;

			}
			else if (prepend_options == str_prepend_behaviour::disallow_partial_prepend) {

				if (ARRAY_SIZE < dst_len + nocp + 1)
				{

					ret_val = 0u;

				}
				else
				{

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = U'\0';

					ret_val = nocp;
				}

			}
			else if (prepend_options == str_prepend_behaviour::allow_partial_prepend)
			{
				if (ARRAY_SIZE < dst_len + nocp + 1)
				{
					nocp = ARRAY_SIZE - dst_len - 1;

					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = U'\0';

					ret_val = nocp;

				}
				else
				{
					copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

					copy(src, src + nocp, dst);

					dst[dst_len + nocp] = U'\0';

					ret_val = nocp;

				}

			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocp + 1;

			return ret_val;

		}

		size_t str_prepend_n(char* dst, const size_t dst_capacity_in_number_of_characters, const char* src,
		                     const size_t number_of_characters_to_prepend,
		                     const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend,
		                     size_t* required_dst_capacity = nullptr);

		size_t str_prepend_n(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const wchar_t* src,
		                     const size_t number_of_characters_to_prepend,
		                     const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend,
		                     size_t* required_dst_capacity = nullptr);

		size_t str_prepend_n(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src,
		                     const size_t number_of_characters_to_prepend,
		                     const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend,
		                     size_t* required_dst_capacity = nullptr);

		size_t str_prepend_n(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src,
		                     const size_t number_of_characters_to_prepend,
		                     const str_prepend_behaviour prepend_options = str_prepend_behaviour::disallow_partial_prepend,
		                     size_t* required_dst_capacity = nullptr);


		template <typename StringType>
		StringType str_prepend_n(const StringType& dst, const StringType& src, size_t number_of_characters_to_prepend)
		{
			number_of_characters_to_prepend = number_of_characters_to_prepend <= src.size()
				                                  ? number_of_characters_to_prepend
				                                  : src.size();

			StringType final_str{src.substr(0, number_of_characters_to_prepend) + dst};

			return final_str;
		}

		template <typename StringType>
		void str_prepend_n(StringType& dst, const StringType& src, size_t number_of_characters_to_prepend)
		{
			number_of_characters_to_prepend = number_of_characters_to_prepend <= src.size()
				                                  ? number_of_characters_to_prepend
				                                  : src.size();

			dst.insert(0, src.substr(0, number_of_characters_to_prepend));
		}

		enum class str_insert_behaviour {
			disallow_partial_insert, allow_partial_insert, do_not_insert_return_required_dst_buffer_capacity_only
		};

		template <size_t ARRAY_SIZE>
		size_t str_insert(char (&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr)
		{			
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;
				
				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			} else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + src_len + 1))) {

					ret_val = 0u;
			
			} else {

					auto const nocti = min(ARRAY_SIZE - position_index_in_dst - 1, src_len);

					copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

					copy(src, src + nocti, dst + position_index_in_dst);						

					dst[dst_len + nocti] = '\0';

					ret_val = nocti;
			}			

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;
		}

		template <size_t ARRAY_SIZE>
		size_t str_insert(wchar_t (&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const wchar_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr)
		{
			
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + src_len + 1))) {

				ret_val = 0u;

			}
			else {

				auto const nocti = min(ARRAY_SIZE - position_index_in_dst - 1, src_len);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = L'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;
		}

		template <size_t ARRAY_SIZE>
		size_t str_insert(char16_t (&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char16_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + src_len + 1))) {

				ret_val = 0u;

			}
			else {

				auto const nocti = min(ARRAY_SIZE - position_index_in_dst - 1, src_len);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = u'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;
		}

		template <size_t ARRAY_SIZE>
		size_t str_insert(char32_t (&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char32_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + src_len + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + src_len + 1))) {

				ret_val = 0u;

			}
			else {

				auto const nocti = min(ARRAY_SIZE - position_index_in_dst - 1, src_len);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = U'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + src_len + 1;

			return ret_val;
		}

		size_t str_insert(char* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst,
		                  const char* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr);

		size_t str_insert(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst,
		                  const wchar_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr);

		size_t str_insert(char16_t* dst, const size_t dst_capacity_in_number_of_characters,
		                  const size_t position_index_in_dst, const char16_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr);

		size_t str_insert(char32_t* dst, const size_t dst_capacity_in_number_of_characters,
		                  const size_t position_index_in_dst, const char32_t* src,
		                  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
		                  size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_insert(const StringType& dst, const size_t position_index_in_dst, const StringType& src)
		{
			auto const dst_len { dst.size() };

			if (!dst_len && (0u == position_index_in_dst)) return StringType{ src };

			StringType final_str{dst};

			final_str.insert(position_index_in_dst, src);

			return final_str;
		}

		template <typename StringType>
		void str_insert(StringType& dst, const size_t position_index_in_dst, const StringType& src)
		{
			auto const dst_len { dst.size() };

			if (!dst_len && (0u == position_index_in_dst)) dst = src;

			dst.insert(position_index_in_dst, src);
		}

		template <size_t ARRAY_SIZE>
		size_t str_insert_n(char(&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char* src, const size_t number_of_characters_to_insert,
					       const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocti = min(number_of_characters_to_insert, src_len);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocti + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + nocti + 1))) {

				ret_val = 0u;

			}
			else {

				nocti = min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = '\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

			return ret_val;		


		}
		
		template <size_t ARRAY_SIZE>
		size_t str_insert_n(wchar_t (&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const wchar_t* src, const size_t number_of_characters_to_insert,
							  const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocti = min(number_of_characters_to_insert, src_len);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocti + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + nocti + 1))) {

				ret_val = 0u;

			}
			else {

				nocti = min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = L'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

			return ret_val;
		}
		
		template <size_t ARRAY_SIZE>
		size_t str_insert_n(char16_t(&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char16_t* src, const size_t number_of_characters_to_insert,
							   const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocti = min(number_of_characters_to_insert, src_len);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocti + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + nocti + 1))) {

				ret_val = 0u;

			}
			else {

				nocti = min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = u'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

			return ret_val;

		}
		
		template <size_t ARRAY_SIZE>
		size_t str_insert_n(char32_t(&dst)[ARRAY_SIZE], const size_t position_index_in_dst, const char32_t* src, const size_t number_of_characters_to_insert,
							   const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert, size_t* required_dst_capacity = nullptr)
		{
			auto const src_len = str_length(src);
			auto const dst_len = str_length(dst);

			auto nocti = min(number_of_characters_to_insert, src_len);

			if (position_index_in_dst > dst_len)
			{
				if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

				return 0u;
			}

			size_t ret_val;

			if (insert_options == str_insert_behaviour::do_not_insert_return_required_dst_buffer_capacity_only)
			{
				ret_val = dst_len + nocti + 1;

			}
			else if ((insert_options == str_insert_behaviour::disallow_partial_insert) && (ARRAY_SIZE < (dst_len + nocti + 1))) {

				ret_val = 0u;

			}
			else {

				nocti = min(ARRAY_SIZE - position_index_in_dst - 1, nocti);

				copy_backward(dst + position_index_in_dst, dst + dst_len, dst + dst_len + nocti);

				copy(src, src + nocti, dst + position_index_in_dst);

				dst[dst_len + nocti] = U'\0';

				ret_val = nocti;
			}

			if (required_dst_capacity) *required_dst_capacity = dst_len + nocti + 1;

			return ret_val;

		}

		size_t str_insert_n(char* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst, const char* src,
						   const size_t number_of_characters_to_insert, const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert, 
						   size_t* required_dst_capacity = nullptr);

		size_t str_insert_n(wchar_t* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst, const wchar_t* src,
							  const size_t number_of_characters_to_insert, const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
							  size_t* required_dst_capacity = nullptr);

		size_t str_insert_n(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst, const char16_t* src,
						       const size_t number_of_characters_to_insert, const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
							   size_t* required_dst_capacity = nullptr);
			
		size_t str_insert_n(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const size_t position_index_in_dst, const char32_t* src,
							   const size_t number_of_characters_to_insert, const str_insert_behaviour insert_options = str_insert_behaviour::disallow_partial_insert,
							   size_t* required_dst_capacity = nullptr);

		template <typename StringType>
		StringType str_insert_n(const StringType& dst, const size_t position_index_in_dst, const StringType& src,
		                        const size_t number_of_characters_to_insert)
		{		

			const auto dst_length { dst.size() };

			const auto src_length { src.size() };

			const auto no_of_chars = min(number_of_characters_to_insert, src_length);

			if (!dst_length && (0u == position_index_in_dst)) return StringType { src.substr(0, no_of_chars) };	

			StringType final_str { dst };

			final_str.insert(position_index_in_dst, src.substr(0, no_of_chars));

			return final_str;
		}

		template <typename StringType>
		void str_insert_n(StringType& dst, const size_t position_index_in_dst, const StringType& src,
		                  const size_t number_of_characters_to_insert)
		{
			const auto dst_length { dst.size() };

			const auto src_length { src.size() };

			const auto no_of_chars = min(number_of_characters_to_insert, src_length);

			if (!dst_length && (0u == position_index_in_dst)) dst = src.substr(0, no_of_chars);

			dst.insert(position_index_in_dst, src.substr(0, no_of_chars));
		}

		// enum class str_replace_behavior { no_partial_replace, allow_partial_place, do_not_replace_return_required_dst_capacity_only };

		template <size_t ARRAY_SIZE>
		size_t str_replace_first(char (&dst)[ARRAY_SIZE], const char* needle, const char* replace, size_t* required_dst_capacity = nullptr)
		{			

			auto const dst_len{ str_length(dst) };
			auto const needle_len{ str_length(needle) };
			auto const replace_len{ str_length(replace) };

			size_t rdc;

			if (needle_len > dst_len) {

				rdc = max(dst_len, replace_len);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			rdc = dst_len - needle_len + replace_len;

			auto const start_pos = str_index_of(dst, needle);

			if (start_pos == string::npos) {				

				if (required_dst_capacity) *required_dst_capacity = rdc;
				
				return 0u;
			
			}

			if ((ARRAY_SIZE - 1) < rdc)
			{

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;			
			} 

			if (needle_len == replace_len)
			{				
				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;
				
				return 1u;
			}

			if (needle_len < replace_len)
			{
				
				auto const noctm = replace_len - needle_len;

				// if needle_len == 2 and replace_len == 10, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward the end of dst.

				copy_backward(dst + start_pos + needle_len, dst + dst_len, dst + dst_len + noctm); 

				dst[dst_len + noctm] = '\0';

				copy(replace, replace + replace_len, dst + start_pos);				

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			
			} else // needle_len > replace_len
			{
				auto const noctm = needle_len - replace_len;

				// if needle_len == 10 and replace_len == 2, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward dst + start_pos + replace_len.
				
				for (auto i = 0; i < dst_len - (start_pos + needle_len) ; i++) dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

				dst[dst_len - noctm] = '\0';

				copy(replace, replace + replace_len, dst + start_pos);
				
				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}

		}

		template <size_t ARRAY_SIZE>
		size_t str_replace_first(wchar_t (&dst)[ARRAY_SIZE], const wchar_t* needle, const wchar_t* replace, size_t* required_dst_capacity = nullptr)
		{
			auto const dst_len{ str_length(dst) };
			auto const needle_len{ str_length(needle) };
			auto const replace_len{ str_length(replace) };

			size_t rdc;

			if (needle_len > dst_len) {

				rdc = max(dst_len, replace_len);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			rdc = dst_len - needle_len + replace_len;

			auto const start_pos = str_index_of(dst, needle);

			if (start_pos == wstring::npos) {

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;

			}

			if ((ARRAY_SIZE - 1) < rdc)
			{

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			if (needle_len == replace_len)
			{
				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}

			if (needle_len < replace_len)
			{

				auto const noctm = replace_len - needle_len;

				// if needle_len == 2 and replace_len == 10, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward the end of dst.

				copy_backward(dst + start_pos + needle_len, dst + dst_len, dst + dst_len + noctm);

				dst[dst_len + noctm] = L'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;

			}
			else // needle_len > replace_len
			{
				auto const noctm = needle_len - replace_len;

				// if needle_len == 10 and replace_len == 2, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward dst + start_pos + replace_len.

				for (auto i = 0; i < dst_len - (start_pos + needle_len); i++) dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

				dst[dst_len - noctm] = L'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}
		}

		template <size_t ARRAY_SIZE>
		size_t str_replace_first(char16_t (&dst)[ARRAY_SIZE], const char16_t* needle, const char16_t* replace, size_t* required_dst_capacity = nullptr)
		{
			auto const dst_len{ str_length(dst) };
			auto const needle_len{ str_length(needle) };
			auto const replace_len{ str_length(replace) };

			size_t rdc;

			if (needle_len > dst_len) {

				rdc = max(dst_len, replace_len);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			rdc = dst_len - needle_len + replace_len;

			auto const start_pos = str_index_of(dst, needle);

			if (start_pos == u16string::npos) {

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;

			}

			if ((ARRAY_SIZE - 1) < rdc)
			{

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			if (needle_len == replace_len)
			{
				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}

			if (needle_len < replace_len)
			{

				auto const noctm = replace_len - needle_len;

				// if needle_len == 2 and replace_len == 10, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward the end of dst.

				copy_backward(dst + start_pos + needle_len, dst + dst_len, dst + dst_len + noctm);

				dst[dst_len + noctm] = u'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;

			}
			else // needle_len > replace_len
			{
				auto const noctm = needle_len - replace_len;

				// if needle_len == 10 and replace_len == 2, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward dst + start_pos + replace_len.

				for (auto i = 0; i < dst_len - (start_pos + needle_len); i++) dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

				dst[dst_len - noctm] = u'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}
		}

		template <size_t ARRAY_SIZE>
		size_t str_replace_first(char32_t (&dst)[ARRAY_SIZE], const char32_t* needle, const char32_t* replace, size_t* required_dst_capacity = nullptr)
		{
			auto const dst_len{ str_length(dst) };
			auto const needle_len{ str_length(needle) };
			auto const replace_len{ str_length(replace) };

			size_t rdc;

			if (needle_len > dst_len) {

				rdc = max(dst_len, replace_len);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			rdc = dst_len - needle_len + replace_len;

			auto const start_pos = str_index_of(dst, needle);

			if (start_pos == u32string::npos) {

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;

			}

			if ((ARRAY_SIZE - 1) < rdc)
			{

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 0u;
			}

			if (needle_len == replace_len)
			{
				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}

			if (needle_len < replace_len)
			{

				auto const noctm = replace_len - needle_len;

				// if needle_len == 2 and replace_len == 10, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward the end of dst.

				copy_backward(dst + start_pos + needle_len, dst + dst_len, dst + dst_len + noctm);

				dst[dst_len + noctm] = U'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;

			}
			else // needle_len > replace_len
			{
				auto const noctm = needle_len - replace_len;

				// if needle_len == 10 and replace_len == 2, all the characters in the upper part of dst ( characters with positions >= dst + start_pos + needle_len characters ) 
				// have to be moved 'noctm' (8) character positions toward dst + start_pos + replace_len.

				for (auto i = 0; i < dst_len - (start_pos + needle_len); i++) dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

				dst[dst_len - noctm] = U'\0';

				copy(replace, replace + replace_len, dst + start_pos);

				if (required_dst_capacity) *required_dst_capacity = rdc;

				return 1u;
			}
		}

		size_t str_replace_first(char *dst, const size_t dst_capacity_in_number_of_characters, const char* needle, const char* replace, size_t* required_dst_capacity = nullptr);
		size_t str_replace_first(wchar_t *dst, const size_t dst_capacity_in_number_of_characters, const char* needle, const char* replace, size_t* required_dst_capacity = nullptr);
		size_t str_replace_first(char16_t *dst, const size_t dst_capacity_in_number_of_characters, const char* needle, const char* replace, size_t* required_dst_capacity = nullptr);
		size_t str_replace_first(char32_t *dst, const size_t dst_capacity_in_number_of_characters, const char* needle, const char* replace, size_t* required_dst_capacity = nullptr);

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_replace_nth(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle,
			const size_t nth_index = 1)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_replace_last(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_replace_all(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_replace_first_n(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle,
			const size_t number_of_copies_to_replace = 1)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_replace_last_n(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle,
			const size_t number_of_copies_to_replace = 1)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_first(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_nth(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_last(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_all(typename remove_const<CharacterPointerType>::type src,
		                                                                typename add_const<CharacterPointerType>::type needle)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_first_n(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle,
			const size_t number_of_copies_to_erase)
		{
			return nullptr;
		}

		template <typename CharacterPointerType>
		typename remove_const<CharacterPointerType>::type str_erase_last_n(
			typename remove_const<CharacterPointerType>::type src, typename add_const<CharacterPointerType>::type needle,
			const size_t number_of_copies_to_erase)
		{
			return nullptr;
		}


		const char* strstr(const char* src, const char* needle);
		const wchar_t* strstr(const wchar_t* src, const wchar_t* needle);
		const char16_t* strstr(const char16_t* src, const char16_t* needle);
		const char32_t* strstr(const char32_t* src, const char32_t* needle);

		template <typename StringType>
		size_t strstr(const StringType& src, const StringType& needle)
		{

			return src.find(needle);

		}

		char* strstr(char* src, const char* needle);
		wchar_t* strstr(wchar_t* src, const wchar_t* needle);
		char16_t* strstr(char16_t* src, const char16_t* needle);
		char32_t* strstr(char32_t* src, const char32_t* needle);

		template <typename StringType>
		size_t strstr(StringType& src, const StringType& needle)
		{

			return src.find(needle);

		}

		const char* strstri(const char* src, const char* needle, const std::locale& loc = std::locale{});
		const wchar_t* strstri(const wchar_t* src, const wchar_t* needle, const std::locale& loc = std::locale{});
		const char16_t* strstri(const char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{});
		const char32_t* strstri(const char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{});

		template <typename StringType>
		size_t strstri(const StringType& src, const StringType& needle, const std::locale& loc = std::locale{})
		{

			StringType src_lc{ src };
			StringType needle_lc{ needle };

			transform(begin(src), end(src), begin(src_lc), [&](const char ch)
			{
				return tolower(ch, loc);
			});

			transform(begin(needle), end(needle), begin(needle_lc), [&](const char ch)
			{
				return tolower(ch, loc);
			});

			return src_lc.find(needle_lc);
		}

		char* strstri(char* src, const char* needle, const std::locale& loc = std::locale{});
		wchar_t* strstri(wchar_t* src, const wchar_t* needle, const std::locale& loc = std::locale{});
		char16_t* strstri(char16_t* src, const char16_t* needle, const std::locale& loc = std::locale{});
		char32_t* strstri(char32_t* src, const char32_t* needle, const std::locale& loc = std::locale{});

		template <typename StringType>
		size_t strstri(StringType& src, const StringType& needle, const std::locale& loc = std::locale{})
		{

			StringType src_lc{ src };
			StringType needle_lc{ needle };

			transform(begin(src), end(src), begin(src_lc), [&](const char ch)
			{
				return tolower(ch, loc);
			});

			transform(begin(needle), end(needle), begin(needle_lc), [&](const char ch)
			{
				return tolower(ch, loc);
			});

			return src_lc.find(needle_lc);

		}

		template <typename StringType>
		StringType to_lower_case(const StringType& str, const std::locale loc = std::locale{})
		{
			using char_type = typename StringType::value_type;

			StringType final_str{ str };

			transform(begin(str), end(str), begin(final_str), [](const char_type ch)
			{
				return tolower(ch, loc);
			});

			return final_str;

		}

		template <typename StringType>
		void to_lower_case_in_place(StringType& str, const std::locale loc = std::locale{})
		{
			for (auto& ch : str) ch = tolower(ch, loc);

		}

		template <typename StringType>
		StringType to_upper_case(const StringType& str, const std::locale loc = std::locale{})
		{
			using char_type = typename StringType::value_type;

			StringType final_str{ str };

			transform(begin(str), end(str), begin(final_str), [](const char_type ch)
			{
				return toupper(ch, loc);
			});

			return final_str;

		}

		template <typename StringType>
		void to_upper_case_in_place(StringType& str, const locale loc = locale{})
		{
			for (auto& ch : str) ch = toupper(ch, loc);

		}

		template <typename StringType>
		StringType to_title_case(const StringType& str, const locale loc = locale{})
		{

			using char_type = typename StringType::value_type;

			StringType final_str{ str };

			auto is_new_sentence{ true };

			for (auto& ch : final_str)
			{				
				if (static_cast<char_type>('\n') == ch) {
					is_new_sentence = true;
					continue;
				}

				if (is_new_sentence && !is_ws_char(ch)) // if (is_new_sentence && is_alphanum_char(ch)) { ... }
				{
					ch = toupper(ch, loc);
					is_new_sentence = false;					
				}			
			}


			return final_str;

		}


		template <typename StringType>
		void to_title_case_in_place(StringType& str, const locale loc = locale{})
		{
			using char_type = typename StringType::value_type;

			auto is_new_sentence{ true };

			for (auto& ch : str)
			{
				if (static_cast<char_type>('\n') == ch) {
					is_new_sentence = true;
					continue;
				}

				if (is_new_sentence && !is_ws_char(ch)) // if (is_new_sentence && is_alphanum_char(ch)) { ... }
				{
					ch = toupper(ch, loc);
					is_new_sentence = false;
				}
			}
		
		}

		
		template <typename StringType>
		bool is_ws_char(const typename StringType::value_type ch)
		{

			using char_type = typename StringType::value_type;			

			switch (ch)
			{

			case static_cast<char_type>(' ') :
			case static_cast<char_type>('\n') :
			case static_cast<char_type>('\r') :
			case static_cast<char_type>('\t') :
			case static_cast<char_type>('\v') :
			case static_cast<char_type>('\f') :
				return true;

			default:
				return false;
			
			}
		}



		// global conversion functions from the appropriate signed/unsigned integral as well as floating point types to std::u16string and std::u32string newer STL C++11 string types

		enum class number_base { decimal, hexadecimal, octal, binary };

		enum class add_number_base_sign
		{
			no_number_base_sign,
			prepend_in_lower_case_format,
			prepend_in_upper_case_format,
			append_in_lower_case_format,
			append_in_upper_case_format
		};

		u16string to_u16string(short number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(unsigned short number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(int number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(unsigned int number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(unsigned long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(long long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(unsigned long long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u16string to_u16string(float number, const int round_to_specified_number_of_digits = 6);
		u16string to_u16string(double number, const int round_to_specified_number_of_digits = 6);
		u16string to_u16string(long double number, const int round_to_specified_number_of_digits = 6);

		u32string to_u32string(short number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(unsigned short number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(int number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(unsigned int number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(unsigned long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(long long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(unsigned long long number, const number_base convert_to_number_base = number_base::decimal,
		                       const add_number_base_sign add_number_base_sign = add_number_base_sign::no_number_base_sign);
		u32string to_u32string(float number, const int round_to_specified_number_of_digits = 6);
		u32string to_u32string(double number, const int round_to_specified_number_of_digits = 6);
		u32string to_u32string(long double number, const int round_to_specified_number_of_digits = 6);

		int stoi(const u16string& str, size_t* pos = nullptr, int base = 10,
		         bool ignore_leading_white_space_characters = true);
		long stol(const u16string& str, size_t* pos = nullptr, int base = 10,
		          bool ignore_leading_white_space_characters = true);
		unsigned long stoul(const u16string& str, size_t* pos = nullptr, int base = 10,
		                    bool ignore_leading_white_space_characters = true);
		long long stoll(const u16string& str, size_t* pos = nullptr, int base = 10,
		                bool ignore_leading_white_space_characters = true);
		unsigned long long stoull(const u16string& str, size_t* pos = nullptr, int base = 10,
		                          bool ignore_leading_white_space_characters = true);
		float stof(const u16string& str, size_t* pos = nullptr, int base = 10,
		           bool ignore_leading_white_space_characters = true);
		double stod(const u16string& str, size_t* pos = nullptr, int base = 10,
		            bool ignore_leading_white_space_characters = true);
		long double stold(const u16string& str, size_t* pos = nullptr, int base = 10,
		                  bool ignore_leading_white_space_characters = true);

		int stoi(const u32string& str, size_t* pos = nullptr, int base = 10,
		         bool ignore_leading_white_space_characters = true);
		long stol(const u32string& str, size_t* pos = nullptr, int base = 10,
		          bool ignore_leading_white_space_characters = true);
		unsigned long stoul(const u32string& str, size_t* pos = nullptr, int base = 10,
		                    bool ignore_leading_white_space_characters = true);
		long long stoll(const u32string& str, size_t* pos = nullptr, int base = 10,
		                bool ignore_leading_white_space_characters = true);
		unsigned long long stoull(const u32string& str, size_t* pos = nullptr, int base = 10,
		                          bool ignore_leading_white_space_characters = true);
		float stof(const u32string& str, size_t* pos = nullptr, int base = 10,
		           bool ignore_leading_white_space_characters = true);
		double stod(const u32string& str, size_t* pos = nullptr, int base = 10,
		            bool ignore_leading_white_space_characters = true);
		long double stold(const u32string& str, size_t* pos = nullptr, int base = 10,
		                  bool ignore_leading_white_space_characters = true);

		template <typename StringType>
		StringType trim(const StringType& str)
		{
			using char_type = typename StringType::value_type;

			if (0u == str.length()) return StringType{};

			size_t begin{};
			size_t end{str.length() - 1};						

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
			using char_type = typename StringType::value_type;

			if (0u == str.length()) return StringType{};

			size_t begin{};
			size_t const end{str.length() - 1};

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
			using char_type = typename StringType::value_type;

			size_t begin{};
			size_t end{str.size() - 1};

			using char_type = typename StringType::value_type;

			if (0u == str.length()) return StringType{};

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

			if (StringType::npos == end) return StringType{};

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

			StringType needle_st(1, needle_char);

			const size_t source_len { source.length() };
			const size_t needle_len { needle_st.length() };

			if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len)) return parts;

			size_t number_of_parts{}, prev{};

			while (true)
			{
				const size_t current { source.find(needle_st, prev) };

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_len) break;
			}			

			if (prev < source_len)
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

			StringType needle_st{needle};

			const size_t source_len{source.length()};
			const size_t needle_len{needle_st.length()};

			if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len)) return parts;

			size_t number_of_parts{}, prev{};

			while (true)
			{
				const size_t current { source.find(needle_st, prev) };

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_len) break;
			}

			if (prev < source_len)
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

			const size_t source_len { source.length() };
			const size_t needle_len { needle.length() };

			if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len)) return parts;

			size_t number_of_parts{}, prev{};

			while (true)
			{
				const size_t current { source.find(needle, prev) };

				if (StringType::npos == current) break;

				number_of_parts++;

				if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_len) break;
			}

			if (prev < source_len)
			{
				if (StringType::npos == max_count) parts.emplace_back(source.substr(prev));

				else if ((StringType::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
			}

			return parts;
		}

		
	}
}

#endif /* _STL_HELPER_FUNCTIONS_H_ */
