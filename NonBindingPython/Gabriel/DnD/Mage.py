
import sys
sys.path.append('..')  
import Entity
import AppData
from Entity import*
import Orc

class Mage(Entity) :

    _fireBallminMax = [0, 0]
    _addDamageMax : int = 0 
    DiceToExecute : int =  18

    def __init__(self):
        super().__init__()  
        self._fireBallminMax = [0, 0]
        

    def SetMinMaxAddDamag(self ,min : int, max : int) :
        self._fireBallminMax[0] = min
        self._fireBallminMax[1] = max

    

    
    def OnSpecial(self,data : AppData.AppData)->bool :
        Dice : int  = super().OnRollDice(0,20)

        if Dice >= Mage.DiceToExecute : 

            print(self.__str__() + "Has throw a fireBall on the enemy")
            Dice = super().OnRollDice(self._fireBallminMax[0],self._fireBallminMax[1])

            for orc  in  data._EntityList :
                if orc is Orc.Orc and orc.IsDead() :   
                    orc -= Dice


            return True
        
        print(self.__str__() + " has Faild his fireBall ")


        return False


    def OnAttack(self,data : AppData.AppData)->bool :

        enemy  = super().GetEnemy(data)
        Dice = super().OnRollDice(0,20)

        if enemy == False : 
            return False


        if(Dice <= enemy.Armor) :
            print(self.__str__() + " attack the orc " + enemy.__str__())
            Dice = super().OnRollDice(self.Damage[0],self.Damage[1])
            enemy.Health -= Dice 
            return True
        
        print(self.__str__() + " has miss his  attack the orc " + enemy.__str__())

    


    def __str__(self) :
        return " The Mage "  + (id(self)).__str__()     