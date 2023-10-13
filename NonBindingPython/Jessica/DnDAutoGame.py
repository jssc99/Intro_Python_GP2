import random
import json


def rollDice (_min : int, _max : int, nbRolls : int) :
	result = 0
	for _ in range(nbRolls) :
		result += random.randrange(_min, _max)
	return result


def rollAttack (attackRange : list) :
	# rolls a dice with range based on sent list
	return rollDice(attackRange[0], attackRange[1], 1)


def rollD20 () :
	return rollDice(0, 20, 1)


def rollD10 () :
	return rollDice(0, 10, 1)


def output (out : str, gameLog) :
	# prints and adds to log any sent str
	print (out)	
	gameLog += out, # ',' to force line return
	

def dumpOutput (gameLog) :
	# open log, dump log in it
	with open('Jessica/log.json', 'w') as log :
		json.dump (gameLog, log, indent=0, separators=(',', ''))
	

def isGameOver () :
	"returns Trues on game over"
	heroAlive = [x for x in allEntity if not x.isDead and not x.isEvil] # get every Hero alive
	evilAlive = [x for x in allEntity if not x.isDead and x.isEvil]	 # get every Villain alive
	
	if len(heroAlive) is len(evilAlive) is 0:
		print ("Everyone died! What a bloodbath! ")
		return True
	if len(heroAlive) is 0 :
		print ("Evil won the fight!")
		return True
	if len(evilAlive) is 0 :
		print ("Heros won the fight!")
		return True
	
	return False # if any list is empty (all killed), game is over otherwise game it is not


class Entity(object) :
	def __init__ (self, name: str, jsonInput : dict, isEvil : bool) :
		self.__isDead = False
		self.__name = name
		self.__armor = jsonInput['armor']
		self.__damage = jsonInput['damage']
		self.__life = jsonInput['life']
		self.__special = jsonInput['special']
		self.__initiative = rollD20()
		self.__isEvil = isEvil

	@property
	def armor(self):
		return self.__armor
	@armor.setter
	def armor(self, value):
		self.__armor = value

	@property
	def damage(self):
		return self.__damage
	@damage.setter
	def damage(self, value):
		self.__damage = value

	@property
	def life(self):
		return self.__life
	@life.setter
	def life(self, value):
		self.__life = value

	@property
	def special(self):
		return self.__special
	@special.setter
	def special(self, value):
		self.__special = value

	@property
	def isDead(self):
		return self.__isDead
	@isDead.setter
	def isDead(self, value):
		self.__isDead = value
		
	@property
	def initiative(self):
		return self.__initiative

	@property
	def name(self):
		return self.__name

	@property
	def isEvil(self):
		return self.__isEvil
	
	def __str__ (self) :
		return "Initiative roll: {}, Armor: {}, Damage: {}, Life: {}, Special: {}".format(self.initiative, self.armor, self.damage, self.life, self.special)
	
	def getDamaged (self, attackRoll, attackDng) :
		"returns 1 on hit, 0 on failed attack"
		if (attackRoll > self.armor) :
			self.life -= attackDng
			if (self.life < 1) :
				self.life = 0 
				self.isDead = True
			return True
		return False
			
	def getTarget (self) :
		"returns 0 if no target found"
		if self.isEvil :
			possibleTargets = [x for x in allEntity if not x.isEvil and not x.isDead] # make list of heroes alive
		else :
			possibleTargets = [x for x in allEntity if x.isEvil and not x.isDead] # make list of villains alive
			
		if not len (possibleTargets) is 0 :
			possibleTargets.sort(key=lambda x: x.life) # sort by health
			return possibleTargets[0] # lowest health villain gets returned
		return 0 # if list empty -> no target to return
	
	def specialAction (self) :
		# unique per class, no standard special action
		return
	
	def attackAction (self) :
		# get target, roll for attack and damage, output action success/faillure
		target = self.getTarget()
		if target is 0 : return
		
		dmg = rollD20()
		success = target.getDamaged(dmg, rollAttack(self.damage))
		
		if success : 
			output ("{} sucessfully attacked {} for {} damage(s)".format(self.name, target.name, dmg), gameLog)
		else : 
			output ("{} failled to attack {}".format(self.name, target.name), gameLog)
			
	def doAction (self) :
		# standard turn procedure
		self.specialAction()
		self.attackAction()


class Warrior(Entity) :
	def __init__ (self, name: str, jsonInput : dict, isEvil : bool = False) :
		super().__init__ (name, jsonInput, isEvil)

	def __str__ (self) :
		return "{} is a Warrior | {} |".format(self.name, super().__str__())
	
	__specialActionDone = False

	def specialAction (self) :
		# Warriors have minor healing as their special action
		if rollD20() > 10 : 
			self.life += rollDice(0, self.special[1], self.special[0])
			self.__specialActionDone = True
			output ("{} heals themselfs a bit".format(self.name), gameLog)
		
	def doAction (self) :
		# Warrior special can only be done once
		if not self.__specialActionDone :
			self.specialAction()
		self.attackAction()


class Rogue(Entity) :
	def __init__ (self, name: str, jsonInput : dict, isEvil : bool = False) :
		super().__init__ (name, jsonInput, isEvil)
		
	def __str__ (self) :
		return "{} is a Rogue | {} |".format(self.name, super().__str__())

	__bonusDice=False

	def specialAction (self) :
		# Rogues get bonus dice for their next attack as their special action
		if rollD20() > 15 :
			self.__bonusDice = True
			output ("{} activates is special action, they get a bonus dice!".format(self.name), gameLog)
	
	def attackAction (self) :
		# get target, roll for attack and damage (take into account the bonus dice), output action success/faillure
		target = self.getTarget()
		if target is 0 : return
		
		dmg = rollD20()
		if self.__bonusDice : 
			dmg += rollDice(0, self.special[1], self.special[0])
		success = target.getDamaged(dmg, rollAttack(self.damage))
		
		if success : 
			output ("{} sucessfully attacked {} for {} damage(s)".format(self.name, target.name, dmg), gameLog)
		else : 
			output ("{} failled to attack {}".format(self.name, target.name), gameLog)


class Mage(Entity) :
	def __init__ (self, name: str, jsonInput : dict, isEvil : bool = False) :
		super().__init__ (name, jsonInput, isEvil)
		
	def __str__ (self) :
		return "{} is a Mage | {} |".format(self.name, super().__str__())
	
	def specialAction (self) :
		# Mages have overpowered fireball attack as their special action
		if rollD20() > 17 :
			damage = rollDice(0, self.special[1], self.special[0])
			[x.getDamaged(100, damage) for x in allEntity if x.isEvil and not x.isDead]
			output ("{} casts is special action to a fiery result".format(self.name), gameLog)


class Orc(Entity) :
	def __init__ (self, name: str, jsonInput : dict, isEvil : bool = True) :
		super().__init__ (name, jsonInput, isEvil)
		
	def __str__ (self) :
		return "{} is an Orc | {} |".format(self.name, super().__str__())
	
	def doAction (self) :
		# Orcs have no special action
		self.attackAction()


# just for fun (40 names)
orcNames = ["Drukk","Skrag","Grung","Thurg","Snark","Bront","Kragg","Glint","Vrash","Trusk","Drang","Norka","Skrul","Dorgo","Grith","Frorn","Krond","Morsk","Zrash","Thrak",
	    "Grulk","Throk","Dorga","Snaga","Urnak","Gloth","Skorn","Brank","Gruft","Throk","Zogar","Krash","Gromm","Drulk","Norgo","Grush","Zarth","Gorka","Vrunk","Smork"]

# load the class BDD
with open('Jessica/bdd.json', 'r') as data :
	bdd : dict = json.load (data)

# GAME SETUP
allEntity = [
Warrior("Amour",                           bdd['Warrior']),
  Rogue("Gloire",                          bdd['Rogue']),
   Mage("Beauty",                          bdd['Mage']),
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']), # load stats/values from BDD
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']), # init is: name, dict for stats, isEvil boolean 
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']), # each class has a default isEvil bool
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']),
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']),
    Orc(orcNames[random.randrange(0, 39)], bdd['Orc']),
]

gameLog = []
[output (str(x), gameLog) for x in allEntity] # first print (show all stats)

allEntity.sort(key=lambda x: x.initiative, reverse = True) # reorder per their initiative

output ("Attack Order: ", gameLog)
output ([x.name for x in allEntity], gameLog) # print attack order

turnCount = 1
# GAME MAIN LOOP
while not isGameOver() :
	output ("", gameLog)
	output ("#### TURN {} ####".format(turnCount), gameLog)
	output ("", gameLog)
	
	[x.doAction() for x in allEntity if not x.isDead] # everyone alive has their turn
	
	output ("", gameLog)
	output ("End of turn life :", gameLog)
	[output (x.name + "'s HP : " + str(x.life), gameLog) for x in allEntity] # print everyone's life
	
	turnCount += 1
	
dumpOutput (gameLog) # dump log to log.json
