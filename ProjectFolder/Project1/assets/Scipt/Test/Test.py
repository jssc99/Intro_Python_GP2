
import sys
sys.path.append('C:/Projet/ModernOpenglGB/source/include/Core/Python')
import CorePython
print("PYTHONNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN")

import importlib.util
spam_spec = importlib.util.find_spec("CorePython")

cam = CorePython.Camera()
print(cam)

def CallString2() : 
   print("dsadsadsadsadd")


class CamerMovement(object) : 


    def Init(self, scene ):
        return
    
    def Awake(self, scene):
        return
    def Start(self, scene):
        return

    def OnDrawGizmo(self, scene):
        return
    
    def FixedUpdate(self, scene):
        return

    def Update(self, scene ):
        print("PYTHONNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN")

    def LateUpdate(self, scene):
        return 

    def Render(self, shader, scene):
        return 

    def OnResizeData(self, ComponentTypeID, data):
        return 
    

    
    