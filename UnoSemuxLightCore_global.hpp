#pragma once

#include "../../GPlatform/GpCore2/GpCore.hpp"
#include "../../GPlatform/GpCryptoCore/GpCryptoCore.hpp"

#if defined(UNOSEMUXLIGHTCORE_LIBRARY)
	#define UNOSEMUXLIGHTCORE_API GP_DECL_EXPORT
#else
	#define UNOSEMUXLIGHTCORE_API GP_DECL_IMPORT
#endif

using namespace GPlatform;
