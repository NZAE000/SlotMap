EXEC 		:= exec
CC 			:= clang++ -std=c++23
CCFLAGS		:= -O3 -Wall -Wextra -Wpedantic
SRCDIR 		:= src
OBJDIR 		:= obj
INCLUDES	:= -I $(SRCDIR)
SUBDIRS 	:= $(shell find $(SRCDIR) -type d)
OBJSUBDIRS 	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SUBDIRS))
ALLSOURCES 	:= $(shell find $(SRCDIR) -type f -iname "*.cpp")
ALLOBJS   	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(patsubst %.cpp,%.o,$(ALLSOURCES)))

.PHONY: info clean

$(EXEC) : $(OBJSUBDIRS) $(ALLOBJS)
	$(CC) $(CCFLAGS) $(ALLOBJS) -o $(EXEC)


$(OBJSUBDIRS):
	mkdir -p $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) $(INCLUDES) -c $^ -o $@


clean:
	rm -r $(OBJDIR) $(EXEC)

info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLSOURCES))
	$(info $(ALLOBJS))