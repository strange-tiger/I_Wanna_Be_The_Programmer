// Type.h : 공통 타입 헤더 파일
#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef int8_t			int8;
typedef int16_t			int16;
typedef int32_t			int32;
typedef int64_t			int64;
typedef uint8_t			uint8;
typedef uint16_t		uint16;
typedef uint32_t		uint32;
typedef uint64_t		uint64;

//위치 좌표 값
typedef struct tagPosition {
	int32 X;	//위치 좌표 x
	int32 Y;	//위치 좌표 y
} Position;