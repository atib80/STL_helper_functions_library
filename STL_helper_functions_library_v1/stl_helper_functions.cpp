#include "stl_helper_functions.hpp"

using namespace std;

namespace cpp {
namespace experimental {

/*size_t str_length(char* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(wchar_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(char16_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(char32_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                length++;
                str++;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(const char* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(const wchar_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(const char16_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                ++length;
                ++str;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

size_t str_length(const char32_t* str, const size_t max_allowed_string_length)
{
        if (!str) return 0u;

        if (!(*str)) return 0u;

        size_t length{0u};

        while (*str)
        {
                length++;
                str++;

                if (max_allowed_string_length == length) return
max_allowed_string_length;
        }

        return length;
}

bool trim(char* str)
{
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto original_end{str_len - 1};

        auto end{original_end};

        if (0u == str_len) return false;

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

        if (0u == begin) {

                if (original_end == end) return false;

                str[end + 1] = '\0';

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

bool trim(wchar_t* str)
{
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto original_end{str_len - 1};

        auto end{original_end};

        if (0u == str_len) return false;

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

        if (0u == begin) {

                if (original_end == end) return false;

                str[end + 1] = L'\0';

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

bool trim(char16_t* str)
{
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto original_end{str_len - 1};

        auto end{original_end};

        if (0u == str_len) return false;

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

        if (0u == begin) {

                if (original_end == end) return false;

                str[end + 1] = u'\0';

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

bool trim(char32_t* str)
{
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto original_end{str_len - 1};

        auto end{original_end};

        if (0u == str_len) return false;

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

        if (0u == begin) {

                if (original_end == end) return false;

                str[end + 1] = U'\0';

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

bool ltrim(char* str)
{
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto end{str_len - 1};

        if (0u == str_len) return false;

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

        if (0u == begin) return false;

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
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto end{str_len - 1};

        if (0u == str_len) return false;

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

        if (0u == begin) return false;

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
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto end{str_len - 1};

        if (0u == str_len) return false;

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

        if (0u == begin) return false;

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
        auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        const auto end{str_len - 1};

        if (0u == str_len) return false;

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

        if (0u == begin) return false;

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
        const auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        auto end{str_len - 1};

        const auto original_end{end};

        if (0u == str_len) return false;

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

        if (original_end == end) return false;

        str[end + 1] = '\0';

        return true;
}

bool rtrim(wchar_t* str)
{
        const auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        auto end{str_len - 1};

        const auto original_end{end};

        if (0u == str_len) return false;

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

        if (original_end == end) return false;

        str[end + 1] = L'\0';

        return true;
}

bool rtrim(char16_t* str)
{
        const auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        auto end{str_len - 1};

        const auto original_end{end};

        if (0u == str_len) return false;

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

        if (original_end == end) return false;

        str[end + 1] = u'\0';

        return true;
}

bool rtrim(char32_t* str)
{
        const auto begin = size_t{0u};

        const auto str_len{str_length(str)};

        auto end{str_len - 1};

        const auto original_end{end};

        if (0u == str_len) return false;

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

        if (original_end == end) return false;

        str[end + 1] = U'\0';

        return true;
}

bool str_starts_with(const char* src,
                     const char start_char,
                     bool ignore_case,
                     const locale& loc) {
  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    return (start_char == src[0]);
  }

  return (tolower(src[0], loc) == tolower(start_char, loc));
}

bool str_starts_with(const wchar_t* src,
                     const wchar_t start_char,
                     bool ignore_case,
                     const locale& loc) {
  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    return (start_char == src[0]);
  }

  return (tolower(src[0], loc) == tolower(start_char, loc));
}

bool str_starts_with(const char16_t* src,
                     const char16_t start_char,
                     bool ignore_case,
                     const locale& loc) {
  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    return (start_char == src[0]);
  }

  return (tolower(src[0], loc) == tolower(start_char, loc));
}

bool str_starts_with(const char32_t* src,
                     const char32_t start_char,
                     bool ignore_case,
                     const locale& loc) {
  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    return (start_char == src[0]);
  }

  return (tolower(src[0], loc) == tolower(start_char, loc));
}

bool str_starts_with(const char* src,
                     const char* start_tag,
                     bool ignore_case,
                     const locale& loc) {
  const string src_str{src};
  const string start_tag_str{start_tag};

  const auto src_len{src_str.size()};
  const auto start_tag_len{start_tag_str.size()};

  if ((0u == src_len) || (0u == start_tag_len) || (start_tag_len > src_len))
    return false;

  if (!ignore_case) {
    if (0u == src_str.find(start_tag_str))
      return true;

    return false;
  }

  string src_lc_str{src};

  auto start_tag_lc{start_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char ch) { return tolower(ch, loc); });

  transform(cbegin(start_tag_str), cend(start_tag_str), begin(start_tag_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  if (0u == src_lc_str.find(start_tag_lc))
    return true;

  return false;
}

bool str_starts_with(const wchar_t* src,
                     const wchar_t* start_tag,
                     bool ignore_case,
                     const locale& loc) {
  const wstring src_str{src};
  const wstring start_tag_str{start_tag};

  const auto src_len{src_str.size()};
  const auto start_tag_len{start_tag_str.size()};

  if ((0u == src_len) || (0u == start_tag_len) || (start_tag_len > src_len))
    return false;

  if (!ignore_case) {
    if (0u == src_str.find(start_tag_str))
      return true;

    return false;
  }

  wstring src_lc_str{src};

  auto start_tag_lc{start_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  transform(cbegin(start_tag_str), cend(start_tag_str), begin(start_tag_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  if (0u == src_lc_str.find(start_tag_lc))
    return true;

  return false;
}

bool str_starts_with(const char16_t* src,
                     const char16_t* start_tag,
                     bool ignore_case,
                     const locale& loc) {
  const u16string src_str{src};
  const u16string start_tag_str{start_tag};

  const auto src_len{src_str.size()};
  const auto start_tag_len{start_tag_str.size()};

  if ((0u == src_len) || (0u == start_tag_len) || (start_tag_len > src_len))
    return false;

  if (!ignore_case) {
    if (0u == src_str.find(start_tag_str))
      return true;

    return false;
  }

  u16string src_lc_str{src};

  auto start_tag_lc{start_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  transform(cbegin(start_tag_str), cend(start_tag_str), begin(start_tag_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  if (0u == src_lc_str.find(start_tag_lc))
    return true;

  return false;
}

bool str_starts_with(const char32_t* src,
                     const char32_t* start_tag,
                     bool ignore_case,
                     const locale& loc) {
  const u32string src_str{src};
  const u32string start_tag_str{start_tag};

  const auto src_len{src_str.size()};
  const auto start_tag_len{start_tag_str.size()};

  if ((0u == src_len) || (0u == start_tag_len) || (start_tag_len > src_len))
    return false;

  if (!ignore_case) {
    if (0u == src_str.find(start_tag_str))
      return true;

    return false;
  }

  u32string src_lc_str{src};

  auto start_tag_lc{start_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  transform(cbegin(start_tag_str), cend(start_tag_str), begin(start_tag_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  if (0u == src_lc_str.find(start_tag_lc))
    return true;

  return false;
}

size_t str_index_of(const char* src,
                    const char needle_char,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  const string src_str{src};

  if (0u == src_str.length())
    return string::npos;

  if (!ignore_case) {
    return src_str.find(needle_char, start_pos);
  }

  string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  return text_lc.find(tolower(needle_char, loc), start_pos);
}

size_t str_index_of(const wchar_t* src,
                    const wchar_t needle_char,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  const wstring src_str{src};

  if (0u == src_str.length())
    return wstring::npos;

  if (!ignore_case) {
    return src_str.find(needle_char, start_pos);
  }

  wstring text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  return text_lc.find(tolower(needle_char, loc), start_pos);
}

size_t str_index_of(const char16_t* src,
                    const char16_t needle_char,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  const u16string src_str{src};

  if (0u == src_str.length())
    return u16string::npos;

  if (!ignore_case) {
    return src_str.find(needle_char, start_pos);
  }

  u16string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  return text_lc.find(tolower(needle_char, loc), start_pos);
}

size_t str_index_of(const char32_t* src,
                    const char32_t needle_char,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  const u32string src_str{src};

  if (0u == src_str.length())
    return u32string::npos;

  if (!ignore_case) {
    return src_str.find(needle_char, start_pos);
  }

  u32string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  return text_lc.find(tolower(needle_char, loc), start_pos);
}
*/

size_t str_index_of(const char* src,
                    const char* needle,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  const string text_str{src};
  const string needle_str{needle};

  const auto text_len{text_str.length()};
  const auto needle_len{needle_str.length()};

  if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len))
    return string::npos;

  if (!ignore_case) {
    return text_str.find(needle_str, start_pos);
  }

  auto text_lc{text_str};

  transform(cbegin(text_str), cend(text_str), begin(text_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  auto needle_lc{needle_str};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  return text_lc.find(needle_lc, start_pos);
}

size_t str_index_of(const wchar_t* src,
                    const wchar_t* needle,
                    const size_t start_pos,
                    bool ignore_case,
                    const std::locale& loc) {
  const wstring text_str{src};
  const wstring needle_str{needle};

  const auto text_len{text_str.length()};
  const auto needle_len{needle_str.length()};

  if ((0u == text_len) || (0u == needle_len) || (needle_len > text_len))
    return wstring::npos;

  if (!ignore_case) {
    return text_str.find(needle_str, start_pos);
  }

  auto text_lc{text_str};

  transform(cbegin(text_str), cend(text_str), begin(text_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  auto needle_lc{needle_str};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  return text_lc.find(needle_lc, start_pos);
}

size_t str_index_of(const char16_t* src,
                    const char16_t* needle,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  u16string text_str{src};
  u16string needle_str{needle};

  const auto text_len{text_str.size()};
  const auto needle_len{needle_str.size()};

  if ((text_len == 0) || (needle_len == 0) || (needle_len > text_len))
    return u16string::npos;

  if (!ignore_case) {
    return text_str.find(needle_str, start_pos);
  }

  u16string text_lc{text_str};

  transform(begin(text_str), end(text_str), begin(text_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  u16string needle_lc{needle_str};

  transform(begin(needle_str), end(needle_str), begin(needle_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  return text_lc.find(needle_lc, start_pos);
}

size_t str_index_of(const char32_t* src,
                    const char32_t* needle,
                    const size_t start_pos,
                    bool ignore_case,
                    const locale& loc) {
  u32string text_str{src};
  u32string needle_str{needle};

  const auto text_len{text_str.size()};
  const auto needle_len{needle_str.size()};

  if ((text_len == 0) || (needle_len == 0) || (needle_len > text_len))
    return u32string::npos;

  if (!ignore_case) {
    return text_str.find(needle_str, start_pos);
  }

  u32string text_lc{text_str};

  transform(begin(text_str), end(text_str), begin(text_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  u32string needle_lc{needle_str};

  transform(begin(needle_str), end(needle_str), begin(needle_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  return text_lc.find(needle_lc, start_pos);
}

bool str_contains(const char* src,
                  const char needle_char,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const string src_str{src};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (string::npos != src_str.find(needle_char, start_pos))
      return true;

    return false;
  }

  string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  if (string::npos != text_lc.find(tolower(needle_char, loc), start_pos))
    return true;

  return false;
}

bool str_contains(const wchar_t* src,
                  const wchar_t needle_char,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const wstring src_str{src};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (wstring::npos != src_str.find(needle_char, start_pos))
      return true;

    return false;
  }

  wstring text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  if (wstring::npos != text_lc.find(tolower(needle_char, loc), start_pos))
    return true;

  return false;
}

bool str_contains(const char16_t* src,
                  const char16_t needle_char,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const u16string src_str{src};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (u16string::npos != src_str.find(needle_char, start_pos))
      return true;

    return false;
  }

  u16string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  if (u16string::npos != text_lc.find(tolower(needle_char, loc), start_pos))
    return true;

  return false;
}

bool str_contains(const char32_t* src,
                  const char32_t needle_char,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const u32string src_str{src};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (u32string::npos != src_str.find(needle_char, start_pos))
      return true;

    return false;
  }

  u32string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  if (u32string::npos != text_lc.find(tolower(needle_char, loc), start_pos))
    return true;

  return false;
}

bool str_contains(const char* src,
                  const char* needle,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const string src_str{src};
  const string needle_str{needle};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (string::npos != src_str.find(needle_str, start_pos))
      return true;

    return false;
  }

  string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char ch) { return tolower(ch, loc); });

  string needle_lc_str{needle};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc_str),
            [&loc](const char ch) { return tolower(ch, loc); });

  if (string::npos == text_lc.find(needle_lc_str, start_pos))
    return true;

  return false;
}

bool str_contains(const wchar_t* src,
                  const wchar_t* needle,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const wstring src_str{src};
  const wstring needle_str{needle};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (wstring::npos != src_str.find(needle_str, start_pos))
      return true;

    return false;
  }

  wstring text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  wstring needle_lc_str{needle};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc_str),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  if (wstring::npos == text_lc.find(tolower(needle_lc_str, loc), start_pos))
    return true;

  return false;
}

bool str_contains(const char16_t* src,
                  const char16_t* needle,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const u16string src_str{src};
  const u16string needle_str{needle};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (u16string::npos != src_str.find(needle_str, start_pos))
      return true;

    return false;
  }

  u16string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  u16string needle_lc_str{needle};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc_str),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  if (u16string::npos == text_lc.find(needle_lc_str, start_pos))
    return true;

  return false;
}

bool str_contains(const char32_t* src,
                  const char32_t* needle,
                  const size_t start_pos,
                  bool ignore_case,
                  const locale& loc) {
  const u32string src_str{src};
  const u32string needle_str{needle};

  if (0u == str_length(src))
    return false;

  if (!ignore_case) {
    if (u32string::npos != src_str.find(needle_str, start_pos))
      return true;

    return false;
  }

  u32string text_lc{src};

  transform(cbegin(src_str), cend(src_str), begin(text_lc),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  u32string needle_lc_str{needle};

  transform(cbegin(needle_str), cend(needle_str), begin(needle_lc_str),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  if (u32string::npos == text_lc.find(needle_lc_str, start_pos))
    return true;

  return false;
}

// str_ends_with global string handling functions (immutable)

bool str_ends_with(const char* src,
                   const char end_char,
                   bool ignore_case,
                   const locale& loc) {
  const auto src_len{str_length(src)};

  if (0u == src_len)
    return false;

  if (!ignore_case) {
    return (end_char == src[src_len - 1]);
  }

  return (tolower(end_char, loc) == tolower(src[src_len - 1], loc));
}

bool str_ends_with(const wchar_t* src,
                   const wchar_t end_char,
                   bool ignore_case,
                   const locale& loc) {
  const auto src_len{str_length(src)};

  if (0u == src_len)
    return false;

  if (!ignore_case) {
    return (end_char == src[src_len - 1]);
  }

  return (tolower(end_char, loc) == tolower(src[src_len - 1], loc));
}

bool str_ends_with(const char16_t* src,
                   const char16_t end_char,
                   bool ignore_case,
                   const locale& loc) {
  const auto src_len{str_length(src)};

  if (0u == src_len)
    return false;

  if (!ignore_case) {
    return (end_char == src[src_len - 1]);
  }

  return (tolower(end_char, loc) == tolower(src[src_len - 1], loc));
}

bool str_ends_with(const char32_t* src,
                   const char32_t end_char,
                   bool ignore_case,
                   const locale& loc) {
  const auto src_len{str_length(src)};

  if (0u == src_len)
    return false;

  if (!ignore_case) {
    return (end_char == src[src_len - 1]);
  }

  return (tolower(end_char, loc) == tolower(src[src_len - 1], loc));
}

bool str_ends_with(const char* src,
                   const char* end_tag,
                   bool ignore_case,
                   const locale& loc) {
  const string src_str{src};
  const string end_tag_str{end_tag};
  const auto src_len{src_str.length()};
  const auto end_tag_len{end_tag_str.length()};

  if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len))
    return false;

  auto expected_start_pos_of_end_tag = src_len - end_tag_len;

  if (!ignore_case) {
    if (src_str.find(end_tag) == expected_start_pos_of_end_tag)
      return true;

    return false;
  }

  auto src_lc_str{src_str};

  auto end_tag_lc_str{end_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char ch) { return tolower(ch, loc); });

  transform(cbegin(end_tag_str), cend(end_tag_str), begin(end_tag_lc_str),
            [&loc](const char ch) { return tolower(ch, loc); });

  expected_start_pos_of_end_tag = src_lc_str.size() - end_tag_lc_str.size();

  if (src_lc_str.find(end_tag_lc_str) == expected_start_pos_of_end_tag)
    return true;

  return false;
}

bool str_ends_with(const wchar_t* src,
                   const wchar_t* end_tag,
                   bool ignore_case,
                   const locale& loc) {
  const wstring src_str{src};
  const wstring end_tag_str{end_tag};
  const auto src_len{src_str.length()};
  const auto end_tag_len{end_tag_str.length()};

  if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len))
    return false;

  auto expected_start_pos_of_end_tag = src_len - end_tag_len;

  if (!ignore_case) {
    if (src_str.find(end_tag) == expected_start_pos_of_end_tag)
      return true;

    return false;
  }

  auto src_lc_str{src_str};

  auto end_tag_lc_str{end_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  transform(cbegin(end_tag_str), cend(end_tag_str), begin(end_tag_lc_str),
            [&loc](const wchar_t ch) { return tolower(ch, loc); });

  expected_start_pos_of_end_tag = src_lc_str.size() - end_tag_lc_str.size();

  if (src_lc_str.find(end_tag_lc_str) == expected_start_pos_of_end_tag)
    return true;

  return false;
}

bool str_ends_with(const char16_t* src,
                   const char16_t* end_tag,
                   bool ignore_case,
                   const locale& loc) {
  const u16string src_str{src};
  const u16string end_tag_str{end_tag};
  const auto src_len{src_str.length()};
  const auto end_tag_len{end_tag_str.length()};

  if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len))
    return false;

  auto expected_start_pos_of_end_tag = src_len - end_tag_len;

  if (!ignore_case) {
    if (src_str.find(end_tag) == expected_start_pos_of_end_tag)
      return true;

    return false;
  }

  auto src_lc_str{src_str};

  auto end_tag_lc_str{end_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  transform(cbegin(end_tag_str), cend(end_tag_str), begin(end_tag_lc_str),
            [&loc](const char16_t ch) { return tolower(ch, loc); });

  expected_start_pos_of_end_tag = src_lc_str.size() - end_tag_lc_str.size();

  if (src_lc_str.find(end_tag_lc_str) == expected_start_pos_of_end_tag)
    return true;

  return false;
}

bool str_ends_with(const char32_t* src,
                   const char32_t* end_tag,
                   bool ignore_case,
                   const locale& loc) {
  const u32string src_str{src};
  const u32string end_tag_str{end_tag};
  const auto src_len{src_str.length()};
  const auto end_tag_len{end_tag_str.length()};

  if ((0u == src_len) || (0u == end_tag_len) || (end_tag_len > src_len))
    return false;

  auto expected_start_pos_of_end_tag = src_len - end_tag_len;

  if (!ignore_case) {
    if (src_str.find(end_tag) == expected_start_pos_of_end_tag)
      return true;

    return false;
  }

  auto src_lc_str{src_str};

  auto end_tag_lc_str{end_tag_str};

  transform(cbegin(src_str), cend(src_str), begin(src_lc_str),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  transform(cbegin(end_tag_str), cend(end_tag_str), begin(end_tag_lc_str),
            [&loc](const char32_t ch) { return tolower(ch, loc); });

  expected_start_pos_of_end_tag = src_lc_str.size() - end_tag_lc_str.size();

  if (src_lc_str.find(end_tag_lc_str) == expected_start_pos_of_end_tag)
    return true;

  return false;
}

int str_compare(const char* str1, const char* str2) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return static_cast<int>(*str1 - *str2);
}

int str_compare(const wchar_t* str1, const wchar_t* str2) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return static_cast<int>(*str1 - *str2);
}

int str_compare(const char16_t* str1, const char16_t* str2) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return static_cast<int>(*str1 - *str2);
}

int str_compare(const char32_t* str1, const char32_t* str2) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return static_cast<int>(*str1 - *str2);
}

int str_compare_n(const char* str1,
                  const char* str2,
                  size_t number_of_characters_to_compare) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return 0;
}

int str_compare_n(const wchar_t* str1,
                  const wchar_t* str2,
                  size_t number_of_characters_to_compare) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return 0;
}

int str_compare_n(const char16_t* str1,
                  const char16_t* str2,
                  size_t number_of_characters_to_compare) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return 0;
}

int str_compare_n(const char32_t* str1,
                  const char32_t* str2,
                  size_t number_of_characters_to_compare) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len{str_length(str1)};
  auto const str2_len{str_length(str2)};

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    if (*str1 != *str2)
      return static_cast<int>(*str1 - *str2);
  }

  return 0;
}

int str_compare_i(const char* str1, const char* str2, const locale& loc) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);

    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return static_cast<int>(tolower(*str1, loc) - tolower(*str2, loc));
}

int str_compare_i(const wchar_t* str1, const wchar_t* str2, const locale& loc) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);

    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return static_cast<int>(tolower(*str1, loc) - tolower(*str2, loc));
}

int str_compare_i(const char16_t* str1,
                  const char16_t* str2,
                  const locale& loc) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);

    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return static_cast<int>(tolower(*str1, loc) - tolower(*str2, loc));
}

int str_compare_i(const char32_t* str1,
                  const char32_t* str2,
                  const locale& loc) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  auto const number_of_characters_to_compare = min(str1_len, str2_len);

  for (auto len = size_t{0u}; len < number_of_characters_to_compare;
       len++, str1++, str2++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);

    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return static_cast<int>(tolower(*str1, loc) - tolower(*str2, loc));
}

int str_compare_n_i(const char* str1,
                    const char* str2,
                    size_t number_of_characters_to_compare,
                    const locale& loc) {
  if (!str1)
    return -1;
  if (!str2)
    return 1;

  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);
    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return 0;
}

int str_compare_n_i(const wchar_t* str1,
                    const wchar_t* str2,
                    size_t number_of_characters_to_compare,
                    const locale& loc) {
  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);
    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return 0;
}

int str_compare_n_i(const char16_t* str1,
                    const char16_t* str2,
                    size_t number_of_characters_to_compare,
                    const locale& loc) {
  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);
    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return 0;
}

int str_compare_n_i(const char32_t* str1,
                    const char32_t* str2,
                    size_t number_of_characters_to_compare,
                    const locale& loc) {
  auto const str1_len = str_length(str1);
  auto const str2_len = str_length(str2);

  if (str1_len < number_of_characters_to_compare ||
      str2_len < number_of_characters_to_compare) {
    number_of_characters_to_compare = min(str1_len, str2_len);
  }

  for (auto i = size_t{0u}; i < number_of_characters_to_compare;
       str1++, str2++, i++) {
    auto const ch1 = tolower(*str1, loc);
    auto const ch2 = tolower(*str2, loc);
    if (ch1 != ch2)
      return static_cast<int>(ch1 - ch2);
  }

  return 0;
}

size_t str_copy(char* dst,
                const size_t dst_capacity_in_number_of_characters,
                const char* src,
                const str_copy_behavior copy_options,
                size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < (src_len + 1)) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_of_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_of_chars_to_copy, dst);

      dst[no_of_chars_to_copy] = '\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst);

  dst[src_len] = '\0';

  return src_len;
}

size_t str_copy(wchar_t* dst,
                const size_t dst_capacity_in_number_of_characters,
                const wchar_t* src,
                const str_copy_behavior copy_options,
                size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < (src_len + 1)) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_of_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_of_chars_to_copy, dst);

      dst[no_of_chars_to_copy] = L'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst);

  dst[src_len] = L'\0';

  return src_len;
}

size_t str_copy(char16_t* dst,
                const size_t dst_capacity_in_number_of_characters,
                const char16_t* src,
                const str_copy_behavior copy_options,
                size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < (src_len + 1)) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_of_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_of_chars_to_copy, dst);

      dst[no_of_chars_to_copy] = u'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst);

  dst[src_len] = u'\0';

  return src_len;
}

size_t str_copy(char32_t* dst,
                const size_t dst_capacity_in_number_of_characters,
                const char32_t* src,
                const str_copy_behavior copy_options,
                size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  const auto ret_val{src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < (src_len + 1)) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_of_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_of_chars_to_copy, dst);

      dst[no_of_chars_to_copy] = U'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst);

  dst[src_len] = U'\0';

  return src_len;
}

size_t str_copy_n(char* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  auto const noctc = min(number_of_characters_to_copy, src_len);

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = '\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = '\0';

  return noctc;
}

size_t str_copy_n(wchar_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const wchar_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  auto const noctc = min(number_of_characters_to_copy, src_len);

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = L'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = L'\0';

  return noctc;
}

size_t str_copy_n(char16_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char16_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  auto const noctc = min(number_of_characters_to_copy, src_len);

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = u'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = u'\0';

  return noctc;
}

size_t str_copy_n(char32_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char32_t* src,
                  const size_t number_of_characters_to_copy,
                  const str_copy_behavior copy_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);

  auto const noctc = min(number_of_characters_to_copy, src_len);

  const auto ret_val{noctc + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (copy_options ==
      str_copy_behavior::do_not_copy_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (copy_options == str_copy_behavior::disallow_partial_copy)
      return 0u;

    if (copy_options == str_copy_behavior::allow_partial_copy) {
      auto const no_chars_to_copy = dst_capacity_in_number_of_characters - 1;

      copy(src, src + no_chars_to_copy, dst);

      dst[no_chars_to_copy] = U'\0';

      return no_chars_to_copy;
    }
  }

  copy(src, src + noctc, dst);

  dst[noctc] = U'\0';

  return noctc;
}

size_t str_append(char* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char* src,
                  const str_append_behavior append_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = '\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = '\0';

  return src_len;
}

size_t str_append(wchar_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const wchar_t* src,
                  const str_append_behavior append_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = L'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = L'\0';

  return src_len;
}

size_t str_append(char16_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char16_t* src,
                  const str_append_behavior append_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = u'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = u'\0';

  return src_len;
}

size_t str_append(char32_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char32_t* src,
                  const str_append_behavior append_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  const auto ret_val{dst_len + src_len + 1};

  if (required_dst_capacity)
    *required_dst_capacity = ret_val;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only)
    return ret_val;

  if (dst_capacity_in_number_of_characters < ret_val) {
    if (append_options == str_append_behavior::disallow_partial_append)
      return ret_val;

    if (append_options == str_append_behavior::allow_partial_append) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_copy, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = U'\0';

      return no_of_chars_to_copy;
    }
  }

  copy(src, src + src_len, dst + dst_len);

  dst[dst_len + src_len] = U'\0';

  return src_len;
}

size_t str_append_n(char* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const char* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options,
                    size_t* required_dst_capacity) {
  const auto src_len{str_length(src)};

  const auto dst_len{str_length(dst)};

  size_t ret_val{};

  auto no_of_chars_to_append = min(src_len, number_of_characters_to_append);

  const auto required_dst_capacity_in_ch_count =
      dst_len + no_of_chars_to_append + 1;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only) {
    ret_val = no_of_chars_to_append;
  } else if (dst_capacity_in_number_of_characters <
             required_dst_capacity_in_ch_count) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      ret_val = 0u;
    } else if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = '\0';

      ret_val = no_of_chars_to_append;
    }
  } else {
    copy(src, src + no_of_chars_to_append, dst + dst_len);

    dst[dst_len + no_of_chars_to_append] = '\0';

    ret_val = no_of_chars_to_append;
  }

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_capacity_in_ch_count;

  return ret_val;
}

size_t str_append_n(wchar_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const wchar_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options,
                    size_t* required_dst_capacity) {
  const auto src_len{str_length(src)};

  const auto dst_len{str_length(dst)};

  size_t ret_val{};

  auto no_of_chars_to_append = min(src_len, number_of_characters_to_append);

  const auto required_dst_capacity_in_ch_count =
      dst_len + no_of_chars_to_append + 1;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only) {
    ret_val = no_of_chars_to_append;
  } else if (dst_capacity_in_number_of_characters <
             required_dst_capacity_in_ch_count) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      ret_val = 0u;
    } else if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = L'\0';

      ret_val = no_of_chars_to_append;
    }
  } else {
    copy(src, src + no_of_chars_to_append, dst + dst_len);

    dst[dst_len + no_of_chars_to_append] = L'\0';

    ret_val = no_of_chars_to_append;
  }

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_capacity_in_ch_count;

  return ret_val;
}

size_t str_append_n(char16_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const char16_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options,
                    size_t* required_dst_capacity) {
  const auto src_len{str_length(src)};

  const auto dst_len{str_length(dst)};

  size_t ret_val{};

  auto no_of_chars_to_append = min(src_len, number_of_characters_to_append);

  const auto required_dst_capacity_in_ch_count =
      dst_len + no_of_chars_to_append + 1;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only) {
    ret_val = no_of_chars_to_append;
  } else if (dst_capacity_in_number_of_characters <
             required_dst_capacity_in_ch_count) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      ret_val = 0u;
    } else if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = u'\0';

      ret_val = no_of_chars_to_append;
    }
  } else {
    copy(src, src + no_of_chars_to_append, dst + dst_len);

    dst[dst_len + no_of_chars_to_append] = u'\0';

    ret_val = no_of_chars_to_append;
  }

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_capacity_in_ch_count;

  return ret_val;
}

size_t str_append_n(char32_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const char32_t* src,
                    const size_t number_of_characters_to_append,
                    const str_append_behavior append_options,
                    size_t* required_dst_capacity) {
  const auto src_len{str_length(src)};

  const auto dst_len{str_length(dst)};

  size_t ret_val{};

  auto no_of_chars_to_append = min(src_len, number_of_characters_to_append);

  const auto required_dst_capacity_in_ch_count =
      dst_len + no_of_chars_to_append + 1;

  if (append_options ==
      str_append_behavior::
          do_not_append_return_required_dst_buffer_capacity_only) {
    ret_val = no_of_chars_to_append;
  } else if (dst_capacity_in_number_of_characters <
             required_dst_capacity_in_ch_count) {
    if (append_options == str_append_behavior::disallow_partial_append) {
      ret_val = 0u;
    } else if (append_options == str_append_behavior::allow_partial_append) {
      no_of_chars_to_append =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy(src, src + no_of_chars_to_append, dst + dst_len);

      dst[dst_capacity_in_number_of_characters - 1] = U'\0';

      ret_val = no_of_chars_to_append;
    }
  } else {
    copy(src, src + no_of_chars_to_append, dst + dst_len);

    dst[dst_len + no_of_chars_to_append] = U'\0';

    ret_val = no_of_chars_to_append;
  }

  if (required_dst_capacity)
    *required_dst_capacity = required_dst_capacity_in_ch_count;

  return ret_val;
}

size_t str_prepend(char* dst,
                   const size_t dst_capacity_in_number_of_characters,
                   const char* src,
                   const str_prepend_behaviour prepend_options,
                   size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = '\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[dst_len + no_of_chars_to_copy] = '\0';

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

size_t str_prepend(wchar_t* dst,
                   const size_t dst_capacity_in_number_of_characters,
                   const wchar_t* src,
                   const str_prepend_behaviour prepend_options,
                   size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = L'\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[dst_len + no_of_chars_to_copy] = L'\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = L'\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

size_t str_prepend(char16_t* dst,
                   const size_t dst_capacity_in_number_of_characters,
                   const char16_t* src,
                   const str_prepend_behaviour prepend_options,
                   size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = u'\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[dst_len + no_of_chars_to_copy] = u'\0';

      ret_val = no_of_chars_to_copy;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = u'\0';

      ret_val = src_len;
    }
  }

  if (required_dst_capacity)
    *required_dst_capacity = dst_len + src_len + 1;

  return ret_val;
}

size_t str_prepend(char32_t* dst,
                   const size_t dst_capacity_in_number_of_characters,
                   const char32_t* src,
                   const str_prepend_behaviour prepend_options,
                   size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = U'\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[dst_len + no_of_chars_to_copy] = U'\0';

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

size_t str_prepend_n(char* dst,
                     const size_t dst_capacity_in_number_of_characters,
                     const char* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options,
                     size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = '\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      nocp = dst_capacity_in_number_of_characters - dst_len - 1;

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

size_t str_prepend_n(wchar_t* dst,
                     const size_t dst_capacity_in_number_of_characters,
                     const wchar_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options,
                     size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = L'\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      nocp = dst_capacity_in_number_of_characters - dst_len - 1;

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

size_t str_prepend_n(char16_t* dst,
                     const size_t dst_capacity_in_number_of_characters,
                     const char16_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options,
                     size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + nocp);

      copy(src, src + nocp, dst);

      dst[dst_len + nocp] = u'\0';

      ret_val = nocp;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < (dst_len + nocp + 1)) {
      nocp = dst_capacity_in_number_of_characters - dst_len - 1;

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

size_t str_prepend_n(char32_t* dst,
                     const size_t dst_capacity_in_number_of_characters,
                     const char32_t* src,
                     const size_t number_of_characters_to_prepend,
                     const str_prepend_behaviour prepend_options,
                     size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  size_t ret_val{};

  if (prepend_options ==
      str_prepend_behaviour::
          do_not_prepend_return_required_dst_buffer_capacity_only) {
    ret_val = dst_len + src_len + 1;
  } else if (prepend_options ==
             str_prepend_behaviour::disallow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      ret_val = 0u;
    } else {
      copy_backward(dst, dst + dst_len, dst + dst_len + src_len);

      copy(src, src + src_len, dst);

      dst[dst_len + src_len] = U'\0';

      ret_val = src_len;
    }
  } else if (prepend_options == str_prepend_behaviour::allow_partial_prepend) {
    if (dst_capacity_in_number_of_characters < dst_len + src_len + 1) {
      auto const no_of_chars_to_copy =
          dst_capacity_in_number_of_characters - dst_len - 1;

      copy_backward(dst, dst + dst_len, dst + dst_len + no_of_chars_to_copy);

      copy(src, src + no_of_chars_to_copy, dst);

      dst[dst_len + no_of_chars_to_copy] = U'\0';

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

size_t str_insert(char* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const size_t position_index_in_dst,
                  const char* src,
                  const str_insert_behaviour insert_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
             (dst_capacity_in_number_of_characters < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    auto const nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            src_len);

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

size_t str_insert(wchar_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const size_t position_index_in_dst,
                  const wchar_t* src,
                  const str_insert_behaviour insert_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
             (dst_capacity_in_number_of_characters < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    auto const nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            src_len);

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

size_t str_insert(char16_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const size_t position_index_in_dst,
                  const char16_t* src,
                  const str_insert_behaviour insert_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
             (dst_capacity_in_number_of_characters < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    auto const nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            src_len);

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

size_t str_insert(char32_t* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const size_t position_index_in_dst,
                  const char32_t* src,
                  const str_insert_behaviour insert_options,
                  size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

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
             (dst_capacity_in_number_of_characters < (dst_len + src_len + 1))) {
    ret_val = 0u;
  } else {
    auto const nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            src_len);

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

size_t str_insert_n(char* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const size_t position_index_in_dst,
                    const char* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options,
                    size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  auto nocti = min(number_of_characters_to_insert, src_len);

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
             (dst_capacity_in_number_of_characters < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            nocti);

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

size_t str_insert_n(wchar_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const size_t position_index_in_dst,
                    const wchar_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options,
                    size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  auto nocti = min(number_of_characters_to_insert, src_len);

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
             (dst_capacity_in_number_of_characters < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            nocti);

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

size_t str_insert_n(char16_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const size_t position_index_in_dst,
                    const char16_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options,
                    size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  auto nocti = min(number_of_characters_to_insert, src_len);

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
             (dst_capacity_in_number_of_characters < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            nocti);

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

size_t str_insert_n(char32_t* dst,
                    const size_t dst_capacity_in_number_of_characters,
                    const size_t position_index_in_dst,
                    const char32_t* src,
                    const size_t number_of_characters_to_insert,
                    const str_insert_behaviour insert_options,
                    size_t* required_dst_capacity) {
  auto const src_len = str_length(src);
  auto const dst_len = str_length(dst);

  auto nocti = min(number_of_characters_to_insert, src_len);

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
             (dst_capacity_in_number_of_characters < (dst_len + nocti + 1))) {
    ret_val = 0u;
  } else {
    nocti =
        min(dst_capacity_in_number_of_characters - position_index_in_dst - 1,
            nocti);

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

size_t str_replace_first(char* dst,
                         const size_t dst_capacity_in_number_of_characters,
                         const char* needle,
                         const char* replace,
                         size_t* required_dst_capacity) {
  auto const dst_len{str_length(dst)};
  auto const needle_len{str_length(needle)};
  auto const replace_len{str_length(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((dst_capacity_in_number_of_characters - 1) < rdc) {
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

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len +
                      noctm);  // copy characters from range [dst + start_pos +
                               // needle_len, dst + dst_len) to [dst + start_pos
                               // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = '\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  } else  // needle_len > replace_len
  {
    auto const noctm = needle_len - replace_len;

    // if needle_len == 10 and replace_len == 2, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward dst
    // + start_pos + replace_len.

    for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
      dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

    dst[dst_len - noctm] = '\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }
}

size_t str_replace_first(wchar_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
                         const wchar_t* needle,
                         const wchar_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{str_length(dst)};
  auto const needle_len{str_length(needle)};
  auto const replace_len{str_length(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((dst_capacity_in_number_of_characters - 1) < rdc) {
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

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len +
                      noctm);  // copy characters from range [dst + start_pos +
                               // needle_len, dst + dst_len) to [dst + start_pos
                               // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = L'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  } else  // needle_len > replace_len
  {
    auto const noctm = needle_len - replace_len;

    // if needle_len == 10 and replace_len == 2, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward dst
    // + start_pos + replace_len.

    for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
      dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

    dst[dst_len - noctm] = L'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }
}

size_t str_replace_first(char16_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
                         const char16_t* needle,
                         const char16_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{str_length(dst)};
  auto const needle_len{str_length(needle)};
  auto const replace_len{str_length(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((dst_capacity_in_number_of_characters - 1) < rdc) {
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

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len +
                      noctm);  // copy characters from range [dst + start_pos +
                               // needle_len, dst + dst_len) to [dst + start_pos
                               // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = u'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  } else  // needle_len > replace_len
  {
    auto const noctm = needle_len - replace_len;

    // if needle_len == 10 and replace_len == 2, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward dst
    // + start_pos + replace_len.

    for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
      dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

    dst[dst_len - noctm] = u'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }
}

size_t str_replace_first(char32_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
                         const char32_t* needle,
                         const char32_t* replace,
                         size_t* required_dst_capacity = nullptr) {
  auto const dst_len{str_length(dst)};
  auto const needle_len{str_length(needle)};
  auto const replace_len{str_length(replace)};

  size_t rdc;

  if (needle_len > dst_len) {
    rdc = max(dst_len, replace_len);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  rdc = dst_len - needle_len + replace_len;

  auto const start_pos = str_index_of(dst, needle);

  if (start_pos == string::npos) {
    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 0u;
  }

  if ((dst_capacity_in_number_of_characters - 1) < rdc) {
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

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward(dst + start_pos + needle_len, dst + dst_len,
                  dst + dst_len +
                      noctm);  // copy characters from range [dst + start_pos +
                               // needle_len, dst + dst_len) to [dst + start_pos
                               // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = U'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  } else  // needle_len > replace_len
  {
    auto const noctm = needle_len - replace_len;

    // if needle_len == 10 and replace_len == 2, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward dst
    // + start_pos + replace_len.

    for (auto i = 0; i < dst_len - (start_pos + needle_len); i++)
      dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

    dst[dst_len - noctm] = U'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }
}

/*

char16_t* u16_strcat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src)
{
        if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

        auto const src_len = u16_strlen(src);

        auto const dst_len = u16_strlen(dst);

        if (src_len > (dst_capacity_in_number_of_characters - dst_len - 1))
return dst;

        while (*dst) dst++;

        if (*src == u'\0') return dst;

        copy(src, src + src_len, dst);

        dst[src_len] = u'\0';

        return dst;
}

char32_t* u32_strcat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src)
{
        if (!dst || !src || !dst_capacity_in_number_of_characters) return dst;

        auto const src_len = u32_strlen(src);

        auto const dst_len = u32_strlen(dst);

        if (src_len > (dst_capacity_in_number_of_characters - dst_len - 1))
return dst;

        while (*dst) dst++;

        if (*src == U'\0') return dst;

        copy(src, src + src_len, dst);

        dst[src_len] = U'\0';

        return dst;
}

char16_t* u16_strncat(char16_t* dst, const size_t
dst_capacity_in_number_of_characters, const char16_t* src, const size_t
number_of_characters_to_concatenate)
{
        if (!dst || !src || !dst_capacity_in_number_of_characters ||
!number_of_characters_to_concatenate) return dst;

        auto const src_len = u16_strlen(src);

        auto const dst_len = u16_strlen(dst);

        auto const noctc = min(number_of_characters_to_concatenate, src_len);

        if (noctc > (dst_capacity_in_number_of_characters - dst_len - 1)) return
dst;

        while (*dst) dst++;

        if (*src == u'\0') return dst;

        copy(src, src + noctc, dst);

        dst[noctc] = u'\0';

        return dst;
}

char32_t* u32_strncat(char32_t* dst, const size_t
dst_capacity_in_number_of_characters, const char32_t* src, const size_t
number_of_characters_to_concatenate)
{
        if (!dst || !src || !dst_capacity_in_number_of_characters ||
!number_of_characters_to_concatenate) return dst;

        auto const src_len = u32_strlen(src);

        auto const dst_len = u32_strlen(dst);

        auto const noctc = min(number_of_characters_to_concatenate, src_len);

        if ((dst_capacity_in_number_of_characters - dst_len - 1) < noctc) return
dst;

        while (*dst) dst++;

        if (*src == U'\0') return dst;

        copy(src, src + noctc, dst);

        dst[noctc] = U'\0';

        return dst;
}

const char16_t* u16_strstr(const char16_t* src, const char16_t* needle)
{
        if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return
nullptr;

        auto si = size_t{0u};

        auto const src_len = u16_strlen(src);
        auto const needle_len = u16_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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
        if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return
nullptr;

        size_t si{0u};

        auto const src_len = u32_strlen(src);
        auto const needle_len = u32_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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
        if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return
nullptr;

        size_t si{0u};

        auto const src_len = u16_strlen(src);
        auto const needle_len = u16_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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
        if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return
nullptr;

        size_t si{0u};

        auto const src_len = u32_strlen(src);
        auto const needle_len = u32_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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

const char16_t* u16_strstri(const char16_t* src, const char16_t* needle, const
locale& loc)
{
        if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return
nullptr;

        auto si = size_t{0u};

        auto const src_len = u16_strlen(src);
        auto const needle_len = u16_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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

const char32_t* u32_strstri(const char32_t* src, const char32_t* needle, const
locale& loc)
{
        if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return
nullptr;

        auto si = size_t{0u};

        auto const src_len = u32_strlen(src);
        auto const needle_len = u32_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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

char16_t* u16_strstri(char16_t* src, const char16_t* needle, const locale& loc)
{
        if (!src || !needle || ((*src == u'\0') && (*needle != u'\0'))) return
nullptr;

        auto si = size_t{0u};

        auto const src_len = u16_strlen(src);
        auto const needle_len = u16_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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

char32_t* u32_strstri(char32_t* src, const char32_t* needle, const locale& loc)
{
        if (!src || !needle || ((*src == U'\0') && (*needle != U'\0'))) return
nullptr;

        auto si = size_t{0u};

        auto const src_len = u32_strlen(src);
        auto const needle_len = u32_strlen(needle);

        if ((src_len == 0) || (needle_len == 0) || (needle_len > src_len))
return nullptr;

        bool match_found{false};

        while (!match_found)
        {
                if ((si + needle_len) > src_len) break;

                match_found = true;

                for (size_t i{0u}, mi{0u}; (match_found && (i < needle_len));
i++ , mi++)
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
}*/

u16string to_u16string(short number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<short>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(unsigned short number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<unsigned short>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(int number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = [&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }();

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(unsigned int number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<unsigned int>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(unsigned long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<unsigned long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(long long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<long long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(unsigned long long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u16string number_str{};

  auto const base = static_cast<unsigned long long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    auto character_code_offset = static_cast<size_t>(number % base);

    char16_t character_to_use =
        static_cast<char16_t>(u'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char16_t>(u'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0b");
          break;

        case 8:
          number_str.insert(0, u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, u"0B");
          break;

        case 8:
          number_str.insert(0, u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, u"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0b");
          break;

        case 8:
          number_str.append(u"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(u"0B");
          break;

        case 8:
          number_str.append(u"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(u"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u16string to_u16string(float number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*f", number_of_decimal_digits, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char16_t>(ch); });

  return number_str;
}

u16string to_u16string(double number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*lf", number_of_decimal_digits, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char16_t>(ch); });

  return number_str;
}

u16string to_u16string(long double number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*Lf", number_of_decimal_digits, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char16_t>(ch); });

  return number_str;
}

u32string to_u32string(short number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<short>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<char32_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(unsigned short number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<unsigned short>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<size_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(int number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = [&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }();

  while (number) {
    const char32_t character_code_offset = static_cast<char32_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(unsigned int number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<unsigned int>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<size_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<size_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(unsigned long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<unsigned long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<size_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(long long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<long long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<char32_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(unsigned long long number,
                       const number_base convert_to_number_base,
                       const add_number_base_sign number_base_sign) {
  u32string number_str{};

  auto const base = static_cast<unsigned long long>([&]() {
    switch (convert_to_number_base) {
      case number_base::binary:
        return 2;

      case number_base::octal:
        return 8;

      case number_base::decimal:
        return 10;

      case number_base::hexadecimal:
        return 16;

      default:
        return 10;
    }
  }());

  while (number) {
    const char32_t character_code_offset = static_cast<char32_t>(number % base);

    auto character_to_use = static_cast<char32_t>(U'0' + character_code_offset);

    if ((base == 16) && (character_code_offset > 9)) {
      character_to_use =
          static_cast<char32_t>(U'A' + (character_code_offset - 10));
    }

    number_str.insert(begin(number_str), character_to_use);

    number /= base;
  }

  switch (number_base_sign) {
    case add_number_base_sign::no_number_base_sign:

      return number_str;

    case add_number_base_sign::prepend_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0b");
          break;

        case 8:
          number_str.insert(0, U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::prepend_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.insert(0, U"0B");
          break;

        case 8:
          number_str.insert(0, U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.insert(0, U"0X");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_lower_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0b");
          break;

        case 8:
          number_str.append(U"0o");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0x");
          break;

        default:
          break;
      }

      return number_str;

    case add_number_base_sign::append_in_upper_case_format:

      switch (base) {
        case 2:
          number_str.append(U"0B");
          break;

        case 8:
          number_str.append(U"0O");
          break;

        case 10:
          break;

        case 16:
          number_str.append(U"0X");
          break;

        default:
          break;
      }

      return number_str;

    default:

      return number_str;
  }
}

u32string to_u32string(float number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*f", number_of_decimal_digits, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char32_t>(ch); });

  return number_str;
}

u32string to_u32string(double number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*lf", number_of_decimal_digits, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char32_t>(ch); });

  return number_str;
}

u32string to_u32string(long double number, const int number_of_decimal_digits) {
  char buffer[128];

  auto const count =
      _snprintf(buffer, 128, "%.*Lf", number_of_decimal_digits, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [&](const auto ch) { return static_cast<char32_t>(ch); });

  return number_str;
}

int stoi(const u16string& str,
         size_t* pos,
         int base,
         bool ignore_leading_white_space_characters) {
  int number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<int>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<int>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<int>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long stol(const u16string& str,
          size_t* pos,
          int base,
          bool ignore_leading_white_space_characters) {
  long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long stoul(const u16string& str,
                    size_t* pos,
                    int base,
                    bool ignore_leading_white_space_characters) {
  unsigned long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<unsigned long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long long stoll(const u16string& str,
                size_t* pos,
                int base,
                bool ignore_leading_white_space_characters) {
  long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<long long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value += static_cast<long long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value += static_cast<long long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long long stoull(const u16string& str,
                          size_t* pos,
                          int base,
                          bool ignore_leading_white_space_characters) {
  unsigned long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == u"0b") ||
                           (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 8:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 10:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;

      case 16:
        if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
            ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

            || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
            number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

          else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - u'A'));

          else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - u'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < u'0') || (temp_str[i] > u'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - u'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

float stof(const u16string& str,
           size_t* pos,
           int base,
           bool ignore_leading_white_space_characters) {
  float number_value{};

  auto negative_sign_found{false};
  float fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - u'0') *
                                   pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2.f, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - u'0') *
                                   pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8.f, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - u'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10.f, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<float>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value += static_cast<float>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value += static_cast<float>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - u'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10.f, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2.f, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

double stod(const u16string& str,
            size_t* pos,
            int base,
            bool ignore_leading_white_space_characters) {
  double number_value{};

  auto negative_sign_found{false};
  double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - u'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<double>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value += static_cast<double>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value += static_cast<double>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - u'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long double stold(const u16string& str,
                  size_t* pos,
                  int base,
                  bool ignore_leading_white_space_characters) {
  long double number_value{};

  auto negative_sign_found{false};
  long double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == u"0b") || (temp_str.substr(0, 2) == u"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == u'b') || (temp_str[0] == u'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == u"0o") ||
                           (temp_str.substr(0, 2) == u"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == u'0') || (temp_str[0] == u'o') ||
                           (temp_str[0] == u'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == u"0x") ||
                            (temp_str.substr(0, 2) == u"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == u'x') || (temp_str[0] == u'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == u'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == u'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == u'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == u'e') || (temp_str[0] == u'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u16string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - u'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= u'0') && (temp_str[i] <= u'9')) ||
                ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))

                || ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= u'0') && (temp_str[i] <= u'9'))
                number_value += static_cast<long double>(temp_str[i] - u'0');

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - u'A'));

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - u'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == u'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == u'e') || (temp_str[i] == u'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == u'+')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == u'-')) {
          if ((temp_str[i - 1] != u'e') && (temp_str[i - 1] != u'E'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == u'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < u'0') || (temp_str[i] > u'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - u'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - u'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - u'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

int stoi(const u32string& str,
         size_t* pos,
         int base,
         bool ignore_leading_white_space_characters) {
  int number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<int>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<int>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<int>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<int>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long stol(const u32string& str,
          size_t* pos,
          int base,
          bool ignore_leading_white_space_characters) {
  long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long stoul(const u32string& str,
                    size_t* pos,
                    int base,
                    bool ignore_leading_white_space_characters) {
  unsigned long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<unsigned long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value +=
                static_cast<unsigned long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long long stoll(const u32string& str,
                size_t* pos,
                int base,
                bool ignore_leading_white_space_characters) {
  long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<long long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value += static_cast<long long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value += static_cast<long long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<long long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

unsigned long long stoull(const u32string& str,
                          size_t* pos,
                          int base,
                          bool ignore_leading_white_space_characters) {
  unsigned long long number_value{};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  auto found_invalid_character{false};

  if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 2) && ((temp_str.substr(0, 2) == U"0b") ||
                           (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'1'))
          found_invalid_character = true;

        number_value *= 2;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 8:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'7'))
          found_invalid_character = true;

        number_value *= 8;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 10:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;

      case 16:
        if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
            ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

            || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
          number_value *= 16;

          if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
            number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

          else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - U'A'));

          else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
            number_value +=
                static_cast<unsigned long long>(10 + (temp_str[i] - U'a'));
        } else {
          found_invalid_character = true;
        }

        break;

      default:
        if ((temp_str[i] < U'0') || (temp_str[i] > U'9'))
          found_invalid_character = true;

        number_value *= 10;

        number_value += static_cast<unsigned long long>(temp_str[i] - U'0');

        break;
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

float stof(const u32string& str,
           size_t* pos,
           int base,
           bool ignore_leading_white_space_characters) {
  float number_value{};

  auto negative_sign_found{false};
  float fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2.f, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8.f, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10.f, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<float>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value += static_cast<float>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value += static_cast<float>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<float>(static_cast<int>(temp_str[i] - U'0') *
                                   pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<float>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10.f, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2.f, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

double stod(const u32string& str,
            size_t* pos,
            int base,
            bool ignore_leading_white_space_characters) {
  double number_value{};

  auto negative_sign_found{false};
  double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<double>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<double>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value += static_cast<double>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value += static_cast<double>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value +=
                static_cast<double>(static_cast<int>(temp_str[i] - U'0') *
                                    pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

long double stold(const u32string& str,
                  size_t* pos,
                  int base,
                  bool ignore_leading_white_space_characters) {
  long double number_value{};

  auto negative_sign_found{false};
  long double fractional_part_value{};
  auto fractional_part_found{false};
  int fractional_part_position_index{-1};

  auto exponential_sign_found{false};
  auto negative_exponent_sign_found{false};
  auto exponent_leading_zero_values{true};
  int exponential_part_value{};

  auto found_invalid_character{false};

  auto temp_str{str};

  if (ignore_leading_white_space_characters)
    temp_str = ltrim(str);

  if ((base == 2) &&
      ((temp_str.substr(0, 2) == U"0b") || (temp_str.substr(0, 2) == U"0B"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 2) && ((temp_str[0] == U'b') || (temp_str[0] == U'B'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 8) && ((temp_str.substr(0, 2) == U"0o") ||
                           (temp_str.substr(0, 2) == U"0O"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 8) && ((temp_str[0] == U'0') || (temp_str[0] == U'o') ||
                           (temp_str[0] == U'O'))) {
    temp_str.erase(cbegin(temp_str));
  }

  else if ((base == 16) && ((temp_str.substr(0, 2) == U"0x") ||
                            (temp_str.substr(0, 2) == U"0X"))) {
    temp_str.assign(temp_str.substr(2));
  }

  else if ((base == 16) && ((temp_str[0] == U'x') || (temp_str[0] == U'X'))) {
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'+') {
    temp_str.erase(cbegin(temp_str));
  }

  else if (temp_str[0] == U'-') {
    negative_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (temp_str[0] == U'.') {
    fractional_part_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  if (pos)
    *pos = 0;

  if (!fractional_part_found && (temp_str[0] == U'0'))
    return number_value;

  if ((base != 16) && ((temp_str[0] == U'e') || (temp_str[0] == U'E'))) {
    if (fractional_part_found)
      return number_value;
    exponential_sign_found = true;
    temp_str.erase(cbegin(temp_str));
  }

  u32string::size_type i{0u};

  for (; (!found_invalid_character && (i < temp_str.size())); i++) {
    switch (base) {
      case 2:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'1')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(2.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 2;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(2, exponential_part_value);
          }
        }

        break;

      case 8:

        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'7')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 2;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(8.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 8;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(8, exponential_part_value);
          }
        }

        break;

      case 10:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;

      case 16:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        } else {
          if (fractional_part_found) {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'0') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'A') *
                    pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f')) {
                fractional_part_value += static_cast<long double>(
                    static_cast<int>(temp_str[i] - U'a') *
                    pow(16.f, fractional_part_position_index));
              }

              fractional_part_position_index--;
            } else {
              found_invalid_character = true;
            }
          } else {
            if (((temp_str[i] >= U'0') && (temp_str[i] <= U'9')) ||
                ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))

                || ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))) {
              number_value *= 16;

              if ((temp_str[i] >= U'0') && (temp_str[i] <= U'9'))
                number_value += static_cast<long double>(temp_str[i] - U'0');

              else if ((temp_str[i] >= U'A') && (temp_str[i] <= U'F'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - U'A'));

              else if ((temp_str[i] >= U'a') && (temp_str[i] <= U'f'))
                number_value +=
                    static_cast<long double>(10 + (temp_str[i] - U'a'));
            } else {
              found_invalid_character = true;
            }
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;
        }

        break;

      default:
        if (temp_str[i] == U'.') {
          if (!fractional_part_found) {
            fractional_part_found = true;
            fractional_part_value = 0.f;
            fractional_part_position_index = -1;
          } else {
            found_invalid_character = true;
          }
        }

        else if (!exponential_sign_found &&
                 ((temp_str[i] == U'e') || (temp_str[i] == U'E'))) {
          exponential_sign_found = true;
        }

        else if (exponential_sign_found && (temp_str[i] == U'+')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && (temp_str[i] == U'-')) {
          if ((temp_str[i - 1] != U'e') && (temp_str[i - 1] != U'e'))
            found_invalid_character = true;

          else
            negative_exponent_sign_found = true;

          exponential_part_value = 0;
        }

        else if (exponential_sign_found && exponent_leading_zero_values &&
                 (temp_str[i] == U'0')) {
          exponential_part_value = 0;
        }

        else if ((temp_str[i] < U'0') || (temp_str[i] > U'9')) {
          found_invalid_character = true;
        }

        else {
          if (exponential_sign_found) {
            exponent_leading_zero_values = false;
            exponential_part_value *= 10;
            exponential_part_value += static_cast<int>(temp_str[i] - U'0');
          } else if (fractional_part_found) {
            fractional_part_value += static_cast<long double>(
                static_cast<int>(temp_str[i] - U'0') *
                pow(10.f, fractional_part_position_index));
            fractional_part_position_index--;
          } else {
            number_value *= 10;
            number_value += static_cast<long double>(temp_str[i] - U'0');
          }
        }

        if (found_invalid_character) {
          number_value += fractional_part_value;

          if (negative_sign_found)
            number_value = -number_value;

          if (exponential_sign_found) {
            if (negative_exponent_sign_found)
              exponential_part_value = -exponential_part_value;

            if (abs(exponential_part_value) != 0)
              number_value *= pow(10, exponential_part_value);
          }
        }

        break;
    }
  }

  if (!found_invalid_character) {
    number_value += fractional_part_value;

    if (negative_sign_found)
      number_value = -number_value;

    if (exponential_sign_found && (base != 16)) {
      if (negative_exponent_sign_found)
        exponential_part_value = -exponential_part_value;

      if (abs(exponential_part_value) != 0)
        number_value *= pow(2, exponential_part_value);
    }
  }

  if (pos)
    *pos = i;

  return number_value;
}

vector<string> split(const char* source,
                     const char needle_char,
                     int const max_count) {
  vector<string> parts{};

  size_t prev = 0, current;

  const string source_st{source};
  const string needle_st(1, needle_char);

  auto const source_len{source_st.size()};

  if ((0u == source_len) || (source_len <= 1))
    return parts;

  size_t number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + 1;

    if (prev >= source_len)
      break;
  } while (string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<wstring> split(const wchar_t* source,
                      const wchar_t needle_char,
                      int const max_count) {
  vector<wstring> parts{};

  size_t prev = 0, current;

  const wstring source_st{source};
  const wstring needle_st(1, needle_char);

  auto const source_len{source_st.size()};

  if ((0u == source_len) || (source_len <= 1))
    return parts;

  size_t number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (wstring::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + 1;

    if (prev >= source_len)
      break;
  } while (wstring::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<u16string> split(const char16_t* source,
                        const char16_t needle_char,
                        int const max_count) {
  vector<u16string> parts{};

  size_t prev = 0, current;

  const u16string source_st{source};
  const u16string needle_st(1, needle_char);

  auto const source_len{source_st.size()};

  if ((0u == source_len) || (source_len <= 1))
    return parts;

  size_t number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (u16string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + 1;

    if (prev >= source_len)
      break;
  } while (u16string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<u32string> split(const char32_t* source,
                        const char32_t needle_char,
                        int const max_count) {
  vector<u32string> parts{};

  size_t prev = 0, current;

  const u32string source_st{source};
  const u32string needle_st(1, needle_char);

  auto const source_len{source_st.size()};

  if ((0u == source_len) || (source_len <= 1))
    return parts;

  size_t number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (u32string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + 1;

    if (prev >= source_len)
      break;
  } while (u32string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<string> split(const char* source,
                     const char* needle,
                     const int max_count) {
  vector<string> parts{};

  size_t prev = 0, current;

  string source_st{source};
  string needle_st{needle};

  auto const source_len{source_st.size()};
  auto const needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len))
    return parts;

  int number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  } while (string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<wstring> split(const wchar_t* source,
                      const wchar_t* needle,
                      const int max_count) {
  vector<wstring> parts{};

  size_t prev = 0, current;

  wstring source_st{source};
  wstring needle_st{needle};

  auto const source_len{source_st.size()};
  auto const needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len))
    return parts;

  auto number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (wstring::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  } while (wstring::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<u16string> split(const char16_t* source,
                        const char16_t* needle,
                        const int max_count) {
  vector<u16string> parts{};

  size_t prev = 0, current;

  u16string source_st{source};
  u16string needle_st{needle};

  auto const source_len{source_st.size()};
  auto const needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len))
    return parts;

  auto number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (u16string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  } while (u16string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

vector<u32string> split(const char32_t* source,
                        const char32_t* needle,
                        const int max_count) {
  vector<u32string> parts{};

  size_t prev = 0, current;

  u32string source_st{source};
  u32string needle_st{needle};

  auto const source_len{source_st.size()};
  auto const needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len) || (needle_len >= source_len))
    return parts;

  auto number_of_parts = 0;

  do {
    current = source_st.find(needle_st, prev);

    if (u32string::npos == current)
      break;

    number_of_parts++;

    if ((-1 != max_count) && (static_cast<int>(parts.size()) == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source_st.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  } while (u32string::npos != current);

  if (number_of_parts > 0 && prev < source_len) {
    if (-1 == max_count)
      parts.emplace_back(source_st.substr(prev));

    else if ((-1 != max_count) && (static_cast<int>(parts.size()) < max_count))
      parts.emplace_back(source_st.substr(prev));
  }

  return parts;
}

}  // namespace experimental
}  // namespace cpp
