import csv
from math import pi, sin, cos
import random
from subprocess import run
from sys import argv
from xml.dom import minidom

def get_curve_points(slices: int, distance: float) -> list[tuple[float, float, float]]:
    angle = (2 * pi) / slices
    points = list()
    for i in range(slices):
        current_angle = i * angle
        point = (distance * sin(current_angle), 0, distance * cos(current_angle))
        points.append(point)

    return points


def create_camera(root: minidom.Document, parent_xml: minidom.Element | None = None):
    camera = root.createElement("camera")

    position = root.createElement("position")
    position.setAttribute("x", "5")
    position.setAttribute("y", "5")
    position.setAttribute("z", "5")

    lookAt = root.createElement("lookAt")
    lookAt.setAttribute("x", "0")
    lookAt.setAttribute("y", "0")
    lookAt.setAttribute("z", "0")

    up = root.createElement("up")
    up.setAttribute("x", "0")
    up.setAttribute("y", "1")
    up.setAttribute("z", "0")

    projection = root.createElement("projection")
    projection.setAttribute("fov", "60")
    projection.setAttribute("near", "1")
    projection.setAttribute("far", "1000")

    camera.appendChild(position)
    camera.appendChild(lookAt)
    camera.appendChild(up)
    camera.appendChild(projection)

    if parent_xml:
        parent_xml.appendChild(camera)
    else:
        root.appendChild(camera)

def create_window(root: minidom.Document, parent: minidom.Element | None):
    window = root.createElement("window")
    window.setAttribute("width", "800")
    window.setAttribute("height", "600")
    if parent:
        parent.appendChild(window)
    else:
        root.appendChild(window)

def create_sun(root: minidom.Document, parent: minidom.Element):
    group = root.createElement("group")
    models = root.createElement("models")

    transform = root.createElement("transform")
    scale = root.createElement("scale")
    scale.setAttribute("x", "3")
    scale.setAttribute("y", "3")
    scale.setAttribute("z", "3")
    transform.appendChild(scale)

    group.appendChild(transform)
    model = root.createElement("model")
    model.setAttribute("file", "solar_system_elements/sphere.3d")

    models.appendChild(model)
    group.appendChild(models)
    parent.appendChild(group)

def create_planets(root: minidom.Document, parent: minidom.Element, planets, satellites):
    BASE_DISTANCE = 3
    SIZE_FACTOR = 60000
    for planet in planets:
        group = root.createElement("group")        
        models = root.createElement("models")
        group.appendChild(models)
        parent.appendChild(group)
        model = root.createElement("model")

        transform = root.createElement("transform")
        radius = float(planet["radius"])
        translate = root.createElement("translate")
        translate.setAttribute("time", "20")
        translate.setAttribute("align", "False")
        distance = float(planet["relative distance"])
        points = get_curve_points(slices=int(10), distance=distance + BASE_DISTANCE)
        for point in points:
            point_xml = root.createElement("point")
            point_xml.setAttribute("x", str(point[0]))
            point_xml.setAttribute("y", str(point[1]))
            point_xml.setAttribute("z", str(point[2]))
            translate.appendChild(point_xml)
        scale = root.createElement("scale")
        scale.setAttribute("x", str(radius / SIZE_FACTOR))
        scale.setAttribute("y", str(radius / SIZE_FACTOR))
        scale.setAttribute("z", str(radius / SIZE_FACTOR))
        transform.appendChild(translate)
        transform.appendChild(scale)
        group.appendChild(transform)

        model.setAttribute("file", "solar_system_elements/sphere.3d")
        print(satellites)
        print(planet["planet"])

        if planet["planet"] in satellites:
            for satellite in satellites[planet["planet"]]:
                sat_group = root.createElement("group")
                model = root.createElement("model")

                transform_sat = root.createElement("transform")
                distance_sat = random.uniform(1.5 * radius / SIZE_FACTOR, 2.5 * radius / SIZE_FACTOR) / (radius / SIZE_FACTOR)
                translate_sat = root.createElement("translate")
                translate_sat.setAttribute("align", "False")
                translate_sat.setAttribute("time", "20")

                points = get_curve_points(slices=int(10), distance=distance_sat)
                for point in points:
                    point_xml = root.createElement("point")
                    point_xml.setAttribute("x", str(point[0]))
                    point_xml.setAttribute("y", str(point[1]))
                    point_xml.setAttribute("z", str(point[2]))
                    translate_sat.appendChild(point_xml)

                transform_sat.appendChild(translate_sat)
                scale_sat = root.createElement("scale")
                radius_sat = float(satellite["radius"]) / (radius / SIZE_FACTOR)
                scale_sat.setAttribute("x", str(radius_sat))
                scale_sat.setAttribute("y", str(radius_sat))
                scale_sat.setAttribute("z", str(radius_sat))
                transform_sat.appendChild(scale_sat)

                model.setAttribute("file", "solar_system_elements/sphere.3d")

                sat_group.appendChild(transform_sat)
                sat_group.appendChild(model)
                group.appendChild(sat_group)

        models.appendChild(model)

def main():

    root = minidom.Document()
    world = root.createElement("world")
    root.appendChild(world)
    create_window(root, world)
    create_camera(root, world)
    create_sun(root, world)

    run(args=["./build/bin/generator", "torus", "3", "0.75", "100", "2", "solar_system_elements/torus.3d"], text=True)
    run(args=["./build/bin/generator", "sphere", "1", "100", "100", "solar_system_elements/sphere.3d"], text=True)


    with open("data/planets.csv", "r") as file:
        with(open("data/satellites.csv", "r")) as file2:
            planets_satellites = dict()
            planets = csv.DictReader(file)
            satellites = csv.DictReader(file2)
            for satellit in satellites:
                if satellit["planet"] not in planets_satellites:
                    planets_satellites[satellit["planet"]] = list()
                planets_satellites[satellit["planet"]].append(satellit)
                
            create_planets(root, world, planets, planets_satellites)

    with open("scenes/solar_system.xml", "w") as file:
        file.write(root.toprettyxml(indent='\t'))


if __name__ == "__main__":
    main()
