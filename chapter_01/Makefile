ECHO = echo
DIRS = CircularDoublyLinkedList DoublyLinkedList LinkedList
all: $(DIRS)

CircularDoublyLinkedList: force_look
	cd CircularDoublyLinkedList; make

DoublyLinkedList: force_look
	cd DoublyLinkedList; make

LinkedList: force_look
	cd LinkedList; make

clean: force_look
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean); done

distclean: force_look
	-for d in $(DIRS); do (cd $$d; $(MAKE) distclean); done

force_look:
	true
