include $(top_srcdir)/config/Rules.am

VPATH = $(top_srcdir)/module/zstd

# Includes kernel code, generate warnings for large stack frames
AM_CFLAGS += $(FRAME_LARGER_THAN)

noinst_LTLIBRARIES = libzstd.la

KERNEL_C = \
	zfs_zstd.c \
	zstd.c

nodist_libzstd_la_SOURCES = $(KERNEL_C)

# -fno-tree-vectorize is set for gcc in zstd/common/compiler.h
# Set it for other compilers, too.
zstd.$(OBJEXT):  CFLAGS += -fno-tree-vectorize
zstd.l$(OBJEXT): CFLAGS += -fno-tree-vectorize

# Quiet warnings about frame size due to unused code in unmodified zstd lib
zstd.$(OBJEXT):  CFLAGS += -Wframe-larger-than=20480
zstd.l$(OBJEXT): CFLAGS += -Wframe-larger-than=20480
