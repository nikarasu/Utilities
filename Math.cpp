#include "stdafx.h"
#include "Math.h"

namespace CU = CommonUtilities;

uint8 CU::CreateRotationOrder(CU::EAxis aAxis1, CU::EAxis aAxis2, CU::EAxis aAxis3)
{
	return (aAxis3 << 4) | (aAxis2 << 2) | aAxis1;
}