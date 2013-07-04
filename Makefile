all:
	$(MAKE) -C lib
	$(MAKE) -C example

clean:
	$(MAKE) clean -C lib
	$(MAKE) clean -C example


