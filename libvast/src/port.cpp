#include <tuple>

#include "vast/concept/printable/to_string.hpp"
#include "vast/concept/printable/vast/port.hpp"
#include "vast/json.hpp"
#include "vast/port.hpp"

namespace vast {

port::port(number_type number, port_type type) : number_(number), type_(type) {
}

port::number_type port::number() const {
  return number_;
}

port::port_type port::type() const {
  return type_;
}

void port::number(number_type n) {
  number_ = n;
}

void port::type(port_type t) {
  type_ = t;
}

bool operator==(port const& x, port const& y) {
  return x.number_ == y.number_
         && (x.type_ == y.type_ || x.type_ == port::unknown
             || y.type_ == port::unknown);
}

bool operator<(port const& x, port const& y) {
  return std::tie(x.number_, x.type_) < std::tie(y.number_, y.type_);
}

bool convert(port const& p, json& j) {
  j = to_string(p);
  return true;
}

} // namespace vast
