#ifndef PARSING_H
#define PARSING_H
#include "parse_errors/xml_parse_error.h"
#include <functional>
#include <tinyxml2.h>

int queryIntegerAttr(const tinyxml2::XMLElement *element,
                     std::string_view name);

float queryFloatAttr(const tinyxml2::XMLElement *element,
                     std::string_view name);

std::uint32_t queryUnsignedAttr(const tinyxml2::XMLElement *element,
                                std::string_view name);

bool queryBooleanAttr(const tinyxml2::XMLElement *element,
                      std::string_view name);

#endif // PARSING_H
