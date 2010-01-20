#include <stdlib.h>
#include <execinfo.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"

#define DONT_DIE

void real_UNIMPLEMENTED(const char* file, const char* function) {
#ifdef DONT_DIE
        fprintf(stderr, "Unimplemented function: %s:%s\n", file,function);
#else
        void* symlocs[20];
        char** syms;
        int count,i;
        count = backtrace(symlocs,20);
        fprintf(stderr, "\nFunction not implemented. Backtrace:\n");
        syms = backtrace_symbols(symlocs, count);
        for (i = 0; i < count; i++)
                fprintf(stderr,"\t%3d: %s\n",i, syms[i]);
        fprintf(stderr,"Aborting\n");
        
        abort();
#endif
}


gboolean flags[FL_NFLAGS];

void set_flag(flag_t fl, gboolean value) {
        assert(fl >= 0 && fl < FL_NFLAGS);
        flags[fl] = value;
}
gboolean get_flag(flag_t fl) {
        assert(fl >= 0 && fl < FL_NFLAGS);
        return flags[fl];
}

void init_flags() {
  // initialize everything to FALSE..
  int i;
  for (i = 0; i < FL_NFLAGS; i++)
    flags[i] = FALSE;
  set_flag(FL_ALPHABET_LATIN, TRUE);
  set_flag(FL_ALPHABET_NUMBERS, TRUE);
  set_flag(FL_ATTACH_LOG, TRUE);
  set_flag(FL_CURRENT_ONLY, TRUE);
  set_flag(FL_OMIT_FRAGMENTS, TRUE);
  set_flag(FL_RESCAN, TRUE);
  set_flag(FL_SHOW_CLASS, TRUE);
}
