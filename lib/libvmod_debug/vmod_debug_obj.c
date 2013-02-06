/*-
 * Copyright (c) 2013 Varnish Software AS
 * All rights reserved.
 *
 * Author: Poul-Henning Kamp <phk@FreeBSD.org>
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
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "config.h"

#include <stdlib.h>

#include "cache/cache.h"

#include "vrt.h"
#include "vcc_if.h"

struct vmod_obj {
	unsigned		magic;
#define VMOD_OBJ_MAGIC		0xccbd9b77
	int foobar;
};

VCL_VOID
vmod_obj(struct req *req, struct vmod_obj **op, VCL_STRING s)
{
	struct vmod_obj *o;

	(void)req;
	(void)s;
	AN(op);
	if (*op == NULL) {
		/* INIT */
		ALLOC_OBJ(o, VMOD_OBJ_MAGIC);
		*op = o;
		o->foobar = 42;
		AN(*op);
	} else {
		/* FINI */
		FREE_OBJ(*op);
		*op = NULL;
	}
}

VCL_STRING
vmod_obj__foo(struct req *req, struct vmod_obj *o, VCL_STRING s)
{
	(void)req;
	(void)s;
	CHECK_OBJ_NOTNULL(o, VMOD_OBJ_MAGIC);
	assert(o->foobar == 42);
	return ("BOO");
}

VCL_TIME
vmod_obj__date(struct req *req, struct vmod_obj *o)
{
	(void)req;
	CHECK_OBJ_NOTNULL(o, VMOD_OBJ_MAGIC);
	assert(o->foobar == 42);
	return (21.4);
}