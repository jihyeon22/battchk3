
###############################################################################
# Path

DESTDIR		:= $(CURDIR)/out

PREFIX		:= /system
BINDIR		:= $(PREFIX)/sbin
INITRCDIR	:= /etc/init.d

###############################################################################
# Compile

CC	:= $(CROSS_COMPILE)gcc

CFLAGS	:= $(EXTRA_CFLAGS)
LDFLAGS	:= $(EXTRA_LDFLAGS)

###############################################################################
# Options

#AUTOSTART	:= y

###############################################################################
# Board Setting
CFLAGS	+= -DBOARD_$(BOARD)

###############################################################################
# Target rules

CFLAGS	+=
LDFLAGS	+=  -lmdsapi 

OBJS	:= src/batt.chk.o
APP	:= battchk3

WORK_PATH    := /system/$(VER)

all:		$(APP)

$(APP):		$(OBJS)
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install:	install-binary

install-binary:	$(APP)
	$(Q)$(call check_install_dir, $(DESTDIR)$(BINDIR))
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(BINDIR)/$(APP)
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(WORK_PATH)

clean:
	$(Q)rm -vrf $(APP) $(OBJS) 

uninstall:
	$(Q)rm -vrf $(DESTDIR)$(BINDIR)/$(APP)


# Functions

define check_install_dir
	if [ ! -d "$1" ]; then mkdir -p $1; fi
endef

