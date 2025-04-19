ifeq ($(OS),Windows_NT)
	RMDIR = rmdir /S /Q
	MKDIR = if not exist
	NULLDEV = nul

	LDFLAGS = -static

	EXE_EXT = .exe
else
	RMDIR = rm -rf
	MKDIR = mkdir -p
	NULLDEV = /dev/null

	ifeq ($(UNAME_S),Linux)
		LDFLAGS = -static
	else
		LDFLAGS =
	endif

	EXE_EXT =
endif