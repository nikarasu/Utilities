#pragma once
#define CU_MIN(a, b) (((a) < (b)) ? (a) : (b))

#define CU_MAX(a, b) (((a) > (b)) ? (a) : (b))

#define CLAMP(val, a, b) (((val) < (a))) ? (a) : (((val) > (b)) ? (b) : (val))

#define PI		3.14159265358979323846
#define PI_F	3.14159265358979323846f
#define _2PI_F 6.283185307f
#define _1DIVPI_F 0.318309886f
#define _1DIV2PI_F 0.159154943f
#define _PIDIV2_F 1.570796327f
#define _PIDIV4_F 0.785398163f

#define INT_MAX       2147483647    // maximum (signed) int value
#define UINT_MAX      0xffffffff    // maximum unsigned int value

#define TO_RAD_CONSTANT (PI_F / 180.f)
#define TO_DEG_CONSTANT (180.f / PI_F)
#define TO_RAD(angleInDegrees) (angleInDegrees * TO_RAD_CONSTANT)
#define TO_DEG(angleInRadians) (angleInRadians * TO_DEG_CONSTANT)

#define SAFE_DELETE(aPtr)\
		delete aPtr;\
		aPtr = nullptr;		

#define SAFE_RELEASE(aResource)\
		if (aResource)\
		{\
			aResource->Release();\
			aResource = nullptr;\
		}

#ifdef _RETAIL
#define ALLOW_DEOPTIMIZE false
#else
#define ALLOW_DEOPTIMIZE true
#endif

#if ALLOW_DEOPTIMIZE
#define PRAGMA_DEOPTIMIZE __pragma(optimize("", off))
#define PRAGMA_REOPTIMIZE __pragma(optimize("", on))
#else
#define PRAGMA_DEOPTIMIZE
#define PRAGMA_REOPTIMIZE
#endif //ALLOW_DEOPTIMIZE

#ifdef DLLEXPORT
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

#define UNUSED(aVar) aVar

#define ARRAY_SIZE(aStaticArray) (sizeof(aStaticArray) / sizeof(*aStaticArray))