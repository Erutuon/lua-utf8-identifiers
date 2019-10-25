/*
** Parsed from DerivedCoreProperties.txt, version __UNICODE_VERSION__.
** For more information, see https://www.unicode.org/reports/tr31/.
*/

/* #define CHECK_BINARY_SEARCH */
#ifdef CHECK_BINARY_SEARCH
#include <stdio.h>
#endif
#include <stddef.h> /* size_t */

#define MAXUNICODE  0x10FFFF

#define IN_RANGES(ranges, code_point) \
  is_in_ranges((ranges), sizeof (ranges) / sizeof (ranges)[0], (code_point))

typedef struct {
  const unsigned int low, high;
} __TYPE_NAME__;

__ARRAYS__

int is_in_ranges (const __TYPE_NAME__ *const ranges, const size_t length,
                  const unsigned int code_point) {
  size_t low = 0, mid, high = length - 1;
  while (low <= high) {
    mid = (high + low) / 2;
#ifdef CHECK_BINARY_SEARCH
    printf("U+%04X <= U+%04X <= U+%04X? (%d, %d)\n",
      ranges[mid].low, code_point, ranges[mid].high, (int) low, (int) high);
#endif
    if (code_point < ranges[mid].low)
      high = mid - 1;
    else if (code_point <= ranges[mid].high)
      return 1;
    else
      low = mid + 1;
  }
  return 0;
}

/*
** Assumes that ASCII characters (0x00-0x7F) have already been validated,
** and that there are no invalid bytes (0xC0, 0xC1, 0xF5-0xFF).
*/
static const char *check_utf8_identifier(const char *const ident, const size_t len) {
  size_t i;
  static const unsigned int limits[] = {0xFF, 0x7F, 0x7FF, 0xFFFF};
  for (i = 0; i < len; i++) {
    unsigned int c = ident[i];
    if (c > 0x7F) {
      /* based on utf8_decode in lutf8lib.c */
      unsigned int code_point = 0;
      int count = 0;  /* to count number of continuation bytes */
      while (c & 0x40) {  /* still have continuation bytes? */
        int cc;
        if (++count + i >= len /* have reached end of string */
            || (cc = ident[i + count], /* read next byte */
            (cc & 0xC0) != 0x80)) { /* not a continuation byte? */
          return "missing continuation byte";
        }
        code_point = (code_point << 6) | (cc & 0x3F);  /* add lower 6 bits from cont. byte */
        c <<= 1;  /* to test next bit */
      }
      code_point |= ((c & 0x7F) << (count * 5));  /* add first byte */
      if (count > 3 || code_point > MAXUNICODE || code_point <= limits[count])
        return "invalid UTF-8";
      else if (!(i == 0 ? IN_RANGES(XID_Start, code_point)
                        : IN_RANGES(XID_Continue, code_point)))
        return "disallowed code point in identifier";
      i += count;  /* skip continuation bytes read */
    }
  }
  return NULL;
}
