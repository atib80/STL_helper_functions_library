#include "stl_helper_functions.hpp"

using namespace std;

namespace cpp {
namespace experimental {

size_t str_append(char* dst,
                  const size_t dst_capacity_in_number_of_characters,
                  const char* src,
                  const str_append_behavior append_options,
                  size_t* required_dst_capacity) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  const auto src_len{len(src)};

  const auto dst_len{len(dst)};

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
  const auto src_len{len(src)};

  const auto dst_len{len(dst)};

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
  const auto src_len{len(src)};

  const auto dst_len{len(dst)};

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
  const auto src_len{len(src)};

  const auto dst_len{len(dst)};

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
                     const str_prepend_behaviour prepend_options,
                     size_t* required_dst_capacity) {
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
  auto const src_len = len(src);
  auto const dst_len = len(dst);

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
    size_t const noctm{replace_len - needle_len};

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward<char*, char*>(dst + start_pos + needle_len, dst + dst_len,
                                dst + dst_len + noctm);
    // copy characters from range [dst + start_pos +
    // needle_len, dst + dst_len) to [dst + start_pos
    // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = '\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in the upper
  // part of dst ( characters with positions >= dst + start_pos + needle_len
  // characters ) have to be moved 'noctm' (8) character positions toward dst
  // + start_pos + replace_len.

  for (size_t i{}; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = '\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

size_t str_replace_first(wchar_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
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
    size_t const noctm{replace_len - needle_len};

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward<wchar_t*, wchar_t*>(dst + start_pos + needle_len,
                                      dst + dst_len, dst + dst_len + noctm);
    // copy characters from range [dst + start_pos +
    // needle_len, dst + dst_len) to [dst + start_pos
    // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = L'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in the upper
  // part of dst ( characters with positions >= dst + start_pos + needle_len
  // characters ) have to be moved 'noctm' (8) character positions toward dst
  // + start_pos + replace_len.

  for (size_t i{}; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = L'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

size_t str_replace_first(char16_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
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
    size_t const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward<char16_t*, char16_t*>(
        dst + start_pos + needle_len, dst + dst_len,
        dst + dst_len +
            noctm);  // copy characters from range [dst + start_pos +
    // needle_len, dst + dst_len) to [dst + start_pos
    // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = u'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in the upper
  // part of dst ( characters with positions >= dst + start_pos + needle_len
  // characters ) have to be moved 'noctm' (8) character positions toward dst
  // + start_pos + replace_len.

  for (size_t i{}; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = u'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
}

size_t str_replace_first(char32_t* dst,
                         const size_t dst_capacity_in_number_of_characters,
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
    size_t const noctm = replace_len - needle_len;

    // if needle_len == 2 and replace_len == 10, all the characters in the upper
    // part of dst ( characters with positions >= dst + start_pos + needle_len
    // characters ) have to be moved 'noctm' (8) character positions toward the
    // end of dst.

    copy_backward<char32_t*, char32_t*>(
        dst + start_pos + needle_len, dst + dst_len,
        dst + dst_len +
            noctm);  // copy characters from range [dst + start_pos +
    // needle_len, dst + dst_len) to [dst + start_pos
    // + needle_len + noctm, dst + dst_len + noctm)
    dst[dst_len + noctm] = U'\0';

    copy(replace, replace + replace_len, dst + start_pos);

    if (required_dst_capacity)
      *required_dst_capacity = rdc;

    return 1u;
  }  // needle_len > replace_len
  auto const noctm = needle_len - replace_len;

  // if needle_len == 10 and replace_len == 2, all the characters in the upper
  // part of dst ( characters with positions >= dst + start_pos + needle_len
  // characters ) have to be moved 'noctm' (8) character positions toward dst
  // + start_pos + replace_len.

  for (size_t i{}; i < dst_len - (start_pos + needle_len); i++)
    dst[start_pos + replace_len + i] = dst[start_pos + needle_len + i];

  dst[dst_len - noctm] = U'\0';

  copy(replace, replace + replace_len, dst + start_pos);

  if (required_dst_capacity)
    *required_dst_capacity = rdc;

  return 1u;
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
  }
}

u16string to_u16string(float number, const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%uf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char16_t>(ch); });

  return number_str;
}

u16string to_u16string(double number, const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%ulf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char16_t>(ch); });

  return number_str;
}

u16string to_u16string(long double number,
                       const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%uLf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u16string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char16_t>(ch); });

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
  }
}

u32string to_u32string(float number, const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%uf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char32_t>(ch); });

  return number_str;
}

u32string to_u32string(double number, const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%ulf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char32_t>(ch); });

  return number_str;
}

u32string to_u32string(long double number,
                       const unsigned number_of_decimal_digits) {
  wchar_t format_str_buffer[32], buffer[32];
  snwprintf(format_str_buffer, 32, L"%%.%uLf", number_of_decimal_digits);

  auto const count = snwprintf(buffer, 32, format_str_buffer, number);

  u32string number_str{};

  transform(buffer, buffer + count, back_inserter(number_str),
            [](const auto ch) { return static_cast<char32_t>(ch); });

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
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(2.f, fractional_part_position_index));
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
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(8.f, fractional_part_position_index));
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
              number_value *= std::pow(8.f, exponential_part_value);
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
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(10.f, fractional_part_position_index));
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
              number_value *= std::pow(10.f, exponential_part_value);
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
                    std::pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'A') && (temp_str[i] <= u'F')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'A') *
                    std::pow(16.f, fractional_part_position_index));
              }

              else if ((temp_str[i] >= u'a') && (temp_str[i] <= u'f')) {
                fractional_part_value += static_cast<float>(
                    static_cast<int>(temp_str[i] - u'a') *
                    std::pow(16.f, fractional_part_position_index));
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
            fractional_part_value += static_cast<float>(
                static_cast<int>(temp_str[i] - u'0') *
                std::pow(10.f, fractional_part_position_index));
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

}  // namespace experimental
}  // namespace cpp
