#include "parsing.h"

bool queryBooleanAttr(const tinyxml2::XMLElement *element,
                      std::string_view name) {
  bool result{false};
  if (element->QueryBoolAttribute(name.data(), &result) !=
      tinyxml2::XML_SUCCESS) {
    throw errors::XMLParseError(fmt::format("Expected element {} on element {}",
                                            name, element->Name()));
  }
  return result;
}

int queryIntegerAttr(const tinyxml2::XMLElement *element,
                     std::string_view name) {
  int result{0};
  if (element->QueryIntAttribute(name.data(), &result) !=
      tinyxml2::XML_SUCCESS) {
    throw errors::XMLParseError(fmt::format("Expected element {} on element {}",
                                            name, element->Name()));
  }

  return result;
}

float queryFloatAttr(const tinyxml2::XMLElement *element,
                     std::string_view name) {
  float result{0};
  if (element->QueryFloatAttribute(name.data(), &result) !=
      tinyxml2::XML_SUCCESS) {
    throw errors::XMLParseError(fmt::format("Expected element {} on element {}",
                                            name, element->Name()));
  }

  return result;
}

std::uint32_t queryUnsignedAttr(const tinyxml2::XMLElement *element,
                                std::string_view name) {
  std::uint32_t result{0};
  if (element->QueryUnsignedAttribute(name.data(), &result) !=
      tinyxml2::XML_SUCCESS) {
    throw errors::XMLParseError(fmt::format("Expected element {} on element {}",
                                            name, element->Name()));
  }

  return result;
}
