/*
 * BSD 2-Clause License (http://www.opensource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 2014-2019, Allan Jude. All rights reserved.
 * Copyright (c) 2020, Brian Behlendorf. All rights reserved.
 * Copyright (c) 2020, Michael Niewöhner. All rights reserved.
 */

#ifndef	_ZSTD_STDLIB_H
#define	_ZSTD_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL

#if defined(__FreeBSD__)

#include <sys/malloc.h>

MALLOC_DECLARE(M_ZSTD);

#undef	malloc
#define	malloc(x)	(malloc)((x), M_ZSTD, M_WAITOK)
#define	free(x)		(free)((x), M_ZSTD)
#define	calloc(a, b)	(mallocarray)((a), (b), M_ZSTD, M_WAITOK | M_ZERO)

#elif defined(__linux__)

//#include <linux/slab.h>

#undef	GCC_VERSION

// TODO fix malloc*; this currently breaks build
/*
#define	malloc(sz)	kmalloc(sz, GFP_KERNEL | __GFP_NOFAIL)
#define	free(ptr)	kfree(ptr)
#define	calloc(n, sz)	kzalloc((n) * (sz), GFP_KERNEL | __GFP_NOFAIL)
*/
extern void *spl_kmem_alloc(size_t sz, int fl, const char *func, int line);
extern void *spl_kmem_zalloc(size_t sz, int fl, const char *func, int line);
extern void spl_kmem_free(const void *ptr, size_t sz);
#define	KM_SLEEP	0x0000  /* can block for memory; success guaranteed */
#define	KM_NOSLEEP	0x0001  /* cannot block for memory; may fail */
#define	KM_ZERO		0x1000  /* zero the allocation */
#undef malloc
#define	malloc(sz)	spl_kmem_alloc((sz), KM_SLEEP, __func__, __LINE__)
#define	free(ptr)	spl_kmem_free((ptr), 0)
#define	calloc(n, sz)	\
    spl_kmem_zalloc((n) * (sz), KM_SLEEP, __func__, __LINE__)

#else
#error "Unsupported platform"
#endif

#else /* !_KERNEL */
#include_next <stdlib.h>	/* malloc, calloc, free */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _ZSTD_STDLIB_H */
