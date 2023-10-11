import Entity
import AppData 
import time
from Entity import Entity
from Entity import EnumTeam

import json
import Mage 
import Warrior 
import Rogue 
import Orc


class App(object): 
 
    data : AppData.AppData = AppData.AppData()
    
    def __init__(self) -> None:
        self.LoadJsonFile()
        for ent in self.data._EntityList : 
            ent.InitiativeRoll()


    def LoadJsonFile(self) : 
        with open('Gabriel/DnD/bdd.json') as json_file:
            data = json.load(json_file)
            ## Load warrior
            str = data['Warrior']
            w = Warrior.Warrior()
            w._Team = EnumTeam.PLAYER
            w.Armor = str['armor']
            w.Damage = str['damage']
            w.Health = str['life']
            minmax = str['special']
            w.SetHealValue(minmax[0],minmax[1])
            self.data._EntityList.append(w)

            str = data['Mage']
            m = Mage.Mage()
            m._Team = EnumTeam.PLAYER
            m.Armor = str['armor']
            m.Health = str['life']
            m.Damage =  str['damage']
            minmax = str['special']
            m.SetMinMaxAddDamag(minmax[0],minmax[1])
            self.data._EntityList.append(m)

            str = data['Rogue']
            r = Rogue.Rogue()
            r._Team = EnumTeam.PLAYER
            r.Armor = str['armor']
            r.Health = str['life']
            r.Damage =  str['damage']
            minmax = str['special']
            r.SetMinMaxAddDamag(minmax[0],minmax[1])
            self.data._EntityList.append(r)    

            str = data['Orc']
            i = 0 
            maxOrc = 5
            while i < maxOrc  :
                orc = Orc.Orc()
                orc._Team = EnumTeam.ENEMY
                orc.Armor = str['armor']
                orc.Health = str['life']
                orc.Damage =  str['damage']
                self.data._EntityList.append(orc)    
                i += 1
        self.CountEntity() 
            



    def EndOfGame(self)-> bool: 
        Countplayerdead = 0
        CountOrcDead = 0 
        for ent in self.data._EntityList : 
            if  ent.IsDead() : 
                if ent._Team == EnumTeam.PLAYER  :
                    Countplayerdead += 1
                if ent._Team == EnumTeam.ENEMY : 
                    CountOrcDead += 1

        if Countplayerdead == self.data._CountNbrAdv or CountOrcDead == self.data._CountNbrOrc  : 

            if CountOrcDead == self.data._CountNbrOrc :  
                self.data._bAdventurerWin = True 

            return True 
          
        return False

                 
    def CountEntity(self) : 

        for ent in self.data._EntityList : 
            if ent._Team is EnumTeam.PLAYER : 
                self.data._CountNbrAdv += 1
            else : 
                self.data._CountNbrOrc += 1


    def PrintEndOfGame(self) : 
        if self.data._bAdventurerWin == True : 
            print("THE Adventurer WIN") 
        else : print("ORC WIN")
        
    


    def Update(self)->None : 
        
    


        maxindex =  Entity.GetMaxTurnTurn(self.data._EntityList)
        while self.EndOfGame() == False :

             
            i = 0
            while( i != maxindex ) : 

                for ent in self.data._EntityList : 
                    if ent.GetTurn() == i : 
                        time.sleep(0.2)
                        ent.Update(self.data)
                i += 1 


        self.PrintEndOfGame()






