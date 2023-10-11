
import AppData 
from enum import Enum
import random

class EnumTeam(Enum) :
    NONE = 0 
    PLAYER = 1
    ENEMY = 2 


class Entity(object):

    _Health : int  = 0 
    _Armor : int  = 0
    _damage : int = 0 
    _name = "Entity"
    _turnIndex : int = -1
    _Team : EnumTeam = EnumTeam.NONE


    def __init__(self):
        self._Team = EnumTeam.NONE
        


    def GetMaxTurnTurn(entityList) :
        turn_indices = [entity._turnIndex for entity in entityList]
        return max(turn_indices) 

    def GetTurn(self) : 
        return self._turnIndex

    @property
    def Health(self):
        return self._Health
    @Health.setter
    def Health(self, value):
        self._Health = value

    @property
    def Armor(self):
        return self._Armor
    @Armor.setter
    def Armor(self, value):
        self._Armor = value
 
    @property
    def Damage(self):
        return self._damage
    @Damage.setter
    def Damage(self, value):
        self._damage = value


    
    def OnSpecial(self,data : AppData.AppData)->bool :
        pass


    def OnAttack(self, data : AppData.AppData)->bool :
        pass
    

    def OnRollDice(self,min ,max) : 
        result = random.randint(min, max)
        return result
        


    def GetEnemy(self,data : AppData.AppData):
        for ent in data._EntityList :
            if ent.IsDead() : 
                continue

            if ent._Team != self._Team :
                return  ent
            

        return False 


    def IsDead(self)->bool :  
        return self.Health <= 0 

    def Update(self,data : AppData.AppData)->None : 
       
       if(self.IsDead()):
           return    

        

       if self.OnSpecial(data) == False : 
        self.OnAttack(data)


   

    
    def InitiativeRoll(self) : 
       self._turnIndex = self.OnRollDice(0,20)

    def __str__(self) :
        return hex(id(self)).__str__() +  " has " + self.Armor.__str__() + " Armor and " + self.Health.__str__() + " Health "    

    def Print(self) :
        return self.__str__()   
    



