from abc import abstractmethod
from xml.dom import minidom
from subprocess import run
from math import pi
from random import randint

"""
<world>
    <window width="512" height="512" />
    <camera>
        <position x="5" y="5" z="5" />
        <lookAt x="0" y="0" z="0" />
        <up x="0" y="1" z="0" />
        <projection fov="60" near="1" far="1000" />
    </camera>
</world>
"""

BASE_DISTANCE = 3

class Dom():
    @abstractmethod
    def get_dom_element(self, root_xml: minidom.Document, angle_rotation = 0) -> minidom.Element:
        pass

class Ring(Dom):
    def __init__(self, raio_interno, raio_externo, name):
        self.raio_interno = raio_interno
        self.raio_externo = raio_externo
        self.file_name = name

    def get_dom_element(self, root_xml: minidom.Document, _ = 0) -> minidom.Element:
        group = root_xml.createElement("group")
        models = root_xml.createElement("models")
        model = root_xml.createElement("model")
        model.setAttribute(attname="file", value="solar_system_elements/" + self.file_name + ".3d")
        models.appendChild(model)
        group.appendChild(models)
        return group

    def generate_coords_file(self):
        run(args=["./build/bin/generator", "torus", str(self.raio_interno), str(self.raio_externo), "100", "2", "solar_system_elements/" + self.file_name + ".3d"], text=True)

class SolarSystemElement(Dom):
    def __init__(self, name: str, ring: Ring | None = None, scale = 1.0, distance = 0.0):
        self.name = name
        self.scale = scale
        self.distance = distance
        self.stars = []
        self.file_name = f"{self.name}.3d"
        self.ring = ring

    def add_star(self, star: "SolarSystemElement"):
        self.stars.append(star)

    def generate_coords_file(self):
        if self.ring:
            self.ring.generate_coords_file()
        for star in self.stars:
            star.generate_coords_file()
        run(args=["./build/bin/generator", "sphere", "1", "100", "100", "solar_system_elements/" + self.file_name], text=True)

    def get_dom_element(self, root_xml: minidom.Document, angle_rotation = 0) -> minidom.Element:
            group = root_xml.createElement("group")
            models = root_xml.createElement("models")
            model = root_xml.createElement("model")
            model.setAttribute(attname="file", value="solar_system_elements/" + self.file_name)

            transforms: minidom.Element | None = None

            if not transforms:
                transforms = root_xml.createElement("transform")
            rotate = root_xml.createElement("rotate")
            rotate.setAttribute("angle", str(randint(0, 360)))
            rotate.setAttribute("x", "0")
            rotate.setAttribute("y", "1")
            rotate.setAttribute("z", "0")
            transforms.appendChild(rotate)


            if self.distance != 0:
                if not transforms:
                    transforms = root_xml.createElement("transform")
                translate = root_xml.createElement("translate")
                translate.setAttribute("x", str(self.distance))
                translate.setAttribute("y", "0")
                translate.setAttribute("z", "0")
                transforms.appendChild(translate)

            if self.scale != 1:
                if not transforms:
                    transforms = root_xml.createElement("transform")
                scale = root_xml.createElement("scale")
                scale.setAttribute("x", str(self.scale))
                scale.setAttribute("y", str(self.scale))
                scale.setAttribute("z", str(self.scale))
                transforms.appendChild(scale)


            if transforms:
                group.appendChild(transforms)

            group.appendChild(models)
            models.appendChild(model)

            if self.ring:
                group.appendChild(self.ring.get_dom_element(root_xml))

            for moon in self.stars:
                group_moon = moon.get_dom_element(root_xml)
                group.appendChild(group_moon)

            return group


class Camera(Dom):
    def __init__(self, position = (5, 5, 5), 
                 lookAt = (0, 0, 0), 
                 up = (0, 1, 0), 
                 projection = (60, 1, 1000)):
                 self.position = position
                 self.lookAt = lookAt
                 self.up = up
                 self.projection = projection

    def get_dom_element(self, root_xml: minidom.Document) -> minidom.Element:
        camera_dom = root_xml.createElement("camera")
        position = root_xml.createElement("position") 
        position.setAttribute(attname="x", value=str(self.position[0]))
        position.setAttribute(attname="y", value=str(self.position[1]))
        position.setAttribute(attname="z", value=str(self.position[2]))
        camera_dom.appendChild(position)
        lookAt = root_xml.createElement("lookAt") 
        lookAt.setAttribute(attname="x", value=str(self.lookAt[0]))
        lookAt.setAttribute(attname="y", value=str(self.lookAt[1]))
        lookAt.setAttribute(attname="z", value=str(self.lookAt[2]))
        camera_dom.appendChild(lookAt)
        up = root_xml.createElement("up") 
        up.setAttribute(attname="x", value=str(self.up[0]))
        up.setAttribute(attname="y", value=str(self.up[1]))
        up.setAttribute(attname="z", value=str(self.up[2]))
        camera_dom.appendChild(up)
        projection = root_xml.createElement("projection") 
        projection.setAttribute(attname="fov", value=str(self.projection[0]))
        projection.setAttribute(attname="near", value=str(self.projection[1]))
        projection.setAttribute(attname="far", value=str(self.projection[2]))
        camera_dom.appendChild(projection)

        return camera_dom

class Window(Dom):
    def __init__(self, width = 800, height = 600):
        self.width = width
        self.height = height

    def get_dom_element(self, root_xml: minidom.Document) -> minidom.Element:
        window = root_xml.createElement("window")
        window.setAttribute(attname="width", value=str(self.width))
        window.setAttribute(attname="height", value=str(self.height))

        return window

class SolarSystem():
    def __init__(self):
        self.root = minidom.Document()
        self.world = self.root.createElement("world")
        self.window = Window()
        self.world.appendChild(self.window.get_dom_element(self.root))
        self.camera = Camera()
        self.world.appendChild(self.camera.get_dom_element(self.root))
        self.root.appendChild(self.world)
        self.elements = []
        self.init_elements()

        self.current_angle = 0

    def init_elements(self):
        #PLANETS = ["Mercury", "Venus", "Earth", "Mars", "Jupiter, Saturn", "Uranus", "Neptune"]
        SUN_SCALE = 3
        sun = SolarSystemElement(scale=SUN_SCALE, name="sphere")
        mercury = SolarSystemElement(scale=0.04332129963, distance=BASE_DISTANCE + 1, name="sphere")
        venus = SolarSystemElement(scale=0.10434782608, distance=BASE_DISTANCE + 2, name="sphere")
        earth = SolarSystemElement(scale=0.11009174311, distance=BASE_DISTANCE + 2.5, name="sphere")
        earth.add_star(SolarSystemElement(scale=0.25, distance=9.8, name="sphere"))
        mars = SolarSystemElement(scale=0.05797101449, distance=4 + BASE_DISTANCE, name="sphere")
        mars.add_star(SolarSystemElement(scale=0.00308641975, distance=5.5176617942886566, name="sphere"))
        mars.add_star(SolarSystemElement(scale=0.00189933523, distance=7.8335344536757265, name="sphere"))
        jupiter = SolarSystemElement(scale=1.09090909091, distance=BASE_DISTANCE + 13, name="sphere")
        jupiter.add_star(SolarSystemElement(scale=0.026055985467236916, distance=7.398371343153356, name="sphere"))
        jupiter.add_star(SolarSystemElement(scale=0.02232552817153238, distance=8.263971011265888, name="sphere"))
        jupiter.add_star(SolarSystemElement(scale=0.037636423452675545, distance=7.4420035672774105, name="sphere"))
        jupiter.add_star(SolarSystemElement(scale=0.03447669179385219, distance=8.734574273614136, name="sphere"))
        saturn = SolarSystemElement(scale=1, distance=BASE_DISTANCE + 24, name="sphere", 
                                    ring=Ring(raio_interno=3, raio_externo=0.75, name="ring-saturn"))
        uranus = SolarSystemElement(scale=0.43795620438, distance=49 + BASE_DISTANCE, name="sphere", 
                                    ring=Ring(raio_interno=3, raio_externo=0.25, name="ring-uranus"))
        neptune = SolarSystemElement(scale=0.43321299639, distance=BASE_DISTANCE + 76, name="sphere")
        neptune.add_star(SolarSystemElement(scale=0.054877949882410196, distance=8.387304877916142, name="sphere"))
        neptune.add_star(SolarSystemElement(scale=0.006893196010055958, distance=8.44113655252599, name="sphere"))

        asth_ring = Ring(raio_interno=20.4, raio_externo=4, name="asteroides-anel")

        self.elements.append(sun)
        self.elements.append(mercury)
        self.elements.append(venus)
        self.elements.append(earth)
        self.elements.append(mars)
        self.elements.append(jupiter)
        self.elements.append(saturn)
        self.elements.append(uranus)
        self.elements.append(neptune)
        self.elements.append(asth_ring)

    def get_xml(self) -> str:
        for element in self.elements:
            element.generate_coords_file()
            group_element = element.get_dom_element(self.root, self.current_angle)
            self.world.appendChild(group_element)
            self.current_angle += 15
            if self.current_angle > 360:
                self.current_angle = 0

        return self.root.toprettyxml(indent='\t')

def main():
    root = SolarSystem()
    xml_str = root.get_xml()

    with open("scenes/solar_system.xml", "w") as file:
        file.write(xml_str)

if __name__ == "__main__":
    main()
