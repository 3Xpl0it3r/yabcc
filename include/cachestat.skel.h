/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */

/* THIS FILE IS AUTOGENERATED BY BPFTOOL! */
#ifndef __SKEL_CACHESTAT_SKEL_H__
#define __SKEL_CACHESTAT_SKEL_H__

#include <errno.h>
#include <stdlib.h>
#include <bpf/libbpf.h>

struct skel_cachestat {
	struct bpf_object_skeleton *skeleton;
	struct bpf_object *obj;
	struct {
		struct bpf_map *count_map;
		struct bpf_map *bss;
	} maps;
	struct {
		struct bpf_program *kprobe_bpf_prog_add_to_page_cache_lru;
		struct bpf_program *kprobe_bpf_prog_mark_page_accessed;
		struct bpf_program *kprobe_bpf_prog_account_page_dirtied;
		struct bpf_program *kprobe_bpf_prog_mark_buffer_dirty;
	} progs;
	struct {
		struct bpf_link *kprobe_bpf_prog_add_to_page_cache_lru;
		struct bpf_link *kprobe_bpf_prog_mark_page_accessed;
		struct bpf_link *kprobe_bpf_prog_account_page_dirtied;
		struct bpf_link *kprobe_bpf_prog_mark_buffer_dirty;
	} links;
	struct skel_cachestat__bss {
		__s64 total;
		__s64 misses;
		__s64 mbd;
	} *bss;

#ifdef __cplusplus
	static inline struct skel_cachestat *open(const struct bpf_object_open_opts *opts = nullptr);
	static inline struct skel_cachestat *open_and_load();
	static inline int load(struct skel_cachestat *skel);
	static inline int attach(struct skel_cachestat *skel);
	static inline void detach(struct skel_cachestat *skel);
	static inline void destroy(struct skel_cachestat *skel);
	static inline const void *elf_bytes(size_t *sz);
#endif /* __cplusplus */
};

static void
skel_cachestat__destroy(struct skel_cachestat *obj)
{
	if (!obj)
		return;
	if (obj->skeleton)
		bpf_object__destroy_skeleton(obj->skeleton);
	free(obj);
}

static inline int
skel_cachestat__create_skeleton(struct skel_cachestat *obj);

static inline struct skel_cachestat *
skel_cachestat__open_opts(const struct bpf_object_open_opts *opts)
{
	struct skel_cachestat *obj;
	int err;

	obj = (struct skel_cachestat *)calloc(1, sizeof(*obj));
	if (!obj) {
		errno = ENOMEM;
		return NULL;
	}

	err = skel_cachestat__create_skeleton(obj);
	if (err)
		goto err_out;

	err = bpf_object__open_skeleton(obj->skeleton, opts);
	if (err)
		goto err_out;

	return obj;
err_out:
	skel_cachestat__destroy(obj);
	errno = -err;
	return NULL;
}

static inline struct skel_cachestat *
skel_cachestat__open(void)
{
	return skel_cachestat__open_opts(NULL);
}

static inline int
skel_cachestat__load(struct skel_cachestat *obj)
{
	return bpf_object__load_skeleton(obj->skeleton);
}

static inline struct skel_cachestat *
skel_cachestat__open_and_load(void)
{
	struct skel_cachestat *obj;
	int err;

	obj = skel_cachestat__open();
	if (!obj)
		return NULL;
	err = skel_cachestat__load(obj);
	if (err) {
		skel_cachestat__destroy(obj);
		errno = -err;
		return NULL;
	}
	return obj;
}

static inline int
skel_cachestat__attach(struct skel_cachestat *obj)
{
	return bpf_object__attach_skeleton(obj->skeleton);
}

static inline void
skel_cachestat__detach(struct skel_cachestat *obj)
{
	return bpf_object__detach_skeleton(obj->skeleton);
}

static inline const void *skel_cachestat__elf_bytes(size_t *sz);

static inline int
skel_cachestat__create_skeleton(struct skel_cachestat *obj)
{
	struct bpf_object_skeleton *s;
	int err;

	s = (struct bpf_object_skeleton *)calloc(1, sizeof(*s));
	if (!s)	{
		err = -ENOMEM;
		goto err;
	}

	s->sz = sizeof(*s);
	s->name = "skel_cachestat";
	s->obj = &obj->obj;

	/* maps */
	s->map_cnt = 2;
	s->map_skel_sz = sizeof(*s->maps);
	s->maps = (struct bpf_map_skeleton *)calloc(s->map_cnt, s->map_skel_sz);
	if (!s->maps) {
		err = -ENOMEM;
		goto err;
	}

	s->maps[0].name = "count_map";
	s->maps[0].map = &obj->maps.count_map;

	s->maps[1].name = "skel_cac.bss";
	s->maps[1].map = &obj->maps.bss;
	s->maps[1].mmaped = (void **)&obj->bss;

	/* programs */
	s->prog_cnt = 4;
	s->prog_skel_sz = sizeof(*s->progs);
	s->progs = (struct bpf_prog_skeleton *)calloc(s->prog_cnt, s->prog_skel_sz);
	if (!s->progs) {
		err = -ENOMEM;
		goto err;
	}

	s->progs[0].name = "kprobe_bpf_prog_add_to_page_cache_lru";
	s->progs[0].prog = &obj->progs.kprobe_bpf_prog_add_to_page_cache_lru;
	s->progs[0].link = &obj->links.kprobe_bpf_prog_add_to_page_cache_lru;

	s->progs[1].name = "kprobe_bpf_prog_mark_page_accessed";
	s->progs[1].prog = &obj->progs.kprobe_bpf_prog_mark_page_accessed;
	s->progs[1].link = &obj->links.kprobe_bpf_prog_mark_page_accessed;

	s->progs[2].name = "kprobe_bpf_prog_account_page_dirtied";
	s->progs[2].prog = &obj->progs.kprobe_bpf_prog_account_page_dirtied;
	s->progs[2].link = &obj->links.kprobe_bpf_prog_account_page_dirtied;

	s->progs[3].name = "kprobe_bpf_prog_mark_buffer_dirty";
	s->progs[3].prog = &obj->progs.kprobe_bpf_prog_mark_buffer_dirty;
	s->progs[3].link = &obj->links.kprobe_bpf_prog_mark_buffer_dirty;

	s->data = (void *)skel_cachestat__elf_bytes(&s->data_sz);

	obj->skeleton = s;
	return 0;
err:
	bpf_object__destroy_skeleton(s);
	return err;
}

static inline const void *skel_cachestat__elf_bytes(size_t *sz)
{
	*sz = 9408;
	return (const void *)"\
\x7f\x45\x4c\x46\x02\x01\x01\0\0\0\0\0\0\0\0\0\x01\0\xf7\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\x40\x1c\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\x40\0\x22\0\
\x01\0\xb7\x01\0\0\x01\0\0\0\x18\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xdb\x12\0\0\0\
\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\xb7\x01\0\0\x01\0\0\0\x18\x02\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xdb\x12\0\0\0\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\
\xb7\x01\0\0\xff\xff\xff\xff\x18\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xdb\x12\0\0\0\
\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\xb7\x01\0\0\xff\xff\xff\xff\x18\x02\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xdb\x12\0\0\0\0\0\0\xb7\x01\0\0\x01\0\0\0\x18\x02\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xdb\x12\0\0\0\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\
\0\0\0\x47\x50\x4c\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x01\x11\x01\x25\x25\x13\x05\x03\x25\x72\x17\x10\x17\x1b\x25\x11\
\x01\x55\x23\x73\x17\x74\x17\0\0\x02\x34\0\x03\x25\x49\x13\x3f\x19\x3a\x0b\x3b\
\x0b\x02\x18\0\0\x03\x16\0\x49\x13\x03\x25\x3a\x0b\x3b\x0b\0\0\x04\x24\0\x03\
\x25\x3e\x0b\x0b\x0b\0\0\x05\x01\x01\x49\x13\0\0\x06\x21\0\x49\x13\x37\x0b\0\0\
\x07\x24\0\x03\x25\x0b\x0b\x3e\x0b\0\0\x08\x13\x01\x0b\x0b\x3a\x0b\x3b\x0b\0\0\
\x09\x0d\0\x03\x25\x49\x13\x3a\x0b\x3b\x0b\x38\x0b\0\0\x0a\x0f\0\x49\x13\0\0\
\x0b\x2e\x01\x11\x1b\x12\x06\x40\x18\x7a\x19\x03\x25\x3a\x0b\x3b\x0b\x27\x19\
\x49\x13\x3f\x19\0\0\x0c\x05\0\x03\x25\x3a\x0b\x3b\x0b\x49\x13\0\0\x0d\x13\x01\
\x03\x25\x0b\x0b\x3a\x0b\x3b\x05\0\0\x0e\x0d\0\x03\x25\x49\x13\x3a\x0b\x3b\x05\
\x38\x0b\0\0\0\x26\x02\0\0\x05\0\x01\x08\0\0\0\0\x01\0\x0c\0\x01\x08\0\0\0\0\0\
\0\0\x02\0\0\0\0\0\0\0\0\0\x08\0\0\0\x0c\0\0\0\x02\x03\x36\0\0\0\0\x0a\x02\xa1\
\0\x03\x3e\0\0\0\x05\x01\x12\x04\x04\x05\x08\x02\x06\x36\0\0\0\0\x0b\x02\xa1\
\x01\x02\x07\x36\0\0\0\0\x0c\x02\xa1\x02\x02\x08\x63\0\0\0\0\x85\x02\xa1\x03\
\x05\x6f\0\0\0\x06\x73\0\0\0\x04\0\x04\x09\x06\x01\x07\x0a\x08\x07\x02\x0b\x82\
\0\0\0\0\x18\x02\xa1\x04\x08\x20\0\x13\x09\x0c\xab\0\0\0\0\x14\0\x09\x0e\xc0\0\
\0\0\0\x15\x08\x09\x0f\xd1\0\0\0\0\x16\x10\x09\x12\xe2\0\0\0\0\x17\x18\0\x0a\
\xb0\0\0\0\x05\xbc\0\0\0\x06\x73\0\0\0\x01\0\x04\x0d\x05\x04\x0a\xc5\0\0\0\x05\
\xbc\0\0\0\x06\x73\0\0\0\x03\0\x0a\xd6\0\0\0\x03\xde\0\0\0\x11\x01\x10\x04\x10\
\x07\x04\x0a\x36\0\0\0\x0b\x05\x30\0\0\0\x01\x5a\x13\0\x2a\xbc\0\0\0\x0c\x17\0\
\x2a\x47\x01\0\0\0\x0b\x06\x30\0\0\0\x01\x5a\x14\0\x3e\xbc\0\0\0\x0c\x17\0\x3e\
\x47\x01\0\0\0\x0b\x07\x30\0\0\0\x01\x5a\x15\0\x56\xbc\0\0\0\x0c\x17\0\x58\x47\
\x01\0\0\0\x0b\x08\x50\0\0\0\x01\x5a\x16\0\x6c\xbc\0\0\0\x0c\x17\0\x6c\x47\x01\
\0\0\0\x0a\x4c\x01\0\0\x0d\x2e\xa8\x01\xc5\x05\x0e\x18\x25\x02\0\0\x01\xc6\x05\
\0\x0e\x1a\x25\x02\0\0\x01\xc7\x05\x08\x0e\x1b\x25\x02\0\0\x01\xc8\x05\x10\x0e\
\x1c\x25\x02\0\0\x01\xc9\x05\x18\x0e\x1d\x25\x02\0\0\x01\xca\x05\x20\x0e\x1e\
\x25\x02\0\0\x01\xcb\x05\x28\x0e\x1f\x25\x02\0\0\x01\xcc\x05\x30\x0e\x20\x25\
\x02\0\0\x01\xcd\x05\x38\x0e\x21\x25\x02\0\0\x01\xce\x05\x40\x0e\x22\x25\x02\0\
\0\x01\xcf\x05\x48\x0e\x23\x25\x02\0\0\x01\xd0\x05\x50\x0e\x24\x25\x02\0\0\x01\
\xd1\x05\x58\x0e\x25\x25\x02\0\0\x01\xd2\x05\x60\x0e\x26\x25\x02\0\0\x01\xd3\
\x05\x68\x0e\x27\x25\x02\0\0\x01\xd4\x05\x70\x0e\x28\x25\x02\0\0\x01\xd5\x05\
\x78\x0e\x29\x25\x02\0\0\x01\xd6\x05\x80\x0e\x2a\x25\x02\0\0\x01\xd7\x05\x88\
\x0e\x2b\x25\x02\0\0\x01\xd8\x05\x90\x0e\x2c\x25\x02\0\0\x01\xd9\x05\x98\x0e\
\x2d\x25\x02\0\0\x01\xda\x05\xa0\0\x04\x19\x07\x08\0\x19\0\0\0\x05\0\x08\0\x01\
\0\0\0\x04\0\0\0\x03\x05\x30\x03\x06\x30\x03\x07\x30\x03\x08\x50\0\xc0\0\0\0\
\x05\0\0\0\0\0\0\0\x25\0\0\0\x3f\0\0\0\x55\0\0\0\x5b\0\0\0\x65\0\0\0\x6b\0\0\0\
\x72\0\0\0\x76\0\0\0\x7f\0\0\0\x84\0\0\0\x98\0\0\0\xa2\0\0\0\xa7\0\0\0\xab\0\0\
\0\xb7\0\0\0\xbb\0\0\0\xc8\0\0\0\xce\0\0\0\xd4\0\0\0\xfa\0\0\0\x1d\x01\0\0\x42\
\x01\0\0\x64\x01\0\0\x68\x01\0\0\x6c\x01\0\0\x7a\x01\0\0\x7e\x01\0\0\x82\x01\0\
\0\x86\x01\0\0\x89\x01\0\0\x8c\x01\0\0\x90\x01\0\0\x94\x01\0\0\x97\x01\0\0\x9a\
\x01\0\0\x9d\x01\0\0\xa0\x01\0\0\xa3\x01\0\0\xa6\x01\0\0\xa9\x01\0\0\xb1\x01\0\
\0\xb4\x01\0\0\xb7\x01\0\0\xbd\x01\0\0\xc0\x01\0\0\xc3\x01\0\0\x55\x62\x75\x6e\
\x74\x75\x20\x63\x6c\x61\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x34\
\x2e\x30\x2e\x30\x2d\x31\x75\x62\x75\x6e\x74\x75\x31\0\x73\x72\x63\x2f\x6b\x70\
\x72\x6f\x67\x2f\x63\x61\x63\x68\x65\x73\x74\x61\x74\x2e\x62\x70\x66\x2e\x63\0\
\x2f\x68\x6f\x6d\x65\x2f\x6c\x30\x63\x61\x6c\x68\x30\x73\x74\x2f\x79\x61\x62\
\x63\x63\0\x74\x6f\x74\x61\x6c\0\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\0\x5f\x5f\
\x73\x36\x34\0\x6d\x69\x73\x73\x65\x73\0\x6d\x62\x64\0\x5f\x6c\x69\x63\x65\x6e\
\x73\x65\0\x63\x68\x61\x72\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\x49\x5a\x45\
\x5f\x54\x59\x50\x45\x5f\x5f\0\x63\x6f\x75\x6e\x74\x5f\x6d\x61\x70\0\x74\x79\
\x70\x65\0\x69\x6e\x74\0\x6d\x61\x78\x5f\x65\x6e\x74\x72\x69\x65\x73\0\x6b\x65\
\x79\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\x74\0\x5f\x5f\x75\x33\x32\0\
\x76\x61\x6c\x75\x65\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\
\x67\x5f\x61\x64\x64\x5f\x74\x6f\x5f\x70\x61\x67\x65\x5f\x63\x61\x63\x68\x65\
\x5f\x6c\x72\x75\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\
\x5f\x6d\x61\x72\x6b\x5f\x70\x61\x67\x65\x5f\x61\x63\x63\x65\x73\x73\x65\x64\0\
\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\x5f\x61\x63\x63\
\x6f\x75\x6e\x74\x5f\x70\x61\x67\x65\x5f\x64\x69\x72\x74\x69\x65\x64\0\x6b\x70\
\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\x5f\x6d\x61\x72\x6b\x5f\
\x62\x75\x66\x66\x65\x72\x5f\x64\x69\x72\x74\x79\0\x72\x65\x67\0\x72\x31\x35\0\
\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\0\x72\x31\x34\0\x72\x31\
\x33\0\x72\x31\x32\0\x62\x70\0\x62\x78\0\x72\x31\x31\0\x72\x31\x30\0\x72\x39\0\
\x72\x38\0\x61\x78\0\x63\x78\0\x64\x78\0\x73\x69\0\x64\x69\0\x6f\x72\x69\x67\
\x5f\x61\x78\0\x69\x70\0\x63\x73\0\x66\x6c\x61\x67\x73\0\x73\x70\0\x73\x73\0\
\x70\x74\x5f\x72\x65\x67\x73\0\x4c\0\0\0\x05\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9f\xeb\x01\0\x18\0\0\0\0\0\0\0\x70\
\x03\0\0\x70\x03\0\0\xd6\x03\0\0\0\0\0\0\0\0\0\x02\x03\0\0\0\x01\0\0\0\0\0\0\
\x01\x04\0\0\0\x20\0\0\x01\0\0\0\0\0\0\0\x03\0\0\0\0\x02\0\0\0\x04\0\0\0\x01\0\
\0\0\x05\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\0\0\0\0\0\0\0\x02\x06\0\0\0\0\0\0\
\0\0\0\0\x03\0\0\0\0\x02\0\0\0\x04\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\x02\x08\0\0\0\
\x19\0\0\0\0\0\0\x08\x09\0\0\0\x1f\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\0\0\0\0\
\0\0\0\x02\x0b\0\0\0\x2c\0\0\0\0\0\0\x08\x0c\0\0\0\x32\0\0\0\0\0\0\x01\x08\0\0\
\0\x40\0\0\x01\0\0\0\0\x04\0\0\x04\x20\0\0\0\x3c\0\0\0\x01\0\0\0\0\0\0\0\x41\0\
\0\0\x05\0\0\0\x40\0\0\0\x4d\0\0\0\x07\0\0\0\x80\0\0\0\x51\0\0\0\x0a\0\0\0\xc0\
\0\0\0\x57\0\0\0\0\0\0\x0e\x0d\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\x02\x10\0\0\0\x61\
\0\0\0\x15\0\0\x04\xa8\0\0\0\x69\0\0\0\x11\0\0\0\0\0\0\0\x6d\0\0\0\x11\0\0\0\
\x40\0\0\0\x71\0\0\0\x11\0\0\0\x80\0\0\0\x75\0\0\0\x11\0\0\0\xc0\0\0\0\x79\0\0\
\0\x11\0\0\0\0\x01\0\0\x7c\0\0\0\x11\0\0\0\x40\x01\0\0\x7f\0\0\0\x11\0\0\0\x80\
\x01\0\0\x83\0\0\0\x11\0\0\0\xc0\x01\0\0\x87\0\0\0\x11\0\0\0\0\x02\0\0\x8a\0\0\
\0\x11\0\0\0\x40\x02\0\0\x8d\0\0\0\x11\0\0\0\x80\x02\0\0\x90\0\0\0\x11\0\0\0\
\xc0\x02\0\0\x93\0\0\0\x11\0\0\0\0\x03\0\0\x96\0\0\0\x11\0\0\0\x40\x03\0\0\x99\
\0\0\0\x11\0\0\0\x80\x03\0\0\x9c\0\0\0\x11\0\0\0\xc0\x03\0\0\xa4\0\0\0\x11\0\0\
\0\0\x04\0\0\xa7\0\0\0\x11\0\0\0\x40\x04\0\0\xaa\0\0\0\x11\0\0\0\x80\x04\0\0\
\xb0\0\0\0\x11\0\0\0\xc0\x04\0\0\xb3\0\0\0\x11\0\0\0\0\x05\0\0\xb6\0\0\0\0\0\0\
\x01\x08\0\0\0\x40\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xc4\0\0\0\x0f\0\0\0\xc8\
\0\0\0\x01\0\0\x0c\x12\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xc4\0\0\0\x0f\0\0\0\
\xaf\x01\0\0\x01\0\0\x0c\x14\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xc4\0\0\0\x0f\
\0\0\0\x4e\x02\0\0\x01\0\0\x0c\x16\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xc4\0\0\
\0\x0f\0\0\0\xe0\x02\0\0\x01\0\0\x0c\x18\0\0\0\xa4\x03\0\0\0\0\0\x0e\x0b\0\0\0\
\x01\0\0\0\xaa\x03\0\0\0\0\0\x0e\x0b\0\0\0\x01\0\0\0\xb1\x03\0\0\0\0\0\x0e\x0b\
\0\0\0\x01\0\0\0\xb5\x03\0\0\0\0\0\x01\x01\0\0\0\x08\0\0\x01\0\0\0\0\0\0\0\x03\
\0\0\0\0\x1d\0\0\0\x04\0\0\0\x04\0\0\0\xba\x03\0\0\0\0\0\x0e\x1e\0\0\0\x01\0\0\
\0\xc3\x03\0\0\x03\0\0\x0f\0\0\0\0\x1a\0\0\0\0\0\0\0\x08\0\0\0\x1b\0\0\0\0\0\0\
\0\x08\0\0\0\x1c\0\0\0\0\0\0\0\x08\0\0\0\xc8\x03\0\0\x01\0\0\x0f\0\0\0\0\x0e\0\
\0\0\0\0\0\0\x20\0\0\0\xce\x03\0\0\x01\0\0\x0f\0\0\0\0\x1f\0\0\0\0\0\0\0\x04\0\
\0\0\0\x69\x6e\x74\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\x49\x5a\x45\x5f\x54\
\x59\x50\x45\x5f\x5f\0\x5f\x5f\x75\x33\x32\0\x75\x6e\x73\x69\x67\x6e\x65\x64\
\x20\x69\x6e\x74\0\x5f\x5f\x73\x36\x34\0\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\0\
\x74\x79\x70\x65\0\x6d\x61\x78\x5f\x65\x6e\x74\x72\x69\x65\x73\0\x6b\x65\x79\0\
\x76\x61\x6c\x75\x65\0\x63\x6f\x75\x6e\x74\x5f\x6d\x61\x70\0\x70\x74\x5f\x72\
\x65\x67\x73\0\x72\x31\x35\0\x72\x31\x34\0\x72\x31\x33\0\x72\x31\x32\0\x62\x70\
\0\x62\x78\0\x72\x31\x31\0\x72\x31\x30\0\x72\x39\0\x72\x38\0\x61\x78\0\x63\x78\
\0\x64\x78\0\x73\x69\0\x64\x69\0\x6f\x72\x69\x67\x5f\x61\x78\0\x69\x70\0\x63\
\x73\0\x66\x6c\x61\x67\x73\0\x73\x70\0\x73\x73\0\x75\x6e\x73\x69\x67\x6e\x65\
\x64\x20\x6c\x6f\x6e\x67\0\x72\x65\x67\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\
\x66\x5f\x70\x72\x6f\x67\x5f\x61\x64\x64\x5f\x74\x6f\x5f\x70\x61\x67\x65\x5f\
\x63\x61\x63\x68\x65\x5f\x6c\x72\x75\0\x6b\x70\x72\x6f\x62\x65\x2f\x61\x64\x64\
\x5f\x74\x6f\x5f\x70\x61\x67\x65\x5f\x63\x61\x63\x68\x65\x5f\x6c\x72\x75\0\x2f\
\x68\x6f\x6d\x65\x2f\x6c\x30\x63\x61\x6c\x68\x30\x73\x74\x2f\x79\x61\x62\x63\
\x63\x2f\x73\x72\x63\x2f\x6b\x70\x72\x6f\x67\x2f\x63\x61\x63\x68\x65\x73\x74\
\x61\x74\x2e\x62\x70\x66\x2e\x63\0\x4b\x50\x52\x4f\x42\x45\x5f\x42\x50\x46\x5f\
\x50\x52\x4f\x47\x28\x61\x64\x64\x5f\x74\x6f\x5f\x70\x61\x67\x65\x5f\x63\x61\
\x63\x68\x65\x5f\x6c\x72\x75\x29\x28\x73\x74\x72\x75\x63\x74\x20\x70\x74\x5f\
\x72\x65\x67\x73\x20\x2a\x72\x65\x67\x29\0\x20\x20\x20\x20\x20\x20\x20\x20\x5f\
\x5f\x73\x79\x6e\x63\x5f\x66\x65\x74\x63\x68\x5f\x61\x6e\x64\x5f\x61\x64\x64\
\x28\x26\x6d\x69\x73\x73\x65\x73\x2c\x20\x31\x29\x3b\0\x20\x20\x20\x20\x72\x65\
\x74\x75\x72\x6e\x20\x30\x3b\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\
\x72\x6f\x67\x5f\x6d\x61\x72\x6b\x5f\x70\x61\x67\x65\x5f\x61\x63\x63\x65\x73\
\x73\x65\x64\0\x6b\x70\x72\x6f\x62\x65\x2f\x6d\x61\x72\x6b\x5f\x70\x61\x67\x65\
\x5f\x61\x63\x63\x65\x73\x73\x65\x64\0\x4b\x50\x52\x4f\x42\x45\x5f\x42\x50\x46\
\x5f\x50\x52\x4f\x47\x28\x6d\x61\x72\x6b\x5f\x70\x61\x67\x65\x5f\x61\x63\x63\
\x65\x73\x73\x65\x64\x29\x28\x73\x74\x72\x75\x63\x74\x20\x70\x74\x5f\x72\x65\
\x67\x73\x20\x2a\x72\x65\x67\x29\0\x20\x20\x20\x20\x20\x20\x20\x20\x5f\x5f\x73\
\x79\x6e\x63\x5f\x66\x65\x74\x63\x68\x5f\x61\x6e\x64\x5f\x61\x64\x64\x28\x26\
\x74\x6f\x74\x61\x6c\x2c\x20\x31\x29\x3b\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\
\x66\x5f\x70\x72\x6f\x67\x5f\x61\x63\x63\x6f\x75\x6e\x74\x5f\x70\x61\x67\x65\
\x5f\x64\x69\x72\x74\x69\x65\x64\0\x6b\x70\x72\x6f\x62\x65\x2f\x61\x63\x63\x6f\
\x75\x6e\x74\x5f\x70\x61\x67\x65\x5f\x64\x69\x72\x74\x69\x65\x64\0\x4b\x50\x52\
\x4f\x42\x45\x5f\x42\x50\x46\x5f\x50\x52\x4f\x47\x28\x61\x63\x63\x6f\x75\x6e\
\x74\x5f\x70\x61\x67\x65\x5f\x64\x69\x72\x74\x69\x65\x64\x29\0\x20\x20\x20\x20\
\x20\x20\x20\x20\x5f\x5f\x73\x79\x6e\x63\x5f\x66\x65\x74\x63\x68\x5f\x61\x6e\
\x64\x5f\x61\x64\x64\x28\x26\x6d\x69\x73\x73\x65\x73\x2c\x20\x2d\x31\x29\x3b\0\
\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\x5f\x6d\x61\x72\
\x6b\x5f\x62\x75\x66\x66\x65\x72\x5f\x64\x69\x72\x74\x79\0\x6b\x70\x72\x6f\x62\
\x65\x2f\x6d\x61\x72\x6b\x5f\x62\x75\x66\x66\x65\x72\x5f\x64\x69\x72\x74\x79\0\
\x4b\x50\x52\x4f\x42\x45\x5f\x42\x50\x46\x5f\x50\x52\x4f\x47\x28\x6d\x61\x72\
\x6b\x5f\x62\x75\x66\x66\x65\x72\x5f\x64\x69\x72\x74\x79\x29\x28\x73\x74\x72\
\x75\x63\x74\x20\x70\x74\x5f\x72\x65\x67\x73\x20\x2a\x72\x65\x67\x29\0\x20\x20\
\x20\x20\x20\x20\x20\x20\x5f\x5f\x73\x79\x6e\x63\x5f\x66\x65\x74\x63\x68\x5f\
\x61\x6e\x64\x5f\x61\x64\x64\x28\x26\x74\x6f\x74\x61\x6c\x2c\x20\x2d\x31\x29\
\x3b\0\x20\x20\x20\x20\x20\x20\x20\x20\x5f\x5f\x73\x79\x6e\x63\x5f\x66\x65\x74\
\x63\x68\x5f\x61\x6e\x64\x5f\x61\x64\x64\x28\x26\x6d\x62\x64\x2c\x20\x31\x29\
\x3b\0\x74\x6f\x74\x61\x6c\0\x6d\x69\x73\x73\x65\x73\0\x6d\x62\x64\0\x63\x68\
\x61\x72\0\x5f\x6c\x69\x63\x65\x6e\x73\x65\0\x2e\x62\x73\x73\0\x2e\x6d\x61\x70\
\x73\0\x6c\x69\x63\x65\x6e\x73\x65\0\0\0\x9f\xeb\x01\0\x20\0\0\0\0\0\0\0\x44\0\
\0\0\x44\0\0\0\xf4\0\0\0\x38\x01\0\0\0\0\0\0\x08\0\0\0\xee\0\0\0\x01\0\0\0\0\0\
\0\0\x13\0\0\0\xd2\x01\0\0\x01\0\0\0\0\0\0\0\x15\0\0\0\x73\x02\0\0\x01\0\0\0\0\
\0\0\0\x17\0\0\0\x02\x03\0\0\x01\0\0\0\0\0\0\0\x19\0\0\0\x10\0\0\0\xee\0\0\0\
\x03\0\0\0\0\0\0\0\x0b\x01\0\0\x3b\x01\0\0\0\xa8\0\0\x08\0\0\0\x0b\x01\0\0\x77\
\x01\0\0\x09\xdc\0\0\x20\0\0\0\x0b\x01\0\0\xa1\x01\0\0\x05\xe4\0\0\xd2\x01\0\0\
\x03\0\0\0\0\0\0\0\x0b\x01\0\0\xec\x01\0\0\0\xf8\0\0\x08\0\0\0\x0b\x01\0\0\x25\
\x02\0\0\x09\x34\x01\0\x20\0\0\0\x0b\x01\0\0\xa1\x01\0\0\x05\x3c\x01\0\x73\x02\
\0\0\x03\0\0\0\0\0\0\0\x0b\x01\0\0\x8f\x02\0\0\0\x58\x01\0\x08\0\0\0\x0b\x01\0\
\0\xb5\x02\0\0\x09\x98\x01\0\x20\0\0\0\x0b\x01\0\0\xa1\x01\0\0\x05\x9c\x01\0\
\x02\x03\0\0\x04\0\0\0\0\0\0\0\x0b\x01\0\0\x1b\x03\0\0\0\xb0\x01\0\x08\0\0\0\
\x0b\x01\0\0\x53\x03\0\0\x09\0\x02\0\x28\0\0\0\x0b\x01\0\0\x7d\x03\0\0\x09\x04\
\x02\0\x40\0\0\0\x0b\x01\0\0\xa1\x01\0\0\x05\x0c\x02\0\x0c\0\0\0\xff\xff\xff\
\xff\x04\0\x08\0\x08\x7c\x0b\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x30\0\0\0\0\0\
\0\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\x14\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x50\0\0\0\0\0\
\0\0\xd3\0\0\0\x05\0\x08\0\x50\0\0\0\x08\x01\x01\xfb\x0e\x0d\0\x01\x01\x01\x01\
\0\0\0\x01\0\0\x01\x01\x01\x1f\x02\0\0\0\0\x16\0\0\0\x03\x01\x1f\x02\x0f\x05\
\x1e\x02\x1e\0\0\0\0\xf6\x8a\x8a\x3a\xeb\xff\xb7\x3c\x27\xea\xa4\xd9\x7f\xc3\
\x9b\xbf\x38\0\0\0\x01\xc2\xb4\x19\x30\x27\xf8\xb7\x08\x77\xac\x14\xda\xb7\x61\
\x71\x0b\x04\0\0\x09\x02\0\0\0\0\0\0\0\0\x03\x2a\x01\x05\x09\x0a\x03\x0c\x20\
\x05\x05\x3e\x02\x02\0\x01\x01\x04\0\0\x09\x02\0\0\0\0\0\0\0\0\x03\x3e\x01\x05\
\x09\x0a\x03\x0e\x20\x05\x05\x3e\x02\x02\0\x01\x01\x04\0\0\x09\x02\0\0\0\0\0\0\
\0\0\x03\xd8\0\x01\x05\x09\x0a\x03\x0d\x20\x05\x05\x3d\x02\x02\0\x01\x01\x04\0\
\0\x09\x02\0\0\0\0\0\0\0\0\x03\xec\0\x01\x05\x09\x0a\x03\x13\x20\x4b\x05\x05\
\x3e\x02\x02\0\x01\x01\x2f\x68\x6f\x6d\x65\x2f\x6c\x30\x63\x61\x6c\x68\x30\x73\
\x74\x2f\x79\x61\x62\x63\x63\0\x69\x6e\x63\x6c\x75\x64\x65\0\x73\x72\x63\x2f\
\x6b\x70\x72\x6f\x67\x2f\x63\x61\x63\x68\x65\x73\x74\x61\x74\x2e\x62\x70\x66\
\x2e\x63\0\x76\x6d\x6c\x69\x6e\x75\x78\x2e\x68\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xee\x01\0\0\x04\0\xf1\xff\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x05\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x07\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x0e\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x11\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x12\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x15\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x1b\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x1d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x1f\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x4e\0\0\0\x12\0\x03\0\0\0\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\xda\0\0\0\
\x11\0\x0b\0\x08\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\x64\x01\0\0\x12\0\x05\0\0\0\0\
\0\0\0\0\0\x30\0\0\0\0\0\0\0\x26\x01\0\0\x11\0\x0b\0\0\0\0\0\0\0\0\0\x08\0\0\0\
\0\0\0\0\xa5\x01\0\0\x12\0\x07\0\0\0\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\x01\0\0\0\
\x12\0\x09\0\0\0\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\xea\x01\0\0\x11\0\x0b\0\x10\0\0\
\0\0\0\0\0\x08\0\0\0\0\0\0\0\x3a\x01\0\0\x11\0\x0c\0\0\0\0\0\0\0\0\0\x04\0\0\0\
\0\0\0\0\x0c\x01\0\0\x11\0\x0d\0\0\0\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\x08\0\0\0\0\
\0\0\0\x01\0\0\0\x0f\0\0\0\x08\0\0\0\0\0\0\0\x01\0\0\0\x11\0\0\0\x08\0\0\0\0\0\
\0\0\x01\0\0\0\x0f\0\0\0\x08\0\0\0\0\0\0\0\x01\0\0\0\x11\0\0\0\x28\0\0\0\0\0\0\
\0\x01\0\0\0\x14\0\0\0\x08\0\0\0\0\0\0\0\x03\0\0\0\x06\0\0\0\x11\0\0\0\0\0\0\0\
\x03\0\0\0\x08\0\0\0\x15\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x23\0\0\0\0\0\0\0\
\x03\0\0\0\x0a\0\0\0\x27\0\0\0\0\0\0\0\x03\0\0\0\x07\0\0\0\x08\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x0c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x10\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x14\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x18\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x1c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x20\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x24\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x28\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x2c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x30\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x34\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x38\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x3c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x44\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x48\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x4c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x50\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x54\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x58\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x5c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x60\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x64\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x68\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x6c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x70\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x74\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x78\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x7c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x80\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x84\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x88\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x8c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x90\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x94\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x98\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x9c\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\xa0\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\xa4\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\xa8\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\xac\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\xb0\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\xb4\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\xb8\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\xbc\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\xc0\0\0\0\0\0\0\0\
\x03\0\0\0\x09\0\0\0\x08\0\0\0\0\0\0\0\x02\0\0\0\x11\0\0\0\x10\0\0\0\0\0\0\0\
\x02\0\0\0\x0f\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\x14\0\0\0\x20\0\0\0\0\0\0\0\
\x02\0\0\0\x15\0\0\0\x28\0\0\0\0\0\0\0\x02\0\0\0\x16\0\0\0\x30\0\0\0\0\0\0\0\
\x02\0\0\0\x02\0\0\0\x38\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x40\0\0\0\0\0\0\0\
\x02\0\0\0\x04\0\0\0\x48\0\0\0\0\0\0\0\x02\0\0\0\x05\0\0\0\x38\x03\0\0\0\0\0\0\
\x04\0\0\0\x11\0\0\0\x44\x03\0\0\0\0\0\0\x04\0\0\0\x0f\0\0\0\x50\x03\0\0\0\0\0\
\0\x04\0\0\0\x14\0\0\0\x68\x03\0\0\0\0\0\0\x04\0\0\0\x16\0\0\0\x80\x03\0\0\0\0\
\0\0\x04\0\0\0\x15\0\0\0\x2c\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x3c\0\0\0\0\0\0\
\0\x04\0\0\0\x03\0\0\0\x4c\0\0\0\0\0\0\0\x04\0\0\0\x04\0\0\0\x5c\0\0\0\0\0\0\0\
\x04\0\0\0\x05\0\0\0\x70\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x80\0\0\0\0\0\0\0\
\x04\0\0\0\x02\0\0\0\x90\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\xa8\0\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\xb8\0\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xc8\0\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\xe0\0\0\0\0\0\0\0\x04\0\0\0\x04\0\0\0\xf0\0\0\0\0\0\0\0\
\x04\0\0\0\x04\0\0\0\0\x01\0\0\0\0\0\0\x04\0\0\0\x04\0\0\0\x18\x01\0\0\0\0\0\0\
\x04\0\0\0\x05\0\0\0\x28\x01\0\0\0\0\0\0\x04\0\0\0\x05\0\0\0\x38\x01\0\0\0\0\0\
\0\x04\0\0\0\x05\0\0\0\x48\x01\0\0\0\0\0\0\x04\0\0\0\x05\0\0\0\x14\0\0\0\0\0\0\
\0\x03\0\0\0\x0b\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\x02\0\0\0\x2c\0\0\0\0\0\0\0\
\x03\0\0\0\x0b\0\0\0\x30\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x44\0\0\0\0\0\0\0\
\x03\0\0\0\x0b\0\0\0\x48\0\0\0\0\0\0\0\x02\0\0\0\x04\0\0\0\x5c\0\0\0\0\0\0\0\
\x03\0\0\0\x0b\0\0\0\x60\0\0\0\0\0\0\0\x02\0\0\0\x05\0\0\0\x22\0\0\0\0\0\0\0\
\x03\0\0\0\x0d\0\0\0\x26\0\0\0\0\0\0\0\x03\0\0\0\x0d\0\0\0\x32\0\0\0\0\0\0\0\
\x03\0\0\0\x0d\0\0\0\x47\0\0\0\0\0\0\0\x03\0\0\0\x0d\0\0\0\x61\0\0\0\0\0\0\0\
\x02\0\0\0\x02\0\0\0\x7f\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x9d\0\0\0\0\0\0\0\
\x02\0\0\0\x04\0\0\0\xbc\0\0\0\0\0\0\0\x02\0\0\0\x05\0\0\0\x0e\x10\x12\x13\x11\
\x0f\x14\x15\x16\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\
\x5f\x6d\x61\x72\x6b\x5f\x62\x75\x66\x66\x65\x72\x5f\x64\x69\x72\x74\x79\0\x2e\
\x72\x65\x6c\x6b\x70\x72\x6f\x62\x65\x2f\x6d\x61\x72\x6b\x5f\x62\x75\x66\x66\
\x65\x72\x5f\x64\x69\x72\x74\x79\0\x2e\x64\x65\x62\x75\x67\x5f\x61\x62\x62\x72\
\x65\x76\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\x5f\x61\
\x64\x64\x5f\x74\x6f\x5f\x70\x61\x67\x65\x5f\x63\x61\x63\x68\x65\x5f\x6c\x72\
\x75\0\x2e\x72\x65\x6c\x6b\x70\x72\x6f\x62\x65\x2f\x61\x64\x64\x5f\x74\x6f\x5f\
\x70\x61\x67\x65\x5f\x63\x61\x63\x68\x65\x5f\x6c\x72\x75\0\x2e\x74\x65\x78\x74\
\0\x2e\x72\x65\x6c\x2e\x42\x54\x46\x2e\x65\x78\x74\0\x2e\x64\x65\x62\x75\x67\
\x5f\x72\x6e\x67\x6c\x69\x73\x74\x73\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\
\x5f\x73\x74\x72\x5f\x6f\x66\x66\x73\x65\x74\x73\0\x2e\x62\x73\x73\0\x2e\x6d\
\x61\x70\x73\0\x6d\x69\x73\x73\x65\x73\0\x2e\x64\x65\x62\x75\x67\x5f\x73\x74\
\x72\0\x2e\x64\x65\x62\x75\x67\x5f\x6c\x69\x6e\x65\x5f\x73\x74\x72\0\x2e\x72\
\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x61\x64\x64\x72\0\x63\x6f\x75\x6e\x74\x5f\
\x6d\x61\x70\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x69\x6e\x66\x6f\0\
\x74\x6f\x74\x61\x6c\0\x2e\x6c\x6c\x76\x6d\x5f\x61\x64\x64\x72\x73\x69\x67\0\
\x5f\x6c\x69\x63\x65\x6e\x73\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\
\x6c\x69\x6e\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x66\x72\x61\x6d\
\x65\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\x72\x6f\x67\x5f\x6d\x61\
\x72\x6b\x5f\x70\x61\x67\x65\x5f\x61\x63\x63\x65\x73\x73\x65\x64\0\x2e\x72\x65\
\x6c\x6b\x70\x72\x6f\x62\x65\x2f\x6d\x61\x72\x6b\x5f\x70\x61\x67\x65\x5f\x61\
\x63\x63\x65\x73\x73\x65\x64\0\x6b\x70\x72\x6f\x62\x65\x5f\x62\x70\x66\x5f\x70\
\x72\x6f\x67\x5f\x61\x63\x63\x6f\x75\x6e\x74\x5f\x70\x61\x67\x65\x5f\x64\x69\
\x72\x74\x69\x65\x64\0\x2e\x72\x65\x6c\x6b\x70\x72\x6f\x62\x65\x2f\x61\x63\x63\
\x6f\x75\x6e\x74\x5f\x70\x61\x67\x65\x5f\x64\x69\x72\x74\x69\x65\x64\0\x6d\x62\
\x64\0\x63\x61\x63\x68\x65\x73\x74\x61\x74\x2e\x62\x70\x66\x2e\x63\0\x2e\x73\
\x74\x72\x74\x61\x62\0\x2e\x73\x79\x6d\x74\x61\x62\0\x2e\x72\x65\x6c\x2e\x42\
\x54\x46\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xfe\x01\0\0\x03\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x29\x1a\0\0\0\0\0\0\x17\x02\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x95\0\0\0\x01\0\0\0\x06\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x78\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x40\0\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x74\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xa0\x13\0\
\0\0\0\0\0\x10\0\0\0\0\0\0\0\x21\0\0\0\x03\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\
\0\0\0\x8b\x01\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x70\0\0\0\0\0\0\
\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x87\x01\
\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb0\x13\0\0\0\0\0\0\x10\0\0\0\
\0\0\0\0\x21\0\0\0\x05\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xce\x01\0\0\
\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xa0\0\0\0\0\0\0\0\x30\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xca\x01\0\0\x09\0\0\0\x40\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xc0\x13\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x21\0\0\0\
\x07\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x27\0\0\0\x01\0\0\0\x06\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xd0\0\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x23\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\xd0\x13\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\x21\0\0\0\x09\0\0\0\x08\0\0\0\0\0\
\0\0\x10\0\0\0\0\0\0\0\xcf\0\0\0\x08\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x20\x01\0\0\0\0\0\0\x18\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x3b\x01\0\0\x01\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x20\x01\0\0\
\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xd4\0\0\0\x01\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x28\x01\0\0\0\0\0\0\x20\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x48\x01\0\0\0\0\0\0\xc1\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x1a\x01\0\0\x01\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\x09\x02\0\0\0\0\0\0\x2a\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x16\x01\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xf0\x13\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\x21\0\0\0\x0f\0\0\0\x08\0\
\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xa8\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x33\x04\0\0\0\0\0\0\x1d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xbc\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x50\x04\0\0\
\0\0\0\0\xc4\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xb8\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\x14\0\0\0\0\0\0\xf0\
\x02\0\0\0\0\0\0\x21\0\0\0\x12\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xe1\0\
\0\0\x01\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x14\x05\0\0\0\0\0\0\xcb\x01\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\x01\0\0\x01\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xdf\x06\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xfc\0\0\0\x09\0\0\0\x40\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\x30\x17\0\0\0\0\0\0\x90\0\0\0\0\0\0\0\x21\0\0\0\x15\0\0\
\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x12\x02\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x30\x07\0\0\0\0\0\0\x5e\x07\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x0e\x02\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\xc0\x17\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\x21\0\0\0\x17\0\0\0\x08\0\0\0\0\0\0\
\0\x10\0\0\0\0\0\0\0\x9f\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x90\
\x0e\0\0\0\0\0\0\x58\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x9b\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x10\x18\0\0\0\0\
\0\0\x10\x01\0\0\0\0\0\0\x21\0\0\0\x19\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\
\0\x57\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xe8\x0f\0\0\0\0\0\0\
\x70\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x53\x01\0\
\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x20\x19\0\0\0\0\0\0\x80\0\0\0\0\
\0\0\0\x21\0\0\0\x1b\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x47\x01\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x58\x10\0\0\0\0\0\0\xd7\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x43\x01\0\0\x09\0\0\0\x40\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\xa0\x19\0\0\0\0\0\0\x80\0\0\0\0\0\0\0\x21\0\0\0\x1d\
\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xec\0\0\0\x01\0\0\0\x30\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x2f\x11\0\0\0\0\0\0\x42\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\
\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x2c\x01\0\0\x03\x4c\xff\x6f\0\0\0\x80\0\0\0\0\0\
\0\0\0\0\0\0\0\x20\x1a\0\0\0\0\0\0\x09\0\0\0\0\0\0\0\x21\0\0\0\0\0\0\0\x01\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x06\x02\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x78\x11\0\0\0\0\0\0\x28\x02\0\0\0\0\0\0\x01\0\0\0\x0e\0\0\0\x08\0\0\0\0\0\0\
\0\x18\0\0\0\0\0\0\0";
}

#ifdef __cplusplus
struct skel_cachestat *skel_cachestat::open(const struct bpf_object_open_opts *opts) { return skel_cachestat__open_opts(opts); }
struct skel_cachestat *skel_cachestat::open_and_load() { return skel_cachestat__open_and_load(); }
int skel_cachestat::load(struct skel_cachestat *skel) { return skel_cachestat__load(skel); }
int skel_cachestat::attach(struct skel_cachestat *skel) { return skel_cachestat__attach(skel); }
void skel_cachestat::detach(struct skel_cachestat *skel) { skel_cachestat__detach(skel); }
void skel_cachestat::destroy(struct skel_cachestat *skel) { skel_cachestat__destroy(skel); }
const void *skel_cachestat::elf_bytes(size_t *sz) { return skel_cachestat__elf_bytes(sz); }
#endif /* __cplusplus */

__attribute__((unused)) static void
skel_cachestat__assert(struct skel_cachestat *s __attribute__((unused)))
{
#ifdef __cplusplus
#define _Static_assert static_assert
#endif
	_Static_assert(sizeof(s->bss->total) == 8, "unexpected size of 'total'");
	_Static_assert(sizeof(s->bss->misses) == 8, "unexpected size of 'misses'");
	_Static_assert(sizeof(s->bss->mbd) == 8, "unexpected size of 'mbd'");
#ifdef __cplusplus
#undef _Static_assert
#endif
}

#endif /* __SKEL_CACHESTAT_SKEL_H__ */
