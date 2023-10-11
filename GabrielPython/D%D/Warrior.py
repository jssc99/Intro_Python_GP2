
import Entity
import AppData

from Entity import*


class Warrior(Entity) :

   
    _hasUseHeal : bool = False
    _healValue : [0,0]
    ValueToHeal = 0 

    def __init__(self):
        super().__init__()  
        self._hasUseHeal = False
        self._healValue = [0, 0]

    def SetHealValue(self , min : int, max : int) : 
        self._healValue[0] = min
        self._healValue[1] = max


    def OnAttack(self, data : AppData.AppData)->bool :
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


    def OnSpecial(self, data : AppData.AppData)->bool :

        if self.Health == True : 
            return False 


        Dice : int  = super().OnRollDice(0,10)

        if Dice >= Warrior.ValueToHeal : 

            Dice = super().OnRollDice(self._healValue[0],self._healValue[1]) 
            self.Health += Dice
            print(self.__str__() + "Heal for " + Dice.__str__())
            self.Health = True
            return True
        

    
    def __str__(self) :
        return " The Warrior "  + (id(self)).__str__()     
        

