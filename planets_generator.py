from abc import abstractmethod
from xml.dom import minidom
from subprocess import run

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


class Dom():
    @abstractmethod
    def get_dom_element(self, root_xml: minidom.Document) -> minidom.Element:
        pass

class SolarSystemElement(Dom):
    def __init__(self, name: str, scale = 1.0, distance = 0.0):
        self.name = name
        self.scale = scale
        self.distance = distance
        self.stars: list["SolarSystemElement"] = []
        self.file_name = f"{self.name}.3d"

    def add_star(self, star: "SolarSystemElement"):
        self.stars.append(star)

    def generate_coords_file(self):
        for star in self.stars:
            star.generate_coords_file()
        run(args=["cmake-build-debug/generator/generator", "sphere", "1", "10", "10", "solar_system_elements/" + self.file_name], text=True)

    def get_dom_element(self, root_xml: minidom.Document) -> minidom.Element:
        group = root_xml.createElement("group")
        models = root_xml.createElement("models")
        model = root_xml.createElement("model")
        model.setAttribute(attname="file", value="solar_system_elements/" + self.file_name)

        transforms: minidom.Element | None = None

        if self.scale != 1:
            if not transforms:
                transforms = root_xml.createElement("transform")
            scale = root_xml.createElement("scale")
            scale.setAttribute("x", str(self.scale))
            scale.setAttribute("y", str(self.scale))
            scale.setAttribute("z", str(self.scale))
            transforms.appendChild(scale)

        if self.distance != 0:
            if not transforms:
                transforms = root_xml.createElement("transform")
            translate = root_xml.createElement("translate")
            translate.setAttribute("x", str(self.distance))
            translate.setAttribute("y", "0")
            translate.setAttribute("z", "0")
            transforms.appendChild(translate)

        if transforms:
            group.appendChild(transforms)

        group.appendChild(models)
        models.appendChild(model)

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
        self.elements: list[SolarSystemElement] = []
        self.init_elements()

    def init_elements(self):
        #PLANETS = ["Mercury", "Venus", "Earth", "Mars", "Jupiter, Saturn", "Uranus", "Neptune"]
        self.elements.append(SolarSystemElement(scale=3, name="sun"))
        self.elements.append(SolarSystemElement(scale=0.0108303249, distance=5, name="mercury"))
        self.elements.append(SolarSystemElement(scale=1, distance=8, name="venus"))
        self.elements.append(SolarSystemElement(scale=1, distance=10, name="earth"))
        self.elements.append(SolarSystemElement(scale=1, distance=15, name="mars"))
        self.elements.append(SolarSystemElement(scale=1, distance=20, name="jupiter"))
        self.elements.append(SolarSystemElement(scale=1, distance=30, name="saturn"))
        self.elements.append(SolarSystemElement(scale=1, distance=40, name="uranus"))
        self.elements.append(SolarSystemElement(scale=1, distance=50, name="neptune"))

    def get_xml(self) -> str:
        for element in self.elements:
            element.generate_coords_file()
            group_element = element.get_dom_element(self.root)
            self.world.appendChild(group_element)

        return self.root.toprettyxml(indent='\t')

def main():
    root = SolarSystem()
    xml_str = root.get_xml()

    with open("solar_system.xml", "w") as file:
        file.write(xml_str)

if __name__ == "__main__":
    main()
