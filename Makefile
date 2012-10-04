SUBDIRS = src \
	test
default: all

all \
release \
clean \
test \
debug: 
	@for subdir in ${SUBDIRS} ; \
	do \
		(cd $${subdir}; $(MAKE) $@ ); \
	done

