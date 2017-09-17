#ifndef _STL_HELPER_FUNCTIONS_H_
#define _STL_HELPER_FUNCTIONS_H_

#include <cwchar>
#include <locale>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <strsafe.h>

#define STL_HELPER_UTILITY_MAJOR_VERSION 1
#define STL_HELPER_UTILITY_MINOR_VERSION 0

namespace std {

	template <typename... Args>
	void say_slow(const wchar_t* szoveg, Args... args) {
		wchar_t buffer[8196];
		const size_t delay = 5;
		bool sleep_on = true;

		StringCchPrintfW(buffer, sizeof(buffer) / sizeof(buffer[0]), szoveg, args...);

		for (size_t i = 0; i < wcslen(buffer); ++i) {
			wprintf(L"%c", buffer[i]);
			if (sleep_on) this_thread::sleep_for(chrono::milliseconds(delay));
			if (_kbhit()) {
				_getch();
				sleep_on = false;
			}
		}

	}

	template <typename... Args>
	void say(const wchar_t* szoveg, Args... args) {
		
		static wchar_t buffer[8196];
		StringCchPrintfW(buffer, sizeof(buffer)/sizeof(buffer[0]), szoveg, args...);
		wprintf(L"%s", buffer);

	}

	template <typename StringType>
	StringType trim(const StringType& str) {

		size_t begin = 0u;
		size_t end = str.size() - 1;

		if (str.size() == 0u) return StringType{};

		for (auto is_ws_char{ true }; begin <= end; ++begin) {

			switch (static_cast<typename StringType::value_type>(str[begin])) {

			case static_cast<typename StringType::value_type>(' ') :
			case static_cast<typename StringType::value_type>('\t') :
			case static_cast<typename StringType::value_type>('\n') :
			case static_cast<typename StringType::value_type>('\r') :
			case static_cast<typename StringType::value_type>('\f') :
			case static_cast<typename StringType::value_type>('\v') :			
				break;

			default:
				is_ws_char = false;
				break;

			}

			if (!is_ws_char) break;
		}

		if (begin > end) return StringType{};

		for (auto is_ws_char{true}; end > begin; --end) {

			switch (static_cast<typename StringType::value_type>(str[end])) {

			case static_cast<typename StringType::value_type>(' ') :
			case static_cast<typename StringType::value_type>('\t') :
			case static_cast<typename StringType::value_type>('\n') :
			case static_cast<typename StringType::value_type>('\r') :
			case static_cast<typename StringType::value_type>('\f') :
			case static_cast<typename StringType::value_type>('\v') :
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
	StringType ltrim(const StringType& str) {

		size_t begin = 0u;
		size_t const end = str.size() - 1;

		if (str.size() == 0u) return StringType{};

		for (auto is_ws_char{ true }; (is_ws_char && (begin <= end)); ++begin) {

			switch (static_cast<typename StringType::value_type>(str[begin])) {

			case static_cast<typename StringType::value_type>(' ') :
			case static_cast<typename StringType::value_type>('\t') :
			case static_cast<typename StringType::value_type>('\n') :
			case static_cast<typename StringType::value_type>('\r') :
			case static_cast<typename StringType::value_type>('\f') :
			case static_cast<typename StringType::value_type>('\v') :			
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
	StringType rtrim(const StringType& str) {

		size_t begin = 0u;
		size_t end = str.size() - 1;

		if (str.size() == 0u) return StringType{};
		
		for (auto is_ws_char{true}; (is_ws_char && (end != StringType::npos)); --end) {

			switch (static_cast<typename StringType::value_type>(str[end])) {

			case static_cast<typename StringType::value_type>(' ') :
			case static_cast<typename StringType::value_type>('\t') :
			case static_cast<typename StringType::value_type>('\n') :
			case static_cast<typename StringType::value_type>('\r') :
			case static_cast<typename StringType::value_type>('\f') :
			case static_cast<typename StringType::value_type>('\v') :
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

	template <typename StringType>
	vector<StringType> split(const StringType& source, const StringType& needle, size_t const max_count = StringType::npos) {

		vector<StringType> parts{};

		size_t prev = 0, current;

		const size_t needle_len = needle.size();

		if ((source.size() == 0) || (needle.size() == 0) || (needle.size() >= source.size())) return parts;

		size_t number_of_parts = 0;

		do {

			current = source.find(needle, prev);

			if (StringType::npos == current) break;

			number_of_parts++;

			if ((StringType::npos != max_count) && (parts.size() == max_count)) break;

			if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

			prev = current + needle_len; // source = "apple|pear|plum|cherry|orange", needle = "|"

			if (prev >= source.size()) break;


		} while (StringType::npos != current);

		if (number_of_parts > 0 && prev < source.size()) {

			if (StringType::npos == max_count) parts.emplace_back(source.substr(prev));

			else if ((StringType::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));

		}

		return parts;

	}
	
	template <typename StringType>
	bool starts_with(const StringType& src, const typename StringType::value_type start_char, bool ignore_case = false) {
		
		if (src.size() == 0) return false;

		locale loc{};

		if (!ignore_case) {
			
			return(src[0] == start_char);
		
		}			
		
		return(tolower(src[0], loc) == tolower(start_char, loc));
		
	}

	template <typename StringType>
	bool starts_with(const StringType& src, const StringType& start_tag, bool ignore_case = false) {

		if ((src.size() == 0) || (start_tag.size() == 0) || (start_tag.size() > src.size())) return false;

		bool found;

		if (!ignore_case) {			

			if (src.find(start_tag) == 0) found = true;

			else found = false;
		
		} else {
			
			StringType src_lc{ src };

			StringType start_tag_lc{ start_tag };

			locale loc{};

			transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::valuetype>(tolower(ch, loc));
			});

			transform(begin(start_tag), end(start_tag), begin(start_tag_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::valuetype>(tolower(ch, loc));
			});

			if (src_lc.find(start_tag_lc) == 0) found = true;

			else found = false;

		}

		return found;
	}

	template <typename StringType>
	typename StringType::size_type index_of(const StringType& text, const StringType& needle, bool ignore_case = false)
	{
		if ((text.size() == 0) || (needle.size() == 0) || (needle.size() > text.size())) return StringType::npos;

		if (!ignore_case)
		{

			return text.find(needle);

		}

		locale loc{};

		StringType text_lc{ text };		

		transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		{
			return static_cast<typename StringType::value_type>(ch);
		});

		StringType needle_lc{ needle };

		transform(begin(needle), end(needle), begin(needle_lc), [&loc](const auto ch)
		{
			return static_cast<typename StringType::value_type>(ch);
		});

		return text_lc.find(needle_lc);

	}

	template <typename StringType>
	bool contains(const StringType& text, const StringType& needle, bool ignore_case = false)
	{
		if ((text.size() == 0) || (needle.size() == 0) || (needle.size() > text.size())) return false;

		if (!ignore_case)
		{
			
			if (text.find(needle) != StringType::npos) return true;

			return false;

		}

		locale loc{};

		StringType text_lc{ text };
		
		transform(begin(text), end(text), begin(text_lc), [&loc](const auto ch)
		{
			return static_cast<typename StringType::value_type>(ch);
		});

		StringType needle_lc{ needle };

		transform(begin(needle), end(needle), begin(needle_lc), [&loc](const auto ch)
		{
			return static_cast<typename StringType::value_type>(ch);
		});

		if (text_lc.find(needle_lc) != StringType::npos) return true;

		return false;

	}	

	template <typename StringType>
	bool ends_with(const StringType& text, const typename StringType::value_type end_char, bool ignore_case = false) {
		
		if (text.size() == 0) return false;

		if (!ignore_case) {

			return (text.back() == end_char);
		
		} 			
			
			return (_tolower(text.back()) == _tolower(end_char));		
	}

	template <typename StringType>
	bool ends_with(const StringType& src, const StringType& end_tag, bool ignore_case = false) {

		if ((src.size() == 0) || (end_tag.size() == 0) || (end_tag.size() > src.size())) return false;

		bool found;

		auto const expected_start_pos_of_end_tag = src.size() - end_tag.size();

		if (!ignore_case) {

			if (src.find(end_tag) == expected_start_pos_of_end_tag) found = true;

			else found = false;

		} else {

			StringType src_lc{ src };

			StringType end_tag_lc{ end_tag };

			locale loc{};

			transform(begin(src), end(src), begin(src_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::valuetype>(tolower(ch, loc));
			});

			transform(begin(end_tag), end(end_tag), begin(end_tag_lc), [&loc](const auto ch)
			{
				return static_cast<typename StringType::valuetype>(tolower(ch, loc));
			});

			if (src_lc.find(end_tag_lc) == 0) found = true;

			else found = false;

		}

		return found;
	}

	template <typename ...Args>
	void unused_args(Args&&...) {}

	template <typename T>
	bool has_value(const T& container, const typename T::value_type& item) {

		return (find(container.cbegin(), container.cend(), item) != container.cend());

	}

	template <typename T>
	bool has_value(T& container, const typename T::value_type& item) {

		return (find(container.begin(), container.end(), item) != container.end());

	}

	template <typename T>
	bool has_key(const T& container, const typename T::key_type& key) {

		return (container.find(key) != container.cend());

	}

	template <typename T>
	bool has_key(T& container, const typename T::key_type& key) {

		return (container.find(key) != container.end());

	}

}

#endif /* _STL_HELPER_FUNCTIONS_H_ */
