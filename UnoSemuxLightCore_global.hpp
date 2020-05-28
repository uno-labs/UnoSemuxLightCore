#pragma once

#include "../GpCore/GpCore.hpp"
#include "../GpCryptoCore/GpCryptoCore.hpp"

#if defined(UNOSEMUXLIGHTCORE_LIBRARY)
	#define UNOSEMUXLIGHTCORE_API GP_DECL_EXPORT
#else
	#define UNOSEMUXLIGHTCORE_API GP_DECL_IMPORT
#endif

using namespace GPlatform;
