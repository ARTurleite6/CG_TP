import csv
from subprocess import run

def download_texture(url, destination):
    print("Downloading texture...")
    run(["wget", "-c", url, "-O", destination])

def download_all_textures(planets):
    for name in planets:
        destination = f"textures/{name}.jpg"
        match name:
            case "Venus":
                download_texture("https://www.solarsystemscope.com/textures/download/8k_venus_surface.jpg", destination)
            case "Earth":
                download_texture("https://www.solarsystemscope.com/textures/download/8k_earth_daymap.jpg", destination)
            case "Uranus":
                download_texture("https://www.solarsystemscope.com/textures/download/2k_uranus.jpg", destination)
            case "Neptune":
                download_texture("https://www.solarsystemscope.com/textures/download/2k_neptune.jpg", destination)
            case _:
                url = f"https://www.solarsystemscope.com/textures/download/8k_{name.lower()}.jpg"
                download_texture(url, destination)
    download_texture("https://www.solarsystemscope.com/textures/download/8k_sun.jpg", "textures/Sun.jpg")

def main():

    names_planets = list()
    with open("data/planets.csv") as file_planets:
        planets = csv.DictReader(file_planets)
        names_planets = list(map(lambda planet: planet["planet"], planets))

    download_all_textures(names_planets)

if __name__ == "__main__":
    main()
