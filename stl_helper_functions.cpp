#include "stl_helper_functions.hpp"

namespace std
{
	namespace helper
	{
		bool trim(char* str)
		{
			size_t begin = 0u;
			size_t end = strlen(str) - 1;

			if (strlen(str) == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = '\0';
				return true;
			}

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = '\0';

			return true;
		}

		bool trim(wchar_t* str)
		{
			size_t begin = 0u;
			size_t end = wcslen(str) - 1;

			if (wcslen(str) == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = L'\0';
				return true;
			}

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = L'\0';

			return true;
		}

		bool trim(char16_t* str)
		{
			std::u16string u16_str{str};

			size_t begin = 0u;
			size_t end = u16_str.size() - 1;

			if (u16_str.size() == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = u'\0';
				return true;
			}

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = u'\0';

			return true;
		}

		bool trim(char32_t* str)
		{
			std::u32string u32_str{str};

			size_t begin = 0u;
			size_t end = u32_str.size() - 1;

			if (u32_str.size() == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = U'\0';
				return true;
			}

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = U'\0';

			return true;
		}

		bool ltrim(char* str)
		{
			size_t begin = 0u;
			size_t end = strlen(str) - 1;

			if (strlen(str) == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = '\0';
				return true;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = '\0';

			return true;
		}

		bool ltrim(wchar_t* str)
		{
			size_t begin = 0u;
			size_t end = wcslen(str) - 1;

			if (wcslen(str) == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = L'\0';
				return true;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = L'\0';

			return true;
		}

		bool ltrim(char16_t* str)
		{
			std::u16string u16_str{str};

			size_t begin = 0u;
			size_t end = u16_str.size() - 1;

			if (u16_str.size() == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = u'\0';
				return true;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = u'\0';

			return true;
		}

		bool ltrim(char32_t* str)
		{
			std::u32string u32_str{str};

			size_t begin = 0u;
			size_t end = u32_str.size() - 1;

			if (u32_str.size() == 0) return false;

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (str[begin])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end)
			{
				*str = U'\0';
				return true;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = U'\0';

			return true;
		}

		bool rtrim(char* str)
		{
			const size_t begin = 0u;
			size_t end = strlen(str) - 1;

			if (strlen(str) == 0) return false;

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = '\0';

			return true;
		}

		bool rtrim(wchar_t* str)
		{
			const size_t begin = 0u;
			size_t end = wcslen(str) - 1;

			if (wcslen(str) == 0) return false;

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = L'\0';

			return true;
		}

		bool rtrim(char16_t* str)
		{
			std::u16string u16_str{str};

			size_t begin = 0u;
			size_t end = u16_str.size() - 1;

			if (u16_str.size() == 0) return false;

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = u'\0';

			return true;
		}

		bool rtrim(char32_t* str)
		{
			std::u32string u32_str{str};

			size_t begin = 0u;
			size_t end = u32_str.size() - 1;

			if (u32_str.size() == 0) return false;

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (str[end])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			size_t j{0u};
			const size_t last{end + 1};

			for (auto i = begin; i < last; i++)
			{
				str[j] = str[i];
				j++;
			}

			str[j] = U'\0';

			return true;
		}

		std::string trim(const char* str)
		{
			std::string source_str{str};

			size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::wstring trim(const wchar_t* str)
		{
			std::wstring source_str{str};

			size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::wstring{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::wstring{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::u16string trim(const char16_t* str)
		{
			std::u16string source_str{str};

			size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u16string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::u16string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::u32string trim(const char32_t* str)
		{
			std::u32string source_str{str};

			size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u32string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::u32string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::string ltrim(const char* str)
		{
			std::string source_str{str};

			size_t begin = 0u;
			const size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::string{};

			return source_str.substr(begin, end - begin + 1);
		}

		std::wstring ltrim(const wchar_t* str)
		{
			std::wstring source_str{str};

			size_t begin = 0u;
			const size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::wstring{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::wstring{};

			return source_str.substr(begin, end - begin + 1);
		}

		std::u16string ltrim(const char16_t* str)
		{
			std::u16string source_str{str};

			size_t begin = 0u;
			const size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u16string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::u16string{};

			return source_str.substr(begin, end - begin + 1);
		}

		std::u32string ltrim(const char32_t* str)
		{
			std::u32string source_str{str};

			size_t begin = 0u;
			const size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u32string{};

			for (auto is_ws_char{true}; begin <= end; ++begin)
			{
				switch (source_str[begin])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			if (begin > end) return std::u32string{};

			return source_str.substr(begin, end - begin + 1);
		}

		std::string rtrim(const char* str)
		{
			std::string source_str{str};

			const size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case ' ':
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::wstring rtrim(const wchar_t* str)
		{
			std::wstring source_str{str};

			const size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::wstring{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case L' ':
				case L'\t':
				case L'\n':
				case L'\r':
				case L'\f':
				case L'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::u16string rtrim(const char16_t* str)
		{
			std::u16string source_str{str};

			const size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u16string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case u' ':
				case u'\t':
				case u'\n':
				case u'\r':
				case u'\f':
				case u'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		std::u32string rtrim(const char32_t* str)
		{
			std::u32string source_str{str};

			const size_t begin = 0u;
			size_t end = source_str.size() - 1;

			if (source_str.size() == 0u) return std::u32string{};

			for (auto is_ws_char{true}; end > begin; --end)
			{
				switch (source_str[end])
				{
				case U' ':
				case U'\t':
				case U'\n':
				case U'\r':
				case U'\f':
				case U'\v':
					break;

				default:
					is_ws_char = false;
					break;
				}

				if (!is_ws_char) break;
			}

			return source_str.substr(begin, end - begin + 1);
		}

		size_t u16_strlen(const char16_t* str)
		{
			if (!str) return 0u;

			size_t length{0u};
			while (*str)
			{
				length++;
				str++;
			}

			return length;
		}

		size_t u32_strlen(const char32_t* str)
		{
			if (!str) return 0u;

			size_t length{0u};
			while (*str)
			{
				length++;
				str++;
			}

			return length;
		}

		int u16_strcmp(const char16_t* src1, const char16_t* src2)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			for (; *src1 && *src2; src1++ , src2++)
			{
				if (*src1 != *src2) return static_cast<int>(*src1 - *src2);
			}

			return static_cast<int>(*src1 - *src2);
		}

		int u32_strcmp(const char32_t* src1, const char32_t* src2)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			for (; *src1 && *src2; src1++ , src2++)
			{
				if (*src1 != *src2) return static_cast<int>(*src1 - *src2);
			}

			return static_cast<int>(*src1 - *src2);
		}

		int u16_strncmp(const char16_t* src1, const char16_t* src2, size_t number_of_characters_to_compare)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			auto const src1_len = u16_strlen(src1);
			auto const src2_len = u16_strlen(src2);

			if (src1_len < number_of_characters_to_compare || src2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(src1_len, src2_len);
			}

			for (size_t i = 0u; i < number_of_characters_to_compare; src1++ , src2++ , i++)
			{
				if (*src1 != *src2) return static_cast<int>(*src1 - *src2);
			}

			return 0;
		}

		int u32_strncmp(const char32_t* src1, const char32_t* src2, size_t number_of_characters_to_compare)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			auto const src1_len = u32_strlen(src1);
			auto const src2_len = u32_strlen(src2);

			if (src1_len < number_of_characters_to_compare || src2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(src1_len, src2_len);
			}

			for (size_t i = 0u; i < number_of_characters_to_compare; src1++ , src2++ , i++)
			{
				if (*src1 != *src2) return static_cast<int>(*src1 - *src2);
			}

			return 0;
		}

		int u16_stricmp(const char16_t* src1, const char16_t* src2, const std::locale& loc)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			for (; *src1 && *src2; src1++ , src2++)
			{
				auto const ch1 = std::tolower(*src1, loc);
				auto const ch2 = std::tolower(*src2, loc);
				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return static_cast<int>(std::tolower(*src1, loc) - std::tolower(*src2, loc));
		}

		int u32_stricmp(const char32_t* src1, const char32_t* src2, const std::locale& loc)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			for (; *src1 && *src2; src1++ , src2++)
			{
				auto const ch1 = std::tolower(*src1, loc);
				auto const ch2 = std::tolower(*src2, loc);
				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return static_cast<int>(std::tolower(*src1, loc) - std::tolower(*src2, loc));
		}

		int u16_strnicmp(const char16_t* src1, const char16_t* src2, size_t number_of_characters_to_compare,
		                 const std::locale& loc)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			auto const src1_len = u16_strlen(src1);
			auto const src2_len = u16_strlen(src2);

			if (src1_len < number_of_characters_to_compare || src2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(src1_len, src2_len);
			}

			for (size_t i = 0u; i < number_of_characters_to_compare; src1++ , src2++ , i++)
			{
				auto const ch1 = std::tolower(*src1, loc);
				auto const ch2 = std::tolower(*src2, loc);
				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return 0;
		}

		int u32_strnicmp(const char32_t* src1, const char32_t* src2, size_t number_of_characters_to_compare,
		                 const std::locale& loc)
		{
			if (!src1) return -1;
			if (!src2) return 1;

			auto const src1_len = u32_strlen(src1);
			auto const src2_len = u32_strlen(src2);

			if (src1_len < number_of_characters_to_compare || src2_len < number_of_characters_to_compare)
			{
				number_of_characters_to_compare = min(src1_len, src2_len);
			}

			for (size_t i = 0u; i < number_of_characters_to_compare; src1++ , src2++ , i++)
			{
				auto const ch1 = std::tolower(*src1, loc);
				auto const ch2 = std::tolower(*src2, loc);
				if (ch1 != ch2) return static_cast<int>(ch1 - ch2);
			}

			return 0;
		}

		char16_t* u16_strcpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			if (*src == u'\0')
			{
				*dst = *src;
				return dst;
			}

			auto const src_len = u16_strlen(src);

			if (src_len > (dst_capacity_in_number_of_characters - 1)) return dst;

			copy(src, src + src_len, dst);

			dst[src_len] = u'\0';

			return dst;
		}

		char32_t* u32_strcpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			if (*src == U'\0')
			{
				*dst = *src;
				return dst;
			}

			auto const src_len = u32_strlen(src);

			if (src_len > (dst_capacity_in_number_of_characters - 1)) return dst;

			copy(src, src + src_len, dst);

			dst[src_len] = U'\0';

			return dst;
		}

		char16_t* u16_strncpy(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src,
		                      const size_t number_of_characters_to_copy)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			if (*src == u'\0')
			{
				*dst = *src;
				return dst;
			}

			auto const src_len = u16_strlen(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			if (noctc > (dst_capacity_in_number_of_characters - 1)) return dst;

			copy(src, src + noctc, dst);

			dst[noctc] = u'\0';

			return dst;
		}

		char32_t* u32_strncpy(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src,
		                      const size_t number_of_characters_to_copy)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			if (*src == U'\0')
			{
				*dst = *src;
				return dst;
			}

			auto const src_len = u32_strlen(src);

			auto const noctc = min(number_of_characters_to_copy, src_len);

			if (noctc > (dst_capacity_in_number_of_characters - 1)) return dst;

			copy(src, src + noctc, dst);

			dst[noctc] = U'\0';

			return dst;
		}

		char16_t* u16_strcat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			auto const src_len = u16_strlen(src);

			auto const dst_len = u16_strlen(dst);

			if (src_len > (dst_capacity_in_number_of_characters - dst_len - 1)) return dst;

			while (*dst) dst++;

			if (*src == u'\0') return dst;

			copy(src, src + src_len, dst);

			dst[src_len] = u'\0';

			return dst;
		}

		char32_t* u32_strcat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

			auto const src_len = u32_strlen(src);

			auto const dst_len = u32_strlen(dst);

			if (src_len > (dst_capacity_in_number_of_characters - dst_len - 1)) return dst;

			while (*dst) dst++;

			if (*src == U'\0') return dst;

			copy(src, src + src_len, dst);

			dst[src_len] = U'\0';

			return dst;
		}

		char16_t* u16_strncat(char16_t* dst, const size_t dst_capacity_in_number_of_characters, const char16_t* src,
		                      const size_t number_of_characters_to_concatenate)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters || !number_of_characters_to_concatenate) return dst;

			auto const src_len = u16_strlen(src);

			auto const dst_len = u16_strlen(dst);

			auto const noctc = min(number_of_characters_to_concatenate, src_len);

			if (noctc > (dst_capacity_in_number_of_characters - dst_len - 1)) return dst;

			while (*dst) dst++;

			if (*src == u'\0') return dst;

			copy(src, src + noctc, dst);

			dst[noctc] = u'\0';

			return dst;
		}

		char32_t* u32_strncat(char32_t* dst, const size_t dst_capacity_in_number_of_characters, const char32_t* src,
		                      const size_t number_of_characters_to_concatenate)
		{
			if (!dst || !src || !dst_capacity_in_number_of_characters || !number_of_characters_to_concatenate) return dst;

			auto const src_len = u32_strlen(src);

			auto const dst_len = u32_strlen(dst);

			auto const noctc = min(number_of_characters_to_concatenate, src_len);

			if ((dst_capacity_in_number_of_characters - dst_len - 1) < noctc) return dst;

			while (*dst) dst++;

			if (*src == U'\0') return dst;

			copy(src, src + noctc, dst);

			dst[noctc] = U'\0';

			return dst;
		}

		const char16_t* u16_strstr(const char16_t* src, const char16_t* needle)
		{
			if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return nullptr;

			auto si = size_t{0u};

			auto const src_len = u16_strlen(src);
			auto const needle_len = u16_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (src[si] != needle[i])
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		const char32_t* u32_strstr(const char32_t* src, const char32_t* needle)
		{
			if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return nullptr;

			size_t si{0u};

			auto const src_len = u32_strlen(src);
			auto const needle_len = u32_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (src[si] != needle[i])
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		char16_t* u16_strstr(char16_t* src, const char16_t* needle)
		{
			if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return nullptr;

			size_t si{0u};

			auto const src_len = u16_strlen(src);
			auto const needle_len = u16_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (src[si] != needle[i])
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		char32_t* u32_strstr(char32_t* src, const char32_t* needle)
		{
			if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return nullptr;

			size_t si{0u};

			auto const src_len = u32_strlen(src);
			auto const needle_len = u32_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (src[si] != needle[i])
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		const char16_t* u16_strstri(const char16_t* src, const char16_t* needle, const std::locale& loc)
		{
			if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return nullptr;

			auto si = size_t{0u};

			auto const src_len = u16_strlen(src);
			auto const needle_len = u16_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (tolower(src[si], loc) != tolower(needle[i], loc))
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		const char32_t* u32_strstri(const char32_t* src, const char32_t* needle, const std::locale& loc)
		{
			if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return nullptr;

			auto si = size_t{0u};

			auto const src_len = u32_strlen(src);
			auto const needle_len = u32_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (tolower(src[si], loc) != tolower(needle[i], loc))
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		char16_t* u16_strstri(char16_t* src, const char16_t* needle, const std::locale& loc)
		{
			if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return nullptr;

			auto si = size_t{0u};

			auto const src_len = u16_strlen(src);
			auto const needle_len = u16_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (tolower(src[si], loc) != tolower(needle[i], loc))
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		char32_t* u32_strstri(char32_t* src, const char32_t* needle, const std::locale& loc)
		{
			if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return nullptr;

			auto si = size_t{0u};

			auto const src_len = u32_strlen(src);
			auto const needle_len = u32_strlen(needle);

			if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len)) return nullptr;

			bool match_found{false};

			while (!match_found)
			{
				if ((si + needle_len) > src_len) break;

				match_found = true;

				for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len)); i++ , mi++)
				{
					if (tolower(src[si], loc) != tolower(needle[i], loc))
					{
						match_found = false;
						si -= mi;
						break;
					}

					si++;
				}

				si++;
			}

			if (!match_found) return nullptr;

			return &src[si - needle_len - 1];
		}

		std::vector<std::string> split(const char* source, const char needle_char, int const max_count)
		{
			std::vector<std::string> parts{};

			size_t prev = 0, current;

			std::string source_st{source};

			const std::string needle_st(1, needle_char);

			if ((source_st.size() == 0) || (source_st.size() <= 1)) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + 1;

				if (prev >= source_st.size()) break;
			}
			while (std::string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::wstring> split(const wchar_t* source, const wchar_t needle_char, int const max_count)
		{
			std::vector<std::wstring> parts{};

			size_t prev = 0, current;

			std::wstring source_st{source};

			std::wstring needle_st(1, needle_char);

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (source_st.size() <= 1)) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::wstring::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + 1;

				if (prev >= source_st.size()) break;
			}
			while (std::wstring::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::u16string> split(const char16_t* source, const char16_t needle_char, int const max_count)
		{
			std::vector<std::u16string> parts{};

			size_t prev = 0, current;

			std::u16string source_st{source};

			std::u16string needle_st(1, needle_char);

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (source_st.size() <= 1)) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::u16string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + 1;

				if (prev >= source_st.size()) break;
			}
			while (std::u16string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::u32string> split(const char32_t* source, const char32_t needle_char, int const max_count)
		{
			std::vector<std::u32string> parts{};

			size_t prev = 0, current;

			std::u32string source_st{source};

			std::u32string needle_st(1, needle_char);

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (source_st.size() <= 1)) return parts;

			size_t number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::u32string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + 1;

				if (prev >= source_st.size()) break;
			}
			while (std::u32string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::string> split(const char* source, const char* needle, const int max_count)
		{
			std::vector<std::string> parts{};

			size_t prev = 0, current;

			std::string source_st{source};
			std::string needle_st{needle};

			auto const needle_len = needle_st.size();

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source_st.size())) return parts;

			int number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_st.size()) break;
			}
			while (std::string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::wstring> split(const wchar_t* source, const wchar_t* needle, const int max_count)
		{
			std::vector<std::wstring> parts{};

			size_t prev = 0, current;

			std::wstring source_st{source};
			std::wstring needle_st{needle};

			auto const needle_len = needle_st.size();

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source_st.size())) return parts;

			auto number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::wstring::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_st.size()) break;
			}
			while (std::wstring::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::u16string> split(const char16_t* source, const char16_t* needle, const int max_count)
		{
			std::vector<std::u16string> parts{};

			size_t prev = 0, current;

			std::u16string source_st{source};
			std::u16string needle_st{needle};

			auto const needle_len = needle_st.size();

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source_st.size())) return parts;

			auto number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::u16string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_st.size()) break;
			}
			while (std::u16string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}

		std::vector<std::u32string> split(const char32_t* source, const char32_t* needle, const int max_count)
		{
			std::vector<std::u32string> parts{};

			size_t prev = 0, current;

			std::u32string source_st{source};
			std::u32string needle_st{needle};

			auto const needle_len = needle_st.size();

			if ((source_st.size() == 0) || (needle_st.size() == 0) || (needle_st.size() >= source_st.size())) return parts;

			auto number_of_parts = 0;

			do
			{
				current = source_st.find(needle_st, prev);

				if (std::u32string::npos == current) break;

				number_of_parts++;

				if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count)) break;

				if ((current - prev) > 0) parts.emplace_back(source_st.substr(prev, current - prev));

				prev = current + needle_len;

				if (prev >= source_st.size()) break;
			}
			while (std::u32string::npos != current);

			if (number_of_parts > 0 && prev < source_st.size())
			{
				if (-1 == max_count) parts.emplace_back(source_st.substr(prev));

				else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
					parts.emplace_back(
						source_st.substr(prev));
			}

			return parts;
		}
	}
}