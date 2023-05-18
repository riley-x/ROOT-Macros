FILES := $(shell find src/ -name '*.cxx')

TARGETS := $(FILES:src/%.cxx=exe/%)
HEADERS := $(shell find src/ -name '*.h')

GIT_COMMIT := $(shell git describe --always --dirty)

.PHONY: all
all: $(TARGETS)

$(TARGETS): exe/%: src/%.cxx $(HEADERS)
	`root-config --cxx --cflags` -g3 -o $@ $< -lTreePlayer `root-config --libs` -Wall -Wno-narrowing -DGIT_COMMIT=\"$(GIT_COMMIT)\"

clean:
	rm exe/*
