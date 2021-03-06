#ifndef VAST_CONCEPT_PRINTABLE_VAST_FILESYSTEM_HPP
#define VAST_CONCEPT_PRINTABLE_VAST_FILESYSTEM_HPP

#include "vast/filesystem.hpp"
#include "vast/concept/printable/core/printer.hpp"
#include "vast/concept/printable/string/string.hpp"

namespace vast {

struct path_printer : printer<path_printer> {
  using attribute = path;

  template <typename Iterator>
  bool print(Iterator& out, path const& p) const {
    return printers::str.print(out, p.str());
  }
};

template <>
struct printer_registry<path> {
  using type = path_printer;
};

} // namespace vast

#endif
