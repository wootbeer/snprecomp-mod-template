#ifndef SNP_H
#define SNP_H

// Basic N64 types.
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define NULL ((void*)0)

// Game variables we know about. These are the same on the Japanese ROM
// and the English translation.
// From snprecomp's src/game/extras.cpp (the Cheats tab uses them).
#define SNP_TIME        (*(volatile s32*)0x800D5A94) // time left
#define SNP_HEALTH      (*(volatile s32*)0x800D5A98) // health, 100 is full
#define SNP_CONTINUES   (*(volatile s16*)0x800D5C0E) // continues left

#define SNP_HEALTH_FULL 100

#endif
