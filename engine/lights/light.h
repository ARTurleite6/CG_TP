#ifndef LIGHT_H
#define LIGHT_H
#include "../include.h"

class Light {
public:

    static std::uint32_t getNextIndex();
    
  explicit Light(): index(Light::getNextIndex()) {}
  virtual ~Light() { glDisable(GL_LIGHT0 + this->index); }

  void configureColor() const noexcept;
  inline void enable() const noexcept { glEnable(GL_LIGHT0 + this->index); }
  inline void disable() const noexcept { glDisable(GL_LIGHT0 + this->index); }
  [[nodiscard]] inline std::uint32_t getIndex() const noexcept {
    return this->index;
  }

  virtual void place() const = 0;

private:
  std::uint32_t index;

  static std::uint32_t current_index;
};

#endif // LIGHT_H
