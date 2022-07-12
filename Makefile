objects = cpu_usage marisa top_process

CFLAGS = -march=native -O2

all: $(objects)

$(objects): %: .local/src/status/%.c
	$(CC) $(CFLAGS) -o .local/bin/$@ $<
