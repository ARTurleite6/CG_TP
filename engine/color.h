#ifndef COLOR_H
#define COLOR_H
#include <tinyxml2.h>

class Color {
public:
  explicit Color(tinyxml2::XMLElement *element = nullptr);

private:
  struct ParamRGB {
    float r, g, b;
  };

  ParamRGB diffuse{200, 200, 200};
  ParamRGB ambient{50, 50, 50};
  ParamRGB specular{0, 0, 0};
  ParamRGB emissive{0, 0, 0};
  float shininess{0};
};

#endif //  COLOR_H
