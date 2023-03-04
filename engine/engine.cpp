#include "engine.h"
#include "camera.h"

Engine::Engine(std::string_view xml_file)
    : xml_file(xml_file), doc(), window_width(800), window_height(800),
      camera(nullptr) {

  this->doc.LoadFile(xml_file.data());

  if (doc.Error()) {
    std::cout << "Error: " << doc.ErrorStr() << '\n';
    return;
  }

  auto world = doc.FirstChildElement("world");
  if (world == nullptr) {
    std::cout << "Error: world element not found" << '\n';
    return;
  }

  auto window = world->FirstChildElement("window");
  if (window == nullptr) {
    std::cout << "Error: window element not found" << '\n';
    return;
  }
  window->QueryUnsignedAttribute("width", &this->window_width);
  window->QueryUnsignedAttribute("height", &this->window_height);

  std::cout << this->window_width << ' ' << this->window_height << '\n';

  auto camera = world->FirstChildElement("camera");

  if (camera == nullptr) {
    std::cout << "Error: camera element not found" << '\n';
    return;
  }

  this->loadCamera(camera);

  auto group = world->FirstChildElement("group");
  if (group == nullptr) {
    std::cout << "Error: group element not found" << '\n';
    return;
  }
  this->group = std::make_unique<Group>(group);
}

void Engine::loadCamera(tinyxml2::XMLElement *camera) {
  camera_engine::Coordinates position;
  camera->QueryUnsignedAttribute("x", &position.x);
  camera->QueryUnsignedAttribute("y", &position.y);
  camera->QueryUnsignedAttribute("z", &position.z);
  std::cout << position.x << ' ' << position.y << ' ' << position.z << '\n';

  auto lookAt = camera->FirstChildElement("lookAt");
  if (lookAt == nullptr) {
    std::cout << "Error: lookAt element not found" << '\n';
    return;
  }
  camera_engine::Coordinates lookAtCoordinates;
  lookAt->QueryUnsignedAttribute("x", &lookAtCoordinates.x);
  lookAt->QueryUnsignedAttribute("y", &lookAtCoordinates.y);
  lookAt->QueryUnsignedAttribute("z", &lookAtCoordinates.z);
  std::cout << lookAtCoordinates.x << ' ' << lookAtCoordinates.y << ' '
            << lookAtCoordinates.z << '\n';

  auto up = camera->FirstChildElement("up");
  if (up == nullptr) {
    std::cout << "Error: up element not found" << '\n';
    return;
  }
  camera_engine::Coordinates upCoordinates;
  up->QueryUnsignedAttribute("x", &upCoordinates.x);
  up->QueryUnsignedAttribute("y", &upCoordinates.y);
  up->QueryUnsignedAttribute("z", &upCoordinates.z);
  std::cout << upCoordinates.x << ' ' << upCoordinates.y << ' '
            << upCoordinates.z << '\n';

  auto projection = camera->FirstChildElement("projection");
  if (projection == nullptr) {
    std::cout << "Error: projection element not found" << '\n';
    return;
  }
  camera_engine::Pov pov;
  projection->QueryUnsignedAttribute("fov", &pov.fov);
  projection->QueryUnsignedAttribute("near", &pov.near);
  projection->QueryUnsignedAttribute("far", &pov.far);
  std::cout << pov.fov << ' ' << pov.near << ' ' << pov.far << '\n';

  this->camera = std::make_unique<camera_engine::Camera>(
      position, lookAtCoordinates, upCoordinates, pov);
}

void Engine::run(int argc, char *argv[]) const {
  engine = (Engine *)this;
  std::cout << "Engine::run()" << '\n';
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(static_cast<int>(this->window_width),
                     static_cast<int>(this->window_height));
  glutCreateWindow("CGEngine");

  glutDisplayFunc(display);

  glutReshapeFunc(reshape);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glutMainLoop();
}

void reshape(int width, int height) {
  if (height == 0)
    height = 1;
  float ratio = (1.0f * static_cast<float>(width)) / static_cast<float>(height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  auto pov_camera = engine->getCamera().getProjection();
  gluPerspective(pov_camera.fov, ratio, pov_camera.near, pov_camera.far);

  glMatrixMode(GL_MODELVIEW);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (engine == nullptr) {
    std::cout << "Error: engine is null" << '\n';
    return;
  }
  auto camera = engine->getCamera();
  auto position = camera.getPosition();
  auto lookAt = camera.getLookAt();
  auto up = camera.getUp();
  glLoadIdentity();
//  gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z,
//            up.x, up.y, up.z);

  gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);
  glVertex3f(-100.0f, 0.0f, 0.0f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);
  glVertex3f(0.0f, -100.0f, 0.0f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);
  glVertex3f(0.0f, 0.0f, -100.0f);
  glEnd();

  engine->draw();
  glutSwapBuffers();
}