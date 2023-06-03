#ifndef COLOR_H
#define COLOR_H
#include "include.h"
#include <tinyxml2.h>

class Color {
public:
  explicit Color(tinyxml2::XMLElement *element = nullptr);

  void setup() const noexcept;

private:
  struct ParamRGB {
    float r, g, b;
    void normalize() noexcept {
      this->r /= 255.0f;
      this->g /= 255.0f;
      this->b /= 255.0f;
    }
  };

  ParamRGB diffuse{200, 200, 200};
  ParamRGB ambient{50, 50, 50};
  ParamRGB specular{0, 0, 0};
  ParamRGB emissive{0, 0, 0};
  float shininess{0};
};

#endif //  COLOR_H
