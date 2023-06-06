# Variables
COURSE    = cs240
SEMESTER  = spring2023
CP_NUMBER = 5
LASTNAME  = Vural
GITUSERID = mertcanvural
EXES 	  = pr_check sch_check

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(GITUSERID).tar.gz

FLAGS = -Wall -Wextra -g


CC = g++
OBJ = obj
all: $(EXES)
#----------------------------------------------------------------
pr_check : $(OBJ)/pr_check.o ./utils/Graph.h
	$(CC) $(FLAGS) $^ -o $@

$(OBJ)/pr_check.o  : pr_check.cpp ./utils/prereq_util.h
	$(CC) $(FLAGS) -c $< -o $@

#----------------------------------------------------------------
# sch_check
sch_check : $(OBJ)/sch_check.o ./utils/Graph.h
	$(CC) $(FLAGS) $^ -o $@

$(OBJ)/sch_check.o  : sch_check.cpp ./utils/sched_util.h ./utils/prereq_util.h ./utils/Schedule.h ./utils/Graph.h
	$(CC) $(FLAGS) -c $< -o $@
#----------------------------------------------------------------

tar: clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o pr_check sch_check *.tar.gz