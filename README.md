# Task Description
(This task was given as an assignment in BSc Computer Science - OOP course at Eötvös Loránd University)
(The given task need to be solved using design patterns)

Layers of gases are given, with certain type (ozone, oxygen, carbon dioxide) and thickness, affected by atmospheric variables (thunderstorm, sunshine, other effects). When a part of one layer changes into another layer due to an athmospheric variable, the newly transformed layer ascends and engrosses the first identical type of layer of gases over it. In case there is no identical layer above, it creates a new layer on the top of the atmosphere.
In the following we declare, how the different types of layers react to the different variables by changing their type and thickness.
No layer can have a thickness less than 0.5 km, unless it ascends to the identical-type upper layer. In case there is no identical one, the layer perishes.


|                | Sunshine           | Thunderstorm       | Other                       |
|----------------|--------------------|--------------------|-----------------------------|
| Ozone          | -                  | -                  | 5% turns to Oxygen          |
| Oxygen         | 50% turns to Ozone | 5% turns to ozone  | 10% turns to Carbon dioxide |
| Carbon dioxide | -                  | 5% turns to oxygen | -                           |


The program reads data from a text file. The first line of the file contains a single integer N indicating the number of layers. Each of the following N lines contains the attributes of a layer separated by spaces: type and thickness. The type is identified by a character: Z – ozone, X – oxygen, C – carbon dioxide.
The last line of the file represents the atmospheric variables in the form of a sequence of characters: T – thunderstorm, S – sunshine, O – others. In case the simulation is over, it continues from the beginning.  
**The program should continue the simulation until the number of layers is the triple of the initial number of layers or is less than three. The program should print all attributes of the layers by simulation rounds!**  
**The program should ask for a filename, then print the content of the input file. You can assume that the input file is correct.**

Sample input: 

4  
Z 3  
X 0.8  
C 2  
X 5  
OOOOSSTSSOO   
