/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */

/* THIS FILE IS AUTOGENERATED BY BPFTOOL! */
#ifndef __SKEL_MEMLEAK_SKEL_H__
#define __SKEL_MEMLEAK_SKEL_H__

#include <errno.h>
#include <stdlib.h>
#include <bpf/libbpf.h>

struct skel_memleak {
	struct bpf_object_skeleton *skeleton;
	struct bpf_object *obj;

#ifdef __cplusplus
	static inline struct skel_memleak *open(const struct bpf_object_open_opts *opts = nullptr);
	static inline struct skel_memleak *open_and_load();
	static inline int load(struct skel_memleak *skel);
	static inline int attach(struct skel_memleak *skel);
	static inline void detach(struct skel_memleak *skel);
	static inline void destroy(struct skel_memleak *skel);
	static inline const void *elf_bytes(size_t *sz);
#endif /* __cplusplus */
};

static void
skel_memleak__destroy(struct skel_memleak *obj)
{
	if (!obj)
		return;
	if (obj->skeleton)
		bpf_object__destroy_skeleton(obj->skeleton);
	free(obj);
}

static inline int
skel_memleak__create_skeleton(struct skel_memleak *obj);

static inline struct skel_memleak *
skel_memleak__open_opts(const struct bpf_object_open_opts *opts)
{
	struct skel_memleak *obj;
	int err;

	obj = (struct skel_memleak *)calloc(1, sizeof(*obj));
	if (!obj) {
		errno = ENOMEM;
		return NULL;
	}

	err = skel_memleak__create_skeleton(obj);
	if (err)
		goto err_out;

	err = bpf_object__open_skeleton(obj->skeleton, opts);
	if (err)
		goto err_out;

	return obj;
err_out:
	skel_memleak__destroy(obj);
	errno = -err;
	return NULL;
}

static inline struct skel_memleak *
skel_memleak__open(void)
{
	return skel_memleak__open_opts(NULL);
}

static inline int
skel_memleak__load(struct skel_memleak *obj)
{
	return bpf_object__load_skeleton(obj->skeleton);
}

static inline struct skel_memleak *
skel_memleak__open_and_load(void)
{
	struct skel_memleak *obj;
	int err;

	obj = skel_memleak__open();
	if (!obj)
		return NULL;
	err = skel_memleak__load(obj);
	if (err) {
		skel_memleak__destroy(obj);
		errno = -err;
		return NULL;
	}
	return obj;
}

static inline int
skel_memleak__attach(struct skel_memleak *obj)
{
	return bpf_object__attach_skeleton(obj->skeleton);
}

static inline void
skel_memleak__detach(struct skel_memleak *obj)
{
	return bpf_object__detach_skeleton(obj->skeleton);
}

static inline const void *skel_memleak__elf_bytes(size_t *sz);

static inline int
skel_memleak__create_skeleton(struct skel_memleak *obj)
{
	struct bpf_object_skeleton *s;
	int err;

	s = (struct bpf_object_skeleton *)calloc(1, sizeof(*s));
	if (!s)	{
		err = -ENOMEM;
		goto err;
	}

	s->sz = sizeof(*s);
	s->name = "skel_memleak";
	s->obj = &obj->obj;

	s->data = (void *)skel_memleak__elf_bytes(&s->data_sz);

	obj->skeleton = s;
	return 0;
err:
	bpf_object__destroy_skeleton(s);
	return err;
}

static inline const void *skel_memleak__elf_bytes(size_t *sz)
{
	*sz = 488;
	return (const void *)"\
\x7f\x45\x4c\x46\x02\x01\x01\0\0\0\0\0\0\0\0\0\x01\0\xf7\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xa8\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\x40\0\x05\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x15\0\0\0\x04\0\xf1\xff\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x2e\x74\x65\x78\x74\0\x2e\x6c\x6c\x76\x6d\x5f\
\x61\x64\x64\x72\x73\x69\x67\0\x6d\x65\x6d\x6c\x65\x61\x6b\x2e\x62\x70\x66\x2e\
\x63\0\x2e\x73\x74\x72\x74\x61\x62\0\x2e\x73\x79\x6d\x74\x61\x62\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x23\0\0\0\x03\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\x70\0\0\0\0\0\0\0\x33\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x07\0\0\0\x03\x4c\xff\x6f\0\0\0\x80\0\0\0\0\0\0\0\0\0\0\0\0\x70\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x2b\0\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\x30\0\
\0\0\0\0\0\0\x01\0\0\0\x02\0\0\0\x08\0\0\0\0\0\0\0\x18\0\0\0\0\0\0\0";
}

#ifdef __cplusplus
struct skel_memleak *skel_memleak::open(const struct bpf_object_open_opts *opts) { return skel_memleak__open_opts(opts); }
struct skel_memleak *skel_memleak::open_and_load() { return skel_memleak__open_and_load(); }
int skel_memleak::load(struct skel_memleak *skel) { return skel_memleak__load(skel); }
int skel_memleak::attach(struct skel_memleak *skel) { return skel_memleak__attach(skel); }
void skel_memleak::detach(struct skel_memleak *skel) { skel_memleak__detach(skel); }
void skel_memleak::destroy(struct skel_memleak *skel) { skel_memleak__destroy(skel); }
const void *skel_memleak::elf_bytes(size_t *sz) { return skel_memleak__elf_bytes(sz); }
#endif /* __cplusplus */

__attribute__((unused)) static void
skel_memleak__assert(struct skel_memleak *s __attribute__((unused)))
{
#ifdef __cplusplus
#define _Static_assert static_assert
#endif
#ifdef __cplusplus
#undef _Static_assert
#endif
}

#endif /* __SKEL_MEMLEAK_SKEL_H__ */