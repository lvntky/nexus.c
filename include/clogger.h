/**
 * @file clogger.h
 * @brief CLogger - a lightweight, header-only logging library for C.
 *
 * CLogger provides a simple and efficient logging mechanism for C programs.
 * It includes a macro, LOG_INFO, which logs informational messages along with
 * file name, line number, and execution time.
 *
 * Usage example:
 * @code
 * #include "clogger.h"
 *
 * int main() {
 *     LOG_INFO("Hello, CLogger!\n");
 *     return 0;
 * }
 * @endcode
 *
 * Author: Levent Kaya
 */

#ifndef _CLOGGER_H_
#define _CLOGGER_H_

#include <time.h>

#define LOG_INFO(fmt, ...)                                                   \
	do {                                                                 \
		clock_t log_start = clock();                                 \
		fprintf(stderr, "\033[0;33mINFO:\033[0m %s:%d - ", __FILE__, \
			__LINE__);                                           \
		fprintf(stderr, fmt, __VA_ARGS__);                           \
		clock_t log_end = clock();                                   \
		fprintf(stderr, " [Execution Time: %.2f ms]\n",              \
			((double)(log_end - log_start) * 1000.0) /           \
				CLOCKS_PER_SEC);                             \
	} while (0)

#define LOG_OK(fmt, ...)                                                   \
	do {                                                               \
		clock_t log_start = clock();                               \
		fprintf(stderr, "\033[0;32mOK:\033[0m %s:%d - ", __FILE__, \
			__LINE__);                                         \
		fprintf(stderr, fmt, __VA_ARGS__);                         \
		clock_t log_end = clock();                                 \
		fprintf(stderr, " [Execution Time: %.2f ms]\n",            \
			((double)(log_end - log_start) * 1000.0) /         \
				CLOCKS_PER_SEC);                           \
	} while (0)

#define LOG_ERROR(fmt, ...)                                                   \
	do {                                                                  \
		clock_t log_start = clock();                                  \
		fprintf(stderr, "\033[0;31mERROR:\033[0m %s:%d - ", __FILE__, \
			__LINE__);                                            \
		fprintf(stderr, fmt, __VA_ARGS__);                            \
		clock_t log_end = clock();                                    \
		fprintf(stderr, " [Execution Time: %.2f ms]\n",               \
			((double)(log_end - log_start) * 1000.0) /            \
				CLOCKS_PER_SEC);                              \
	} while (0)

#endif