X ?=

BIN_NAME := fullsendx
ORG_NAME := com.pointshiftdo

BIN_DIR := bin/
BIN_PATH := $(BIN_DIR)$(BIN_NAME)

LAUNCHD_DIR := launchd/
LAUNCHD_SERVICE_NAME := $(ORG_NAME).$(BIN_NAME)
LAUNCHD_STDOUT_PATH := $(LAUNCHD_DIR)stdout.log
LAUNCHD_STDERR_PATH := $(LAUNCHD_DIR)stderr.log

LAUNCHD_INSTALL_DIR := $(HOME)/Library/LaunchAgents/
LAUNCHD_INSTALL_PATH := $(LAUNCHD_INSTALL_DIR)$(LAUNCHD_SERVICE_NAME).plist
LAUNCHD_UID := $(shell id -u $(USER))
LAUNCHD_DOMAIN_ID := gui/$(LAUNCHD_UID)
LAUNCHD_SERVICE_ID := $(LAUNCHD_DOMAIN_ID)/$(LAUNCHD_SERVICE_NAME)


# general

.PHONY: all
all: $(BIN_PATH)
ifeq ($(X),)
else
	$(BIN_PATH) $(X)
endif

.PHONY: clean
clean:
	@make uninstalld 2>/dev/null
	rm -rf $(BIN_DIR) $(LAUNCHD_DIR)


# build

CFLAGS := \
	-std=c99 \
	-pedantic \
	-fvisibility=hidden \
	-O2 \
	-Wall \
	-Wno-deprecated-declarations
LFLAGS := \
	-framework ApplicationServices \
	-framework CoreFoundation

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_PATH): $(BIN_DIR) fullsendx.h main.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $(BIN_PATH) main.c


# launchd

$(LAUNCHD_DIR):
	@mkdir -p $(LAUNCHD_DIR)
	@touch $(LAUNCHD_STDOUT_PATH) $(LAUNCHD_STDERR_PATH)
	@ln -sf $(LAUNCHD_INSTALL_DIR) $(LAUNCHD_DIR)

.PHONY: installd
installd: $(LAUNCHD_DIR) $(BIN_PATH) main.plist
	@make uninstalld 2>/dev/null

	sed \
		-e 's|LAUNCHD_SERVICE_NAME|$(LAUNCHD_SERVICE_NAME)|g' \
		-e 's|LAUNCHD_BIN_PATH|$(shell realpath $(BIN_PATH))|g' \
		-e 's|LAUNCHD_EXEC_PATH|$(X)|g' \
		-e 's|LAUNCHD_LOGS_STDOUT_PATH|$(shell realpath $(LAUNCHD_STDOUT_PATH))|g' \
		-e 's|LAUNCHD_LOGS_STDERR_PATH|$(shell realpath $(LAUNCHD_STDERR_PATH))|g' \
		main.plist > $(LAUNCHD_INSTALL_PATH)

	launchctl bootstrap $(LAUNCHD_DOMAIN_ID) $(LAUNCHD_INSTALL_PATH)
	launchctl kickstart $(LAUNCHD_SERVICE_ID)

.PHONY: uninstalld
uninstalld:
	launchctl bootout $(LAUNCHD_SERVICE_ID); true
	rm -f $(LAUNCHD_INSTALL_PATH)

.PHONY: statusd
statusd:
	launchctl print $(LAUNCHD_SERVICE_ID); true
	@echo
	launchctl list $(LAUNCHD_SERVICE_NAME); true
	@echo
	launchctl list | grep $(LAUNCHD_SERVICE_NAME); true
