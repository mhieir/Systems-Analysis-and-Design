build and run :
kotlinc first/src/data/*.kt first/src/domain/*.kt first/src/pres/*.kt first/src/main.kt -include-runtime -d first/src/main.jar
java -jar first/src/main.jar

uml :
java -jar first/src/puml/plantuml.jar first/src/puml/pres.puml
java -jar first/src/puml/plantuml.jar first/src/puml/domain.puml
java -jar first/src/puml/plantuml.jar first/src/puml/data.puml