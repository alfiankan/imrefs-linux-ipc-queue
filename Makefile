build:
	nim c imrefs.nim && mv imrefs dist/imrefs
install:
	cp dist/imrefs /usr/local/bin
cleanque:
	ipcrm --all=msg