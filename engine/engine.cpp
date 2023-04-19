#include "engine.h"
#include "camera.h"
#include "utils.h"

Engine::Engine(std::string_view xml_file)
    : xml_file(xml_file), doc(), window_width(800), window_height(800),
      camera(nullptr) {

  this->doc.LoadFile(xml_file.data());

  for (auto &key : this->keyboard) {
    key = false;
  }

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

  auto camera = world->FirstChildElement("camera");

  if (camera == nullptr) {
    std::cout << "Error: camera element not found" << '\n';
    return;
  }

  this->loadCamera(camera);

  auto group = world->FirstChildElement("group");
  while (group != nullptr) {
    this->groups.emplace_back(group);
    group = group->NextSiblingElement("group");
  }

  if (this->groups.empty()) {
    std::cerr << "No group found to draw\n";
    throw std::runtime_error("No group found to draw\n");
  }
}

void Engine::loadCamera(tinyxml2::XMLElement *camera) {
  utils::Vertex position;
  auto position_xml = camera->FirstChildElement("position");
  if (position_xml == nullptr) {
    std::cout << "Error: position element not found" << '\n';
    return;
  }
  position_xml->QueryAttribute("x", &position.x);
  position_xml->QueryAttribute("y", &position.y);
  position_xml->QueryAttribute("z", &position.z);
  auto lookAt = camera->FirstChildElement("lookAt");
  if (lookAt == nullptr) {
    std::cout << "Error: lookAt element not found" << '\n';
    return;
  }
  utils::Vertex lookAtCoordinates;
  lookAt->QueryAttribute("x", &lookAtCoordinates.x);
  lookAt->QueryAttribute("y", &lookAtCoordinates.y);
  lookAt->QueryAttribute("z", &lookAtCoordinates.z);

  auto up = camera->FirstChildElement("up");
  if (up == nullptr) {
    std::cout << "Error: up element not found" << '\n';
    return;
  }
  utils::Vertex upCoordinates;
  up->QueryAttribute("x", &upCoordinates.x);
  up->QueryAttribute("y", &upCoordinates.y);
  up->QueryAttribute("z", &upCoordinates.z);

  auto projection = camera->FirstChildElement("projection");
  if (projection == nullptr) {
    std::cout << "Error: projection element not found" << '\n';
    return;
  }
  camera_engine::Pov pov;
  projection->QueryAttribute("fov", &pov.fov);
  projection->QueryAttribute("near", &pov.near);
  projection->QueryAttribute("far", &pov.far);
  this->camera = std::make_unique<camera_engine::Camera>(
      position, lookAtCoordinates, upCoordinates, pov, this->window_width,
      this->window_height);
}

void Engine::run(int argc, char *argv[]) const {
  engine = (Engine *)this;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(static_cast<int>(this->window_width),
                     static_cast<int>(this->window_height));
  glutCreateWindow("CGEngine");

  glutDisplayFunc(display);
  glutIdleFunc(display);

  glutReshapeFunc(reshape);

  glutKeyboardFunc(processKeyDown);
  glutKeyboardUpFunc(processKeyUp);

  glutMouseFunc(mouseFunc);
  glutMotionFunc(motionFunc);
  glutPassiveMotionFunc(passiveMouseFunc);

  glewInit();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glutMainLoop();
}

void passiveMouseFunc(int x, int y) { engine->handleMouseMotion(x, y); }

void motionFunc(int x, int y) { engine->handleMouseMotion(x, y); }

void mouseFunc(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    std::cout << "Tracking set to 1\n";
    engine->setCameraTracking(1);
    engine->setMousePosition(x, y);
  } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    std::cout << "Tracking set to 0\n";
    engine->setCameraTracking(0);
  }
}

void reshape(int width, int height) {
  if (height == 0)
    height = 1;
  float ratio = (1.0f * static_cast<float>(width)) / static_cast<float>(height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  engine->setCameraPerspective(ratio);
  glMatrixMode(GL_MODELVIEW);
}

void display() {

  int elapsedTime = glutGet(GLUT_ELAPSED_TIME);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (engine == nullptr) {
    std::cout << "Error: engine is null" << '\n';
    return;
  }
  engine->placeCamera();

  engine->handleInput();

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

  engine->draw(elapsedTime);
  glutSwapBuffers();
}

void processKeyDown(unsigned char key, int x, int y) {
  if (engine == nullptr) {
    std::cout << "Engine is null\n";
    return;
  }

  std::cout << "Pressed key: " << key << '\n';

  engine->registerKey(key);
}

void Engine::handleInput() { this->camera->handleInput(this->keyboard); }

void processKeyUp(unsigned char key, int x, int y) {
  if (engine == nullptr) {
    std::cout << "Engine is null\n";
    return;
  }

  std::cout << "Released key: " << key << '\n';

  engine->unregisterKey(key);
}

void Engine::registerKey(unsigned char key) {
  if (static_cast<int>(key) > std::numeric_limits<unsigned char>::max())
    throw std::invalid_argument("keycode not valid");

  this->keyboard[key] = true;
}

void Engine::unregisterKey(unsigned char key) {
  if (static_cast<int>(key) > std::numeric_limits<unsigned char>::max())
    throw std::invalid_argument("keycode not valid");
  this->keyboard[key] = false;
}
