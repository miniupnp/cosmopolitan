/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/calls/calls.h"
#include "libc/calls/internal.h"
#include "libc/dce.h"

/**
 * Returns current working directory.
 *
 * @param buf is where UTF-8 NUL-terminated path string gets written,
 *     which may be NULL to ask this function to malloc a buffer
 * @param size is number of bytes available in buf, e.g. PATH_MAX,
 *     which may be 0 if buf NULL
 * @return buf containing system-normative path or NULL w/ errno
 * @see get_current_dir_name() which is better
 * @error ERANGE, EINVAL
 */
char *(getcwd)(char *buf, size_t size) {
  if (buf && size) buf[0] = '\0';
  if (!IsWindows()) {
    if (IsXnu()) {
      return sys_getcwd_xnu(buf, size);
    } else if (sys_getcwd(buf, size) != (void *)-1) {
      return buf;
    } else {
      return NULL;
    }
  } else {
    return sys_getcwd_nt(buf, size);
  }
}
