#ifndef PARSING_H
#define PARSING_H
#include "parse_errors/xml_parse_error.h"
#include <functional>
#include <tinyxml2.h>

int queryIntegerAttr(tinyxml2::XMLElement *element,
                            std::string_view name);

float queryFloatAttr(tinyxml2::XMLElement *element,
                            std::string_view name);

std::uint32_t queryUnsignedAttr(tinyxml2::XMLElement *element,
                                       std::string_view name);

#endif // PARSING_H
