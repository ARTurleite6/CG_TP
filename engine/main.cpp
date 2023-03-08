#include "engine.h"
#include <GLUT/glut.h>

void changeSize(int w, int h) {
  if (h == 0)
    h = 1;
  float ratio = 1.0f * (static_cast<float>(w) / static_cast<float>(h));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  Engine engine(argv[1]);

  --argc;
  ++argv;

  engine.run(argc, argv);

  return 0;
}
