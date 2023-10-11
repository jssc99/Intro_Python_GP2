 
import Entity
import AppData

from Entity import*


class Rogue(Entity) :


    _addDamageminMax = [0, 0]
    DiceToExecute : int =  16
    _increaseDamage = 0 

    def __init__(self):
        super().__init__()  
        self._addDamageminMax = [0, 0]


    def SetMinMaxAddDamag(self ,min : int,max : int) :
        self._addDamageminMax[0] = min 
        self._addDamageminMax[1] = max 
    

    def OnSpecial(self,data : AppData.AppData)->bool :
        Dice : int  = super().OnRollDice(0,20)

        if Dice >= Rogue.DiceToExecute : 
            Dice = super().OnRollDice(self._addDamageminMax[0],self._addDamageminMax[1]) 
            _increaseDamage = Dice
            return True
        
        _increaseDamage = 1   
        return False


    def OnAttack(self,data : AppData.AppData)->bool :

        enemy  = super().GetEnemy(data)
        Dice = super().OnRollDice(0,20)

        if enemy == False : 
            return False


        if(Dice <= enemy.Armor) :
            print(self.__str__() + " attack the orc " + enemy.__str__())
            Dice = super().OnRollDice(self.Damage[0],self.Damage[1])
            enemy.Health -= Dice * self._increaseDamage

            return True
        
        print(self.__str__() + " has miss his  attack   " + enemy.__str__())

        pass
    

        

    
    def __str__(self) :
        return " The Rogue "  + (id(self)).__str__()     
        
