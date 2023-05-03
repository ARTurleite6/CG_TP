import csv
from math import pi, sin, cos, pow, sqrt
import random
from subprocess import run
from xml.dom import minidom

def to_rgb(hex: str) -> tuple[int, int, int]:
    hex = hex.lstrip("#")
    return tuple(int(hex[i:i+2], 16) for i in (0, 2, 4))

def get_comet_curve_points(slices: int) -> list[tuple[float, float, float]]:
    excentricidade = 0.967
    semi_eixo_maior = 45.96
    perielio = 1.51311397438
    afelio = 90.6319121175
    points = list()
    step = (2 * pi) / slices

    b = sqrt(1 - pow(excentricidade, 2))

    for i in range(slices):
        angle = step * i
        r = semi_eixo_maior * (1 - pow(excentricidade, 2)) / (1 + excentricidade * cos(angle))
        x = r * sin(angle)
        z = r * cos(angle)

    return points

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

def create_light(root: minidom.Document) -> minidom.Element:
    lights = root.createElement("lights")
    light = root.createElement("light")
    light.setAttribute("type", "point")
    light.setAttribute("posX", "0")
    light.setAttribute("posY", "0")
    light.setAttribute("posZ", "0")
    lights.appendChild(light)
    return lights

def create_color_element(root: minidom.Document, color_hex: str) -> minidom.Element:
    color = root.createElement("color")
    diffuse = root.createElement("diffuse")
    
    (r, g, b) = to_rgb(color_hex)

    diffuse.setAttribute("R", str(r))
    diffuse.setAttribute("G", str(g))
    diffuse.setAttribute("B", str(b))

    ambient = root.createElement("ambient")

    ambient.setAttribute("R", str(r))
    ambient.setAttribute("G", str(g))
    ambient.setAttribute("B", str(b))

    specular = root.createElement("specular")

    specular.setAttribute("R", str(r))
    specular.setAttribute("G", str(g))
    specular.setAttribute("B", str(b))

    emissive = root.createElement("emissive")

    emissive.setAttribute("R", str(r))
    emissive.setAttribute("G", str(g))
    emissive.setAttribute("B", str(b))

    shininess = root.createElement("shininess")
    shininess.setAttribute("value", "128")

    color.appendChild(diffuse)
    color.appendChild(ambient)
    color.appendChild(specular)
    color.appendChild(emissive)
    color.appendChild(shininess)

    return color

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

    model.appendChild(create_color_element(root, "#FDB813"))

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
        radius = float(planet["radius"]) / SIZE_FACTOR
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
        scale.setAttribute("x", str(radius))
        scale.setAttribute("y", str(radius))
        scale.setAttribute("z", str(radius))
        transform.appendChild(translate)
        transform.appendChild(scale)


        group.appendChild(transform)

        model.setAttribute("file", "solar_system_elements/sphere.3d")

        if planet["planet"] in satellites:
            for satellite in satellites[planet["planet"]]:
                sat_group = root.createElement("group")
                model = root.createElement("model")

                transform_sat = root.createElement("transform")
                distance_sat = random.uniform(1.5 * radius, 2.5 * radius) / radius
                translate_sat = root.createElement("translate")
                translate_sat.setAttribute("align", "False")
                translate_sat.setAttribute("time", "20")

                points = get_curve_points(slices=10, distance=distance_sat)
                for point in points:
                    point_xml = root.createElement("point")
                    point_xml.setAttribute("x", str(point[0]))
                    point_xml.setAttribute("y", str(point[1]))
                    point_xml.setAttribute("z", str(point[2]))
                    translate_sat.appendChild(point_xml)

                rotation_sat = root.createElement("rotate")
                angle = random.uniform(0, 360)
                rotation_sat.setAttribute("angle", str(angle))
                rotation_sat.setAttribute("x", "1")
                rotation_sat.setAttribute("y", "0")
                rotation_sat.setAttribute("z", "0")

                transform_sat.appendChild(rotation_sat)
                transform_sat.appendChild(translate_sat)
                scale_sat = root.createElement("scale")
                radius_sat = float(satellite["radius"]) / radius
                scale_sat.setAttribute("x", str(radius_sat))
                scale_sat.setAttribute("y", str(radius_sat))
                scale_sat.setAttribute("z", str(radius_sat))
                transform_sat.appendChild(scale_sat)

                model.setAttribute("file", "solar_system_elements/sphere.3d")
                model.appendChild(create_color_element(root, planet["color"]))

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
    run(args=["./build/bin/generator", "bezzier", "patches/teapot.patch", "10", "solar_system_elements/sphere.3d"], text=True)


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

    world.appendChild(create_light(root))

    with open("scenes/solar_system.xml", "w") as file:
        file.write(root.toprettyxml(indent='\t'))


if __name__ == "__main__":
    main()
