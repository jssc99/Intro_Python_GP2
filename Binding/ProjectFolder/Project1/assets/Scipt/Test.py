import sys
##sys.path.append('C:/Projet/ModernOpenglGB/source/include/Core/Python')
import CorePython
##from CorePython import*

from CorePython import*

def Init(scene : Scene):
    return
    
def Awake(scene: Scene):
    return
  
def FixedUpdate(scene: Scene):
    return

def Update(scene : Scene ) :
    print("This prinet is from Test.py in sript folder from project folder")
    print("Change here Than Press F5 TO Reload")
    print("print vector2")
    v = Vector2(10,67)
    print("x = " + v.x.__str__() + " y = " +  v.y.__str__())

    return


def UpdateCam(camera : Camera) :
    return
