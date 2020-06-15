/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2016-2018, Klara Inc.
 * Copyright (c) 2016-2018, Allan Jude.
 * Copyright (c) 2018-2019, Sebastian Gottschall. All rights reserved.
 * Copyright (c) 2019-2020, Michael Niewöhner. All rights reserved.
 */

#ifndef	_ZFS_ZSTD_H
#define	_ZFS_ZSTD_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * ZSTD block header
 * NOTE: all fields in this header are in big endian order.
 */
typedef struct zfs_zstd_header {
	/* Compressed size of data */
	uint32_t c_len;

	/*
	 * Version and compression level
	 * We have to choose a union here to handle endian conversation
	 * correctly, since the version and level is bitmask encoded.
	 */
	union {
		uint32_t raw_version_level;
		struct {
			uint32_t version : 24;
			uint8_t level;
		};
	};

	char data[];
} zfs_zstdhdr_t;

/* (de)init for user space / kernel emulation */
int zstd_init(void);
void zstd_fini(void);

size_t zstd_compress(void *s_start, void *d_start, size_t s_len, size_t d_len,
    int level);
int zstd_get_level(void *s_start, size_t s_len, uint8_t *level);
int zstd_decompress_level(void *s_start, void *d_start, size_t s_len,
    size_t d_len, uint8_t *level);
int zstd_decompress(void *s_start, void *d_start, size_t s_len, size_t d_len,
    int n);

#ifdef	__cplusplus
}
#endif

#endif /* _ZFS_ZSTD_H */
