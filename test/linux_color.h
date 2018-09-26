#ifndef __LINUX_COLOR_H__
#define __LINUX_COLOR_H__

#define COLOR_NORMAL    "\x1B[0m"
#define COLOR_RED       "\x1B[31m"
#define COLOR_GREEN     "\x1B[32m"
#define COLOR_BLUE      "\x1B[34m"

#define COLOR_TEXT(T, C) C T COLOR_NORMAL

#endif
