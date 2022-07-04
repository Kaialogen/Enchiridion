OUT = bin

SEARCHPATH += $(shell find src -type d | sort)

vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h

_OBJS = $(shell find src -iname *.c -type f -exec basename {} \; | sed 's/\.c/\.o/g' | sort | grep -v win32)

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

all: $(PROG)

$(OUT)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) -rf $(OUT) $(PROG)

