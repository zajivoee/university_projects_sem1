#include "types.h"
#include "stat.h"
#include "user.h"

static void
putc(int fd, char c)
{
  write(fd, &c, 1);
}

static void
printint(int fd, int xx, int base, int sgn, int len)
{
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
  if(sgn && xx < 0){
    neg = 1;
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  while (i < len - neg) {
    buf[i++] = '0';
  }
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
    putc(fd, buf[i]);
}

int readint(char *fmt, int *l)
{
  int i;
  for (i = 0; fmt[i] >= '0' && fmt[i] <= '9'; i++) {
    *l = *l*10 + fmt[i] - '0';
  }
  return i;
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void
printf(int fd, char *fmt, ...)
{
  char *s;
  int c, i, state, len;
  uint *ap;

  state = 0;
  ap = (uint*)(void*)&fmt + 1;
  for(i = 0; fmt[i]; i++){
    c = fmt[i] & 0xff;
    if(state == 0){
      if(c == '%'){
        state = '%';
        len = 0;
      } else {
        putc(fd, c);
      }
    } else if(state == '%'){
      if(c == '0'){
        i += readint(&fmt[i+1], &len);
        continue;
      }
      if(c == 'd'){
        printint(fd, *ap, 10, 1, len);
        ap++;
      } else if(c == 'x' || c == 'p'){
        printint(fd, *ap, 16, 0, len);
        ap++;
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
          putc(fd, *s);
          s++;
        }
      } else if(c == 'c'){
        putc(fd, *ap);
        ap++;
      } else if(c == '%'){
        putc(fd, c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
        putc(fd, c);
      }
      state = 0;
    }
  }
}
