from PIL import Image
import sys

def get_pixels():
    i = Image.open(sys.argv[1])    
    pixels = i.load() # this is not a list, nor is it list()'able
    width, height = i.size
    all_pixels = []
    for x in range(width):
        for y in range(height):
            cpixel = pixels[x, y]
            all_pixels.append(cpixel)
    return all_pixels    


def main():
    lol = []
    for r,g,b in get_pixels():
        if (chr(r).isalpha() and chr(g).isalpha() and chr(b).isalpha()):
            lol.append(chr(r))
            lol.append(chr(g))
            lol.append(chr(b))
    print "".join(lol)

if __name__ == "__main__":
    main()
