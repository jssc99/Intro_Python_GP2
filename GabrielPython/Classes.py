
#Objects and classes
from datetime import date

class Date:     #descriptor
    def __set_name__(self, owner, name):
        self._name = name

    def __get__(self, instance, owner):
        return instance.__dict__[self._name]

    def __set__(self, instance, value):
        instance.__dict__[self._name] = date.fromisoformat(value)

class Animal (object):
    '''Classe Animal'''
    # When defining a class's attributes, if they are preceded by __, it means they are private
    # if they are preceded by _, it means they are protected
    __weight=0
    __birth_date=Date()

    # Defining methods inside a class
    # Constructor with parameters
    def __init__(self, race, name, weight,birth_date):      #https://docs.python.org/3/reference/datamodel.html
        self.__race = race
        self.__name = name
        self.__weight = weight
        self.__birth_date = birth_date
        
    # to print all properties of an object we will create a toSting method:
    def __str__(self):
        #as this method exists inside the class, it is not necessary to call the getters to obtain the information
        return "{} is of race {} and weighs {} kilograms ".format(self.name, self.get_race(),self.weight)

    #some other instance method
    def feed(self):
        print("{} has been fed".format(self.name))

    # getter/setter, properties         https://realpython.com/python-getter-setter/
    def get_race(self):
        return self.__race

    def set_race(self, race):
        self.__race = race

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

 
    @property
    def weight(self):
        return self.__weight

    @weight.setter
    def weight(self, value):
        self.__weight = value 

# Declaring and initializing an Object based on the class we just created
dog = Animal('dog','gooddog', 33, '2019-12-04')

# Calling one of the methods from the Object
print(dog)
dog.feed()
print(type(dog))



# INHERITANCE
# To inherit from a class, we write the superclass in parentheses after the name of the subclass

class Dog(Animal):
    # once the inheritance is declared, the subclass gets all the variables and functions from the superclass
    __owner = ''

    #Overriding the constructor of the animal class
    def __init__(self, name, weight, birthdate, owner):
        super().__init__('dog',name,weight,birthdate)
        self.owner = owner

    @property
    def owner(self):
        return self.__owner
    @owner.setter
    def owner(self, value):
        self.__owner = value

    #Overriding the __str__() function
    def __str__(self):
        return Animal.__str__(self)+" and owner is {}".format(self.owner)

# Creating an object based on the subclass we just created
spot = Dog("spot", 53, '2020-11-20','david')
print(spot)
spot.feed()
print(type(spot))
