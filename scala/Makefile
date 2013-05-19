SCALA = scalac
SCALAFLAGS = -d bin

all: compile	

compile:
	@mkdir bin -p && $(SCALA) $(SCALAFLAGS) src/*.scala

run:
	@scala -classpath bin Main

clean:
	@rm -rf bin
