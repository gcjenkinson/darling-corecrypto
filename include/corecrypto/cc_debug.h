/*
 *  cc_debug.h
 *  corecrypto
 *
 *  Created on 01/25/2012
 *
 *  Copyright (c) 2012,2014,2015 Apple Inc. All rights reserved.
 *
 */

//debug configuration header file
#ifndef _CORECRYPTO_CCN_DEBUG_H_
#define _CORECRYPTO_CCN_DEBUG_H_

#include <corecrypto/cc_config.h>

// DO NOT INCLUDE this HEADER file in CoreCrypto files added for XNU project or headers
// included by external clients.

// ========================
// Printf for corecrypto
// ========================
#if CC_KERNEL
#include <pexpert/pexpert.h>
#define cc_printf(x...) kprintf(x)
extern int printf(const char *format, ...) __printflike(1,2);
#elif CC_USE_S3
#include <stdio.h>
#define cc_printf(x...) printf(x)
#else
#include <stdio.h>
#define cc_printf(x...) fprintf(stderr, x)
#endif

// ========================
// Integer types
// ========================

#if CC_KERNEL
/* Those are not defined in libkern */
#define PRIx64 "llx"
#define PRIx32 "x"
#define PRIx16 "hx"
#define PRIx8  "hhx"
#else
#include <inttypes.h>
#endif

#if  CCN_UNIT_SIZE == 8
#define CCPRIx_UNIT ".016" PRIx64
#elif  CCN_UNIT_SIZE == 4
#define CCPRIx_UNIT ".08" PRIx32
#elif CCN_UNIT_SIZE == 2
#define CCPRIx_UNIT ".04" PRIx16
#elif CCN_UNIT_SIZE == 1
#define CCPRIx_UNIT ".02" PRIx8
#else
#error invalid CCN_UNIT_SIZE
#endif

// ========================
// Print utilities for corecrypto
// ========================

#include <corecrypto/cc.h>

/* Print a byte array of arbitrary size */
CC_INLINE
void cc_print(const char* label, size_t count, const uint8_t* array) {
	printf("%s: ", label);
	for (size_t i = 0; i < count; ++i)
		printf("%02x", array[i]);
};

CC_INLINE
void cc_println(const char* label, size_t count, const uint8_t* array) {
	cc_print(label, count, array);
	putchar('\n');
};

CC_INLINE
void cc_print_be(const char* label, size_t size, const uint8_t* array) {
	printf("%s: ", label);
	for (size_t i = size; i > 0; --i)
		printf("%02x", array[i - 1]);
};

CC_INLINE
void cc_println_be(const char* label, size_t count, const uint8_t* array) {
	cc_print_be(label, count, array);
	putchar('\n');
};

#endif /* _CORECRYPTO_CCN_DEBUG_H_ */
