#include "engine.h"
#include "camera.h"
#include "parse_errors/xml_parse_error.h"
#include "parsing.h"
#include "tinyxml2.h"

Engine::Engine(std::string_view xml_file)
    : xml_file(xml_file), doc(), window_width(800), window_height(800),
      camera(nullptr) {

  this->doc.LoadFile(xml_file.data());

  for (auto &key : this->keyboard) {
    key = false;
  }

  if (doc.Error())
    throw errors::XMLParseError(doc.ErrorStr());

  auto world = doc.FirstChildElement("world");
  if (world == nullptr)
    throw errors::XMLParseError("Error: world element not found");

  auto window = world->FirstChildElement("window");
  if (window == nullptr)
    throw errors::XMLParseError("Error: window element not found");

  this->window_width = queryUnsignedAttr(window, "width");
  this->window_height = queryUnsignedAttr(window, "height");

  auto camera = world->FirstChildElement("camera");

  if (camera == nullptr)
    throw errors::XMLParseError("Error: camera element not found");

  this->loadCamera(camera);

  auto group = world->FirstChildElement("group");
  while (group != nullptr) {
    this->groups.emplace_back(group);
    group = group->NextSiblingElement("group");
  }

  auto lights = world->FirstChildElement("lights");
  if (lights != nullptr)
    this->loadLights(lights);
}

void Engine::placeLights() const {
  for (const auto &light : this->lights) {
    light->place();
  }
}

void Engine::loadCamera(tinyxml2::XMLElement *camera) {
  maths::Vertex position;
  auto position_xml = camera->FirstChildElement("position");
  if (position_xml == nullptr)
    throw errors::XMLParseError("Error: position element not found");
  position.x = queryFloatAttr(position_xml, "x");
  position.y = queryFloatAttr(position_xml, "y");
  position.z = queryFloatAttr(position_xml, "z");

  auto lookAt = camera->FirstChildElement("lookAt");
  if (lookAt == nullptr) {
    std::cout << "Error: lookAt element not found" << '\n';
    return;
  }
  maths::Vertex lookAtCoordinates;
  lookAtCoordinates.x = queryFloatAttr(lookAt, "x");
  lookAtCoordinates.y = queryFloatAttr(lookAt, "y");
  lookAtCoordinates.z = queryFloatAttr(lookAt, "z");

  auto up = camera->FirstChildElement("up");
  if (up == nullptr) {
    std::cout << "Error: up element not found" << '\n';
    return;
  }
  maths::Vertex upCoordinates;

  upCoordinates.x = queryFloatAttr(up, "x");
  upCoordinates.y = queryFloatAttr(up, "y");
  upCoordinates.z = queryFloatAttr(up, "z");

  auto projection = camera->FirstChildElement("projection");
  if (projection == nullptr) {
    std::cout << "Error: projection element not found" << '\n';
    return;
  }
  camera_engine::Pov pov;

  pov.fov = queryFloatAttr(projection, "fov");
  pov.near = queryFloatAttr(projection, "near");
  pov.far = queryFloatAttr(projection, "far");

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
  glEnable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  this->configureLights();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

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
  glLoadIdentity();
  engine->placeLights();
  engine->placeCamera();

  engine->handleInput();

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

void Engine::loadLights(tinyxml2::XMLElement *lights) {
  auto light = lights->FirstChildElement("light");
  std::uint32_t index = 0;
  for (auto light = lights->FirstChildElement("light"); light != nullptr;
       light = light->NextSiblingElement("light")) {

    std::string_view type = light->Attribute("type");
    if (type == "point")
      this->lights.push_back(std::make_unique<PointLight>(light, index++));
    else if (type == "directional")
      this->lights.push_back(
          std::make_unique<DirectionalLight>(light, index++));
    else if (type == "spotlight")
      this->lights.push_back(std::make_unique<SpotLight>(light, index++));
    else
      throw errors::XMLParseError(
          fmt::format("Error, {} type of light no supported", type));
  }
}

void Engine::configureLights() const noexcept {
  for (const auto &light : this->lights) {
    light->configureColor();
  }
  float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
}
