
# Registry Design Pattern

1. Factory design pattern violates OCP principle. Factory class has to maintain "if-else" for every new backend service/class is introduced. As it violates OCP, registry design pattern helps solve OCP problem like a plugin system.

2. New Class/Servie introduced in the backend has to register with the registryClass. this creates object of the new Class and Cache it with hash-map for the "look-up"

3. For client to call the instance of the new class, it calls "create" method and this method does the look-up with the type(a string), create method does a look-up and return the instance of the class.
