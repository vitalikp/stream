
PROJNAME = stream
SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(SOURCES:.c=.o)

#CFLAGS	+= -ggdb -DDEBUG
CFLAGS  += -std=c99
CFLAGS  += -Isrc

all: $(PROJNAME)

$(PROJNAME): $(OBJECTS)
	@echo -e "\e[1;32m CCLD\e[0m\t$(PROJNAME)" 
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(PROJNAME)

%.o: %.c 
	@echo -e "\e[1m   CC\e[0m\t$<"
	@$(CC) -c $< $(CFLAGS) -o $@
	
clean:
	@echo -e "\e[1;31m   RM\e[0m\t$(OBJECTS)" 
	@rm -f $(OBJECTS)
	@echo -e "\e[1;31m   RM\e[0m\t$(PROJNAME)"
	@rm -f "$(PROJNAME)"
