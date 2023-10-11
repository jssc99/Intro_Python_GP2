# Code exemple pour affichage d une image
import math
from math import *
import cmath
from cmath import *
from PIL import Image,ImageDraw

# image size
# attention: l origine du referentiel image se situe en haut a gauche de l image,
# et l axe des ordonnees positivement oriente vers le bas
imgx = 1000
imgy = 1000

#image declaration
image = Image.new("RGB", (imgx, imgy))
draw = ImageDraw.Draw(image)

#drawing instructions
#draw.rectangle((0, 0, imgx, imgy), fill='white')
#draw.line((0, 0, imgx/2, imgy/2),fill='black',width=4)
#draw.ellipse((1,1,999,999), outline ='blue')




def DrawCross(draw : ImageDraw, center : complex, radius : float, nBranches : int, angleoffset, color : str, w) :
    draw.rectangle((0, 0, imgx, imgy), fill='white')
    if (nBranches < 1) : 
        print("invalid nb of branches")
        return 0
    angle = (2 * pi / nBranches) 
    for i in range(nBranches) :
        c = cos(angle * i + radians(angleoffset)).real
        s = sin(angle * i + radians(angleoffset)).real
        p = (radius * (c - s) + center.real), (radius * (c + s) + center.imag)
        draw.line((center.real, center.imag, p[0], p[1]), fill=color, width=w)
    
#DrawCross(draw, complex(imgx / 2.0, imgy / 2.0), 100*pi, 15, 45, 'black', 3)

def DrawRegularPolygon(draw : ImageDraw, center : complex, radius : float, nBranches : int, angleoffset, color : str, w) :
    draw.rectangle((0, 0, imgx, imgy), fill='white')
    if (nBranches < 3) : 
        print("invalid nb of branches")
        return 0
    angle = (2 * pi / nBranches)
    for i in range(nBranches + 1) :
        z = cmath.rect(radius, angle * i + radians(angleoffset))
        p = z + center
        if (i > 0) :
            draw.line((pprevious.real, pprevious.imag, p.real, p.imag), fill=color, width=w)
        pprevious = p
    
DrawRegularPolygon(draw, complex(imgx / 2.0, imgy / 2.0), 100*pi, 15, 45, 'black', 5)





#showing image
image = image.transpose(Image.FLIP_TOP_BOTTOM) # pour afficher l image
# verticalement retournee, et ainsi obtenir l origine du referentiel en bas a gauche
image.show()