/* Verify that we don't offer names that are reserved for the
   implementation (PR c/83236).  */
/* { dg-options "-nostdinc" } */

/* Example of an identifier with a leading double-underscore.
   We shouldn't offer '__ino_t' as a suggestion for an unknown 'ino_t'.  */

typedef unsigned long int __ino_t;
ino_t inode; /* { dg-error "did you mean 'int'" } */


/* Example of a typedef with a leading double-underscore.  */

typedef unsigned char __u_char;
u_char ch; /* { dg-error "did you mean 'char'" } */


/* Example of a macro with a leading double-underscore.  */

# define __SOME_MACRO	int

SOME_MACRO foo; /* { dg-bogus "__SOME_MACRO" } */
/* { dg-error "'SOME_MACRO'" "" { target *-*-* } .-1 } */


/* If the misspelled name itself matches the "reserved" pattern, then
   it's OK to suggest such names.  */

void test (const char *buf, char ch)
{
  __builtin_strtchr (buf, ch); /* { dg-line misspelled_reserved } */
  /* { dg-warning "did you mean '__builtin_strchr'" "" { target c } misspelled_reserved } */
  /* { dg-error "not declared"  "" { target c++ } misspelled_reserved } */
  /* { dg-message "'__builtin_strrchr'"  "" { target c++ } misspelled_reserved } */
}

/* Similarly for a name that begins with a single underscore.  */

void test_2 (const char *buf, char ch)
{
  _builtin_strchr (buf, ch); /* { dg-line misspelled_one_underscore } */
  /* { dg-warning "did you mean '__builtin_strchr'" "" { target c } misspelled_one_underscore } */
  /* { dg-error "not declared"  "" { target c++ } misspelled_one_underscore } */
  /* { dg-message "'__builtin_strchr'"  "" { target c++ } misspelled_one_underscore } */
}

/* Verify that we can correct "__FILE_" to "__FILE__".  */

const char * test_3 (void)
{
  return __FILE_; /* { dg-line misspelled__FILE_ } */
  /* { dg-error "did you mean '__FILE__'" "" { target c } misspelled__FILE_ } */
  /* { dg-error "not declared"  "" { target c++ } misspelled__FILE_ } */
  /* { dg-message "'__FILE__'"  "" { target c++ } misspelled__FILE_ } */
}
