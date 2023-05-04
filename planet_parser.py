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
    a = 44.691666667
    points = list()
    step = (2 * pi) / slices

    b = a * sqrt(1 - pow(excentricidade, 2))

    for i in range(slices):
        angle = step * i
        distance = (a * b) / sqrt(pow(b * cos(angle), 2) + pow(a * sin(angle), 2))
        x = distance * cos(angle)
        z = distance * sin(angle)
        points.append((x, 0, z))

    return points

def get_point(root: minidom.Document, point_coords: tuple[float, float, float]) -> minidom.Element:
    point = root.createElement("point")
    point.setAttribute("x", str(point_coords[0]))
    point.setAttribute("y", str(point_coords[1]))
    point.setAttribute("z", str(point_coords[2]))
    return point


def generate_asteroids(root: minidom.Document, number_asteroids: int) -> minidom.Element:
    ast_group = root.createElement("group")

    for _ in range(number_asteroids):
        group = root.createElement("group")
        models = root.createElement("models")

        transform = root.createElement("transform")
        translate = root.createElement("translate")
        scale = root.createElement("scale")
        scale_factor = str(random.uniform(0.001, 0.01))
        scale.setAttribute("x", scale_factor)
        scale.setAttribute("y", scale_factor)
        scale.setAttribute("z", scale_factor)
        translate.setAttribute("align", "False")
        orbita = (random.uniform(3.5, 6) * 365) / 40
        translate.setAttribute("time", str(orbita))

        for point in get_curve_points(100, random.uniform(8, 10) + 3):
            translate.appendChild(get_point(root, point))

        transform.appendChild(translate)
        transform.appendChild(scale)

        model = root.createElement("model")
        model.setAttribute("file", "solar_system_elements/spherelowquality.3d")
        models.appendChild(model)
        group.appendChild(transform)
        group.appendChild(models)

        ast_group.appendChild(group)

    return ast_group

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

def create_color_element(root: minidom.Document, color_hex: str, sun = False) -> minidom.Element:
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

    specular.setAttribute("R", "0")
    specular.setAttribute("G", "0")
    specular.setAttribute("B", "0")

    emissive = root.createElement("emissive")

    emissive.setAttribute("R", str(r) if sun else "0")
    emissive.setAttribute("G", str(g) if sun else "0")
    emissive.setAttribute("B", str(b) if sun else "0")

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

    model.appendChild(create_color_element(root=root, color_hex="#FDB813", sun=True))

    models.appendChild(model)
    group.appendChild(models)
    parent.appendChild(group)

def create_comet(root: minidom.Document) -> minidom.Element:
    group = root.createElement("group")
    models = root.createElement("models")
    model = root.createElement("model")
    model.setAttribute("file", "solar_system_elements/teapot.3d")

    transform = root.createElement("transform")
    translate = root.createElement("translate")
    translate.setAttribute("align", "True")
    translate.setAttribute("time", "91.615")
    
    points = get_comet_curve_points(1000)
    for point in points:
        point_xml = root.createElement("point")
        point_xml.setAttribute("x", str(point[0]))
        point_xml.setAttribute("y", str(point[1]))
        point_xml.setAttribute("z", str(point[2]))
        translate.appendChild(point_xml)

    scale = root.createElement("scale")
    scale.setAttribute("x", "0.1")
    scale.setAttribute("y", "0.1")
    scale.setAttribute("z", "0.1")

    rotate = root.createElement("rotate")
    rotate.setAttribute("angle", "-162.3")
    rotate.setAttribute("x", "1")
    rotate.setAttribute("y", "0")
    rotate.setAttribute("z", "0")
    transform.appendChild(rotate)
    transform.appendChild(translate)

    rotate = root.createElement("rotate")
    rotate.setAttribute("angle", "90.0")
    rotate.setAttribute("x", "1")
    rotate.setAttribute("y", "0")
    rotate.setAttribute("z", "0")
    transform.appendChild(rotate)

    transform.appendChild(scale)
    group.appendChild(transform)
    model.appendChild(create_color_element(root, "#FF8337"))
    models.appendChild(model)
    group.appendChild(models)
    return group

def create_planets(root: minidom.Document, parent: minidom.Element, planets, satellites):
    BASE_DISTANCE = 3
    SIZE_FACTOR = 60000
    parent.appendChild(create_comet(root))
    for planet in planets:
        group = root.createElement("group")        
        models = root.createElement("models")
        group.appendChild(models)
        parent.appendChild(group)
        model = root.createElement("model")

        orbit = str(float(planet["orbit time (days)"]) / 20)

        rotation = root.createElement("rotate")
        rotation.setAttribute("angle", str(random.uniform(0, 360)))
        rotation.setAttribute("x", "0")
        rotation.setAttribute("y", "1")
        rotation.setAttribute("z", "0")

        transform = root.createElement("transform")
        radius = float(planet["radius"]) / SIZE_FACTOR
        translate = root.createElement("translate")
        translate.setAttribute("time", orbit)
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
        transform.appendChild(rotation)
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
                translate_sat.setAttribute("time", str(float(orbit) / 2))

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

                model.setAttribute("file", "solar_system_elements/spherelowquality.3d")
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
    run(args=["./build/bin/generator", "sphere", "1", "10", "10", "solar_system_elements/spherelowquality.3d"], text=True)
    run(args=["./build/bin/generator", "bezzier", "patches/teapot.patch", "10", "solar_system_elements/teapot.3d"], text=True)


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

    world.appendChild(generate_asteroids(root, 100))
    world.appendChild(create_light(root))

    with open("scenes/solar_system.xml", "w") as file:
        file.write(root.toprettyxml(indent='\t'))


if __name__ == "__main__":
    main()
