include $(top_srcdir)/config/Rules.am

VPATH = \
	$(top_srcdir)/contrib/zstd \
	$(top_srcdir)/contrib/zstd/common \
	$(top_srcdir)/contrib/zstd/compress \
	$(top_srcdir)/contrib/zstd/decompress \
	$(top_srcdir)/module/zstd

# Quiet warnings about frame size due to unused code in unmodified zstd lib
AM_CFLAGS += -Wframe-larger-than=18000

DEFAULT_INCLUDES += \
	-I$(top_srcdir)/contrib/zstd \
	-I$(top_srcdir)/contrib/zstd/common \
	-I$(top_srcdir)/contrib/zstd/compress \
	-I$(top_srcdir)/contrib/zstd/decompress

noinst_LTLIBRARIES = libzstd.la

KERNEL_C = \
	zstd_common.c \
	fse_decompress.c \
	entropy_common.c \
	xxhash.c \
	hist.c \
	error_private.c \
	zstd_compress.c \
	zstd_compress_literals.c \
	zstd_compress_sequences.c \
	fse_compress.c \
	huf_compress.c \
	zstd_double_fast.c \
	zstd_fast.c \
	zstd_lazy.c \
	zstd_ldm.c \
	zstd_opt.c \
	zstd_ddict.c \
	zstd_decompress.c \
	zstd_decompress_block.c \
	huf_decompress.c \
	zstd.c

nodist_libzstd_la_SOURCES = $(KERNEL_C)
