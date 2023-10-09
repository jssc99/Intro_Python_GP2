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
    t : Entity = scene.GetEntities(1)
    print(t.GetID())

