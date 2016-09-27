#ifndef VAST_CONCEPT_PRINTABLE_VAST_HTTP_HPP
#define VAST_CONCEPT_PRINTABLE_VAST_HTTP_HPP

#include <string>

#include "vast/concept/printable/core.hpp"
#include "vast/concept/printable/numeric/integral.hpp"
#include "vast/concept/printable/numeric/real.hpp"
#include "vast/concept/printable/string/any.hpp"
#include "vast/concept/printable/string/string.hpp"
#include "vast/http.hpp"

namespace vast {

struct http_header_printer : printer<http_header_printer> {
  using attribute = http::header;

  template <typename Iterator>
  bool print(Iterator& out, http::header const& hdr) const {
    using namespace printers;
    auto p = str << ": " << str;
    return p.print(out, std::tie(hdr.name, hdr.value));
  }
};

template <>
struct printer_registry<http::header> {
  using type = http_header_printer;
};

struct http_response_printer : printer<http::response> {
  using attribute = http::response;

  template <typename Iterator>
  bool print(Iterator& out, http::response const& res) const {
    using namespace printers;
    auto version = real_printer<double, 1>{};
    auto p 
      =   str     // proto
      << '/' 
      << version 
      << ' ' 
      << u32      // status code
      << ' ' 
      << str      // status text
      << "\r\n"
      << ~(http_header_printer{} % "\r\n")
      << "\r\n\r\n"
      << str      // body
      ;
    auto t = std::tie(res.protocol, res.version, res.status_code,
                      res.status_text, res.headers, res.body);
    return p.print(out, t);
  }
};

template <>
struct printer_registry<http::response> {
  using type = http_response_printer;
};

} // namespace vast

#endif
