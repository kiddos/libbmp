all:
	$(MAKE) -C src $@

clean:
	$(MAKE) -C src $@

test:
	$(MAKE) -C src $@

install:
	$(MAKE) -C src $@

.PHONY: all clean test install
