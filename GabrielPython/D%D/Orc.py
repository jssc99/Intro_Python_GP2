import Entity
import AppData 

class Orc(Entity.Entity): 

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

        print(self.__str__() + " has miss his attack " + enemy.__str__())


        

    def OnSpecial(self, data : AppData.AppData)->bool :
        return False
      

    def __str__(self) :
        return " The Orc "  + (id(self)).__str__()  