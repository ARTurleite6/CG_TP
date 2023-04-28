#ifndef LIGHT_H
#define LIGHT_H

class Light {
public:
  virtual ~Light() = default;

  virtual void place() const = 0;
  virtual void enable() const = 0;
  virtual void disable() const = 0;
};

#endif // LIGHT_H
